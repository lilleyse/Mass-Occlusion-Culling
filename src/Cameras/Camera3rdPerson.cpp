#include "Camera3rdPerson.h"

Camera3rdPerson::Camera3rdPerson(void) : Camera()
{
    this->currXZRads = 0.0f;
    this->currYRads = 0.0f;
    this->radius = 10;
    this->lookAt = glm::vec3(0,0,0);
    this->updateWorldToCameraMatrix();
}

Camera3rdPerson::~Camera3rdPerson(void)
{
	//Do nothing
}

//-----------------------------
// Camera Movements ///////////
//-----------------------------
void Camera3rdPerson::pan(float x, float y)
{
	glm::vec3 right = glm::normalize(glm::cross(this->lookDir,this->upDir));
	glm::vec3 up = this->upDir;
	glm::vec3 moveX = x*right;
	glm::vec3 moveY = y*up;
	this->lookAt += moveX;
	this->lookAt += moveY;
	this->updateWorldToCameraMatrix();
}
void Camera3rdPerson::rotate(float x, float y)
{
	this->currXZRads += x;
	this->currYRads += y;
	this->updateWorldToCameraMatrix();
}
void Camera3rdPerson::zoom(float distance)
{
	this->radius -= distance;
	this->updateWorldToCameraMatrix();
}

void Camera3rdPerson::CalcMatrix(void)
{
    //Compute the position vector along the xz plane.
    float cosa = cosf(currXZRads);
    float sina = sinf(currXZRads);

    glm::vec3 currPos(sina, 0.0f, cosa);

    //Compute the "up" rotation axis.
    //This axis is a 90 degree rotation around the y axis. Just a component-swap and negate.
    glm::vec3 UpRotAxis;

    UpRotAxis.x = currPos.z;
    UpRotAxis.y = currPos.y;
    UpRotAxis.z = -currPos.x;

    //Now, rotate around this axis by the angle.
    //Framework::MatrixStack theStack;

    //theStack.SetIdentity();
    glm::mat4 xRotation = Transformations::getRotationMatrixRads(UpRotAxis, currYRads);
    currPos = glm::vec3(xRotation * glm::vec4(currPos, 0.0));

    //Set the position of the camera.
    glm::vec3 tempVec = currPos * float(radius);
    this->cameraPos = tempVec + lookAt;

    //Now, compute the up-vector.
    //The direction of the up-vector is the cross-product of currPos and UpRotAxis.
    //Rotate this vector around the currPos axis given m_currSpin.

    this->upDir = glm::normalize(glm::cross(currPos, UpRotAxis));
    this->lookDir = glm::normalize(this->lookAt - this->cameraPos);

    this->CalcLookAtMatrix();
}

//Getters
glm::vec3 Camera3rdPerson::getLookAt(void)
{
	return this->lookAt;
}