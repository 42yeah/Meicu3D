//+-------------------------------------------------------------------------------
//    AiryRenderSystem.cpp - Implementation - Implementation
//                           Copyleft 2025 42yeah

#include "AiryRenderSystem.hpp"

#include "../ECS/AiryEntity.hpp"
#include "../Components/AiryMeshRenderer.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <algorithm>
#include <spdlog/spdlog.h>

bool RenderSystem::Init() {
    return true;
}

void RenderSystem::Finalize() {
    mEntities.clear();
}

bool RenderSystem::RegisterEntity(const Ref<Entity> &entity) {
    if (!entity)
        return false;

    const MeshRenderer *pMeshRenderer = entity->GetComponentPtr<MeshRenderer>();
    if (!pMeshRenderer) return false;

    mEntities.push_back(entity);
    return true;
}

bool RenderSystem::UnregisterEntity(const Ref<Entity> &entity) {
    auto it = std::find(mEntities.begin(), mEntities.end(), entity);
    if (it == mEntities.end())
        return false;
    mEntities.erase(it);
    return true;
}

bool RenderSystem::Render() {
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

        if (!meshRenderer->Render("Lighting")) {
            spdlog::error("Failed to render entity {}", pEntity->Name());
        }

        ++it;
    }
    return true;
}
