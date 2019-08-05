#ifndef FIREBALL_H
#define FIREBALL_H

#include "Model.h"

namespace GAME {
	class FireBall : public Model {
	protected:

		class Shader *shader;

		Matrix4 modelMatrix;
		std::vector<Mesh*> meshes;

	public:
		FireBall(const Vec3 pos_, const Vec3 orientation_);
		~FireBall();

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);

		virtual bool LoadMesh(const char* filename);

	};
}

#endif // !FIREBALL_H