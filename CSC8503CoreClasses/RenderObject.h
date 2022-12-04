#pragma once
#include "TextureBase.h"
#include "ShaderBase.h"

namespace NCL {
	using namespace NCL::Rendering;

	class MeshGeometry;
	namespace CSC8503 {
		class Transform;
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(Transform* parentTransform, MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader);
			~RenderObject();

			/*void SetDefaultTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetDefaultTexture() const {
				return texture;
			}*/

			void AddTexture(TextureBase* t) {
				if (t) textures.emplace_back(t);
			}

			std::vector<TextureBase*> GetTextures() const {
				return textures;
			}

			MeshGeometry*	GetMesh() const {
				return mesh;
			}

			Transform*		GetTransform() const {
				return transform;
			}

			ShaderBase*		GetShader() const {
				return shader;
			}

			void SetColour(const Vector4& c) {
				colour = c;
			}

			Vector4 GetColour() const {
				return colour;
			}

		protected:
			MeshGeometry*	mesh;
			std::vector<TextureBase*>	textures;
			ShaderBase*		shader;
			Transform*		transform;
			Vector4			colour;
		};
	}
}
