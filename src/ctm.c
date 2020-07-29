#include "ctm.h"

// Cell

void cell_init(Cell *pcell, cell_value_t blank_symbol, cell_type_t default_cell_type) {
   pcell->value = blank_symbol;
   pcell->type = default_cell_type;
}

// Tape

Tape *tape_create(int init_tape_size, int max_tape_size, cell_value_t blank_symbol, cell_type_t default_cell_type) {
    Tape *tape= malloc(sizeof(Tape));
    tape->cell_array = (Cell*)malloc(sizeof(Cell)*init_tape_size);
    tape->size = init_tape_size;
    tape->max_tape_size = max_tape_size;
    tape->blank_symbol = blank_symbol;
    tape->default_cell_type = default_cell_type;
    for (int i=0; i<init_tape_size; i++) {
        cell_init(&(tape->cell_array[i]), blank_symbol, default_cell_type);
    }
    return tape;
}

void tape_free(Tape *tape) {
    free(tape->cell_array);
    free(tape);
}

int tape_extend(Tape *tape) {
    int new_tape_size = min(tape->max_tape_size, 2*tape->size);
    if (new_tape_size == tape->size) {
        fprintf(stderr, "[tape_extend] Tape already reached CTM_MAX_TAPE_SIZE %d\n", tape->size);
        return -1;
    }
    if (new_tape_size > tape->max_tape_size) {
        fprintf(stderr, "[tape_extend] CTM_MAX_TAPE_SIZE exceeded. %d > %d\n", new_tape_size, tape->max_tape_size);
        return -1;
    }

    tape->cell_array = realloc(tape->cell_array, sizeof(Cell)*new_tape_size);
    if (!tape->cell_array) {
        fprintf(stderr, "[tape_extend] Couldn't realloc to size %d\n", new_tape_size);
        return -1;
    }

    int old_size = tape->size;
    tape->size = new_tape_size;
    for (int i=old_size; i<new_tape_size; i++) {
        cell_init(&(tape->cell_array[i]), tape->blank_symbol, tape->default_cell_type);
    }
    return 0;
}

// TM
TM *TM_create(int init_tape_size, int max_tape_size, cell_value_t blank_symbol, cell_type_t default_cell_type) {
    TM *tm = malloc(sizeof(TM));
    tm->tape = tape_create(init_tape_size, max_tape_size, blank_symbol, default_cell_type);
    tm->current_pos = 0;
    return tm;
}

void TM_free(TM *tm) {
    tape_free(tm->tape);
    free(tm);
}

int TM_initialise_tape_input(TM *tm, char *input, int args_as_integers) {
    int input_length = 0;
    while (*input) {
        if (input_length >= (tm->tape)->size) {
            fprintf(stderr, "[TM_initialise_tape_input] Tape input length is greater than the current tape size (%d).\n", (tm->tape)->size);
            return -1;
        }
        (tm->tape)->cell_array[input_length].value = *input - (args_as_integers ? '0' : 0);
        input++;
        input_length++;
    }
    return 0;
}

int TM_move_header_left(TM *tm, int step) {
    tm->current_pos -= step;
    if (tm->current_pos < 0) {
        fprintf(stderr, "[TM_move_header_left] Machine's header went too far left. The U.S. overthrew it.\n");
        return -1;
    }
    return 0;
}

int TM_move_header_right(TM *tm, int step) {
    tm->current_pos += step;
    if (tm->current_pos >= (tm->tape)->size) {
        fprintf(stderr, "[TM_move_header_right] Current position is %d greater or equal than tape size %d. Calling extend.\n", tm->current_pos, (tm->tape)->size);
        return tape_extend(tm->tape);
    }
    return 0;
}

cell_value_t TM_read_cell(TM *tm) {
    return (tm->tape)->cell_array[tm->current_pos].value;
}

void TM_write_cell(TM *tm, cell_value_t value) {
    (tm->tape)->cell_array[tm->current_pos].value = value;
}

int TM_state_is_accept(TM *tm) {
    for (int i=0; i<tm->number_of_final_states; i++) {
        if (tm->current_state == tm->final_states[i]) {
            return ACCEPT;
        }
    }
    return REJECT;
}

void TM_print(TM *tm, int n) {
    printf("#%d - state: %d, pos: %d, read: %d, tape size: %d\n", n, tm->current_state, tm->current_pos, TM_read_cell(tm)+'0', (tm->tape)->size);
}


#define BUF_INITSIZE 1024
#define READ_NBYTES 1024
void read_file(FILE *stream, char** buf) {
    *buf = malloc(BUF_INITSIZE);
    int current_size = BUF_INITSIZE;
    int already_read = 0;
    int rd;
    if (*buf) {
        while ((rd = fread(*(buf+already_read), 1, min(READ_NBYTES, current_size-already_read), stream))) {
            already_read += rd;
            if (current_size == already_read) {
                current_size <<= 1;
                *buf = realloc(*buf, (size_t)current_size);
            }
        }
        (*buf)[already_read] = '\0';
    } else {
        perror("malloc");
        exit(-1);
    }
}

