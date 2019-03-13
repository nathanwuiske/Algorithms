#ifndef structs_H
#define structs_H
const int maximum = 5000;
struct component {
  int storeP;
  int storeM;
};

struct secondArray {
  component *element;
  int totalSize;
};

struct firstArray {
  int *element;
  int totalSize;
};

struct fArray {
  int element[maximum];
  int totalSize;
};

#endif
