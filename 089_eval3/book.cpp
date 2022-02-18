#include "book.h"

/********************************************************************************
Description: read all consecutive pages in a directory
Input: path -> the directory name
Return: void
********************************************************************************/
void Book::readPages(char * path) {
    size_t i = 1; //a flag to represent current page number
    while(true) {
        Page page;
        std::stringstream ss;
        ss << path << "/page" << std::to_string(i) << ".txt"; 
        bool readable = page.readPage((char *)ss.str().c_str()); //read a page and return if it has been read successfully
        if(readable) {pages.push_back(page);}
        else {break;} //no more consecutive pages
        i++;
    }
    if(pages.empty()) {HandError("page1.txt does not exist");}
}

/********************************************************************************
Description: check whether the relationship between pages is valid
Return: void
********************************************************************************/
void Book::checkPages() {
    std::set<unsigned> refNum; //pages that have been referenced by other pages
    for(size_t i = 0; i < pages.size(); i++) {
        for(size_t j = 0; j < pages[i].choices.size(); j++) {
            if(pages[i].choices[j].first > pages.size()) {
                HandError("Invalid page reference -- Every page that is referenced by a choice should be valid");
            }
            refNum.insert(pages[i].choices[j].first);
        }
    }
    for (size_t m = 2; m < pages.size() + 1; m++) {
        if(refNum.find(m) == refNum.end()) {
            HandError("Invalid page reference -- Every page (except page1) must be referenced by at least one other page");
        }
    }
    std::vector<unsigned> losePages = findLose(); //find LOSE pages
    findWin(); //find WIN pages
    if(winPages.empty()) {
        HandError("Lack of WIN pages");
    }
    if(losePages.empty()) {
        HandError("Lack of LOSE pages");
    }
}

/********************************************************************************
Description: find WIN pages and update field winPages
Return: void
********************************************************************************/
void Book::findWin() {
    for (size_t i = 0; i< pages.size(); i++) {
        if(pages[i].result == true) {
            winPages.push_back(i + 1);
        }
    }
}

/********************************************************************************
Description: find LOSE pages
Return: std::vector<unsigned>
********************************************************************************/
std::vector<unsigned> Book::findLose() {
    std::vector<unsigned> losePages;
    for (size_t i = 0; i< pages.size(); i++) {
        if(pages[i].result == false && pages[i].choices.empty()) {
            losePages.push_back(i + 1);
        }
    }
    return losePages;
}

/********************************************************************************
Description: begin the story --> print page1 and then print other pages based on the user's choices
Return: void
********************************************************************************/
void Book::beginStory(){
    pages[0].printPage();
    unsigned num = 1; //cureent page number
    while(true) {
        if(!pages[num - 1].choices.empty()) { //encounter choice page
            std::string str;
            std::getline(std::cin, str);
            for (size_t i = 0; i < str.length(); i++) {
                if (isdigit(str[i]) == 0) {
                    std::cout << "That is not a valid choice, please try again" << std::endl;
                    continue;
                }
            }
            unsigned choice = (unsigned)atoi(str.c_str());
            if(choice > pages[num - 1].choices.size() || choice == 0) {
                std::cout << "That is not a valid choice, please try again" << std::endl;
                continue;
            }
            num = pages[num - 1].choices[choice - 1].first;
            pages[num - 1].printPage();
        }
        else {return;} //finish when encounter WIN page or LOSE page
    }
}

/********************************************************************************
Description: calculate the depth of a page
Input: pageNum -> number of the page
Return: int
********************************************************************************/
int Book::depth(unsigned pageNum) {
    //bfs
    std::queue<std::vector<unsigned> > todo;
    std::set<unsigned> visited;
    std::vector<unsigned> currentPath;
    todo.push(std::vector<unsigned>(1, 1));
    while(!todo.empty()) {
        currentPath = todo.front();
        todo.pop();
        unsigned currentNode = currentPath.back();
        if (currentNode == pageNum) {
            int storyDep = currentPath.size() - 1;
            return storyDep;
        }
        if (visited.find(currentNode) == visited.end()) {
            visited.insert(currentNode);
            for (size_t i = 0; i < pages[currentNode - 1].choices.size(); i++) {
                currentPath.push_back(pages[currentNode - 1].choices[i].first);
                todo.push(currentPath);
                currentPath.pop_back();
            }
        }
    }
    return -1; //if the page is unreachable, return -1
}

/********************************************************************************
Description: print the depth of all the pages in a book
Return: void
********************************************************************************/
void Book::printDepth() {
    for (size_t i = 0; i < pages.size(); i++) {
        int dep = depth(i + 1);
        if(dep == -1) { //unreachable page
            std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
        }
        else {
            std::cout << "Page " << i + 1 << ":" << dep << std::endl;
        }
    }
}

/********************************************************************************
Description: find all reachable WIN pages
Return: std::vector<unsigned>
********************************************************************************/
std::vector<unsigned> Book::findValidWin() {
    std::vector<unsigned> valiWinPages;
    for (size_t i = 0; i< winPages.size(); i++) {
        if(depth(winPages[i]) != -1) {
            valiWinPages.push_back(winPages[i]);
        }
    }
    return valiWinPages;
}

/********************************************************************************
Description: calculate all WIN paths of a page
Input: pageNum -> number of the page
Return: std::vector<std::vector<unsigned> >
********************************************************************************/
std::vector<std::vector<unsigned> > Book::winPath(unsigned pageNum) {
    //dfs
    std::stack<std::vector<unsigned> > todo;
    std::set<unsigned> visited;
    std::vector<unsigned> currentPath;
    std::vector<std::vector<unsigned> > ans;
    todo.push(std::vector<unsigned>(1, 1));
    while(!todo.empty()) {
        currentPath = todo.top();
        todo.pop();
        unsigned currentNode = currentPath.back();
        if (currentNode == pageNum) {
            ans.push_back(currentPath);
            visited.clear();
            for (size_t j = 0; j < todo.top().size() - 1; j++) {
                visited.insert(todo.top()[j]);
            }
            continue;
        }
        if (visited.find(currentNode) == visited.end()) {
            visited.insert(currentNode);
            for (size_t i = 0; i < pages[currentNode - 1].choices.size(); i++) {
                currentPath.push_back(pages[currentNode - 1].choices[i].first);
                todo.push(currentPath);
                currentPath.pop_back();
            }
        }
    }
    return ans;
}

/********************************************************************************
Description: print all cycle-free ways to "win" for a book
Input: valiWinPages -> all reachable WIN pages
Return: void
********************************************************************************/
void Book::printWin(std::vector<unsigned> valiWinPages){
    if(valiWinPages.empty()) {
        std::cout << "This story is unwinnable!" << std::endl;
    }
    for (size_t i = 0; i < valiWinPages.size(); i++) {
        if(valiWinPages[i] == 1) {
            std::cout << "1" << "(win)" << std::endl;
            return;
        }
        std::vector<std::vector<unsigned> > winPaths = winPath(valiWinPages[i]);
        for (size_t j = 0; j < winPaths.size(); j++) {
            for (size_t m = 0; m < winPaths[j].size() - 1; m++) {
                //find the corresponding choice number
                unsigned num;
                for (size_t n = 0; n < pages[winPaths[j][m] - 1].choices.size(); n++) {
                    if(pages[winPaths[j][m] - 1].choices[n].first == winPaths[j][m+1]) {
                        num = n + 1;
                    }
                }
                std::cout << winPaths[j][m] << "(" << num << "),";
            }
            std::cout << winPaths[j].back() << "(win)";
            std::cout << std::endl;
        }
    }
}
