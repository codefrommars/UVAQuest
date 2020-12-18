#include <iostream>
#include <sstream>
#include <string>

int64_t eval(std::istringstream& ss, bool delayMult);

int64_t operand(std::istringstream& ss, bool delayMult){
    char c; ss >> c;
    if( c == '(' )
        return eval(ss, delayMult);
    return c - '0';
}
//This assumes the expressions are well constructed
int64_t eval(std::istringstream& ss, bool delayMult){
    int64_t val = operand(ss, delayMult);
    char c;
    while( ss >> c ){
        if( c == '*'){
            if( delayMult )
                return val *= eval(ss, delayMult);
            val *= operand(ss, delayMult);
        }
        if( c == ')')
            return val;
        if( c == '+' )
            val += operand(ss, delayMult);
    }
    return val;
}

void run(bool delayMult) {
    int64_t s = 0; std::istringstream ss;
    for( std::string line; std::getline(std::cin, line);)
        s += eval(ss = std::istringstream(line), delayMult);
    
    std::cout << s << std::endl;
}

void part1() {
    run(false);
}

void part2() {
    run(true);
}

int main() {
    part2();
}