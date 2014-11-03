/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  addr_t i;
  flush_cache();
  access_cache(0);
  i = 1;
  while (TRUE) { // focus on one block
    if (!access_cache(i)) { // break if we step over this block
      break;
    }
    i++;
  }
  return i;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */

  addr_t block_size = size;
  addr_t cache_size = block_size;
  while (TRUE) {
    flush_cache();
    access_cache(0);
    //access_cache(cache_size);
    addr_t i = block_size;
    while (i <= cache_size) { // fulfill the cache. we need this loop to evade the influence of multi-associality
      access_cache(i);
      i += block_size;
    }
    //printf("%llu\n", cache_size);
    if (!access_cache(0)) { // initial cached block is retired
      break;
    }
    cache_size <<= 1;
  }  
  return cache_size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int cache_size = size;
  int assoc = 1;
  while (TRUE) {
    flush_cache();
    access_cache(0);
    int i;
    for (i=1; i<=assoc; ++i) {
      access_cache(cache_size * i);
    }
    if (!access_cache(0)) { // first block is retired
      break;
    }
    assoc <<= 1;
  }
  return assoc;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
