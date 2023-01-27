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
