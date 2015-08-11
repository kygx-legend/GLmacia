{
  'variables': {
    'project_name': 'examples',
    'current_dir': '<(DEPTH)',
  },
  'targets': [
    {
      'target_name': 'basic_sample',
      'type': 'executable',
      'dependencies': [
        '<(current_dir)/src/macia.gyp:macia',
      ],
      'sources': [
        'basic_sample.cc',
      ],
      'include_dirs': [
        '<(current_dir)',
      ],
    },
    {
      'target_name': 'basic_render',
      'type': 'executable',
      'dependencies': [
        '<(current_dir)/src/macia.gyp:macia',
      ],
      'sources': [
        'basic_render.cc',
      ],
      'include_dirs': [
        '<(current_dir)',
      ],
    },
    {
      'target_name': 'simple_texture',
      'type': 'executable',
      'dependencies': [
        '<(current_dir)/src/macia.gyp:macia',
      ],
      'sources': [
        'simple_texture.cc',
      ],
      'include_dirs': [
        '<(current_dir)',
      ],
    },
  ],
}
