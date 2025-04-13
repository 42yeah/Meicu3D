#+--------------------------------------------------------------------------------
#    meson.build - Airy Engine build script - Script de construction pour Airy
#                  Copyleft 2025 42yeah

spdlog = dependency('spdlog', required: true)
glfw3 = dependency('glfw3', required: true)
glm = dependency('glm', required: true)

airy = library(
    'airy',
    [
        'AiryGlobalContext.cpp',
        'AiryEngine.cpp',
        'AiryMeshRenderer.cpp',
        'Data/AiryShader.cpp',
        'Data/AiryProgram.cpp',
        'Data/AiryMesh.cpp',
        'Data/AiryMaterial.cpp',
        'Data/AiryMaterialPass.cpp',
        'External/glad/glad.c'
    ],
    dependencies: [spdlog, glfw3, glm]
)

subdir('Assets')
