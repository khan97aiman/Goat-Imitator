#include "Camera.h"
#include "Window.h"
#include <algorithm>
#include <math.h>

using namespace NCL;
/*
Polls the camera for keyboard / mouse movement.
Should be done once per frame! Pass it the msec since
last frame (default value is for simplicities sake...)
*/
void Camera::UpdateCamera(float dt) {
	//Update the mouse by how much
	pitch	-= (Window::GetMouse()->GetRelativePosition().y);

	//Bounds check the pitch, to be between straight up and straight down ;)
	pitch = std::min(pitch, 90.0f);
	pitch = std::max(pitch, -90.0f);

	CalculateZoom();
	CalculateAngleAroundPlayer();
}

/*
Generates a view matrix for the camera's viewpoint. This matrix can be sent
straight to the shader...it's already an 'inverse camera' matrix.
*/
Matrix4 Camera::BuildViewMatrix() const {
	//Why do a complicated matrix inversion, when we can just generate the matrix
	//using the negative values ;). The matrix multiplication order is important!
	return	Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) *
		Matrix4::Translation(-position);
};

Matrix4 Camera::BuildProjectionMatrix(float currentAspect) const {
	if (camType == CameraType::Orthographic) {
		return Matrix4::Orthographic(left, right, bottom, top, nearPlane, farPlane);
	}
	//else if (camType == CameraType::Perspective) {
		return Matrix4::Perspective(nearPlane, farPlane, currentAspect, fov);
	//}
}

Camera Camera::BuildPerspectiveCamera(const Vector3& pos, float pitch, float yaw, float fov, float nearPlane, float farPlane) {
	Camera c;
	c.camType	= CameraType::Perspective;
	c.position	= pos;
	c.pitch		= pitch;
	c.yaw		= yaw;
	c.nearPlane = nearPlane;
	c.farPlane  = farPlane;

	c.fov		= fov;

	return c;
}
Camera Camera::BuildOrthoCamera(const Vector3& pos, float pitch, float yaw, float left, float right, float top, float bottom, float nearPlane, float farPlane) {
	Camera c;
	c.camType	= CameraType::Orthographic;
	c.position	= pos;
	c.pitch		= pitch;
	c.yaw		= yaw;
	c.nearPlane = nearPlane;
	c.farPlane	= farPlane;

	c.left		= left;
	c.right		= right;
	c.top		= top;
	c.bottom	= bottom;

	return c;
}

void NCL::Camera::CalculateZoom() {
	float zoomLevel = Window::GetMouse()->GetWheelMovement() * 0.1f;
	distanceFromPlayer -= zoomLevel;
}

void NCL::Camera::CalculateAngleAroundPlayer() {
	if (Window::GetMouse()->ButtonDown(MouseButtons::LEFT)) {
		angleAroundPlayer += Window::GetMouse()->GetRelativePosition().x * 0.3f;
	}
}

float NCL::Camera::CalculateHorizontalDistanceFromPlayer() {
	return distanceFromPlayer * cos(Maths::DegreesToRadians(pitch));
}

float NCL::Camera::CalculateVerticalDistanceFromPlayer() {
	return distanceFromPlayer * sin(Maths::DegreesToRadians(pitch));
}

void NCL::Camera::CalculateThirdPersonCameraPosition(const Vector3& playerPosition, const Quaternion& playerOrientation) {
	float vDist = CalculateVerticalDistanceFromPlayer();
	float hDist = CalculateHorizontalDistanceFromPlayer();

	float theta = Maths::DegreesToRadians(playerOrientation.ToEuler().y + angleAroundPlayer);
	float xOffset = hDist * sin(theta);
	float zOffset = hDist * cos(theta);

	position.x = playerPosition.x - xOffset;
	position.z = playerPosition.z - zOffset;
	position.y = playerPosition.y + vDist;

	Vector3 lockedOffset = Vector3(0, 14, distanceFromPlayer);	

	Matrix4 temp = Matrix4::BuildViewMatrix(position, playerPosition, Vector3(0, 1, 0));

	Matrix4 modelMat = temp.Inverse();

	Quaternion q(modelMat);
	Vector3 angles = q.ToEuler(); 
	SetYaw(angles.y);
}
