#include <string.h>
#include <stdlib.h>
#include "lagerhantering.h"

/**
@file lagermain.c
@author Johan Hullberg
@author  Rebecca Oskarsson
@brief Creates an databases and ask the user what she would like to do.
 */

/**
@brief Runs the program and calls funcitons from the headerfile lagerhantering.h
@return always 0
 */
int main() {
  bool should_continue = true;
  db_t db1 = malloc(sizeof(struct db_t));
  db1->amount = 0;
  db_t backup;
  int i = 0;
  while (should_continue) { 
    print_menu();
    switch (ask_char_question("What do you want to do?", "AaRrEeUuPpQq")){
      // Add
    case 'a':
      puts("You chose 'Add'");
      if (i > 0){
      free_db(backup);
      }
      backup = db_copy(db1);
      i++;
      add_item(db1);
      break;

      // Remove
    case 'r':
      puts("You chose 'Remove'");
      if(i>0){
      free_db(backup);
      }     
      backup = db_copy(db1);
      i++;
      remove_item(db1);
      break;
      
      // Edit
    case 'e':
      puts("You chose 'Edit'");
      if (i>0){
      free_db(backup);
      }
      backup = db_copy(db1);
      i++;
      edit_item(db1);
      break;
      
      // Undo
    case 'u':
      puts("You chose 'Undo'");
      if(i>0){
      free_db(db1);
      } 
     db1 = db_copy(backup);
      i++;
      // backup = db_copy(db1);
      break;
      
      // Print
    case 'p':
      puts("You chose 'Print'");
      print_db(db1);
      break;
      
      // Quit
    case 'q':
      if (ask_char_question("Do you wish to exit the programme?", "YyNn") == 'y') {
	puts("Goodbye!");
	should_continue  = false;
	free_db(db1);
	if(i > 0){
	  free_db(backup);
	}
	/*	if(db1 != NULL){
	free_db(db1);
	}
	else
	  free(db1);
	if (backup != NULL) {
	  free_db(backup);
	  }
	else if(backup == NULL){
	  free(backup);
	  }*/ 
	}
      break;
    default:
      puts("Did not enter any valid command, please try again.\n");
    }
  }
  return 0;
}
