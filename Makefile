All:
	g++ -I include/SDL2 -L lib -o main src/main.cpp src/chessPiece.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image