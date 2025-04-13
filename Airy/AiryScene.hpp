//+-------------------------------------------------------------------------------
//    AiryScene.hpp - Engine scene implementation - Implementation de la scene
//                    Copyleft 2025 42yeah

#pragma once

#include "ECS/AiryEntity.hpp"
#include "Pervasives/AiryObject.hpp"
#include "ECS/AirySystem.hpp"

#include <unordered_map>
#include <vector>

class Scene : public Object {
public:
    Scene() : mSystems(), mEntities() {}
    ~Scene() {
        Finalize();
    }

public:
    bool Init();
    void Finalize() override;

    // T must be Ref<U>, where U is derived from System
    template <typename T>
    void AddSystem(T &&system) {
        using U = std::decay_t<decltype(*system.get())>;
        static_assert(
            std::is_base_of<System, U>(), "Failed type compliancy test");

        size_t typeHash = typeid(U).hash_code();
        mSystems[typeHash] = std::forward<T>(system);
    }
    template <typename T>
    Ref<T> GetSystem() {
        static_assert(std::is_base_of<System, T>(), "Failed type compliancy test");
        size_t typeHash = typeid(T).hash_code();
        return std::static_pointer_cast<T>(mSystems[typeHash]);
    }
    template <typename T>
    Ref<T> GetSystem() const {
        static_assert(std::is_base_of<System, T>(), "Failed type compliancy test");
        size_t typeHash = typeid(T).hash_code();
        auto it = mSystems.find(typeHash);
        if (it == mSystems.end())
            return nullptr;
        return std::static_pointer_cast<T>(it->second);
    }
    template <typename T>
    T *GetSystemPtr() {
        static_assert(std::is_base_of<System, T>(), "Failed type compliancy test");
        size_t typeHash = typeid(T).hash_code();
        return static_cast<T *>(mSystems[typeHash].get());
    }
    template <typename T>
    const T *GetSystemPtr() const {
        static_assert(std::is_base_of<System, T>(), "Failed type compliancy test");
        size_t typeHash = typeid(T).hash_code();
        auto it = mSystems.find(typeHash);
        if (it == mSystems.end())
            return nullptr;
        return static_cast<T *>(it->second.get());
    }

    bool Render();

    void AddEntity(const Ref<Entity> &entity);

private:
    std::unordered_map<size_t, Ref<System> > mSystems;

    using EntityGroup = std::vector<Ref<Entity> >;
    EntityGroup mEntities;
};
