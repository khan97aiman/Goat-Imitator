#pragma once
#include "TextureBase.h"
#include "ShaderBase.h"
#include "MeshAnimation.h"
#include "MeshGeometry.h"
#include "../OpenGLRendering/OGLShader.h"

namespace NCL {
	using namespace NCL::Rendering;

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

			void SetRigged(bool rigged) {
				this->rigged = rigged;
			}

			bool IsRigged() const {
				return rigged;
			}

			void GetFrameMatrices(vector<Matrix4>& frameMatrices) const {
				const vector<Matrix4> invBindPose = mesh->GetInverseBindPose();
				const Matrix4* frameData = animation->GetJointData(currentFrame);
				for (unsigned int i = 0; i < mesh->GetJointCount(); ++i) {
					frameMatrices.emplace_back(frameData[i] * invBindPose[i]);
				}
				/*OGLShader* shader = (OGLShader*)(this->shader);
				glUniformMatrix4fv(glGetUniformLocation(shader->GetProgramID(), "joints"), frameMatrices.size(), false, (float*)frameMatrices.data());*/
			}

			MeshAnimation* animation;
			int currentFrame = 0;
			float frameTime = 0.0f;
		protected:
			MeshGeometry*	mesh;
			std::vector<TextureBase*>	textures;
			ShaderBase*		shader;
			Transform*		transform;
			Vector4			colour;
			bool	rigged = false;
		};
	}
}
