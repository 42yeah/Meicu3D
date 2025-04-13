//+-------------------------------------------------------------------------------
//    AiryObject.hpp - Object for Airy Engine - Objet pour Moteur Airy
//                     Copyleft 2025 42yeah

#pragma once

#include <memory>

class Object {
public:
    virtual ~Object() {}

    Object() {}
    Object(const Object &) = delete;
    Object(Object &&) = delete;

    virtual void Finalize() = 0;
};

template <typename T>
using Ref = std::shared_ptr<T>;
