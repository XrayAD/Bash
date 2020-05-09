/*
 * A general purpose C unit testing framework developed for CPE 357 and
 * provided to students to expose them to and encourage their use of unit
 * testing and test driven development (TDD). While it was provided in
 * conjunction with the hash table project and associated exercise(s), students
 * are welcome and encourage to use and/or modify it, as they see fit, on
 * subsequent assignments in CPE 357 or anywhere else it they find it useful.
 *
 * Author: Kurt Mammen
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include "unitTest.h"
#include "hashTable.h"
#include "Hash.h"
#include "NumHash.h"
#define TEST_ALL -1
#define REGULAR -2 
#define SPECIAL -3

#define MAX_RANDOM_STR 72 /* Max length of any random string */

/* Prototype for all test functions. This allows the creation of an array of
 * function pointers which makes the testing code shorter and more clear. It
 * also makes it easier/faster to add new tests - NICE!
 */
typedef void (*TestFunc)();

/* Structure for a test. See initRegularTests and initSpecialTests to see
 * how it is used.
 */
typedef struct
{
   TestFunc fn;
   char *fnName;
} Test;

/* Modified hash algorithm from K&R (page 144). This version does NOT mod the
 * calculated hash value by the table size because it does not know the table
 * size - the caller (the hash table itself) does though!
 *
 * Also note the following:
 *   * This hash only works for C strings.
 *   * Not the best/fastest/most flexible hash - you'll want something better
 *     for the Word Frequency project.
 */
static unsigned dumbHash(const void *data)
{
   return 0;
}
static unsigned hashString(const void *data)
{
   unsigned hash;
   const char *str = data;

   for (hash = 0; *str;  str++)
      hash = *str + 31 * hash;

   /* Return the raw hash value - the modulo must be done by caller */
   return hash;
}

static int compareString(const void *a, const void *b)
{
   return strcmp(a, b);
}

/* Helper function to make random strings for robust testing. Strings will be
 * a minimum of 3 characters up to MAX_RANDOM_STR characters in length.
 */
static char* randomString()
{
   char *str;
   int i;
   int length = (rand() % MAX_RANDOM_STR - 2) + 10;

   if (NULL == (str = malloc(length + 1)))
   {
      perror("randomString()");
      exit(EXIT_FAILURE);
   }

   /* Put random but visible char values in the string */
   for (i = 0; i < length; i++)
      str[i] = (rand() % (' ' - '~' + 1)) + ' ';

   str[length] = 0; /* nul-terminate it! */

   return str; 
}

/* PROVIDED TEST (do not modify)
 *
 * This is a provided sample test that matches the Evaluation System's English
 * test description for the Hash Table project's core test01. I hope it is
 * obvious to you that this is but one of many many variations that one could
 * write that would satisfy the English test description. Recall that one of
 * the important goals of the Evaluation System is to provide you with guidance
 * on how to test you solution but still allow you the opportunity develop your
 * own tests in the hopes that doing so will create an efficient and fruitful
 * learning experience!
 */
static void core01()
{
   unsigned sizes[] = {7};
   HTFunctions funcs = {hashString, compareString, NULL};

   TEST_ERROR(htCreate(&funcs, sizes, -987, 0.73));
}

static void core02()
{
   unsigned sizes[] = {7};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 0, .73));
}

static void core03()
{
   unsigned sizes[] = {0};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 1, .35));
}

static void core04()
{
   unsigned sizes[] = {1,2,3,3};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 4, .35));
}

static void core05()
{
   unsigned sizes[] = {1,2,3,2};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 4, .75));
}

static void core06()
{
   unsigned sizes[] = {1,2,3,4};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 4, -1));
}

static void core07()
{
   unsigned sizes[] = {1};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 4, 0));
}

static void core08()
{
   unsigned sizes[] = {1};
   HTFunctions funcs = {hashString, compareString, NULL};
   TEST_ERROR(htCreate(&funcs, sizes, 4, 1.1));
}
static void assertAdd()
{
   
   unsigned sizes[] = {1};
   HTFunctions funcs = {hashString, compareString, NULL};
   HashTable ht;
   TEST_ERROR(htAdd(&ht, NULL));
}
static void assertLookUp()
{
   HashTable ht;
   TEST_ERROR(htLookUp(&ht, NULL));
}
static void add01()
{
   int x = 4;
   int freq;
   int *ptr= malloc(sizeof(int));
   *ptr = x;
   HashTable *ht;
   unsigned sizes[] = {8};
   HTFunctions funcs = {hash_num, comp_num, NULL};
   ht = htCreate(&funcs, sizes, 1, .75);
   TEST_UNSIGNED(ht->unique, 0);
   TEST_UNSIGNED(ht->totalentries, 0);
   TEST_UNSIGNED(ht->numsizes, 1);
   TEST_UNSIGNED(ht->loadfactor, .75);
   TEST_UNSIGNED((ht->sizelist)[0], 8);
   freq = htAdd(ht, ptr);
   TEST_UNSIGNED(ht->unique, 1);
   TEST_UNSIGNED(ht->totalentries, 1);
   TEST_UNSIGNED(freq,1 );
   freq = htAdd(ht, ptr);
   TEST_UNSIGNED(ht->unique, 1);
   TEST_UNSIGNED(ht->totalentries, 2);
   TEST_UNSIGNED(freq, 2);
   htDestroy(ht);
}
/* PROVIDED TEST (do not modify)
 *
 * This is a provided sample test that matches the Evaluation System's English
 * test description for the Hash Table project's core test11. I hope it is
 * obvious to you that this is but one of many many variations that one could
 * write that would satisfy the English test description. Recall that one of
 * the important goals of the Evaluation System is to provide you with guidance
 * on how to test you solution but still allow you the opportunity develop your
 * own tests in the hopes that doing so will create an efficient and fruitful
 * learning experience!
 */ 
static void core11()
{
   unsigned sizes[] = {31};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 1, 0.73);

   /* Do the test(s) */
   TEST_UNSIGNED(htCapacity(ht), 31);
   TEST_UNSIGNED(htUniqueEntries(ht), 0);
   TEST_UNSIGNED(htTotalEntries(ht), 0);

   htDestroy(ht);
}

/* PROVIDED TEST (do not modify)
 *
 * This is a provided sample test that matches the Evaluation System's English
 * test description for the Hash Table project's core test12. I hope it is
 * obvious to you that this is but one of many many variations that one could
 * write that would satisfy the English test description. Recall that one of
 * the important goals of the Evaluation System is to provide you with guidance
 * on how to test you solution but still allow you the opportunity develop your
 * own tests in the hopes that doing so will create an efficient and fruitful
 * learning experience!
 */ 
static void core12()
{
   int freq = 0;
   unsigned sizes[] = {11, 23};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, 0.73);

   /* Single entry */
   freq = htAdd(ht, randomString());

   TEST_UNSIGNED(freq, 1);
   TEST_UNSIGNED(htCapacity(ht), 11);
   TEST_UNSIGNED(htUniqueEntries(ht), 1);
   TEST_UNSIGNED(htTotalEntries(ht), 1);
   
   htDestroy(ht);
}

static void core14()
{
   char *str = malloc(sizeof(char)*3);
   char *str2 = malloc(sizeof(char)*3);
   *str='H';
   *(str+1)='i';
   *(str+2)='\0';
   *str2='H';
   *(str2+1)='i';
   *(str2+2)='\0';
   int freq = 0;
   unsigned sizes[]={11,23};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .73);
   freq = htAdd(ht, str);
   freq = htAdd(ht, str2);
   TEST_UNSIGNED(freq, 2);
   TEST_UNSIGNED(htCapacity(ht), 11);
   TEST_UNSIGNED(htUniqueEntries(ht), 1);
   TEST_UNSIGNED(htTotalEntries(ht), 2);

   htDestroy(ht);
   free(str2);
}

static void core15()
{

   char *str = malloc(sizeof(char)*3);
   char *str2 = malloc(sizeof(char)*3);
   *str='H';
   *(str+1)='i';
   *(str+2)='\0';
   *str2='H';
   *(str2+1)='O';
   *(str2+2)='\0';
   int freq = 0;
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .73);
   freq = htAdd(ht, str);
   freq = htAdd(ht, str2);
   TEST_UNSIGNED(freq, 1);
   TEST_UNSIGNED(htCapacity(ht), 11);
   TEST_UNSIGNED(htUniqueEntries(ht), 2);
   TEST_UNSIGNED(htTotalEntries(ht), 2);

   htDestroy(ht);
}
   
static void core16()
{
   int freq=0;
   char *some = "hi";
   unsigned sizes[]={11, 23};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .73);
   HTEntry sam = htLookUp(ht,some);
   TEST_UNSIGNED(sam.frequency, 0);
   TEST_BOOLEAN(sam.data ==NULL, 1);
   htDestroy(ht);
}

static void singleEntry()
{
   int freq;
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   freq = htAdd(ht, randomString());
   TEST_UNSIGNED(freq, 1);
   TEST_UNSIGNED(11, htCapacity(ht));
   TEST_UNSIGNED(1, htTotalEntries(ht));
   TEST_UNSIGNED(1, htUniqueEntries(ht));
   htDestroy(ht);
}

static void twoUnique()
{
   int freq;
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   freq = htAdd(ht, randomString());
   freq = htAdd(ht, randomString());
   TEST_UNSIGNED(freq, 1);
   TEST_UNSIGNED(11, htCapacity(ht));
   TEST_UNSIGNED(2, htTotalEntries(ht));
   TEST_UNSIGNED(2, htUniqueEntries(ht));
   htDestroy(ht);
}
static void twoDiffAdd()
{
   char *a = malloc(sizeof(char)*2);
   char *b = malloc(sizeof(char)*2);
   int freq;
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   *a='P';
   *(a+1)='\0';
   *b='P';
   *(b+1)='\0';
   htAdd(ht,a);
   freq = htAdd(ht, b);
   TEST_UNSIGNED(freq,2);
   TEST_UNSIGNED(htCapacity(ht),11);
   TEST_UNSIGNED(htUniqueEntries(ht),1);
   TEST_UNSIGNED(htTotalEntries(ht), 2);
   htDestroy(ht);
   free(b);
}

static void sameHash()
{
   char *a = malloc(sizeof(char)*2);
   char *b = malloc(sizeof(char)*2);
   int freq;
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   *a='P';
   *(a+1)='\0';
   *b='X';
   *(b+1)='\0';
   htAdd(ht,a);
   freq = htAdd(ht, b);
   TEST_UNSIGNED(freq,1);
   TEST_UNSIGNED(htCapacity(ht),11);
   TEST_UNSIGNED(htUniqueEntries(ht),2);
   TEST_UNSIGNED(htTotalEntries(ht), 2);
   htDestroy(ht);
}

static void emptyLookup()
{
   char *lol = "hey";
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   HTEntry sam = htLookUp(ht, lol);
   TEST_UNSIGNED(sam.frequency,0);
   TEST_BOOLEAN(sam.data==NULL, 1);
   htDestroy(ht);
}

static void fullLookup()
{
   char *sav = "herro";
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   HTEntry sam = htLookUp(ht, sav);
   TEST_UNSIGNED(sam.frequency,0);
   TEST_BOOLEAN(sam.data==NULL, 1);
   htDestroy(ht);
}

static void fullerLookup()
{
   char *a=malloc(sizeof(char)*2);
   char *b=malloc(sizeof(char)*2);
   char *c=malloc(sizeof(char)*2);
   *a='a';
   *(a+1)='\0';
   *b='b';
   *c='c';
   *(b+1)='\0';
   *(c+1)='\0';
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   htAdd(ht, a);
   htAdd(ht, a);
   htAdd(ht, a);
   htAdd(ht, b);
   htAdd(ht, b);
   htAdd(ht, c);
   HTEntry first = htLookUp(ht, a);
   HTEntry sec = htLookUp(ht, b);
   HTEntry th = htLookUp(ht, c);
   TEST_UNSIGNED(first.frequency, 3);
   TEST_UNSIGNED(sec.frequency, 2);
   TEST_UNSIGNED(th.frequency, 1);
   TEST_BOOLEAN(strcmp(a, first.data), 0);
   TEST_BOOLEAN(strcmp(b, sec.data), 0);
   TEST_BOOLEAN(strcmp(c, th.data), 0);
   TEST_BOOLEAN(a==first.data, 2);
   htDestroy(ht);
}

static void fullestLookup()
{
   char *a=malloc(sizeof(char)*2);
   char *b=malloc(sizeof(char)*2);
   char *c=malloc(sizeof(char)*2);
   char *d = malloc(sizeof(char)*2);
   *a='a';
   *(a+1)='\0';
   *b='a';
   *c='c';
   *d = 'c';
   *(d+1)='\0';
   *(b+1)='\0';
   *(c+1)='\0';
   unsigned sizes[] = {11,23};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   htAdd(ht,a);
   htAdd(ht,b);
   htAdd(ht,c);
   htAdd(ht,d);
   HTEntry sam = htLookUp(ht, b);
   HTEntry samuel = htLookUp(ht, d);
   TEST_UNSIGNED(sam.frequency, 2);
   printf("a: %p\n", a);
   printf("sam.data: %p\n", sam.data);
   TEST_BOOLEAN(a==sam.data,1);
   TEST_BOOLEAN(a==sam.data, 1);
   TEST_UNSIGNED(samuel.frequency, 2);
   TEST_BOOLEAN(strcmp(c,samuel.data),0);
   TEST_BOOLEAN(c==samuel.data, 1);
   printf("c: %p\n", c);
   printf("samuel.data: %p\n", samuel.data);
   htDestroy(ht);
   free(b);
   free(d);
}
static void hash()
{
   unsigned sizes[] = {3,4, 10};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   char *a=malloc(sizeof(char)*2);
   char *b=malloc(sizeof(char)*2);
   char *c=malloc(sizeof(char)*2);
   char *d=malloc(sizeof(char)*2);
   char *e=malloc(sizeof(char)*2);
   *a='a';
   *d='d';
   *(d+1)='\0';
   *e='e';
   *(e+1) = '\0';
   *(a+1)='\0';
   *b='b';
   *c='c';
   *(b+1)='\0';
   *(c+1)='\0';
   htAdd(ht,a);
   htAdd(ht,b);
   htAdd(ht,c);
   TEST_UNSIGNED(htCapacity(ht), 3);
   htAdd(ht,d);
   TEST_UNSIGNED(htCapacity(ht), 4);
   TEST_UNSIGNED(htUniqueEntries(ht), 4);
   TEST_UNSIGNED(htTotalEntries(ht), 4);
   HTEntry ax = htLookUp(ht, a);
   HTEntry bx = htLookUp(ht, b);
   HTEntry cx = htLookUp(ht, c);
   TEST_BOOLEAN(ax.data==a, 1);
   TEST_BOOLEAN(bx.data==b, 1);
   TEST_BOOLEAN(cx.data==c, 1);
   htAdd(ht,e);
   TEST_UNSIGNED(htCapacity(ht), 10);
   TEST_UNSIGNED(htUniqueEntries(ht), 5);
   TEST_UNSIGNED(htTotalEntries(ht), 5);
   ax = htLookUp(ht, a);
   bx = htLookUp(ht, b);
   cx = htLookUp(ht, c);
   HTEntry dx = htLookUp(ht, d);
   TEST_BOOLEAN(ax.data==a, 1);
   TEST_BOOLEAN(bx.data==b, 1);
   TEST_BOOLEAN(cx.data==c, 1);
   TEST_BOOLEAN(dx.data==d, 1);
   htDestroy(ht);
}

static void emptyArr()
{
   unsigned sizes[] = {3,4, 10};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   int size = 300;
   HTEntry *sam = htToArray(ht, &size);
   TEST_BOOLEAN(sam==NULL, 1);
   TEST_UNSIGNED(size, 0);
   htDestroy(ht);
}
static void colArr()
{
   unsigned sizes[] = {3,4, 10};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   int size = 300;
   char *a=malloc(sizeof(char)*2);
   char *b=malloc(sizeof(char)*2);
   char *c=malloc(sizeof(char)*2);
   char *d=malloc(sizeof(char)*2);
   *a='a';
   *d='a';
   *(d+1)='\0';
   *(a+1)='\0';
   *b='b';
   *c='c';
   *(b+1)='\0';
   *(c+1)='\0';
   htAdd(ht, a);
   htAdd(ht, d);
   htAdd(ht, b);
   htAdd(ht, c);
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   htAdd(ht, randomString());
   HTEntry *sam = htToArray(ht,&size);
   HTEntry john =htLookUp(ht, a);
   TEST_UNSIGNED(htTotalEntries(ht),8);
   TEST_UNSIGNED(htUniqueEntries(ht), 7);
   TEST_UNSIGNED(john.frequency, 2);
   TEST_UNSIGNED(size, 7);
   for (size=0; size<7;size++){
      if (sam[size].data == a){
         printf("ok found a..\n");
         TEST_UNSIGNED(sam[size].frequency, 2);
      }
   }
   htDestroy(ht);
   free(d);
   free(sam);
}
static void time01(){
   unsigned sizes[] = {1000,2000};
   HTFunctions funcs = {hash_num, comp_num, NULL};
   void *ht = htCreate(&funcs, sizes, 2, .75);
   int i; int j = 4;
   for (i=0;i<10000;i++){
      j++;
      int *ptr = malloc(sizeof(int));
      *ptr = j;
      htAdd(ht, ptr);
   }
   htDestroy(ht);
}
static void time02(){
   unsigned sizes[] = {1000,2000, 10000};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   int i;
   for (i=0;i<10000;i++){
      htAdd(ht, randomString());
   }
   int size=5l;
   HTEntry *arr = htToArray(ht, &size);
   free(arr);
   htDestroy(ht);
}
static void time03(){
   unsigned sizes[] = {10000,20000, 25000};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   int i;
   for (i=0;i<100000;i++){
      htAdd(ht, randomString());
   }
   htDestroy(ht);
}
static void heap03(){
   unsigned sizes[] = {97, 433, 739, 2063, 8123, 16427, 29873, 103669, 188463};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 9, .75);
   int j, i;
   for (i=0;i<100000;i++){
      char *herro = randomString();
      j = htAdd(ht, herro);
      if (j>1)
         free(herro);
   }
   htDestroy(ht);
}
static void heap04(){
   unsigned sizes[] = {97, 433, 739, 2063, 8123, 16427, 29873, 103669, 188463, 387503, 980197};
   int i;
   int j;
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 11, .1);
   for (i=0;i<1000000;i++){
      char *herro = randomString();
      j = htAdd(ht, herro);
      if (j > 1)
         free(herro);
   }
   HTEntry *sam = htToArray(ht,&i);
   free(sam);
   htDestroy(ht);
}
static void time04(){
   unsigned sizes[] = {10000,20000, 300000};
   int i;
   HTFunctions funcs = {hash_num, comp_num, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   for (i=0;i<1000000;i++){
      int *ptr = malloc(sizeof(int));
      *ptr = i;
      htAdd(ht, ptr);
   }
   htDestroy(ht);
}
static void met()
{
   unsigned sizes[] = {3,4, 10};
   HTFunctions funcs = {hashString, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   HTMetrics sam = htMetrics(ht);
   TEST_UNSIGNED(sam.numberOfChains, 0);
   TEST_UNSIGNED(sam.maxChainLength, 0);
   TEST_REAL(0, sam.avgChainLength, FLT_EPSILON);
   htDestroy(ht);
}
static void metCheck()
{
   unsigned sizes[] = {4,8, 10};
   HTFunctions funcs = {dumbHash, compareString, NULL};
   void *ht = htCreate(&funcs, sizes, 3, .75);
   int size = 300;
   char *a=malloc(sizeof(char)*2);
   char *b=malloc(sizeof(char)*2);
   char *c=malloc(sizeof(char)*2);
   char *d=malloc(sizeof(char)*2);
   *a='a';
   *d='a';
   *(d+1)='\0';
   *(a+1)='\0';
   *b='b';
   *c='c';
   *(b+1)='\0';
   *(c+1)='\0';
   htAdd(ht,a);
   htAdd(ht,d);
   htAdd(ht,c);
   HTMetrics sam = htMetrics(ht);
   TEST_REAL(sam.avgChainLength, 2, FLT_EPSILON);
   TEST_UNSIGNED(sam.maxChainLength, 2);
   TEST_UNSIGNED(sam.numberOfChains, 1);
   htAdd(ht, b);
   sam = htMetrics(ht);
   TEST_REAL(sam.avgChainLength, 3, FLT_EPSILON);
   TEST_UNSIGNED(sam.maxChainLength, 3);
   TEST_UNSIGNED(sam.numberOfChains, 1);
   htDestroy(ht);
   free(d);

}
static void testAll(Test* tests)
{
   int i;

   for (i = 0; tests[i].fn != NULL; i++)
   {
      printf("Running regular %s\n", tests[i].fnName);

      /* Call the test function via function pointer in the array */
      tests[i].fn();
   }
}

static void findAndCall(Test* tests, const char *type, char *fnName)
{
   int i;

   for (i = 0; tests[i].fn != NULL; i++)
   {
      if (0 == strcmp(tests[i].fnName, fnName))
      {
         /* Found it, call the function via function pointer... */
         printf("Running %s %s\n", type, fnName);
         tests[i].fn();
         return;
      }
   }

   fprintf(stderr, "ERROR %s %s: Function not found\n", type, fnName);
   exit(EXIT_FAILURE);
}

static void runTests(Test *tests, const char *type, char *fnName)
{
   if (fnName == NULL)
      testAll(tests);
   else
      findAndCall(tests, type, fnName);

   /* Free the tests (allocated in initTests) */
   free(tests);
}

static char* checkArgs(int argc, char *argv[], int *testType)
{
   char *testName;

   if (argc == 1)
   {
      *testType = REGULAR;      
      testName = NULL;
   }
   else if (argc == 2)
   {
      *testType = REGULAR; 
      testName = argv[1];
   }
   else if (argc == 3)
   {
      if (0 != strcmp(argv[1], "-special"))
      {
         fprintf(stderr, "Invalid option '%s'\n", argv[1]);
         exit(EXIT_FAILURE);
      }
      
      *testType = SPECIAL;
      testName = argv[2];
   }
   else
   {
      fprintf(stderr, "Usage: %s [testName | -special testName]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   return testName;
}

Test* initTests(Test tests[], int size)
{
   Test *dynamicMemory = malloc(size);

   if (dynamicMemory == NULL)
   {
      fprintf(stderr, "FAILURE in %s at %d: ", __FILE__, __LINE__);
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   return memcpy(dynamicMemory, tests, size);
}

/* Allocates, initializes, and returns the array of regular test functions.
 * Regular test functions are those that are expected to pass or report failure
 * BUT NOT terminate the test driver.
 *
 * By default, the test driver runs ALL of the regular tests. Alternatively, you
 * can run one at a time by simply specifying its name when you invoke the
 * test driver.
 *
 * See initSpecialTests for tests that you always want to run individually.
 *
 * NOTE: The last structure in the array must have NULL values as this indicates
 *    the array's end.
 *
 * IMPORTANT SUBTLETY: You can only use sizeof to obtain an array's size in
 *    the scope where the array is declared, otherwise you will just get
 *    the size of the pointer to the array.
 */
Test* initRegularTests()
{
   Test local[] = {
      {core11, "core11"},
      {core12, "core12"},
      {core14, "core14"},
      {core15, "core15"},
      {core16, "core16"},
      {add01, "add01"},
      {singleEntry, "singleEntry"},
      {twoUnique, "twoUnique"},
      {twoDiffAdd, "twoDiffAdd"},
      {sameHash, "sameHash"},
      {emptyLookup, "emptyLookup"},
      {fullLookup, "fullLookup"},
      {fullerLookup, "fullerLookup"},
      {fullestLookup, "fullestLookup"},
      {hash, "hash"},
      {emptyArr, "emptyArr"},
      {colArr, "colArr"},
      {met, "met"},
      {metCheck, "metCheck"},
      {time01, "time01"},
      {time02, "time02"},
      {time03, "time03"},
      {time04, "time04"},
      {heap03, "heap03"},
      {heap04, "heap04"},
      {NULL, NULL}
   };

   /* See IMPORTANT SUBTLETY above regarding the use of sizeof on arrays */
   return initTests(local, sizeof(local));
}

/* Allocates, initializes, and returns the array of special test functions.
 * Special test functions are those that you want to run individually for one
 * reason or another. For example, a test to see if a function asserts failure
 * when it is supposed to. Or, a test intended to measure CPU or memory
 * performance using tools like the Unix time command or Valgrind - for
 * tests like these you only want to run the single test and then observe the
 * results.
 *
 * See initRegularTests for tests that can together.
 *
 * NOTE: The last structure in the array must have NULL values as this indicates
 *    the array's end.
 *
 * IMPORTANT SUBTLETY: You can only use sizeof to obtain an array's size in
 *    the scope where the array is declared, otherwise you will just get
 *    the size of the pointer to the array.
 */
Test* initSpecialTests()
{
   Test local[] = {
      {core01, "core01"},
      {core02, "core02"},
      {core03, "core03"},
      {core04, "core04"},
      {core05, "core05"},
      {core06, "core06"},
      {core07, "core07"},
      {core08, "core08"},
      {assertAdd, "assertAdd"},
      {assertLookUp, "assertLookUp"},
      {NULL, NULL}
   };

   /* See IMPORTANT SUBTLETY above regarding the use of sizeof on arrays */
   return initTests(local, sizeof(local)); 
}

/* Test driver for Hash Table Project.
 *
 * Usage: testHashTable [functionName | -special functionName]
 *
 * When no option is specified ALL of the regular tests are run.
 * When "functionName" is specified that single regular test is run.
 * When "-special functionName" is specified that single special test is run.
 *
 * What TODO: As provided with the Unit Test Hash Table exercise, this unit test
 * driver provides several working examples of actual Evaluation System tests
 * for the Hash Table project. The exercise asks you to develop a few more so
 * that you can experience how easy it is to develop unit tests BEFORE you even
 * implement any actual code for the solution being tested. The hope is that
 * this will encourage you to develop tests early and often as you develop your
 * Hash Table project solution thereby adding unit testing and Test Driven
 * Development (TDD) to your personal repertoire of programming skills! 
 *    
 * To add a new test you must:
 * 
 *    1) Write a test function.
 *    2) Add its name to the appropriate array of test functions, see
 *       initRegularTests and initSpecialTests for details.
 *    3) Compile and test your test by verifying:
 *          1. It report failure when run on code known to be incorrect.
 *          2. It passes (does NOT report failure) when run on code believed to
 *             be correct.
 *    4) Be sure use Valgrind, where appropriate, to check for memory errors
 *       and/or leaks too!
 */
int main(int argc, char *argv[])
{
   char *testName;
   int testType;

   /* Random numbers used to produce "interesting" strings for testing */
   srand(182955);

   /* Make stdout unbuffered so that test output is synchronous on signals */
   setbuf(stdout, NULL);

   /* Get the test name type */
   testName = checkArgs(argc, argv, &testType);
 
   /* Run the test(s)... */
   if (testType == REGULAR)
      runTests(initRegularTests(), "regular", testName);
   else
      runTests(initSpecialTests(), "special", testName);
   
   return 0;
}
