#include <iostream>
#include <algorithm>

#define SQRT_3 1.732050807568877

int g(double w, double h){
    return (int)w * (int)h;
}

int st(double w, double h){
    int m = (int)( (2.0 * (h - 1.0)) / SQRT_3 + 1);
    int n = (int)w;

    return m * n - m / 2;
}

int ss(double w, double h){
    int m = (int)( (2.0 * (h - 1.0)) / SQRT_3 + 1);
    int n = (int)(w - 0.5);

    return m * n;
}

int main() {

    double w, h;
    while( std::scanf("%lf %lf", &w, &h) != EOF ) {
        int mg = std::max(g(w, h), g(h, w));        
        int mst = std::max( st(w, h), st(h, w));        
        int mss = std::max( ss(w, h), ss(h, w));        
        int ms = std::max(mst, mss);

        if( ms > mg )
            std::printf("%i skew\n", ms);           
        else
            std::printf("%i grid\n", mg);
    }

    return 0;
}