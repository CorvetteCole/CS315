//
// Created by coleg on 2/15/21.
//

#include "Train.h"

Train::Train() {
    cars = DoublyLinkedList<int>();
}

Train::Train(DoublyLinkedList<int> cars) {
    this->cars = cars;
}

int Train::getValue() {
    int value = 0;
    int position = 1;

    value = cars.getValue();


//    for (int car : cars){   couldn't figure out how to implement range based loops in a way I understood :(
//        value += car * position;
//        position++;
//    }

    return value;
}

bool Train::isEmpty() {
    return cars.isEmpty();
}

int Train::removeFront() {
    return cars.removeFront();
}

int Train::removeBack() {
    return cars.removeBack();
}

void Train::insertFront(int car) {
    cars.insertFront(car);
}


