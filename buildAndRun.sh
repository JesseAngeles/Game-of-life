clear

g++ -c -I./include src/Functions.cpp         -o build/Functions.o
g++ -c -I./include src/GameController.cpp    -o build/GameController.o
g++ -c -I./include src/gui/Grapher.cpp       -o build/Grapher.o
g++ -c -I./include src/gui/Frame.cpp         -o build/Frame.o
g++ -c -I./include src/gui/Button.cpp        -o build/Button.o
g++ -c -I./include src/gui/FrameBoard.cpp    -o build/FrameBoard.o
g++ -c -I./include src/gui/FrameButtons.cpp  -o build/FrameButtons.o
g++ -c -I./include src/gui/FrameGraphics.cpp -o build/FrameGraphics.o
g++ -c -I./include main.cpp                  -o build/main.o

g++ build/Functions.o build/GameController.o build/Grapher.o build/Frame.o build/Button.o build/FrameBoard.o build/FrameButtons.o build/FrameGraphics.o build/main.o -o build/main.exe -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

./build/main.exe