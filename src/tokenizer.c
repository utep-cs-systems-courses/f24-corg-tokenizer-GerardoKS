
#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"
 
int main(){
  List* list = init_history();
  while(1){
    printf("$\n");
    char* input = (char*) malloc(100);
    fgets(input, sizeof(char* )* 100, stdin);
    char * input_token_start = token_start(input);
    if(input_token_start[0] == '!'){
      int id = 0;
      int index = 0;
      char* start = input_token_start + 1;
      start = token_start(start);
      if(*start != '\0'){
	id += atoi(start);
	printf("%s", get_history(list, id));
	continue;
      }
    }
    if (input_token_start[0] == 'e' && input_token_start[1] == 'x' && input_token_start[2] == 'i' && input_token_start[3] == 't') {
      free_history(list);
      return 0;
    }

    else if (input_token_start[0] == 'h' && input_token_start[1] == 'i' && input_token_start[2] == 's' && input_token_start[3] == 't' && input_token_start[4] == 'o' && input_token_start[5] == 'r' && input_token_start[6] == 'y') {
      printf("\nprinting history log\n\n");
      print_history(list);
      continue;
    }
    int len = count_tokens(input);
    char** sentence = (char**) calloc(len +1, sizeof(char*));
    
    if (sentence == NULL) {
      printf("calloc pointers is null");
      continue;
    }
    sentence = tokenize(input);
    add_history(list, input);
    print_tokens(sentence);
  }
}




 // true if c is a tab or space, and not zero
int space_char(char c){
  switch(c){
    case(' '):
      return 1;
    case('\t'):
      return 1;
    case('\0'):
      return 0;
  }
  return 0;
}

 // true if c not a tab or space, and not zero
int non_space_char(char c){
  if(c == '\0')
    return 0;
  return space_char(c) - 1;
}


 // * to first (non-space) char in first token in s.  Return zero if there are no tokens in s.
char* token_start(char* s){
  while(space_char(*s)){
    if(*s == '\0')
      return s;
    s++;
  }
  return s;
}


 // * to char after end of token.
char* token_terminator(char* token){
  char* current = token;
  while(non_space_char(*current)){
    current++;
  }

  return current;
}



 // the number of tokens in s
int count_tokens(char* s){
  int total_count = 0;
  char* new_pointer= s;
  while(*new_pointer != '\0'){
    new_pointer = token_start(new_pointer);
    if(*new_pointer != '\0')
      total_count = total_count + 1;
    new_pointer = token_terminator(new_pointer);
  }
  return total_count;
}

 // return a pointer to a (terminated) copy of inSr
char* copy_str(char* inStr, short len){
  char* word_pointer = (char*)calloc(len+1,sizeof(char));
  if(word_pointer == NULL){
   printf("calloc pointers is null");
   return NULL;
  }
  for(short i = 0; i < len; i++){
    word_pointer[i] =  inStr[i];
  }
  word_pointer[len] = '\0';
  return word_pointer;
}


char** tokenize(char* s) {
  int len = count_tokens(s);
  char** sentence_pointer = (char**) calloc(len +1, sizeof(char*));
    
  if (sentence_pointer == NULL) {
    printf("calloc pointers is null");
    return 0;
  }

 
  char* temp = s;
  int len_of_word = 0;
  for (int i = 0; i < len; i++) {
    char* start_of_token = token_start(temp);
    char* end_of_str = token_terminator(start_of_token);
    len_of_word = (end_of_str - start_of_token);
    sentence_pointer[i] = copy_str(start_of_token, len_of_word);
    temp = end_of_str;
  }
 
  sentence_pointer[len] = NULL;

  return sentence_pointer;
}



void print_tokens(char** tokens){
  char** sentence = tokens;
  while(*sentence != NULL){
    char* word = *sentence;
    printf("%s\n", word);
    sentence++;
  }
  free_tokens(tokens);
}


void free_tokens(char** tokens){
  char* word = *tokens;
  int index = 0;
  while(tokens[index] != NULL){
    free(tokens[index]);
    index ++;
  }
  free(tokens);
}

