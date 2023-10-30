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
        std::string waarde;
        binaireBoom boom;

        while (menu){
            std::cout << std::endl
            << "Kies een optie:" << std::endl
            << "* exp <expressie>" << std::endl
            << "* print " << std::endl
            << "* dot <bestandsnaam>" << std::endl
            << "* eval <waarde>" << std::endl
            << "* diff" << std::endl
            << "* simp" << std::endl
            << "* end " << std::endl << std:: endl;


            std::getline(std::cin, keuze);

            if (keuze.substr(0, 4) == "exp "){
                formule = keuze.substr(4);
                std::cout<<formule << std::endl;
                boom.maakBoomCall(formule);
            }else if (keuze == "print"){
                boom.printIOCall();
            }else if (keuze.substr(0, 4) == "dot "){
                uitvoer = keuze.substr(4);
                boom.printDOT(uitvoer);
            }else if( keuze.substr(0, 5) == "eval "){
                std::cout<<"nog niet geimplementeerd" << std::endl;
                // waarde = keuze.substr(6);
            }else if( keuze == "diff"){
                std::cout<<"nog niet geimplementeerd" << std::endl;
            }else if( keuze == "simp"){
                boom.vereenvoudigCall();

            }else if( keuze == "end"){
                menu = false;
            }else{
                std::cout << "Ongeldige instructie, probeer nog eens." << std::endl;
            }
        }

    return 0;
}
