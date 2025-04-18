//+-------------------------------------------------------------------------------
//    AiryRenderSystem.hpp - Renders registered "Renderers"
//                         - Rendus enregistres "Renderers"
//                           Copyleft 2025 42yeah

#pragma once

#include "../ECS/AirySystem.hpp"
#include "../Components/AiryCamera.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <set>

class RenderSystem : public System {
public:
    RenderSystem() : mEntities() {}
    ~RenderSystem() override {
        Finalize();
    }

public:
    const char *Name() override {
        return "RenderSystem";
    }

    bool Init() override;
    void Finalize() override;

    bool RegisterEntity(const Ref<Entity> &entity) override;
    bool UpdateEntity(const Ref<Entity> &entity) override;
    bool UnregisterEntity(const Ref<Entity> &entity) override;

    bool Render(const Ref<Camera> &camera);

private:
    std::set<Ref<Entity> > mEntities;
};
