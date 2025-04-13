//+-------------------------------------------------------------------------------
//    AiryScene.cpp - Implementation - Implementation
//                    Copyleft 2025 42yeah

#include "AiryScene.hpp"

#include "ECS/AiryEntity.hpp"
#include "ECS/AirySystem.hpp"
#include "Systems/AiryRenderSystem.hpp"
#include "Pervasives/AiryObject.hpp"

#include <spdlog/spdlog.h>
#include <algorithm>

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
    mMainCamera = nullptr;

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
    if (!mMainCamera) {
        spdlog::error("No main camera detected - add one entity with a camera to continue");
        return false;
    }
    return pRenderSystem->Render(mMainCamera);
}

void Scene::AddEntity(const Ref<Entity> &entity) {
    if (!entity) {
        spdlog::error("Trying to add NULL entity to scene");
        return;
    }

    entity->SetScene(this);
    mEntities.push_back(entity);

    // Register to ALL systems
    for (std::pair<size_t, const Ref<System> &> systemPair : mSystems) {
        systemPair.second->RegisterEntity(entity);
    }
    Ref<Camera> camera = entity->GetComponent<Camera>();
    if (camera && !mMainCamera) {
        spdlog::info("Setting default main camera to {}", camera->Name());
        mMainCamera = camera;
    }
}

Ref<Entity> Scene::AddEntity(const char *szName) {
    Ref<Entity> entity = std::make_shared<Entity>();
    entity->SetName(szName);
    AddEntity(entity);
    return entity;
}

void Scene::RemoveEntity(const Ref<Entity> &entity) {
    if (!entity) return;

    auto it = std::find(mEntities.begin(), mEntities.end(), entity);
    if (it == mEntities.end()) {
        spdlog::error("No such entity: {}", entity->Name());
        return;
    }
    for (std::pair<size_t, const Ref<System> &> systemPair : mSystems) {
        const Ref<System> &system = systemPair.second;
        for (const Ref<Entity> &entity : mEntities) {
            system->UnregisterEntity(entity);
        }
    }

    mEntities.erase(it);
}

void Scene::NotifyEntityChanged(const Ref<Entity> &entity) {
    if (!entity) return;

    for (std::pair<size_t, const Ref<System> &> systemPair : mSystems) {
        const Ref<System> &system = systemPair.second;
        system->UpdateEntity(entity);
    }
    Ref<Camera> camera = entity->GetComponent<Camera>();
    if (camera && !mMainCamera) {
        spdlog::info("[{}] Setting default main camera to {}", TAG, camera->Name());
        mMainCamera = camera;
    }
}
