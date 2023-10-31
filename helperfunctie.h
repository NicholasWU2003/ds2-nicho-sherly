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
        std::vector<std::string> leesIn(std::string formule);
        std::string enumToString(int type);
        std::string plaatsToken(Token* token);
        void verwijderBoom(Token* token);
        void printIO(Token* token);
        void printDOT(const std::string& uitvoerNaam);
        void printHelpDOT(Token* begin,std::ofstream& wegschrijven);
        void evalueer(Token* token, double waarde);

        void printIOCall();
        void maakBoomCall(std::string formule);
        void vereenvoudigCall();
        void evalCall(double waarde);
        void diffCall();

        bool bijnaGelijk(double a, double b);
        bool maakToken(std::string karakter);
        Token* maakBoom(Token token);
        Token* simplify(Token* token);
        Token* differentieer(Token* token);



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
