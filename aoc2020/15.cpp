#include <iostream>
#include <vector>

void runTo(const std::vector<int>& starting, int limit){
    std::vector<int> lastSpokenTurn(limit);
    int prevNum = -1, currNum;
    for(int turn = 0; turn < limit; turn++){
        if( turn < starting.size() )
            currNum = starting[turn];
        else if (lastSpokenTurn[prevNum] == 0)
            currNum = 0;
        else
            currNum = turn - lastSpokenTurn[prevNum];
        if( prevNum >= 0 )
            lastSpokenTurn[prevNum] = turn;
        prevNum = currNum;
    }
    std::cout << prevNum << std::endl;
}

void part1(){
    runTo({14,3,1,0,9,5}, 2020);
}

void part2(){
    runTo({14,3,1,0,9,5}, 30000000);
}

int main(){
    part1();
}