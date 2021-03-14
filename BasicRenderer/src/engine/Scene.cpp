#include "engine/Scene.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Renderer.hpp"
#include "engine/Skybox.hpp"

#include "opengl/Shader.h"

#include "lighting/LightManager.hpp"
#include "lighting/PointLight.hpp"
#include "lighting/DirectionalLight.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>


Scene::Scene()
	:  _skybox(nullptr)
{
	Init();
}

Scene::~Scene() {}

void Scene::Init()
{
	// Init all static meshes
	//=======================
	Model m_sphere("res/models/sphere.obj");
	StaticMesh sm_sphere(m_sphere, TransformLayout(glm::vec3(0, 0, 0)), "DefaultLighting");
	//sm_sphere.Scale(1);
	AddStaticMesh(std::make_shared<StaticMesh>(sm_sphere));

	// Load All Lights
	// =================
	LightManager::Get().LoadAllLights();
}

void Scene::Draw()
{
	// Render the Skybox
	// =================
	//_skybox->Draw(_fog);
	

	// Render all the static meshes
	// ============================
	for (size_t i = 0; i < _staticMeshesCount; i++)
	{
		_staticMeshes[i]->Draw();
	}
}

void Scene::AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh)
{
	_staticMeshes.push_back(mesh);
	_staticMeshesCount++;
}

void Scene::Free()
{
	// Free all static meshes
	// ==========================
	for (size_t i = 0; i < _staticMeshesCount; i++)
		_staticMeshes[i]->Free();

	// Free all textures 
	// ==========================
	ResourceManager::Get().DeleteAllResources();
}

