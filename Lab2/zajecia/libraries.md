We have main file main.c and library stringlibrary.c

# Static libraries:

$ gcc -c stringlibrary.c$                     ##-c flag compiles file without linking
$ arc rcs libstringlibrary.a stringlibrary.o$ ## creating library .a
$ gcc -c main.c$                              ##main file compilation with -c flag
$ gcc main.o libstringlibrary.a -o main$      ##linking main.o with library (*)
$ ./main $

(*) Also we can do this:
gcc main.o -l stringlibrary -L. -o main # -l flag deletes lib prefix from libraryname and we dont add .a extension; -L flag tells compiler where it should search for library . is a current directory

# Shared libraries

$ $

