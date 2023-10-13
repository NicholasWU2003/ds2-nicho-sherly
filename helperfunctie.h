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
        SINE,
        COSINE,
        TANGENT,
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
        binaireBoom(std::string invoerNaam);
        Token maakBoom(Token token);
        bool maakToken(std::string karakter);
        std::vector<std::string> leesIn(std::string invoerNaam);
        void printIO(Token token);

    private:
        std::vector<std::string> prefix;
        std::vector<std::string> inorder;
        std::vector<Token> tokens;
        Token* begin;
        int huidigTokenIndex;
        



};

#endif
