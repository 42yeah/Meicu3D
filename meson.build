#+--------------------------------------------------------------------------------
#    meson.build - Entry build script - Script d'entree pour la construction
#                  Copyleft 2025 42yeah

project('Meicu3D', ['c', 'cpp'], meson_version: '>= 1.1.0', version: '0.0.0')

spdlog = dependency('spdlog', required: true)

subdir('Airy')
subdir('Tests')

executable(
    'meicu3d',
    [
        'main.cpp'
    ],
    link_with: [airy],
    dependencies: [spdlog]
)
