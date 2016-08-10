cmake_minimum_required(VERSION 2.8.11)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(jubeon)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src/)
file(GLOB_RECURSE jubeon_cpp_files src/*.cpp)
file(GLOB_RECURSE jubeon_header_files src/*.hpp)
set(EXECUTABLE_NAME "jubeon")
add_executable(${EXECUTABLE_NAME} ${jubeon_cpp_files} ${jubeon_header_files})

source_group("Jmemo2" REGULAR_EXPRESSION "src/Jmemo2/(.*).(cpp|hpp)")
source_group("Input" REGULAR_EXPRESSION "src/Input/(.*).(cpp|hpp)")
source_group("Theme" REGULAR_EXPRESSION "src/Theme/(.*).(cpp|hpp)")
source_group("Storages" REGULAR_EXPRESSION "src/Storages/(.*).(cpp|hpp)")
source_group("Models" REGULAR_EXPRESSION "src/Models/(.*).(cpp|hpp)")
source_group("Graphics" REGULAR_EXPRESSION "src/Graphics/(.*).(cpp|hpp)")
source_group("Graphics\\Layer" REGULAR_EXPRESSION "src/Graphics/Layer/(.*).(cpp|hpp)")
source_group("Game" REGULAR_EXPRESSION "src/Game/(.*).(cpp|hpp)")
source_group("Game\\Layers" REGULAR_EXPRESSION "src/Game/Layers/(.*).(cpp|hpp)")
source_group("Game\\Scenes" REGULAR_EXPRESSION "src/Game/Scenes/(.*).(cpp|hpp)")
source_group("Systems" REGULAR_EXPRESSION "src/Systems/(.*).(cpp|hpp)")
source_group("Main" FILES src/main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(SFML_ROOT "${CMAKE_SOURCE_DIR}/lib/SFML")
set(THOR_ROOT "${CMAKE_SOURCE_DIR}/lib/Thor")

# add sfml
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

file(GLOB sfml_dlls ${CMAKE_SOURCE_DIR}/lib/SFML/bin/*.dll)
foreach(dll ${sfml_dlls})
    configure_file(${dll} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

file(COPY ${CMAKE_SOURCE_DIR}/media/ DESTINATION ${CMAKE_BINARY_DIR}/media/)
file(COPY ${CMAKE_SOURCE_DIR}/musics/ DESTINATION ${CMAKE_BINARY_DIR}/musics/)

# add thor
find_package(Thor 2 REQUIRED)
if(THOR_FOUND)
    include_directories(${THOR_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${THOR_LIBRARY})
endif()
