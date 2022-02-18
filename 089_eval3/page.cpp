#include "page.h"

/********************************************************************************
Description: read one page from the input file
Input: fileName -> name of the input file
Return: bool
********************************************************************************/
bool Page::readPage(char * fileName) {
    bool reachText = false; //show if '#' is encountered
    std::ifstream infile;
    infile.open(fileName);
    if(!infile.good()) {return false;}
    while(!infile.eof()) {
        std::string str;
        std::getline(infile, str);
        if (str.front() == '#') {
            reachText = true;
            continue;
        }
        if(!reachText) {
            if(isalnum(str.front())) {
                if(isdigit(str.front())) {readChoice(str);}
                else {readResult(str);}
            }
            else {HandError("invalid file format -- choice section");}
        }
        else {
            text += str;
            text += '\n';
        }
    }
    if(reachText == false) {HandError("invalid file format -- No '#' exist");}
    infile.close();
    return true;
}

/********************************************************************************
Description: read and parse a choice from the string read from the input file
Input: str -> a string read from the input file
Return: void
********************************************************************************/
void Page::readChoice(std::string str) {
    result = false; //set choice pages' result as false
    size_t ind = str.find(':');
    if(ind != -1) {
        //read page number
        std::string pageNum = str.substr(0, ind);
        for (size_t i = 0; i < ind; i++) {
            if (isdigit(pageNum[i]) == 0) {
                HandError("invalid file format -- choice page number invalid");
            }
        }
        unsigned num = (unsigned)atoi(pageNum.c_str());
        if (num == 0) {HandError("invalid file format -- choice page number can't be 0");};
        //read choice content
        std::string choiceCont = str.substr(ind + 1);
        std::pair<unsigned, std::string> choice(num, choiceCont);
        choices.push_back(choice);
    }
    else { //can't find ':'
        HandError("invalid file format -- choice section require ':'");
    }
}

/********************************************************************************
Description: read the result of a page --> WIN or LOSE
Input: str -> a string read from the input file
Return: void
********************************************************************************/
void Page::readResult(std::string str) {
    if(str == "WIN") {result = true;}
    else if(str == "LOSE") {result = false;}
    else {
        HandError("invalid file format -- WIN/LOSE section");
    }
}

/********************************************************************************
Description: print a page using specified format
Return: void
********************************************************************************/
void Page::printPage() {
    std::cout << text;
    if(!choices.empty()) { //choice page
        std::cout << "What would you like to do?" << std::endl;
        std::cout << std::endl;
        for(size_t i = 0; i < choices.size(); i++) {
            std::cout << " " << i+1 << ". " << choices[i].second << std::endl;
        }
    }
    else { //WIN or LOSE page
        if(result) {std::cout << "Congratulations! You have won. Hooray!" << std::endl;}
        else {std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;}
    }
}

/********************************************************************************
Description: handle the error encounted
Input: errorInfo -> the error information that needs to be printed
Return: void
********************************************************************************/
void HandError(std::string errorInfo){
    std::cerr << errorInfo << std::endl;
    exit(EXIT_FAILURE);
}
