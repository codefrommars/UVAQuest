#include <iostream>
#include <string>
#include <unordered_map>

using Memory = std::unordered_map<uint64_t, uint64_t>;
using WriteFunc = void (Memory&, int64_t, const char*, int64_t, int64_t, int64_t );

void process(WriteFunc func){
    Memory mem;
    std::string mask;
    for( std::string line ; std::getline(std::cin, line); ) {
        if( line[1] == 'a' ){
            mask = line.substr(7);
        }else {
            uint64_t addr, value = 0;
            sscanf(line.c_str(), "mem[%lu] = %lu", &addr, &value );
            func(mem, addr, mask.c_str(), value, 0, 0);
        }
    }
    uint64_t s = 0;
    for( auto v : mem )
        s += v.second;
    std::cout << s << std::endl;
}
// ---- Part 1 ----
void writeRule1(Memory& mem, int64_t addr, const char* mask, int64_t value, int64_t om, int64_t am){
    if( *mask == 0 )
        mem[addr] = (value & ~am) | om ;
    else if( *mask == '1' )
        writeRule1(mem, addr, mask + 1, value, 2 * om + 1, 2 * am);
    else if( *mask == '0' )
        writeRule1(mem, addr, mask + 1, value, 2 * om, 2 * am + 1);
    else if( *mask == 'X' )
        writeRule1(mem, addr, mask + 1, value, 2 * om, 2 * am);
}

void part1() {
    process(writeRule1);
}
// ---- Part 2 ----
void writeRule2(Memory& mem, int64_t addr, const char* mask, int64_t value, int64_t om, int64_t am ){
    if( *mask == 0 )
        mem[(addr & ~am) | om] = value;
    else if( *mask == 'X' ){
        writeRule2(mem, addr, mask + 1, value, 2 * om + 1, 2 * am);
        writeRule2(mem, addr, mask + 1, value, 2 * om, 2 * am + 1);
    }else if( *mask == '1' )
        writeRule2(mem, addr, mask + 1, value, 2 * om + 1, 2 * am);
    else
        writeRule2(mem, addr, mask + 1, value, 2 * om, 2 * am);
}

void part2() {
    process(writeRule2);
}

int main() {
    part2();
}