cmake_minimum_required( VERSION 3.10 )
#link_directories(BEFORE "deps" ".")

set( CMAKE_CXX_FLAGS "-g" )

# extra stuff for ycm to function
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

project(task1)
add_executable(task1
    task1.cpp
    DoublyLinkedList.cpp
)


#if(WIN32)
#    include_directories(BEFORE "deps" "deps/winin/include/")
#    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES)
#    configure_file("deps/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll" COPYONLY)
#    target_link_libraries(task1 ${CMAKE_SOURCE_DIR}/deps/SDL2.lib ${CMAKE_SOURCE_DIR}/deps/SDL2main.lib )
#    target_link_libraries(task2 ${CMAKE_SOURCE_DIR}/deps/SDL2.lib ${CMAKE_SOURCE_DIR}/deps/SDL2main.lib )
#else()
#    include_directories("deps" "deps/include")
#    target_link_libraries(task1 dl pthread sndio ${CMAKE_SOURCE_DIR}/deps/libSDL2-2.0.so)
#    target_link_libraries(task2 dl pthread sndio ${CMAKE_SOURCE_DIR}/deps/libSDL2-2.0.so)
#endif()
