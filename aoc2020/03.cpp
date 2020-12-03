#include <iostream>
#include <string>
#include <vector>

void part1() {
    std::string line;
    int row = 0;
    int trees = 0;

    while( std::cin >> line ){
        int index = (3 * row) % line.size();
        if( line[index] == '#' )
            trees++;
        row++;
    }
    std::cout << trees << std::endl; 
}

int trees(std::vector<std::string> lines, int dc, int dr) {
    int r = 0, c = 0;
    int t = 0;

    while( r < lines.size() ){
        if( lines[r][c] == '#' )
            t++;
        c = (c + dc) % lines[r].size();
        r += dr;
    }

    return t;
}

void part2() {
    std::vector<std::string> lines;
    std::string line;
    
    while( std::cin >> line )
        lines.push_back(line);
    
    int64_t s = trees(lines, 1, 1);
            s*= trees(lines, 3, 1);  
            s*= trees(lines, 5, 1);  
            s*= trees(lines, 7, 1);  
            s*= trees(lines, 1, 2);
              
    std::cout << s << std::endl;
}

int main() {
    part2();
}