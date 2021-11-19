# mandelbrot
Implements an interactive [Mandelbrot zoom](https://en.wikipedia.org/wiki/Mandelbrot_set#Image_gallery_of_a_zoom_sequence)

Uses the optimized but naive [escape time algorithm](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Optimized_escape_time_algorithms) to color the points

Made with [SFML 2.5](https://www.sfml-dev.org/tutorials/2.5). Install SFML with:
```
sudo apt-get install libsfml-dev
```
[Commands for compiling](https://www.sfml-dev.org/tutorials/2.5/start-linux.php) are in the makefile. Although note that this will NOT [link it statically](https://www.sfml-dev.org/faq.php#build-link-static)

Build and run using: (respectively)
```
make exe
./exe
```
(in the repo directory)
or the equivalent
```
make run
```
