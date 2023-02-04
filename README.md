## CS 298 Course Project:
# Mandelbrot zoom implementation
Implements an interactive [Mandelbrot zoom](https://en.wikipedia.org/wiki/Mandelbrot_set#Image_gallery_of_a_zoom_sequence)

Uses the optimized but naive [escape time algorithm](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Optimized_escape_time_algorithms) to color the points

Made with [SFML 2.5](https://www.sfml-dev.org/tutorials/2.5). Install SFML with:
```
sudo apt-get install libsfml-dev
```
Commands for installation and [compiling](https://www.sfml-dev.org/tutorials/2.5/start-linux.php) are in the makefile too. Although note that this compilation will NOT [link it statically](https://www.sfml-dev.org/faq.php#build-link-static) [(although can't do it on linux anyways)](https://en.sfml-dev.org/forums/index.php?topic=3003.msg19631#msg19631)

To install SFML, run
```
make install
```
To build the executable,
```
make exe
```
run with
```
./exe
```
or equivalently, build and run with:
```
make run
```
app.exe is the compiled and statically linked execuable (built on win10 but likely works on win11 too) so that it will run on its own without any installation required (not that you should trust unknown executables though), it's present for demonstration purposes since setting up SFML on windows is not as straightforward sometimes. Might even have to build SFML from source if there is a version mismatch between (say) the MinGW installation used to build the libraries provided as installation and the MinGW installation on your system. But atleast we get the choice to link statically or dynamically on windows.
