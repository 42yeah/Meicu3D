//+-------------------------------------------------------------------------------
//    AiryVertexDataStream.hpp - Vertices, normals, etc. - Sommets, normaux, etc.
//                               Copyleft 2025 42yeah

#pragma once

#include "AiryObject.hpp"

#include <cstring>
#include <glm/glm.hpp>

#include <spdlog/spdlog.h>
#include <vector>

template <size_t N>
class VertexDataStream : public Object {
public:
    VertexDataStream() : mData() {}
    ~VertexDataStream() override {
        Finalize();
    }

    using vecNf = glm::vec<N, float>;

public:
    void Init(const float *pData, size_t nD, size_t numVertices) {
        mData.resize(numVertices);
        if (nD == N) {
            memcpy(&mData[0], pData, sizeof(vecNf) * numVertices);
            return;
        }

        for (size_t i = 0; i < numVertices; ++i) {
            size_t idx = i * nD;
            vecNf vertex = vecNf(1.0f);
            for (size_t d = 0; d < nD; ++d) {
                vertex[d] = pData[idx + d];
            }
            mData[i] = vertex;
        }
    }

    void Finalize() override {
        mData.clear();
    }

    size_t NumVertices() const {
        return mData.size();
    }

    size_t Size() const {
        return mData.size() * sizeof(vecNf);
    }

    const void *Data() const {
        return mData.data();
    }

private:
    std::vector<vecNf> mData;
};
