//+-------------------------------------------------------------------------------
//    main.cpp - Entry point of Meicu3D - Point d'entree de Meicu3D
//               Copyleft 2025 42yeah

#include "Airy/AiryEngine.hpp"

int main() {
    Ref<Engine> engine = std::make_shared<Engine>();

    do {
        if (!engine->CreateWindow(400, 300, "Hello")) {
            spdlog::error("Failed to create window");
            return 1;
        }

        if (!engine->InitEngine()) {
            spdlog::error("Failed to initialize engine");
            return 2;
        }

        engine->MainLoop();

        return 0;
    } while (false);

    return 1;
}
