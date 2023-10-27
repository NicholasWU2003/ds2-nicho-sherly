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
        // binaireBoom(std::string invoerNaam);
        ~binaireBoom();
        void verwijderBoom(Token* token);
        std::string enumToString(int type);
        void maakBoomCall(std::string formule);
        Token* maakBoom(Token token);
        bool maakToken(std::string karakter);
        std::vector<std::string> leesIn(std::string formule);
        void printIOCall();
        void printIO(Token* token);
        void printDOT(const std::string& uitvoerNaam);
        void printHelpDOT(Token* begin,std::ofstream& wegschrijven);
        std::string plaatsToken(Token* token);

        Token* vereenvoudig(Token* token);



    private:
        std::vector<std::string> prefix;
        std::vector<std::string> inorder;
        std::vector<Token> tokens;
        std::vector<Token*> tokenPtrs;
        Token* begin;
        int huidigTokenIndex;
        int telDOT;

};

#endif
