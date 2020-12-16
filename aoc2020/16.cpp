#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <numeric>

struct Constraint { int a, b, c, d; };

std::vector<int> parseTicket(std::istringstream line){
    std::vector<int> t;
    for( std::string v; std::getline(line, v, ','); )
        t.push_back( atoi(v.c_str() ));
    return t;
}

std::vector<Constraint> constraints;
std::vector<int> ticket;

void loadHeader() {
    std::string line; Constraint c;
    for( ; std::getline( std::cin, line); ){
        if( sscanf(line.c_str(), "%*[^:]: %d-%d or %d-%d", &c.a, &c.b, &c.c, &c.d) != 4 )
            break;
        constraints.push_back( c );
    }
    std::getline( std::cin, line);// line = "your ticket:"
    std::getline( std::cin, line);// line = <the actual ticket >
    ticket = parseTicket( std::istringstream(line));
    std::getline( std::cin, line);// line = <ws>
    std::getline( std::cin, line);// line = "nearby tickets:"
}

bool isValid(int v, const Constraint& c ){
    return (c.a <= v && v <= c.b) || (c.c <= v && v <= c.d);
}

int sumImpossibleInTicket(const std::vector<int>& t){
    return std::accumulate(begin(t), end(t), 0, [&](int sum, int value){
        for( Constraint c : constraints )
            if(isValid(value, c))
                return sum; 
        return sum + value;
    });
}

void part1() {
    loadHeader();
    int sum = 0;
    for( std::string line; std::getline( std::cin, line); )
        sum += sumImpossibleInTicket( parseTicket(std::istringstream(line)) );

    std::cout << sum << std::endl;
}

void part2() {
    loadHeader();
    int N = constraints.size();
    std::vector<std::vector<bool>> possible;
    for(int i = 0; i < N; i++)
        possible.push_back( std::vector<bool>(N, true) );
    
    for( std::string line; std::getline( std::cin, line); ){
        std::vector<int> t = parseTicket(std::istringstream(line));
        if( sumImpossibleInTicket(t) == 0 )
            for(int i = 0; i < N; i++)
                for( int j = 0; j < N; j++ )
                    if( !isValid(t[j], constraints[i]) )//Value j in the ticket t doesn't conform with constraint i 
                        possible[i][j] = false;
    }

    std::vector<int> sol(N, -1);
    for(int k = 0; k < N; k++){//For all constraints
        for( int i = 0; i < N; i++){//Find the constraint(i) with only 1 valid position NOT in the solution
            int lastValidCol = 0, validPosCount = 0;
            for( int j = 0; j < N; j++ ){
                if( possible[i][j] && std::find(begin(sol), end(sol), j) == end(sol)){
                    validPosCount++;
                    lastValidCol = j;
                }
            }
            if( validPosCount == 1)
                sol[i] = lastValidCol;
        }
    }

    int64_t r = 1;
    for(int i = 0; i < 6; i++)
        r *= ticket[ sol[i] ];

    std::cout << r << std::endl;
}

int main() {
    part2();
}