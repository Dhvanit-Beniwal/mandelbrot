#include <cmath>
// using iter to decide the Hue and then converting HSV to RGB to create an sf::Color object

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
    /*
    H = Hue (can be thought of to be in the range 0-6 since we use int(H)%6 for the switch statement
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
        case 0: return sf::Color(V,T,P); break;
        case 1: return sf::Color(Q,V,P); break;
        case 2: return sf::Color(P,V,T); break;
        case 3: return sf::Color(P,Q,V); break;
        case 4: return sf::Color(T,P,V); break;
        case 5: return sf::Color(V,P,Q); break;
        default: return sf::Color(V,P,Q); break; // throws warning without default return
    }
}