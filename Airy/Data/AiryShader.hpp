//+-------------------------------------------------------------------------------
//    AiryShader.hpp - Shader wrapper for Airy - Embellage pour Nuanceur
//                     Copyleft 2025 42yeah

#pragma once

#include "../External/glad/glad.h"
#include "../Pervasives/AiryObject.hpp"

#include <string>

class Shader : public Object {
public:
    Shader(GLuint type, const char *path)
        : mType(type)
        , mPath(path)
        , mValid(false)
        , mShader(GL_NONE)
        , mCompileLog()
    {
    }

    ~Shader() {
        Finalize();
    }

public:
    bool Compile();

    void Finalize();

    bool Valid() const {
        return mValid;
    }

    const std::string &CompileLog() const {
        return mCompileLog;
    }

    GLuint NativeHandle() const {
        return mShader;
    }

private:
    GLuint mType;
    const char *mPath;

    bool mValid;
    GLuint mShader;

    std::string mCompileLog;
};
