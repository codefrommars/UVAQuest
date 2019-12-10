#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// void clear(bool** aux, int w, int h){
//     for( int r = 0; r < h; r++){
//         for(int c = 0 ; c < w; c++){
//             aux[r][c] = false;
//         }
//     }
// }


bool isVisible(bool** map, int w, int h, int or, int oc, int tr, int tc){
    int adr = std::abs(tr - or);
    int adc = std::abs(tc - oc);
    int dr = tr - or;
    int dc = tc - oc;
    
    int d = std::max( adr, adc );
    // std::cout << "Testing "<< or <<", "<< oc <<" -> " << tr << ", " << tc << " //  d: " << d;
    for( int k = 2; k <= d; k ++){
        if( adr % k == 0 && adc % k == 0 ){
            for( int m = 1; m < k; m++ )
                if( map[or + m * dr/k][oc + m * dc/k] ){
                   // std::cout << " Blocked"<< std::endl;
                    return false;
                }
        }
    }
    // std::cout << " Visible"<< std::endl;
    return true;
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

int maxVisible(bool** map, int** aux, int w, int h , int& br, int& bc){
    int max = -1;
    for( int r = 0; r < h; r++){
        for(int c = 0 ; c < w; c++){
            if( !map[r][c] )
                continue;

            int v = countVisible(map, w, h, r, c);
            aux[r][c] = v;
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
    int** aux = new int*[h];

    for( int r = 0; r < h; r++){
        map[r] = new bool[w];
        aux[r] = new int[w];
        for(int c = 0 ; c < w; c++){
            map[r][c] = lines[r][c] == '#';
            aux[r][c] = -1;
        }
    }
    int br = 0, bc = 0;
    std::cout << maxVisible(map, aux, w, h, br, bc) << std::endl;
    // std::cout << br << ", " << bc;
    // for( int r = 0; r < h; r++){
    //     for(int c = 0 ; c < w; c++){
    //         if( aux[r][c] == -1 )
    //             std::cout << '.';
    //         else
    //             std::cout << aux[r][c];
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}