#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5

int main() {
  char *buffer[MAX_LINES];
  int count = 0;
  int head = 0;

  char *input = NULL;
  size_t capacity = 0;

  for (int i = 0; i < MAX_LINES; i++) {
    buffer[i] = NULL;
  }

  while (1) {
    printf("Enter input: ");
    fflush(stdout);

    ssize_t nread = getline(&input, &capacity, stdin);
    if (nread == -1) {
      printf("\n");
      break;
    }

    if (nread > 0 && input[nread - 1] == '\n') {
      input[nread - 1] = '\0';
    }

    int slot;
    if (count < MAX_LINES) {
      slot = count;
      count++;
    } else {
      slot = head;
      head = (head + 1) % MAX_LINES;
    }
    free(buffer[slot]);
    buffer[slot] = strdup(input);

    if (strcmp(input, "print") == 0) {
      for (int i = 0; i < count; i++) {
        int idx = (head + i) % MAX_LINES;
        printf("%s\n", buffer[idx]);
      }
    }
  }

  free(input);
  for (int i = 0; i < MAX_LINES; i++) {
    free(buffer[i]);
  }

  return 0;
}
