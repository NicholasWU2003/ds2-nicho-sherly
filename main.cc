#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "helperfunctie.h"
int main(int argc, char** argv) {
    bool debugMode = false;
    std::string filename;

    if (argc >= 3) {
        if (std::string(argv[1]) == "d"){
            debugMode = true;
            filename = argv[2];
            std::cout<<"debugMode ingeschakeld"<<std::endl;
        }
        
    }

    std::ifstream file;
    if (!filename.empty()){
        file.open(filename);
        if (!file.is_open()){
            std::cerr << "Bestand niet gevonden: " << filename << std::endl;
            return 1;
        }
    }

    bool menu = true;
    std::string keuze;
    double waarde;
    binaireBoom boom;

    while (menu) {
        if (!debugMode) {
            std::cout << std::endl
            << "Kies een optie:" << std::endl
            << "* exp <expressie>" << std::endl
            << "* print " << std::endl
            << "* dot <bestandsnaam>" << std::endl
            << "* eval <waarde>" << std::endl
            << "* diff" << std::endl
            << "* simp" << std::endl
            << "* end " << std::endl
            << std::endl;
        }

        std::string line;

        if (file.is_open() && std::getline(file, line)){
            keuze = line;
            // std::cout << keuze << std::endl;
        }
        else if (!debugMode){
            std::getline(std::cin, keuze);
        }
        
        // std::cout << keuze << std::endl;
        
        if (keuze.substr(0, 4) == "exp ") {
            std::string formule = keuze.substr(4);
            boom.maakBoomCall(formule);
        } else if (keuze.substr(0, 5) == "print") {
            boom.printIOCall();
        } else if (keuze.substr(0, 4) == "dot ") {
            std::string uitvoer = keuze.substr(4);
            boom.printDOT(uitvoer);
        } else if (keuze.substr(0, 5) == "eval ") {
            waarde = std::stod(keuze.substr(5));
            boom.evalCall(waarde);
        } else if (keuze.substr(0, 4) == "diff") {
            boom.diffCall();
        } else if (keuze.substr(0, 4) == "simp") {
            boom.vereenvoudigCall();
        } else if (keuze == "end") {
            menu = false;
        } else {
            std::cout << "Ongeldige instructie, probeer nog eens." << std::endl;
        }


    }

    if (file.is_open()) {
        file.close();
    }

    return 0;
}