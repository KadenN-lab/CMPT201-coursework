#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

#define SIZE 256
#define BLOCKS 2
#define BLOCK_SIZE (SIZE / BLOCKS)
#define DATA_SIZE (BLOCK_SIZE - sizeof(struct header))

int main() {
  void *heap_start = sbrk(SIZE);
  if (heap_start == (void *)-1) {
    perror("sbrk");
    return 1;
  }

  struct header *one = (struct header *)heap_start;
  struct header *two = (struct header *)((char *)heap_start + BLOCK_SIZE);

  char *one_data = (char *)(one + 1);
  char *two_data = (char *)(two + 1);

  one->size = BLOCK_SIZE;
  one->next = NULL;

  two->size = BLOCK_SIZE;
  two->next = one;

  memset(one_data, 0, DATA_SIZE);
  memset(two_data, 1, DATA_SIZE);

  printf("first block:        %p\n", (void *)one);
  printf("second block:       %p\n", (void *)two);

  printf("first block size:   %lu\n", one->size);
  printf("first block next:   %p\n", (void *)one->next);
  printf("second block size:  %lu\n", two->size);
  printf("second block next:  %p\n", (void *)two->next);

  for (size_t i = 0; i < DATA_SIZE; i++) {
    printf("%d\n", (unsigned char)one_data[i]);
  }
  for (size_t i = 0; i < DATA_SIZE; i++) {
    printf("%d\n", (unsigned char)two_data[i]);
  }

  return 0;
}
