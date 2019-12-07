#include <vector>

#include <iostream>

struct Segment{
    int p[2];
    int dir; //0 -> horizontal, 1 -> vertical
    int len;
};

int readSegment(Segment *s ) {
    
    char dir;
    int len;
    int scan = scanf("%c%i", &dir, &len);
    
    if( scan ){
        s->dir = (dir == 'U' || dir == 'D');
        
        if( dir == 'L' || dir == 'D' )
            len *= -1;

        s->len = len;
    }

    return scan;
}

std::vector<Segment> readWire() {
    std::vector<Segment> wire;

    int x = 0, y = 0;

    while( true ){
        Segment s;
        s.p[0] = x;
        s.p[1] = y;

        if( !readSegment(&s) )
            break;

        if( s.dir == 0 )
            x += s.len;
        else
            y += s.len;
        
        wire.push_back(s);
        
        if( std::cin.peek() == '\n'){
            std::cin.get();           
            break;
        }

        if (std::cin.peek() == ',')
           std::cin.ignore();        
    }
    return wire;
}

int inside(int i0, int i1, int v){
    return (v > i0 && v < i1) || (v > i1 && v < i0);
}

int intSameAxis(Segment &a, Segment &b) {
    int d = a.dir;
    if( a.p[d] != b.p[d] )
        return -1;

    if( inside(a.p[d], a.p[d] + a.len, b.p[d] ) )
        return std::abs(b.p[0] + b.p[1]);
    
    return -1;
}

int intersection(Segment &a, Segment &b){
    if( a.dir == b.dir ){
        int len = intSameAxis( a, b);
        if( len > 0 )
            return len;
        return intSameAxis(b, a);
    }

    if( !(inside(b.p[b.dir], b.p[b.dir] + b.len, a.p[b.dir]) && inside(a.p[a.dir], a.p[a.dir] + a.len, b.p[a.dir]) )  )
        return -1;

    return std::abs(b.p[a.dir]) + std::abs ( a.p[b.dir] );
}

int findClosestIntersection(std::vector<Segment> &wa, std::vector<Segment> &wb) {
    unsigned int minDist = -1;
    
    for(int i = 0; i < wa.size(); i++){
        for(int j = 0; j < wb.size(); j++){
            int d = intersection(wa[i], wb[j]);
            if( d <= 0 )
                continue;            
            if( d < minDist )
                minDist = d;
        }
    }

    return minDist;
}

int main(){
    std::vector<Segment> w1 = readWire();
    std::vector<Segment> w2 = readWire();

    int dist = findClosestIntersection(w1, w2);

    std::cout << dist << std::endl;

    // for( int i = 0; i < w2.size(); i++)
    //     std::cout << w2[i].p[0] << ", " << w2[i].p[1] << "(" << w2[i].dir << ", " << w2[i].len << ")" << std:: endl;
    return 0;
}