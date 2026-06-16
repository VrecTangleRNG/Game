#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "box2d/box2d.h"

#define TRIE_SIZE 36

typedef struct Node
{
	void *valueptr;					// Typecast to (datatype *)
	struct Node *next[TRIE_SIZE];	// Lowercases and decimal digits
} Trie;

// Trie related functions
Trie *CreateTrie(void);				// Free memory using FreeTrie()
void InsertTrie(Trie *root, char *strpath, void *valueptr);
void *SearchTrie(Trie *root, char *strpath);
void FreeTrie(Trie *root);
int Hash(char c);

// Linear math related functions
int IntPower(int base, int exp);
int ExtractNumerics(char *string);

// String related function
void TruncateString(char *string, signed int cut);

// Vector related utilities
Vector2 B2vecToRlvec(b2Vec2 v);
b2Vec2 RlvecToB2vec(Vector2 v);

// Texture related utilities
Texture2D LoadPathTexture(char *path, char *filename);

// File handling utilities
char *GetStringFromFile(const char *absPath);	// CAUTION: needs to be freed by receiver

#endif