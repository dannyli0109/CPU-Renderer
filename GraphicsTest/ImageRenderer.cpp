#include "ImageRenderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"


ImageRenderer::ImageRenderer(int width, int height)
{
	SetSize(width, height);
	CreateImage();
	CreateQuad();
}

void ImageRenderer::CreateImage()
{
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, image.data());

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageRenderer::CreateQuad()
{
	glGenBuffers(1, &quadBuffer);

	float vertexPositionData[] = {
		1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,

		-1.0f, -1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertexPositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ImageRenderer::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void ImageRenderer::BindVertex(unsigned int id)
{
	activeVertex = id;
}

void ImageRenderer::BindIndex(unsigned int id)
{
	activeIndex = id;
}

void ImageRenderer::BindTexture(unsigned int id)
{
	activeTexture = id;
}

void ImageRenderer::UnbindVertex()
{
	activeVertex = 0;
}

void ImageRenderer::UnbindIndex()
{
	activeIndex = 0;
}

void ImageRenderer::UnbindTexture()
{
	activeTexture = 0;
}

unsigned int ImageRenderer::GetNextId()
{
	return ++bufferCount;
}

unsigned int ImageRenderer::UploadVertexData(const std::vector<Vertex>& vertexData)
{
	unsigned int id = GetNextId();
	BindVertex(id);
	positions[activeVertex].reserve(vertexData.size());
	uvs[activeVertex].reserve(vertexData.size());
	normals[activeVertex].reserve(vertexData.size());
	vertTangents[activeVertex].reserve(vertexData.size());
	vertBitangents[activeVertex].reserve(vertexData.size());

	for (int i = 0; i < vertexData.size(); i++)
	{
		positions[activeVertex].push_back(vertexData[i].position);
		uvs[activeVertex].push_back(vertexData[i].uv);
		normals[activeVertex].push_back(vertexData[i].normal);
		vertTangents[activeVertex].push_back(vertexData[i].vertTangent);
		vertBitangents[activeVertex].push_back(vertexData[i].vertBitangent);
	}
	UnbindVertex();
	return id;
}

unsigned int ImageRenderer::UploadIndexData(const std::vector<unsigned short>& indexData)
{
	unsigned int id = GetNextId();
	BindIndex(id);
	indices[activeIndex].reserve(indexData.size());
	for (int i = 0; i < indexData.size(); i++)
	{
		indices[activeIndex].push_back(indexData[i]);
	}
	UnbindIndex();
	return id;
}

unsigned int ImageRenderer::UploadTexture(const unsigned char* data, int& width, int& height, int& channels)
{
	unsigned int id = GetNextId();
	BindTexture(id);

	std::vector<std::vector<unsigned char>> texture;
	texture.reserve(height);

	for (int y = 0; y < height; y++)
	{
		std::vector<unsigned char> row;
		row.reserve(width * 4);
		for (int x = 0; x < width; x++)
		{
			unsigned char r = data[y * width * channels + x * channels];
			unsigned char g = data[y * width * channels + x * channels + 1];
			unsigned char b = data[y * width * channels + x * channels + 2];
			unsigned char a = channels == 4 ? data[y * width * channels + x * channels + 3] : 255;
			row.push_back(r);
			row.push_back(g);
			row.push_back(b);
			row.push_back(a);
		}
		texture.push_back(row);
	}
	textures[activeTexture] = texture;

	UnbindTexture();
	//textureUnits.push_back()
	// map of 1d array of unsigned char	
	return id;
}

void ImageRenderer::ActiveTexture(int textureUnit)
{
	textureUnits[textureUnit] = activeTexture;
}

//Vector4 ImageRenderer::TextureLookup(const std::vector<std::vector<unsigned char>>& texture, float u, float v)
//{
//	int i = round(u * (texture[0].size() / 4) - 0.5f);
//	int j = round(v * texture.size() - 0.5f);
//	
//	return GetTexturePixel(texture, i % (texture[0].size() / 4), j % (texture.size()));
//}
//
//Vector4 ImageRenderer::GetTexturePixel(const std::vector<std::vector<unsigned char>>& texture, int i, int j)
//{
//	return Vector4(
//		texture[j][i * 4] / 255.0f,
//		texture[j][i * 4 + 1] / 255.0f,
//		texture[j][i * 4 + 2] / 255.0f,
//		texture[j][i * 4 + 3] / 255.0f
//	);
//}

Vector4 lerp(float coe, Vector4 a, Vector4 b) {
	return a + (b - a) * coe;
}
Vector4 ImageRenderer::TextureLookup(const std::vector<std::vector<unsigned char>>& texture, float u, float v)
{
	float uImg = u * (texture[0].size() / 4);
	float vImg = v * texture.size();

	Vector2 u00(std::floor(uImg), std::floor(vImg));
	Vector2 u10(std::ceil(uImg), std::floor(vImg));
	Vector2 u01(std::floor(uImg), std::ceil(vImg));
	Vector2 u11(std::ceil(uImg), std::ceil(vImg));

	float s = uImg - u00.x;
	float t = vImg - u00.y;

	Vector4 u0 = lerp(s, GetTexturePixel(texture, u00.x, u00.y), GetTexturePixel(texture, u10.x, u10.y));
	Vector4 u1 = lerp(s, GetTexturePixel(texture, u01.x, u01.y), GetTexturePixel(texture, u11.x, u11.y));

	return lerp(t, u0, u1);
}

Vector4 ImageRenderer::GetTexturePixel(const std::vector<std::vector<unsigned char>>& texture, int i, int j)
{
	i = i % (texture[0].size() / 4);
	j = j % texture.size();
	return Vector4(
		texture[j][i * 4] / 255.0f,
		texture[j][i * 4 + 1] / 255.0f,
		texture[j][i * 4 + 2] / 255.0f,
		texture[j][i * 4 + 3] / 255.0f
	);
}

void ImageRenderer::SetUniform(std::string s, Matrix4 m)
{
	uniformM4[s] = m;
}

void ImageRenderer::SetUniform(std::string s, int i)
{
	uniformI1[s] = i;
}

void ImageRenderer::SetUniform(std::string s, float f)
{
	uniformF1[s] = f;
}

void ImageRenderer::SetUniform(std::string s, Vector3 v)
{
	uniformV3[s] = v;
}

void ImageRenderer::SetPixel(int x, int y, float red, float green, float blue)
{
	if (x < 0 || x >= w) return;
	if (y < 0 || y >= h) return;
	//Unsafe function! Setting a pixel outside the bounds of the screen might crash the program.
	frameBuffer[y * w + x] = { red, green, blue };
}

void ImageRenderer::SetSize(int width, int height)
{
	w = width;
	h = height;
	image.resize(w * h);
	frameBuffer.resize(w * h);
	depthBuffer.resize(w * h);
	Clear();
}

void ImageRenderer::DrawImage(ShaderProgram* shader)
{
	PupulateTexture();
	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, image.data());
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	GLuint texLocation = shader->GetUniformLocation("defaultTexture");
	glUniform1i(texLocation, 0);

	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


	ShaderProgram::ClearPrograms();
}

void ImageRenderer::Draw()
{
	if (activeVertex == 0 || activeIndex == 0) return;
	float f1 = (100 - 0.1) / 2.0;
	float f2 = (100 + 0.1) / 2.0;
	Matrix4 modelMatrix = uniformM4["modelMatrix"];
	Matrix4 viewMatrix = uniformM4["viewMatrix"];
	Matrix4 projectionMatrix = uniformM4["projectionMatrix"];
	Matrix4 viewportMatrix = uniformM4["viewportMatrix"];
	
	//int diffuseTextureUnit = uniformI1["diffuseTexture"];
	//std::vector<std::vector<unsigned char>>& diffuseTexture = textures[textureUnits[diffuseTextureUnit]];

	Matrix4 m = projectionMatrix * viewMatrix * modelMatrix;

	for (int i = 0; i < indices[activeIndex].size(); i+=3)
	{
		unsigned short i1 = indices[activeIndex][i];
		unsigned short i2 = indices[activeIndex][i + 1];
		unsigned short i3 = indices[activeIndex][i + 2];

		Vector4 p1 = Vector4(positions[activeVertex][i1], 1);
		Vector4 p2 = Vector4(positions[activeVertex][i2], 1);
		Vector4 p3 = Vector4(positions[activeVertex][i3], 1);

		Vector4 cp1 = m * p1;
		Vector4 cp2 = m * p2;
		Vector4 cp3 = m * p3;

		std::vector<Vector4> verts = { cp1, cp2, cp3 };
		for (Vector4& p : verts)
		{
			//p /= p.w;
			//p.w = 1;

			p.x /= p.w;
			p.y /= p.w;
			p.z /= p.w;
		}

		for (Vector4& p : verts)
		{
			/*p.x = 0.5f * w * (p.x + 1.0f);
			p.y = h * (1.0f - 0.5f * (p.y + 1.0f));
			p.z = p.z * f1 + f2;*/
			Vector4 newP(p.x, p.y, p.z, 1);

			newP = viewportMatrix * newP;
			p.x = newP.x;
			p.y = newP.y;
			p.z = newP.z;
		}

		Vector3 wp1 = modelMatrix * p1;
		Vector3 wp2 = modelMatrix * p2;
		Vector3 wp3 = modelMatrix * p3;

		Vector2 uv1 = uvs[activeVertex][i1];
		Vector2 uv2 = uvs[activeVertex][i2];
		Vector2 uv3 = uvs[activeVertex][i3];

		Vector3 t1 = Normalize(modelMatrix * Vector4(vertTangents[activeVertex][i1], 0));
		Vector3 t2 = Normalize(modelMatrix * Vector4(vertTangents[activeVertex][i2], 0));
		Vector3 t3 = Normalize(modelMatrix * Vector4(vertTangents[activeVertex][i3], 0));

		Vector3 b1 = Normalize(modelMatrix * Vector4(vertBitangents[activeVertex][i1], 0));
		Vector3 b2 = Normalize(modelMatrix * Vector4(vertBitangents[activeVertex][i2], 0));
		Vector3 b3 = Normalize(modelMatrix * Vector4(vertBitangents[activeVertex][i3], 0));

		Vector3 n1 = Normalize(modelMatrix * Vector4(normals[activeVertex][i1], 0));
		Vector3 n2 = Normalize(modelMatrix * Vector4(normals[activeVertex][i2], 0));
		Vector3 n3 = Normalize(modelMatrix * Vector4(normals[activeVertex][i3], 0));

		//Matrix3 tbn1(
		//	t1.x, t1.y, t1.z,
		//	b1.x, b1.y, b1.z,
		//	n1.x, n1.y, n1.z
		//);

		//Matrix3 tbn2(
		//	t2.x, t2.y, t2.z,
		//	b2.x, b2.y, b2.z,
		//	n2.x, n2.y, n2.z
		//);

		//Matrix3 tbn3(
		//	t3.x, t3.y, t3.z,
		//	b3.x, b3.y, b3.z,
		//	n3.x, n3.y, n3.z
		//);

		Matrix3 tbn1(
			t1.x, b1.x, n1.x,
			t1.y, b1.y, n1.y,
			t1.z, b1.z, n1.z
		);

		Matrix3 tbn2(
			t2.x, b2.x, n2.x,
			t2.y, b2.y, n2.y,
			t2.z, b2.z, n2.z
		);

		Matrix3 tbn3(
			t3.x, b3.x, n3.x,
			t3.y, b3.y, n3.y,
			t3.z, b3.z, n3.z
		);


		DrawTriangle(verts[0], verts[1], verts[2], uv1, uv2, uv3, tbn1, tbn2, tbn3, wp1, wp2, wp3);
	}
}

void ImageRenderer::DrawLine(Vector3 p1, Vector3 p2, Vector4 color)
{
	int x1 = p1.x;
	int x2 = p2.x;
	int y1 = p1.y;
	int y2 = p2.y;
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	float err = dx + dy;

	while (true)
	{
		SetPixel(x1, y1, color.x, color.y, color.z);
		if (x1 == x2 && y1 == y2) break;
		float e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}

		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void ImageRenderer::PupulateTexture()
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			image[x + y * w] = frameBuffer[x + y * w];
		}
	}
}

float* ImageRenderer::BaryCentric(float x, float y, Vector3 p0, Vector3 p1, Vector3 p2)
{
	float output[3];
	output[0] = (x * (p1.y - p2.y) + (p2.x - p1.x) * y + p1.x * p2.y - p2.x * p1.y) / (p0.x * (p1.y - p2.y) + (p2.x - p1.x) * p0.y + p1.x * p2.y - p2.x * p1.y);
	output[1] = (x * (p2.y - p0.y) + (p0.x - p2.x) * y + p2.x * p0.y - p0.x * p2.y) / (p1.x * (p2.y - p0.y) + (p0.x - p2.x) * p1.y + p2.x * p0.y - p0.x * p2.y);
	output[2] = (x * (p0.y - p1.y) + (p1.x - p0.x) * y + p0.x * p1.y - p1.x * p0.y) / (p2.x * (p0.y - p1.y) + (p1.x - p0.x) * p2.y + p0.x * p1.y - p1.x * p0.y);
	return output;
}

void ImageRenderer::DrawTriangle(
	Vector4 p1, Vector4 p2, Vector4 p3, 
	Vector2 uv1, Vector2 uv2, Vector2 uv3, 
	Matrix3 tbn1, Matrix3 tbn2, Matrix3 tbn3,
	Vector3 wp1, Vector3 wp2, Vector3 wp3
)
{
	int xMin = std::min(p1.x, std::min(p2.x, p3.x));
	int xMax = std::max(p1.x, std::max(p2.x, p3.x));
	int yMin = std::min(p1.y, std::min(p2.y, p3.y));
	int yMax = std::max(p1.y, std::max(p2.y, p3.y));

	int diffuseTextureUnit = uniformI1["diffuseTexture"];
	std::vector<std::vector<unsigned char>>& diffuseTexture = textures[textureUnits[diffuseTextureUnit]];

	int normalTextureUnit = uniformI1["normalTexture"];
	std::vector<std::vector<unsigned char>>& normalTexture = textures[textureUnits[normalTextureUnit]];

	int specularTextureUnit = uniformI1["specularTexture"];
	std::vector<std::vector<unsigned char>>& specularTexture = textures[textureUnits[specularTextureUnit]];

	for (int y = yMin; y <= yMax; y++)
	{
		for (int x = xMin; x <= xMax; x++)
		{
			if (x < 0 || y < 0) continue;
			if (x >= w || y >= h) continue;
			float xi = x + 0.5f;
			float yi = y + 0.5f;
			if (InsideTriangle(xi, yi, p1, p2, p3))
			{
				float* barycentic = BaryCentric(xi, yi, p1, p2, p3);
				float alpha = barycentic[0];
				float beta = barycentic[1];
				float gamma = barycentic[2];

				//    * v[i].w() is the vertex view space depth value z.
				//    * Z is interpolated view space depth for the current pixel
				//    * zp is depth between zNear and zFar, used for z-buffer

				 float Z = 1.0 / (alpha / p1.w + beta / p2.w + gamma / p3.w);
				 float zp = alpha * p1.z / p1.w + beta * p2.z / p2.w + gamma * p3.z / p3.w;
				 zp *= Z;
				
				// float zp = alpha * p1.w + beta * p2.w + gamma * p3.w;
				
				if (zp < depthBuffer[x + y * w])
				{
					depthBuffer[x + y * w] = zp;
					Vector2 interpolatedTexCoords = uv1 * alpha + uv2 * beta  + uv3 * gamma;
					Vector4 normalTap = TextureLookup(normalTexture, interpolatedTexCoords.x, interpolatedTexCoords.y);
					Vector3 mapNormal(normalTap.x * 2.0f - 1.0f, normalTap.y * 2.0f - 1.0f, normalTap.z * 2.0f - 1.0f);
					//Matrix3 tbnInterpolated = tbn1 * alpha + tbn2 * beta + tbn3 * gamma;
					//Vector3 interpolatedNormals = Normalize(tbnInterpolated * mapNormal);
					Vector3 n1 = Normalize(tbn1 * mapNormal);
					Vector3 n2 = Normalize(tbn2 * mapNormal);
					Vector3 n3 = Normalize(tbn3 * mapNormal);

					Vector3 interpolatedNormals = n1 * alpha + n2 * beta + n3 * gamma;
					Vector3 interpolatedWorldPosition = wp1 * alpha + wp2 * beta + wp3 * gamma;
					Vector3 lightPosition = uniformV3["lightPosition"];
					Vector3 diffuseColor = uniformV3["diffuseColor"];
					Vector4 color = TextureLookup(diffuseTexture, interpolatedTexCoords.x, interpolatedTexCoords.y);


					float lightDistSquared = Dot(Vector4(lightPosition, 1.0) - interpolatedWorldPosition, Vector4(lightPosition, 1.0) - interpolatedWorldPosition);
					float attenuation = 1.0 / lightDistSquared;

					Vector3 toLight = Normalize(lightPosition - interpolatedWorldPosition);
					float diffuseLevel = std::max(0.0f, Dot(toLight, interpolatedNormals));
					Vector3 diffuseTerm = Vector3(0.8f, 0.8f, 0.8f) * diffuseColor * Vector3(20, 20, 20) * diffuseLevel * attenuation;
					Vector4 diffuse = Vector4(diffuseTerm, 0) * color;

					Vector3 cameraPosition = uniformV3["cameraPosition"];
					Vector3 toCamera = Normalize(cameraPosition - interpolatedWorldPosition);
					float specularPower = uniformF1["specularPower"];
					Vector3 reflection = Reflect(-toLight, interpolatedNormals);
					float specularLevel = std::pow(std::max(0.0f, Dot(toCamera, reflection)), specularPower);
					Vector3 specularColor = TextureLookup(specularTexture, interpolatedTexCoords.x, interpolatedTexCoords.y);
					Vector3 specularTerm = Vector3(0.5f, 0.5f, 0.5f) * specularColor * Vector3(20, 20, 20) * specularLevel * attenuation;

					Vector4 fragColor = diffuse + Vector4(specularTerm, 1);
					SetPixel(x, y, fragColor.x, fragColor.y, fragColor.z);
					//SetPixel(x, y, interpolatedNormals.x, interpolatedNormals.y, interpolatedNormals.z);

					//SetPixel(x, y, specularColor.x, specularColor.y, specularColor.z);
				}
			}
		}
	}
}

bool ImageRenderer::InsideTriangle(float x, float y, Vector3 p1, Vector3 p2, Vector3 p3)
{
	Vector3 p(x, y, 1);
	Vector3 v12 = p2 - p1;
	Vector3 v1p = p - p1;
	Vector3 v1c = Cross(v12, v1p);

	Vector3 v23 = p3 - p2;
	Vector3 v2p = p - p2;
	Vector3 v2c = Cross(v23, v2p);

	Vector3 v31 = p1 - p3;
	Vector3 v3p = p - p3;
	Vector3 v3c = Cross(v31, v3p);

	float sign1 = v1c.z;
	float sign2 = v2c.z;
	float sign3 = v3c.z;

	bool hasPositive = false;
	bool hasNegative = false;

	hasPositive = sign1 > 0 || sign2 > 0 || sign3 > 0;
	hasNegative = sign1 < 0 || sign2 < 0 || sign3 < 0;

	return !(hasPositive && hasNegative);
}

void ImageRenderer::Clear()
{
	std::fill(frameBuffer.begin(), frameBuffer.end(), clearColor);
	std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::infinity());

}

int ImageRenderer::GetWidth()
{
	return w;
}

int ImageRenderer::GetHeight()
{
	return h;
}

ImageRenderer* ImageRenderer::GetInstance()
{
	return instance;
}

ImageRenderer* ImageRenderer::CreateInstance(int width, int height)
{
	if (!instance) {
		instance = new ImageRenderer(width, height);
	}
	return instance;
}

ImageRenderer::~ImageRenderer()
{
	glDeleteBuffers(1, &quadBuffer);
	glDeleteTextures(1, &textureID);

}
ImageRenderer* ImageRenderer::instance = nullptr;

