#pragma once

using std::vector;

using namespace NCL::Maths;

namespace NCL {
	namespace CSC8503 {
		class Transform
		{
		public:
			Transform();
			~Transform();

			Transform& SetPosition(const Vector3& worldPos);
			Transform& SetScale(const Vector3& worldScale);
			Transform& SetOrientation(const Quaternion& newOr);
			void IncreasePosition(const Vector3& worldPos);
			void DecreasePosition(const Vector3& worldPos);
			void IncreaseRotation(const Vector3& axis, float degrees);

			Vector3 GetPosition() const {
				return position;
			}

			Vector3 GetScale() const {
				return scale;
			}

			Quaternion GetOrientation() const {
				return orientation;
			}

			Matrix4 GetMatrix() const {
				return matrix;
			}
			void UpdateMatrix();
		protected:
			Matrix4		matrix;
			Quaternion	orientation;
			Vector3		position;

			Vector3		scale;
		};
	}
}

