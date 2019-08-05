#ifndef GRASS_H
#define GRASS_H

#include "Model.h"

namespace GAME{
class Grass : public Model
{
protected:

	class Shader *shader;

	Matrix4 modelMatrix;
	std::vector<Mesh*> meshes;

public:
	Grass(const Vec3 pos_, const Vec3 orientation_);
	~Grass();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Render() const;
	virtual void Update(const float deltaTime);

	virtual bool LoadMesh(const char * filename);

};
}
#endif // !GRASS_H