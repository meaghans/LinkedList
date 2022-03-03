#pragma once
#include <iostream>
#include <vector>
//#include "leaker.h"
using namespace std;
// Implementing a Linked List instead of an Array
template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
    };

    // Part 1 of Project
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);

    unsigned int NodeCount() const;
    void PrintForward() const;
    void PrintReverse() const;

    LinkedList();
    ~LinkedList();
    // End Part 1 of Project

    // Part 2 of Project
    Node* Head();
    Node* Tail();

    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);

    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);

    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    void FindAll(vector<Node*>& outData, const T& value) const;

    LinkedList(const LinkedList<T>& list);
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    // End Part 2 of Project 

    // Part 3 of Project
    void InsertBefore(Node* node, const T& data);
    void InsertAfter(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    bool operator==(const LinkedList<T>& rhs) const;
    // End Part 3 of Project

    // Part 4 of Project
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
    // End Part 4 of Project
private:
    Node* head;
    Node* tail;
    unsigned int nodeCount;
};
// Create a new Node at the front of the list to store the passed in parameter
// translation: need to store "data" in a new node added to the front of the list
template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
    Node* newNode = new Node; // create that new node for storage
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if (head == nullptr) // if there is nothing @ the front of the list, set head and tail to the new node
    {
        head = newNode;
        tail = newNode;
    }
    else // what if the front of the list isn't nullptr? what if there's something at the front of the list?
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    // add one to the amount of nodes in the list since you've added 1 node to the front of the list
    nodeCount++;
}
// Create a new Node at the end of the list to store the passed in parameter
// translation: store "data" at the end of the list as a new node
// similar to prior function definition (adding to front of the list, but this time it's the back)
template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    // what if there's nothing at the end of the list? go ahead and add the new node
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    }
    // what if there's something at the end of the list? get the other elements (surrounding) 
    // to interact, only those will be aware of the passed in parameter or new node being added to the tail of the list
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    // add 1 to the amount of nodes after adding 1 node to the end of the list
    nodeCount++;
}
// Given an array of values, insert a node for each of those @ the beginning of the list, maintaining the original order
template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    int start = count - 1;
    // keep decrementing by 1 until i is NOT greater than/equal to 0 (goes negative)
    for (int i = start; i >= 0; i--) {
        // Add data[i] to the front of the list
        AddHead(data[i]);
    }
}
// Same as before, but for the Tail implementation (back/tail of the list)
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    // begin at ZERO
    for (unsigned int i = 0; i < count; i++) {
        AddTail(data[i]);
    }
}
// How many things are stored in this list?
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}
// Iterator through all the nodes and print our their values one at a time
// Use LinkedList operations (Supplemental Video)
template <typename T>
void LinkedList<T>::PrintForward() const {

    Node* newNode = head;
    // while newNode is NOT nullptr, print it out. if it IS nullptr, while loop will END
    while (newNode != nullptr) {
        cout << newNode->data << endl;
        newNode = newNode->next;
    }
}
// Exactly the same as PrintFoward, except completely the opposite 
template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* newNode = tail; // instead of head, it is TAIL
    while (newNode != nullptr) { // same while loop as before
        cout << newNode->data << endl; // printing out the data..
        newNode = newNode->prev; // keep going back (reverse, NOT next)
    }
}
// Default constructor, How many nodes in an empty list? ZERO
// What is head pointing to? NOTHING
// What is tail pointing to? NOTHING
// Simply initializing my variables
template <typename T>
LinkedList<T>::LinkedList()
{
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
}
// The usual. Clean up your mess (Delete all the nodes created by the list)
// DEALLOCATE DYNAMICALY ALLOCATED MEMORY!!
template <typename T>
LinkedList<T>::~LinkedList()
{
    // here is the new pointer
    Node* newNode = head;

    // if the new pointer isn't NULL (if it IS pointing to something)
    while (newNode != nullptr) {
        // go to the next node
        newNode = newNode->next;
        // delete the top (head) node, not [] since not an array
        delete head;
        // set the head to the newNode
        head = newNode;
    }
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}
// returns the head pointer - const and non-const versions
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}
// returns the tail pointer - const and non-const versions
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}
/* == CONST AND NON-CONST VERSIONS */
// Given an index, return a pointer to the node at that index 
// Throw an exception of type out_of_range if the index is out_of_range
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    unsigned int i = 0;
    Node* newNode = head;
    // set newNode to first node (head)

    // if the given index is greater than or equal to the amount of nodes in the Linked List
    if (index >= nodeCount) {
        // throw an out of range error
        throw out_of_range("Index is Out of Range!");
    }
    // if the given index is NOT EQUAL to the indice (starting at 0, 1, 2, 3...), 
    // keep iterating to the next node and increasing the indice until the indice
    // is equal to the passed in INDEX parameter
    else {
        while (i != index) {
            newNode = newNode->next;
            // iterator, i
            i++;
        }
        return newNode;
    }
}
/* NON-CONST VERSION OF PERVIOUS GetNode() FOLLOWING SAME INSTRUCTIONS  */
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    unsigned int i = 0;
    Node* newNode = head;
    // IF PASSED IN PARAMETER INDEX IS GREATER THAN AMOUNT OF NODES IN LIST
    // THROW INDEX IS OUT OF RANGE ERROR
    if (index >= nodeCount) {
        throw out_of_range("Index is Out of Range!");
    }
    else {
        // if the given index is NOT EQUAL to the indice (starting at 0, 1, 2, 3,...),
        // keep iterating to the next node and increasing the indice until the indice
        // is equal to the passed in INDEX parameter
        while (i != index) {
            newNode = newNode->next;
            // iterator, i
            i++;
        }
        // return newNode of given index until index is equal to the indice iterating through the Linked List
        return newNode;
    }

}
/****** operator[] -- CONST AND NON-CONST VERSIONS ******/
// Overloaded subscript [] operator. 
// Takes an index, and returns data from the index-th node
// Throws an out of range exception for an invalid index 

// Given a passed-in INDEX, return the data from that index (node @ index)
// Throw OUT OF RANGE EXCEPTION for an INVALID INDEX
template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    unsigned int i = 0; // this will be our iterator
    Node* newNode = head; // set newNode to the head (top/beginning) of the linked list
    if (index > nodeCount) { // is the index greater than the amount of nodes in the list?
        throw out_of_range("Index is Out of Range!"); // if YES, throw OUT OF RANGE
    }
    // while the indice is NOT equal to the passed in INDEX
    while (i != index) {
        // go to the next node
        newNode = newNode->next;
        // iterator, i 
        i++;
    }
    // once the indice IS EQUAL to the passed in INDEX, return the data at that index
    return newNode->data;
}
/* SAME AS BEFORE, NON - CONST VERSION */
// Overloaded subscript [] operator
template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    unsigned int i = 0; // iterator, i -> needs to be unsigned (received error for unsigned int and unsigned int index, etc.)
    Node* newNode = head; // newNode is at the top of the list (beginning, head)
    if (index > nodeCount) { // if the index is greater than the NODE count (as before), out of range
        throw out_of_range("Index is Out of Range!");
    }
    while (i != index) { // while the indice i is NOT EQUAL to the passed in index 
        newNode = newNode->next; // go to the next node
        i++; // iterator i going through the linkedlist 
    }
    // once the indice IS EQUAL to the passed in INDEX, return the data at that index
    return newNode->data;
}

/** Finding the first node based on a value **/

// Find the first node with a data value matching the passed in parameter, 
// returning a pointer to that node
// Returns nullptr if no matching node found
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
    Node* newNode = head; // start at the head
    // while the created node is pointing to data and isn't null
    while (newNode != nullptr) { // if the created node is valid
        if (newNode->data == data) {
            // if pointing to data passed in (value passed in), matches
            return newNode; // return the node
        }
        newNode = newNode->next; // continue
    }
    return nullptr;
}
// FIND, NON-CONST VERSION, same as before
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* newNode = head;
    while (newNode != nullptr) {
        if (newNode->data == data) {
            return newNode;
        }
        newNode = newNode->next;
    }
    return nullptr;
}
// Find all nodes which match the passed in parameter value
// Store a pointer to that node in the passed in vector
// Use of a parameter like this (passing something in by reference, and storing data for later use) -- output parameter
template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* newNode = head; // set newNode to the head or top/beginning of the list 
    // this is where we'll start 
    // iterator i starts at 0 and iterates until it is NO LONGER LESS THAN the nodeCount (amt of nodes in the linked list)
    for (unsigned int i = 0; i < nodeCount; i++) {
        // while iterating ) for each iteration, if the newNode's data is equal to the passed in value
        if (newNode->data == value) {
            // store that data (as the pointer before) to the passed in VECTOR outData
            outData.push_back(newNode);
        }
        // move to the next node to get the next Data at the next Node and see if it matches the value
        newNode = newNode->next;
    }
    // Once you're done, set the newNode to NULLPTR
    newNode = nullptr;
}

// Copy constructor (remember: same parameter as copy assignment operator)
template<typename T>
// Sets "this" to a copy of the passed in LinkedList 
// Ex: if the other list has TEN NODES, (1-10 VALUES, 1 being [0] and 10 being [9]), "this" would have a copy of that same data

// basically just make a copy of the passed in list
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    head = nullptr;
    tail = nullptr;
    nodeCount = 0; // nodeCount needs to be ZERO for the amount of nodes thus far

    Node* newNode = list.head;
    // while the newNode IS NOT nullptr (if the newNode is pointing to something)
    while (newNode != nullptr) {
        // add the newNode's data to the tail
        AddTail(newNode->data);
        newNode = newNode->next; // go to the next node
    }
}

// if you define one of the big three you must define the others
// defined copy constructor, need to define copy assignment operator (next) and destructor (done)

// After listA = listB, then listA = listB is TRUE
// Can you use any functions to make write this one?

// ?? go to OH for help - getting errors w copy assignment operator
// got help from daniel (TA) -- needed to copy/paste destructor code over 
template <typename T>
LinkedList<T>& LinkedList<T>:: operator=(const LinkedList<T>& rhs) {
    // rhs needs to be copied as a LinkedList
    // similar to before

    // same as copy constructor but returns *this
    // here is the new pointer
    Node* newNode = head;

    // if the new pointer isn't NULL (if it IS pointing to something)
    while (newNode != nullptr) {
        // go to the next node
        newNode = newNode->next;
        // delete the top (head) node, not [] since not an array
        delete head;
        // set the head to the newNode
        head = newNode;
    }

    head = nullptr;
    tail = nullptr;
    nodeCount = 0;

    // copy assignment operator
    newNode = rhs.head;

    while (newNode != nullptr) {
        AddTail(newNode->data);
        newNode = newNode->next; // go to the next node

    }

    return *this;

}
// End of Part 2 of Project 1

// Part 3 of Project 1

// Given a pointer to a node, create a new node to store the passed in value
// after the indicated node
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    // create a new node
    Node* newNode = new Node;
    // if the passed in node is empty
    if (node == nullptr) {
        cout << "Passed in Node is empty" << endl;
    }
    // set the new node's data to the passed in data, previous to the node, and next to the next node's node
    newNode->data = data; // newNode points to passed in data value
    newNode->prev = node;
    newNode->next = node->next;
    // change previous pointer

    node->next->prev = newNode;
    node->next = newNode;
    nodeCount = nodeCount + 1;
}
// Ditto as before, except insert the new node before the indicated node
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    Node* newNode = new Node;

    if (node == nullptr) {
        cout << "Passed in Node is empty" << endl;
    }
    // go to OH
    newNode->data = data; // newNode points to passed in data value
    newNode->next = node;
    newNode->prev = node->prev;

    node->prev->next = newNode;
    node->prev = newNode;
    nodeCount = nodeCount + 1;
}
// Inserts a new Node to store the first parameter, at the index-th location
// If you specified 3 as the index, the new Node should have 3 nodes before it
// THROW OUT_OF_RANGE EXCEPTION IF GIVEN AN INVALID INDEX
template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    if (index > nodeCount) { // if index passed in is greater than amount of nodes
        throw out_of_range("Index is Out of Range!");
    }
    // what if the index is equal to the node count?, store data at LinkedList[index]
    else if (index == nodeCount) { // put in at the last index 
        Node* newNode = new Node;
        newNode->data = data;

        //Node* store = newNode;

        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = nullptr;
        tail = newNode;

        nodeCount++;
    }
    else { // NOT equal to the node count (last index) or greater than the NODE count
        Node* newNode = new Node;
        unsigned int i = 0;
        newNode->data = data;

        Node* newNode2 = head;
        while (i != index) {
            newNode2 = newNode2->next;
            i++; // iterator
        }
        newNode->prev = newNode2->prev;
        newNode->next = newNode2;

        if (newNode2->prev != nullptr) {
            newNode2->prev->next = newNode;
        }
        else {
            head = newNode;
        }

        newNode2->prev = newNode;
        nodeCount++;

    }
}
// Overloaded equality operator. Given listA and listB is listA equal to listB
// What would make one LinkedList equal to another?
// If each of its nodes were equal to the corresponding node of the other

// Similar to comparing 2 arrays, just with non-contiguous data (linked lists)
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    Node* newNode = rhs.head;
    bool torf = true;
    Node* newNode2 = head;

    if (nodeCount != rhs.nodeCount) {
        torf = false;
    }

    for (unsigned int i = 0; i < nodeCount; i++) {
        if (newNode->data != newNode2->data) {// index comparison
            torf = false;
            newNode = newNode->next;
            newNode2 = newNode2->next;
        }
    }
    return torf;
}

// End of Part 3 of Project 1

// Part 4 of Project 1

// Deletes the first Node in the list. 
// Returns whether or not the Node was removed
template <typename T>
bool LinkedList<T>::RemoveHead() {
    bool torf = false;
    if (nodeCount == 0) { // nothing here, no nodes
        torf = false;
    }
    // only one node in linked list
    else if (nodeCount == 1) {
        Node* newNode = head; // create a pointer to the node at the head
        delete newNode; // delete head
        head = nullptr; // set head to null
        tail = nullptr; // set tail to null
        nodeCount--; // decrease node element count by 1 after removing head
        torf = true; // YES we removed the head
    }
    else { // more than one head?
        Node* newNode = head->next; // set newNode to the node AFTER the head
        newNode->prev = nullptr; // node before the node AFTER the head needs to be null 
        delete head; // delete the head node
        head = newNode; // set the head to point to the new node (after the head), pointer we created
        nodeCount--; // decrease node element count by 1
        torf = true; // YES we removed the head
    }
    return torf;
}
// Same as before, but deletes last node (use prev) returning whether or not the op was successful (TRUE/FALSE)
template <typename T>
bool LinkedList<T>::RemoveTail() {
    bool torf = false;
    if (nodeCount == 0) { // nothing here, no ondes
        torf = false;
    }
    // only one node in linked list
    else if (nodeCount == 1) {
        Node* newNode = tail;
        delete newNode;
        head = nullptr;
        tail = nullptr;
        nodeCount--;
        torf = true;
    }
    else {
        Node* newNode = tail->prev;
        newNode->next = nullptr;
        delete tail;
        tail = newNode;
        nodeCount--;
        torf = true;
    }
    return torf;
}
// Remove ALL Nodes containing values matching that of the passed in parameter
// Returns how many instances were removed
template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    unsigned int i = 0;
    Node* newNode = head;
    Node* store;
    // while the newNode HAS items in it
    while (newNode != nullptr) {
        store = newNode->next;
        if (newNode->data == data) {
            if (newNode->prev == nullptr) {
                newNode->next->prev = nullptr;
            }
            else if (newNode->next == nullptr) {
                newNode->prev->next = nullptr;
            }
            else {
                newNode->prev->next = newNode->next;
                newNode->next->prev = newNode->prev;
            }
            delete newNode;
            i++;
        }
        newNode = store;
    }
    nodeCount = nodeCount - i;
    return i;
}
// Deletes the index-th Node from the list, returning whether or not the operationw as successful
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    bool torf = false;
    if (index >= nodeCount) {
        torf = false;
    } // if index is at the very beginning
    else {
        Node* newNode = head;
        unsigned int i = 0;
        while (i != index) {
            i++;
            newNode = newNode->next;
        }
        if (index == 0) {
            RemoveHead();
            return true;
        }
        else if (index == (nodeCount - 1)) {
            RemoveTail();
            return true;
        }
        else {
            newNode->prev->next = newNode->next;
            newNode->next->prev = newNode->prev;
        }
        delete newNode;
        nodeCount = nodeCount - 1;
        torf = true;
    }
    return torf;
}
// Deletes all nodes. Don't forgot the node count
// How many nodes do you have after you deleted all of them?
template <typename T>
void LinkedList<T>::Clear() {
    // here is the new pointer
    Node* newNode = head;

    // if the new pointer isn't NULL (if it IS pointing to something)
    while (newNode != nullptr) {
        // go to the next node
        newNode = newNode->next;
        // delete the top (head) node, not [] since not an array
        delete head;
        // set the head to the newNode
        head = newNode;
    }
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
    // call printforward, printreverse - work on lab 
}
// This function takes in a pointer to a Node -- a starting node
// From that node, recursively visit each node that follows, in forward order & print values
// NEEDS to be implemented using recursion (or tests using it will be worth ZERO points)
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    // while node if NOT null
    if (node != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }

    /*while (node != nullptr) {
        cout << node->data << endl; // print
        PrintForwardRecursive(node->next); // needs base case
    }*/
}

// same as before but opposite (starting from the end)
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    if (node != nullptr) {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }


    /*while (node != nullptr) {
        cout << node->data << endl; // print
        node = node->prev; // move and keep going until nullptr (end is reached),
    }*/
}
// last 2 functions - set up main function, test function
// End of Part 4 of Project 1