#+--------------------------------------------------------------------------------
#    meson.build - Shaders - Nuanceurs
#                  Copyleft 2025 42yeah

shader_sources = [
    'Triangle.fs',
    'Triangle.vs'
]

fs = import('fs')

foreach shader : shader_sources
    fs.copyfile(shader)
endforeach
