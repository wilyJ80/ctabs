#ifndef GRAPH_H
#define GRAPH_H

#include "token_type.h"
#include "stack.h"
#include <stdio.h>
#include <stdbool.h>

struct GraphState {
	char currentChar;
	char* currentLexeme;
	int currentLexemeSize;
	struct Stack* stack;
	void (*consumeAndLexemeBuildingIs)(bool isLexeme, struct GraphState* self);
	FILE *filePointer;
	bool isDebugOn;
};

void _consumeAndLexemeBuildingIs(bool isLexeme, struct GraphState* self);

void* start(struct GraphState* graphState);

void* _collecting(struct GraphState* graphState);

void* _isField(struct GraphState* graphState);

void* _field(struct GraphState* graphState);

void* _endField(struct GraphState* graphState);

#endif
