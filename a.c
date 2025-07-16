#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int *data;
  int size;
} MyVector;

int main() {
  MyVector v;
  v.data = malloc(4*3);
  v.data[0] = 123;
  v.data[1] = 456;
  v.data[2] = 789;
  v.size = 3;
  return 0;
}
