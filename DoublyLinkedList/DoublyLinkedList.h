#ifndef DOUBLY_LINKED_LISint_H
#define DOUBLY_LINKED_LISint_H value

class Node
{
public:
    Node(int d);

    int get_data();
    void set_data(int d);
    Node* get_next();
    void set_next(Node* n);
    Node* get_prev();
    void set_prev(Node* p);

private:
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;
};


class DoublyLinkedList
{
public:
    DoublyLinkedList() {};
    virtual ~DoublyLinkedList();

    bool add(Node* data, unsigned int pos);
    bool remove(unsigned int pos);
    bool replace(Node* old_node, Node* new_node);
    int search(Node* data);
    Node* node_at(unsigned int pos);
    Node* operator[](unsigned int pos) { return node_at(pos); }
    void display_forward();
    void display_backward();
    unsigned int size();

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    unsigned int m_size = 0;
};

#endif /* ifndef DOUBLY_LINKED_LISint_H */
