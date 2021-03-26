

/* C++ implementation QuickSort using Lomuto's partition
   Scheme.*/
#include<bits/stdc++.h>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>

using namespace std;

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* Function to print an array */
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


// Problem 3c
struct Node {
    char data;
    unsigned isEndOfString: 1;
    struct Node *left, *eq, *right;
} *temp = NULL;

struct Node *newNode(char data) {
    temp = new Node;
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

void insert(struct Node **root, char *word) {
    if (!(*root))
        *root = newNode(*word);

    if ((*word) < (*root)->data)
        insert(&((*root)->left), word);

    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word);

    else {
        if (*(word + 1))
            insert(&((*root)->eq), word + 1);

        else
            (*root)->isEndOfString = 1;
    }
}

void traverseTSTUtil(struct Node *root, char *buffer, int depth) {
    if (root) {
        traverseTSTUtil(root->left, buffer, depth);

        buffer[depth] = root->data;
        if (root->isEndOfString) {
            buffer[depth + 1] = '\0';
            cout << buffer << endl;
        }

        traverseTSTUtil(root->eq, buffer, depth + 1);

        traverseTSTUtil(root->right, buffer, depth);
    }
}

void traverseTST(struct Node *root) {
    char buffer[50];
    traverseTSTUtil(root, buffer, 0);
}

int searchTST(struct Node *root, char *word) {
    if (!root)
        return 0;

    if (*word < (root)->data)
        return searchTST(root->left, word);

    else if (*word > (root)->data)
        return searchTST(root->right, word);

    else {
        if (*(word + 1) == '\0')
            return root->isEndOfString;

        return searchTST(root->eq, word + 1);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Function to build a Max-Heap from the given array
void buildHeap(int arr[], int n) {
    // Index of last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// A utility function to print the array
// representation of Heap
void printHeap(int arr[], int n) {
    cout << "Array representation of Heap is:\n";

    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

void problem2c() {
    int arr[] = {7, 2, 4, 1, 8, 3, 6, 9, 5, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    partition(arr, 0, n - 1);


//    quickSort(arr, 0, n - 1);
//    printf("Sorted array: \n");
    printArray(arr, n);
}

void problem2d() {
    vector<int> numbers = {7, 2, 4, 1, 8, 3, 6, 9, 5, 0};

    make_heap(begin(numbers), end(numbers));

    for (int number : numbers) {
        cout << number << ' ';
    }
}

void problem3c() {
    struct Node *root = NULL;
    int arr[] = {7, 2, 4, 1, 8, 3, 6, 9, 5, 0};


    insert(&root, "7");
    insert(&root, "2");
    insert(&root, "4");
    insert(&root, "1");
    insert(&root, "8");
    insert(&root, "3");
    insert(&root, "6");
    insert(&root, "9");
    insert(&root, "5");
    insert(&root, "0");

    cout << "Following is traversal of ternary search tree\n";
    traverseTST(root);
}

void problem3e() {
    // Binary Tree Representation
    // of input array
    // 1
    //           /     \
    // 3         5
    //      /    \     /  \
    // 4      6   13  10
    //    / \    / \
    // 9   8  15 17
    int arr[] = {7, 2, 4, 1, 8, 3, 6, 9, 5, 0};

    int n = sizeof(arr) / sizeof(arr[0]);

    buildHeap(arr, n);

    printHeap(arr, n);
    // Final Heap:
    // 17
    //           /      \
    // 15         13
    //       /    \      /  \
    // 9      6    5   10
    //     / \    /  \
    // 4   8  3    1
}


// Driver program to test above functions
int main() {
//    problem2c();
//    problem2d();
    problem3c();
//    problem3e();


    return 0;
}