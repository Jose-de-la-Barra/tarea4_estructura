cmake_minimum_required(VERSION "3.21.1")

project("Tarea 4 Estructura de datos")

add_executable("tarea4" "main.c")

install(TARGETS "tarea4" DESTINATION bin)
install(FILES "main.c" DESTINATION src)
