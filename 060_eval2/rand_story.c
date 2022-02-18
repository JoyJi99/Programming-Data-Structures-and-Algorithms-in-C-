#include "rand_story.h"



/* ======================================= main ======================================= */


/********************************************************************************
Description: check whether the number of arguments is valid
Input: argc -> number of arguments
       argNum -> desired number of atguments
       num -> step number
       str -> string to print
Return: void
********************************************************************************/
void argCheck(int argc, int argNum, int num, char * str) {
    if (argc != argNum) {
        fprintf(stderr, "Usage: ./story-step%d %s\n", num, str);
        exit(EXIT_FAILURE);
    }
}

/********************************************************************************
Description: check whether the file opened is NULL
Input: f -> the opened file
       num -> step number
       fileName -> file name
Return: void
********************************************************************************/
void fNull(FILE * f, int num, char * fileName) {
    if (f == NULL) {
        fprintf(stderr, "Step%d: Can not open file %s!\n", num, fileName);
        exit(EXIT_FAILURE);
    }
}

/********************************************************************************
Description: check whether the file can be closed successfully
Input: f -> the opened file
       num -> step number
       fileName -> file name
Return: void
********************************************************************************/
void close(FILE * f, int num, char * fileName){
    if (fclose(f) != 0) {
        fprintf(stderr, "Step%d: Close %s failure!\n", num, fileName);
        exit(EXIT_FAILURE);
    }
}





/* ======================================= Step 1 ======================================= */


/********************************************************************************
Description: convert category to word and print story with single line from template
Input: line -> pointer to line get from getline fuction
       cats -> array of categories to choose words from
       reuse -> 0 if cannot choose the same word from categories when encounter same category in template
                1 if can repeatedly choose the previous used words
       track -> pointer to category struct that stores used words sequence
Return: void
********************************************************************************/
void printStoryLine(char * line, catarray_t * cats, int reuse, category_t * track) {
    size_t i = 0;
    int j = 0;  //indicator to show if line[i] is in the blank area
    size_t catLen = 0;
    char * cat = NULL;
    while (line[i] != '\0') {
        if (line[i] != '_' && j == 0) {  //out of blank area
            printf("%c", line[i]);
            i++;
        }
        if (line[i] == '_' && j == 0) {  //new blank area
            j = 1;
            i++;
        }
        if (line[i] != '_' && j == 1) {  //in blank area
            //store category name into cat
            cat = realloc(cat, (catLen + 1) * sizeof(*cat));
            cat[catLen] = line[i];
            catLen++;
            i++;
        }
        if (line[i] == '_' && j == 1) {  //end of blank area
            cat = realloc(cat, (catLen + 1) * sizeof(*cat));
            cat[catLen] = '\0';
            j = 0;
            i++;
            catLen = 0;
            const char * word = newChooseWord(cat, cats, track);
            //print word into story
            printf("%s", word);
            //store used words in track
            track->n_words++;
            track->words = realloc(track->words, (track->n_words) * sizeof(*track->words));
            track->words[track->n_words - 1] = strdup(word);
            //reuse == 0, remove used word from cats
            if (cat != NULL && reuse == 0) {
                if (atoi(cat) == 0 && contains(cats, cat) != -1 && cats->arr[contains(cats, cat)].n_words != 0) {//determine if word is in cats
                    removeWord(cats, cat, word);
                }
            }
        }
    }
    free(cat);
    if (j == 1) {//no matching '_' with a pervious '_'
        fprintf(stderr, "Underscore invalid: %s\n", line);
        exit(EXIT_FAILURE);
    }
}

/********************************************************************************
Description: free dynamically allocated memory for category_t * cat
Input: cat -> pointer to a category struct
Return: void
********************************************************************************/
void freeCat(category_t * cat) {
    for (size_t i = 0; i < cat->n_words; i++) {
        free(cat->words[i]);
    }
    free(cat->words);
    free(cat->name);
    free(cat);
}

/********************************************************************************
Description: parse whole story file and print the converted story
Input: f -> the opened file
       cats -> categories to choose word from
       reuse -> 0 if cannot choose the same word from categories when encounter same category in template
                1 if can repeatedly choose the previous used words
Return: void
********************************************************************************/
void parseTemplate(FILE * f, catarray_t * cats, int reuse) {
    char * line = NULL;
    size_t linecap;
    category_t * track = malloc(sizeof(*track));
    track->n_words = 0;
    track->words = NULL;
    track->name = strdup("used");
    //parse story file and print each lines with blank converted
    while (getline(&line, &linecap, f) >= 0) {
        printStoryLine(line, cats, reuse, track);
    }
    free(line);
    freeCat(track);
}





/* ======================================= Step 2 ======================================= */


/********************************************************************************
Description: get the category name before the first ":"
Input: line -> pointer to a line from word file
Return: char * -> the string before the first ":"
********************************************************************************/
char * getCat(char * line) {
    char * ptr = strchr(line, ':');
    if (ptr == NULL) {
        fprintf(stderr, "file format invalid: %s\n", line);
        exit(EXIT_FAILURE);
    }
    *ptr = '\0'; //strip ":" and characters after ":"
    char * category = strdup(line);
    return category;
}

/********************************************************************************
Description: get the word after the first ":"
Input: line -> pointer to a line from word file
Return: char * -> the string after the first ":"
********************************************************************************/
char * getWord(char * line) {
    if (strchr(line,'\n') != NULL) {
      char * newLine = strchr(line, '\n');
      *newLine = '\0'; //strip newline character
    }
    char * ptr = strchr(line, ':');
    if (ptr == NULL) {
        fprintf(stderr, "file format invalid: %s\n", line);
        exit(EXIT_FAILURE);
    }
    ptr++;
    char * word = strdup(ptr);
    return word;
}

/********************************************************************************
Description: check if a categoies array contains a specific category
Input: cats -> pointer to a categoies array
       cat -> specific category name
Return: int -> -1 if the categories array "cats" doesn't contain the category "cat"
               the index of the category "cat" in catrgories array if "cats" contains the category "cat"
********************************************************************************/
int contains(catarray_t * cats, char * cat) {
    for (size_t i = 0; i < cats->n; i++) {
        if (!strcmp(cats->arr[i].name, cat)) {
            return i; //cats contains cat, return index
        }
    }
    return -1; //cats doesn't contain cat
}

/********************************************************************************
Description: parse word file (each line of the file must have a colon)
Input: f -> the opened file
Return: catarray_t * -> pointer to categoies array which contains all categories and words parsed
********************************************************************************/
catarray_t * parseCategories(FILE * f) {
    char * line = NULL;
    size_t sz;
    catarray_t * cats = malloc(sizeof(*cats));
    cats->n = 0;
    cats->arr = NULL;
    while (getline(&line, &sz, f) >= 0) {
        //get word from line
        char * word = getWord(line);
	//get category name from line
        char * category = getCat(line);
	//save word and category name by updating cats
        int c = contains(cats, category);
        if (c == -1) { //new category
            cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
            cats->arr[cats->n].name = category;
            cats->arr[cats->n].n_words = 1;
            cats->arr[cats->n].words = malloc(sizeof(*cats->arr[cats->n].words));
            cats->arr[cats->n].words[0] = word;
            cats->n++;
        }
        else { //category exits in catarray "cats"
            free(category);
            cats->arr[c].n_words++;
            cats->arr[c].words = realloc(cats->arr[c].words,(cats->arr[c].n_words) * sizeof(*cats->arr[c].words));
            cats->arr[c].words[cats->arr[c].n_words - 1] = word;
        }
    }
    free(line);
    return cats;
}

/********************************************************************************
Description: free the dynamically allocated memory for catarray_t * cats
Input: cats -> pointer to a categoies array
Return: void
********************************************************************************/
void freeCatArr(catarray_t * cats) {
    for (size_t i = 0; i < cats->n; i++) {
        free(cats->arr[i].name);
        for (size_t j = 0; j < cats->arr[i].n_words; j++) {
            free(cats->arr[i].words[j]);
        }
        free(cats->arr[i].words);
    }
    free(cats->arr);
    free(cats);
}





/* ======================================= Step 3 ======================================= */


/********************************************************************************
Description: Advanced version of chooseWord() function that returns word from cats
Input: category -> specific category name
       cats -> pointer to a categoies array
       track -> pointer to category struct that stores used words sequence
Return: const char * -> "cats" if second argument "cats" is NULL
                        a random word if the category name is a category in cats
                        num-th previously used word if category name is a valid integer of at least one
********************************************************************************/
const char * newChooseWord(char * category, catarray_t * cats, category_t * track){
    int num = atoi(category); //atoi returns 0 if category can't be converted
    if(cats == NULL) {
        return chooseWord(category, NULL);
    }
    else{
        if(num == 0 && contains(cats, category) != -1 && cats->arr[contains(cats, category)].n_words != 0) {
	    //cats contains category and the category still has words
            return chooseWord(category, cats);
        }
        else if(num >= 1 && (unsigned int)num <= track->n_words) {
	    //category name is a valid integer of at least one and the integer is less than number of previously used words
	    return track->words[track->n_words - (unsigned int)num];
        }
        else if(num >= 1 && (unsigned int)num > track->n_words) {
	    //integer is larger than the number of previously used words
            fprintf(stderr, "storyFile with invalid integer\n");
            exit(EXIT_FAILURE);
        }
        else {
	  fprintf(stderr, "catarray doesn't contain categoty %s or catarray dosen't contain enough words in category %s\n", category, category);
            exit(EXIT_FAILURE);
        }
    }
}





/* ======================================= Step 4 ======================================= */


/********************************************************************************
Description: remove a word from categories struct cats
Input: cats -> pointer to a categoies array
       category -> specific category name
       word -> the word we want to remove
Return: void
********************************************************************************/
void removeWord(catarray_t * cats, char * category, const char * word){
    int cati = contains(cats, category);
    // find the index of word
    size_t wordi;
    for (size_t i = 0; i < cats->arr[cati].n_words; i++) {
        if (strcmp(word, cats->arr[cati].words[i]) == 0) {
            wordi = i;
        }
    }
    //remove word and decrease n_words by 1
    free(cats->arr[cati].words[wordi]);
    cats->arr[cati].n_words--;
    //re-allocate the remaining words in memory to make them consecutive
    size_t j = 0;
    char ** temp = malloc(cats->arr[cati].n_words * sizeof(*temp));
    for (size_t i = 0; i < (cats->arr[cati].n_words + 1); i++) {
        if (i != wordi) {
            temp[j] = cats->arr[cati].words[i];
            j++;
        }
    }
    free(cats->arr[cati].words);
    cats->arr[cati].words = malloc(cats->arr[cati].n_words * sizeof(*cats->arr[cati].words));
    for (size_t i = 0; i < cats->arr[cati].n_words; i++) {
        cats->arr[cati].words[i] = temp[i];
    }
    free(temp);
    
}
