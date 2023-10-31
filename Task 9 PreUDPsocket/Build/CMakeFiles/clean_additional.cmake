# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PreUDPsocket_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PreUDPsocket_autogen.dir\\ParseCache.txt"
  "PreUDPsocket_autogen"
  )
endif()
