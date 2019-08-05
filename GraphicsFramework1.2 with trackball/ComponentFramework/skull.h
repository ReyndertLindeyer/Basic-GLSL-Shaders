#ifndef SKULL_H
#define SKULL_H


#include "Model.h"

namespace GAME {
	class skull : public Model
	{
	protected:

		class Shader *shader;

		Matrix4 modelMatrix;
		std::vector<Mesh*> meshes;

	public:
		skull(const Vec3 pos_, const Vec3 orientation_);
		~skull();

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);

		virtual bool LoadMesh(const char* filename);
	};

}
#endif // !SKULL_H