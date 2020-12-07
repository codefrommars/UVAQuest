#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>

int contains[1024][1024];
std::map< std::string, int > colorId;

int getId(std::string colorName){
    if( colorId.count(colorName) == 0 )
        colorId[colorName] = colorId.size();

    return colorId[colorName];
}

void load() {
    for( std::string line; std::getline(std::cin, line); ){
        std::istringstream strLine(line);
        std::string adj, color, ignore;

        strLine >> adj >> color >> ignore >> ignore;
        int colorRow = getId(adj + color);
        
        int ammount = 0;
        while( strLine >> ammount ){
            strLine >> adj >> color >> ignore;
            int contained = getId(adj + color);
            contains[colorRow][contained] = ammount;
        }
    }
}

// ---- Part 1 ----
void addContainers(int color, std::set<int> &containers){
    if( containers.count(color) != 0 )
        return;

    containers.insert(color);
    for(int i = 0; i < colorId.size(); i++){
        if( contains[i][color] )
            addContainers(i, containers);
    }
}

void part1() {
    load();
    std::set<int> containers;
    addContainers(getId("shinygold"), containers);
    std::cout << containers.size() - 1 << std::endl; //Remove shiny gold from the count
}

// ---- Part 2 ----
int insideOf(int color){
    int total = 0;

    for(int j = 0; j < colorId.size(); j++){
        int mult = contains[color][j];
        if( mult != 0 )
            total += mult * (1 +  insideOf(j));
    }
    return total;
}

void part2() {
    load();
    std::cout << insideOf(getId("shinygold")) << std::endl;
}

int main() {
    part2();
}