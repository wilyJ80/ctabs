#include "graph.h"
#include "token_type.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void _consumeAndLexemeBuildingIs(bool isLexeme, struct GraphState* self) {
	if (isLexeme) {
		// Collect characters to lexeme
		self->currentLexeme[self->currentLexemeSize] = self->currentChar;
		self->currentLexeme[++(self->currentLexemeSize)] = '\0';
		if (self->isDebugOn) {
			printf("[INFO] Updated lexeme: %s\n", self->currentLexeme);
		}
	}
	// Consume character
	int ch = fgetc(self->filePointer);
	// Update current character
	self->currentChar = (char)ch;
	if (self->isDebugOn) {
		printf("[INFO] Consumed char: %c\n", self->currentChar);
	}
}

void* start(struct GraphState* graphState) {
	// Quit if we find EOF
	if (graphState->currentChar == EOF) {
		return NULL;
	
	} else if (!isprint((char)graphState->currentChar)) {
		// Nonprinting character: consume, not collect
		graphState->consumeAndLexemeBuildingIs(false, graphState);
		return start;

	} else {
		// Printing character: consume and collect
		graphState->consumeAndLexemeBuildingIs(true, graphState);
		return _collecting;
	}
}

void* _collecting(struct GraphState* graphState) {
	if (isprint((char)graphState->currentChar)) {
		// Printing character: consume and collect
		graphState->consumeAndLexemeBuildingIs(true, graphState);
		return _collecting;

	} else if ((char)graphState->currentChar == (char)'\t') {
		// Tab: consume
		graphState->consumeAndLexemeBuildingIs(false, graphState);
		return _isField;
	
	} else if ((char)graphState->currentChar == (char)'\n' || graphState->currentChar == EOF) {
		// End of line: consume
		graphState->consumeAndLexemeBuildingIs(false, graphState);
		return _endField;
	}
	return NULL; // Just to suppress clangd errors
}

void* _isField(struct GraphState* graphState) {
	if ((char)graphState->currentChar == (char)'\n' || graphState->currentChar == EOF) {
		// End of line: consume
		graphState->consumeAndLexemeBuildingIs(false, graphState);
		return _endField;
	} else {
		return _field;
	}
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
