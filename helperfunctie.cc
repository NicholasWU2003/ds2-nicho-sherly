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
                huidig.type = Token::SINE;
            }
            else if(kar == "cos"){
                huidig.type = Token::COSINE;
            }
            else if(kar == "tan"){
                huidig.type = Token::TANGENT;
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
            else if(kar == "p"){
                huidig.type = Token::PI;
                huidig.variable = 'p';
            }
            else if((kar >= "a" && kar <= "z") || (kar >= "A" && kar <= "Z"))
            {
                huidig.type = Token::VARIABLE;
                huidig.variable = kar[0];
            }
            else if(kar == "(")
            {
                haakjes = true;
            }
            else if (kar == ")")
            {
                if (!haakjes)
                {
                    std::cout << "invoer klopt niet" << std::endl;
                    return;
                }
                 haakjes = false;
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


bool binaireBoom::leesIn (std::string invoerNaam){
    std::ifstream invoer;
    invoer.open(invoerNaam, std::ios::in);
    if (!invoer.is_open()){
        std::cout << std::endl << "Gegeven bestand is niet gevonden." << std::endl;


    }
    invoer.close();
    

}
// kijken of alles goed wordt gemaakt 
void binaireBoom::printTokens() const {
    for (const auto& token : tokens) {
        switch (token.type) {
        case Token::NUMBER:
            std::cout << "Number: " << token.number << std::endl; // 8
            break;
        case Token::SINE://10
            std::cout << "Sine" << std::endl;
            break;
        case Token::COSINE://11
            std::cout << "Cosine" << std::endl;
            break;
        case Token::TANGENT://12
            std::cout << "Tangent" << std::endl;
            break;
        case Token::PLUS:
            std::cout << "Plus" << std::endl; // 0
            break;
        case Token::MINUS:
            std::cout << "Minus" << std::endl; // 1
            break;
        case Token::POWER: //2
            std::cout << "Power" << std::endl;
            break;
        case Token::TIMES://4
            std::cout << "Times" << std::endl;
            break;
        case Token::PI:// 7
            std::cout << "Pi: " << token.variable << std::endl;
            break;
        case Token::VARIABLE: //9
            std::cout << "Variable: " << token.variable << std::endl;
            break;
        default:
            std::cout << "Unknown token" << std::endl;
        }
    }
    for (const auto& token : tokens) 
    {
        std::cout<<token.type << std::endl;
    }

}


void binaireBoom::maakBoom()
{
    std::vector<Token*> values;
    std::vector<Token*> operators;
    Token token;

    if (token.type == 8 || token.type == 9 )
    {//numbers and pi

    }
    else 
    {//alle andere idk

    }




}