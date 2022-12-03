#pragma once
#include "Transform.h"
#include "CollisionVolume.h"

using namespace NCL::CSC8503;
using namespace NCL::Maths;

namespace NCL {
	class OBBVolume : CollisionVolume {
	public:
		OBBVolume(const Maths::Vector3& halfDims) {
			type		= VolumeType::OBB;
			halfSizes	= halfDims;
		}
		~OBBVolume() {}

		Maths::Vector3 GetHalfDimensions() const {
			return halfSizes;
		}
		void GetAxes(const Transform& worldTransform, std::vector<Vector3>& axes) const {
			Matrix3 orientation = Matrix3(worldTransform.GetOrientation());
			axes.push_back(orientation * Vector3(1.0f, 0.0f, 0.0f)); //X - Axis
			axes.push_back(orientation * Vector3(0.0f, 1.0f, 0.0f)); //Y - Axis
			axes.push_back(orientation * Vector3(0.0f, 0.0f, 1.0f)); //Z - Axis
		}
		void GetMinMaxVertices(const Transform& worldTransform, Vector3& min, Vector3& max) const {
			//transforming OBB into an ABB to get the min and max of the box
			Quaternion orientation = worldTransform.GetOrientation();
			Matrix3 invOrientation = Matrix3(orientation.Conjugate());
			Vector3 localPos = invOrientation * worldTransform.GetPosition();
			min = localPos - halfSizes;
			max = localPos + halfSizes;

			min = orientation * min;
			max = orientation * min;
		}
	protected:
		Maths::Vector3 halfSizes;
	};
}

