//+-------------------------------------------------------------------------------
//    AiryEngine.hpp - High-level APIs for Airy - Haute-niveau APIs pour Airy
//                     Copyleft 2025 42yeah

#pragma once

#include "Airy/External/glad/glad.h"
#include "Airy/AiryGlobalContext.hpp"
#include "Airy/AiryObject.hpp"

#include <GLFW/glfw3.h>
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
    void MainLoop();

private:
    Ref<GlobalContext> mpGlobalContext;
    GLFWwindow *mpWindow;

    bool mRunning;
};
