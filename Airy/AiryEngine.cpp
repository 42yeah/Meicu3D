//+-------------------------------------------------------------------------------
//    AiryEngine.cpp - Implementation - Implementation
//                     Copyleft 2025 42yeah

#include "AiryEngine.hpp"

#include "Assets/AiryAssets.h"
#include "Data/AiryShader.hpp"
#include "Data/AiryMesh.hpp"
#include "Pervasives/AiryObject.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

void Engine::Finalize() {
    mTestMeshRenderer = nullptr;
    mShaderLibary.clear();
    mMaterials.clear();
    if (mpWindow) {
        glfwDestroyWindow(mpWindow);
        mpWindow = nullptr;
    }
    mRunning = false;
}

bool Engine::CreateWindow(size_t width, size_t height, const char *szName) {
    mpGlobalContext = GlobalContext::Get();
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

bool Engine::InitEngine() {
    do {
        mpGlobalContext = GlobalContext::Get();
        if (!mpGlobalContext)
            break;
        if (!CompileInternalShaders())
            break;

        CreateInternalMaterials();

        CreateDebugStuffs();

        return true;
    } while (false);

    return true;
}

void Engine::MainLoop() {
    mRunning = true;

    while (mRunning && !glfwWindowShouldClose(mpWindow)) {
        glfwPollEvents();

        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mTestMeshRenderer->Render("Lighting");

        glfwSwapBuffers(mpWindow);
    }

    mRunning = false;
}

bool Engine::CompileInternalShaders() {
    Ref<Program> program = nullptr;

    CompileProgram(
        "Triangle",
        shaders::Triangle_vs_Path(),
        shaders::Triangle_fs_Path(),
        program);

    return true;
}

void Engine::CreateInternalMaterials() {
    Ref<Material> triangleMaterial = std::make_shared<Material>();
    Ref<MaterialPass> trianglePass = std::make_shared<MaterialPass>(triangleMaterial.get(), mShaderLibary["Triangle"]);

    triangleMaterial->AddPass("Lighting", trianglePass);
    // triangleMaterial->DeclareProperty<float>("time");

    mMaterials["Triangle"] = std::move(triangleMaterial);
}

void Engine::CreateDebugStuffs() {
    Ref<Mesh> testMesh = Mesh::TriangleMesh();
    Ref<MeshRenderer> renderer = std::make_shared<MeshRenderer>();
    renderer->SetMesh(std::move(testMesh));
    renderer->SetMaterial(mMaterials["Triangle"]);

    mTestMeshRenderer = std::move(renderer);
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

    mShaderLibary[szName] = outProgram;
    return true;
}
