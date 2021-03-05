//
// Created by coleg on 2/15/21.
//

#ifndef PROJECT_1_TRAINS_TRAIN_H
#define PROJECT_1_TRAINS_TRAIN_H

#include "DoublyLinkedList.h"

class Train {
public:
    Train();

    Train(DoublyLinkedList<int> cars);

    int getValue();

    bool isEmpty();

    int removeFront();

    int removeBack();

    void insertFront(int car);

private:
    DoublyLinkedList<int> cars;
};


#endif //PROJECT_1_TRAINS_TRAIN_H
