#include "Grass.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "Camera.h"
#include "SceneEnvironment.h"
#include "Trackball.h"
#include "SDL_image.h"

GAME::Grass::Grass(const Vec3 pos_, const Vec3 orientation_)
{
	pos = pos_;
	orientation = orientation_;
	shader = nullptr;
}

GAME::Grass::~Grass()
{
	OnDestroy();
}

bool GAME::Grass::OnCreate()
{
	shader = new Shader("GrassVert.glsl", "GrassFrag.glsl", 4, 0, "vVertex", 1, "vNormal", 2, "vTexture", 3, "vPosition");
	
	/// Let's generate two textures in the GPU and bind the first one
	glGenTextures(2, textureID);
	/// Bind the first one
	glBindTexture(GL_TEXTURE_2D, textureID[0]);

	///Load the image from the hard drive
	SDL_Surface *textureSurface = IMG_Load("grass.png");
	if (textureSurface == nullptr) {
		return false;
	}

	/// Are we using alpha? Not in jpeg but let's be careful
	int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

	/// Wrapping and filtering options
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/// Load the texture data from the SDL_Surface to the GPU memmory
	glTexImage2D(GL_TEXTURE_2D, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	/// Release the memory
	SDL_FreeSurface(textureSurface); /// let go of the memory

	return true;
}

void GAME::Grass::OnDestroy()
{
	if (shader) delete shader;
}

void GAME::Grass::Render() const
{
	glDisable(GL_CULL_FACE);

	//Get the id's of the variables
	GLint projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	GLint modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
	GLint normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	GLint lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	GLint grassID = glGetUniformLocation(shader->getProgram(), "vTexture");
	GLint positionID = glGetUniformLocation(shader->getProgram(), "vPosition");
	GLint clusterTranslationID = glGetUniformLocation(shader->getProgram(), "vClusterTranslation");

	glUseProgram(shader->getProgram());
	glBindTexture(GL_TEXTURE_2D, 1);

	//Set the variables using the id's
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, Camera::currentCamera->getProjectionMatrix());
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, Camera::currentCamera->getViewMatrix() * Trackball::getInstance()->getMatrix4());
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix * Trackball::getInstance()->getMatrix4());
	glUniform1i(grassID, textureID[0]);
	glUniformMatrix3fv(positionID, 1, GL_FALSE, pos);
	Vec3 temp = Vec3(sin(Timer::GetElapsedTime()) / 10, sin(Timer::GetElapsedTime()) / 10, sin(Timer::GetElapsedTime()) / 10);
	glUniform3fv(clusterTranslationID, 1, temp);



	/// Assigning the 4x4 modelMatrix to the 3x3 normalMatrix 
	/// copies just the upper 3x3 of the modelMatrix
	Matrix3 normalMatrix = modelMatrix * Trackball::getInstance()->getMatrix4();
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);

	glUniform3fv(lightPosID, 1, SceneEnvironment::getInstance()->getLight());

	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnable(GL_CULL_FACE);
}

void GAME::Grass::Update(const float deltaTime)
{
	// See Entity.h
}

bool GAME::Grass::LoadMesh(const char * filename)
{

	if (ObjLoader::loadOBJ("grassMultiple.obj") == false) {
		return false;
	}
	/// Get the data out of the ObjLoader and into our own mesh
	meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));
	return true;

	if (ObjLoader::loadOBJ("plane2.obj") == false) {
		return false;
	}

	meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));

	if (ObjLoader::loadOBJ("plane3.obj") == false) {
		return false;
	}

	meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));

}
