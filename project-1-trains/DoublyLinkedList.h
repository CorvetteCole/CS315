//
// Created by coleg on 2/15/21.
//

#ifndef PROJECT_1_TRAINS_DOUBLYLINKEDLIST_H
#define PROJECT_1_TRAINS_DOUBLYLINKEDLIST_H

using namespace std;

template<typename T>
struct Node {
    Node *previous = nullptr;
    Node *next = nullptr;
    T data;
};

template<class T>
class DoublyLinkedList {
public:

    DoublyLinkedList() {
        front = nullptr;
        back = nullptr;
    };

    T removeFront() {
        T removed = front->data;
        removeNode(front);
        return removed;
    };

    T removeBack() {
        T removed = back->data;
        removeNode(back);
        return removed;
    };

    T remove(int index) {
        Node<T> *node = getNode(index);
        T removed = node->data;
        removeNode(node);
        return removed;
    };

    // TODO this is hacky
    int getValue() {
        auto *currentNode = front;
        int total = 0;
        int index = 1;
        while (currentNode != nullptr) {
            total += (currentNode->data * index);
            currentNode = currentNode->next;
            index++;
        }
        return total;
    }

    void insertFront(T data){
        Node<T> *newNode;
        newNode = new Node<T>();
        newNode->data = data;
        newNode->next = front;
        newNode->previous = nullptr;
        if (front == nullptr) {
            // list empty
            back = newNode;
        } else {
            front->previous = newNode;
        }
        front = newNode;
    };

    void insertBack(T data){
        auto *newNode = new Node<T>();
        newNode->data = data;
        newNode->previous = back;
        if (back == nullptr) {
            // list empty
            front = newNode;
        } else {
            back->next = newNode;
        }
        back = newNode;
    };

    bool isEmpty() {
        return front == nullptr || back == nullptr;
    };

    T &operator[](int index) {

        return getNode(index)->data;
    };

private:

    Node<T> *getNode(int index) {
        // TODO improve this
        Node<T> *current = front;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return current;
    };

    void removeNode(Node<T> *node) {
        // check if node was in back or front
        if (node->previous == nullptr) {
            // front
            front = front->next;
            if (front != nullptr) {
                front->previous = nullptr;
            } else {
                // if front is nullptr set back to that as well
                back == nullptr;
            }
        } else if (node->next == nullptr) {
            // back
            back = back->previous;
            back->next = nullptr;
        } else {
            // cut node out of chain
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
        delete (node);
    };

    Node<T> *front;
    Node<T> *back;
};

#endif //PROJECT_1_TRAINS_DOUBLYLINKEDLIST_H
