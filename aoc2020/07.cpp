#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>

std::map< std::string, std::set<std::string> > parents;
std::map< std::string, std::map<std::string, int> > contents;

void load() {
    for( std::string line; std::getline(std::cin, line); ){
        std::istringstream strLine(line);
        std::string adj, color, ignore;

        strLine >> adj >> color >> ignore >> ignore;
        std::string colorRow = adj + color;
        
        int ammount = 0;
        while( strLine >> ammount ){
            strLine >> adj >> color >> ignore;
            contents[colorRow][adj + color] = ammount;
            parents[adj + color].insert( colorRow );
        }
    }
}

// ---- Part 1 ----
void listAncestors(std::string id, std::set<std::string> &ancestors) {
    ancestors.insert(id);
    std::set<std::string> par = parents[id];
    for(auto p = par.begin(); p != par.end(); p++ )
        listAncestors(*p, ancestors);
}

void part1() {
    load();
    std::set<std::string> an;
    listAncestors("shinygold", an);
    std::cout << an.size() - 1 << std::endl;
}

// ---- Part 2 ----
int insideOf(std::string id){
    int total = 0;

    std::map<std::string, int> contained = contents[id];
    for(auto c = contained.begin(); c != contained.end(); c++){
        if( c->second != 0 )
            total += c->second * (1 +  insideOf(c->first));
    }
    return total;
}

void part2() {
    load();
    std::cout << insideOf("shinygold") << std::endl;
}

int main() {
    part1();
}