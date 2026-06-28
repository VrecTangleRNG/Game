/* --- Header files --- */

#include "utils.h"
/* --- ------------ --- */

/* --- Main methods --- */

Trie *CreateTrie(void)
{
	Trie *root = malloc(sizeof(Trie));
	if (!root) {printf("Unable to create Trie"); return NULL;}
	root->valueptr = NULL;
	for (int i = 0; i < TRIE_SIZE; i++)
	{
		root->next[i] = NULL;
	}
	return root;
}

void InsertTrie(Trie *root, char *strpath, void *valueptr)
{
	Trie *main = root;
	for (size_t i = 0; i < strlen(strpath); i++)
	{
		uint1 travPos = Hash(strpath[i]);
		if (main->next[travPos] == NULL) main->next[travPos] = CreateTrie();
		main = main->next[travPos];
		if (!main) return;
	}
	main->valueptr = valueptr;
}

void *SearchTrie(Trie *root, char *strpath)
{
	int i = 0;
	Trie *main = root;
	for (int i = 0; i < strlen(strpath); i++)
	{
		int travPos = Hash(strpath[i]);
		main = main->next[travPos];
		if (!main) return NULL;
	}
	return main->valueptr;
}

void FreeTrie(Trie *root)
{
	for (int i = 0; i < TRIE_SIZE; i++)
	{
		Trie *main = root->next[i];
		if (main) FreeTrie(main);
	}
	free(root);
}

int Hash(char c)
{
	if (isalpha(c)) return toupper(c) - 'A';
	else if (isdigit(c)) return c - '0' + 26;
}

Stack *CreateStack(void)
{
	Stack *base = calloc(1, sizeof(Stack));
	if (!base) {printf("Unable to create Stack"); return NULL;}
	return base;
}

void Push(Stack **head, void *valueptr)
{
	Stack *buffer = CreateStack();
	if (buffer != NULL)
	{
		buffer->valueptr = valueptr;
		buffer->next = *head;
		*head = buffer;
	}
}

void *Pop(Stack **head)
{
	if (!head || !(*head)) return NULL;
	Stack *temp = *head;
	void *valueptr = temp->valueptr;
	*head = (*head)->next;
	if (temp) free(temp);
	return valueptr;
}

Deque *CreateDeque(void)
{
	Deque *buffer = calloc(1, sizeof(Deque));
	if (!buffer) {printf("Unable to create Deque"); return NULL;}
	return buffer;
}

void InsertFrontDq(Deque **dq, void *valueptr)
{
	Deque *temp = *dq;
	DLL *buffer = malloc(sizeof(DLL));
	if (!buffer) {printf("Unable to create DLL"); return;}
	buffer->valueptr = valueptr;
	if (temp->count == 0)
	{
		temp->front = temp->rear = buffer;
		temp->count = 1;
		buffer->next = buffer->prev = NULL;
	}
	else
	{
		buffer->next = temp->front;
		buffer->prev = NULL;
		temp->front = temp->front->prev = buffer;
		temp->count++;
	}
}

void InsertRearDq(Deque **dq, void *valueptr)
{
	Deque *temp = *dq;
	DLL *buffer = malloc(sizeof(DLL));
	if (!buffer) {printf("Unable to create DLL"); return;}
	buffer->valueptr = valueptr;
	if (temp->count == 0)
	{
		temp->rear = temp->front = buffer;
		temp->count = 1;
		buffer->next = buffer->prev = NULL;
	}
	else
	{
		buffer->prev = temp->rear;
		buffer->next = NULL;
		temp->rear = temp->rear->next = buffer;
		temp->count++;
	}
}

void *PopFrontDq(Deque **dq)
{
	Deque *temp = *dq;
	DLL *buffer = temp->front;
	if (temp->count > 1)
	{
		temp->front = buffer->next;
		temp->front->prev = NULL;
	}
	void *valueptr = buffer->valueptr;
	free(buffer);
	temp->count--;
	return valueptr;
}

void *PopRearDq(Deque **dq)
{
	Deque *temp = *dq;
	DLL *buffer = temp->rear;
	if (temp->count > 1)
	{
		temp->rear = buffer->prev;
		temp->rear->next = NULL;
	}
	void *valueptr = buffer->valueptr;
	free(buffer);
	temp->count--;
	return valueptr;
}

int IntPower(int base, int exp)
{
	int res = 1;
	for (int i = 0; i < exp; i++)
	{
		res = res * base;
	}
	return res;
}

int ExtractNumerics(char *string)
{
	int digits = 0;
	int j = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		char c = *(string + i);
		if (isdigit(c))
		{
			digits = digits * IntPower(10, j) + (c - '0');
			j++;
		}
	}
	return digits;
}

void TruncateString(char *string, signed int cut)
{
	if (cut > 0) string[cut] = '\0';
	else if (cut < 0) string[strlen(string) + cut] = '\0';
	else return;
}

uint2 ExtractAlpha(char *string)
{
	uint2 len = strlen(string);
	for (uint2 i = 0; i < len; i++)
	{
		if (isdigit(string[i])) return i + 1;
	}
	return 0;
}

Vector2 B2vecToRlvec(b2Vec2 v)
{
	return (Vector2){ v.x, v.y };
}

b2Vec2 RlvecToB2vec(Vector2 v)
{
	return (b2Vec2){ v.x, v.y };
}

Texture2D LoadPathTexture(char *path, char *filename)
{
	return LoadTexture(TextFormat(path, filename));
}

char *GetStringFromFile(const char *absPath)
{
	FILE *file = fopen(absPath, "rb");
	char *buffer;
	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		rewind(file);
		buffer = malloc(size + 1);

		// CAUTION: this malloc needs to be freed by receiver
		if (buffer != NULL)
		{
			fread(buffer, size, 1, file);
			buffer[size] = '\0';
		}
		else
		{
			fclose(file);
			return NULL;
		}
		fclose(file);
		return buffer;
	}
	else
	{
		return NULL;
	}
}
/* --- ------------ --- */
