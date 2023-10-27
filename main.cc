#include <iostream>
#include <fstream>
#include <sstream>
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

int main(){
        bool menu = true;
        std::string bestandsnaam;
        std::string uitvoer;
        std::string formule;
        std::string keuze;
        binaireBoom boom;
        
        while (menu){
            std::cout << std::endl
            << "Kies een optie:" << std::endl
            << "* exp <expressie>" << std::endl
            << "* print " << std::endl
            << "* dot <bestandsnaam>" << std::endl
            << "* end " << std::endl << std:: endl;

            std::getline(std::cin, keuze);

            if (keuze.substr(0, 4) == "exp "){
                formule = keuze.substr(5);
                boom.maakBoomCall(formule);
            }else if (keuze == "print"){
                boom.printIOCall();
            }else if (keuze.substr(0, 4) == "dot "){
                uitvoer = keuze.substr(5);
                boom.printDOT(uitvoer);
            }else if( keuze == "end"){
                menu = false;
            }else{
                std::cout << "Ongeldige instructie, probeer nog eens." << std::endl;
            }
        }

    return 0;
}