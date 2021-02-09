{
  "targets": [
    {
      "target_name": "zynk",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ 
        "addon.cc", 
        "GetProcessIdEx.cpp", 
        "ReadProcessMemoryEx.cpp", 
        "WriteProcessMemoryEx.cpp",
        "SetSeDebugPrivilege.cpp" 
        ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
