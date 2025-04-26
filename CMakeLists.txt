cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 17)

include_directories("C:\\Users\\Simon\\Downloads\\SDL3-3.2.10\\include" "C:\\Users\\Simon\\Downloads\\SDL3_image-3.2.4\\include")
link_directories("C:\\Users\\Simon\\Downloads\\SDL3-3.2.10\\lib\\x64" "C:\\Users\\Simon\\Downloads\\SDL3_image-3.2.4\\lib\\x64")

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
        layer.h "utils.h" "character.h" "character.c" "unit.h" "unit.c" "animated-sprite.h" "animated-sprite.c" "keycodes.h" "point.h" "toml.h" "toml.c")

target_link_libraries(untitled PRIVATE SDL3 SDL3_image)
