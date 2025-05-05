cmake_minimum_required(VERSION 3.20)

project(untitled C)

set(CMAKE_C_STANDARD 23)

include_directories("C:\\Users\\Simon\\Downloads\\CSFML\\include")
link_directories("C:\\Users\\Simon\\Downloads\\CSFML\\lib\\msvc")

add_executable(untitled main.c
        window.c
        window.h
        texture.c
        texture.h
        sprite.c
        sprite.h
        texture-manager.c
        texture-manager.h
        tileset.c
        tileset.h
        camera.c
        camera.h
        vector2.c
        vector2.h
        tilemap-manager.c
        tilemap-manager.h
        tilemap.c
        tilemap.h
        layer.c
        layer.h "utils.h" "character.h" "character.c" "unit.h" "unit.c" "animated-sprite.h" "animated-sprite.c" "keycodes.h" "point.h"   "color.h"
        unit-group.c
        unit-group.h
        xml.c
        xml.h "file.h" "file.c" "convert.h")

target_link_libraries(untitled PRIVATE csfml-window csfml-graphics csfml-system)
