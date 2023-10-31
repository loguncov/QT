# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MainQtModules_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MainQtModules_autogen.dir/ParseCache.txt"
  "MainQtModules_autogen"
  )
endif()
