//+-------------------------------------------------------------------------------
//    AiryEntity.cpp - Implementation - Implementation
//                     Copyleft 2025 42yeah

#include "AiryEntity.hpp"

#include "../AiryScene.hpp"

void Entity::Finalize() {
    mName = "Entity";
    mComponents.clear();
    mTransform = Transform();
    mpScene = nullptr;
}

void Entity::NotifyScene() {
    mpScene->NotifyEntityChanged(shared_from_this());
}
