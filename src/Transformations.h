#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include "Utils.h"


class Transformations
{
public:

    Transformations(void);
    virtual ~Transformations(void);


    static glm::mat4 getTranslationMatrix(glm::vec3 vector);
    static glm::mat4 getScaleMatrix(float amount);
    static glm::mat4 getScaleMatrix(glm::vec3 vector);
    static glm::mat4 getRotationMatrixDegrees(glm::vec3 axis, float angleDegrees);
    static glm::mat4 getRotationMatrixRads(glm::vec3 axis, float angleRads);
};



