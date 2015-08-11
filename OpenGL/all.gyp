{
  'variables': {
    'project_name': 'GLmacia',
    'version': '1.0.0',
    'current_dir': '<(DEPTH)',
  },
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
        'basic_sample',
      ],
      'cflags': [
        '-g',
      ],
      'cflags_cc': [
        '-std=gnu++11',
      ],
    },
    {
      'target_name': 'basic_sample',
      'type': 'executable',
      'dependencies': [
        '<(current_dir)/src/macia.gyp:macia',
      ],
      'sources': [
        '<(current_dir)/examples/basic_sample.cc',
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
        '<(current_dir)/examples/basic_render.cc',
      ],
      'include_dirs': [
        '<(current_dir)',
      ],
      'cflags': [
        '-g',
      ],
    },
    {
      'target_name': 'simple_texture',
      'type': 'executable',
      'dependencies': [
        '<(current_dir)/src/macia.gyp:macia',
      ],
      'sources': [
        '<(current_dir)/examples/simple_texture.cc',
      ],
      'include_dirs': [
        '<(current_dir)',
      ],
      'cflags': [
        '-g',
      ],
    },
  ],
}
