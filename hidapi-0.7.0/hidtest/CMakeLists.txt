message ("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})

# Properties->C/C++->General->Additional Include Directories
message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/hidapi-0.7.0/hidapi")

# Set Properties->General->Configuration Type to Application(.exe)
# Creates hidtest.exe with the listed sources (hidtest.cpp)
# Adds sources to the Solution Explorer
add_executable (hidtest hidtest.cpp ${PROJECT_SOURCE_DIR}/hidapi-0.7.0/hidapi/hidapi.h)

if(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_DEPRECATE")
endif()

# Properties->Linker->Input->Additional Dependencies
target_link_libraries (hidtest hidapi)

if(UNIX)
target_link_libraries (hidtest pthread usb-1.0)
endif()

# Creates a folder "executables" and adds target 
# project (hidapi.vcproj) under it
set_property(TARGET hidtest PROPERTY FOLDER "executables")

# Properties->General->Output Directory
message("***PROJECT_BINARY_DIR***: " ${PROJECT_BINARY_DIR})
set_target_properties(hidtest PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
					  
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
#install (TARGETS app
#         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)



