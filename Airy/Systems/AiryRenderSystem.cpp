//+-------------------------------------------------------------------------------
//    AiryRenderSystem.cpp - Implementation - Implementation
//                           Copyleft 2025 42yeah

#include "AiryRenderSystem.hpp"

#include "../ECS/AiryEntity.hpp"
#include "../Components/AiryMeshRenderer.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <algorithm>

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
    return true;
}
