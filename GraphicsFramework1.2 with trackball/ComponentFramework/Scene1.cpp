#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include "MMath.h"
#include "Window.h"
#include "Shader.h"
#include "Scene1.h"
#include "SceneEnvironment.h"
#include "Trackball.h"

#include "skull.h"
#include "GlassBall.h"
#include "CartoonBall.h"
#include "WaterBall.h"
#include "Grass.h"

#include "ObjLoader.h"

using namespace GAME;
using namespace MATH;


Scene1::Scene1(Window& windowRef):Scene(windowRef) {

	////////////////////////////////////////////////////////
	// whatObject 0 is for a sphere that looks like glass //
	// whatObject 1 is for a sphere that looks like water //
	// whatObject 2 is for a sphere that looks cartoony   //
	// whatObject 3 is for moving grass                   //
	////////////////////////////////////////////////////////
	whatObject = 0;

}


bool Scene1::OnCreate() {
	
	camera = nullptr;
	
	totalTime = 0.0f;

	
	
	/// Load Assets: as needed 
	if (whatObject != 3) {
		if (addModel("sphere.obj") == false) {
			return false;
		}
	}
	else {
		if (addModel("grassMultiple.obj") == false) {
			return false;
		}
	}

	skybox = new SkyBox();
	skybox->OnCreate();

	/// Create a shader with attributes
	SceneEnvironment::getInstance()->setLight(Vec3(0.0f, 3.0f, 7.0f));

	OnResize(windowPtr->getWidth(), windowPtr->getHeight());
	return true;
}


bool GAME::Scene1::addModel(const char* filename)
{
	if (whatObject == 0) {
		models.push_back(new GlassBall(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	}
	else if (whatObject == 1) {
		models.push_back(new WaterBall(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	}
	else if (whatObject == 2) {
		models.push_back(new CartoonBall(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	}
	else {
		models.push_back(new Grass(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	}

	models[models.size() - 1]->OnCreate();

	if (models[models.size() - 1]->LoadMesh(filename) == false) {
		return false;
	}
	return true;
}

void Scene1::OnResize(int w_, int h_){
	windowPtr->setWindowSize(w_,h_);
	glViewport(0,0,windowPtr->getWidth(),windowPtr->getHeight());
	if (camera) delete camera;
	camera = new Camera(w_, h_, Vec3(0.0f, 0.0f, 10.0f));
	Camera::currentCamera = camera;
	Trackball::getInstance()->setWindowDimensions(windowPtr->getWidth(), windowPtr->getHeight());
}

void Scene1::Update(const float deltaTime) {
	for (Model* model : models) {
		model->Update(deltaTime);
	}
	skybox->Update(deltaTime);
	totalTime += deltaTime;
}

void Scene1::Render() const{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	skybox->Render(camera->getProjectionMatrix(), Matrix4());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	/// Draw your scene here
	for (Model* model : models) {
		model->Render();
	}

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
	
}

void Scene1::HandleEvents(const SDL_Event& SDLEvent){
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Trackball::getInstance()->onLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}else if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONUP){
		Trackball::getInstance()->onLeftMouseUp(SDLEvent.button.x, SDLEvent.button.y);
	}else if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION && 
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		Trackball::getInstance()->onMouseMove(SDLEvent.button.x, SDLEvent.button.y);
	}
		
}

Scene1::~Scene1() {
	OnDestroy();
}

void Scene1::OnDestroy() {
	/// Cleanup Assets
	if (skybox) delete skybox;
	if (camera) delete camera;
	for (Model* model : models) {
		if (model) delete model;
	}
}
