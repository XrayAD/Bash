#include "NumHash.h"
int comp_num(const void *data1, const void *data2){
   int num1 = (*(int *)data1);
   int num2 = (*(int *)data2);
   return num1-num2;
}

unsigned hash_num(const void *data){
   int num =(*(int *)data);
   return num*97;
}

unsigned badhash(const void *data){
   return 0;
}
