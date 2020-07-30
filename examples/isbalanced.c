#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "ctm.h"

#define __TRANSPILED_MACROS

// <macros> (replace __TRANSPILED_MACROS)

#define CTM_ALPHABET_SIZE 6
#define CTM_ALPHABET
int ctm_alphabet[CTM_ALPHABET_SIZE] = {'(',')','+','$','s','n'};
#define CTM_BLANK_SYMBOL ' '
#define CTM_INIT_POS 1
#define CTM_INIT_TAPE_SIZE 100
#define CTM_MAX_TAPE_SIZE 150
#define CTM_MAX_NUMBER_TRANSITIONS 500
#define CTM_PRINT_STATUS 1
#define CTM_HALT_ON_UNHANDLED_BLANK 0
#define CTM_NUMBER_OF_STATES 12
#define CTM_NUMBER_OF_FINAL_STATES 1
#define CTM_FINAL_STATES
int ctm_final_states[CTM_NUMBER_OF_FINAL_STATES] = {11};
#define CTM_INIT_STATE 1
#define __CTM_TRANSPILED_MACROS

// </macros>

#ifndef __CTM_TRANSPILED_MACROS
#error "Transpiled macros were not inserted in the preamble."
#endif

#include "ctm_macros.h"

void show_info() {
    show_int_arr(ctm_alphabet, CTM_ALPHABET_SIZE);
    show_macro(CTM_INIT_TAPE_SIZE);
    show_macro(CTM_MAX_TAPE_SIZE);
    show_macro(CTM_MAX_NUMBER_TRANSITIONS);
    show_macro(CTM_NUMBER_OF_STATES);
    show_macro(CTM_NUMBER_OF_FINAL_STATES);
    show_macro(CTM_BLANK_SYMBOL);
    show_macro(CTM_PRINT_STATUS);
    show_macro(CTM_ALLOW_PARTIAL_ACCEPT);
    show_macro(CTM_HALT_ON_UNHANDLED_BLANK);
}

#if CTM_ALLOW_PARTIAL_ACCEPT
#define HANDLE_HEADER(tm, retval)    \
    if (retval < 0) { \
        return TM_state_is_accept(tm) | RUNTAPE_ERROR; \
    }
#else
#define HANDLE_HEADER(tm, retval)    \
    if (retval < 0) { \
        return REJECT | RUNTAPE_ERROR; \
    }
#endif // CTM_ALLOW_PARTIAL_ACCEPT


int TM_run(TM *tm) {
    int transitions_count = 0;
    while (transitions_count < CTM_MAX_NUMBER_TRANSITIONS) {
#if CTM_PRINT_STATUS
        TM_show_status(tm, transitions_count);
#endif // CTM_PRINT_STATUS
        switch(tm->current_state) {
            // <program>
            case 1:

                switch (TM_read_cell(tm)) {
                    case '(':
                        TM_write_cell(tm, '$');
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        tm->current_state = 3;
                        break;
                    case ')':
                        TM_write_cell(tm, '$');
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        tm->current_state = 5;
                        break;
                    case ' ':
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        tm->current_state = 2;
                        break;
                    default:
                        return TM_state_is_accept(tm);

                }
            break;
            case 3:

                switch (TM_read_cell(tm)) {
                    case ' ':
                        tm->current_state = 4;
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;
                    default:
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;


                }
            break;
            case 4:

                switch (TM_read_cell(tm)) {
                    case '+':
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;
                    case ' ':
                        TM_write_cell(tm, '+');
                        tm->current_state = 9;
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        break;
                    default:
                        return TM_state_is_accept(tm);

                }
            break;
            case 5:

                switch (TM_read_cell(tm)) {
                    case ' ':
                        tm->current_state = 6;
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;
                    default:
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;


                }
            break;
            case 6:

                switch (TM_read_cell(tm)) {
                    case '+':
                        tm->current_state = 7;
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;
                    case ' ':
                        tm->current_state = 12;
                        break;
                    default:
                        return TM_state_is_accept(tm);

                }
            break;
            case 7:

                switch (TM_read_cell(tm)) {
                    case ' ':
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        tm->current_state = 8;
                        break;
                    default:
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;


                }
            break;
            case 8:

                switch (TM_read_cell(tm)) {
                    case '+':
                        TM_write_cell(tm, ' ');
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        tm->current_state = 9;
                        break;
                    default:
                        return TM_state_is_accept(tm);
#if CTM_HALT_ON_UNHANDLED_BLANK
                    case CTM_BLANK_SYMBOL:
                        return TM_state_is_accept(tm);
#endif // CTM_HALT_ON_UNHANDLED_BLANK
                }
            break;
            case 9:

                switch (TM_read_cell(tm)) {
                    case '+':
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        break;
                    case ' ':
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        tm->current_state = 10;
                        break;
                    default:
                        return TM_state_is_accept(tm);

                }
            break;
            case 10:

                switch (TM_read_cell(tm)) {
                    case '$':
                        tm->current_state = 1;
                        HANDLE_HEADER(tm, TM_move_header_right(tm, 1));
                        break;
                    case '(':
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        break;
                    case ')':
                        HANDLE_HEADER(tm, TM_move_header_left(tm, 1));
                        break;
                    default:
                        return TM_state_is_accept(tm);
#if CTM_HALT_ON_UNHANDLED_BLANK
                    case CTM_BLANK_SYMBOL:
                        return TM_state_is_accept(tm);
#endif // CTM_HALT_ON_UNHANDLED_BLANK
                }
            break;
            case 2:

                switch (TM_read_cell(tm)) {
                    case ' ':
                        tm->current_state = 11;
                        break;
                    default:
                        TM_write_cell(tm, ' ');
                        tm->current_state = 12;
                        break;


                }
            break;
            case 11:

                switch (TM_read_cell(tm)) {
                    case ' ':
                        TM_write_cell(tm, 's');
                        break;
                    default:
                        return TM_state_is_accept(tm);

                }
            break;
            case 12:

                switch (TM_read_cell(tm)) {
                    case ' ':
                        TM_write_cell(tm, 'n');
                        break;
                    default:
                        return TM_state_is_accept(tm);

                }
            break;
            // </program>
            default:
                return TM_state_is_accept(tm);
        }
        transitions_count++;
    }
    return TM_state_is_accept(tm) | REACHED_MAX_TRANSITIONS;
}


int main(int argc, char *argv[]) {
    int read_from_args = 0;
    char *input_tape;
    int input_from_stdin = 0;
    int args_as_integers = 0;
    int show_tm_info = 0;
    int verbose = 0;

    int tape_input;
    while (1) {
        static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"info", no_argument, 0, 'i'},
            {"tape", required_argument, 0, 't'},
            {"asint", no_argument, 0, 'n'},
            {"stdin", no_argument, 0, '-'},
            {"verbose", no_argument, 0, 'v'},
            {0, 0, 0, 0}
        };

        switch (getopt_long(argc, argv, "hint:-v", long_options, NULL)) {
            case 'h':
                // https://stackoverflow.com/a/2199698
                fprintf(stdout, "%s is a C-based Turing Machine (or CTM)\n"
                       "As such, it is a binary program compiled from CTM language source code\n"
                       "transpiled to C, which simulates a particular Turing Machine.\n\n"
                       "Options:\n"
                       "\t-h\t\t"
                       "Display this help.\n"
                       "\t-t [tape]\t"
                       "Initialises the Machine's tape with the values specified\n"
                       "\t\t\tas second parameter. All characters will be cast to\n"
                       "\t\t\tintegers.\n"
                       "\t-n\t"
                       "All input characters will be substracted 48 ('0'), effectively\n"
                       "\t\t\tconverting chars to integers on the tape.\n"
                       "\t--stdin\n"
                       "\t--\t\t"
                       "Initialises the Machine's tape with the values read from\n"
                       "\t\t\tstdin.\n"
                       "\t-i\t\t"
                       "Show the Machine's configurations.\n\n"
#ifdef CTM_HELP
                       "Machine's help:\n"
                       CTM_HELP
#endif //CTM_HELP
                       , argv[0]);
                return 0;
            case 'i':
                show_info();
                return 0;
            case 'n':
                args_as_integers = 1;
                break;
            case 't':
                read_from_args = 1;
                input_tape = optarg;
                break;
            case '-':
                read_from_args = 1;
                input_from_stdin = 1;
                read_file(stdin, &input_tape);
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [ -h | -i | -n | -t [tape] | --[stdin] | -v ]\n", argv[0]);
                return -1;
            case -1:
                goto finish_options;
        }
    }
finish_options: ;

    TM *tm = TM_create(CTM_INIT_TAPE_SIZE,
                       CTM_MAX_TAPE_SIZE,
                       CTM_BLANK_SYMBOL,
                       CTM_DEFAULT_CELL_TYPE);

    tm->current_state = CTM_INIT_STATE;
    tm->current_pos = CTM_INIT_POS;
    tm->final_states = ctm_final_states;
    tm->number_of_states = CTM_NUMBER_OF_STATES;
    tm->number_of_final_states = CTM_NUMBER_OF_FINAL_STATES;

    if (read_from_args) {
        if(TM_initialise_tape_input(tm, input_tape, args_as_integers) < 0) {
            return -1;
        }
    }

    int retval = TM_run(tm);

    if (verbose) {
        if (read_from_args) {
            printf("Input tape: '%s'\n", input_tape);
        }

        if (retval & REACHED_MAX_TRANSITIONS) {
            printf("Reached maximum number of transitions (%d)\n", CTM_MAX_NUMBER_TRANSITIONS);
        }
        if (retval & ACCEPT) {
            printf("TM accepted!\n");
        } else {
            printf("TM rejected!\n");
        }
    }

    TM_print_output(tm);

    TM_free(tm);
    if (input_from_stdin) {
        free(input_tape);
    }

    return !(retval & ACCEPT);
}


