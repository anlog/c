//
// Created by Knight on 2020/6/23.
//

#ifndef HELLO_CPP_LIST_STRUCTURE_H
#define HELLO_CPP_LIST_STRUCTURE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//
// Created by Knight on 2020/6/23.
//

// Singly linked list
typedef void *Data;

//typedef struct __ListNode * __ListNode;
//typedef __ListNode ListNode;

typedef struct __ListNode {
    Data data;
    struct __ListNode *next;
} *ListNode;

typedef enum {
    MATCH_OK,
    MATCH_FAIL,
} _BOOL;

typedef _BOOL BOOL;

typedef BOOL(*MatchFunc)(const Data d1, const Data d2);

typedef void(*DestroyFunc)(Data data);

typedef struct __LinkedList {
    unsigned long size;
    MatchFunc matchFunc;
    DestroyFunc destroyFunc;
    ListNode head;
    ListNode tail;
} *LinkedList;

// create
LinkedList List_Create(DestroyFunc);

LinkedList List_Create_WithMatch(MatchFunc, DestroyFunc);

LinkedList List_Init(Data[], DestroyFunc);

LinkedList List_Init_WithMatch(Data[], MatchFunc, DestroyFunc);

void List_Destroy(LinkedList);

ListNode newNode(Data d);

void freeNode(ListNode node);

// operations
void addToListHead(LinkedList, Data);

void addToListTail(LinkedList, Data);

Data deleteListHead(LinkedList);

Data deleteListTail(LinkedList);

Data deleteListNode(LinkedList, ListNode);

Data deleteListNodeWithFunc(LinkedList, ListNode, MatchFunc func);

Data deleteListData(LinkedList l, Data data);

Data deleteListDataWithFunc(LinkedList l, Data data, MatchFunc func);

LinkedList reverseList(LinkedList);

void dumpList(LinkedList);

void dumpNode(ListNode);

#ifdef __cplusplus
}
#endif

void xexit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void *xmalloc(int size) {
    void *p = malloc(size);
    if (p) {
        return p;
    }
    xexit("xmalloc");
    return NULL;
}

#include <stdarg.h>

void dump(const char *s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    va_end(args);
}


#ifndef DEBUG
#define DEBUG
#endif

//#undef DEBUG
void debug(const char *s, ...) {
#ifdef DEBUG
    va_list args;
    va_start(args, s);
    vprintf(s, args);
    va_end(args);
#endif
}

#endif //HELLO_CPP_LIST_STRUCTURE_H
