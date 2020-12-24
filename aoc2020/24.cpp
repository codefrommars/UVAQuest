#include <iostream>
#include <string>
#include <map>
#include <set>

std::map<std::string, std::pair<int,int> > nDelta;
std::set< std::pair<int, int> > grid;

void loadGrid(){
                        nDelta["nw"] = {-1, 1};   nDelta["ne"] = {1, 1};
    nDelta["w"] = {-2, 0};                                            nDelta["e"] = {2, 0};
                        nDelta["sw"] = {-1, -1};  nDelta["se"] = {1, -1};

    for(std::string line; std::cin >> line; ){
        std::pair<int, int> coord = {0, 0};
        for(int i = 0; i < line.size(); ){
            auto ng = nDelta.find( line.substr(i, 1) );
            if( ng == nDelta.end() )
                ng = nDelta.find(line.substr(i, 2));
            coord.first += ng->second.first;
            coord.second += ng->second.second;
            i += ng->first.size();
        }
        if( grid.find(coord) == grid.end() )
            grid.insert(coord);
        else
            grid.erase(coord);
    }
}
// ---- Part1 ----
void part1(){
    loadGrid();
    std::cout << grid.size() << std::endl;
}
// ---- Part2 ----
void step(){
    std::map< std::pair<int, int>, int > nCount;

    for( auto kv : grid ){
        nCount[kv]; //Forces the map to put a 0 if there's no element
        for( auto dh : nDelta ){
            int x = kv.first + dh.second.first;
            int y = kv.second + dh.second.second;
            nCount[ {x, y} ]++;
        }
    }

    for( auto c : nCount )
        if( grid.count(c.first) == 1 ){ //is black
            if(  c.second == 0 || c .second > 2 )
                 grid.erase(c.first);
        }else{
            if( c.second == 2 )
                grid.insert(c.first);
        }
}

void part2() {
    loadGrid();
    for(int i = 0; i < 100; i++)
        step();
    std::cout << grid.size() << std::endl;
}

int main(){
    part2();
}