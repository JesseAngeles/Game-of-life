clear

g++ -c -I./include src/Functions.cpp      -o build/Functions.o
g++ -c -I./include src/GameController.cpp -o build/GameController.o
g++ -c -I./include src/Grapher.cpp        -o build/Grapher.o
g++ -c -I./include main.cpp               -o build/main.o

g++ build/Functions.o build/GameController.o build/Grapher.o build/main.o -o build/main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

./build/main.exe