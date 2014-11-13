#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

// Amount of products, each product has its own index.
struct db_t {
  struct product_t* product;
  int amount;
};

typedef struct db_t* db_t;

// Prints the welcome-screen.
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

void printEdit(){
  puts("\n[N]ame");
  puts("[D]escription");
  puts("[P]lace");
  puts("P[r]ice");
  puts("[A]mount");
  
}

// Asks the user to enter a valid string for the desired label of the product.
char* ask_string_question(char* question) {
  printf("A string suited for the current label, %s: ", question);
  char buffer[128];
  fgets(buffer, 128, stdin);
  char* reply = strdup(buffer);
  return reply;
}

// Asks the user a question, and returns the answer as a char.
char* whatName(char* question) {
  printf("Enter the name of the product to %s: ", question);
  char buffer[128];
  fgets(buffer, 128, stdin);
  char* reply = strdup(buffer);
  return reply;
}

// Asks the user to name a number.
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

// Asks a question that can be answered with a string.
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

void print_item (struct product_t product) {
  printf("\nName: %sDescription: %sPlace: %sPrice: %d\nAmount: %d\n\n", product.name, product.description, product.place, product.price, product.amount);
}

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

int positionOfProduct(db_t db, char* name1) {
  int n = (db->amount)-1;
  for (int i = 0; i <= n; i++) {
    if (strcmp(name1, db->product[i].name) == 0){
      return i;
    }
  }
  return -1;
}

// Adds an item to the inventory.
void add_item (db_t db) {
  struct product_t product;
  product.name = ask_string_question("Name");
  if (positionOfProduct(db, product.name) != -1){
    puts("Product already exist");
}
  else{
    product.description = ask_string_question("Description");
    product.place = ask_string_question("Place");
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

// Remove an item from the inventory
void remove_item (db_t db) {
  char* reply = whatName("remove");
  if (positionOfProduct(db, reply) == -1) {
    puts("Product does not exist");
  }
  else{
    int a = positionOfProduct(db, reply);
    printf("The product is at database-index: %d\n", a+1);
    printf("You wish to remove the product: %s", db->product[a].name);
    //db->product[a] = NULL;
    //free(&db->product[a]); 
    for (int i = a; i < db->amount; i++){ // Thought it could look something like this..
      db->product[i] = db->product[i+1];
    }
    db->amount--;
    puts("The product has been removed.\n");
  }
}


void edit_item(db_t db){
  char* reply = whatName("edit");
  if(positionOfProduct(db, reply) == -1){
    puts("Product does not exist");
  }
  else {
    int a = positionOfProduct(db, reply);
    print_item(db->product[a]);
    printEdit();
    switch (ask_char_question("What do you want to edit?", "NnDdPpRrAa")){
    case 'n':
      db->product->name = ask_string_question("Name");
      break;
  
    case 'd':
      db->product->description = ask_string_question("Description");
      break;

    case 'p':
      db->product->place = ask_string_question("Place");
      break;
     
    case 'r':
      db->product->price = ask_int_question("Price");
      break;

    case 'a':
      db->product->amount = ask_int_question("Amount");
      break;
    }
       
    
  }
  
}

void free_db(db_t db){
  for(int i = 0; i < db->amount; i++){
    free(db->product[i].name);
  free(db->product[i].description);
  free(db->product[i].place);

  }
  free(db->product);
  free(db);
}

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

void undo(db_t db, db_t backup){
  db = db_copy(backup);

}

void print_db(db_t db) {
  if (db->amount == 0) {
    puts("The database is empty.\n");
  }
  else {
    int* n = &db->amount;
    for(int i = 0; i < *n; i++){
      if(db->product[i].name == NULL){
	
}
      else if (&db->product[i] != NULL){
	print_item(db->product[i]);
	printf("Database-index: %d\n\n", i+1);
      }
    }
    puts("End of Database\n");
    printf("amount = %d\n", db->amount);
  }
}

int main() {
  bool should_continue = true;
  db_t db1 = malloc(sizeof(struct db_t));
  db_t backup = db_copy(db1);
  while (should_continue) { 
    printMenu();
    switch (ask_char_question("What do you want to do?", "AaRrEeUuPpQq")){
      // Add
    case 'a':
      free_db(backup);
      db_t backup = db_copy(db1);
      add_item(db1);
      break;

      // Remove
    case 'r':
      free_db(backup);
      backup = db_copy(db1);
      remove_item(db1);
      break;
      
      // Edit
    case 'e':
      free_db(backup);
      backup = db_copy(db1);
      edit_item(db1);
      break;
      
      // Undo
    case 'u':
      undo(db1, backup);
      // backup = db_copy(db1);
      break;
      
      // Print
    case 'p':
      print_db(db1);
      puts("\nbackup:\n");
      print_db(backup);
      break;
      
      // Quit
    case 'q':
      if (ask_char_question("Do you wish to exit the programme?", "YyNn") == 'y') {
	puts("Goodbye!");
	should_continue  = false;
	free_db(db1);
	free_db(backup);
      } 
      break;
    default:
      puts("Did not enter any valid command, please try again.\n");
    }
  }
  return 0;
}
