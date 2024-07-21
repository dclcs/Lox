//
// Created by cl d on 2024/7/11.
//

#ifndef CLOX_OBJECT_H
#define CLOX_OBJECT_H

#include "common.h"
#include "value.h"
#include "table.h"
#include "chunk.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

typedef enum {
    OBJ_FUNCTION,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_CLOSURE,
    OBJ_UPVALUE
} ObjType;

struct Obj {
    ObjType type;
    struct Obj* next;
    bool isMarked;
};

typedef struct {
    Obj obj;
    int arity;
    Chunk chunk;
    ObjString* name;
    int upvalueCount;
} ObjFunction;

typedef struct ObjUpvalue {
    Obj obj;
    Value* location;
    struct ObjUpvalue* next;
    Value closed;
} ObjUpvalue;

typedef Value (*NativeFn)(int argCount, Value* args);
typedef struct  {
    Obj obj;
    NativeFn function;
} ObjNative;

struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

typedef struct {
    Obj obj;
    ObjFunction* function;
    ObjUpvalue** upvalues;
    int upvalueCount;
} ObjClosure;

#define IS_STRING(value)       isObjType(value, OBJ_STRING)
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)
#define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
#define AS_FUNCTION(value)      ((ObjFunction*)AS_OBJ(value))
#define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
#define AS_NATIVE(value) \
    (((ObjNative*)AS_OBJ(value))->function)
#define IS_CLOSURE(value)       isObjType(value, OBJ_CLOSURE)
#define AS_CLOSURE(value)       ((ObjClosure*)AS_OBJ(value))

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

ObjString* copyString(const char* chars, int length);
#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

void printObject(Value value);
ObjString* takeString(char* chars, int length);
ObjString* tableFindString(Table* table, const char* chars,
                           int length, uint32_t hash);

ObjFunction* newFunction();
ObjNative* newNative(NativeFn function);
ObjClosure* newClosure(ObjFunction* function);
ObjUpvalue* newUpvalue(Value* slot);
#endif //CLOX_OBJECT_H
