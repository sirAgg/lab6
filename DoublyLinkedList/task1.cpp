#include <stdio.h>

#include "DoublyLinkedList.h"

int main(int argc, char *argv[])
{
    DoublyLinkedList l;

    l.add(new Node(6), 0);
    l.add(new Node(5), 1);
    l.add(new Node(7), 1);

    l.display_forward();
    l.display_backward();

    //-----------------
    printf("----\n");

    printf("%d\n", l.search(l[3]));
    printf("%d\n", l.search(l[0]));
    printf("%d\n", l.search(l[2]));

    //-----------------
    printf("----\n");

    l.display_forward();

    printf("Replacing 7 with 8\n");
    l.replace( l[1], new Node(8));

    l.display_forward();

    //-----------------
    printf("----\n");

    if( l.remove(1)) printf("Removed element\n");
    else             printf("Failed to remove\n");
    if( l.remove(1)) printf("Removed element\n");
    else             printf("Failed to remove\n");
    if( l.remove(1)) printf("Removed element\n");
    else             printf("Failed to remove\n");

    printf("Size: %d\n", l.size());

    //-----------------
    printf("----\n");
    l.display_forward();

    return 0;
}
