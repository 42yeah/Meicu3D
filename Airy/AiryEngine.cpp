//+-------------------------------------------------------------------------------
//    AiryEngine.cpp - Implementation - Implementation
//                     Copyleft 2025 42yeah

#include "AiryEngine.hpp"

#include "Assets/AiryAssets.h"
#include "AiryObject.hpp"
#include "AiryShader.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

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

bool Engine::CompileInternalShaders() {
    Ref<Program> dummyProgram = nullptr;

    CompileProgram(
        "Triangle",
        shaders::Triangle_vs_Path(),
        shaders::Triangle_fs_Path(),
        dummyProgram);

    return true;
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

bool Engine::CompileProgram(
    const char *szName, const char *vertexShaderPath,
    const char *fragmentShaderPath, Ref<Program> &outProgram) {

    Ref<Shader> vertexShader =
        std::make_shared<Shader>(GL_VERTEX_SHADER, vertexShaderPath);

    Ref<Shader> fragmentShader =
        std::make_shared<Shader>(GL_FRAGMENT_SHADER, fragmentShaderPath);

    outProgram = std::make_shared<Program>();
    bool ok = outProgram->Link(vertexShader, fragmentShader);

    if (!ok) {
        spdlog::error("Failed to link program '{}'", szName);

        if (!vertexShader->Valid()) {
            spdlog::error(
                "Vertex shader '{}' is invalid, log: {}",
                vertexShaderPath, vertexShader->CompileLog());
        }
        if (!fragmentShader->Valid()) {
            spdlog::error(
                "Fragment shader '{}' is invalid, log: {}",
                fragmentShaderPath, fragmentShader->CompileLog());
        }
        return false;
    }

    mShaderLibary[szName] = std::move(outProgram);
    return true;
}
