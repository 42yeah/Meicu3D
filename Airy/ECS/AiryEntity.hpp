//+-------------------------------------------------------------------------------
//    AiryEntity.hpp - Entity part of ECS - La partie "entite" de ECS
//                     Copyleft 2025 42yeah

#pragma once

#include "AiryComponent.hpp"

#include "../Data/AiryTransform.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <memory>
#include <type_traits>
#include <unordered_map>

class Scene;

class Entity : public Object, public std::enable_shared_from_this<Entity> {
public:
    Entity() : mName("Entity"), mComponents(), mTransform(), mpScene(nullptr) {}
    ~Entity() {
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

    template <typename T>
    Ref<T> AddComponent() {
        static_assert(
            std::is_base_of<Component, T>(), "Failed type compliancy test");
        Ref<T> comp = std::make_shared<T>();
        comp->SetEntity(this);
        size_t typeHash = typeid(T).hash_code();
        auto it = mComponents.find(typeHash);
        if (it != mComponents.end()) {
            spdlog::warn(
                "Component {} already present in entity {} - recreating",
                it->second->Name(), Name());
        }
        mComponents[typeHash] = comp;

        NotifyScene();
        return comp;
    }

    // T must be Ref<U>, where U is derived from Component
    template <typename T>
    void AddComponent(T &&comp) {
        using U = std::decay_t<decltype(*comp.get())>;
        static_assert(std::is_base_of<Component, U>(), "Failed type compliancy test");
        size_t typeHash = typeid(U).hash_code();
        if (comp) {
            comp->SetEntity(this);
        }
        auto it = mComponents.find(typeHash);
        if (it != mComponents.end()) {
            spdlog::warn(
                "Component {} already present in entity {} - replacing with {}",
                it->second->Name(), Name(), comp->Name());
        }
        mComponents[typeHash] = std::forward<T>(comp);
        NotifyScene();
    }

    template <typename T>
    Ref<T> GetComponent() const {
        static_assert(
            std::is_base_of<Component, T>(), "Failed type compliancy test");
        size_t typeHash = typeid(T).hash_code();
        auto it = mComponents.find(typeHash);
        if (it != mComponents.end())
            return std::static_pointer_cast<T>(it->second);
        return nullptr;
    }
    template <typename T>
    const T *GetComponentPtr() const {
        static_assert(
            std::is_base_of<Component, T>(), "Failed type compliancy test");
        size_t typeHash = typeid(T).hash_code();
        auto it = mComponents.find(typeHash);
        if (it != mComponents.end())
            return static_cast<T *>(it->second.get());
        return nullptr;
    }

    const std::unordered_map<size_t, Ref<Component> > &Components() {
        return mComponents;
    }

    void SetTransform(const Transform &transform) {
        mTransform = transform;
    }
    const Transform GetTransform() const {
        return mTransform;
    }

    // WARN: Should be used by `Scene` only
    void SetScene(Scene *pScene) {
        mpScene = pScene;
    }
    Scene *GetScene() const {
        return mpScene;
    }

private:
    void NotifyScene();

private:
    std::string mName;
    std::unordered_map<size_t, Ref<Component> > mComponents;
    Transform mTransform;

    Scene *mpScene;
};
