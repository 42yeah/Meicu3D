//+-------------------------------------------------------------------------------
//    main.cpp - Entry point of Meicu3D - Point d'entree de Meicu3D
//               Copyleft 2025 42yeah

#include <spdlog/spdlog.h>

#include "Airy/AiryEngine.hpp"
#include "Airy/AiryObject.hpp"

int main() {
    Ref<Engine> engine = std::make_shared<Engine>();
    engine->Init();
    engine->CreateWindow(400, 300, "Hello");
    engine->MainLoop();

    return 0;
}
