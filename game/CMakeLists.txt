cmake_minimum_required( VERSION 3.10 )
project(game)

link_directories(BEFORE 
    "deps/SDL2" 
    "deps/glm/" 
)

#SET(CMAKE_CXX_FLAGS "-O3")

# extra stuff for ycm to function
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()


# Add libraries
set(GLM_TEST_ENABLE FALSE CACHE BOOL "" FORCE)
add_subdirectory(deps/glm)


add_executable(game
    src/main.cpp
    src/Point2D.cpp
    src/Shape.cpp
    src/Rectangle.cpp
    src/FilledRectangle.cpp
    src/Triangle.cpp
    src/Circle.cpp
    src/Shape3D.cpp
    src/ModelShape.cpp
    src/ParticleShape.cpp
    src/GameObject.cpp
    src/SpaceShip.cpp
    src/Asteroid.cpp
    src/LazerShot.cpp
    src/ParticleSystem.cpp
    src/Game.cpp
    src/autogen/generated_models.cpp
)



SET(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/game")
SET(CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}/game")
message(${CMAKE_SOURCE_DIR})

if(WIN32)
    include_directories(BEFORE "deps/SDL2/win_include/")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES)
    configure_file("deps/SDL2/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll" COPYONLY)
    target_link_libraries(game glm ${CMAKE_SOURCE_DIR}/deps/SDL2/SDL2.lib ${CMAKE_SOURCE_DIR}/deps/SDL2/SDL2main.lib )
else()
    set(CMAKE_CXX_FLAGS "-g")
    find_library(SDL2 SDL2-2.0 "${CMAKE_SOURCE_DIR}/deps/SDL2" NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
    include_directories("deps/SDL2/unix_include")
    target_link_libraries(game dl pthread sndio glm "${CMAKE_SOURCE_DIR}/deps/SDL2/libSDL2-2.0.so")
endif()
