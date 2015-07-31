{
  'variables': {
    'macia_sources': [
      'structure.h',
      'util.h',
      'shader_manager.h',
      'shader_manager.cc',
      'program_manager.h',
      'program_manager.cc',
      'buffer_manager.h',
      'buffer_manager.cc',
      'texture_manager.h',
      'texture_manager.cc',
      'render_manager.cc',
      'render_manager.h',
    ],
  },
  'targets': [
    {
      'target_name': 'macia',
      'type': 'static_library',
      'sources': [
        '<@(macia_sources)',
      ],
      'link_settings': {
        'libraries': [
          '-ljpeg',
        ],
      },
      'cflags': [
        '-g',
      ],
    },
  ],
}
