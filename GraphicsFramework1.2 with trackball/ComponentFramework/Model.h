#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Entity.h"
#include "Timer.h"

namespace GAME {

using namespace MATH;

class Model : public Entity {

protected:

	class Shader *shader;

	Matrix4 modelMatrix;
	std::vector<Mesh*> meshes;

public:

	Model(const Vec3 _pos, const Vec3 _orientation);
	Model(const Model&) = delete;
	Model(Model&&) = delete;
	Model& operator = (const Model&) = delete;
	Model& operator = (Model&&) = delete;

	virtual ~Model();

	Model();

	void setPos(const Vec3& pos_) override;
	void setOrientation(const Vec3& orienration_) override;

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Render() const;
	virtual void Update(const float deltaTime);

	virtual bool LoadMesh(const char* filename);

	unsigned int textureID[2];


protected:

	void updateModelMatrix();
};
} /// end of namespace

#endif