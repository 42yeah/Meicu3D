//+-------------------------------------------------------------------------------
//    AiryMaterial.hpp - Material for Airy - Materiel pour Airy
//                       Copyleft 2025 42yeah

#pragma once

#include "AiryMaterialPass.hpp"
#include "../Pervasives/AiryObject.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <variant>

class Material;

struct MaterialProperty {
    using Variant = std::variant<
        int, float, glm::vec2, glm::vec3,
        glm::vec4, glm::mat2x2, glm::mat3x3,
        glm::mat4x4
    >;

    const char *name;
    Variant value;

    MaterialProperty()
        : name(nullptr)
        , value() {
    }
};

class MaterialProperties {
public:
    MaterialProperties() : mProperties() {}

    bool Set(const char *uniformName, const MaterialProperty::Variant &value);

private:
    std::unordered_map<const char *, MaterialProperty> mProperties;

    friend class Material;
    friend class MaterialPass;
};

class Material : public Object {
public:
    Material() : mProperties(), mPasses() {}
    ~Material() {
        Finalize();
    }

public:
    void Finalize() override;

    template <typename T>
    void DeclareProperty(const char *szPropertyName) {
        MaterialProperty &prop = mProperties.mProperties[szPropertyName];
        prop.name = szPropertyName;
        prop.value = static_cast<T>(0);
    }

    MaterialProperties &Properties() {
        return mProperties;
    }
    const MaterialProperties &Properties() const {
        return mProperties;
    }

    void AddPass(const char *szPassName, const Ref<MaterialPass> &pass);

    const Ref<MaterialPass> &GetPass(const char *szPassName) {
        return mPasses[szPassName];
    }

private:
    MaterialProperties mProperties;
    std::unordered_map<std::string, Ref<MaterialPass> > mPasses;
};
