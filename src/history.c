#include <stdio.h>
#include <stdlib.h>
#include "history.h"


/* Initialize the linked list to keep the history. */
/*
int other(){
  List* list = init_history();
  char* output1 = get_history(list, 1);
  printf("%s", output1);
  char* String1 = (char*) malloc(75);
  char* String2 = (char*) malloc(75);
  char* String3 = (char*) malloc(75);
  sprintf(String1, "String1");
  sprintf(String2, "String2");
  sprintf(String3, "String3");
  add_history(list, String1);
  add_history(list, String2);  
  add_history(list, String3);
  print_history(list);
  free_history(list);
}
*/
List *init_history(){
  List* history_log = (List *)malloc(sizeof(List));
  history_log -> root = NULL;
  return history_log;
}



/* Add a history item to the end of the list.

   List* list - the linked list

   char* str - the string to store

*/
void add_history(List *list, char *str) {

  Item *new_record = (Item *)malloc(sizeof(Item));
  if (new_record == NULL) {
    printf("Memory allocation failed!\n");
    return;
  }

  new_record->str = str;
  new_record->next = NULL;


  if (list->root == NULL) {
    new_record->id = 1;
    list->root = new_record;
  } else {
    Item *find_tail = list->root;
    while (find_tail->next != NULL) {
      find_tail = find_tail->next;
    }
    new_record->id = find_tail->id + 1;
    find_tail->next = new_record;
  }
}


/* Retrieve the string stored in the node where Item->id == id.

   List* list - the linked list

   int id - the id of the Item to find */

char *get_history(List *list, int id) {
  char* output = (char*) malloc(75);
  if (list->root == NULL) {
    sprintf(output, "No values have been given, history is empty\n");
    return output;
  }

  int items_till_id = id;
  Item *traverse = list->root;

  // Traverse the list until we reach the nth node or the end of the list
  while (items_till_id != 1 && traverse != NULL) {
    items_till_id--;
    traverse = traverse->next;
  }

   // If the id exists, return the string
  if (traverse != NULL) {
    return traverse->str;
  }

  sprintf(output, "There is no record for id: %d, the last id recorded is: %d\n", id, id - items_till_id);
  return output;
}



/*Print the entire contents of the list. */

void print_history(List *list){
  Item* traverse = list -> root;
  while(traverse != NULL){ 
    printf("id %d: %s\n",traverse -> id, traverse -> str); 
    traverse = traverse -> next;
  }
}


/*Free the history list and the strings it references. */

void free_history(List *list){
  Item* traverse = list -> root;
  while(traverse != NULL){
    Item* traverse_next = traverse -> next;
    free(traverse -> str);
    traverse-> str = NULL;
    free(traverse);
    traverse = NULL;
    traverse = traverse_next;
  }
  free(list);
  list = NULL;
}

