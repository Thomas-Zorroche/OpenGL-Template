#pragma once

#include "engine/Model.hpp"
#include "opengl/Shader.h"

#include <string>
#include <memory>
#include <functional>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Fog;
class CollisionManager;

class TransformLayout
{
public:
	TransformLayout(const glm::vec3& loc, const glm::vec3& rot = glm::vec3(0, 0, 0), float scale = 1.0f, float uvScale = 1.0f)
		: _location(loc), _rotation(rot), _scale(scale), _uvScale(uvScale) {}

	glm::vec3 Location() const { return _location; }
	glm::vec3 Rotation() const { return _rotation; }
	float Scale() const { return _scale; }
	float UvScale() const { return _uvScale; }

private:
	glm::vec3 _location;
	glm::vec3 _rotation;
	float _scale;
	float _uvScale;
};



class StaticMesh
{
public:
	// Constructor
	StaticMesh(const Model& model, const TransformLayout& transLayout, const std::string& shaderName = "Default");

	void Draw(bool isParticuleInstance = false, int countParticule = 0);

	glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	std::shared_ptr<Shader>& GetShader() { return _shader; }

	void Translate(const glm::vec3& delta, bool dynamicCBox = true);
	void Scale(float alpha, bool dynamicCBox = true);
	void Rotate(const glm::vec3& alpha, bool dynamicCBox = true);

	unsigned int GetVAO() const { return _model.GetVAO(); }

	void Free();

private:
	void SendUniforms();

	Model _model;

	TransformLayout _transformLayout;
	std::shared_ptr<Shader> _shader;
	glm::mat4 _modelMatrix;
};