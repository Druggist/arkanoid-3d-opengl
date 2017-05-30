LIBS=-lGL -lglfw -lGLEW
FILES=lodepng.cpp  main.cpp  model.cpp  shaderprogram.cpp

main: $(FILES)
	g++ -o main.exe $(FILES)  $(LIBS) -I.
