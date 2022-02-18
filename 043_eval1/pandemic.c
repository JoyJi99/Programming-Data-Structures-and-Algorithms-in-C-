#include "pandemic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/*************************************************
Function: dataLen
Description: check whether the data length exceeds the range
Called By: parseLine
Input: hi -> pointer to the highest bit of a string
       lo -> pointer to the lowest bit of a string
       m -> maximum length permitted
       n -> length when string is null
Return: void
*************************************************/
void dataLen(char * hi, char * lo, int m, int n){
    if((hi - lo) >= m){
        fprintf(stderr, "parseLine: The data is too long to read.\n");
        exit(EXIT_FAILURE);
    }
    else if((hi - lo) == n){
        fprintf(stderr, "parseLine: There is no data to read.\n");
        exit(EXIT_FAILURE);
    }
}

/*************************************************
Function: isNumber
Description: check whether the char passed in is a number
Called By: parseLine
Input: c -> char
Return: 0 -> is not number
        1 -> is number
*************************************************/
int isNumber(char c) {
    // the ascii of 0-9 is 48-57
    if (c >= 48 && c <= 57) {
        return 1;
    }
    return 0;
}

/*************************************************
Function: stringGenerator
Description: replace all enters in the string with null terminators
Called By: parseLine
Input: str -> a string
Return: void
*************************************************/
void stringGenerator(char * str){
    char * p = strchr(str, '\n');
    if(p != NULL){
        *p = '\0';
    }
}

/************************************************* 
Function: parseLine
Description: parse a string to a struct which includes country name and population
Calls: stringGenerator, dataLen, isNumber 
Input: line -> a string which need to be parsed 
Return: country_t 
*************************************************/
country_t parseLine(char * line) {
    //check empty line
    if(line == NULL) {
        fprintf(stderr, "ParseLine: The line is NULL.\n");
        exit(EXIT_FAILURE);
    }
    //check the existence of comma
    char * comma = strchr(line, ',');
    if(comma == NULL){
        fprintf(stderr, "ParseLine: There is no comma.\n");
        exit(EXIT_FAILURE);
    }
    //check the length of country name
    dataLen(comma, line, 64, 0);
    //read the country name
    country_t ans;
    int i = 0;
    while(line[i] != ','){
        ans.name[i] = line[i];
        i++;
    }
    ans.name[i] = '\0';
    //replace enters with null terminator
    stringGenerator(line);
    //check the length of population
    char * tail = strchr(line, '\0');
    dataLen(tail, comma, 2^64, 1);
    //check if population is a number
    i++;
    while(line[i] != '\0'){
        if (!isNumber(line[i])) {
            fprintf(stderr, "ParseLine: The population is not a number.\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    //read the population
    unsigned long population = strtoul(comma + 1, NULL, 10);
    if(population == 0) {
        fprintf(stderr, "ParseLine: The population can't be 0!\n");
        exit(EXIT_FAILURE);
    }
    ans.population = population;
    return ans;
}

/*************************************************
Function: calcRunningAvg
Description: calculate the seven-day running average of case data
Input: data -> an array of daily case data
       n_days -> the number of days over which the data is measured
       avg -> an array of doubles which writes the result of the calculation
Return: void
*************************************************/
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
    //check if the parameters are invalid
    if(data == NULL || n_days < 7 || avg == NULL) {
        fprintf(stderr, "calcRunningAvg: The parameters passed in are invalid!\n");
        exit(EXIT_FAILURE);
    }
    unsigned * first = data;
    unsigned * pointer;
    unsigned sum = 0;
    //calculate running average
    for(int i = 0; i < n_days - 6; i++) {
        pointer = first;
        for(int j = 0; j < 7; j++) {
            sum += *pointer;
	    pointer++;
        }
	avg[i] = (double)sum/7;
        sum = 0;
	first++;
    }
}

/*************************************************
Function: calcCumulative
Description: calculate the cumulative number of cases that day per 100,000 people
Input: data -> an array of daily case data
       n_days -> the number of days over which the data is measured
       pop -> the population for that country
       cum -> the result of the calculation
Return: void
*************************************************/
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
    //check if the parameters passed in is valid
    if(data == NULL || n_days == 0 || pop == 0 || cum == NULL) {
        fprintf(stderr, "calcCumulative: The parameters passed in are invalid!\n");
        exit(EXIT_FAILURE);
    }
    //calculate the cumulative number of cases for each day
    unsigned sum = 0;
    unsigned * pointer = data;
    for(int i = 0; i < n_days; i++) {
        sum += *pointer;
        cum[i] = (double)sum / pop * 100000;
	pointer++;
    }  
}

/*************************************************
Function: printCountryWithMax
Description: find the maximum number of daily cases of all countries represented in the data, over the entire time period
Input: countries -> an array of country_t's with length n_countries
       n_countries -> the number of countries over which the data is measured
       data -> a 2-D array of data with each country's data representing a row 
       n_days ->  the number of days over which the data is measured
Return: void
*************************************************/
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
    //check if the parameters passed in is valid
    if (countries == NULL || n_countries == 0 || n_days == 0 || data == NULL) {
        fprintf(stderr, "printCountryWithMax: The parameters passed in are invalid!\n");
        exit(EXIT_FAILURE);
    }
    //calculate the maximum number of daily cases and the corresponding country
    unsigned max = 0;
    int country_i = 0;
    for(int j = 0; j < n_days; j++) {
        for(int i = 0; i < n_countries; i++) {
            if(data[i][j] > max) {
                country_i = i;
                max = data[i][j];
            }
        }
    }
    printf("%s has the most daily cases with %u\n", countries[country_i].name, max);
}
