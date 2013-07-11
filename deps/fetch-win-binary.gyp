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
            '../bin/cefclient/cefclient.exe'
          ],
          'action': ['python',
                     './download_and_extract.py',
                     '../bin/'
                    ]
        }
      ]
    }
  ]
}
