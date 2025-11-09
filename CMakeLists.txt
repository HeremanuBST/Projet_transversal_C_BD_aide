cmake_minimum_required(VERSION 4.0)
project(Projet_transversal_C_BD C)

set(CMAKE_C_STANDARD 11)


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