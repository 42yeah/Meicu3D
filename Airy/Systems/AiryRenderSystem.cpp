//+-------------------------------------------------------------------------------
//    AiryRenderSystem.cpp - Implementation - Implementation
//                           Copyleft 2025 42yeah

#include "AiryRenderSystem.hpp"

#include "../ECS/AiryEntity.hpp"
#include "../Components/AiryMeshRenderer.hpp"
#include "../Data/AiryRenderContext.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <algorithm>
#include <cassert>
#include <spdlog/spdlog.h>

bool RenderSystem::Init() {
    return true;
}

void RenderSystem::Finalize() {
    mEntities.clear();
}

bool RenderSystem::RegisterEntity(const Ref<Entity> &entity) {
    return UpdateEntity(entity);
}

bool RenderSystem::UpdateEntity(const Ref<Entity> &entity) {
    if (!entity)
        return false;

    auto it = mEntities.find(entity);
    bool entityRegistered = (it != mEntities.end());
    bool hasMeshRenderer = entity->GetComponentPtr<MeshRenderer>();

    if (hasMeshRenderer == entityRegistered) {
        return false;
    } else if (hasMeshRenderer && !entityRegistered) {
        mEntities.emplace(entity);
        return true;
    } else if (!hasMeshRenderer && entityRegistered) {
        mEntities.erase(it);
        return false;
    }
    assert(false);  // Unreachable
    return false;
}

bool RenderSystem::UnregisterEntity(const Ref<Entity> &entity) {
    auto it = std::find(mEntities.begin(), mEntities.end(), entity);
    if (it == mEntities.end())
        return false;
    mEntities.erase(it);
    return true;
}

bool RenderSystem::Render(const Ref<Camera> &camera) {
    if (!camera) {
        spdlog::error("Rendering for a NULL camera");
        return false;
    }

    RenderContext renderContext;
    renderContext.camera = camera;

    for (auto it = mEntities.cbegin(); it != mEntities.cend();) {
        const Entity *pEntity = it->get();
        const Ref<MeshRenderer> &meshRenderer = pEntity->GetComponent<MeshRenderer>();

        if (!meshRenderer) {
            spdlog::warn("MeshRenderer is missing in entity {} - removing", pEntity->Name());
            auto itNext = ++it;
            mEntities.erase(it);
            it = itNext;
            continue;
        }

        if (!meshRenderer->Render(renderContext, "Lighting")) {
            spdlog::error("Failed to render entity {}", pEntity->Name());
        }

        ++it;
    }
    return true;
}
