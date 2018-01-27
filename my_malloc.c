#include "my_malloc.h"

void *head = NULL;

//TAKE space from free list, returns pointer to requested user-block
void *useFreeSpace(free_list_node *old_free_block, free_list_node *last, int size) {
  free_list_node *new_free_block;
  free_list_node *new_user_block;

  //setup new free block if not same size
  if (old_free_block->size != size) {
    new_free_block = (void*)old_free_block + size + sizeof(free_list_node);
    new_free_block->size = old_free_block->size - size - sizeof(free_list_node);
    new_free_block->next = old_free_block->next;

    if (last == NULL) {
      head = new_free_block;
    } else {
      if (last != old_free_block) {
        last->next = new_free_block;
      }
    }
  //"delete" block if exact size
  } else {
    if (last == NULL) {
      head = old_free_block->next;
    } else {
      last->next = old_free_block->next;
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
  free_list_node *new_block;

  void *previous_break = sbrk(SIZE);
  if (previous_break == (void*)-1) {
    return NULL;
  }

  //create and setup new free block
  new_block = previous_break;
  new_block->size = SIZE - 16;
  new_block->next = NULL;


  //update last's pointer
  if (last != NULL) {
    last->next = new_block;
  }

  return previous_break;
}


void *my_malloc(int size) {
  if (size < 0) {
    return NULL;
  }
  if (size > 2032) {
    fprintf(stderr, "Error: my_malloc doesn't support memory allocation larger than 2032 bytes\n");
    return NULL;
  }

  fprintf(stderr, "my_malloc: called with size = %d\n", size);
  void *user_space_break;
  void *previous_break;


  //if no free list
  if (head == NULL) {
    fprintf(stderr, "my_malloc: allocating new free list\n");

    //returns previous break, takes last of free list
    previous_break = allocateSpace(NULL);
    free_list_node *free_block = previous_break;

    head = previous_break;

    fprintf(stderr, "my_malloc: scanning free list...found space in free list\n");

    //returns location of user's requested space,
    user_space_break = useFreeSpace(free_block, NULL, size);


  //if free list
  } else {
    fprintf(stderr, "my_malloc: scanning free list...");
    free_list_node *free_block = NULL;
    free_list_node *last = NULL;
    free_list_node *current = head;

    //START SCAN
    while (current->next != NULL) {
      //first block in free list
      if ( (current->size >= size + 16 && last == NULL) || (current->size == size && last == NULL) ) {
        fprintf(stderr, "found space in free list.\n");
        free_block = current;
        break;

      //middle block in free list
      } else if ( (current->size >= size + 16 && last != NULL) || (current->size == size && last != NULL) ) {
        fprintf(stderr, "found space in free list.\n");
        free_block = current;
        break;

      //keep searching
      } else {
        last = current;
        current = current->next;
      }
    }
    //only block in free list
    if ( (current->size >= size + 16 && last == NULL && free_block == NULL) || (current->size == size && last == NULL && free_block == NULL) ) {
      fprintf(stderr, "found space in free list.\n");
      free_block = current;
    }
    //last block in free list
    if ( (current->size >= size + 16 && last != NULL && free_block == NULL) || (current->size == size && last != NULL && free_block == NULL) ) {
      fprintf(stderr, "found space in free list.\n");
      free_block = current;
    }
    //END SCAN


    //if dont need more space (found a free block)
    if (free_block != NULL) {

      //returns location of user's requested space
      user_space_break = useFreeSpace(free_block, last, size);


    //if need more space (didn't find a free block)
    } else {
      fprintf(stderr, "no space in free list.\n");
      fprintf(stderr, "my_malloc: calling sbrk() to expand heap...\n");
      last = current;

      //returns previous break
      previous_break = allocateSpace(last);
      free_list_node *free_block = previous_break;

      fprintf(stderr, "my_malloc: scanning free list...found space in free list\n");
      //returns location of user's requested space
      user_space_break = useFreeSpace(free_block, last, size);
    }
  }


  return user_space_break;
}

void my_free(void *ptr) {
  free_list_node* block = ptr - 16;
  fprintf(stderr, "my_free: called with 0x%x, size = %d\n", ptr, block->size);

  //err check
  if (block->size < 0 || block->size > 2032) {
    fprintf(stderr, "my_free: invalid pointer: 0x%x\n");
    exit(1);
  }

  free_list_node* current;
  current = head;

  while (current->next != NULL) {
    current = current->next;
  }
  current->next = block;
  block->next = NULL;
  fprintf(stderr, "my_free: next = 0x%x\n", block->next);
}

void print_free_list() {
  free_list_node* current;
  int number = 0;
  current = head;

  if (current != NULL) {
    fprintf(stderr, "==========FREE LIST==================================\n");
    fprintf(stderr, "    NODE #  |      ADDRESS  |    SIZE  |         NEXT\n");
    while (current->next != NULL) {
      fprintf(stderr, "       %3d  |  0x  %7x  |    %4d  |  0x  %7x\n", number, current, current->size, current->next);
      current = current->next;
      number = number + 1;
    }
    fprintf(stderr, "       %3d  |  0x  %7x  |    %4d  |  0x  %7x\n", number, current, current->size, current->next);
    fprintf(stderr, "=====================================================\n");
  } else {
    fprintf(stderr, "==========FREE LIST==================================\n");
    fprintf(stderr, "  NODE #  |      ADDRESS  |    SIZE  |         NEXT\n");
    fprintf(stderr, "=====================================================\n");
  }

}
