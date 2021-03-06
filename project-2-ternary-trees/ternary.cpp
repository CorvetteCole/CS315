#include <iostream>
#include <bits/stdc++.h> // TODO get rid of this

class Node {
public:
    static int MAX_VALUES;
    static int MAX_CHILDREN;

    Node(int values[], int numValues = 2, int maxChildren = 3) {
        MAX_CHILDREN = maxChildren;
        MAX_VALUES = numValues;
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
        return children != nullptr;
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

                    if (predictedIndex < 0 || predictedIndex >= numValues){
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
            //Node **target;  // pointer to pointer

            int targetNodeIndex = 0;

            int compareLimits = MAX_VALUES - MAX_CHILDREN;
            if (compareLimits >= 0) { // values >= children
                int valuesPerChild = MAX_VALUES / (MAX_CHILDREN - 1);
                int extraValues = MAX_VALUES % (MAX_CHILDREN - 1);
                // TODO investigate possible point of failure if numValues != MAX_VALUES
                // iterate children node index by 1, value index by calculated valuesPerChild
                for (int i = 0, valueIndex = 0;
                     valueIndex < MAX_VALUES; valueIndex += valuesPerChild) {
                    if (extraValues > 0) {
                        valueIndex++;
                        extraValues--;
                    }
                    if (newValue <= values[valueIndex]) {
                        targetNodeIndex = i;
                        break;
                    }
                    // TODO possible source of bugs
                    targetNodeIndex = i;
                }

            } else { // values < children

                // offset to account for there being one more state than values in the math
                int childrenPerValue = MAX_CHILDREN / (MAX_VALUES + 1);
                int extraChildren = MAX_CHILDREN % (MAX_VALUES + 1);
                // TODO investigate possible point of failure if i != MAX_VALUES
                // iterate value index by 1, children index by calculated childrenPerValue
                for (int i = 0, childIndex = 0;
                     childIndex < MAX_CHILDREN; childIndex += childrenPerValue) {
                    if (extraChildren > 0) {
                        childIndex++;
                        extraChildren--;
                    }
                    int tempValue = values[i];

                    if (newValue <= tempValue) {
                        targetNodeIndex = childIndex;
                        break;
                    }
                    // TODO possible source of bugs
                    targetNodeIndex = childIndex;
                    if (i + 1 != numValues){
                        i++;
                    }
                }
            }

            if (children == nullptr){
                children = new Node[MAX_CHILDREN]{};
            }

            auto targetNode = (children + targetNodeIndex);
            (children + targetNodeIndex)->insertValue(newValue);
            if (targetNodeIndex + 1 > numChildren){
                numChildren = targetNodeIndex + 1;
            }
//            if ((children + targetNodeIndex)->numChildren == 0) { // TODO verify this works as intended
//                Node *newNode = new Node(newValue);
//                numChildren++;
//                printf("numChildren in target node: %d\n" , children[targetNodeIndex].numChildren);
//                *(children + targetNodeIndex) = *newNode; // TODO no way this works
//            } else {
//                (children + targetNodeIndex)->insertValue(newValue);
//            }
        }
    }


    void print(bool topNode = false) {
        if (!topNode) {
            std::cout << "(";
        }

//        if (hasChildren()) {
//            if (children[0].numValues > 0) {
//                children[0].print();
//                printf(" ");
//            }
//        }
//
//        if (numValues >= 1) {
//            printf("%d", values[0]);
//        }
//
//        if (hasChildren()) {
//            if (children[1].numValues > 0) {
//                printf(" ");
//                children[1].print();
//            }
//        }
//
//        if (numValues >= 2) {
//            printf(" ");
//            printf("%d", values[1]);
//        }
//
//        if (hasChildren()) {
//            if (children[2].numValues > 0) {
//                printf(" ");
//                children[2].print();
//            }
//        }
//
//
//        if (!topNode) {
//            std::cout << ")";
//        }



//        if (numChildren == 0){
//            for (int valueIndex = 0; valueIndex < numValues; valueIndex++) {
//                printf("%d", values[valueIndex]);
//                if (valueIndex != numValues - 1) {
//                    printf(" ");
//                }
//            }
//        } else {
//
//            for (int valueIndex = 0; valueIndex < numValues; valueIndex++) {
//                if (&children[valueIndex])+ {
//                    std::cout << "(";
//                    children[valueIndex].print();
//                    std::cout << ")";
//                }
//
//                //printf("%d", values[valueIndex]);
//            }
//        }

//        if (numValues < MAX_VALUES){ // no children present
//
//        } else { // children present
//            if (&children[0]){
//                children[0].print();
//                printf(" ");
//            }
//            if (values[0])
//        }
//
//
        if (!hasChildren()) { // no children present
            for (int valueIndex = 0; valueIndex < numValues; valueIndex++) {
                printf("%d", values[valueIndex]);
                if (valueIndex != numValues - 1) {
                    printf(" ");
                }
            }
        }
//        else {
//            for (int valueIndex = 0; valueIndex < MAX_VALUES; valueIndex++){
//                printf("%d", values[valueIndex]);
//                if (valueIndex != numValues - 1) {
//                    printf(" ");
//                }
//            }
//            printf("(");
//            for (int i = 0; i < numChildren; i++) {
//                children[i].print();
//            }
//            printf(")");
//        }


        else { // children present

            int childrenPerValue = 1;
            int extraChildren = 0;
            int valuesPerChild = 1;
            int extraValues = 0;

            if (MAX_VALUES >= MAX_CHILDREN) {
                valuesPerChild= MAX_VALUES / (MAX_CHILDREN - 1);
                extraValues = MAX_VALUES % (MAX_CHILDREN - 1);
            } else { // values < children
                childrenPerValue = MAX_CHILDREN / (MAX_VALUES + 1);
                extraChildren = MAX_CHILDREN % (MAX_VALUES + 1);
            }







            if (numValues <= numChildren){
                int valueIndex = 0;
                int childIndex = 0;

                while (childIndex < numChildren){
                    int targetChildIndex = childIndex + childrenPerValue + !!extraChildren;
                    if (extraChildren > 0) extraChildren--;

                    for (; childIndex < targetChildIndex; childIndex++){
                        if (children[childIndex].numValues > 0) {
                            printf(" ");
                            children[childIndex].print();
                            printf(" ");
                        }
                    }

                    if (valueIndex < numValues) {
                        printf("%d", values[valueIndex]);
                        valueIndex++;
                    }

                }
            } else if (numValues > numChildren){
                int valueIndex = 0;
                int childIndex = 0;
                while (valueIndex < numValues && childIndex < numChildren){
                    children[childIndex].print();
                    childIndex++;
                    for (valueIndex = 0; valueIndex < valuesPerChild + !!extraValues; valueIndex++){
                        if (extraValues > 0) extraValues--;
                        values[valueIndex];
                    }
                }


            }

//            for (int valueIndex = 0; valueIndex < numValues; valueIndex++) {
//                // print children
//
//                printf("printing child at index %d for value %d\n", valueIndex, values[valueIndex]);
//                if (children[valueIndex].numValues > 0) {
//                    children[valueIndex].print();
//                }
//                printf("\n");
//
//
////                for (int childIndex = valueIndex; childIndex < childIndex + childrenPerValue; childIndex++) {
////                    children[childIndex].print();
////                    for (childIndex + 1;
////                         childIndex < numChildren && childIndex < childIndex + childrenPerValue + !!extraChildren; childIndex++) {
////                        extraChildren--;
////                        // print children
////                        children[childIndex].print();
////                    }
//
////                }
//                printf("%d", values[valueIndex]);
////                for (valueIndex + 1;
////                     valueIndex < numValues && valueIndex < valueIndex + valuesPerChild + !!extraValues; valueIndex++) {
////                    extraValues--;
////                    // print children
////                    printf("%d", values[valueIndex]);
////                    if (valueIndex != numValues - 1){
////                        printf(" ");
////                    }
////                }
//
//                // TODO might need to do something about the space printing above
//                //                 if (valueIndex != numValues - 1){
//                //                    printf(" ");
//                //                }
//
//            }
        }
        if (!topNode) {
            std::cout << ")";
        }

    }


private:
    // TODO need to init arrays
    explicit Node(int a) {
        init();
        values = new int [MAX_VALUES];
        values[0] = a;
        numValues++;
    }

    Node() {
        init();
    }

    void init() {
        //children = ;
    }

//    Node *left{};
//    Node *middle{};
//    Node *right{};

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
    if (argc < 4){
        printf("please include 3 integer parameters. num points, num values per node, num children per node\n");
    } else {


        const int NUM_INTEGERS = std::atoi(argv[1]);
        const int NUM_VALUES = std::atoi(argv[2]);
        const int NUM_CHILDREN = std::atoi(argv[3]);

//    if (NUM_CHILDREN >= NUM_VALUES) {
//        printf("num children per node (%d) should be less than num of values (%d)\n", NUM_CHILDREN, NUM_VALUES);
//    } else {

        int *topValues = new int[NUM_VALUES]{};
        for (int i = 0; i < NUM_VALUES; i++) {
            topValues[i] = getInt();
        }
        std::sort(topValues, topValues + NUM_VALUES);

        Node topNode = Node(topValues, NUM_VALUES, NUM_CHILDREN);

        for (int i = 2; i < NUM_INTEGERS; i++) {
            int newNum = getInt();
            //printf("newNum value: %d", newNum);
            topNode.insertValue(newNum);
        }

        topNode.print(true);
        //traverseNode(topNode);
    }

    return 0;
}