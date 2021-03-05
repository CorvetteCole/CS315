#include <iostream>
#include "DoublyLinkedList.h"
#include "Train.h"

using namespace std;

DoublyLinkedList<Train> initTrains(const int NUM_TRAINS, const int NUM_CARS) {
    DoublyLinkedList<Train> startTrains = DoublyLinkedList<Train>();

    for (int trainIndex = 0; trainIndex < NUM_TRAINS; trainIndex++) {
        DoublyLinkedList<int> startCars = DoublyLinkedList<int>();
        for (int car = 0; car < NUM_CARS; car++) {
            startCars.insertBack((car + 1));
        }
        startTrains.insertBack(Train(startCars));
        //startTrains[trainIndex] = Train();
    }

    return startTrains;
}

int tossDie(int sides) {
    int randValue;
    cin >> randValue;
    return (randValue % sides);
}

int main(int argc, char **argv) {

    const int NUM_TRAINS = atoi(argv[1]);
    const int STARTING_CARS = atoi(argv[2]);
    const int MAX_STEPS = atoi(argv[3]);


    if (NUM_TRAINS <= 0 || STARTING_CARS <= 0 || MAX_STEPS <= 0) {
        // fail gently
        cout << "Arguments must be positive integers." << endl;
    }

    //Train trains[NUM_TRAINS];

    DoublyLinkedList<Train> trainList = initTrains(NUM_TRAINS, STARTING_CARS);

    bool trainEmpty = false;
    int maxTrainIndex;
    // run train routine
    for (int currentStep = 0; currentStep < MAX_STEPS && !trainEmpty; currentStep++) {

        int donorTrainNum = tossDie(NUM_TRAINS);
        bool removeFromBack = tossDie(2);
        int receiverTrainNum = tossDie(NUM_TRAINS);
        //printf("donorTrain: %s receiverTrain %s remove")

        printf("turn %d: train %d sends a car to train %d, from %s \n", currentStep + 1, donorTrainNum + 1,
               receiverTrainNum + 1, removeFromBack ? "back" : "front");


        Train *donorTrain = &trainList[donorTrainNum];
        Train *receiverTrain = &trainList[receiverTrainNum];

        int car = removeFromBack ? donorTrain->removeBack() : donorTrain->removeFront();

        receiverTrain->insertFront(car);

        int maxValue = INT32_MIN;
        for (int i = 0; i < NUM_TRAINS; i++) {
            Train train = trainList[i];
            int trainValue = train.getValue();
            printf("\ttrain %d: value: %d\n", i + 1, trainValue);
            if (trainValue > maxValue){
                maxValue = trainValue;
                maxTrainIndex = i;
            }
            if (train.isEmpty()) {
                trainEmpty = true;
            }
        }
    }

    printf("The simulation is finished. Train %d has the highest value.\n", maxTrainIndex + 1);

    return 0;
}



