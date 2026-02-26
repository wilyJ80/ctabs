#include "stack.h"
#include "token_type.h"

int initStack(struct Stack* self) {
	self->index = 0;
	self->initStack = initStack;
	self->addItem = addItem;
	return 0;
}

int addItem(struct Stack* self, enum TOKEN_TYPE tokenType) {
	if (self->index == MAX_SIZE) {
		return 1;
	}
	self->tokens[self->index] = tokenType;
	(self->index)++;
	return 0;
}
