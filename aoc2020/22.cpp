#include <iostream>
#include <deque>
#include <string>
#include <unordered_set>

std::deque<int> loadDeck() {
    std::deque<int> deck;
    for( std::string line; std::getline(std::cin, line);){
        line = line.substr(0, line.size() - 1);
        if( line[0] == 'P')
            continue;
        if( line.empty() )
            break;
        deck.push_back( atoi(line.c_str()) );
    }
    return deck;
}

int getPoints( const std::deque<int>& q ){
    int points = 0;
    for( int i = 1; i <= q.size(); i++)
        points += i * q[q.size() - i];
    return points;
}
//This works for my input, but it should be replaced by a better hash calculation
uint64_t state(const std::deque<int>& d1, const std::deque<int>& d2){
    uint64_t p1 = getPoints(d1);
    return p1 * p1 * (uint64_t)getPoints(d2);
}

bool game(std::deque<int>& d1, std::deque<int>& d2, bool recursive = false){
    std::unordered_set<uint64_t> cache;
    while( d1.size() > 0 && d2.size() > 0 ){
        auto st = state(d1, d2);
        if( cache.count(st) == 1 ) 
            return true;
        cache.insert(st);

        int t1 = d1.front(); d1.pop_front(); 
        int t2 = d2.front(); d2.pop_front();

        bool p1Wins = t1 > t2;
        if( recursive && (d1.size() >= t1 && d2.size() >= t2)){
            auto c1 = std::deque<int>(), c2 = std::deque<int>();
            for( int i = 0; i < t1; i++)
                c1.push_back(d1[i]);

            for( int i = 0; i < t2; i++)
                c2.push_back(d2[i]);

            p1Wins = game(c1, c2, true) ;
        }
        if( p1Wins ){
            d1.push_back(t1);
            d1.push_back(t2);
        }else{
            d2.push_back(t2);
            d2.push_back(t1);
        }
    }
    return d1.size() > 0;
}

void run(bool recursive){
    std::deque<int> d1 = loadDeck(), d2 = loadDeck();
    std::cout<< ( game(d1, d2, recursive) ? getPoints(d1) : getPoints(d2) ) << std::endl ;
}

void part1(){
    run(false);
}

void part2(){
    run(true);
}

int main(){
    part2();
}