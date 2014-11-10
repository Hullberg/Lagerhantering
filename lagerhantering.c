#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
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


/*
    char *
    fgets(char * restrict str, int size, FILE * restrict stream);

där stream skall vara stdin. 

Du bör läsa in i en buffert. Denna buffer är lämpligen en char
array på stacken. När du har läst in, använd strdup för att 
kopiera strängen till heapen. 
 */
// Asks the user to enter a valid string for the desired label of the product.
char* ask_string_question(char* question) {
  printf("A string suited for the current label, %s: ", question);
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
      printf("\nName: %sDescription: %sPlace: %sPrice: %d\nAmount: %d\n\n", product.name, product.description, product.place, product.price, product.amount );
    }



void add_to_db (db_t db, struct product_t product) {
  db->product = malloc(sizeof(struct product_t));
  db->product[db->amount++] = product;
}


// Adds an item to the inventory.
void add_item (db_t db) {
  struct product_t product;
  product.name = ask_string_question("Name");
  product.description = ask_string_question("Description");
  product.place = ask_string_question("Place");
  product.price = ask_int_question("Price");
  product.amount = ask_int_question("Amount");
  
  print_item(product);

  while(getchar() != '\n');

  if (ask_char_question("Save to database?", "YyNn") == 'y') {
    add_to_db(db, product);
    puts("The item was added to the database.\n");
  }
  else {
    puts("The item was not added to the database.\n");
  }
}


void print_db(db_t db) {
  int i = 0;
  while(&db->product[i] != NULL){
    print_item(db->product[i]);
    i++;
  }
}


int main (void){
  bool should_continue = true;
  db_t db1 = malloc(sizeof(struct db_t));
  while (should_continue) {
    printMenu();

    switch (ask_char_question("What do you want to do?", "AaRrEeUuPpQq")){
      // Add
    case 'a':
      add_item(db1);
      break;

      /*     // Remove
    case 'r':

      break;

      // Edit
    case 'e':

      break;

      // Undo
    case 'u':

    break;*/

      // Print
    case 'p':
      print_db(db1);
    break;

      // Quit
    case 'q':
      if (ask_char_question("Do you wish to exit the programme?", "YyNn") == 'y') {
	puts("Goodbye!");
	should_continue  = false;
	free(db1);
      } 
      break;
    default:
      puts("Did not enter any valid command, please try again.\n");
    }
  }
  return 0;
}
