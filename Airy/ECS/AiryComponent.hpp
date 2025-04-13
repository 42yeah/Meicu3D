//+-------------------------------------------------------------------------------
//    AiryComponent.hpp - Component part of ECS - La partie "composante" de ECS
//                        Copyleft 2025 42yeah

#pragma once

#include "../Pervasives/AiryObject.hpp"
#include <string>

class Entity;

class Component : public Object {
public:
    Component() : mName("GenericComponent"), mpEntity(nullptr) {}
    ~Component() {
        Finalize();
    }

public:
    void Finalize() override;

    void SetName(const std::string &name) {
        mName = name;
    }
    const std::string &Name() const {
        return mName;
    }

    /* WARN: Should be used by `Entity` only - don't do this unless you know what
             you're doing!
    */
    void SetEntity(Entity *pEntity) {
        mpEntity = pEntity;
    }
    Entity *GetEntity() {
        return mpEntity;
    }
    const Entity *GetEntity() const {
        return mpEntity;
    }

protected:
    std::string mName;
    Entity *mpEntity;
};
