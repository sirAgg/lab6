cmake_minimum_required( VERSION 3.10 )
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


project(game)

add_executable(game
    main.cpp
    Point2D.cpp
    Shape.cpp
    Rectangle.cpp
    Triangle.cpp
    Circle.cpp
)



if(WIN32)
    include_directories(BEFORE "deps/SDL2/win_include/")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES)
    configure_file("deps/SDL2/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll" COPYONLY)
    target_link_libraries(game glm ${CMAKE_SOURCE_DIR}/deps/SDL2.lib ${CMAKE_SOURCE_DIR}/deps/SDL2main.lib )
else()
    include_directories("deps/SDL2/unix_include")
    target_link_libraries(game dl pthread sndio glm ${CMAKE_SOURCE_DIR}/deps/SDL2/libSDL2-2.0.so)
endif()
