#include "my_malloc.h"
#include <time.h>


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

  printf("main: allocating array of 250 doubles\n");
  void *burritos_pointer = my_malloc(250 * sizeof(double));
  printf("main: my memory starts at 0x%x\n", burritos_pointer);
  print_free_list();

  printf("main: allocating array of 250 doubles\n");
  void *pointer = my_malloc(250 * sizeof(double));
  printf("main: my memory starts at 0x%x\n", pointer);
  print_free_list();

  printf("main: allocating array of 200 doubles\n");
  pointer = my_malloc(200 * sizeof(double));
  printf("main: my memory starts at 0x%x\n", pointer);
  print_free_list();

  printf("main: allocating array of 416 chars\n");
  pointer = my_malloc(416 * sizeof(char));
  printf("main: my memory starts at 0x%x\n", pointer);
  print_free_list();

  //void *pointer = my_malloc(254 * sizeof(double));
  //printf("main: my memory starts at 0x%x\n", pointer);
  //print_free_list();

  // void *chips_pointer = my_malloc(251 * sizeof(double));
  // printf("main: my memory starts at 0x%x\n", chips_pointer);
  // print_free_list();




  int iters = 1000;
  srand(time(NULL));
  int i;

  for (i = 0; i < iters; i++) {
    int r = rand() % 10;
    r = r * 100;
    printf("main: allocating array of %d chars\n", r);
    pointer = my_malloc(r * sizeof(char));
    printf("main: my memory is at 0x%x\n", pointer);
    print_free_list();
    my_free(pointer);
    print_free_list();
  }

  // printf("main: memory is at 0x%x\n", burritos_pointer);
  // printf("main: memory is at 0x%x\n", burritos_pointer - 16);
  // my_free(burritos_pointer);
  // printf("main: memory is at 0x%x\n", pointer);
  // printf("main: memory is at 0x%x\n", pointer - 16);
  // my_free(pointer);
  // print_free_list();






  return 0;
}
