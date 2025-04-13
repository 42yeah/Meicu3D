//+-------------------------------------------------------------------------------
//    AiryGlobalContext.hpp - Global static context such as GLFW states
//                          - Contexte mondiale pour etats GLFW
//
//                            Copyleft 2025 42yeah

#pragma once

#include "Pervasives/AiryObject.hpp"

class GlobalContext : public Object {
public:
    static Ref<GlobalContext> Get();

public:
    GlobalContext() : mValid(false) {}
    ~GlobalContext() override {
        Finalize();
    }

    bool Init();
    void Finalize() override;

    bool LoadGLFunctions();

    bool Valid() const {
        return mValid;
    }

private:
    bool mValid;
};
