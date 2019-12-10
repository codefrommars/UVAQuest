#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

double score( int or, int oc, int r, int c ){
    double dr = r - or;
    double dc = c - oc;
    double ang = std::atan2(dc, -dr); //reverse Y, switch x and y

    if( ang < 0 )
        ang += 2.0 * 3.14159265358979323846;
    
    return ang;
}

bool isVisible(bool** map, int w, int h, int or, int oc, int tr, int tc){
    int adr = std::abs(tr - or);
    int adc = std::abs(tc - oc);
    int dr = tr - or;
    int dc = tc - oc;
    
    int d = std::max( adr, adc );
    
    for( int k = 2; k <= d; k ++){
        if( (adr % k == 0) && (adc % k == 0) ){
            for( int m = 1; m < k; m++ )
                if( map[or + m * dr/k][oc + m * dc/k] ){
                    return false;
                }
        }
    }
    return true;
}

void sort(std::vector<int> &visibles, int w, int h, int or, int oc){

    std::sort(visibles.begin(), visibles.end(), 
        [w, h, or, oc](int i, int j) -> bool { 
            int ri = i / w;
            int ci = i % w;
            
            int rj = j / w;
            int cj = j % w;

            double si = score(or, oc, ri, ci);
            double sj = score(or, oc, rj, cj);

            return si < sj;
        }
    );
}



int compDestructedAsteroid(int index, bool** map, int w, int h, int or, int oc){
    std::vector<int> visibles;
    
    do{
        visibles.clear();

        for( int r = 0; r < h; r++){
            for(int c = 0 ; c < w; c++){
                if( !map[r][c] )
                    continue;

                if( or == r && oc == c )
                    continue;

                if( isVisible(map, w, h, or, oc, r, c) )
                    visibles.push_back( r * w + c );
            }
        }

        //destroy visibles
        for(int i = 0; i < visibles.size(); i++){
            int v = visibles[i];
            map[ v / w ][ v % w ] = false;
        }

        index -= visibles.size();

        if( index <= 0 ){
            sort( visibles, w, h, or, oc );
            return visibles[ visibles.size() + index - 1 ];
        }
    }while( visibles.size() > 0 );

    return -1 ; //  !! index > number of asteroids
}

int countVisible(bool** map, int w, int h, int or, int oc){
    int visible = 0;
    for( int r = 0; r < h; r++){
        for(int c = 0 ; c < w; c++){
            if( !map[r][c] )
                continue;

            if( r == or && c == oc )
                continue;

            if( isVisible(map, w, h, or, oc, r, c) )
                visible ++;
        }
    }

    return visible;
}

int maxVisible(bool** map, int w, int h , int& br, int& bc){
    int max = -1;
    for( int r = 0; r < h; r++){
        for(int c = 0 ; c < w; c++){
            if( !map[r][c] )
                continue;

            int v = countVisible(map, w, h, r, c);
            if( v > max ){
                max = v;
                br = r;
                bc = c;
            }
        }
    }
    return max;
}

int main() {
    
    std::string line;
    std::vector<std::string> lines;
    
    while( std::getline(std::cin, line) )
        lines.push_back(line);    

    int w = lines[0].size();
    int h = lines.size();

    bool** map = new bool*[h];

    for( int r = 0; r < h; r++){
        map[r] = new bool[w];
        for(int c = 0 ; c < w; c++){
            map[r][c] = lines[r][c] == '#';
        }
    }

    int br = 0, bc = 0;
    maxVisible(map, w, h, br, bc);
    int a = compDestructedAsteroid(200, map, w, h, br, bc);
    std::cout << 100 * (a % w) + (a / w) << std::endl;
    return 0;
}