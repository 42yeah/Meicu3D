//+-------------------------------------------------------------------------------
//    AiryMesh.hpp - 3D render primitives - Primitives de rendre
//                   Copyleft 2025 42yeah

#pragma once

#include "External/glad/glad.h"
#include "AiryObject.hpp"
#include "AiryVertexDataStream.hpp"

#include <utility>

class Mesh : public Object {
public:
    Mesh()
        : mPositionStream(nullptr)
        , mNormalStream(nullptr)
        , mTexCoordStream(nullptr)
        , mIndices(nullptr) {
    }

    ~Mesh() override {
        Finalize();
    }

public:
    static Ref<Mesh> TriangleMesh();

public:
    void Finalize() override;

    size_t NumVertices();
    size_t NumIndices() const {
        if (!mIndices)
            return 0;
        return mIndices->size();
    }

    template <typename T>
    void SetPositionStream(T &&positionStream) {
        mPositionStream = std::forward<T>(positionStream);
    }
    template <typename T>
    void SetNormalStream(T &&normalStream) {
        mNormalStream = std::forward<T>(normalStream);
    }
    template <typename T>
    void SetTexCoordStream(T &&texCoordStream) {
        mTexCoordStream = std::forward<T>(texCoordStream);
    }
    template <typename T>
    void SetIndices(T &&indices) {
        mIndices = std::forward<T>(indices);
    }

    Ref<VertexDataStream<3> > PositionStream() {
        return mPositionStream;
    }
    const Ref<VertexDataStream<3> > PositionStream() const {
        return mPositionStream;
    }

    Ref<VertexDataStream<3> > NormalStream() {
        return mNormalStream;
    }
    const Ref<VertexDataStream<3> > NormalStream() const {
        return mNormalStream;
    }

    Ref<VertexDataStream<2> > TexCoordStream() {
        return mTexCoordStream;
    }
    const Ref<VertexDataStream<2> > TexCoordStream() const {
        return mTexCoordStream;
    }

    Ref<std::vector<GLuint> > Indices() {
        return mIndices;
    }
    const Ref<std::vector<GLuint> > Indices() const {
        return mIndices;
    }

    // TODO: Material indices, etc. Or maybe use submesh?

private:
    Ref<VertexDataStream<3> > mPositionStream;
    Ref<VertexDataStream<3> > mNormalStream;
    Ref<VertexDataStream<2> > mTexCoordStream;

    Ref<std::vector<GLuint> > mIndices;
};
