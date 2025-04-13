//+-------------------------------------------------------------------------------
//    AiryMeshRenderer.hpp - Renders a AiryMesh - Rendre un maille Airy
//                           Copyleft 2025 42yeah

#pragma once

#include "../External/glad/glad.h"

#include "../Data/AiryMaterial.hpp"
#include "../Data/AiryMesh.hpp"
#include "../Data/AiryMaterialPass.hpp"
#include "../Data/AiryRenderContext.hpp"
#include "../ECS/AiryComponent.hpp"

#include <glm/glm.hpp>
#include <utility>

class MeshRenderer : public Component {
public:
    MeshRenderer()
        : mMesh(nullptr)
        , mMaterial(nullptr)
        , mReady(false)
        , mIndexedDraw(false)
        , mVAO(GL_NONE)
        , mVBO(GL_NONE)
        , mEBO(GL_NONE) {
        SetName("MeshRenderer");
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
    bool Render(RenderContext &renderContext, const char *szPassName);

private:
    Ref<Mesh> mMesh;
    Ref<Material> mMaterial;  // TODO: Multiple materials

    bool mReady;
    bool mIndexedDraw;
    GLuint mVAO, mVBO, mEBO;
};
