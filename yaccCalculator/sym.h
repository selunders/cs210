// #ifndef SYMTBL_H
// #define SYMTBL_H

struct sym {
    char* name;
    double value;
    struct sym * next;
};

struct sym * sym_lookup(char *);
// void sym_Add(char *, double);
void printList();

// void swapNode

// #endif /* SYMTBL_H */
