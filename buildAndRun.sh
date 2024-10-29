clear

g++ -c -I./include src/Functions.cpp      -o build/Functions.o
g++ -c -I./include src/GameController.cpp -o build/GameController.o
g++ -c -I./include main.cpp               -o build/main.o

g++ build/Functions.o build/GameController.o build/main.o -o build/main.exe

./build/main.exe