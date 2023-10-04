#ifndef HELPERFUNCTIE_H
#define HELPERFUNCTIE_H

#include <iostream> 
#include <string>
#include <vector>


struct Token {
    enum {
        PLUS,
        MINUS,
        NUMBER,
        VARIABLE
    } type;
    
    union {
        char variable;
        double number;
    };
};


class binaireBoom
{
    public:
        bool leesIn(const char* invoerNaam);

    private:
        std::vector<std::string> woorden;


};

#endif
