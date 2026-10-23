#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ridgelib::ridgelib" for configuration ""
set_property(TARGET ridgelib::ridgelib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ridgelib::ridgelib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libridgelib.a"
  )

list(APPEND _cmake_import_check_targets ridgelib::ridgelib )
list(APPEND _cmake_import_check_files_for_ridgelib::ridgelib "${_IMPORT_PREFIX}/lib/libridgelib.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
