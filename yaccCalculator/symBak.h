#ifndef SYMTBL_H
#define SYMTBL_H

#define NSYMS   (4)

struct sym {
    char * name;
    double value;
} sym_tbl[NSYMS];

struct sym * sym_lookup(char *);

#endif /* SYMTBL_H */
