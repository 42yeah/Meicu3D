//+-------------------------------------------------------------------------------
//    AiryEngine.cpp - Implementation - Implementation
//                     Copyleft 2025 42yeah

#include "AiryEngine.hpp"

#include <GLFW/glfw3.h>

bool Engine::Init() {
    mpGlobalContext = GlobalContext::Get();
    if (!mpGlobalContext) {
        return false;
    }

    return true;
}

void Engine::Finalize() {
    if (mpWindow) {
        glfwDestroyWindow(mpWindow);
        mpWindow = nullptr;
    }
    mRunning = false;
}

bool Engine::CreateWindow(size_t width, size_t height, const char *szName) {
    if (!mpGlobalContext) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mpWindow = glfwCreateWindow(width, height, szName, nullptr, nullptr);
    if (!mpWindow)
        return false;

    glfwMakeContextCurrent(mpWindow);
    return mpGlobalContext->LoadGLFunctions();
}

void Engine::MainLoop() {
    mRunning = true;

    while (mRunning && !glfwWindowShouldClose(mpWindow)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(mpWindow);
    }

    mRunning = false;
}
