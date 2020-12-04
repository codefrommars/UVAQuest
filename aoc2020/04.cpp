#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

typedef std::map< std::string, std::string > Password;

std::vector<Password> readPasswords() {

    std::vector<Password>  passwords;
    std::string line ;

    int current = 0;  
    Password password;
    while( std::getline( std::cin, line ) ) {

        if( line.size() == 1  ){
            passwords.push_back( password );
            password = Password();
            continue;
        }

        std::string keyPair;
        std::istringstream lineStream(line);
        
        while( lineStream >> keyPair ){
            std::string key, value;
            int pos = keyPair.find(':');
            key = keyPair.substr(0, pos);
            value = keyPair.substr(pos + 1);
            password[key] = value;
        }
    }

    passwords.push_back( password );
    return passwords;
}

bool isValid1(Password password){
    if( password.size() == 8 )
        return true;

    if( password.size() < 7 )
        return false;
    
    return password.count("cid") == 0;
}

void part1() {
    std::vector<Password> passwords = readPasswords();
    int valids = 0;
    for( auto p = passwords.begin(); p < passwords.end(); p++)
        valids += isValid1(*p);
    
    std::cout << valids <<std::endl;
}


std::map< std::string, std::string > validEyeColors;

bool isValid2(Password password){
    if( !isValid1(password) )
        return false;

    int byr = 0;
    sscanf( password["byr"].c_str(), "%d", &byr );
    if( byr < 1920 || byr > 2002 )
        return false;
 
    int iyr = 0;
    sscanf( password["iyr"].c_str(), "%d", &iyr );
    if( iyr < 2010 || iyr > 2020 )
        return false;

    int eyr = 0;
    sscanf( password["eyr"].c_str(), "%d", &eyr );
    if( eyr < 2020 || eyr > 2030 )
        return false;
    
    int hgt = 0; 
    int unit = password["hgt"].find_first_not_of("0123456789");
    if( unit == -1 )
        return false;

    sscanf( password["hgt"].substr(0, unit).c_str(), "%d", &hgt );
    if( password["hgt"][unit] == 'c' ){ //This is a hack. The proper validation should test for "cm" and "in"
        if( hgt < 150 || hgt > 193 )
            return false;
    }else {
        if( hgt < 59 || hgt > 76 )
            return false;
    }

    if( password["hcl"].size() != 7 || password["hcl"][0] != '#' )
        return false;
    
    if( password["hcl"].find_last_not_of("0123456789abcdef") != 0 )
        return false;

    if( password["ecl"].size() != 3 ) 
        return false;

    if( validEyeColors.count( password["ecl"] ) == 0 )
        return false;

    if( password["pid"].size() != 9 ) 
        return false;

    int dif = password["pid"].find_first_not_of("0123456789");
    if( dif >= 0 )
        return false;

    return true;
}

void part2() {
    std::vector<Password> passwords = readPasswords();
    int valids = 0;

    validEyeColors["amb"] = 1;
    validEyeColors["blu"] = 1;
    validEyeColors["brn"] = 1;
    validEyeColors["gry"] = 1;
    validEyeColors["grn"] = 1;
    validEyeColors["hzl"] = 1;
    validEyeColors["oth"] = 1;

    for( auto p = passwords.begin(); p < passwords.end(); p++)
        valids += isValid2(*p);
    
    std::cout << valids <<std::endl;
}

int main() {
    part2();
    return 0;
}