#include <string.h>
#include <stdlib.h>
#include "lagerhantering.h"

/**
@file lagermain.c
@author Rebecca Oskarsson Johan Hullberg
@brief Creates an databases and ask the user what she would like to do.
 */
int main() {
  bool should_continue = true;
  db_t db1 = malloc(sizeof(struct db_t));
  db_t backup;
  while (should_continue) { 
    printMenu();
    switch (ask_char_question("What do you want to do?", "AaRrEeUuPpQq")){
      // Add
    case 'a':
      puts("You chose 'Add'");
      free_db(backup);
      backup = db_copy(db1);
      add_item(db1);
      break;

      // Remove
    case 'r':
      puts("You chose 'Remove'");
      free_db(backup);
      backup = db_copy(db1);
      remove_item(db1);
      break;
      
      // Edit
    case 'e':
      puts("You chose 'Edit'");
      free_db(backup);
      backup = db_copy(db1);
      edit_item(db1);
      break;
      
      // Undo
    case 'u':
      puts("You chose 'Undo'");
      free_db(db1);
      db1 = db_copy(backup);
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
	if(db1 != NULL){
	free_db(db1);
	}
	else
	  free(db1);
	if (backup != NULL) {
	  free_db(backup);
	  }
	else if(backup == NULL){
	  free(backup);
	} 
      }
      break;
    default:
      puts("Did not enter any valid command, please try again.\n");
    }
  }
  return 0;
}
