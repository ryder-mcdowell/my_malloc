#include "my_malloc.h"


int main() {
  printf("----------------------------------------\n");
  printf("----------------------------------------\n");
  int tacos[100];
  double burritos[200];
  double burgers[100];
  int hotdogs[200];
  char cheetos[1000];
  char chips[100];

  printf("main: printing free list\n");
  print_free_list();

  printf("main: allocating array of 200 doubles\n");
  void *burritos_pointer = my_malloc(sizeof(burritos));
  printf("main: my memory starts at 0x%x\n", burritos_pointer);
  print_free_list();

  //printf("main: allocating array of 400 chars\n");
  //cheetos_pointer = my_malloc(400 * sizeof(char));
  //printf("main: my memory is at 0x%x\n", cheetos_pointer);
  //print_free_list();

  printf("main: freeing chips\n");
  my_free(chips);
  print_free_list();



  return 0;
}
