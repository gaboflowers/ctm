#ifndef CTM_MACROS_H
#define CTM_MACROS_H

#ifndef CTM_INIT_POS
#define CTM_INIT_POS 0
#endif

#ifndef CTM_INIT_TAPE_SIZE
#define CTM_INIT_TAPE_SIZE 200
#endif

#ifndef CTM_MAX_TAPE_SIZE
#warning CTM_MAX_TAPE_SIZE is undefined. Will use default value 200
#define CTM_MAX_TAPE_SIZE 500
#endif

#ifndef CTM_NUMBER_OF_STATES
#warning CTM_NUMBER_OF_STATES is undefined. This binary will certainly fail (or at least, it is pretty likely).
#define CTM_NUMBER_OF_STATES 3
#endif

#ifndef CTM_NUMBER_OF_FINAL_STATES
#warning CTM_NUMBER_OF_FINAL_STATES is undefined. This binary will most likely fail.
#define CTM_NUMBER_OF_FINAL_STATES 3
#endif

#ifndef CTM_MAX_NUMBER_TRANSITIONS
#warning CTM_MAX_NUMBER_TRANSITIONS is undefined. Will use default value 500
#define CTM_MAX_NUMBER_TRANSITIONS 500
#endif

#ifndef CTM_ALPHABET_SIZE
#warning CTM_ALPHABET_SIZE is undefined. Using default: 2.
#define CTM_ALPHABET_SIZE 2
#endif

#ifndef CTM_ALPHABET
#warning CTM_ALPHABET is undefined. Will use default {0, 1}.
int ctm_alphabet[CTM_ALPHABET_SIZE] = {0, 1};
#endif

#ifndef CTM_BLANK_SYMBOL
#warning CTM_BLANK_SYMBOL is undefined. This binary will most likely fail.
#define CTM_BLANK_SYMBOL -1
#endif

#ifndef CTM_DEFAULT_CELL_TYPE
#warning CTM_DEFAULT_CELL_TYPE is undefined. Will use CELL_TYPE_CHAR
#define CTM_DEFAULT_CELL_TYPE CELL_TYPE_CHAR
#endif

#ifndef CTM_INIT_STATE
#warning CTM_INIT_STATE is undefined. Will use unreachable state. This Machine will reject everything.
#define CTM_INIT_STATE -1
#endif

#ifndef CTM_FINAL_STATES
#warning CTM_FINAL_STATES is undefined. Will use unreachable states. This Machine will reject everything.
int ctm_final_states[CTM_NUMBER_OF_FINAL_STATES] = {-5, -6};
#endif

#ifndef CTM_PRINT_STATUS
#define CTM_PRINT_STATUS 0
#endif

#ifndef CTM_ALLOW_PARTIAL_ACCEPT
#define CTM_ALLOW_PARTIAL_ACCEPT 0
#endif

#ifndef CTM_HALT_ON_UNHANDLED_BLANK
#define CTM_HALT_ON_UNHANDLED_BLANK 1
#endif

#ifndef CTM_HELP
// Do nothing.
#endif

#endif
