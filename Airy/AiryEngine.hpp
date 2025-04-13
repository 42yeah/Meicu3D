//+-------------------------------------------------------------------------------
//    AiryEngine.hpp - High-level APIs for Airy - Haute-niveau APIs pour Airy
//                     Copyleft 2025 42yeah

#pragma once

#include "External/glad/glad.h"

#include "AiryScene.hpp"
#include "AiryGlobalContext.hpp"
#include "Data/AiryProgram.hpp"
#include "Data/AiryMaterial.hpp"
#include "Pervasives/AiryObject.hpp"

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <cstddef>

class Engine : public Object {
public:
    Engine()
        : mpGlobalContext(nullptr)
        , mpWindow(nullptr)
        , mRunning(false)
        , mShaderLibary()
        , mMaterials()
        , mScene(nullptr) {
    }

    ~Engine() override {
        Finalize();
    }

public:
    void Finalize() override;

public:
    bool CreateWindow(size_t width, size_t height, const char *szName);

    // Call CreateWindow first
    bool InitEngine();

    void MainLoop();

private:
    bool CompileInternalShaders();
    void CreateInternalMaterials();

    bool CompileProgram(
        const char *szName, const char *vertexShaderPath,
        const char *fragmentShaderPath, Ref<Program> &outProgram);

private:
    Ref<GlobalContext> mpGlobalContext;
    GLFWwindow *mpWindow;

    bool mRunning;
    std::unordered_map<std::string, Ref<Program> > mShaderLibary;
    std::unordered_map<std::string, Ref<Material> > mMaterials;

    Ref<Scene> mScene;
};
