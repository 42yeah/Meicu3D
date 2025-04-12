//+-------------------------------------------------------------------------------
//    AiryMeshRenderer.cpp - Implementation - Implementation
//                           Copyleft 2025 42yeah

#include "AiryMeshRenderer.hpp"
#include "AiryObject.hpp"
#include "AiryVertexDataStream.hpp"
#include <spdlog/spdlog.h>

void MeshRenderer::Finalize() {
    mReady = false;
    mIndexedDraw = false;

    if (mVAO != GL_NONE)
        glDeleteVertexArrays(1, &mVAO);

    if (mVBO != GL_NONE)
        glDeleteBuffers(1, &mVBO);

    if (mEBO != GL_NONE)
        glDeleteBuffers(1, &mEBO);

    mMesh = nullptr;
    mMaterial = nullptr;
}

bool MeshRenderer::Prepare() {
    if (!mMesh)
        return false;

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    size_t fullSize = 0;
    const Ref<VertexDataStream<3> > &positions = mMesh->PositionStream();
    const Ref<VertexDataStream<3> > &normals = mMesh->NormalStream();
    const Ref<VertexDataStream<2> > &texCoords = mMesh->TexCoordStream();

    if (positions)
        fullSize += positions->Size();
    if (normals)
        fullSize += normals->Size();
    if (texCoords)
        fullSize += texCoords->Size();

    glBufferData(
        GL_ARRAY_BUFFER, fullSize, nullptr, GL_STATIC_DRAW);

    size_t offset = 0;
    if (positions) {
        glBufferSubData(GL_ARRAY_BUFFER, offset, positions->Size(), positions->Data());
        offset += positions->Size();
    }
    if (normals) {
        glBufferSubData(GL_ARRAY_BUFFER, offset, normals->Size(), normals->Data());
        offset += normals->Size();
    }
    if (texCoords) {
        glBufferSubData(GL_ARRAY_BUFFER, offset, texCoords->Size(), texCoords->Data());
        offset += texCoords->Size();
    }

    offset = 0;
    if (positions) {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
        offset += positions->Size();
    }
    if (normals) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void *>(offset));
        offset += normals->Size();
    }
    if (texCoords) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void *>(offset));
        offset += texCoords->Size();
    }

    const Ref<std::vector<GLuint> > &indices = mMesh->Indices();

    if (indices) {
        glGenBuffers(1, &mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices->size(), indices->data(), GL_STATIC_DRAW);

        mIndexedDraw = true;
    }

    mReady = true;
    return true;
}

bool MeshRenderer::Render(const char *szPassName) {
    if (!mReady) {
        bool ok = Prepare();
        if (!ok || !mReady)
            return false;
    }

    if (!mMaterial || !szPassName) return false;

    const Ref<MaterialPass> &pass = mMaterial->GetPass(szPassName);
    if (!pass) {
        spdlog::warn("No such material pass: {}", szPassName);
        return false;
    }

    pass->SetupRenderer();

    glBindVertexArray(mVAO);

    if (!mMesh) return false;

    if (mIndexedDraw) {
        if (!mMesh->Indices()) return false;
        glDrawElements(GL_TRIANGLES, mMesh->Indices()->size(), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, mMesh->NumVertices());
    }

    return true;
}
