{
  'targets': [
    {
      'target_name': 'download_cef',
      'type': 'none',
      'hard_dependency': 1,
      'actions': [
        {
          'action_name': 'download_and_unpack',
          'inputs': [],
          'outputs': [
            './cefclient-0.0.2.tar.gz',
            '../bin/cefclient/cefclient.exe'
          ],
          'action': ['python',
                     './download_and_extract.py',
                     'https://github.com/downloads/mapbox/cefclient/cefclient-0.0.2.tar.gz',
                     './cefclient-0.0.2.tar.gz',
                     '../bin/'
                    ]
        }
      ]
    }
  ]
}
