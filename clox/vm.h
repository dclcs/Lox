//
// Created by cl d on 2024/7/10.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "value.h"
#include "table.h"
#include "object.h"
#include "compiler.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;

typedef struct {
    Chunk* chunk;
    uint8_t* ip; //instruction pointer
    Value stack[STACK_MAX];
    Value* stackTop;
    Obj* objects;
    Table strings;
    Table globals;
    CallFrame frames[FRAMES_MAX];
    int frameCount;
    ObjUpvalue* openUpvalues;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;


void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif //CLOX_VM_H
