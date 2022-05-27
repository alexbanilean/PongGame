cmake_minimum_required(VERSION 3.21)
project(PongGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PongGame src/main.cpp headers/highscoretable.h src/game.cpp headers/game.h src/gamescreen.cpp headers/gamescreen.h src/player.cpp headers/player.h src/blade.cpp headers/blade.h src/circle.cpp headers/circle.h src/update.cpp src/wall.cpp headers/wall.h src/highscoretable.cpp)

include_directories(headers d:/SFML/include)

set(SFML_ROOT d:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(PongGame ${SFML_LIBRARIES} ${SFML_DEPENDECIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../BIN/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

