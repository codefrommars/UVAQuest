#include <iostream>
#include <sstream>
#include <unordered_set>
#include <map>
#include <string>

std::map<std::string, std::unordered_set<std::string>> allergens;
std::map<std::string, int> ingCounter;

void load() {
    for(std::string str ; std::getline( std::cin, str); ){
        std::istringstream rstream(str); 
        std::unordered_set<std::string> ingredients;
        for(std::string ingredient; rstream >> ingredient; ){
            if( ingredient[0] == '(')
                break;
            if( ingCounter.count(ingredient) == 0 )
                ingCounter[ingredient] = 1;
            else 
                ingCounter[ingredient]++;
            ingredients.insert(ingredient);
        }
        for(; rstream >> str; ){
            auto allergen = str.substr(0, str.size() - 1);
            if( allergens.count(allergen) == 0 )
                allergens[allergen] = ingredients;
            else//Intersect the one we had previously with the new set
                for( auto ings = allergens[allergen].begin(); ings != allergens[allergen].end(); )
                    if(ingredients.count(*ings) == 0)
                        ings = allergens[allergen].erase(ings);
                    else
                        ings++;
        }
    }
}

void part1() {
    load();
    int total = 0;
    for( auto icounter : ingCounter ){
        bool active = false;
        for( auto agx : allergens )
            if( agx.second.count(icounter.first) != 0 )
                active = true;
        if( !active )
            total += icounter.second;
    }
    std::cout << total << std::endl;
}

void part2() {
    load();
    for( int i = 0; i < allergens.size(); i++)
        for( auto agx : allergens )
            if( agx.second.size() == 1 ) //solved, it could be cached in another set to avoid the deleting iteration
                for( auto& agx2 : allergens )
                    if( agx2.first.compare(agx.first) != 0 )
                        agx2.second.erase(*agx.second.begin());
    
    for( auto sol = allergens.begin(); sol != allergens.end(); sol++ ){ //Print solution
        if( sol != allergens.begin() )
            std::cout <<",";
        std::cout << *sol->second.begin();
    }
    std::cout << std::endl;
}

int main(){
    part2();
}