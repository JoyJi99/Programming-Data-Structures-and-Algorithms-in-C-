#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

/*
void stripNewLine(char * str){
  char * p = strchr(str, '\n');
  if(p != NULL){
    *p = '\0';
  }
}

kvpair_t * parseKVline(char * str) {
  stripNewLine(str);
  char * place = strchr(str, '=');
  if(place == NULL){
    perror("error");
    exit(EXIT_FAILURE);
  }
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = NULL;
  pair->value = NULL;
  int rightLen = strlen(place+1);
  int leftLen = strlen(str) - rightLen - 1;
  if(strlen(str) == 0){
    perror("error");
    exit(EXIT_FAILURE);
  }
  pair->key = malloc((leftLen + 1) * sizeof(*pair->key));
  pair->value = malloc((rightLen + 1) * sizeof(*pair->value));
  //strncpy will not add \0 automatically
  //if there is a space no being initialized, valgrind will report
  strncpy(pair->key, str, leftLen);
  pair->key[leftLen] = '\0';
  strcpy(pair->value, place+1);
  return pair;
}
*/
kvpair_t parseKVline(char * line) {
  kvpair_t pair;
  pair.key = NULL;
  pair.value = NULL;
  size_t i = 0;
  size_t j = 0;
  while (line[i] != '=' && line[i] != '\n' && line[i] != '\0') {
    pair.key = realloc(pair.key, (j + 1) * sizeof(*pair.value));
    pair.key[j] = line[i];
    i++;
    j++;
  }
  if (line[i] != '=') {
    fprintf(stderr, "Line doesn't have '='\n");
    exit(EXIT_FAILURE);
  }
  pair.key = realloc(pair.key, (j + 1) * sizeof(*pair.key));
  pair.key[j] = '\0';
  i++;  // form line[i]='=' to value area in line
  j = 0;
  while (line[i] != '\n' && line[i] != '\0') {
    pair.value = realloc(pair.value, (j + 1) * sizeof(*pair.value));
    pair.value[j] = line[i];
    i++;
    j++;
  }
  pair.value = realloc(pair.value, (j + 1) * sizeof(*pair.value));
  pair.value[j] = '\0';
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r"); 
  if (f == NULL) {
    return NULL; //Could not open file->indicate failure 
  }
  kvarray_t * pairs = malloc(sizeof(*pairs));
  pairs->len = 0;
  pairs->kvpair = NULL;
  size_t sz = 0;
  ssize_t length = 0;
  char * line = NULL;
  while ((length = getline(&line, &sz, f)) >= 0) {
    pairs->len++;
    pairs->kvpair = realloc(pairs->kvpair, pairs->len * sizeof(*pairs->kvpair));
    pairs->kvpair[pairs->len - 1] = parseKVline(line);
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t i;
  for (i = 0; i < pairs->len; i++) {
    free(pairs->kvpair[i].key);
    free(pairs->kvpair[i].value);
  }
  free(pairs->kvpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i = 0; i < pairs->len; i++){
    printf("key = '%s' value = '%s'\n", pairs->kvpair[i].key, pairs->kvpair[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    if (!strcmp(pairs->kvpair[i].key, key)) {
      return pairs->kvpair[i].value;
    }
  }
  return NULL;
}
