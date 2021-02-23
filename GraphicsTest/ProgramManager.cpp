#include "ProgramManager.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include <iostream>
#include "Mesh.h"

bool ProgramManager::Initialise()
{
	if (!glfwInit())
		return false;

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPU Graphics", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
		return false;


	glfwSwapInterval(1);

	simpleShader = new ShaderProgram("Plain.vert", "Plain.frag");
	simpleShader->UseProgram();
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetWindowSizeCallback(window, OnWindowResized);

	ImageRenderer::CreateInstance(width, height);
	ImageRenderer* r = ImageRenderer::GetInstance();

	//r->UploadTexture()
	//std::vec
	//ParseObj("soulspear/soulspear.obj", );

	diffuseTexture = new Texture("soulspear\\soulspear_diffuse.tga");

	r->SetUniform("diffuseTexture", 0);

	Mesh* mesh = new Mesh("soulspear/soulspear.obj");
	meshes.push_back(mesh);

	glEnableVertexAttribArray(0);

	return true;

}

void ProgramManager::Run()
{

	while (!glfwWindowShouldClose(window))
	{
		Draw();
		ImageRenderer::GetInstance()->DrawImage(simpleShader);

		glfwSwapBuffers(window);

		glfwPollEvents();
		UpdateMouseState();
	}
}


void ProgramManager::UpdateMouseState()
{
	double mouseXDouble, mouseYDouble;	//Some platforms allow sub-pixel cursor position...
	glfwGetCursorPos(window, &mouseXDouble, &mouseYDouble);
	//...but we're going to clobber it if it exists.
	mouseX = int(mouseXDouble) / PIXEL_SCALE;
	mouseY = int(mouseYDouble) / PIXEL_SCALE;

	mouseLeftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	mouseRightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

void ProgramManager::ShutDown()
{
	// delete r;

	for (Mesh* mesh : meshes)
	{
		delete mesh;
	}
	delete simpleShader;
	ImageRenderer::DeleteInstance();
	//delete image;
	glfwTerminate();
}

void ProgramManager::Draw()
{
	ImageRenderer* r = ImageRenderer::GetInstance();
	r->Clear();

	Matrix4 modelMatrix = RotateY(Matrix4(), 0);
	Matrix4 translateMatrix = Translate(Matrix4(), { 0.0f, 0.0f, 0.0f });
	Matrix4 viewMatrix = GetViewMatrix({ 0, 2.0f, 5.0f }, { 0, 2.0f, 0 }, { 0, 1, 0 });
	Matrix4 projectionMatrix = GetPerspProjectionMatrix(3.1415926f / 4.0f, r->GetWidth() / (float)(r->GetHeight()), 0.1f, 100.0f);
	Matrix4 viewportMatrix = GetViewportMatrix(0, r->GetWidth(), r->GetHeight(), 0);

	r->SetUniform("modelMatrix", modelMatrix);
	r->SetUniform("viewMatrix", viewMatrix);
	r->SetUniform("projectionMatrix", projectionMatrix);
	r->SetUniform("viewportMatrix", viewportMatrix);

	diffuseTexture->Bind(0);
	for (Mesh* mesh : meshes)
	{
		mesh->Bind();
		r->Draw();
	}
	Mesh::Unbind();
	Texture::Unbind();

}
