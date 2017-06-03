LIBS=-lGL -lglfw -lGLEW
FILES=lodepng.cpp  main.cpp  game_object.cpp  shaderprogram.cpp

main: $(FILES)
	g++ -o main.exe $(FILES)  $(LIBS) -I.
