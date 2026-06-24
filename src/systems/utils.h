#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "box2d/box2d.h"

#define TRIE_SIZE 36

#define int1 int8_t
#define int2 int16_t
#define int4 int32_t
#define uint1 uint8_t
#define uint2 uint16_t
#define uint4 uint32_t

typedef struct Node
{
	void *valueptr;					// Typecast to (datatype *)
	struct Node *next[TRIE_SIZE];	// Lowercases and decimal digits
} Trie;

typedef struct List
{
	void *valueptr;
	struct List *next;
} Stack;


// Data structures related functions
	//Trie
Trie *CreateTrie(void);											// Returns trie root that extensible by InsertTrie()
void InsertTrie(Trie *root, char *strpath, void *valueptr);		// Make a new branch to root and assign value valueptr
void *SearchTrie(Trie *root, char *strpath);					// Returns the value held by strpath, and NULL if not found
void FreeTrie(Trie *root);										// Free a trie and its branches recursively
int Hash(char c);												// Returns int; the index of c for trie insertion
	// Linked list A.K.A Stack
Stack *CreateStack(void);
void Push(Stack **head, void *valueptr);
void *Pop(Stack **head);
#define StackForEach(item, stack) for (item = (stack); item != NULL; item = (item)->next)

// Linear math related functions
int IntPower(int base, int exp);
int ExtractNumerics(char *string);

// String related function
void TruncateString(char *string, signed int cut);				// Cut string from index (cut)

// Vector related utilities
Vector2 B2vecToRlvec(b2Vec2 v);
b2Vec2 RlvecToB2vec(Vector2 v);

// Texture related utilities
Texture2D LoadPathTexture(char *path, char *filename);

// File handling utilities
char *GetStringFromFile(const char *absPath);					// CAUTION: needs to be freed by receiver

#endif
