#+--------------------------------------------------------------------------------
#    meson.build - Shaders, images, etc. - Nuanceurs, images, etc.
#                  Copyleft 2025 42yeah

subdir('Shaders')

shader_declarations = ''
foreach shader : shader_sources
    symbol_name = shader.replace('.', '_')
    shader_declarations += f'inline const char *@symbol_name@_Path() { return "Airy/Assets/Shaders/@shader@"; }\n'
endforeach

configure_file(
    input: 'AiryAssets.h.in',
    output: 'AiryAssets.h',
    configuration: {
        'shaders': shader_declarations
    }
)
