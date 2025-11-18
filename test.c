#include <stdio.h>

int main() {
  char test_chars[] = {'c', '$', '@', '_', 'Z', '1', '#'};
  int n = sizeof(test_chars) / sizeof(test_chars[0]);

  for (int i = 0; i < n; i++) {
    char x = test_chars[i];
    if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || x == '_') {
      printf("Character '%c' passes the identifier check.\n", x);
    } else {
      printf("Character '%c' does NOT pass the identifier check.\n", x);
    }
  }

  return 0;
}
