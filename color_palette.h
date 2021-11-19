#include <cmath>
// using iter to decide the Hue and then converting HSV to RGB to create an sf::Color object

struct colors{
        sf::Color array[1100];
        bool calculated[1100];
        
        colors(){
            for(int i=0; i<1100; i++){calculated[i] = false;}
        }

        void insert(int i, sf::Color color){
            array[i-1] = color; 
            calculated[i-1] = true;
            return;
        }
};

colors lookup_table;

double grad(double iter){
    /*
    outputs the hue corresponding to # of escape iterations
    it's a helper function to customize color palette
    has no mathematical meaning
    */
    return (iter < 400 ? iter/15 : sqrt(iter/200)*(200/15));
    //return iter/15;
}

sf::Color palette(int iter, int max_iter){
    if(iter == max_iter){return sf::Color(0,0,0);}
    if(lookup_table.calculated[iter-1]){return lookup_table.array[iter-1];}
    /*
    H = Hue (can be thought of to be in the range 0-6 since we use int(H)%6 for the switch statement)
    Usually H is in 0-360 and we do use (H/60) for calculating fract and switch()
    but here I wanted grad() to have full creative freedom and the Hue value can 
    just wrap around to 0 when it gets > 360. so it would just make sense to include all
    the multipliers (like 60) in grad() itself.
    S = Saturation in 0-1
    V = "Value" in 0-255, set V = 0 for black
    */
    double H = grad(iter), S = 1, V = (iter<max_iter ? 255 : 0); 
    double P, Q, T, fract;
    fract = H - int(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    switch(int(H)%6){
        case 0: 
            lookup_table.insert(iter, sf::Color(V,T,P));
            return sf::Color(V,T,P);
            break;
        case 1:
            lookup_table.insert(iter, sf::Color(Q,V,P));
            return sf::Color(Q,V,P);
            break;
        case 2:
            lookup_table.insert(iter, sf::Color(P,V,T));
            return sf::Color(P,V,T);
            break;
        case 3:
            lookup_table.insert(iter, sf::Color(P,Q,V));
            return sf::Color(P,Q,V);
            break;
        case 4:
            lookup_table.insert(iter, sf::Color(T,P,V));
            return sf::Color(T,P,V);
            break;
        case 5:
            lookup_table.insert(iter, sf::Color(V,P,Q));
            return sf::Color(V,P,Q);
            break;
        default: return sf::Color(V,P,Q); break; // throws warning without default return
    }
}
