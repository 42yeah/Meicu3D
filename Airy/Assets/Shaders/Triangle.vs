//+-------------------------------------------------------------------------------
//    Triangle.vs - Test Shader for Airy - Nuanceur de test pour Airy
//                  Copyleft 2025 42yeah

#version 450 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
