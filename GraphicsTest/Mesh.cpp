#include "Mesh.h"


Mesh::Mesh(std::string fileName)
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	//std::vector<Vertex> vertices = {
	//	{ {-0.5, -0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {1, 0, 0, 1}, {0, 0} },
	//	{ {-0.5, 0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {1, 0, 0, 1}, {0, 1} },
	//	{ {0.5, 0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {1, 0, 0, 1}, {1, 1} },
	//	{ {0.5, -0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {1, 0, 0, 1}, {1, 0} },

	//	{ {-0.5, -0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 1, 1}, {0, 0} },
	//	{ {-0.5, 0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 1, 1}, {0, 1} },
	//	{ {0.5, 0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 1, 1}, {1, 1} },
	//	{ {0.5, -0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 1, 1}, {1, 0} },

	//	{ {-0.5, -0.5, -0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0, 1}, {0, 0} },
	//	{ {-0.5, -0.5, 0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0, 1}, {0, 1} },
	//	{ {-0.5, 0.5, 0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0, 1}, {1, 1} },
	//	{ {-0.5, 0.5, -0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0, 1}, {1, 0} },

	//	{ {0.5, -0.5, -0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 1, 1}, {0, 0} },
	//	{ {0.5, -0.5, 0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 1, 1}, {0, 1} },
	//	{ {0.5, 0.5, 0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 1, 1}, {1, 1} },
	//	{ {0.5, 0.5, -0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 1, 1}, {1, 0} },

	//	{ {-0.5, -0.5, -0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 0, 1}, {0, 0} },
	//	{ {-0.5, -0.5, 0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 0, 1}, {0, 1} },
	//	{ {0.5, -0.5, 0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 0, 1}, {1, 1} },
	//	{ {0.5, -0.5, -0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 0, 1}, {1, 0} },

	//	{ {-0.5, 0.5, -0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0, 1, 1}, {0, 0} },
	//	{ {-0.5, 0.5, 0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0, 1, 1}, {0, 1} },
	//	{ {0.5, 0.5, 0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0, 1, 1}, {1, 1} },
	//	{ {0.5, 0.5, -0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0, 1, 1}, {1, 0} }
	//};

	//std::vector<unsigned short> vertIndices = {
	//	0, 1, 2, 2, 3, 0,
	//	4, 5, 6, 6, 7, 4,
	//	8, 9, 10, 10, 11, 8,
	//	12, 13, 14, 14, 15, 12,
	//	16, 17, 18, 18, 19, 16,
	//	20, 21, 22, 22, 23, 20
	//};

	//Assimp::Importer importer;
	//const aiScene* soulspearScene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//std::vector<Vertex> vertices;
	//std::vector<unsigned short> indices;
	//aiMesh* meshInfo = soulspearScene->mMeshes[0];
	//vertices.reserve(meshInfo->mNumVertices);
	//indices.reserve(meshInfo->mNumFaces);

	//for (int i = 0; i < meshInfo->mNumVertices; i++)
	//{
	//	Vertex newVertex;
	//	newVertex.position = { meshInfo->mVertices[i].x, meshInfo->mVertices[i].y, meshInfo->mVertices[i].z };

	//	if (meshInfo->HasVertexColors(0))
	//	{
	//		newVertex.color = { meshInfo->mColors[0][i].r,meshInfo->mColors[0][i].g,meshInfo->mColors[0][i].b, meshInfo->mColors[0][i].a };
	//	}
	//	else {
	//		newVertex.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	//	}

	//	if (meshInfo->HasTextureCoords(0))
	//	{
	//		newVertex.uv = { meshInfo->mTextureCoords[0][i].x, meshInfo->mTextureCoords[0][i].y };
	//	}
	//	else {
	//		newVertex.uv = { newVertex.position.x, newVertex.position.y };
	//	}

	//	if (meshInfo->HasNormals())
	//	{
	//		newVertex.normal = { meshInfo->mNormals[i].x, meshInfo->mNormals[i].y, meshInfo->mNormals[i].z };
	//	}
	//	else {
	//		newVertex.normal = { 0, 0, 0 };
	//	}

	//	if (meshInfo->HasTangentsAndBitangents())
	//	{
	//		newVertex.vertTangent = { meshInfo->mTangents[i].x, meshInfo->mTangents[i].y, meshInfo->mTangents[i].z };
	//		newVertex.vertBitangent = { meshInfo->mBitangents[i].x, meshInfo->mBitangents[i].y, meshInfo->mBitangents[i].z };
	//	}
	//	else {
	//		newVertex.vertTangent = { 0, 0, 0 };
	//		newVertex.vertBitangent = { 0, 0, 0 };
	//	}
	//	vertices.push_back(newVertex);
	//}

	//for (int i = 0; i < meshInfo->mNumFaces; i++)
	//{
	//	indices.push_back(meshInfo->mFaces[i].mIndices[0]);
	//	indices.push_back(meshInfo->mFaces[i].mIndices[1]);
	//	indices.push_back(meshInfo->mFaces[i].mIndices[2]);
	//}

	std::vector<Vertex> vertices;
	std::vector<Vector3> verts; 
	std::vector<unsigned short> vertIndices;
	std::vector<Vector2> uvs;
	std::vector<unsigned short> uvIndices;
	std::vector<Vector3> normals;
	std::vector<unsigned short> normalIndices;
	
	// Super not bullet proof parser, it doesn't eliminate identical verts, but it's fine for now
	ParseObj(fileName, verts, vertIndices, uvs, uvIndices, normals, normalIndices, true);

	for (int i = 0; i < verts.size(); i++)
	{
		Vertex newVert;
		newVert.position = verts[i];
		vertices.push_back(newVert);
	}

	for (int i = 0; i < vertIndices.size(); i++)
	{
		if (uvIndices.size() > i)
		{
			vertices[vertIndices[i]].uv = uvs[uvIndices[i]];
		}

		if (normalIndices.size() > i)
		{
			vertices[vertIndices[i]].normal = normals[normalIndices[i]];
		}
	}

	vertexId = r->UploadVertexData(vertices);
	indexId = r->UploadIndexData(vertIndices);
}

void Mesh::Bind()
{
	ImageRenderer* resteriser = ImageRenderer::GetInstance();
	resteriser->BindVertex(vertexId);
	resteriser->BindIndex(indexId);
}

void Mesh::Unbind()
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	r->UnbindVertex();
	r->UnbindIndex();

}

void Mesh::Update()
{
}

void Mesh::Draw()
{
	//for (int i = 0; i < indices.size(); i+=3)
	//{
	//	const Vertex& v1 = vertices[i];
	//	const Vertex& v2 = vertices[i + 1];
	//	const Vertex& v3 = vertices[i + 2];

	//	image->DrawTriangle(
	//		v1.position.x, v1.position.y,
	//		v2.position.x, v2.position.y,
	//		v3.position.x, v3.position.y,
	//		v1.color.x, v1.color.y, v1.color.z
	//	);
	//}
}

