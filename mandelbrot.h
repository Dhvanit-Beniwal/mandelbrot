int mandelbrot(double x_0, double y_0, int max_iter){
    double x2 = 0, y2 = 0, s = 0;
    int iter = 0;
    while(x2+y2 <= 4 && iter < max_iter){
        double x = x2 - y2 + x_0;
        double y = s - x2 - y2 + y_0;
        x2 = x*x;
        y2 = y*y;
        s = (x+y)*(x+y);
        iter ++;
    }
    return iter;
}