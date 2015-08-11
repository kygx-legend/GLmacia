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
        '<(current_dir)/app/app.gyp:app',
      ],
    },
  ],
}
