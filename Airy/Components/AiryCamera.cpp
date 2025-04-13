//+-------------------------------------------------------------------------------
//    AiryCamera.cpp - Implementation - Implementation
//                     Copyleft 2025 42yeah

#include "AiryCamera.hpp"

#include "../ECS/AiryEntity.hpp"
#include "Data/AiryTransform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

void Camera::Finalize() {
    mFovY = glm::radians(45.0f);
    mAspect = 1.0f;
    mNear = 0.1f;
    mFar = 100.0f;
}

glm::mat4 Camera::View() const {
    if (!mpEntity) {
        spdlog::error("No entity for camera {}", Name());
    }
    Transform transform = mpEntity->GetTransform();
    transform.scale = glm::vec3(1.0f);
    return transform.Inv();
}

glm::mat4 Camera::Perspective() const {
    return glm::perspective(mFovY, mAspect, mNear, mFar);
}
