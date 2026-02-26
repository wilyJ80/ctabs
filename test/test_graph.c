#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/lexer/graph.h"
#define MAX_LEXEME_SIZE 512

int main()
{
	const char* mockData = "something\tsomething\t\nyetanotherthing\tyetanotherthing\n";
	FILE *mockFile = fmemopen((void*)mockData, strlen(mockData), "r");
	if (mockFile == NULL) {
		fprintf(stderr, "[ERROR] Error opening source file.\n");
		exit(EXIT_FAILURE);
	}

	struct Stack stack;
	initStack(&stack);
	char lexemeBuffer[MAX_LEXEME_SIZE];
	struct GraphState graphState = {
		.currentLexeme = lexemeBuffer,
		.currentLexemeSize = 0,
		.stack = &stack,
		.filePointer = mockFile,
		.isDebugOn = true,
		.consumeAndLexemeBuildingIs = _consumeAndLexemeBuildingIs
	};

	// Necessary typedef to make sure the compiler
	// knows it's a function pointer
	typedef void* (*StateFunc)(struct GraphState*);
	StateFunc func = start;
	while (func != NULL) {
		func = func(&graphState);
	}

	assert(graphState.stack->tokens[0] == FIELD);
	assert(graphState.stack->tokens[1] == FIELD);
	assert(graphState.stack->tokens[2] == ENDFIELD);
	assert(graphState.stack->tokens[3] == FIELD);
	assert(graphState.stack->tokens[4] == ENDFIELD);

	return EXIT_SUCCESS;
}
