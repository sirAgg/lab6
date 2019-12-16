#include "DoublyLinkedList.h"

#include <stdio.h>

Node::Node(int d): data(d) {}

int Node::get_data() { return data; }
void Node::set_data(int d) { data = d; }

Node* Node::get_next() { return next; }
void Node::set_next(Node* n) { next = n; }

Node* Node::get_prev() { return prev; }
void Node::set_prev(Node* p) { prev = p; }


DoublyLinkedList::~DoublyLinkedList()
{
    Node* current = head;
    while(current)
    {
        Node* next = current->get_next(); 
        delete current;
        current = next;
    }
}

bool DoublyLinkedList::add(Node* data, unsigned int pos)
{
    if( pos > m_size )
        return false;

    // list is empty
    if( m_size == 0 )
    {
        head = data;    
        tail = data;
        m_size++;
        return true;
    }

    // insert at begining of list
    if( pos == 0 )
    {
        head->set_prev(data);
        data->set_next(head);
        data->set_prev(nullptr);
        head = data;
        m_size++;
        return true;
    }
    
    // insert at end of list
    if( pos == m_size )
    {
        tail->set_next(data);
        data->set_prev(tail);
        data->set_next(nullptr);
        tail = data;
        m_size++;
        return true;
    }

    Node* current = head;
    int curr_pos = 1;   // case for 0 is already handled
    while(current)
    {
        if(curr_pos == pos)
        {
            current->get_next()->set_prev(data);
            data->set_next(current->get_next());
            data->set_prev(current);
            current->set_next(data);
            m_size++;
            return true;     
        }

        current = current->get_next();
        curr_pos++;
    }

    return false;
}

bool DoublyLinkedList::remove(unsigned int pos)
{
    Node* n = node_at(pos);

    if(!n)
        return false;

    Node* prev_n = n->get_prev();
    Node* next_n = n->get_next();

    if(prev_n)
        prev_n->set_next( next_n );
    else
        head = next_n;

    if(next_n)
        next_n->set_prev( prev_n );
    else
        tail = prev_n;

    delete n;
    m_size--;
        
    return true;
}

bool DoublyLinkedList::replace(Node* old_node, Node* new_node)
{
    if(!search(old_node) || !new_node)
        return false;


    if (old_node == head) {
        head = new_node;
    }
    else {
        old_node->get_prev()->set_next(new_node);
        new_node->set_prev(old_node->get_prev());
    }

    if (old_node == tail) {
        tail = new_node;
    }
    else {
        old_node->get_next()->set_prev(new_node);
        new_node->set_next(old_node->get_next());
    }

    delete old_node;
    return true;
}

int DoublyLinkedList::search( Node* data )
{
    Node* current = head;
    int index = 0;
    while (current)
    {
        if( current == data )
          return index; 

        current = current->get_next();
        index++;
    }
    return -1;
}

unsigned int DoublyLinkedList::size()
{
    return m_size;
}

Node* DoublyLinkedList::node_at(unsigned int pos)
{
    if(pos > m_size)
        return NULL;

    // start looking from head
    if( pos < m_size/2 )
    {
        Node* current = head;
        unsigned int curr_idx = 0;
        while(current)
        {
            if(pos == curr_idx)
                return current;

            current = current->get_next();
            curr_idx++;
        }
    }

    // start looking from tail
    else
    {
        Node* current = tail;
        unsigned int curr_idx = m_size-1;
        while(current)
        {
            if(pos == curr_idx)
                return current;

            current = current->get_prev();
            curr_idx--;
        }
    }

    return NULL;
}

void DoublyLinkedList::display_forward()
{
    Node* current = head;
    while(current)
    {
        printf("%d\n",current->get_data());
        current = current->get_next();
    }
}

void DoublyLinkedList::display_backward()
{
    Node* current = tail;
    while(current)
    {
        printf("%d\n",current->get_data());
        current = current->get_prev();
    }
}
