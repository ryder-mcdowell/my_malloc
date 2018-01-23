#include "my_malloc.h"


int main() {
  printf("----------------------------------------\n");
  printf("----------------------------------------\n");
  int tacos[100];
  double burritos[200];
  double burgers[100];
  int hotdogs[200];
  char cheetos[1000];

  //printf("main: printing free list\n");
  //print_free_list();

  printf("main: allocating array of 100 doubles\n");
  void* burgers_pointer = my_malloc(100 * sizeof(double));
  printf("main: my memory starts at 0x%x\n", burgers_pointer);
  print_free_list();

  printf("main: allocating array of 100 integers\n");
  void* tacos_pointer = my_malloc(100 * sizeof(int));
  printf("main: my memory is at 0x%x\n", tacos_pointer);
  print_free_list();

  printf("main: allocating array of 1000 chars\n");
  void *cheetos_pointer = my_malloc(1000 * sizeof(char));
  printf("main: my memory is at 0x%x\n", cheetos_pointer);
  print_free_list();

  //printf("main: allocating array of 200 doubles\n");
  //void *pppp = my_malloc(200 * sizeof(double));
  //print_free_list();

  //uses all free space
  //printf("main: allocating array of 200 doubles\n");
  //void *pp = my_malloc(200 * sizeof(double));
  //print_free_list();

  //printf("main: printing free list\n");
  //print_free_list();



  return 0;
}
