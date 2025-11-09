cmake_minimum_required(VERSION 4.0)
project(Projet_transversal_C_BD C)

set(CMAKE_C_STANDARD 11)

add_executable(V1 V1.c)

add_executable(V2 V2.c)

add_executable(main main.c
        utils.c
        utils.h
        fichiers.c
        fichiers.h
        emprunts.c
        emprunts.h
        utilisateurs.c
        utilisateurs.h
        livres.c
        livres.h
        structures.h)

add_executable(utils utils.c
        utils.h)

add_executable(fichiers fichiers.c
        fichiers.h)

add_executable(emprumts emprunts.c
        emprunts.h)

add_executable(utilisateurs utilisateurs.c
        utilisateurs.h)

add_executable(livres livres.c
        livres.h)
