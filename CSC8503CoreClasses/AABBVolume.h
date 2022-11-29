#pragma once
#include "CollisionVolume.h"
#include "Vector3.h"
#include <OBBVolume.h>

namespace NCL {
	using namespace NCL::Maths;
	class AABBVolume : CollisionVolume
	{
	public:
		AABBVolume(const Vector3& halfDims) {
			type		= VolumeType::AABB;
			halfSizes	= halfDims;
		}

		AABBVolume(const OBBVolume& volume) {
			type = VolumeType::AABB;
			halfSizes = volume.GetHalfDimensions();
		}
		~AABBVolume() {

		}

		Vector3 GetHalfDimensions() const {
			return halfSizes;
		}

	protected:
		Vector3 halfSizes;
	};
}
