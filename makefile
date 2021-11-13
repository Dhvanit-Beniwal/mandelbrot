.SILENT:
exe : main.cpp mandelbrot.h color_palette.h render.h
	g++ -c main.cpp -o main.o
	g++ main.o -o exe -lsfml-graphics -lsfml-window -lsfml-system
run : exe
	./exe
clean :
	rm main.o exe