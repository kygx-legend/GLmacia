{
  'variables': {
    'project_name': 'app',
  },
  'targets': [
    {
      'target_name': 'app',
      'type': 'none',
      'dependencies': [
        'examples/examples.gyp:basic_sample',
        'examples/examples.gyp:basic_render',
        'examples/examples.gyp:simple_texture',
      ],
      'cflags': [
        '-g',
      ],
      'cflags_cc': [
        '-std=gnu++11',
      ],
    },
  ],
}
