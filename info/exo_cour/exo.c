#include <stdio.h>

typedef float ELEMENT;
typedef struct s_cell {
    ELEMENT data;
    struct s_cellule *next;
} Cell;

typedef *Cell List;

Cell* find (List l, ELEMENT e)
{
    while (l != NULL) {
        if (l->data == e) {
            return l;
        }
        l = l->next;
    }
    return NULL;
}



int main ()
{

    return 0;
}
