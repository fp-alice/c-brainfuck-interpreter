//
// Created by alice on 1/29/21.
//
#include "tape.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

char* read_file(const char* file_name)
{
    // Open file for reading
    FILE* file = fopen(file_name, "r");

    // Exit if file can't be opened
    if (file==NULL) {
        printf("Could not open file %s", file_name);
        exit(ENOENT);
    }

    // Get file size by seeking to end of file and telling position
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);

    // Reset position to beginning of file
    rewind(file);

    // Allocate string for contents + 1 for null byte
    char* contents = malloc(1+file_size*sizeof(char));

    // Read until EOF
    fread(contents, file_size+1, 1, file);

    // Close file
    fclose(file);

    return contents;
}

tape_t * create_tape(const char* file_path)
{
    tape_t * tape = malloc(sizeof(tape_t));
    tape->instructions = read_file(file_path);
    tape->current_instruction = tape->instructions[0];
    tape->instructions_length = strlen(tape->instructions);
    tape->instruction_pointer = 0;
    tape->data = malloc(30000);
    memset(tape->data, 0, 30000);
    tape->data_pointer = 0;
    return tape;
}

void free_tape(tape_t* tape)
{
    free(tape->instructions);
    free(tape->data);
    free(tape);
}

void advance_tape(tape_t* tape)
{
    tape->current_instruction = tape->instructions[++tape->instruction_pointer];
}

void rewind_tape(tape_t* tape)
{
    tape->current_instruction = tape->instructions[--tape->instruction_pointer];
}

void tape_right(tape_t* tape)
{
    ++tape->data_pointer;
    advance_tape(tape);
}

void tape_left(tape_t* tape)
{
    --tape->data_pointer;
    advance_tape(tape);
}

void tape_increment(tape_t* tape)
{
    ++tape->data[tape->data_pointer];
    advance_tape(tape);
}

void tape_decrement(tape_t* tape)
{
    --tape->data[tape->data_pointer];
    advance_tape(tape);
}

void tape_put_char(tape_t* tape)
{
    putchar(tape->data[tape->data_pointer]);
    fflush(stdout);
    advance_tape(tape);
}

void tape_get_char(tape_t* tape)
{
    tape->data[tape->data_pointer] = (char) getchar();
    advance_tape(tape);
}

void tape_jump_forward(tape_t* tape)
{
    if (tape->data[tape->data_pointer]==0) {
        int count = 1;
        while (count!=0) {
            advance_tape(tape);
            switch (tape->current_instruction) {
            case '[':++count;
                break;
            case ']':--count;
                break;
            }
        }
    }
    advance_tape(tape);
}

void tape_jump_back(tape_t* tape)
{
    if (tape->data[tape->data_pointer]!=0) {
        int count = 1;
        while (count!=0) {
            rewind_tape(tape);
            switch (tape->current_instruction) {
            case ']':++count;
                break;
            case '[':--count;
                break;
            }
        }
    }
    advance_tape(tape);
}