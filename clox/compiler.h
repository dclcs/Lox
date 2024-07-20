//
// Created by cl d on 2024/7/10.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H
#include "scanner.h"
#include "chunk.h"
#include "object.h"

typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

#define UINT8_COUNT (UINT8_MAX + 1)
ObjFunction* compile(const char* source);

#endif //CLOX_COMPILER_H
