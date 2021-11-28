struct iterAndZ{
    int iter;
    double x2,y2,sumsq;
    iterAndZ(int i = 0, double x = 0, double y = 0, double s = 0){iter = i; x2 = x; y2 = y; sumsq = s;}
};

// mandelbrot() returns a number from 0 to max_iter that is the escape time of z_0 = 0 when c = (x_0, y_0) under the iteration z^2+c
// by default iteration starts at z_0 = 0, but can be changed by calling with extra parameters. Is used to prevent
// repetetive calculations when the same point is successively checked with higher and higher values of max_iter i.e
// in the implementation of mandelRender::enhance()

struct iterAndZ mandelbrot(double x_0, double y_0, int max_iter, double initX2 = 0, double initY2 = 0, double initSumsq = 0){
    
    //main cardioid check to reduce unnecessary computation
    if( (16*(x_0*x_0 + y_0*y_0) - 3)*(16*(x_0*x_0 + y_0*y_0) - 3) < 12 - 32*x_0 ){return iterAndZ(max_iter,initX2,initY2,initSumsq);}

    //main circle check to reduce unnecessary computation
    if((x_0 + 1)*(x_0 + 1) + (y_0+1)*(y_0 +1) < 1/16){return iterAndZ(max_iter,initX2,initY2,initSumsq);}

    double x2 = initX2, y2 = initY2, sumsq = initSumsq;
    int iter = 0;
    while(x2+y2 <= 4 && iter < max_iter){
        double x = x2 - y2 + x_0;
        double y = sumsq - x2 - y2 + y_0;
        x2 = x*x;
        y2 = y*y;
        sumsq = (x+y)*(x+y);
        iter ++;
    }
    return iterAndZ(iter,x2,y2,sumsq);
}
