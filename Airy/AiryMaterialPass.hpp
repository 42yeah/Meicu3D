//+-------------------------------------------------------------------------------
//    AiryMaterialPass.hpp - Material pass for Airy - Passe de Materiel pour Airy
//                           Copyleft 2025 42yeah

#pragma once

#include "AiryProgram.hpp"
#include "AiryObject.hpp"

class Material;

class MaterialPass : public Object {
public:
    MaterialPass(Material *pMaterial, const Ref<Program> &program)
        : mpMaterial(pMaterial)
        , mProgram(program) {
    }

    ~MaterialPass() {
        Finalize();
    }

public:
    void Finalize() override;

    // Let the renderer use it
    // TODO: Model matrices et al.
    void SetupRenderer();

private:
    Material *mpMaterial;
    Ref<Program> mProgram;
};
