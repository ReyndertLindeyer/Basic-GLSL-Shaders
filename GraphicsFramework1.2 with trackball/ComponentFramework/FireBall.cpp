#include "FireBall.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "Camera.h"
#include "SceneEnvironment.h"
#include "Trackball.h"
#include "SDL_image.h"

GAME::FireBall::FireBall(const Vec3 pos_, const Vec3 orientation_)
{
	pos = pos_;
	orientation = orientation_;
	shader = nullptr;
}

GAME::FireBall::~FireBall()
{
	OnDestroy();
}

bool GAME::FireBall::OnCreate()
{
	shader = new Shader("lavaVert.glsl", "lavaFrag.glsl", 2, 0, "vVertex", 1, "vNormal");
	//textureID[0] = CreateNoise3D();
	return true;
}

void GAME::FireBall::OnDestroy()
{
	if (shader) delete shader;
}

void GAME::FireBall::Render() const
{
	//Get the id's of the variables
	GLint projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	GLint modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
	GLint normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	GLint lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	GLint timeID = glGetUniformLocation(shader->getProgram(), "time");
	GLint noiseID = glGetUniformLocation(shader->getProgram(), "noiseTexture");

	glUseProgram(shader->getProgram());

	//Set the variables using the id's
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, Camera::currentCamera->getProjectionMatrix());
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, Camera::currentCamera->getViewMatrix() * Trackball::getInstance()->getMatrix4());
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix * Trackball::getInstance()->getMatrix4());
	glUniform1f(timeID, Timer::GetElapsedTime());
	glUniform1i(noiseID, textureID[0]);


	/// Assigning the 4x4 modelMatrix to the 3x3 normalMatrix 
	/// copies just the upper 3x3 of the modelMatrix
	Matrix3 normalMatrix = modelMatrix * Trackball::getInstance()->getMatrix4();
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);

	glUniform3fv(lightPosID, 1, SceneEnvironment::getInstance()->getLight());

	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
}

void GAME::FireBall::Update(const float deltaTime)
{
	// See Entity.h
}

bool GAME::FireBall::LoadMesh(const char * filename)
{
	if (ObjLoader::loadOBJ(filename) == false) {
		return false;
	}
	/// Get the data out of the ObjLoader and into our own mesh
	meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));
	return true;
}
