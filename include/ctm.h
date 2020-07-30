#ifndef CTM_H
#define CTM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ACCEPT 1
#define REJECT 0
#define REACHED_MAX_TRANSITIONS 2
#define RUNTAPE_ERROR 4 // Yes, it's a TM Runtime pun

#define show_macro(macro_name) printf(#macro_name ":  %d\n", macro_name);
#define show_int_arr(arr_name, n) {printf(#arr_name " (%d):  ", n);print_int_array(arr_name, n);}

//#define min(a, b) (a) < (b) ? a : b
#define min(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

// -------- Cells

// For the first 4 bits of the Cell type (defines data type)
// TODO: Implement mixed cell type rules.
#define CELL_TYPE_INT 2
#define CELL_TYPE_CHAR 1

typedef uint32_t cell_value_t; // ints are already 32 bits in my computer, but portability.
typedef uint32_t cell_type_t;  // 4 bytes for type might seem like a waste of memory,
                               // but anyway memory alignment is to the next power of 2,
                               // so might as well use all the space.

typedef struct cell {
    cell_value_t value;
    cell_type_t type; // 1st 4 bits: type
} Cell;

void cell_init(Cell *pcell, cell_value_t blank_symbol, cell_type_t default_cell_type);

// -------- Tape
typedef struct tape {
    Cell *cell_array;
    int size;
    int max_tape_size;
    int blank_symbol;
    int default_cell_type;
} Tape;

Tape *tape_create(int init_tape_size, int max_tape_size, cell_value_t blank_symbol, cell_type_t default_cell_type);
void tape_free(Tape *tape);
int tape_extend(Tape *tape);

// -------- TM
typedef struct turing_machine {
    Tape *tape;
    int current_pos;
    int current_state;
    int *final_states; // array of size CTM_NUMBER_OF_FINAL_STATES
    int number_of_states; // CTM_NUMBER_OF_STATES
    int number_of_final_states; // CTM_NUMBER_OF_FINAL_STATES
} TM;

TM *TM_create(int init_tape_size, int max_tape_size, cell_value_t blank_symbol, cell_type_t default_cell_type);
void TM_free(TM *tm);
int TM_initialise_tape_input(TM *tm, char *input, int args_as_integers);
int TM_move_header_left(TM *tm, int step);
int TM_move_header_right(TM *tm, int step);
cell_value_t TM_read_cell(TM *tm);
void TM_write_cell(TM *tm, cell_value_t value);
int TM_state_is_accept(TM *tm);
void TM_show_status(TM *tm, int n);
void TM_print_output(TM *tm);

// -------- Misc
void print_char_array(char *buf, int n);
void print_int_array(int *buf, int n);

#define BUF_INITSIZE 1024
#define READ_NBYTES 1024
void read_file(FILE *stream, char** buf);

#endif // CTM_H

