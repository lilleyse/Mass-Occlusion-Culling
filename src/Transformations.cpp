#include "Transformations.h"

Transformations::Transformations(void)
{

}

glm::mat4 Transformations::getTranslationMatrix(glm::vec3 vector)
{
    glm::mat4 theMat(1.0f);
    theMat[3].x = vector.x;
    theMat[3].y = vector.y;
    theMat[3].z = vector.z;
    return theMat;
}
glm::mat4 Transformations::getScaleMatrix(float amount)
{
    glm::mat4 theMat(1.0f);
    theMat[0].x = amount;
    theMat[1].y = amount;
    theMat[2].z = amount;
    return theMat;
}

glm::mat4 Transformations::getScaleMatrix(glm::vec3 vector)
{
    glm::mat4 theMat(1.0f);
    theMat[0].x = vector.x;
    theMat[1].y = vector.y;
    theMat[2].z = vector.z;
    return theMat;
}

glm::mat4 Transformations::getRotationMatrixDegrees(glm::vec3 axis, float angleDegrees)
{
    return getRotationMatrixRads(axis, angleDegrees * DEGREE_TO_RAD);
}

glm::mat4 Transformations::getRotationMatrixRads(glm::vec3 axis, float angleRads)
{
    float fCos = cosf(angleRads);
    float fInvCos = 1.0f - fCos;
    float fSin = sinf(angleRads);
    //float fInvSin = 1.0f - fSin;

    glm::vec3 axisNorm = glm::normalize(axis);

    glm::mat4 theMat(1.0f);
    theMat[0].x = (axisNorm.x * axisNorm.x) + ((1 - axisNorm.x * axisNorm.x) * fCos);
    theMat[1].x = axisNorm.x * axisNorm.y * (fInvCos) - (axisNorm.z * fSin);
    theMat[2].x = axisNorm.x * axisNorm.z * (fInvCos) + (axisNorm.y * fSin);

    theMat[0].y = axisNorm.x * axisNorm.y * (fInvCos) + (axisNorm.z * fSin);
    theMat[1].y = (axisNorm.y * axisNorm.y) + ((1 - axisNorm.y * axisNorm.y) * fCos);
    theMat[2].y = axisNorm.y * axisNorm.z * (fInvCos) - (axisNorm.x * fSin);

    theMat[0].z = axisNorm.x * axisNorm.z * (fInvCos) - (axisNorm.y * fSin);
    theMat[1].z = axisNorm.y * axisNorm.z * (fInvCos) + (axisNorm.x * fSin);
    theMat[2].z = (axisNorm.z * axisNorm.z) + ((1 - axisNorm.z * axisNorm.z) * fCos);

    return theMat;
}


Transformations::~Transformations(void)
{

}
