#ifndef CARTOONBALL_H
#define CARTOONBALL_H

#include "Model.h"

namespace GAME {
	class CartoonBall : public Model {
	protected:

		class Shader *shader;

		Matrix4 modelMatrix;
		std::vector<Mesh*> meshes;

	public:
		CartoonBall(const Vec3 pos_, const Vec3 orientation_);
		~CartoonBall();

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);

		virtual bool LoadMesh(const char* filename);

	};
}

#endif // !CARTOONBALL_H
