#+--------------------------------------------------------------------------------
#    meson.build - Entry build script - Script d'entree pour la construction
#                  Copyleft 2025 42yeah

project('Meicu3D', ['c', 'cpp'], meson_version: '>= 1.1.0', version: '0.0.0')

spdlog = dependency('spdlog', required: true)
glfw3 = dependency('glfw3', required: true)

executable(
    'meicu3d',
    [
        'main.cpp',
        'Airy/AiryGlobalContext.cpp',
        'Airy/AiryEngine.cpp',
        'Airy/External/glad/glad.c'
    ],
    dependencies: [spdlog, glfw3]
)
