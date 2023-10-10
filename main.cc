#include <iostream>
#include <fstream>
#include <vector>
#include "helperfunctie.h"

// instructies:
    // exp <expressie>
    // print
    // dot <bestandsnaam> 
    // end

    // evaluate < waarde>
    // differentieert
    // simpligy



// inlezen vanuit een .txt bestand
// 
// prefix notatie
// karakters worden gescheiden met een spatie
// 
// 
// 

#include <iostream>
#include <vector>

int main(){

        binaireBoom boom;
        std::string invoerNaam;
        std::cout << "Geef de naam van het bestand: " << std::endl;
        std::cin >> invoerNaam;
        boom.leesIn(invoerNaam);

        boom.printTokens();

    return 0;
}