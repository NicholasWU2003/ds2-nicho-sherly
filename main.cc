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

int main(){
  
        std::string invoerNaam;
        std::cout << "Geef de naam van het bestand: " << std::endl;
        binaireBoom boom("test.txt");
        bool menu = true;
        char keuze = ' ';

        while(menu){
            std::cout << "[E]xp [P]rint [D]ot e[N]d" << std::endl;
            std::cin >> keuze;
            switch (keuze){
                case 'e':
                case 'E':
                    // boom = binaireBoom("test.txt");
                    break;
                case 'p':
                case 'P':
                    boom.printIOCall();
                    break;
                case 'd':
                case 'D':
                    break;
                case 'n':
                case 'N':
                    menu = false;
            }
        }

    return 0;
}