//+-------------------------------------------------------------------------------
//    AiryCamera.hpp - Camera instance - Instance de camera
//                     Copyleft 2025 42yeah

#pragma once

#include "../ECS/AiryComponent.hpp"

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class Camera : public Component {
public:
    Camera()
        : mFovY(glm::radians(45.0f))
        , mAspect(1.0f)
        , mNear(0.1f)
        , mFar(100.0f) {
        SetName("Camera");
    }

    ~Camera() {
        Finalize();
    }

public:
    void Finalize() override;

    glm::mat4 View() const;
    glm::mat4 Perspective() const;

    float FovY() const {
        return mFovY;
    }
    void SetFovY(float fovy) {
        mFovY = fovy;
    }

    float Aspect() const {
        return mAspect;
    }
    void SetAspect(float aspect) {
        mAspect = aspect;
    }

    float Near() const {
        return mNear;
    }
    void SetNear(float near) {
        mNear = near;
    }

    float Far() const {
        return mFar;
    }
    void SetFar(float far) {
        mFar = far;
    }

private:
    float mFovY;
    float mAspect;
    float mNear;
    float mFar;
};
