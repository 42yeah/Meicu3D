//+-------------------------------------------------------------------------------
//    main.cpp - Entry point of Meicu3D - Point d'entree de Meicu3D
//               Copyleft 2025 42yeah

#include "Airy/AiryEngine.hpp"
#include "Airy/AiryScene.hpp"
#include "Airy/Components/AiryMeshRenderer.hpp"
#include "Airy/Pervasives/AiryObject.hpp"

bool AppMain() {
    Ref<Engine> engine = std::make_shared<Engine>();

    if (!engine->CreateWindow(400, 300, "Hello")) {
        spdlog::error("Failed to create window");
        return false;
    }

    if (!engine->InitEngine()) {
        spdlog::error("Failed to initialize engine");
        return false;
    }

    Ref<Scene> scene = engine->GetScene();
    // Ref<Entity> demoEntity = scene->AddEntity("TriangleEntity");
    Ref<Entity> demoEntity = std::make_shared<Entity>();
    demoEntity->SetName("Triangle Entity");
    Ref<MeshRenderer> demoMeshRenderer = demoEntity->AddComponent<MeshRenderer>();

    Ref<Mesh> demoMesh = Mesh::TriangleMesh();
    demoMeshRenderer->SetMesh(demoMesh);
    Ref<Material> demoMaterial = engine->GetMaterial("Triangle");
    demoMeshRenderer->SetMaterial(std::move(demoMaterial));

    scene->AddEntity(std::move(demoEntity));

    engine->MainLoop();

    return true;
}

int main() {
    bool ok = AppMain();

    if (!ok)
        return 1;

    return 0;
}
