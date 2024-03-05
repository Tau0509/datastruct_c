//
// Created by 陶子昊 on 2024/3/5.
//
#define MAX 100
#define elemtype int

#include "basicdef_struct.h"

typedef struct {
    elemtype *elem;  //动态分配
    int length; //表长
} LinearList, *LL;

status initLinearList(LL L) {
    if (!L) return ERROR;
    L->elem = (elemtype *) malloc(MAX * sizeof(elemtype));
    if (!L->elem) return ERROR;
    L->length = MAX;
    return OK;
}

status destroyLinearList(LL L) {
    if (L == NULL) return ERROR;
    free(L->elem);
    free(L);
    return OK;
}

status
