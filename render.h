class mandelRender{
        int default_max_iter = 50;
        int max_iter;
        double cx, cy, l;
        sf::VertexArray pixels;
        std::deque<int> blackPixelIndices; //stores pixel indices that evaluated to black, for enhance() to act upon them
        std::vector<iterAndZ> zdata; //stores iter and z_final data for evaluated points for enhance() to act upon
        sf::Font font;
        sf::Text iter_count;
        sf::Text zoom_extent;
        sf::Text coords;
        
        iterAndZ color_pixel(int i, int j){
            double x = cx + l*(-0.5 + (double)(i)/window_x);
            double y = cy + l*( 0.5 - (double)(j)/window_y)*((double)window_y/window_x);
            iterAndZ obj = mandelbrot(x,y,max_iter);
            int iter = obj.iter;
            pixels[j*window_x + i].color = palette(iter,max_iter);
            return obj;
        }
        
        iterAndZ color_pixel(int i){
            return color_pixel(i%window_x, i/window_x);
        }
        
        void update(bool positionsAlso = false){
            blackPixelIndices.clear();
            for(int j = 0 ; j < window_y ; j++){
                for(int i = 0 ; i < window_x ; i++){
                    if(positionsAlso) pixels[j*window_x + i].position = sf::Vector2f(i + 0.5f,j + 0.5f);
                    iterAndZ obj = color_pixel(i,j);
                    if(obj.iter == max_iter){
                        blackPixelIndices.push_back(j*window_x + i);
                        zdata[j*window_x + i] = obj;
                    }
                }
            }
            iter_count.setString(" max_iter : " + std::to_string(max_iter));
            std::stringstream l_value, x_value, y_value;
            l_value << l;
            x_value << cx;
            y_value << cy;
            zoom_extent.setString(" zoom extent : " + l_value.str());
            coords.setString("(" + x_value.str() + "," + y_value.str() + ")");
        }
        
    public:

        mandelRender(double X = -0.04536275, double Y = 0.98687645, double L = 5, int max = 50){
            pixels = sf::VertexArray(sf::Points, window_x*window_y);
            cx = X; cy = Y; l = L; max_iter = max;
            zdata.reserve(window_x*window_y);
            
            if (!font.loadFromFile("OpenSans-Light.ttf")){std::cout << "error loading font" << std::endl;}
            
            iter_count.setFont(font);
            iter_count.setFillColor(sf::Color(255,255,255));
            iter_count.setOutlineColor(sf::Color(0,0,0));
            iter_count.setOutlineThickness(2);
            
            zoom_extent.setFont(font);
            zoom_extent.setFillColor(sf::Color(255,255,255));
            zoom_extent.setOutlineColor(sf::Color(0,0,0));
            zoom_extent.setOutlineThickness(2);
            zoom_extent.setPosition(window_x - 400,0);

            coords.setFont(font);
            coords.setFillColor(sf::Color(255,255,255));
            coords.setOutlineColor(sf::Color(0,0,0));
            coords.setOutlineThickness(2);
            coords.setPosition(window_x/2 - 150, window_y - 50);

            update(1);
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
            if(((float)blackPixelIndices.size())/(window_x*window_y) > 0.75){default_max_iter += 50;}
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
            for(int k = 0; k<N; k++){
                
                int index = blackPixelIndices.front();
                int i = index%window_x, j = index/window_x;
                double x = cx + l*(-0.5 + (double)(i)/window_x);
                double y = cy + l*( 0.5 - (double)(j)/window_y)*((double)window_y/window_x);

                iterAndZ obj = zdata[index];
                iterAndZ obj_new = mandelbrot(x,y,max_iter - obj.iter, obj.x2, obj.y2, obj.sumsq);
                obj_new.iter += obj.iter;
                
                pixels[j*window_x + i].color = palette(obj_new.iter,max_iter);
                
                if(obj_new.iter == max_iter){
                    blackPixelIndices.push_back(blackPixelIndices.front());
                    zdata[index] = obj;
                }
                blackPixelIndices.pop_front();
            }
            iter_count.setString(" max_iter : " + std::to_string(max_iter));
        }
        
        sf::VertexArray& render(){
            return pixels;
        }

        sf::Text& text_iter(){
            return iter_count;
        }

        sf::Text& text_zoom(){
            return zoom_extent;
        }

        sf::Text& text_coords(){
            return coords;
        }
};
