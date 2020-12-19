#define _GLIBCXX_REGEX_STATE_LIMIT 1000000 //The max regex len is capped at 100k

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>

using PTable = std::unordered_map<int, std::vector< std::vector<int> >>;
std::unordered_map<int, std::string> rCache;

std::string regexFor(int idx, PTable pTable){
    if( rCache.find(idx) != rCache.end() )
        return rCache[idx];

    std::string re = "(";
    
    for( int i = 0; i < pTable[idx].size(); i++ ){
        for( auto pIdx : pTable[idx][i] ){
            re += regexFor(pIdx, pTable);
        }
        if( i != pTable[idx].size() -1 )
            re += "|";
    }

    rCache[idx] = re + ")";
    return rCache[idx];
}

void run(bool injectRules){
    PTable prod;

    for( std::string line; std::getline(std::cin, line); ){
        int col = line.find(':');
        if( col == line.npos )
            break;

        int idx = atoi( line.substr(0, col).c_str() );

        auto rSide = line.substr(col + 2);

        if( rSide[0] == '"'){
            rCache[idx] = rSide[1];
            continue;
        }

        std::istringstream stream(rSide);
        std::vector<int> list;
        while( stream >> line ){
            if( line[0] == '|' ){
                prod[idx].push_back( std::vector<int>(list) );
                list.clear();
            }else{
                list.push_back( atoi(line.c_str()) );
            }
        }
        prod[idx].push_back( std::vector<int>(list) );
    }
    
    if( injectRules ){
        std::string re42 = regexFor(42, prod);
        rCache[8] = "("+ re42 + ")+";
        
        std::string re31 = regexFor(31, prod);
        std::string re11 = "" + re42 + re31 +"";
        for( int i = 2; i < 10; i++)
            re11 += "|" + re42 + "{" + std::to_string(i) +"}"+ re31 + "{" + std::to_string(i) + "}";
        
        rCache[11] = "(" + re11 + ")";
    }

    auto reg = std::regex( regexFor(0, prod) );
    int count = 0;
    for( std::string line; std::cin >> line; )
        if( std::regex_match( line, reg ) )
            count++;
    
    std::cout << count << std::endl;
}

void part1() {
    run(false);
}

void part2(){
    run(true);
}

int main(){
    part2();
}