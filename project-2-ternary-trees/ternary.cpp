#include <iostream>


class Node {
public:

    Node(int values[], int numValues, int maxChildren = 3, int maxValues = 2) {
        this->MAX_CHILDREN = maxChildren;
        this->MAX_VALUES = maxChildren;
        init();
        this->values = values;
        this->numValues = numValues;
    }


//    Node(int a, int b) {
//        values[0] = a;
//        values[MAX_VALUES - 1] = b;
//        valueSet[0] = true;
//        valueSet[1] = true;
//    }

    bool isEmpty() {
        return values == nullptr;
    }

    bool hasChildren() {
//        bool hasChildren = valueSet[MAX_VALUES - 1]; // last value will never exist if children exist
//
//        if (hasChildren) {
//            hasChildren = left == nullptr && middle == nullptr && right == nullptr;
//        }
        return nodes == nullptr;
    }

    void insertValue(int newValue) {
        if (values == nullptr) {
            // great news, node is empty we can just insert here
            // allocate new arrays
            values = new int[MAX_VALUES]{};
            values[0] = newValue;
            numValues++;
        } else if (numValues < MAX_VALUES) {
            // good news, there is some room so we can insert here
            // TODO code needs to be rewritten slightly to handle different node sizes (sorting needed etc)

            if (newValue > values[numValues - 1]) { // new value is largest value seen, just add it to the end
                values[numValues] = newValue;
                numValues++;
            } else {
                int newValueIndex = 0;
                if (newValue >= values[0]) {
                    // try to predict where index will be
                    // if we make a safe assumption that these random numbers might follow a bell curve we can
                    // calculate a "predicated" index based on the max and min numbers
                    int predictedIndex = (((float) values[numValues - 1] / (float) values[0]) * numValues) - 1;

                    // now we need to find the actual index it will be at, we can use our predicted value to
                    // speed this up
                    if (values[predictedIndex] > newValue) {
                        // if value at index is larger than newValue our prediction was too high
                        for (; predictedIndex > 0; predictedIndex--) {
                            if (values[predictedIndex] < newValue) {
                                // found the actual index!
                                newValueIndex = predictedIndex;
                            }
                        }
                    } else if (values[predictedIndex] < newValue) {
                        if (values[predictedIndex + 1] > newValue) {
                            // wow our prediction was spot on.
                            newValueIndex = predictedIndex;
                        } else {
                            for (; predictedIndex < numValues; predictedIndex++) {
                                if (values[predictedIndex + 1] > newValue) {
                                    // found the actual index!
                                    newValueIndex = predictedIndex;
                                }
                            }
                        }
                    }
                }

                int *temp = new int[MAX_VALUES];
                temp[newValueIndex] = newValue;
                for (int i = 0; i < numValues; i++) {
                    if (i >= newValueIndex) {
                        temp[i + 1] = values[i];
                    } else {
                        temp[i] = values[i];
                    }

                }

                values = temp;
                numValues++;
                // TODO uncomment this and test
                //delete[](temp);
            }
        } else {
            // can't insert here, check children
            Node **target;  // pointer to pointer


            // TODO uh-oh brain time you are gonna need thinky bits for this
            if (newValue <= values[0]) {
                // insert in to node on left
                target = &left;
            } else if (newValue <= values[MAX_VALUES - 1]) {
                // insert in to node in middle
                target = &middle;
            } else { // (implicitly, newValue > topNode.b)
                // insert in to node on right
                target = &right;
            }



            if (*target == nullptr) {
                Node *newNode = new Node(newValue);
                *target = newNode;
            } else {
                (*target)->insertValue(newValue);
            }
        }
    }

    Node getLeftNode() {
        return *left;
    }

    Node getMiddleNode() {
        return *middle;
    }

    Node getRightNode() {
        return *right;
    }

    void print(bool topNode = false) {
        if (!topNode) {
            std::cout << "(";
        }


        if (left) {
            left->print();
            printf(" ");
        }

        if (valueSet[0]) {
            printf("%d", values[0]);
        }

        if (middle) {
            printf(" ");
            middle->print();
        }

        if (valueSet[MAX_VALUES - 1]) {
            printf(" ");
            printf("%d", values[MAX_VALUES - 1]);
        }
        if (right) {
            printf(" ");
            right->print();
        }

        if (!topNode) {
            std::cout << ")";
        }
    }


private:
    static int MAX_VALUES;
    static int MAX_CHILDREN;

    // TODO need to init arrays
    explicit Node(int a) {
        init();
        values[0] = a;
        numValues++;
    }

    Node() {
        init();
    }

    void init() {
        nodes = new Node[MAX_CHILDREN]{};
    }

//    Node *left{};
//    Node *middle{};
//    Node *right{};

    int numValues = 0;
    Node *nodes;
    int *values;
};

int getInt() {
    int val;
    std::cin >> val;
    return val;
}

//void insert(int newValue, Node& parentNode) {
//    Node targetNode = parentNode.insertValue(newValue);
//
//    if (targetNode == parentNode) {
//        targetNode = new Node(newValue);
//    } else {
//        insert(newValue, *targetNode);
//    }
//}

//void traverseNode(Node parentNode) {
//    // print from left to right
//    if (parentNode.)
//
//        Node left = parentNode.getLeftNode();
//    Node middle = parentNode.getMiddleNode();
//    Node right = parentNode.getRightNode();
//
//    if (!left.isEmpty()) {
//        printf("(%d", left.getA());
//        traverseNode(left);
//        std::cout << ")";
//    }
//
//    printf(" %d ", parentNode.getA());
//
//    if (!middle.isEmpty()) {
//        printf("(%d", middle.getA());
//        traverseNode(middle);
//        std::cout << ")";
//    }
//
//    printf(" %d ", parentNode.getB());
//
//    if (!right.isEmpty()) {
//        printf("(%d", right.getA());
//        traverseNode(right);
//        std::cout << ")";
//    }
//
//}


int main(int argc, char **argv) {
    const int NUM_INTEGERS = std::atoi(argv[1]);

    Node topNode = Node(getInt(), getInt());
//return *this;
    for (int i = 2; i < NUM_INTEGERS; i++) {
        int newNum = getInt();
        //printf("newNum value: %d", newNum);
        topNode.insertValue(newNum);
    }

    topNode.print(true);
    //traverseNode(topNode);

    return 0;
}