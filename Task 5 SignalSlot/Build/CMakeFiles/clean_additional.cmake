# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SignalSlot_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SignalSlot_autogen.dir\\ParseCache.txt"
  "SignalSlot_autogen"
  )
endif()
