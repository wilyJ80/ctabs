#ifndef STACK_H
#define STACK_H

#include "token_type.h"
#define MAX_SIZE 1000

struct Stack {
	enum TOKEN_TYPE tokens[MAX_SIZE];
	int index;
	int (*initStack)(struct Stack* self);
	int (*addItem)(struct Stack* self, enum TOKEN_TYPE tokenType);
};

int initStack(struct Stack* self);
int addItem(struct Stack* self, enum TOKEN_TYPE tokenType);

#endif
