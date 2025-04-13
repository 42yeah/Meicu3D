//+-------------------------------------------------------------------------------
//    AiryECSTest.cpp - Test for ECS template correctness
//                    - Test de l'exactitude du modele ECS
//                      Copyleft 2025 42yeah

#include "../Airy/AiryScene.hpp"
#include "../Airy/Systems/AiryRenderSystem.hpp"
#include "../Airy/ECS/AiryEntity.hpp"

#include <spdlog/spdlog.h>
#include <memory>

int main() {
    Ref<Scene> scene = std::make_shared<Scene>();
    scene->Init();
    RenderSystem *pRenderSystem = scene->GetSystemPtr<RenderSystem>();
    assert(pRenderSystem);
    Ref<RenderSystem> renderSystemRef = scene->GetSystem<RenderSystem>();
    assert(renderSystemRef);
    spdlog::info("OK");

    Ref<Entity> entity = std::make_shared<Entity>();
    Ref<MeshRenderer> renderer = entity->AddComponent<MeshRenderer>();

    Ref<MeshRenderer> another = std::make_shared<MeshRenderer>();
    entity->AddComponent(another);
    return 0;
}
