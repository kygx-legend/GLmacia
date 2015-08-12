{
  'variables': {
    'macia_sources': [
      'buffer.h',
      'buffer.cc',
      'shader.h',
      'shader.cc',
      'program.h',
      'program.cc',
      'sampler.h',
      'sampler.cc',
      'texture.h',
      'texture.cc',
      'fw.h',
      'fw.cc',
      'ut.h',
      'ut.cc',
    ],
    'depended_libraries': [
      '<!@(pkg-config --static --libs glfw3)',
      '<!@(pkg-config --static --libs glew)',
      '-lSOIL',
      '-lglut',
     ],
  },
  'targets': [
    {
      'target_name': 'macia',
      'type': 'static_library',
      'sources': [
        '<@(macia_sources)',
      ],
      'include_dirs': [
        'base',
      ],
      'link_settings': {
        'libraries': [
          '<@(depended_libraries)',
        ],
      },
    },
  ],
}
