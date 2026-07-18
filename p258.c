  #include <stdio.h>
  int is_little_endian() {
      int x = 1;
      unsigned char *p = (unsigned char *)&x;
      return p[0] == 1;
  }
  int main() {
      printf("%d\n", is_little_endian());
      return 0;
  }
