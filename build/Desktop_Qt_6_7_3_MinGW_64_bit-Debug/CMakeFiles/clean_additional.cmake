# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\piton_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\piton_autogen.dir\\ParseCache.txt"
  "piton_autogen"
  )
endif()
