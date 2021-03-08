#include <iostream>

class Node {
public:
    static int MAX_VALUES;
    static int MAX_CHILDREN;

    Node(int values[], int numValues = 2, int maxChildren = 3) {
        MAX_CHILDREN = maxChildren;
        MAX_VALUES = numValues;
        for (int i = 0; i < numValues; i++) {
            insertValue(values[i]);
        }

    }

    bool hasChildren() {
        return children != nullptr;
    }

    void insertValue(int newValue) {
        if (values == nullptr) { // node is empty we can just insert here
            // allocate new arrays
            values = new int[MAX_VALUES]{};
            values[0] = newValue;
            numValues++;
        } else if (numValues < MAX_VALUES) { // there is some room so we can insert in this node

            if (newValue > values[numValues - 1]) { // new value is largest value seen, just add it to the end
                values[numValues] = newValue;
                numValues++;
            } else {
                int newValueIndex = 0;
                if (newValue >= values[0]) {
                    getPredictedValueIndex(newValue, newValueIndex);
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
                delete[](values);
                values = temp;
                numValues++;
            }
        } else {
            int targetNodeIndex = 0;

            getTargetNodeIndex(newValue, targetNodeIndex);

            if (children == nullptr) {
                children = new Node[MAX_CHILDREN]{};
            }

            (children + targetNodeIndex)->insertValue(newValue);
            if (targetNodeIndex + 1 > numChildren) {
                numChildren = targetNodeIndex + 1;
            }
        }
    }


    void print(bool topNode = false) {
        if (!topNode) {
            std::cout << "(";
        }
        if (!hasChildren()) { // no children present
            for (int valueIndex = 0; valueIndex < numValues; valueIndex++) {
                printf("%d", values[valueIndex]);
                if (valueIndex != numValues - 1) {
                    printf(" ");
                }
            }
        } else { // children present

            int childrenPerValue = 1;
            int extraChildren = 0;
            int valuesPerChild = 1;
            int extraValues = 0;

            if (MAX_VALUES >= MAX_CHILDREN) {
                valuesPerChild = MAX_VALUES / (MAX_CHILDREN - 1);
                extraValues = MAX_VALUES % (MAX_CHILDREN - 1);
            } else { // values < children
                childrenPerValue = MAX_CHILDREN / (MAX_VALUES + 1);
                extraChildren = MAX_CHILDREN % (MAX_VALUES + 1);
            }


            int valueIndex = 0;
            int childIndex = 0;

            while (childIndex < numChildren || valueIndex < numValues) {
                int targetChildIndex = childIndex + childrenPerValue + !!extraChildren;
                if (extraChildren > 0) extraChildren--;

                for (; childIndex < targetChildIndex; childIndex++) {
                    if (children[childIndex].numValues > 0) {
                        if (childIndex != 0) {
                            //printf(" ");
                        }
                        children[childIndex].print();
                        if (childIndex != numChildren - 1) {
                            //printf(" ");
                        }
                    }
                }

                int targetValueIndex = valueIndex + valuesPerChild + !!extraChildren;
                if (extraValues > 0) extraChildren--;

//                if (valueIndex < numValues){
//                    printf("%d", values[valueIndex]);
//                    valueIndex++;
//                }

                for (; valueIndex < targetValueIndex && valueIndex < numValues; valueIndex++) {
                    if (valueIndex < targetValueIndex) {
                        printf(" ");
                    }

                    printf("%d", values[valueIndex]);
                    if (valueIndex == targetValueIndex - 1) {
                        printf(" ");
                    }

                }

            }
        }
        if (!topNode) {
            std::cout << ")";
        }

    }


private:
    explicit Node(int a) {
        values = new int[MAX_VALUES];
        values[0] = a;
        numValues++;
    }

    Node() = default;

    void getTargetNodeIndex(int newValue, int &targetNodeIndex) {
        int compareLimits = MAX_VALUES - MAX_CHILDREN;
        if (compareLimits >= 0) { // values >= children
            int valuesPerChild = MAX_VALUES / (MAX_CHILDREN - 1);
            int extraValues = MAX_VALUES % (MAX_CHILDREN - 1);
            // iterate children node index by 1, value index by calculated valuesPerChild
            for (int childIndex = 0, valueIndex = 0;
                 valueIndex < MAX_VALUES; valueIndex += valuesPerChild) {
                if (extraValues > 0) {
                    valueIndex++;
                    extraValues--;
                }
                if (newValue <= values[valueIndex]) {
                    targetNodeIndex = childIndex;
                    break;
                }
                // if the newValue is not smaller than any existing values...
                targetNodeIndex = childIndex;
            }

        } else { // values < children

            // offset to account for there being one more state than values in the math
            int childrenPerValue = MAX_CHILDREN / (MAX_VALUES + 1);
            int extraChildren = MAX_CHILDREN % (MAX_VALUES + 1);
            // iterate value index by 1, children index by calculated childrenPerValue
            for (int valueIndex = 0, childIndex = 0;
                 childIndex < MAX_CHILDREN; childIndex += childrenPerValue) {
                if (extraChildren > 0) {
                    childIndex++;
                    extraChildren--;
                }
                if (newValue <= values[valueIndex]) {
                    targetNodeIndex = childIndex;
                    break;
                }

                // if the newValue is not smaller than any existing values...
                targetNodeIndex = childIndex;
                if (valueIndex + 1 != numValues) {
                    valueIndex++;
                }
            }
        }
    }

    void getPredictedValueIndex(int newValue, int &newValueIndex) {
        // try to predict where index will be
        // if we make a safe assumption that these random numbers might follow a bell curve we can
        // calculate a "predicated" index based on the max and min numbers
        int predictedIndex = (((float) values[numValues - 1] / (float) values[0]) * numValues) - 1;

        if (predictedIndex < 0 || predictedIndex >= numValues) {
            predictedIndex = 0;
        }

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

    int numValues = 0;
    int numChildren = 0;
    Node *children = nullptr;
    int *values;
};

int Node::MAX_VALUES = 0;
int Node::MAX_CHILDREN = 0;


int getInt() {
    int val;
    std::cin >> val;
    return val;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("please include 3 integer parameters. num points, num values per node, num children per node\n");
    } else {
        const int NUM_INTEGERS = std::atoi(argv[1]);
        const int NUM_VALUES = std::atoi(argv[2]);
        const int NUM_CHILDREN = std::atoi(argv[3]);

        int *topValues = new int[NUM_VALUES]{};
        for (int i = 0; i < NUM_VALUES; i++) {
            topValues[i] = getInt();
        }

        Node topNode = Node(topValues, NUM_VALUES, NUM_CHILDREN);

        for (int i = 2; i < NUM_INTEGERS; i++) {
            int newNum = getInt();
            topNode.insertValue(newNum);
        }

        topNode.print(true);
    }

    return 0;
}