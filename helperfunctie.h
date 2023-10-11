#ifndef HELPERFUNCTIE_H
#define HELPERFUNCTIE_H

#include <iostream> 
#include <string>
#include <vector>


struct Token{
    enum{
        PLUS,
        MINUS,
        POWER,
        DIVIDE,
        TIMES,
        SIN,
        COS,
        PI,
        NUMBER,
        VARIABLE,
    } type;
    
    union{
        char variable;
        double number;
    };

    Token* links = nullptr;
    Token* rechts = nullptr;
};

class binaireBoom{
    public:
        binaireBoom();
        binaireBoom(std::vector<std::string> invoer);
        void maakBoom(Token token);
        bool maakToken(std::string karakter);
        bool leesIn(const char* invoerNaam);

    private:
        std::vector<std::string> prefix;
        std::vector<Token> tokens;
        Token* begin;

};

#endif
