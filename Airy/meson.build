#+--------------------------------------------------------------------------------
#    meson.build - Airy Engine build script - Script de construction pour Airy
#                  Copyleft 2025 42yeah

spdlog = dependency('spdlog', required: true)
glfw3 = dependency('glfw3', required: true)

airy = library(
    'airy',
    [
        'AiryGlobalContext.cpp',
        'AiryEngine.cpp',
        'AiryShader.cpp',
        'AiryProgram.cpp',
        'External/glad/glad.c'
    ],
    dependencies: [spdlog, glfw3]
)

subdir('Assets')
