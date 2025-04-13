//+-------------------------------------------------------------------------------
//    AiryTransform.hpp - Position, rotation & scaling - Position
//                      - Position, rotation & mise a l'echelle
//                        Copyleft 2025 42yeah

#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

/* We only allow transforms to be valid transforms - they are always first scaled,
   then rotated, and lastly translated (in SRT order)
*/
struct Transform {
    glm::vec3 scale;
    glm::mat3 rotate;
    glm::vec3 translate;

public:
    Transform() : scale(1.0f), rotate(1.0f), translate(0.0f) {}

    // Get the transform matrix, or the Local -> World matrix
    glm::mat4 Matrix() const {
        glm::mat4 trs = glm::mat4(rotate) * glm::scale(glm::mat4(1.0f), scale);
        trs[3] = glm::vec4(translate, 1.0f);
        return trs;
    }

    // Get the inverse transform matrix, or World -> Local matrix
    glm::mat4 Inv() const {
        glm::mat4 transInv = glm::translate(glm::mat4(1.0f), -translate);
        glm::mat4 rotInv = glm::mat4(glm::transpose(rotate));
        glm::mat4 scaleInv = glm::scale(glm::mat4(1.0f), 1.0f / scale);
        return scaleInv * rotInv * transInv;
    }
};
