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

std::string readColor(std::istringstream &str){
    std::string adj, color;
    str >> adj;
    str >> color;
    return adj + color;
}

void load() {
    for( std::string line; std::getline(std::cin, line); ){
        std::istringstream strLine(line);
        int colorRow = getId(readColor(strLine));
        
        std::string ignore;
        strLine >> ignore;//bags
        strLine >> ignore;//contain

        int ammount = 0;
        while( strLine >> ammount ){
            int contained = getId(readColor(strLine));
            contains[colorRow][contained] = ammount;
            strLine >> ignore;//bags...
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