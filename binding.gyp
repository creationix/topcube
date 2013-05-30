{
  'targets': [
    {
      'target_name': 'topcube',
      'type': 'executable',
      'sources': [
        'src/topcube.cpp'
      ],
      'conditions': [
        ['OS=="linux"', {
          'cflags_cc' : [
              '<!@(pkg-config gtk+-2.0 --cflags)',
              '<!@(pkg-config glib-2.0 --cflags)',
              '<!@(pkg-config webkit-1.0 --cflags)'
          ],
          'libraries':[
              '<!@(pkg-config gtk+-2.0 --libs)',
              '<!@(pkg-config glib-2.0 --libs)',
              '<!@(pkg-config webkit-1.0 --libs)'
          ]
        }]
      ],
    },
    {
      'target_name': 'action_after_build',
      'type': 'none',
      'dependencies': [ 'topcube' ],
      'actions': [
        {
          'action_name': 'move_topcube',
          'inputs': [
            '<@(PRODUCT_DIR)/topcube'
          ],
          'outputs': [
            'lib/topcube'
          ],
          'action': ['cp', '<@(PRODUCT_DIR)/topcube', 'lib/topcube']
        }
      ]
    }
  ]
}
