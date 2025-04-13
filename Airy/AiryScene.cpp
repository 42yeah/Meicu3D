//+-------------------------------------------------------------------------------
//    AiryScene.cpp - Implementation - Implementation
//                    Copyleft 2025 42yeah

#include "AiryScene.hpp"

#include "ECS/AiryEntity.hpp"
#include "ECS/AirySystem.hpp"
#include "Systems/AiryRenderSystem.hpp"
#include "Pervasives/AiryObject.hpp"

#include <spdlog/spdlog.h>

constexpr const char *TAG = "AiryScene";

bool Scene::Init() {
    // Add internal systems
    AddSystem(std::make_shared<RenderSystem>());

    // Initialize all systems
    bool ok = true;
    for (std::pair<size_t, const Ref<System> &> systemPair : mSystems) {
        const Ref<System> &system = systemPair.second;
        if (!system) {
            spdlog::error("[{}] System {} is NULL!", TAG, typeid(system).name());
            ok = false;
            continue;
        }
        if (!system->Init()) {
            spdlog::warn("[{}] Failed to initialize system {}", TAG, system->Name());
            ok = false;
            continue;
        }
        spdlog::info("[{}] System initialized: {}", TAG, system->Name());
    }

    return ok;
}

void Scene::Finalize() {
    for (std::pair<size_t, const Ref<System> &> systemPair : mSystems) {
        const Ref<System> &system = systemPair.second;
        for (const Ref<Entity> &entity : mEntities) {
            system->UnregisterEntity(entity);
        }
    }
    mEntities.clear();
    mSystems.clear();
}

bool Scene::Render() {
    RenderSystem *pRenderSystem = GetSystemPtr<RenderSystem>();
    if (!pRenderSystem) {
        spdlog::error("No render system - initialization might've failed");
        return false;
    }
    return pRenderSystem->Render();
}

void Scene::AddEntity(const Ref<Entity> &entity) {
    if (!entity) {
        spdlog::error("Trying to add NULL entity to scene");
        return;
    }
    mEntities.push_back(entity);

    // Register to ALL systems
    for (std::pair<size_t, const Ref<System> &> systemPair : mSystems) {
        systemPair.second->RegisterEntity(entity);
    }
}

Ref<Entity> Scene::AddEntity(const char *szName) {
    Ref<Entity> entity = std::make_shared<Entity>();
    entity->SetName(szName);
    AddEntity(entity);
    return entity;
}
