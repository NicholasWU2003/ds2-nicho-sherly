#include <iostream>
#include <fstream>
#include <vector>
#include "helperfunctie.h"

bool binaireBoom::maakToken(std::string kar){
    struct Token huidig;
    struct Token* hulp =  &huidig;

    if(begin == nullptr)
    {
        begin = hulp;
    }

    try{
        int getal = std::stoi(kar);
        huidig.type = Token::NUMBER;
        huidig.number = getal;

    }catch(const std::invalid_argument&){
        try{
            double dGetal = std::stod(kar);
            huidig.type = Token::NUMBER;
            huidig.number = dGetal;

        }catch(const std::invalid_argument&){

            if(kar == "sin"){
                huidig.type = Token::SIN;
            }
            else if(kar == "cos"){
                huidig.type = Token::COS;
            }
            else if(kar == "+"){
                huidig.type = Token::PLUS;
            }
            else if(kar == "-"){
                huidig.type = Token::MINUS;
            }
            else if(kar == "^"){
                huidig.type = Token::POWER;
            }
            else if(kar == "*"){
                huidig.type = Token::TIMES;
            }
            else if(kar == "pi"){
                huidig.type = Token::PI;
                huidig.variable = 'p';
            }
            else if((kar >= "a" && kar <= "z") || (kar >= "A" && kar <= "Z"))
            {
                huidig.type = Token::VARIABLE;
                huidig.variable = kar[0];
            }
            
        }catch(const std::invalid_argument&){
            return false;
        }
    }
    tokens.push_back(huidig);
    return true;
}

void binaireBoom::maakBoom(Token token){

}



binaireBoom::binaireBoom(){}

binaireBoom::binaireBoom(std::vector<std::string> invoer){
    for(const std::string & kar : invoer){
        maakToken(kar);
    }

    
}


bool binaireBoom::leesIn (const char* invoerNaam){
    std::ifstream invoer;
    invoer.open(invoerNaam, std::ios::in);
    if (!invoer.is_open()){
        std::cout << std::endl << "Gegeven bestand is niet gevonden." << std::endl;


    }
    invoer.close();
    
    for (const std::string& w : woorden){
        std::cout << w << std::endl;
    }
}