#include <iostream>
#include <string>
#include <bitset>

void part1() {
    std::bitset<32> answers;
    int total = 0;

    for( std::string line; std::getline( std::cin, line );  ){
        if( line.size() == 0 ){
            total += answers.count();
            answers.reset();
            continue;
        }

        for( auto c : line )
            answers[c - 'a'] = true;
    }
    //Maybe didn't end with an endline
    total += answers.count();
    std::cout << total << std::endl;
}

void part2() {
    std::bitset<32> groupAnswers;
    int total = 0;
    groupAnswers.set();

    for( std::string line; std::getline( std::cin, line );  ){
        if( line.size() == 0 ){
            total += groupAnswers.count();
            groupAnswers.set();
            continue;
        }

        std::bitset<32> answer;
        for( auto c : line )
            answer[c - 'a'] = true;

        groupAnswers &= answer;
    }
    //Maybe didn't end with an endline
    total += groupAnswers.count();
    std::cout << total << std::endl;
}

int main() {
    part2();
    return 0;
}