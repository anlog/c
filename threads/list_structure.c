//
// Created by Knight on 2020/6/23.
//

#include "list_structure.h"

LinkedList List_Create(DestroyFunc func) {
    debug("List_Create\n");
    LinkedList list = (LinkedList) xmalloc(sizeof(struct __LinkedList));
    list->matchFunc = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->destroyFunc = func;
    list->size = 0;
    return list;
}

LinkedList List_Create_WithMatch(MatchFunc mf, DestroyFunc df) {
    LinkedList l = List_Create(df);
    l->matchFunc = mf;
    return l;
}

LinkedList List_Init(Data *ds, DestroyFunc func) {
    debug("List_Init\n");
    LinkedList list = List_Create(func);

    Data d;
    ListNode current = list->head;
    while ((d = *ds)) {
        debug("while list size: %d\n", list->size);
        ListNode node = newNode(d);
        if (!current) {
            list->head = node;
            current = node;
        } else {
            current->next = node;
            current = node;
        }
        ds++;
        list->size++;
    }
    list->tail = current;
    return list;
}

LinkedList List_Init_WithMatch(Data *ds, MatchFunc mf, DestroyFunc df) {
    LinkedList l = List_Init(ds, df);
    l->matchFunc = mf;
    return l;
}

void List_Destroy(LinkedList l) {
    debug("List_Destroy");
    while (l->size > 0) {
        if (l->destroyFunc) {
            l->destroyFunc(l->head->data);
        }
        deleteListHead(l);
    }
    free(l);
}

ListNode newNode(Data d) {
    ListNode node = (ListNode) xmalloc(sizeof(struct __ListNode));
    node->data = d;
    node->next = NULL;
    return node;
}

void freeNode(ListNode node) {
    free(node);
}

// operations
void addToListHead(LinkedList l, Data data) {
    if (!l) {
        xexit("list is not init");
    }
    ListNode node = newNode(data);
    node->next = l->head;
    l->head = node;
    if (!l->tail) {
        l->tail = node;
    }
    l->size++;
}

void addToListTail(LinkedList l, Data data) {
    debug("addToTail\n");
    if (!l) {
        xexit("list is not init");
    }
    ListNode node = newNode(data);
    if (l->tail) {
        l->tail->next = node;
        l->tail = node;
    } else {
        l->tail = l->head = node;
    }

    l->size++;
}

Data deleteListHead(LinkedList l) {
    debug("deleteHead\n");
    if (!l) {
        xexit("list is not init");
    }
    if (l->size > 0) {
        ListNode oldHead = l->head;
        Data data = oldHead->data;
        l->head = oldHead->next;
        freeNode(oldHead);
        l->size--;
        return data;
    }
    return NULL;
}

Data deleteListTail(LinkedList l) {
    debug("deleteTail\n");
    if (!l) {
        xexit("list is not init");
    }
    if (l->size > 0) {
        unsigned long size = l->size;
        ListNode current = l->head;
        ListNode prev = current;
        while (--size > 0) {
            prev = current;
            current = current->next;
        }
        debug("deleteTail: current: %p - prev: %p\n", current, prev);
        prev->next = NULL;
        l->tail = prev;
        l->size--;
        Data data = current->data;
        freeNode(current);
        return data;
    }
    return NULL;
}

Data deleteListData(LinkedList l, Data data) {
    return deleteListDataWithFunc(l, data, l->matchFunc);
}

Data deleteListDataWithFunc(LinkedList l, Data data, MatchFunc func) {
    debug("deleteTail\n");
    if (!l) {
        xexit("list is not init");
    }
    if (l->size > 0) {
        ListNode current = l->head;
        ListNode prev = current;
        while ((current)) {
            Data currentData = current->data;

            if (func == NULL ? data == currentData :
                (func(data, currentData) == MATCH_OK)) {
                if (current == prev) {
                    return deleteListHead(l);
                } else {
                    prev->next = current->next;
                    l->size--;
                    freeNode(current);
                    return currentData;
                }
            }
            prev = current;
            current = current->next;
        }
    }
    return NULL;
}

Data deleteListNode(LinkedList l, ListNode node) {
    return deleteListNodeWithFunc(l, node->data, l->matchFunc);
}

Data deleteListNodeWithFunc(LinkedList l, ListNode node, MatchFunc func) {
    return deleteListDataWithFunc(l, node->data, func);
}

LinkedList reverseList(LinkedList l) {
    debug("reverseList\n");
    if (!l) {
        xexit("list is not init");
    }

    if (l->size > 0) {
        LinkedList newList = List_Create(l->destroyFunc);
        ListNode current = l->head;
        while ((current)) {
            addToListHead(newList, current->data);
            current = current->next;
        }
        List_Destroy(l);
        return newList;
    }
    return l;
}

void dumpList(LinkedList l) {
    debug("dumpList\n");
    if (!l) {
        xexit("list is not init");
    }
    dump("list(head:[%p], tail:[%p], size: %d) destroyFunc[%p] - matchFunc[%p]\n",
         l->head, l->tail, l->size, l->matchFunc, l->matchFunc);
    if (l->size > 0) {
        ListNode current = l->head;
        while ((current)) {
            dumpNode(current);
            current = current->next;
        }
        dump("Node[%p->%p](%s)", NULL, NULL, NULL);

    }
}

void dumpNode(ListNode node) {
    dump("Node[%p->%p](%s) -> ", node, node->next, node->data);
}



