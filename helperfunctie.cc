#include <iostream>
#include <fstream>
#include <vector>
#include "helperfunctie.h"




bool binaireBoom::leesIn (const char* invoerNaam)
{
    std::ifstream invoer;
    invoer.open(invoerNaam, std::ios::in);
        if (!invoer.is_open())
        {
            std::cout << std::endl << "Gegeven bestand is niet gevonden." << std::endl;

            return false;
        }
        std::vector<std::string> woorden;
        std:: string woord;

        while (invoer >> woord){
            woorden.push_back(woord);
        }

        invoer.close();
    
    for (const std::string& w : woorden) 
    {
        std::cout << w << std::endl;
    }
        
}