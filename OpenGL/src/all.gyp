{
  'variables': {
    'project_name': 'GLmacia',
    'version': '1.0.0',
    'gl_link_libraries': [
       '-lGL',
       '-LGLES3',
       '-lglut',
     ],
  },
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
        'clear_render',
        'simple_color',
        'simple_texture',
      ],
      'cflags': [
        '-g',
      ],
      'cflags_cc': [
        '-std=gnu++11',
      ],
    },
    {
      'target_name': 'clear_render',
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/src/macia/macia.gyp:macia',
      ],
      'sources': [
        '<(DEPTH)/src/examples/clear_render.cc',
      ],
      'include_dirs': [
        '<(DEPTH)/src',
      ],
      'link_settings': {
        'libraries': [
          '<@(gl_link_libraries)',
        ],
      },
      'cflags': [
        '-g',
      ],
    },
    {
      'target_name': 'simple_color',
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/src/macia/macia.gyp:macia',
      ],
      'sources': [
        '<(DEPTH)/src/examples/simple_color.cc',
      ],
      'include_dirs': [
        '<(DEPTH)/src',
      ],
      'link_settings': {
        'libraries': [
          '<@(gl_link_libraries)',
        ],
      },
      'cflags': [
        '-g',
      ],
    },
    {
      'target_name': 'simple_texture',
      'type': 'executable',
      'dependencies': [
        '<(DEPTH)/src/macia/macia.gyp:macia',
      ],
      'sources': [
        '<(DEPTH)/src/examples/simple_texture.cc',
      ],
      'include_dirs': [
        '<(DEPTH)/src',
      ],
      'link_settings': {
        'libraries': [
          '<@(gl_link_libraries)',
        ],
      },
      'cflags': [
        '-g',
      ],
    },
  ],
}
