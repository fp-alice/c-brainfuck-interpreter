#include "tape.h"

const char* FILE_PATH = "../helloworld.bf";

void run_program(tape_t* tape)
{
    while (tape->instructions_length>=tape->instruction_pointer) {
        switch (tape->instructions[tape->instruction_pointer]) {
        case '>':tape_right(tape);
            break;
        case '<':tape_left(tape);
            break;
        case '+':tape_increment(tape);
            break;
        case '-':tape_decrement(tape);
            break;
        case '.':tape_put_char(tape);
            break;
        case ',':tape_get_char(tape);
            break;
        case '[':tape_jump_forward(tape);
            break;
        case ']':tape_jump_back(tape);
            break;
        }
    }
}

int main()
{
    tape_t* tape = create_tape(FILE_PATH);
    run_program(tape);
    free_tape(tape);
    return 0;
}
