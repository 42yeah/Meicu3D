//+-------------------------------------------------------------------------------
//    AiryMeshRenderer.hpp - Renders a AiryMesh - Rendre un maille Airy
//                           Copyleft 2025 42yeah

#pragma once

#include "External/glad/glad.h"
#include "AiryMaterial.hpp"
#include "AiryMesh.hpp"
#include "AiryObject.hpp"

#include <utility>

class MeshRenderer : public Object {
public:
    MeshRenderer()
        : mMesh(nullptr)
        , mMaterial(nullptr)
        , mReady(false)
        , mIndexedDraw(false)
        , mVAO(GL_NONE)
        , mVBO(GL_NONE)
        , mEBO(GL_NONE) {
    }

    ~MeshRenderer() {
        Finalize();
    }

public:
    template <typename T>
    void SetMesh(T &&mesh) {
        mMesh = std::forward<T>(mesh);
    }

    template <typename T>
    void SetMaterial(T &&material) {
        mMaterial = std::forward<T>(material);
    }

    void Finalize() override;

    bool Prepare();
    bool Render(const char *szPassName);

private:
    Ref<Mesh> mMesh;
    Ref<Material> mMaterial;  // TODO: Multiple materials

    bool mReady;
    bool mIndexedDraw;
    GLuint mVAO, mVBO, mEBO;
};
