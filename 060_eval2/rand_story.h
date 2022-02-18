#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"

//main
void argCheck(int argc, int argNum, int num, char * str);
void fNull(FILE * f, int num, char * fileName);
void close(FILE * f, int num, char * fileName);
//step1
void printStoryLine(char * line, catarray_t * cats, int reuse, category_t * track);
void freeCat(category_t * cat);
void parseTemplate(FILE * f, catarray_t * cats, int reuse);
//step2
int contains(catarray_t * cats, char * catName);
char * getWord(char * line);
char * getCat(char * line);
catarray_t * parseCategories(FILE * f);
void freeCatArr(catarray_t * cats);
//step3
const char * newChooseWord(char * category, catarray_t * cats, category_t * track);
//step4
void removeWord(catarray_t * cats, char * category, const char * word);

#endif
