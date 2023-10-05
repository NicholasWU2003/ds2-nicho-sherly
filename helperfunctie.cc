#include <iostream>
#include <fstream>
#include <vector>
#include "helperfunctie.h"




std::vector<Token> binaireBoom::leesIn (const char* invoerNaam)
{
    std::vector<Token> tokens;

    std::ifstream invoer;
    invoer.open(invoerNaam, std::ios::in);
        

        std:: string huidig;
        Token token;

        while (invoer >> huidig){
        
          if (huidig == " ")
          {// spaties overslaan
            continue;
          }
          else if (huidig == "+")
          {
            token.type = Token::PLUS;
            tokens.push_back(token);
          }
          else if (huidig == "-")
          {
            token.type = Token::MINUS;
            tokens.push_back(token);
          }
          else if (huidig == "*")
          {
            token.type = Token::MULTIPLY;
            tokens.push_back(token);
          }
          else if (huidig == "/")
          {
            token.type = Token::DIVIDE;
            tokens.push_back(token);
          }
          else if (huidig >= "a" && huidig <= "z")
          {
            token.type = Token::VARIABLE;
            tokens.push_back(token);
          }
          else if (huidig >= "1" && huidig <= "9")
          {// idk als huidig bv 386 is herkent die dat?
            token.type = Token::NUMBER;
            tokens.push_back(token);
          }
          else if (huidig == "cos")
          {
            token.type = Token::COSINE;
            tokens.push_back(token);
          }
          else if (huidig == "sin")
          {
            token.type = Token::SINE;
            tokens.push_back(token);
          }
          else if (huidig == "tan")
          {
            token.type = Token::TANGENT;
            tokens.push_back(token);
          }
          else
          {
            std::cout << "de formule klopt niet!" << std::endl;
            break;
          }


        }

        invoer.close();
    
    return tokens;
}

std::string binaireBoom::drukaf1()
{
  int grootte = elementen.size();



}