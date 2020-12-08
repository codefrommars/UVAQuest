#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <utility>

using Instruction = std::pair<char, int>;

int exec(const Instruction& inst, int* acum){
    if( inst.first == 'j' )
        return inst.second;
    
    if( inst.first == 'a' )
        *acum += inst.second;
    return 1;
}

std::vector<Instruction> load(){
    std::string mnemonic;
    int param;
    std::vector<Instruction> program;
    for( std::string line;  std::cin >> mnemonic >> param ; )
        program.push_back( Instruction(mnemonic[0], param) );
    return program;
}

// ---- Part 1 ----
void part1() {
    std::vector<Instruction> program = load();
    std::set<int> executed;
    int acum = 0;
    for( int pc = 0; executed.count(pc) == 0; pc += exec(program[pc], &acum) )
        executed.insert(pc);
    
    std::cout << acum << std::endl;
}

// ---- Part 2 ----
bool fixes(std::vector<Instruction> program, int index, int acum){
    program[index].first = (program[index].first == 'n') ? 'j' : 'n'; //Patch the program
    std::set<int> executed;
    for(int pc = index; pc < program.size(); pc += exec(program[pc], &acum) ){
        if( executed.count(pc) != 0 )
            return false;
        executed.insert(pc);
    }
    std::cout << acum << std::endl;
    return true;
}

void part2(){
    std::vector<Instruction> program = load();
    int acum = 0;
    for(int pc = 0; pc < program.size();  pc += exec(program[pc], &acum) ){
        if( program[pc].first != 'a' )
            if( fixes(program, pc, acum) )
                return;
    }
}

int main() {
    part2();
    return 0;
}