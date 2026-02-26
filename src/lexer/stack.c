#include "stack.h"
#include "token_type.h"

int initStack(struct Stack* self) {
	struct Stack stack = {
		.index = 0
	};
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
