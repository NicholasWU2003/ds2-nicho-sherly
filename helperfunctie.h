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
        SINE,
        COSINE,
        TANGENT
    
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
        void maakToken(std::string karakter);
        bool leesIn(std::string invoerNaam);
        void printTokens() const; 
        void maakBoom();

    private:
        std::vector<std::string> prefix;
        std::vector<Token> tokens;
        Token* begin;
        bool haakjes = false;


};

#endif
