#ifndef LAGERHANTERING_H
#define LAGERHANTERING_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
@file lagerhantering.h
@author Rebecca Oskarsson and Johan Hullberg
@brief Header file containing the typedefinitions of structures and funktions.
 */

struct product_t {
  char* name;
  char* description;
  char* place;
  int price;
  int amount;
};
  
struct db_t {
  struct product_t* product;
  int amount;
};

typedef struct db_t* db_t;

/**
Prints the main screen
 */
void printMenu();

/**
Prints the 'edit-screen'
 */
void printEdit();

/**
Asks the user a question and returns the answer (string)
 */
char* ask_string_question(char* question);

/**
Same as above, but for different purpose.
 */
char* whatName(char* question);

/**
Asks the user a question and returns the answer (digit)
 */
int ask_int_question(char* question);

/**
Asks the user a question with certain alternatives
 */
char ask_char_question(char* question, char* alternative);

/**
Prints the information about the product
 */
void print_item(struct product_t product);

/**
Adds a product to a database
 */
void add_to_db(db_t db, struct product_t product);

/**
Returns an int that represents where in the database we can find the product with name name1
 */
int positionOfProduct(db_t db, char* name1);

/**
Returns an int that represents where in the database we can find the product at place place1
 */
int placeExist(db_t db, char* place1);
/**
Adds a product to the database, asks questions for the user to answer
 */
void add_item(db_t db);

/**
Removes an item from the database, depending on input from user
 */
void remove_item(db_t db);

/**
Edits the information about a product, depending on input
 */
void edit_item(db_t db);

/**
Frees the allocated memory for a database
 */
void free_db(db_t db);

/**
Creates a copy of a database, used for backup
 */
db_t db_copy(db_t db);

/**
Prints out a list of the products in a database
 */
void print_db(db_t db);

/**
Equality between products
 */
bool equalProducts(struct product_t p1, struct product_t p2);

/**
Equality between databases
 */
bool equalDatabases(db_t db1, db_t db2);

/**
Runs the program
 */
int main();

#endif
