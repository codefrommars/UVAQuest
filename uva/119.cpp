#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

std::map<std::string, int> people;

int main() {
    char name[12];
    std::string group[20];
	int n;
    int balance[20];
	while( std::scanf("%i", &n) != EOF ){
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

            int pp = given / k;
            int kept = given % k;
            
            balance[index] += kept;
            balance[index] -= pp * k;
            for( int j = 0; j < k; j++){
                std::scanf("%s", &name[0]);
                int r = people[std::string(name)];
                balance[r] += pp;
            }
        }

        for(int i = 0; i < n; i++ )
            std::printf("%s %i\n", group[i].c_str(), balance[i]);
        
	}
}