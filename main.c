#include "my_malloc.h"


int main() {
  printf("----------------------------------------\n");
  int tacos[100];
  double burritos[200];

  //printf("main: printing free list\n");
  //print_free_list();

  printf("main: allocating array of 100 integers\n");
  void *p = my_malloc(100 * sizeof(int));

  printf("main: allocating array of 300 doubles\n");
  void *pp = my_malloc(200 * sizeof(double));

  //printf("main: printing free list\n");
  //print_free_list();



  return 0;
}
