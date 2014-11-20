#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
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

void testLAGER_equalDatabases(void)
{
  db_t db1 = malloc(sizeof(struct db_t));
  db_t db2 = malloc(sizeof(struct db_t));

  struct product_t product1;
  product1.name = "Apple";
  product1.description = "A fruit";
  product1.place = "A01";
  product1.price = 12;
  product1.amount = 10;
  
  add_to_db(db1, product1);
  add_to_db(db2, product1);

  CU_ASSERT(equalDatabases(db1, db2) == true);

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

void testLAGER_placeExist(void)
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
  
  CU_ASSERT(placeExist(db1, product1.place) == 0);
  CU_ASSERT(placeExist(db1, product2.place) == 1);
}


void testLAGER_dbCopy(void){
  db_t db1 = malloc(sizeof(struct db_t));
  CU_ASSERT(equalDatabases(db_copy(db1), db1));
}


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
  if ((NULL == CU_add_test(pSuite1, "test of lager_equalProducts()", testLAGER_equalProducts)) ||
      (NULL == CU_add_test(pSuite1, "test of lager_positionOfProduct()", testLAGER_positionOfProduct)) ||
      (NULL == CU_add_test(pSuite1, "test of lager_placeExist()", testLAGER_placeExist)) ||
      (NULL == CU_add_test(pSuite1, "test of lager_dbCopy()", testLAGER_dbCopy))
      
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if ((NULL == CU_add_test(pSuite2, "test of lager_add()", testLAGER_ADD)) ||
      (NULL == CU_add_test(pSuite2, "test of lager_equalDatabases()", testLAGER_equalDatabases)))
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


