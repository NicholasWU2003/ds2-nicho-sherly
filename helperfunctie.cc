#include <iostream>
#include <fstream>
#include <vector>
#include "helperfunctie.h"

bool binaireBoom::maakToken(std::string kar){
    struct Token huidig;

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

            try{

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
                else if(kar == "/"){
                    huidig.type = Token::DIVIDE;
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
            
            }catch(const std::invalid_argument&){
                return false;
            }   
        }
    }

    tokens.push_back(huidig);
    return true;
}


binaireBoom::binaireBoom(){}

binaireBoom::binaireBoom(std::string invoerNaam){
    
    std::vector<std::string> invoer = leesIn(invoerNaam);
    huidigTokenIndex = 0;
    for(const std::string element : invoer){
        maakToken(element);
    }

    Token temp = maakBoom(tokens[huidigTokenIndex]);
    begin = &temp;

    printIO(temp);
    
}
 
std::vector<std::string> binaireBoom::leesIn(std::string invoerNaam){
    std::ifstream invoer;
    std::string huidig;
    std::vector<std::string> lijstje;
    
    invoer.open(invoerNaam, std::ios::in);
    if (!invoer.is_open()){
        std::cout << std::endl << "Gegeven bestand is niet gevonden." << std::endl;
      
    }

    while (invoer >> huidig){
        lijstje.push_back(huidig);
    }

    invoer.close();

    return(lijstje);
    
}

Token binaireBoom::maakBoom(Token token)// + * 1 23
{   
    if(token.type  == 8 || token.type == 7 || token.type == 9){//NUMMER && PI & variable
        return(token);
    }
    else if(token.type == 0 || token.type == 1 || token.type ==2 || token.type == 4){ // plus min keer macht
        huidigTokenIndex++;// volgende
        Token temp = maakBoom(tokens[huidigTokenIndex]);
        token.links = &temp;
        huidigTokenIndex++;
        temp = maakBoom(tokens[huidigTokenIndex]);
        token.rechts = &temp;
        return(token);
    }
    else if (token.type == 10 || token.type == 11 || token.type == 12){ // cos sin tan
        huidigTokenIndex++;
        Token temp = maakBoom(tokens[huidigTokenIndex]);
        token.links = &temp;
        return(token);
    }

    return(token);
}




void binaireBoom::printIO(Token token){

    if(token.type  == 8 || token.type == 7 || token.type == 9){//NUMMER && PI & variable
    
        std::cout << tokens[huidigTokenIndex].variable;
        std::cout << tokens[huidigTokenIndex].number;
        return;

    }
    else if(token.type == 0 || token.type == 1 || token.type ==2 || token.type == 4){ // plus min keer macht
        std::cout << "(";
        huidigTokenIndex++;// volgende
        printIO(tokens[huidigTokenIndex]);
        
       switch (token.type) {
            case 0: std::cout << "+"; break;
            case 1: std::cout << "-"; break;
            case 2: std::cout << "^"; break;
            case 4: std::cout << "*"; break;
       }

        huidigTokenIndex++;
        printIO(tokens[huidigTokenIndex]);
        std::cout << ")";

    }
    else if (token.type == 10 || token.type == 11 || token.type == 12){ // cos sin tan

        std::cout << "";
        switch (token.type) {
                case 10: std::cout << "sin("; break;
                case 11: std::cout << "cos("; break;
                case 12: std::cout << "tan("; break;
            }

        huidigTokenIndex++;
        printIO(tokens[huidigTokenIndex]);
        std::cout << ")";
    }

}