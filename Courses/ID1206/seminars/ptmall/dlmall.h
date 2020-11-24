#ifndef DLMALL
#define DLMALL

#include <stddef.h>

struct head *new_arena();
struct head *split(struct head *block, int size);
void insert(struct head *block);
int adjust(size_t request);
void detach(struct head *block);
void *dalloc(size_t request);
void dfree(void *memory);
void init();
void sanity();
int length_of_free();
void sizes(int *buffer, int max);

#endif
