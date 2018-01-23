#include "my_malloc.h"

void* head = NULL;

//TAKE space from free list, returns pointer to new user-block
void* takeSpace(free_list_node *node, int size) {
  free_list_node *new;
  void* node_break;
  node_break = node;

  //set location of new free space
  new = node_break + size + 16 + 1;
  printf("ryder: new brk = 0x%x\n", new);
  //set new free space block values
  new->size = node->size - size - 16;
  printf("ryder: new size = %d\n", new->size);
  new->next = NULL;
  printf("ryder: new next = %d\n", new->next);

  return new;
}

void* allocateSpace() {
  void* previous_break;
  free_list_node *node;

  previous_break = sbrk(SIZE);
  printf("ryder: prev_brk = 0x%x\n", previous_break);

  //set node pointer to start of new memory
  node = previous_break;
  //set nodes values
  node->size = SIZE - 16;
  printf("ryder: node size = %d\n", node->size);
  node->next = NULL;
  printf("ryder: node next = %d\n", node->next);

  return node;
}

void *my_malloc(int size) {
  free_list_node *node;
  free_list_node *previous;
  free_list_node *current;
  void* previous_break;
  void* return_break;



  printf("my_malloc: called with size = %d\n", size);
  printf("ryder: head = 0x%x\n", head);

  //SCAN
  //if no free list exists
  if (head == NULL) {
    printf("my_malloc: allocating new free list\n");

    node = allocateSpace();

    head = takeSpace(node, size);

    return_break = previous_break;


  } else {
    //set current as first node for scanning
    current = head;
    //check and move current until a big enough block or on last node
    while (current->next != NULL) {

      if (current->size >= size) {
        node = current;
      }
      current = current->next;

    }
    //if fits in last block, take free space
    if (current->size >= size) {
      node = current;
      printf("bingo\n");
      //
    //else, doesn't fit in any blocks, allocated more

    } else {
      printf("ahhh shit, need more memory\n");
    }

  }





  return return_break;
}

void my_free(void *ptr) {


}

void print_free_list() {
  printf("==========FREE LIST==============================\n");
  printf("NODE #  |      ADDRESS  |   SIZE  |      NEXT\n");
  printf("=================================================\n");

}
