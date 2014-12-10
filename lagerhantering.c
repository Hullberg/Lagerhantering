#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// valgrind --tool=memcheck --leak-check=full ./lager

/**
@file lagerhantering.c
@author Johan Hullberg
@author Rebecca Oskarsson
@brief A file consisting of the functions needed to add, change, remove etc. a file in a database aka inventory.
 */
/*
// Example: place A25
struct place_t{
char shelf;
int number;
};*/
/**
@brief A product with a name, description, place, price and amount
 */
struct product_t {
  char* name;
  char* description;
  char* place;
  int price;
  int amount;
};

/**
@brief Amount of products, each product has its own index.
 */
struct db_t {
  struct product_t* product;
  int amount;
};


typedef struct db_t* db_t;

/**
@brief Prints the welcome-screen.
 */
void print_menu() {
  puts("\nWelcome to the Warehouse-Inventory 2.0");
  puts("============================");
  puts("[A]dd a product to the inventory");
  puts("[R]emove a product from the inventory");
  puts("[E]dit a product in the inventory");
  puts("[U]ndo last change");
  puts("[P]rint the whole inventory");
  puts("[Q]uit\n");
}
/**
@brief Prints the choices.
 */
void print_edit(){
  puts("\n[N]ame");
  puts("[D]escription");
  puts("[P]lace");
  puts("P[r]ice");
  puts("[A]mount");
  
}
/**
@brief Return true if the two given products are equal.
@param p1 the first product to compare
@param p2 the second product compare
@return boolean wether the given products are equal or not.
 */
bool equal_products(struct product_t p1, struct product_t p2){
  if((p1.name == p2.name) && (p1.description == p2.description) && (p1.place == p2.place) && (p1.price == p2.price) && (p1.amount == p2.amount)){
    return true;
  }
  else return false;
}
/**
@brief Returns true if the two given databases are equal.
@param db1 the first database to compare
@param db2 the second databse to compare
@return boolean wether the given databases are equal or not
 */
bool equal_databases(db_t db1, db_t db2) {
  if (db1->amount == db2->amount) {
    int i = 0;
    bool stop = true;
    while (i < db1->amount && stop == true) {
      if (equal_products(db1->product[i], db2->product[i]) == false) {
	stop = false;
	}
      i++;
    }
    return stop;
  }
  else return false;
}

/**
@brief Asks the user to enter a valid string for the desired label of the product.
@param question what label the user should name
@return the name that the user gave to the given label
 */
char* ask_string_question(char* question) {
  printf("A string suited for the current label, %s: ", question);
  char buffer[128];
  fgets(buffer, 128, stdin);
  char* reply = strdup(buffer);
  return reply;
}

/**
@brief Asks the user a question, and returns the answer as a char.
@param question the action the user chose to do to a product
@return the name of the product the user gave
 */
char* what_name(char* question) {
  printf("Enter the name of the product to %s: ", question);
  char buffer[128];
  fgets(buffer, 128, stdin);
  char* reply = strdup(buffer);
  return reply;
}

/**
@brief Asks the user to name a number.
@param question the kind of digit the user should give
@return the integer the user gave
 */
int ask_int_question (char* question) {
  printf("%s, a reasonable digit: ", question);
  int reply = 0;
  scanf("%d", &reply);
  if (isdigit(reply) == 0) {
    return reply;
  }
  else {
    puts("Entered invalid number, will return 0 now.");
    return 0;
  }
}

/**
@brief Asks a question that can be answered with a string.
@param question a question the user should answer
@param alternative the alternatives the user should get
@return the answer the user gave as a lowercase letter
 */
char ask_char_question (char* question, char* alternative) {
  printf("%s [%s]\n", question, alternative);
  while(true) {
    char reply = getchar();
    while (getchar() != '\n');
    if (strchr(alternative, reply)) {
      return tolower(reply);
    }
    printf("Invalid answer, try [%s]\n", alternative);
  }
}
/**
@brief Prints the given product.
@param product the product to print
 */
void print_item (struct product_t product) {
  printf("\nName: %sDescription: %sPlace: %sPrice: %d\nAmount: %d\n\n", product.name, product.description, product.place, product.price, product.amount);
}

/**
@brief Adds the given product to the given database.
@param db the database to add the product in
@param product the product to put into the database
 */
void add_to_db (db_t db, struct product_t product) {
  db->amount++;
  if (db->amount == 1){
    db->product = malloc(sizeof(struct product_t));
    db->product[0] = product;
  }
  else{
    db->product = realloc(db->product, sizeof(struct product_t) * ((db->amount)));
    db->product[db->amount-1] = product;
  }
}
/**
@brief Gives the position of the product with the given name in the given databse.
@param db the database to search through
@param name1 the name of a product to look for in the database
@return the position of the product with the given name in the database or -1 if no product has the given name
 */
int position_of_product(db_t db, char* name1) {
  int n = (db->amount)-1;
  for (int i = 0; i <= n; i++) {
    if (strcmp(name1, db->product[i].name) == 0){
      return i;
    }
  }
  return -1;
}
/**
@brief Returns the place in the database where the product with the given name is placed.
@param db the database to search through
@param place1 the place to look for in the given database
@return the position of the product at the given place in the database or -1 if the place is available
 */
int place_exist(db_t db, char* place1){
 int n = (db->amount)-1;
  for (int i = 0; i <= n; i++) {
    if (strcmp(place1, db->product[i].place) == 0){
      return i;
    }
  }
  return -1;
}

/**
@brief Adds an item to the inventory.
@param db the databse where a pontentially product should be put into
 */
void add_item (db_t db) {
  struct product_t product;
  product.name = ask_string_question("Name");
  if (position_of_product(db, product.name) != -1){
    puts("Product already exist");
  }
  else{
    product.description = ask_string_question("Description");
    char* reply = ask_string_question("Place");
    int i = 0;
    while (place_exist(db, reply) != -1){
      i++;
      if (i >= 3){
	puts("REALLY dude?! Stop it! Enter another place, PLEASE!");
      }
      else{
      puts("Place is already taken, please try again");
      }
    reply = ask_string_question("Place");
    }
    product.place = reply;
    product.price = ask_int_question("Price");
    product.amount = ask_int_question("Amount");
  
    print_item(product);
    printf("Database-index: %d\n\n", db->amount+1);

    while(getchar() != '\n');

    if (ask_char_question("Save to database?", "YyNn") == 'y') {
      add_to_db(db, product);
      puts("The item was added to the database.\n");
    }
    else {
      puts("The item was not added to the database.\n");
    }
  }
}

/**
@brief Remove an item from the inventory
@param db the database to remove a product from
 */
void remove_item (db_t db) {
  char* reply = what_name("remove");
  if (position_of_product(db, reply) == -1) {
    puts("Product does not exist");
  }
  else{
    int a = position_of_product(db, reply);
    printf("The product is at database-index: %d\n", a+1);
    printf("You wish to remove the product: %s", db->product[a].name);
    free(db->product[a].name);
    free(db->product[a].description);
    free(db->product[a].place);

    for (int i = a; i < db->amount; i++){ 
      db->product[i] = db->product[i+1];
    }
    db->amount--;
    puts("The product has been removed.\n");
   
  }
  free(reply);
}

/**
@brief Edit an item from the given inventory.
@param db the database to edit a product from
 */
void edit_item(db_t db){
  if (db->amount == 0) {
    puts("There are no items in the database to edit!");
  }
  else {
    char* reply = what_name("edit");
    if(position_of_product(db, reply) == -1){
      puts("Product does not exist");
    }
    else {
      int a = position_of_product(db, reply);
      print_item(db->product[a]);
      print_edit();
      char* edited;
      int answer;
      switch (ask_char_question("What do you want to edit?", "NnDdPpRrAa")){
      case 'n':
	edited = ask_string_question("Name");
	printf("You are about to change the name from: %s, to: %s\n", db->product->name, edited);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  free(db->product->name);
	  db->product->name = edited;
	}else{
	  free(edited);
	}
	break;
	
      case 'd':
	edited = ask_string_question("Description");
	printf("You are about to change the description from: %s, to: %s\n", db->product->description, edited);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  free(db->product->description);
	  db->product->description = edited;
	}else{
	  free(edited);
	}
	break;
      
      case 'p':
	edited = ask_string_question("Place");
	printf("You are about to change the place from: %s, to: %s\n", db->product->place, edited);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  free(db->product->place);
	  db->product->place = edited;
	}else{
	  free(edited);
	}
	break;
	
      case 'r':
	answer = ask_int_question("Price");
	while(getchar() != '\n');
	printf("You are about to change the price from: %d, to: %d\n", db->product->price, answer);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  db->product->price = answer;
	}
	break;
	
      case 'a':
	answer = ask_int_question("Amount");
	while(getchar() != '\n');
	printf("You are about to change the amount from: %d, to: %d\n", db->product->amount, answer);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  db->product->amount = answer;
	}
	break;
      }   
    }
    free(reply);
  }
}
/**
@brief Frees the whole memoryspace connected to the given inventory.
@param db the database to be freed
 */
void free_db(db_t db){
  if (db != NULL) {
    for(int i = 0; i < db->amount; i++){
      free(db->product[i].name);
      free(db->product[i].description);
      free(db->product[i].place);   
    }
    free(db->product);
    free(db);
  }
}

/**
@brief Returns a copy of the given inventory.
@param db the database to make a copy of
@return a copy of the given database
 */
db_t db_copy(db_t db){
  db_t newDb = malloc(sizeof(struct db_t));
  newDb->amount = db->amount;
  newDb->product = malloc((sizeof(struct product_t) * db->amount));
  for (int i = 0; i < db->amount; i++){
    newDb->product[i].name = strdup(db->product[i].name);
    newDb->product[i].description = strdup(db->product[i].description);
    newDb->product[i].place = strdup(db->product[i].place);
    newDb->product[i].price = db->product[i].price;
    newDb->product[i].amount = db->product[i].amount;
  }
  return newDb;
}

/**
@brief Prints out the given database.
@param db the database to print
 */
void print_db(db_t db) {
  char* reply = "n";
  if (db->amount == 0) {
    puts("The database is empty.\n");
  }
  else {
    int* n = &db->amount;
    for(int i = 0; i < *n; i++){
      if(&db->product[i] == NULL){
      }
      else if (&db->product[i] != NULL){
	printf("%d %s", i+1, db->product[i].name);
      }
    }
    puts("End of Database\n");
    int re = 0;
    while(strncmp(reply,"r",1) != 0 && (re <= 0 || re > db->amount)){
      char answer = ask_char_question("[C]hoose number for description or [R]eturn,", "CcRr");
      if (answer == 'c') {
	int number = ask_int_question("Enter the index of the product you wish to examine") - 1;
	while(getchar() != '\n');
	print_item(db->product[number]);
      }
      if (answer == 'r') {
	//free(answer);
	break;
      }
    }
  }
}



