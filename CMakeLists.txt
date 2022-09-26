#Require a minimum version of cmake.
cmake_minimum_required(VERSION 3.15)

#Set the name of the project.
project(Project2D
    VERSION 1.0
    DESCRIPTION "2D rendering using modern OpenGL"
    LANGUAGES CXX)
  
find_package( OpenGL REQUIRED )

#Adds a subdirectory to the build.
add_subdirectory(libs/glfw)
add_subdirectory(libs/GLAD)
add_subdirectory(libs/STB)

# File manipulation command. (Automatically checks and finds all source files at build time)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

# Add an executable to the project using the specified source files.
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add expected compiler features to a target.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Add include directories to a target.
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Specify libraries or flags to use when linking a given target. (Linking OpenGL, glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw GLAD STB)

# Copy assets folder to source to the build directory:
FILE(COPY ${PROJECT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Disable console window for windows
#target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
