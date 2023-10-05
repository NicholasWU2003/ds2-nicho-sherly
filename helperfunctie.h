#ifndef HELPERFUNCTIE_H
#define HELPERFUNCTIE_H

#include <iostream> 
#include <string>
#include <vector>


struct Token {
    enum
    {
        PLUS,
        MINUS,
        DIVIDE,
        MULTIPLY,
        NUMBER,
        VARIABLE,
        SINE,
        COSINE,
        TANGENT
    } type;

    
    union
    {
        char variable;
        double number;
    };
};


class binaireBoom
{
    public:
        std::vector<Token> leesIn(const char* invoerNaam);
        std::string drukaf1();

    private:
        std::vector<std::string> infix;

};

#endif
