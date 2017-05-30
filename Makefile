LIBS=-lGL -lglfw -lGLEW
FILES=cube.cpp  lodepng.cpp  main_file.cpp  model.cpp  shaderprogram.cpp  teapot.cpp

main_file: $(FILES)
	g++ -o main_file $(FILES)  $(LIBS) -I.
