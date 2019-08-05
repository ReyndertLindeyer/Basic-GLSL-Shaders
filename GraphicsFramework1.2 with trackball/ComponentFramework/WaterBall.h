#ifndef WATERBALL_H
#define WATERBALL_H

#include "Model.h"

namespace GAME {
	class WaterBall : public Model {
	protected:

		class Shader *shader;

		Matrix4 modelMatrix;
		std::vector<Mesh*> meshes;

	public:
		WaterBall(const Vec3 pos_, const Vec3 orientation_);
		~WaterBall();

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);

		virtual bool LoadMesh(const char* filename);

	};
}

#endif // !WATERBALL_H
