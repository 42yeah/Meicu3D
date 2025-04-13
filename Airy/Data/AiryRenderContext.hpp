//+-------------------------------------------------------------------------------
//    AiryRenderContext.hpp - Data required to render one frame (transforms, etc.)
//                          - Donnees necessaires au rendu une trame
//                            Copyleft 2025 42yeah

#pragma once

#include "../Data/AiryTransform.hpp"
#include "../Components/AiryCamera.hpp"
#include "../Pervasives/AiryObject.hpp"

struct RenderContext {
    // Set by AiryScene
    Ref<Camera> camera;

    // Set by MeshRenderer
    // TODO: Pass in a vector of ROs like a normal human being
    Transform transform;

public:
    RenderContext() : camera(nullptr), transform() {
    }
};
