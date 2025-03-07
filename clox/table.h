//
// Created by cl d on 2024/7/13.
//

#ifndef CLOX_TABLE_H
#define CLOX_TABLE_H

#include "common.h"
#include "value.h"

typedef struct {
    ObjString* key;
    Value value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableSet(Table* table, ObjString* key, Value value);
void tableAddAll(Table* from, Table* to);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableDelete(Table* table, ObjString* key);
void markTable(Table* table);
void tableRemoveWhite(Table* table);

#endif //CLOX_TABLE_H
