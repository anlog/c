//
// Created by Knight on 2020/6/23.
//
#include "list_structure.h"

BOOL match(Data s, Data t) {
    debug("match in\n");
    if (s == t) {
        debug("match ==\n");
        return MATCH_OK;
    }
    debug("match: %p(%ld) - %p(%ld) \n", s, (*(long long *) s, t, *(long long *) t));
    return (s && t && (*(long long *) s - *(long long *) t) == 0)
           ? MATCH_OK : MATCH_FAIL;
}

void destroy(Data d) {
    dump("the node has [%s] being destroyed\n", d);
}

int main() {
    debug("main\n");
    LinkedList list = List_Create_WithMatch(match, destroy);
    dumpList(list);
    addToListTail(list, (Data) "abc");
    int a = 123;
    addToListTail(list, (Data) &a);
    dumpList(list);

    addToListHead(list, (Data) "sdfgdfhfgju");
    deleteListTail(list);

    addToListTail(list, (Data) &a);
    addToListTail(list, (Data) &a);
    deleteListData(list, (Data) &a);
//    deleteListData(list, (Data) &a);
//    addToListHead(list, (Data)&a);
    addToListHead(list, (Data) "sdifhsjgjeoyjdfkhjfjklfkjlh");
    deleteListHead(list);
    deleteListDataWithFunc(list, (Data) "abc", NULL);
    dumpList(list);

    List_Destroy(list);

    const char *arr[] = {"avc", "sdf", "sdgf", "sdgf", "weqr", "455415", "5454", NULL};

    LinkedList pList = List_Init_WithMatch((Data *) arr, match, destroy);
    deleteListHead(pList);
    deleteListTail(pList);
    deleteListData(pList, (Data)"sdgf");
    dumpList(pList);
    List_Destroy(pList);

}