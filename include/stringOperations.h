//
// Created by liam on 7/25/22.
//

#ifndef PUREPURSUITSIMULATION_STRINGOPERATIONS_H
#define PUREPURSUITSIMULATION_STRINGOPERATIONS_H
#include <string>
#include <cstring>

char* stringToCharArray(const std::string& string){

    char array[string.length() + 1];

    return strcpy(array, string.c_str());
}

std::string toLowerCase(const std::string& string){

    for (char i : string) {

        if(i != ' '){
            char lower = i;
            lower = (tolower(lower));
            response.c_str()[i] = lower;
        }
        //todo scuffed & needs testing
    }
}


#endif //PUREPURSUITSIMULATION_STRINGOPERATIONS_H
