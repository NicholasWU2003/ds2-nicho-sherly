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
        ~binaireBoom();
        binaireBoom(std::string invoerNaam);
        void verwijderBoom(Token* token);
        std::string enumToString(int type);
        Token* maakBoom(Token token);
        bool maakToken(std::string karakter);
        std::vector<std::string> leesIn(std::string invoerNaam);
        void printIO(Token* token);
        void printDOT(const std::string& uitvoerNaam);
        void printHelpDOT(Token* begin,std::ofstream& wegschrijven);
        std::string plaatsToken(Token* token);

        Token* vereenvoudig(Token* token);



    private:
        std::vector<std::string> prefix;
        std::vector<std::string> inorder;
        std::vector<Token> tokens;
        Token* begin;
        int huidigTokenIndex;
        int telDOT = 1;

};

#endif
