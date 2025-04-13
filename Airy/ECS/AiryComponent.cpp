//+-------------------------------------------------------------------------------
//    AiryComponent.cpp - Implementation - Implementation
//                        Copyleft 2025 42yeah

#include "AiryComponent.hpp"

void Component::Finalize() {
    mpEntity = nullptr;
    mName = "GenericComponent";
}
