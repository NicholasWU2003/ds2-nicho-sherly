#include <iostream>
#include <fstream>
#include <vector>
#include "helperfunctie.h"

std::string binaireBoom::enumToString(int type){
    switch (type){
        case Token::PLUS: return "+";
        case Token::MINUS: return "-";
        case Token::POWER: return "^";
        case Token::DIVIDE: return "/";
        case Token::TIMES: return "*";
        case Token::SINE: return "sin";
        case Token::COSINE: return "cos";
        case Token::TANGENT: return "tan";
        case Token::PI: return "pi";
        default: return "unknown";
    }
}

bool binaireBoom::maakToken(std::string kar){
    struct Token huidig;

    if (kar == "p"){
        huidig.type = Token::PI;
        huidig.variable = 'p';
    }
    else if (kar == "sin"){
        huidig.type = Token::SINE;
    }
    else if (kar == "cos"){
        huidig.type = Token::COSINE;
    }
    else if (kar == "tan"){
        huidig.type = Token::TANGENT;
    }
    else if (kar == "+"){
        huidig.type = Token::PLUS;
    }
    else if (kar == "-"){
        huidig.type = Token::MINUS;
    }
    else if (kar == "^"){
        huidig.type = Token::POWER;
    }
    else if (kar == "*"){
        huidig.type = Token::TIMES;
    }
    else if (kar == "/"){
        huidig.type = Token::DIVIDE;
    }
    else if((kar >= "a" && kar <= "z") || (kar >= "A" && kar <= "Z")){
        huidig.type = Token::VARIABLE;
        huidig.variable = kar[0];
    }
    else{ // kijken of het een getal is 
        try {
            double getal = std::stod(kar);
            huidig.type = Token::NUMBER;
            huidig.number = getal;
        }
        catch (const std::invalid_argument&){ // anders bestaat niet 
            std::cout << "dit:" << kar << "bestaat niet";
            return false; 

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
        if(!maakToken(element))
        {
            std::cout << "klopt niet" << std::endl;
        }
    }

    // Token temp = maakBoom(tokens[huidigTokenIndex]);
    // begin = &temp;
    Token* temp = maakBoom(tokens[huidigTokenIndex]);
    begin = temp;

    // std::cout << temp.links->type << std::endl;

    // huidigTokenIndex = 0;
    // printIO(temp);
    std::cout << "Inorder Traversal: ";
    printIO(begin);
    std::cout << std::endl;

    printDOT("testFile.dot");
    
}
 
std::vector<std::string> binaireBoom::leesIn(std::string invoerNaam){
    std::ifstream invoer;
    std::string huidig;
    std::vector<std::string> lijstje;
    
    invoer.open(invoerNaam, std::ios::in);
    if (!invoer.is_open()){
        std::cout << std::endl << "Gegeven bestand is niet gevonden." << std::endl;
        return(lijstje);
    }

    while (invoer >> huidig){
        lijstje.push_back(huidig);
    }

    invoer.close();

    return(lijstje);
    
}

Token* binaireBoom::maakBoom(Token token) {

    if (token.type == Token::NUMBER || token.type == Token::VARIABLE || token.type == Token::PI) {
        return new Token(token);
    }
    else if (token.type == 0 || token.type == 1 || token.type == 2 || token.type == 3 || token.type == 4) {
        huidigTokenIndex++;
        Token* temp1 = maakBoom(tokens[huidigTokenIndex]);
        token.links = temp1;

        huidigTokenIndex++;
        Token* temp2 = maakBoom(tokens[huidigTokenIndex]);
        token.rechts = temp2;

        return new Token(token);
    }
    else if (token.type == 5 || token.type == 6 || token.type == 7) {
        huidigTokenIndex++;
        Token* temp3 = maakBoom(tokens[huidigTokenIndex]);
        token.links = temp3;
        token.rechts = nullptr;
        return new Token(token);
    }

    return new Token(token);
}

void binaireBoom::printIO(Token* huidigeRoot) {
    if (huidigeRoot == nullptr) {
        return;
    }

    if(huidigeRoot->type == 5)
    {
        std::cout << enumToString(huidigeRoot->type) << "(";

    }
    if (huidigeRoot->type >= 0 && huidigeRoot->type <= 4 && huidigeRoot!=begin) {
        std::cout << "(";
    }
    // Traverse the left subtree (links)

    printIO(huidigeRoot->links);

    // Print the current token's value (assuming Token has a value field)
    if(huidigeRoot->type == 9){
        std::cout << huidigeRoot->number;

    }
    else if (huidigeRoot->type == 10){
        std::cout << huidigeRoot->variable;
    }
    else{
        if(huidigeRoot->type != 5){
            std::cout << enumToString(huidigeRoot->type);
        }
    }

    // Traverse the right subtree (rechts)
    printIO(huidigeRoot->rechts);

    // begin->type == 9 || begin->type == 10 || 
    if (huidigeRoot->type >= 0 && huidigeRoot->type <= 4&& huidigeRoot!=begin) {
        std::cout << ")";
    }

    if(huidigeRoot->type == 5 || huidigeRoot->type == 6 || huidigeRoot->type == 7)//sin cos tan
    {
        std::cout << ")";

    }
}

void  binaireBoom::printDOT(const std::string& uitvoerNaam){
    std::ofstream dotFile(uitvoerNaam);

    if (!dotFile) {
        std::cerr << "Kan niet wegschrijven!" << std::endl;
        return;
    }

    dotFile << "digraph G {\n" << std::endl;
    printHelpDOT(begin, dotFile);
    dotFile << "}\n";

    dotFile.close();

}

void binaireBoom::printHelpDOT(Token* token, std::ofstream& dotFile){
    if (!token){
        return;
    }

    int telHuidig = telDOT++;
    int telLinks;
    int telRechts;

    if (token->links) {
        telLinks = telDOT;
        // huidig
        dotFile << telHuidig << "  [label = \" "<< plaatsToken(token) <<  " \" ]" <<  std::endl;
        //links 
        dotFile << telLinks << "  [label = \" "<< plaatsToken(token->links) <<  " \" ]" << std::endl;
        dotFile << telHuidig << " -> " << telLinks  << std::endl;
        printHelpDOT(token->links, dotFile);
    }
    if (token->rechts) {
        telRechts = telDOT;
        dotFile << telRechts << "   [label = \" "<< plaatsToken(token->rechts) <<  " \" ]" << std::endl;
        dotFile << telHuidig << " -> " << telRechts  << std::endl;
        printHelpDOT(token->rechts, dotFile);
    }
}

std::string binaireBoom::plaatsToken(Token* token){
    if (!token) return "";

    if (token->type == Token::NUMBER) {
        double getal = token->number;
        std::cout << getal<< "dit is getal" <<  std::endl;
        return std::to_string(getal);
    } else if (token->type == Token::VARIABLE) {
        return std::string(1, token->variable);
    } else {
        return enumToString(token->type);
    }

}

