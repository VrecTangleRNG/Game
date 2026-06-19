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
#include "box2d/box2d.h"

#define TRIE_SIZE 36

#define smalluint uint8_t
#define meduint uint16_t

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
Trie *CreateTrie(void);
void InsertTrie(Trie *root, char *strpath, void *valueptr);
void *SearchTrie(Trie *root, char *strpath);
void FreeTrie(Trie *root);
int Hash(char c);
	// Linked list A.K.A Stack
Stack *CreateStack(void);
void Push(Stack **head, void *valueptr);
void *Pop(Stack **head);
#define StackForEach(item, stack) for (item = (stack); item != NULL; item = (item)->next)

// Linear math related functions
int IntPower(int base, int exp);
int ExtractNumerics(char *string);

// String related function
void TruncateString(char *string, signed int cut);				// Cut string from index "cut"

// Vector related utilities
Vector2 B2vecToRlvec(b2Vec2 v);
b2Vec2 RlvecToB2vec(Vector2 v);

// Texture related utilities
Texture2D LoadPathTexture(char *path, char *filename);

// File handling utilities
char *GetStringFromFile(const char *absPath);	// CAUTION: needs to be freed by receiver

#endif
