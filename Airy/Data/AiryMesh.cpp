//+-------------------------------------------------------------------------------
//    AiryMesh.cpp - Implementation - Implementation
//                   Copyleft 2025 42yeah

#include "AiryMesh.hpp"

#include "../Pervasives/AiryObject.hpp"

#include <memory>

Ref<Mesh> Mesh::TriangleMesh() {
    const float data[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    Ref<VertexDataStream<3> > position = std::make_shared<VertexDataStream<3> >();
    position->Init(data, 3, 3);

    Ref<std::vector<GLuint> > indices = std::make_shared<std::vector<GLuint> >();
    indices->insert(indices->end(), {0, 1, 2});

    Ref<Mesh> mesh = std::make_shared<Mesh>();
    mesh->SetPositionStream(std::move(position));
    mesh->SetIndices(std::move(indices));

    return mesh;
}

void Mesh::Finalize() {
    if (mPositionStream)
        mPositionStream->Finalize();
    if (mNormalStream)
        mNormalStream->Finalize();
    if (mTexCoordStream)
        mTexCoordStream->Finalize();
    mPositionStream = nullptr;
    mNormalStream = nullptr;
    mTexCoordStream = nullptr;
}

size_t Mesh::NumVertices() {
    if (!mPositionStream) {
        return 0;
    }
    return mPositionStream->NumVertices();
}
