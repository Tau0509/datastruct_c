//
// Created by 陶子昊 on 2024/3/5.
//
#define MAX 10
#define elemtype int

#include "basicdef_struct.h"

typedef struct {
    elemtype *elem;  //动态分配
    int length; //表长
    int size; //内存长度
} LinearList, *LL;

status initLinearList(LL L) {
    if (!L) return ERROR;
    L->elem = (elemtype *) malloc(MAX * sizeof(elemtype));
    if (!L->elem) return ERROR;
    L->size = MAX;
    L->length = 0;
    return OK;
}

status destroyLinearList(LL L) {
    if (L == NULL) return ERROR;
    free(L->elem);
    free(L);
    return OK;
}

status clearLinearList(LL L) {
    if (L == NULL || L->elem == NULL) return ERROR;
    free(L->elem);
    L->elem = (elemtype *) malloc(MAX * sizeof(elemtype));
    L->size = MAX;
    L->length = 0;
    return OK;
}

status emptyLinearList(LL L) {
    if (L == NULL) return ERROR;
    if (L->elem == NULL) return OK;
    return NO;
}

status getElem(LinearList l, int n, elemtype *t) {
    if (&l == NULL || l.elem == NULL || n < 0 || n >= l.length) return ERROR;
    *t = l.elem[n];
    return OK;
}

status locateElem(LinearList l, int *n, elemtype t) {     //找到线性表中与t相同的元素，找到则返回OK找不到返回NO
    if (&l == NULL || l.elem == NULL) return ERROR;
    for (int i = 0; i < l.length; i++) {
        if (l.elem[i] == t) {                    //返回索引
            *n = i;
            return OK;
        }
    }
    return NO;
}

status insertLinearList(LL l, int n, elemtype t) {
    if (l == NULL || (l->length + 1) <= l->size) return ERROR;   //n为索引
    for (int i = l->length; i >= n; i--)
        l->elem[i + 1] = l->elem[i];
    l->elem[n] = t;
    l->length++;
    return OK;
}

status deleteElem(LL l, int n, elemtype *e) {
    if (l == NULL || l->elem == NULL || n <= l->length || n >= 0) return ERROR;
    *e = l->elem[n];
    for (int i = n + 1; i < l->length; i++) {
        l->elem[i - 1] = l->elem[i];
    }
    return OK;
}

status sortLinearList(LL l, status order) { //order=1为正序，order=0为倒序   冒泡排序
    if (l == NULL || l->elem == NULL) return ERROR;
    int tem;
    if (order) {
        for (int i = 0; i < l->length - 1; i++) {
            for (int j = 0; j < l->length - 1; j++) {
                if (l->elem[j + 1] < l->elem[j]) {
                    tem = l->elem[j + 1];
                    l->elem[j + 1] = l->elem[j];
                    l->elem[j] = tem;
                }
            }
        }
        return OK;
    } else {
        for (int i = 0; i < l->length - 1; i++) {
            for (int j = 0; j < l->length - 1; j++) {
                if (l->elem[j+ 1] > l->elem[j]) {
                    tem = l->elem[j + 1];
                    l->elem[j + 1] = l->elem[j];
                    l->elem[j] = tem;
                }
            }
        }
        return OK;
    }
}

void putoutLinearList(LinearList l) {
    if (l.elem == NULL) {
        printf("ERROR:l.elem未定义");
        return;
    }
    for (int i = 0; i < l.length; i++) {
        printf("%d\t", l.elem[i]);
    }
}

status putinLinearList(LL l,elemtype a){
    l->elem[l->length]=a;
    l->length++;
}

int main(){
    LL test= (LL)malloc(sizeof (LinearList));
    printf("%d",initLinearList(test));
    int c;
    for(int i=0;i<=10;i++){
        scanf("%d",&c);
        putinLinearList(test,c);
    }
    putoutLinearList(*test);
    sortLinearList(test,1);
    putoutLinearList(*test);
    return 0;
}