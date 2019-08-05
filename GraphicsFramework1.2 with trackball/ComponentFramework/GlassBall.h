#ifndef GLASSBALL_H
#define GLASSBALL_H

#include "Model.h"

namespace GAME {
	class GlassBall : public Model {
	protected:

		class Shader *shader;

		Matrix4 modelMatrix;
		std::vector<Mesh*> meshes;

	public:
		GlassBall(const Vec3 pos_, const Vec3 orientation_);
		~GlassBall();

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);

		virtual bool LoadMesh(const char* filename);

	};
}

#endif // !GLASSBALL_H
