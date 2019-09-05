#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

std::map<std::string, int> people;

int main() {
    char name[50];
    std::string group[20];
	int n;
    int balance[20];
    int group_number = 0;

	while( std::scanf("%i", &n) != EOF ){
        if( group_number != 0 ){
            std::printf("\n");            
        }

        for(int i = 0; i < n; i++ ){
            std::scanf("%s", &name[0]);
            group[i] = std::string(name);
            people[group[i]] = i;
            balance[i] = 0;            
        }

        for(int i = 0; i < n; i++ ){
            std::scanf("%s", &name[0]);
            
            int index = people[std::string(name)];
            int given, k;
            std::scanf("%i", &given);
            std::scanf("%i", &k);            

            if( k == 0 ){
                //balance[index] += given;
                continue;
            }

            int kept = given % k;
            int rgiven = given - kept;
            int pp = rgiven / k;
            
            //balance[index] -= pp * k;
            balance[index] -= rgiven;

            for( int j = 0; j < k; j++){
                std::scanf("%s", &name[0]);                
                int r = people[std::string(name)];
                balance[r] += pp;
            }
        }

        for(int i = 0; i < n; i++ )
            std::printf("%s %i\n", group[i].c_str(), balance[i]);
            
        group_number++;
	}
}