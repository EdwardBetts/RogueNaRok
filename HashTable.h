#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"


typedef struct hash_el
{
  unsigned int fullKey;
  void *value;
  struct hash_el *next;
} HashElem;

typedef struct hash_table
{
  unsigned int tableSize;
  unsigned int entryCount;
  void *commonAttributes;
  unsigned int (*hashFunction)(struct hash_table *h, void *value);
  boolean (*equalFunction)(struct hash_table *hashtable, void *entrA, void *entryB);
  HashElem **table;
#ifdef PARALLEL
  pthread_mutex_t **lockPerSlot;
  pthread_mutex_t *cntLock; 
#endif
} HashTable;

typedef struct 
{
  HashTable *hashTable;
  HashElem *hashElem;
  unsigned int index;
} HashTableIterator;

#define FOR_HASH(htIter, hashtable)  boolean hasNext = TRUE; for(htIter = createHashTableIterator(hashtable); htIter && hasNext ; hasNext = hashTableIteratorNext(htIter))
#define FOR_HASH_2(htIter, hashtable)  hasNext = TRUE; for(htIter = createHashTableIterator(hashtable); hasNext ; hasNext = hashTableIteratorNext(htIter))

HashTable *createHashTable(unsigned int size, void *commonAttr, unsigned int (*hashFunction)(HashTable *hash_table, void *value), boolean (*equalFunction)(HashTable *hash_table, void *entryA, void *entryB));
HashTableIterator *createHashTableIterator(HashTable *hashTable); 
void *getCurrentValueFromHashTableIterator(HashTableIterator *hashTableIterator);
boolean hashTableIteratorNext(HashTableIterator *hashTableIterator);
void *searchHashTableWithInt(HashTable *hashtable, unsigned int hashValue);
void *searchHashTable(HashTable *hashtable, void *value, unsigned int hashValue);
void insertIntoHashTable(HashTable *hashTable, void *value, unsigned int index);
boolean removeElementFromHash(HashTable *hashtable, void *value);
void destroyHashTable(HashTable *hashTable, void (*freeValue)(void *value));

#endif
