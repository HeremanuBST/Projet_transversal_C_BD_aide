cmake_minimum_required(VERSION 4.0)
project(Bibilotheque_numerique C)

set(CMAKE_C_STANDARD 11)

# --- Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

# --- Targets
add_executable(raygui_ing3 main.c raygui.h)
target_link_libraries(raygui_ing3 PRIVATE raylib)

add_executable(Bibilotheque_numerique main.c
        livre.c
        livre.h
        structure.c
        structure.h
        emprunt.c
        emprunt.h
        exemplaire.c
        exemplaire.h
        utilisateur.c
        utilisateur.h
        fichier.c
        fichier.h
        utils.c
        utils.h
        raygui.c
        raygui.h
        raylib.c
        raylib.h
)



