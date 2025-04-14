//+-------------------------------------------------------------------------------
//    AiryMaterialPass.cpp - Implementation - Implementation
//                           Copyleft 2025 42yeah

#include "AiryMaterialPass.hpp"

#include "AiryMaterial.hpp"
#include "AiryRenderContext.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <variant>

void MaterialPass::Finalize() {
    mpMaterial = nullptr;
    mProgram = nullptr;
}

void MaterialPass::SetupRenderer(const RenderContext &renderContext) {
    if (!mpMaterial || !mProgram) {
        spdlog::error("Incomplete material pass");
        assert(false);
        return;
    }

    mProgram->Use();

    // MVP
    if (mProgram->HasUniform("model"))
        mProgram->UniformMat4x4f("model", renderContext.transform.Matrix());

    if (mProgram->HasUniform("view"))
        mProgram->UniformMat4x4f("view", renderContext.camera->View());

    if (mProgram->HasUniform("perspective"))
        mProgram->UniformMat4x4f("perspective", renderContext.camera->Perspective());

    const std::unordered_map<const char *, MaterialProperty> &props =
        mpMaterial->Properties().mProperties;

    for (const std::pair<const char *, const MaterialProperty &> prop : props) {
        const MaterialProperty::Variant &value = prop.second.value;

        const int *piVal = std::get_if<int>(&value);
        if (piVal) {
            mProgram->Uniform1i(prop.first, *piVal);
            continue;
        }

        const float *pfVal = std::get_if<float>(&value);
        if (pfVal) {
            mProgram->Uniform1f(prop.first, *pfVal);
            continue;
        }

        const glm::vec2 *pVec2 = std::get_if<glm::vec2>(&value);
        if (pVec2) {
            mProgram->Uniform2f(prop.first, *pVec2);
            continue;
        }

        const glm::vec3 *pVec3 = std::get_if<glm::vec3>(&value);
        if (pVec3) {
            mProgram->Uniform3f(prop.first, *pVec3);
            continue;
        }

        const glm::vec4 *pVec4 = std::get_if<glm::vec4>(&value);
        if (pVec4) {
            mProgram->Uniform4f(prop.first, *pVec4);
            continue;
        }

        const glm::mat2 *pMat2 = std::get_if<glm::mat2>(&value);
        if (pMat2) {
            mProgram->UniformMat2x2f(prop.first, *pMat2);
            continue;
        }

        const glm::mat3 *pMat3 = std::get_if<glm::mat3>(&value);
        if (pMat3) {
            mProgram->UniformMat3x3f(prop.first, *pMat3);
            continue;
        }

        const glm::mat4 *pMat4 = std::get_if<glm::mat4>(&value);
        if (pMat4) {
            mProgram->UniformMat4x4f(prop.first, *pMat4);
            continue;
        }

        spdlog::error("Invalid variant {}", prop.first);
        assert(false);
    }
}
