# Print Current Source & Binary DIR
message ("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})

# Properties->C/C++->General->Additional Include Directories
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/libGIS")

# GLOB libGIS Source
file(GLOB TEST_LIBGIS_SOURCE *.c)
message("***TEST_LIBGIS_SOURCE***: " ${TEST_LIBGIS_SOURCE})

# Set Properties->General->Configuration Type to Application(.exe)
# Creates testGIS.exe with the listed sources
# Adds sources to the Solution Explorer
add_executable (testGIS ${TEST_LIBGIS_SOURCE} )

if(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_DEPRECATE")
endif()

# Creates a folder "executables" and adds target
# project (testGIS.vcproj) under it
set_property(TARGET testGIS PROPERTY FOLDER "executables")

# Properties->General->Output Directory
message("***PROJECT_BINARY_DIR***: " ${PROJECT_BINARY_DIR})
set_target_properties(testGIS PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

