//+-------------------------------------------------------------------------------
//    AiryProgram.hpp - Program wrapper for Airy - Emballage pour Program
//                      Copyleft 2025 42yeah

#include "External/glad/glad.h"
#include "AiryShader.hpp"
#include "AiryObject.hpp"

class Program : public Object {
public:
    Program() : mValid(false), mProgram(GL_NONE) {}
    ~Program() {
        Finalize();
    }

public:
    bool Link(const Ref<Shader> &vertexShader, const Ref<Shader> &fragmentShader);

    void Finalize();

    bool Valid() const {
        return mValid;
    }

    GLuint NativeHandle() const {
        return mProgram;
    }

    const std::string &LinkLog() const {
        return mLinkLog;
    }

private:
    bool mValid;

    GLuint mProgram;

    std::string mLinkLog;
};
