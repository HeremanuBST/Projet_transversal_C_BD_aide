cmake_minimum_required(VERSION 4.0)
project(Projet_transversal_C_BD C)

set(CMAKE_C_STANDARD 11)


add_executable(main src/main.c
        src/utils.c
        include/utils.h
        src/fichiers.c
        include/fichiers.h
        src/emprunts.c
        include/emprunts.h
        src/utilisateurs.c
        include/utilisateurs.h
        src/livres.c
        include/livres.h
        include/structures.h)