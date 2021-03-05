#include <iostream>

const int NODE_SIZE = 2;

class Node {
public:
    Node(int a, int b) {
        values[0] = a;
        values[NODE_SIZE - 1] = b;
        valueSet[0] = true;
        valueSet[1] = true;
    }

    explicit Node(int a) {
        values[0] = a;
        valueSet[0] = true;
    }

    Node() = default;

    bool isEmpty() {
        return !(valueSet[0] || valueSet[1]);
    }

    bool hasChildren() {
        bool hasChildren = valueSet[NODE_SIZE - 1]; // last value will never exist if children exist
        if (hasChildren) {
            hasChildren = left == nullptr && middle == nullptr && right == nullptr;
        }
        return hasChildren;
    }

    void insertValue(int newValue) {
        if (isEmpty()) {
            // great news, node is empty we can just insert here
            values[0] = newValue;
            valueSet[0] = true;
            // TODO code needs to be rewritten slightly to handle different node sizes (sorting needed etc)
        } else if (!valueSet[NODE_SIZE - 1]) {
            // good news, b is empty, we can just insert here
            // if newValue < a, move a to b and insert in a. otherwise just insert in b
            if (newValue < values[0]) {
                values[NODE_SIZE - 1] = values[0];
                values[0] = newValue;
            } else {
                values[NODE_SIZE - 1] = newValue;
            }
            valueSet[NODE_SIZE - 1] = true;
        } else {
            // can't insert here, check children
            Node **target;  // pointer to pointer
            if (newValue <= values[0]) {
                // insert in to node on left
                target = &left;
            } else if (newValue <= values[NODE_SIZE - 1]) {
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

        if (valueSet[NODE_SIZE - 1]) {
            printf(" ");
            printf("%d", values[NODE_SIZE - 1]);
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
    int values[NODE_SIZE]{};
    bool valueSet[NODE_SIZE]{}; // default for array is false
    Node *left{};
    Node *middle{};
    Node *right{};


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