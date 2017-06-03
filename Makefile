LIBS=-lGL -lglfw -lGLEW
FILES=lodepng.cpp main.cpp shaderprogram.cpp game.cpp game_object.cpp ball_object.cpp model.cpp renderer.cpp cube.cpp

main: $(FILES)
	g++ -std=c++11 -o main.exe $(FILES)  $(LIBS) -I.
