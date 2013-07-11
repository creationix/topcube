{
  'targets': [
    {
      'target_name': 'topcube',
      'type': 'executable',
      'conditions': [
        ['OS!="win"', {
          'sources': [
            'src/topcube.cpp'
          ],
        }],
        ['OS=="win"', {
          'dependencies': [ 'deps/fetch-win-binary.gyp:download_cef' ],
        }],
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
      ]
    },
    {
      'target_name': 'action_after_build',
      'type': 'none',
      'dependencies': [ 'topcube' ],
      'conditions': [
        ['OS!="win"', {
          'actions': [
            {
              'action_name': 'move_topcube',
              'inputs': [
                '<@(PRODUCT_DIR)/topcube'
              ],
              'outputs': [
                'bin/topcube'
              ],
              'action': ['cp', '<@(PRODUCT_DIR)/topcube', 'bin/topcube']
            }
          ]
        }]
      ]
    }
  ]
}
