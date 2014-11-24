#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// valgrind --tool=memcheck --leak-check=full ./lager

/**
@file lagerhantering.c
@author Rebecca Oskarsson and Johan Hullberg
@brief A file consisting of the functions needed to add, change, remove etc. a file in a database aka inventory.
 */
/*
// Example: place A25
struct place_t{
char shelf;
int number;
};*/

struct product_t {
  char* name;
  char* description;
  char* place;
  int price;
  int amount;
};

/**
Amount of products, each product has its own index.
 */
struct db_t {
  struct product_t* product;
  int amount;
};

typedef struct db_t* db_t;

/**
Prints the welcome-screen.
 */
void printMenu() {
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
Prints the choices.
 */
void printEdit(){
  puts("\n[N]ame");
  puts("[D]escription");
  puts("[P]lace");
  puts("P[r]ice");
  puts("[A]mount");
  
}
/**
@parameter p1 the first product
@parameter p2 the second product
Return true if the two given products are exactly the same.
 */
bool equalProducts(struct product_t p1, struct product_t p2){
  if((p1.name == p2.name) && (p1.description == p2.description) && (p1.place == p2.place) && (p1.price == p2.price) && (p1.amount == p2.amount)){
    return true;
  }
  else return false;
}
/**
Returns true if the two given databases are exactly the same.
 */
bool equalDatabases(db_t db1, db_t db2) {
  if (db1->amount == db2->amount) {
    int i = 0;
    bool stop = true;
    while (i < db1->amount && stop == true) {
      if (equalProducts(db1->product[i], db2->product[i]) == false) {
	stop = false;
	}
      i++;
    }
    return stop;
  }
  else return false;
}

/**
Asks the user to enter a valid string for the desired label of the product.
 */
char* ask_string_question(char* question) {
  printf("A string suited for the current label, %s: ", question);
  char buffer[128];
  fgets(buffer, 128, stdin);
  char* reply = strdup(buffer);
  return reply;
}

/**
Asks the user a question, and returns the answer as a char.
 */
char* whatName(char* question) {
  printf("Enter the name of the product to %s: ", question);
  char buffer[128];
  fgets(buffer, 128, stdin);
  char* reply = strdup(buffer);
  return reply;
}

/**
Asks the user to name a number.
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
Asks a question that can be answered with a string.
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
Prints the given product.
 */
void print_item (struct product_t product) {
  printf("\nName: %sDescription: %sPlace: %sPrice: %d\nAmount: %d\n\n", product.name, product.description, product.place, product.price, product.amount);
}

/**
Adds the given product to the given database.
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
Gives the position of the product with the given name in the given databse.
 */
int positionOfProduct(db_t db, char* name1) {
  int n = (db->amount)-1;
  for (int i = 0; i <= n; i++) {
    if (strcmp(name1, db->product[i].name) == 0){
      return i;
    }
  }
  return -1;
}
/**
Returns the place in the database where the product with the given name is placed. 
 */
int placeExist(db_t db, char* place1){
 int n = (db->amount)-1;
  for (int i = 0; i <= n; i++) {
    if (strcmp(place1, db->product[i].place) == 0){
      return i;
    }
  }
  return -1;
}

/**
Adds an item to the inventory.
 */
void add_item (db_t db) {
  struct product_t product;
  product.name = ask_string_question("Name");
  if (positionOfProduct(db, product.name) != -1){
    puts("Product already exist");
  }
  else{
    product.description = ask_string_question("Description");
    char* reply = ask_string_question("Place");
    int i = 0;
    while (placeExist(db, reply) != -1){
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
Remove an item from the inventory
 */
void remove_item (db_t db) {
  char* reply = whatName("remove");
  if (positionOfProduct(db, reply) == -1) {
    puts("Product does not exist");
  }
  else{
    int a = positionOfProduct(db, reply);
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
Edit an item from the given inventory.
 */
void edit_item(db_t db){
  if (db->amount == 0) {
    puts("There are no items in the database to edit!");
  }
  else {
    char* reply = whatName("edit");
    if(positionOfProduct(db, reply) == -1){
      puts("Product does not exist");
    }
    else {
      int a = positionOfProduct(db, reply);
      print_item(db->product[a]);
      printEdit();
      char* edited;
      int answer;
      switch (ask_char_question("What do you want to edit?", "NnDdPpRrAa")){
      case 'n':
	edited = ask_string_question("Name");
	printf("You are about to change the name from: %s, to: %s\n", db->product->name, edited);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  free(db->product->name);
	  db->product->name = edited;
	}
	//free(edited);
	break;
	
      case 'd':
	edited = ask_string_question("Description");
	printf("You are about to change the description from: %s, to: %s\n", db->product->description, edited);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  free(db->product->description);
	  db->product->description = edited;
	}
	free(edited);
	break;
      
      case 'p':
	edited = ask_string_question("Place");
	printf("You are about to change the place from: %s, to: %s\n", db->product->place, edited);
	if (ask_char_question("Are you sure?", "YyNn") == 'y') {
	  free(db->product->place);
	  db->product->place = edited;
	}
	free(edited);
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
Frees the whole memoryspace connected to the given inventory.
 */
void free_db(db_t db){
  if (db != NULL) {
    for(int i = 0; i < db->amount; i++){
      free(db->product[i].name);
      free(db->product[i].description);
      free(db->product[i].place);   
    }
    free(db->product);
  }
  free(db);
}

/**
Returns a copy of the given inventory.
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
Prints out the given database.
 */
void print_db(db_t db) {
  char* reply = "n";
  if (db->amount == 0) {
    puts("The database is empty.\n");
  }
  else {
    int* n = &db->amount;
    for(int i = 0; i < *n; i++){
      if(db->product[i].name == NULL){	
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



