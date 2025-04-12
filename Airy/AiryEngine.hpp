//+-------------------------------------------------------------------------------
//    AiryEngine.hpp - High-level APIs for Airy - Haute-niveau APIs pour Airy
//                     Copyleft 2025 42yeah

#pragma once

#include "External/glad/glad.h"
#include "AiryGlobalContext.hpp"
#include "AiryObject.hpp"
#include "AiryProgram.hpp"

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <cstddef>

class Engine : public Object {
public:
    Engine() : mpGlobalContext(nullptr), mpWindow(nullptr), mRunning(false) {}
    ~Engine() override {
        Finalize();
    }

public:
    bool Init();
    void Finalize() override;

public:
    bool CreateWindow(size_t width, size_t height, const char *szName);
    bool CompileInternalShaders();
    void MainLoop();

    bool CompileProgram(
        const char *szName, const char *vertexShaderPath,
        const char *fragmentShaderPath, Ref<Program> &outProgram);

private:
    Ref<GlobalContext> mpGlobalContext;
    GLFWwindow *mpWindow;

    bool mRunning;
    std::unordered_map<std::string, Ref<Program> > mShaderLibary;
};
