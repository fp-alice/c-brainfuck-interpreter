//
// Created by alice on 1/29/21.
//

#ifndef C_BF_TAPE_H
#define C_BF_TAPE_H

#include <stddef.h>

typedef struct {
  char* instructions;
  size_t instructions_length;
  size_t instruction_pointer;
  char current_instruction;
  char* data;
  size_t data_pointer;
} tape_t;

tape_t* create_tape(const char* file_path);
void free_tape(tape_t* tape);
void tape_right(tape_t* tape);
void tape_left(tape_t* tape);
void tape_increment(tape_t* tape);
void tape_decrement(tape_t* tape);
void tape_put_char(tape_t* tape);
void tape_get_char(tape_t* tape);
void tape_jump_forward(tape_t* tape);
void tape_jump_back(tape_t* tape);

#endif //C_BF_TAPE_H
