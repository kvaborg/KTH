#ifndef DLMALL
#define DLMALL

#include <stddef.h>

struct head *new_arena();
struct head *split(struct head *block, int size);
int adjust(size_t request);
void detach(struct head *block);
void *dalloc(size_t request);
void dfree(void *memory);
void sanity();

#endif
