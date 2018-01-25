#include "my_malloc.h"

void *head = NULL;

//TAKE space from free list, returns pointer to requested user-block
void *useFreeSpace(free_list_node *old_free_block, free_list_node *last, int size) {
  printf("-USEFREEPACE: taking %d from block @ 0x%x\n", size, old_free_block);
  free_list_node *new_free_block;
  free_list_node *new_user_block;


  //setup new free block
  if (old_free_block->size != size) {
    new_free_block = (void*)old_free_block + size + sizeof(free_list_node);
    new_free_block->size = old_free_block->size - size - sizeof(free_list_node);
    new_free_block->next = old_free_block->next;
    printf("-USEFREEPACE: free block updated with size %d and @ 0x%x\n", new_free_block->size, new_free_block);

    if (last == NULL) {
      head = new_free_block;
    } else {
      if (last != old_free_block) {
        last->next = new_free_block;
      }
    }
  //delete block
  } else {
    printf("-USEFREEPACE: free block completely used\n");
    if (last == NULL) {
      head = old_free_block->next;
    } else {
      head = last;
    }
  }


  //setup user's requested block
  new_user_block = (void*)old_free_block;
  new_user_block->size = size;
  new_user_block->next = NULL;


  return (void*)new_user_block + 16;
}

//ALLOCATE more space and append to free list, returns previous break point
void *allocateSpace(free_list_node *last) {
  printf("-ALLOCATESPACE: allocating new free block\n");
  free_list_node *new_block;

  void *previous_break = sbrk(SIZE);

  //create and setup new free block
  new_block = previous_break;
  new_block->size = SIZE - 16;
  new_block->next = NULL;


  printf("-ALLOCATESPACE: new free block created with size %d and @ 0x%x\n", new_block->size, new_block);

  //update last's pointer
  if (last != NULL) {
    last->next = new_block;
  }

  return previous_break;
}


void *my_malloc(int size) {
  void *user_space_break;
  void *previous_break;

  printf("MY_MALLOC: called with size = %d\n", size);
  printf("-my_malloc: head = 0x%x\n", head);


  //if no free list
  if (head == NULL) {
    printf("-my_malloc: no free list\n");

    //returns previous break, takes last of free list
    previous_break = allocateSpace(NULL);
    free_list_node *free_block = previous_break;

    head = previous_break;

    //returns location of user's requested space,
    user_space_break = useFreeSpace(free_block, NULL, size);


  //if free list
  } else {
    printf("-my_malloc: scanning free list...");
    free_list_node *free_block;
    free_list_node *last = NULL;
    free_list_node *current = head;

    //START SCAN
    while (current->next != NULL) {
      if (current->size >= size && last == NULL) {
        printf("found space in free list(first)\n");
        free_block = current;
        break;

      } else if (current->size >= size && last != NULL) {
        printf("found space in free list(middle)\n");
        free_block = current;
        break;

      } else {
        last = current;
        current = current->next;
      }
    }
    //only block in free list
    if (current->size >= size && last == NULL && free_block == NULL) {
      printf("found space in free list(only)\n");
      free_block = current;
    }
    //last block in free list
    if (current->size >= size && last != NULL && free_block == NULL) {
      printf("found space in free list(last)\n");
      free_block = current;
    }
    //END SCAN


    //if need more space (didn't find a free block)
    if (free_block != NULL) {
      printf("-my_malloc: free space is @ 0x%x\n", free_block);

      //returns location of user's requested space
      user_space_break = useFreeSpace(free_block, last, size);

    //if dont need more space (found a free block)
    } else {
      printf("not enough space in free list\n");
      last = current;

      //returns previous break
      previous_break = allocateSpace(last);
      free_list_node *free_block = previous_break;

      //returns location of user's requested space
      user_space_break = useFreeSpace(free_block, last, size);
    }
  }


  return user_space_break;
}

void my_free(void *ptr) {
  free_list_node* block = ptr - 16;
  printf("my_free: freeing memory @ 0x%x with size %d\n", block, block->size);

  //err check
  if (block->size < 1 || block->size > 2048) {
    printf("my_free: invalid pointer\n");
    exit(1);
  }

  free_list_node* current;
  current = head;

  printf("my_free: free size = %d\n", block->size);

  while (current->next != NULL) {
    current = current->next;
  }
  current->next = block;
  block->next = NULL;
}

void print_free_list() {
  free_list_node* current;
  int number;
  current = head;

  if (current != NULL) {
    printf("==========FREE LIST================================\n");
    printf("  NODE #  |      ADDRESS  |    SIZE  |         NEXT\n");
    while (current->next != NULL) {
      printf("       %d  |  0x  %7x  |    %4d  |  0x  %7x\n", number, current, current->size, current->next);
      current = current->next;
      number = number + 1;
    }
    printf("       %d  |  0x  %7x  |    %4d  |  0x  %7x\n", number, current, current->size, current->next);
    printf("===================================================\n");
  } else {
    printf("==========FREE LIST================================\n");
    printf("  NODE #  |      ADDRESS  |    SIZE  |         NEXT\n");
    printf("===================================================\n");
  }

}
