class mandelRender{
        int default_max_iter = 50;
        int max_iter;
        double cx, cy, l;
        sf::VertexArray pixels;
        std::deque<int> blackPixelIndices; //stores pixel indices that evaluated to black, for enhance() to act upon them
        
        bool color_pixel(int i, int j){
            double x = cx + l*(-0.5 + (double)(i)/window_x);
            double y = cy + l*( 0.5 - (double)(j)/window_y)*((double)window_y/window_x);
            int iter = mandelbrot(x,y,max_iter);
            pixels[j*window_x + i].color = palette(iter,max_iter);
            return iter == max_iter;
        }
        
        bool color_pixel(int i){
            return color_pixel(i%window_x, i/window_x);
        }
        
        void update(){
            double lx = l, ly = l*((double)window_y/window_x);
            for(int j = 0 ; j < window_y ; j++){
                for(int i = 0 ; i < window_x ; i++){
                    pixels[j*window_x + i].position = sf::Vector2f(i,j);
                    if(color_pixel(i,j)){blackPixelIndices.push_back(j*window_x + i);}
                }
            }
        }
        
    public:

        mandelRender(double X = -0.5499751, double Y = 0.6251115, double L = 2, int max = 50){
            pixels = sf::VertexArray(sf::Points, window_x*window_y);
            cx = X; cy = Y; l = L; max_iter = max;
            update();
        }

        void move(int mouseX, int mouseY, double scale){
            max_iter = default_max_iter;
            cx += l*(-0.5 + (double)(mouseX)/window_x);
            cy += l*( 0.5 - (double)(mouseY)/window_y)*((double)window_y/window_x);
            l *= scale;
            update();
            //if the default max_iter starts  to give largely black screen, we increase it
            if(((float)blackPixelIndices.size())/(window_x*window_y) > 0.75){default_max_iter += 50;}
        }

        void zoom(double scale){
            max_iter = default_max_iter;
            l *= scale;
            update();
            //if the default max_iter starts  to give largely black screen, we increase it
            if(((float)blackPixelIndices.size())/(window_x*window_y) > 0.9){default_max_iter += 50;}
        }
        
        void reset(){
            max_iter = 50;
            default_max_iter = 50;
            cx = -0.75; cy = 0; l = 3;
            //updating pixels:
            update();
        }
        
        void enhance(){
            if(max_iter < 1000){
                max_iter += 100;
            }
            int N = blackPixelIndices.size(); // only want to loop through once
            double lx = l, ly = l*((double)window_y/window_x);
            for(int k = 0; k<N; k++){
                if(color_pixel(blackPixelIndices.front())){blackPixelIndices.push_back(blackPixelIndices.front());}
                blackPixelIndices.pop_front();
            }
        }
        
        sf::VertexArray& render(){
            return pixels;
        }
};