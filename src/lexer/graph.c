#include "graph.h"
#include "token_type.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void _consumeAndLexemeBuildingIs(bool isLexeme, struct GraphState* self) {
	if (isLexeme) {
		self->currentLexeme[self->currentLexemeSize] = self->currentChar;
		self->currentLexeme[++(self->currentLexemeSize)] = '\0';
		if (self->isDebugOn) {
			printf("[INFO] Updated lexeme: %s\n", self->currentLexeme);
		}
	}
	int ch = fgetc(self->filePointer);
	self->currentChar = (char)ch;
	if (self->isDebugOn) {
		printf("[INFO] Consumed char: %c\n", self->currentChar);
	}
}

void* start(struct GraphState* graphState) {
	if (graphState->currentChar == EOF) {
		return NULL;
	
	} else if (!isprint((char)graphState->currentChar)) {
		_consumeAndLexemeBuildingIs(false, graphState);
		return start;
	} else {
		_consumeAndLexemeBuildingIs(true, graphState);
		return _inField;
	}
}

void* _inField(struct GraphState* graphState) {
	if (isprint((char)graphState->currentChar)) {
		_consumeAndLexemeBuildingIs(true, graphState);
		return _inField;

	} else if ((char)graphState->currentChar == (char)'\t') {
		_consumeAndLexemeBuildingIs(false, graphState);
		return _field;
	
	} else if ((char)graphState->currentChar == (char)'\n' || graphState->currentChar == EOF) {
		_consumeAndLexemeBuildingIs(false, graphState);
		return _endField;
	}
	return NULL; // Just to satisfy clangd
}

void* _field(struct GraphState* graphState) {
	graphState->stack->addItem(graphState->stack, FIELD);
	graphState->currentLexeme[0] = '\0';
	graphState->currentLexemeSize = 0;
	return start;
}

void* _endField(struct GraphState* graphState) {
	graphState->stack->addItem(graphState->stack, ENDFIELD);
	graphState->currentLexeme[0] = '\0';
	graphState->currentLexemeSize = 0;
	return start;
}
