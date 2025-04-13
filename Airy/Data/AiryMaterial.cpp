//+-------------------------------------------------------------------------------
//    AiryMaterial.cpp - Implementation - Implementation
//                       Copyleft 2025 42yeah

#include "AiryMaterial.hpp"

bool MaterialProperties::Set(const char *uniformName, const MaterialProperty::Variant &value) {
    auto it = mProperties.find(uniformName);
    if (it == mProperties.end()) {
        spdlog::error("Uniform '{}' is not part of the properties", uniformName);
        assert(false);
        return false;
    }
    if (value.index() != it->second.value.index()) {
        spdlog::error(
            "Invalid type for '{}'. Expected type is {}, supplied type is {}",
            uniformName, it->second.value.index(), value.index());
        assert(false);
        return false;
    }
    it->second.value = value;
    return true;
}

void Material::Finalize() {
    mPasses.clear();
    mProperties.mProperties.clear();
}

void Material::AddPass(const char *szPassName, const Ref<MaterialPass> &pass) {
    mPasses[szPassName] = pass;
}
