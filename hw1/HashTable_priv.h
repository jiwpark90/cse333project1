/*
 * Copyright 2011 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HW1_HASHTABLE_PRIV_H_
#define _HW1_HASHTABLE_PRIV_H_

#include "./LinkedList.h"
#include "./HashTable.h"

// Define the internal, private structs and helper functions associated with a
// HashTable.

// This is the struct that we use to represent a hash table. Quite simply, a
// hash table is just an array of buckets, where each bucket is a linked list
// of HTKeyValue structs.
typedef struct htrec {
  uint64_t        num_buckets;   // # of buckets in this HT?
  uint64_t        num_elements;  // # of elements currently in this HT?
  LinkedList     *buckets;       // the array of buckets
} HashTableRecord;

// This is the struct we use to represent an iterator.
typedef struct ht_itrec {
  bool       is_valid;    // is this iterator valid?
  HashTable  ht;          // the HT we're pointing into
  uint64_t   bucket_num;  // which bucket are we in?
  LLIter     bucket_it;   // iterator for the bucket, or NULL
} HTIterRecord;

// This is the internal hash function we use to map from uint64_t keys to a
// bucket number.
uint64_t HashKeyToBucketNum(HashTable ht, uint64_t key);

// This is an internal helper function used to check if a certain key is already
// mapped to a value in the given LinkedList, and optionally remove it if the caller
// wishes to.
//
// Arguments:
//
// - chain: the LinkedList to look through
//
// - key: the key to look up
//
// - resultkeyvalue: if the key is present, the pointer to the payload is passed
//   via this parameter
//
// - removeonfind: if the function finds the target payload, it also removes it if
//   this parameter is set to true
//
// Returns:
//
// - -1 if there was an err (e.g., out of memory)
//
// - 0 if the key was not found in the list
//
// - +1 if the key was found in the list
int LookupKey(LinkedList chain, uint64_t key, HTKeyValue **resultkeyvalue, bool removeonfind);

#endif  // _HW1_HASHTABLE_PRIV_H_
