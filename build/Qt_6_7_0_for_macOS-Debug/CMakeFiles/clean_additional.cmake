# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/HexBinCharEditor_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/HexBinCharEditor_autogen.dir/ParseCache.txt"
  "HexBinCharEditor_autogen"
  )
endif()
