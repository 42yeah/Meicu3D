//+-------------------------------------------------------------------------------
//    AirySystem.hpp - System part of ECS - La partie "systeme" de ECS
//                     Copyleft 2025 42yeah

#pragma once

#include "../Pervasives/AiryObject.hpp"
#include "../ECS/AiryComponent.hpp"

class System : public Object {
public:
    System() {}
    ~System() override {
        Finalize();
    }

    virtual const char *Name() = 0;

    virtual bool RegisterEntity(const Ref<Entity> &entity) = 0;
    virtual bool UnregisterEntity(const Ref<Entity> &entity) = 0;

public:
    virtual bool Init() = 0;
    void Finalize() override;
};
