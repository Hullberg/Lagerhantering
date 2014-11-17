#include <string.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "lagerhantering.h"

int init_suite_1(void)
{
  return 0;
}

int clean_suite_1(void)
{
  return 0;
}

int init_suite_2(void)
{
  return 0;
}

int clean_suite_2(void)
{
  return 0;
}

// Empty database initialized




void testLAGER_equalProducts(void)
{

struct product_t product1;
product1.name = "Apple";
product1.description = "A fruit";
product1.place = "A01";
product1.price = 12;
product1.amount = 10;
  
struct product_t product2;
product2.name = "Cookie";
product2.description = "Pastry";
product2.place = "B02";
product2.price = 20;
product2.amount = 7;
  CU_ASSERT(equalProducts(product1, product1) == true);
  CU_ASSERT(equalProducts(product1, product2) == false);
}

void testLAGER_ADD(void) 
{
  db_t db1 = malloc(sizeof(struct db_t));
struct product_t product1;
product1.name = "Apple";
product1.description = "A fruit";
product1.place = "A01";
product1.price = 12;
product1.amount = 10;
  
struct product_t product2;
product2.name = "Cookie";
product2.description = "Pastry";
product2.place = "B02";
product2.price = 20;
product2.amount = 7;
  // Test add_to_db instead of add_item
  add_to_db(db1, product1);
  add_to_db(db1, product2);

  CU_ASSERT(equalProducts(db1->product[0], product1));
  CU_ASSERT(equalProducts(db1->product[1], product2));

}

void testLAGER_positionOfProduct(void)
{
  db_t db1 = malloc(sizeof(struct db_t));
  struct product_t product1;
product1.name = "Apple";
product1.description = "A fruit";
product1.place = "A01";
product1.price = 12;
product1.amount = 10;
  
struct product_t product2;
product2.name = "Cookie";
product2.description = "Pastry";
product2.place = "B02";
product2.price = 20;
product2.amount = 7;
 
  add_to_db(db1, product1);
  add_to_db(db1, product2);
  
  CU_ASSERT(positionOfProduct(db1, product1.name) == 0);
  CU_ASSERT(positionOfProduct(db1, product2.name) == 1);
}


void testLAGER_dbCopy(void){
  db_t db1 = malloc(sizeof(struct db_t));
  CU_ASSERT(equalDatabases(db_copy(db1), db1));
}



/* ----- ISTRING ------ */
/*
void testISTRING_MK(void)
{
  char *str1 = istring_mk(NULL);
  CU_ASSERT(str1 == NULL);
  char str2[] = "foo";
  char *str3 = istring_mk(str2);
  CU_ASSERT(strlen(str3) == strlen(str2));
  CU_ASSERT(strcmp(str2, str3)  == 0);
  CU_ASSERT(str3[0]  == 'f');
  CU_ASSERT(str3[1]  == 'o');
  CU_ASSERT(str3[2]  == 'o');
  CU_ASSERT(str3[3]  == '\0');
  str3[0]  = 'F';
  CU_ASSERT(strcmp(str2, str3) > 0);
  istring_rm(str1);
  istring_rm(str3);
}

void testISTRING_RM(void)
{
  istring_rm(istring_mk("test"));
}

void testISTRLEN(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("ekieki");
  CU_ASSERT(istrlen(str1) == 4);
  CU_ASSERT(istrlen(str2) == 6);
  START(str2)->length = 3;
  CU_ASSERT(istrlen(str2) == 3);
  CU_ASSERT(strlen(str2) == 6);
  istring_rm(str1);
  istring_rm(str2);
}

void testISTRING_TO_STRING(void)
{
  char *str1 = istring_mk("spam");
  CU_ASSERT(strcmp(istring_to_string(str1), "spam") == 0);
  istring_rm(str1);
}


void testISTRCAT(void)
{
  // You must implement you own!
  CU_FAIL("Test not implemented yet");
}

void testISTRNCAT(void)
{
  // You must implement you own!
  CU_FAIL("Test not implemented yet");
}

void testISTRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, 'b') == str + 10);
  CU_ASSERT(istrchr(str, 'c') == str + 12);
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrrchr(str, '\0') == str + 20);
  CU_ASSERT(istrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, 'b') == str + 10);
  CU_ASSERT(istrrchr(str, 'c') == str + 12);
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, '\0') == str + 20);
  CU_ASSERT(istrrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRCMP(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrcmp(str1, str1) == 0);
  CU_ASSERT(istrcmp(str1, str2) == 0);
  CU_ASSERT(istrcmp(str2, str3) > 0);
  CU_ASSERT(istrcmp(str3, str2) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRNCMP(void)
{
  char *str1 = istring_mk("spam ");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrncmp(str1, str2, 4) == 0);
  CU_ASSERT(istrncmp(str1, str2, 5) > 0);
  CU_ASSERT(istrncmp(str2, str3, 4) > 0);
  CU_ASSERT(istrncmp(str3, str2, 4) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRCPY(void)
{
  // You must implement your own!
  CU_FAIL("Test not implemented yet");
}

void testISTRNCPY(void)
{
  // You must implement your own!
  CU_FAIL("Test not implemented yet");
}

*/
/* ----- ISTRING ----- */


int main()
{
  CU_pSuite pSuite1 = NULL;
  CU_pSuite pSuite2 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suites */
  if (/* Here we put our own tests
    (NULL == CU_add_test(pSuite1, "test of istring_mk()", testISTRING_MK)) ||
    (NULL == CU_add_test(pSuite1, "test of istring_rm()", testISTRING_RM)) ||
    (NULL == CU_add_test(pSuite1, "test of istring_to_string()", testISTRING_TO_STRING)) ||
    (NULL == CU_add_test(pSuite1, "test of istrlen()", testISTRLEN))*/
     
      (NULL == CU_add_test(pSuite1, "test of lager_equalProducts()", testLAGER_equalProducts)) ||
      (NULL == CU_add_test(pSuite1, "test of lager_positionOfProduct()", testLAGER_positionOfProduct)) ||
      (NULL == CU_add_test(pSuite1, "test of lager_dbCopy()", testLAGER_dbCopy))
      
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (/* Here we put our own tests
    (NULL == CU_add_test(pSuite2, "test of istrcat()", testISTRCAT)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncat()", testISTRNCAT)) ||
    (NULL == CU_add_test(pSuite2, "test of istrchr()", testISTRCHR)) ||
    (NULL == CU_add_test(pSuite2, "test of istrrchr()", testISTRRCHR)) ||
    (NULL == CU_add_test(pSuite2, "test of istrcmp()", testISTRCMP)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncmp()", testISTRNCMP)) ||
    (NULL == CU_add_test(pSuite2, "test of istrcpy()", testISTRCPY)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncpy()", testISTRNCPY))*/

      (NULL == CU_add_test(pSuite2, "test of lager_add()", testLAGER_ADD))
      
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}


