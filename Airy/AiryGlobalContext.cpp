//+-------------------------------------------------------------------------------
//    AiryGlobalContext.cpp - Implementation - Implementation
//                            Copyleft 2025 42yeah

#include "AiryGlobalContext.hpp"
#include "External/glad/glad.h"

#include <GLFW/glfw3.h>

Ref<GlobalContext> gpGlobalContext = nullptr;

Ref<GlobalContext> GlobalContext::Get() {
    if (!gpGlobalContext) {
        gpGlobalContext = std::make_shared<GlobalContext>();
        if (!gpGlobalContext->Init()) {
            gpGlobalContext = nullptr;
            return nullptr;
        }
    }
    return gpGlobalContext;
}

bool GlobalContext::Init() {
    do {
        if (!glfwInit())
            break;

        mValid = true;
    } while (false);

    return mValid;
}

void GlobalContext::Finalize() {
    if (mValid) {
        glfwTerminate();
    }
    mValid = false;
}

bool GlobalContext::LoadGLFunctions() {
    if (!mValid) {
        return false;
    }
    return gladLoadGL();
}
