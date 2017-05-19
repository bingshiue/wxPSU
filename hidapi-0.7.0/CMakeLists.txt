message ("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})

# Glob HIDAPI Header Files
file(GLOB HIDAPI_HEADER hidapi/hidapi.h)

# Collect HIDAPI Sources Files
if(WIN32)
message("***WIN32***: " ${WIN32})
file(GLOB HIDAPI_SOURCE windows/*.c)
message("***HIDAPI_SOURCE***: " ${HIDAPI_SOURCE})

elseif(UNIX AND NOT APPLE)
message("***UNIX***: " ${UNIX})
file(GLOB HIDAPI_SOURCE linux/hid-libusb.c)
message("***HIDAPI_SOURCE***: " ${HIDAPI_SOURCE})
endif()

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
#source_group("" FILES ${MATH_SOURCES})
#source_group("hidapi" FILES ${HIDAPI_SOURCE})
#source_group("include" FILES ${HIDAPI_HEADER})

include_directories(/usr/include/libusb-1.0/)
include_directories(hidapi/)

add_library(hidapi SHARED ${HIDAPI_SOURCE} ${HIDAPI_HEADER})

# Creates folder "libraries" and adds target project (hidapi.vcproj)
set_property(TARGET hidapi PROPERTY FOLDER "libraries")

# Properties->General->Output Directory
message("***PROJECT_BINARY_DIR***: " ${PROJECT_BINARY_DIR})
set_target_properties(hidapi PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

					  
# Add Preprocessor
#target_compile_options(hidapi PRIVATE "/D_CRT_SECURE_NO_DEPRECATE")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_DEPRECATE")
add_definitions("/DHIDAPI_EXPORTS")
add_definitions("/D_CRT_SECURE_NO_DEPRECATE")
#set_target_properties(hidapi PROPERTIES
                      #COMPILE_DEFINITIONS "-DHIDAPI_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
#target_compile_options(hidapi)
#message("***CMAKE_CXX_FLAGS***: " ${CMAKE_CXX_FLAGS})

if(WIN32)				  
target_link_libraries(hidapi setupapi)
endif()

# Adds logic to INSTALL.vcproj to copy math.dll to the destination directory
#install (TARGETS math
#         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
#         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)
