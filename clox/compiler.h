//
// Created by cl d on 2024/7/10.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H
#include "scanner.h"
#include "chunk.h"
typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;


bool compile(const char* source, Chunk* chunk);

#endif //CLOX_COMPILER_H
