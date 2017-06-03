LIBS=-lGL -lglfw -lGLEW
FILES=lodepng.cpp main.cpp shaderprogram.cpp game.cpp game_object.cpp ball_object.cpp model.cpp

main: $(FILES)
	g++ -o main.exe $(FILES)  $(LIBS) -I.
