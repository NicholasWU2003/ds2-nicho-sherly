#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
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

    if (kar == "pi"){
        huidig.type = Token::PI;
        huidig.variable = 'p';
        huidig.number = 3.141592;
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

binaireBoom::binaireBoom(){
    begin = nullptr;
    telDOT = 1;
    huidigTokenIndex = 0;

}

// binaireBoom::binaireBoom(std::string invoerNaam){
    
//     std::vector<std::string> invoer = leesIn(invoerNaam);
//     huidigTokenIndex = 0;
//     telDOT = 1;

//     for(const std::string &element : invoer){
//         if(!maakToken(element))
//         {
//             std::cout << "klopt niet" << std::endl;
//         }
//     }

//     Token* temp = maakBoom(tokens[huidigTokenIndex]);
//     begin = temp;

//     // std::cout << "begin type: " << begin->type << std::endl;
    
// }

binaireBoom::~binaireBoom(){
    if(!tokenPtrs.empty()){
        for(Token* huidig:tokenPtrs){
            verwijderBoom(huidig);
        }
    }

}

void binaireBoom::verwijderBoom(Token* token){

    if(token == nullptr){
        return;
    }
    verwijderBoom(token->links);
    verwijderBoom(token->rechts);

    delete token;

}
 
std::vector<std::string> binaireBoom::leesIn(std::string formule){
    std::string huidig;
    std::vector<std::string> lijstje;
    std::stringstream invoer(formule);
    
    while (invoer >> huidig){
        lijstje.push_back(huidig);
    }

    return(lijstje);
    
}

void binaireBoom::maakBoomCall(std::string formule){
    tokens.clear();

    std::vector<std::string> invoer = leesIn(formule);
    huidigTokenIndex = 0;
    telDOT = 1;

    for(const std::string &element : invoer){
        if(!maakToken(element))
        {
            std::cout << "klopt niet" << std::endl;
        }
    }

    Token* temp = maakBoom(tokens[huidigTokenIndex]);
    begin = temp;
    tokenPtrs.push_back(begin);
}

Token* binaireBoom::maakBoom(Token token){

    if (token.type >= 8 && token.type <= 10){
        token.links = nullptr;
        token.rechts = nullptr;

        return new Token(token);
    }
    else if (token.type >= 0 && token.type <= 4){
        huidigTokenIndex++;
        Token* temp1 = maakBoom(tokens[huidigTokenIndex]);
        token.links = temp1;

        huidigTokenIndex++;
        Token* temp2 = maakBoom(tokens[huidigTokenIndex]);
        token.rechts = temp2;

        return new Token(token);
    }
    else if (token.type >= 5 && token.type <= 7){
        huidigTokenIndex++;
        Token* temp3 = maakBoom(tokens[huidigTokenIndex]);
        token.links = temp3;
        token.rechts = nullptr;
        return new Token(token);
    }

    delete token.links;
    delete token.rechts;
    return new Token(token);
}

void binaireBoom::printIOCall(){

    if(begin != nullptr){
        printIO(begin);

    }
    else{
        std::cout << "There is no tree";
    }
    std::cout << std::endl;

}

void binaireBoom::printIO(Token* huidigeRoot){

    if(huidigeRoot == nullptr){
        return;
    }

    if(huidigeRoot->type >= 5 && huidigeRoot->type <= 7){ // sin cos tan als eerst printen
        std::cout << enumToString(huidigeRoot->type) << "(";

    }
    else if(huidigeRoot->type >= 0 && huidigeRoot->type <= 4 && huidigeRoot!=begin){
        std::cout << "(";
    }

    // naar linker node
    printIO(huidigeRoot->links);

    // print the token
    if(huidigeRoot->type == 9){
        std::cout << huidigeRoot->number;
    }
    else if (huidigeRoot->type == 10){
        std::cout << huidigeRoot->variable;
    }
    else{
        if(huidigeRoot->type < 5 || huidigeRoot->type > 7){
            std::cout << enumToString(huidigeRoot->type);
        }
    }

    // naar rechter node
    printIO(huidigeRoot->rechts);

    if(huidigeRoot->type >= 0 && huidigeRoot->type <= 4 && huidigeRoot!=begin){
        std::cout << ")";
    }
    else if(huidigeRoot->type >= 5 && huidigeRoot->type <= 7){ // sin cos tan altijd haakje dicht
        std::cout << ")";
    }

}



void  binaireBoom::printDOT(const std::string& uitvoerNaam){
    std::ofstream dotFile(uitvoerNaam);

    if(!dotFile){
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

    if(token->links){
        telLinks = telDOT;
        // huidig
        dotFile << telHuidig << "  [label = \" "<< plaatsToken(token) <<  " \" ]" <<  std::endl;
        //links 
        dotFile << telLinks << "  [label = \" "<< plaatsToken(token->links) <<  " \" ]" << std::endl;
        dotFile << telHuidig << " -> " << telLinks  << std::endl;
        printHelpDOT(token->links, dotFile);
    }
    if(token->rechts){
        telRechts = telDOT;
        dotFile << telRechts << "   [label = \" "<< plaatsToken(token->rechts) <<  " \" ]" << std::endl;
        dotFile << telHuidig << " -> " << telRechts  << std::endl;
        printHelpDOT(token->rechts, dotFile);
    }
}

std::string binaireBoom::plaatsToken(Token* token){
    if (!token) return "";

    if (token->type == Token::NUMBER) {
        // haalt de extra decimalen weg
        std::string nummer = std::to_string(token->number);
        // als . gevonden checken of laaste kar een 0 is of een . zo ja dan weg halen 
        while (nummer.find('.') != std::string::npos && (nummer.back() == '0' || nummer.back() == '.')) {
            nummer.pop_back();
        }
        return nummer;
    }
     else if (token->type == Token::VARIABLE) {
        return std::string(1, token->variable);
    } else {
        return enumToString(token->type);
    }

}

Token* binaireBoom::simplify(Token* token) {
    if(!token){
        return nullptr;
    }

    // Recursively simplify the left and right subtrees
    token->links = simplify(token->links);
    token->rechts = simplify(token->rechts);

    // Simplification rules go here
    if(token->type == Token::PLUS){
        if (token->links && token->links->type == Token::NUMBER &&
            token->rechts && token->rechts->type == Token::NUMBER) {
            // Simplify addition of two constants
            token->number = token->links->number + token->rechts->number;
            delete token->links;
            delete token->rechts;
            token->links = nullptr;
            token->rechts = nullptr;
            token->type = Token::NUMBER;
        }
    }
    else if (token->type == Token::MINUS){
        if(token->links && token->links->type == Token::NUMBER &&
            token->rechts && token->rechts->type == Token::NUMBER) {
            // Simplify subtraction of two constants
            token->number = token->links->number - token->rechts->number;
            delete token->links;
            delete token->rechts;
            token->links = nullptr;
            token->rechts = nullptr;
            token->type = Token::NUMBER;
        }
        else if(token->links->type == Token::VARIABLE && token->rechts->type == Token::VARIABLE){

            if(token->links->variable == token->rechts->variable){

                token->type = Token::NUMBER;  
                token->number = 0;  
                
                delete token->links;
                delete token->rechts;
                token->links = nullptr;
                token->rechts = nullptr;

                return token;
            }
        }

    }
    else if(token->type == Token::TIMES){

        if(token->links && token->links->type == Token::NUMBER &&
            token->rechts && token->rechts->type == Token::NUMBER){
            // Simplify multiplication of two constants
            token->number = token->links->number * token->rechts->number;
            delete token->links;
            delete token->rechts;
            token->links = nullptr;
            token->rechts = nullptr;
            token->type = Token::NUMBER;
        }
    }
    else if(token->type == Token::DIVIDE){
        
        if(token->links && token->links->type == Token::NUMBER &&
            token->rechts && token->rechts->type == Token::NUMBER && token->rechts->number != 0){
            // Simplify division of two constants (excluding division by zero)
            token->number = token->links->number / token->rechts->number;
            delete token->links;
            delete token->rechts;
            token->links = nullptr;
            token->rechts = nullptr;
            token->type = Token::NUMBER;
        }
        else if(token->links->type == Token::VARIABLE && token->rechts->type == Token::VARIABLE){
            
            if(token->links->variable == token->rechts->variable){

                token->type = Token::NUMBER;  
                token->number = 1;
            
                delete token->links;
                delete token->rechts;
                token->links = nullptr;
                token->rechts = nullptr;

                return token;
            }
        }
        else{ // als delen door 0
            std::cout << "delen door nul is flauwekul"<< std::endl
            << " herschrijf de expressie "<< std::endl;
        }
    }
    else if(token->type == Token::SINE){
        if(token->links && (token->links->type == Token::NUMBER || token->links->type == Token::PI)){
            if (token->links->number == 0 || bijnaGelijk(token->links->number, 3.141592)){
                token->type = Token::NUMBER;
                token->number = 0;
                delete token->links;
                token->links = nullptr;
                return token;
            }
        }
    } 
    else if(token->type == Token::COSINE){
        if(token->links && (token->links->type == Token::NUMBER || token->links->type == Token::PI)){
            if (token->links->number == 0){
                token->type = Token::NUMBER;
                token->number = 1;
            }
            else if(bijnaGelijk(token->links->number, 3.141592)){
                token->type = Token::NUMBER;
                token->number = -1;

            }
            delete token->links;
            token->links = nullptr;
            return token;
        }
    } 
    else if(token->type == Token::TANGENT){
        if(token->links && token->links->type == Token::NUMBER){
            if (token->links->number == 0 || bijnaGelijk(token->links->number, 3.141592)){
                token->type = Token::NUMBER;
                token->number = 0;
                delete token->links;
                token->links = nullptr;
                return token;
            }
        }
    }
    else if(token->type == Token::POWER){
        if(token->rechts->type == Token::NUMBER && token->rechts->number == 0){
            token->type = Token::NUMBER;
            token->number = 1;

            delete token->links;
            delete token->rechts;
            token->links = nullptr;
            token->rechts = nullptr;

            return token;
        }
        if(token->rechts && token->rechts->type == Token::NUMBER && token->rechts->number == 1){

            // Token* hulp = token->links;
            // delete token->rechts;
            // token->rechts = nullptr;
            // token = hulp;
            // delete hulp;
            
            // return token;
// -------------------------------------
            // Token* temp = token->links;
            // token = temp;
            // token->links = temp->links;
            // token->rechts = temp->rechts;

            // delete temp;
            
            // return token;
        }
    }

    // Return the token if no simplifications were applied
    return token;
}


void binaireBoom::vereenvoudigCall(){
    if(begin != nullptr){        
        simplify(begin);
    }
    else{
        std::cout << "There is no tree";
    }
    std::cout << std::endl;
}

void binaireBoom::evalCall(double waarde){
    if(begin != nullptr){        
        evalueer(begin, waarde);
        simplify(begin);
    }
    else{
        std::cout << "There is no tree";
    }
    std::cout << std::endl;
}

void binaireBoom::evalueer(Token* token, double waarde){
    if (!token) return;

    if (token->type == Token::VARIABLE && token->variable == 'x') {
        token->type = Token::NUMBER;
        token->number = waarde;
    }

    evalueer(token->links, waarde);
    evalueer(token->rechts, waarde);
}

//  ________  cursor parkeerplek
// |        | 
// |        |
// |________|

Token* binaireBoom::differentieer(Token* token) {
    std::cout<<"diffcal"<<std::endl;
    std::cout << "Token: " << token << std::endl;
    if (!token){
        return nullptr;
    }

    if (token->type == Token::NUMBER){//constante
        std::cout<<"ik komhier 1" << std::endl;
        Token* hulp = new Token();
        hulp->type = Token::NUMBER;
        hulp->number = 0;
        return hulp;
    }
    if (token->type == Token::VARIABLE && token->variable == 'x'){//variabele
        Token* hulp = new Token();
        hulp->type = Token::NUMBER;
        hulp->number = 1;
        return hulp;
    }
    if (token->type == Token::VARIABLE && token->variable == 'x'){//variabele is x 
        Token* hulp = new Token();
        hulp->type = Token::NUMBER;
        hulp->number = 1;
        return hulp;
    }
    if (token->type == Token::VARIABLE && token->variable != 'x'){//variabele is niet x 
        Token* hulp = new Token();
        hulp->type = Token::NUMBER;
        hulp->number = 0;
        return hulp;
    }
    // if (token->type == Token::POWER){// macht met constante
    //     token->links 
    //     Token* hulp = new Token();
    //     hulp->type = Token::NUMBER;
    //     hulp->number = 1;
    //     return hulp;
    // }


}

void binaireBoom::diffCall()
{
    if(begin != nullptr){        
        differentieer(begin);
    }
    else{
        std::cout << "There is no tree";
    }
    std::cout << std::endl;
}




bool binaireBoom::bijnaGelijk(double a, double b) {
    const double EPSILON = 1e-9;
    return std::abs(a - b) < EPSILON;
}

