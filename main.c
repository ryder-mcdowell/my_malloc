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


  fprintf(stderr, "main: printing free list\n");
  print_free_list();

  fprintf(stderr, "main: allocating array of 100 burgers\n");
  void *burgers_pointer = my_malloc(sizeof(burgers));
  fprintf(stderr, "main: printing free list:\n");
  print_free_list();

  fprintf(stderr, "main: allocating array of 100 tacos\n");
  void *tacos_pointer = my_malloc(sizeof(tacos));
  fprintf(stderr, "main: printing free list:\n");
  print_free_list();








  return 0;
}
