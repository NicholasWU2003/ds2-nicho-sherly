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
    else if (kar >= "0" && kar <= "9"){
        try{
            int getal = std::stoi(kar);
            huidig.type = Token::NUMBER;
            huidig.number = getal;
        }
        catch (const std::invalid_argument&){
            try{
                double dGetal = std::stod(kar);
                huidig.type = Token::NUMBER;
                huidig.number = dGetal;
            }
            catch (const std::invalid_argument&){
                return false; // kar is not a valid number
            }
        }
    }
    else if((kar >= "a" && kar <= "z") || (kar >= "A" && kar <= "Z")){
        huidig.type = Token::VARIABLE;
        huidig.variable = kar[0];
    }
    else{
        std::cout << "dit:" << kar << "bestaat niet";
        return false; // kar doesn't match any known token type
    }

    tokens.push_back(huidig);
    return true;
}


binaireBoom::binaireBoom(){}

binaireBoom::binaireBoom(std::string invoerNaam){
    
    std::vector<std::string> invoer = leesIn(invoerNaam);
    huidigTokenIndex = 0;
    haakje = 0;

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


// Token binaireBoom::maakBoom(Token token)// + * 1 23
// {   
//     if(token.type == Token::NUMBER|| token.type == Token::VARIABLE || token.type == Token::PI){//NUMMER && PI & variable
//         return(token);
//     }
//     else if(token.type == 0 || token.type == 1 || token.type == 2 ||token.type == 3 || token.type == 4){ // plus min keer delen macht
//         huidigTokenIndex++;// volgende
//         Token temp = maakBoom(tokens[huidigTokenIndex]);
//         token.links = &temp;

//         huidigTokenIndex++;
//         temp = maakBoom(tokens[huidigTokenIndex]);
//         token.rechts = &temp;
        
//         return(token);
//     }
//     else if (token.type == 10 || token.type == 11 || token.type == 12){ // cos sin tan
//         huidigTokenIndex++;
//         Token temp = maakBoom(tokens[huidigTokenIndex]);
//         token.links = &temp;
//         return(token);
//     }

//     return(token);
// }

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


// void binaireBoom::printIO(Token token){
//     // stel eerste is een nummer toch
//     // dan gaat de functie niet meer verder

//     if (token.type == Token::NUMBER) {

//         huidigTokenIndex++;
//         // printIO(tokens[huidigTokenIndex]); 

//     }

//     else if (token.type == Token::VARIABLE || token.type == Token::PI) {
//         std::cout << token.variable;
//         huidigTokenIndex++;

//         // printIO(tokens[huidigTokenIndex]);
//     }

//     else if(token.type == Token::PLUS || token.type == Token::MINUS || token.type == Token::POWER || token.type == Token::TIMES){ 
//         std::cout << "(";
//         // std::cout<< huidigTokenIndex << std::endl;
//         huidigTokenIndex++;// volgende
//         printIO(tokens[huidigTokenIndex]);
        
//        switch (token.type) {
//             case Token::PLUS: std::cout << "+"; break;
//             case Token::MINUS: std::cout << "-"; break;
//             case Token::POWER: std::cout << "^"; break;
//             case Token::TIMES: std::cout << "*"; break;
//             default:break;
//        }


//         huidigTokenIndex++;
//         printIO(tokens[huidigTokenIndex]);

//         std::cout << ")";

//     }
//     else if (token.type == Token::SINE || token.type == Token::COSINE || token.type == Token::TANGENT){ 

//         std::cout << "";
//         switch (token.type) {// sotp met typen //ik typte niet eens en maak die terminal write ik kan er niet in . dankje
//                 case Token::SINE: std::cout << "sin("; break;
//                 case Token::COSINE: std::cout << "cos("; break;
//                 case Token::TANGENT: std::cout << "tan("; break;
//                 default: break;//dit kreefg ik dus de hele tijd wtf okeeeeeeeeeee wacht ff sitnkaap
//             }

//         huidigTokenIndex++;
//         printIO(tokens[huidigTokenIndex]);
//         std::cout << ")";
//     }

// }

void binaireBoom::printIO(Token* begin) {
    if (begin == nullptr) {
        return;
    }

    if(begin->type == 5)
    {
        std::cout << enumToString(begin->type) << "(";
        haakje++;

    }
    // Traverse the left subtree (links)
    printIO(begin->links);

    // Print the current node's value (assuming Token has a value field)
    if(begin->type == 9){
        std::cout << begin->number << " ";

    }
    else if (begin->type == 10){
        std::cout << begin->variable << " ";
    }
    else{
        if(begin->type != 5){
            std::cout << enumToString(begin->type) << " ";
        }
    }

    // Traverse the right subtree (rechts)
    printIO(begin->rechts);

    if(haakje>0){
        std::cout << ") ";
        haakje--;
    }
}

// void binaireBoom::printIO(Token token){

//     if (token.type == Token::NUMBER) {
        
//         std::cout << token.number;
//         return;

//     }
//     else if (token.type == Token::VARIABLE || token.type == Token::PI) {
//         std::cout << token.variable;
//         return;
//     }
//     else if(token.type == Token::PLUS || token.type == Token::MINUS 
//                 || token.type == Token::POWER || token.type == Token::TIMES 
//                 || token.type == Token::TIMES){ 

//         std::cout << "(";

//         if(token.links != nullptr)
//         {
//             Token temp = *(token.links);

//             printIO(temp);
//         }

        
//        switch (token.type) {
//             case Token::PLUS: std::cout << "+"; break;
//             case Token::MINUS: std::cout << "-"; break;
//             case Token::POWER: std::cout << "^"; break;
//             case Token::DIVIDE: std::cout << "/"; break;
//             case Token::TIMES: std::cout << "*"; break;
//             default:break;
//        }

//         huidigTokenIndex++;

//         if(token.rechts != nullptr)
//         {
//             Token temp = *(token.rechts);
//             printIO(temp);
//         }

//         std::cout << ")";
//         return;

//     }
//     else if (token.type == Token::SINE || token.type == Token::COSINE || token.type == Token::TANGENT){ 

//         std::cout << "";
        
//         switch (token.type) {
//                 case Token::SINE: std::cout << "sin("; break;
//                 case Token::COSINE: std::cout << "cos("; break;
//                 case Token::TANGENT: std::cout << "tan("; break;
//                 default: break;
//             }

//         if(token.links != nullptr)
//         {
//             Token temp = *(token.links);
//             printIO(temp);
//         }

//         std::cout << ")";
//         return;
//     }

// }
