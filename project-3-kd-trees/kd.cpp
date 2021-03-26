#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int BUCKET_SIZE = 10;
int NUM_DIMENSIONS;
int NUM_POINTS;

class Node {
public:
    Node(vector<vector<int>> dataPoints) {
        insert(std::move(dataPoints));
    }

    vector<vector<int>> search(vector<int> point) {
        if (data.empty()) {
            if (point[discriminantDimension] < discriminantValue) {
                return left->search(point);
            } else if (point[discriminantDimension] > discriminantValue) {
                return right->search(point);
            } else {
                return right->search(point);
            }
        } else {
            return data;
        }
    }

private:
    void insert(vector<vector<int>> dataPoints) {
        if (dataPoints.size() > BUCKET_SIZE) {
            discriminantDimension = getDiscriminateDimension(dataPoints);
            discriminantValue = getDiscriminateValue(dataPoints, discriminantDimension);
            vector<vector<int>> leftVec;
            vector<vector<int>> rightVec;
            for (int i = 0; i < dataPoints.size(); i++) {
                if (dataPoints[i][discriminantDimension] < discriminantValue) {
                    leftVec.push_back(dataPoints[i]);
                } else if (dataPoints[i][discriminantDimension] > discriminantValue) {
                    rightVec.push_back(dataPoints[i]);
                } else {
                    rightVec.push_back(dataPoints[i]);
                }
            }
            left = new Node();
            left->insert(leftVec);
            right = new Node();
            right->insert(rightVec);
        } else {
            data = dataPoints;
        }
    }


    Node *left{}, *right{};
    int discriminantDimension{}, discriminantValue{};
    vector<vector<int>> data;

    Node() = default;

    static int getDiscriminateDimension(const vector<vector<int>> &dataPoints) {
        int *minPoints = new int[NUM_DIMENSIONS]{};
        int *maxPoints = new int[NUM_DIMENSIONS]{};
        for (int i = 0; i < NUM_DIMENSIONS; i++) {
            minPoints[i] = INT32_MAX;
            maxPoints[i] = INT32_MIN;
        }

        for (auto point : dataPoints) {
            for (int i = 0; i < NUM_DIMENSIONS; i++) {
                if (point[i] > maxPoints[i]) {
                    maxPoints[i] = point[i];
                } else if (point[i] < minPoints[i]) {
                    minPoints[i] = point[i];
                }
            }
        }
        int largestRange = INT32_MIN;
        int largestRangeIndex = 0;
        for (int i = 0; i < NUM_DIMENSIONS; i++) {
            int range = maxPoints[i] - minPoints[i];
            if (range > largestRange) {
                largestRange = range;
                largestRangeIndex = i;
            }
            //printf("dim: %d, min: %d, max: %d\n", i, minPoints[i], maxPoints[i]);
        }
        //printf("largest range at dim: %d\n", largestRangeIndex);
        return largestRangeIndex;
    }

    static int median(vector<int> &v) {
        size_t n = v.size() / 2;
        nth_element(v.begin(), v.begin() + n, v.end());
        return v[n];
    }

    static int getDiscriminateValue(const vector<vector<int>> &dataPoints, const int discriminateDim) {

        vector<int> dimVal;
        dimVal.reserve(dataPoints.size());
        for (auto point : dataPoints) {
            dimVal.push_back(point[discriminateDim]);
        }

        int medianVal = median(dimVal);
        // TODO replace with own median code
        return medianVal;
    }


};


int main(int argc, char **argv) {
    if (argc != 4) {
        printf("please include 3 integer parameters. num dimensions, num points, num probes\n");
    } else {
        NUM_DIMENSIONS = std::atoi(argv[1]);
        NUM_POINTS = std::atoi(argv[2]);
        int NUM_PROBES = std::atoi(argv[3]);

        if (NUM_DIMENSIONS > 0 && NUM_POINTS > 0 && NUM_PROBES > 0) {
            vector<vector<int>> dataPoints(NUM_POINTS);
            vector<vector<int>> probes(NUM_PROBES);


            for (int i = 0; i < NUM_POINTS; i++) {
                dataPoints[i] = vector<int>(NUM_DIMENSIONS);
                //printf("i: %d", i);
                for (int j = 0; j < NUM_DIMENSIONS; j++) {
                    cin >> dataPoints[i][j];
                    //printf(", %d", dataPoints[i][j]);
                }
                //printf("\n");
            }

            for (int i = 0; i < NUM_PROBES; i++) {
                probes[i] = vector<int>(NUM_DIMENSIONS);
                //printf("i: %d", i);
                for (int j = 0; j < NUM_DIMENSIONS; j++) {
                    cin >> probes[i][j];
                    //printf(", %d", dataPoints[i][j]);
                }
                //printf("\n");
            }

            // vector<vector<int>> dataPoints, int numDimensions, int bucketSize, int numPoints
            Node kdRoot = Node(dataPoints);

            for (auto probe : probes) {
                vector<vector<int>> bucket = kdRoot.search(probe);

                printf("probe");
                for (auto val : probe) {
                    printf(" %d", val);
                }
                printf(" reaches bucket: %d elements\n", bucket.size());
                for (auto point : bucket) {
                    for (auto val : point) {
                        printf("%d ", val);
                    }
                    printf("\n");
                }


            }



































//            // generate two dimension array of data
//            int **dataPoints = new int *[NUM_POINTS];
//
//            int *minPoints = new int[NUM_DIMENSIONS]{};
//            int *maxPoints = new int[NUM_DIMENSIONS]{};
//            for (int i = 0; i < NUM_DIMENSIONS; i++) {
//                minPoints[i] = INT32_MAX;
//                maxPoints[i] = INT32_MIN;
//            }
//
//
//            for (int i = 0; i < NUM_POINTS; i++) {
//                dataPoints[i] = new int[NUM_DIMENSIONS];
//                printf("i: %d", i);
//                for (int j = 0; j < NUM_DIMENSIONS; j++) {
//                    cin >> dataPoints[i][j];
//
//                    if (dataPoints[i][j] < minPoints[j]) {
//                        minPoints[j] = dataPoints[i][j];
//                    }
//                    if (dataPoints[i][j] > maxPoints[j]) {
//                        maxPoints[j] = dataPoints[i][j];
//                    }
//
//                    printf(", %d", dataPoints[i][j]);
//                }
//                printf("\n");
//            }
//
//            int largestRange = INT32_MIN;
//            int largestRangeIndex = 0;
//            for (int i = 0; i < NUM_DIMENSIONS; i++) {
//                int range = maxPoints[i] - minPoints[i];
//                if (range > largestRange) {
//                    largestRange = range;
//                    largestRangeIndex = i;
//                }
//                printf("dim: %d, min: %d, max: %d\n", i, minPoints[i], maxPoints[i]);
//            }
//            printf("largest range at dim: %d\n", largestRangeIndex);
//
//            int *dim = new int[NUM_POINTS]{};
//            for (int i = 0; i < NUM_POINTS; i++) {
//                dim[i] = dataPoints[i][largestRangeIndex];
//            }
//
//            int median = findMedian(dim, NUM_POINTS);
//
//            vector<int *> leftArray = vector<int *>();
//            vector<int *> rightArray = vector<int *>();
//            for (int i = 0; i < NUM_POINTS; i++) {
//                if (dataPoints[i][largestRangeIndex] < median) {
//                    leftArray.push_back(dataPoints[i]);
//                } else if (dataPoints[i][largestRangeIndex] > median) {
//                    rightArray.push_back(dataPoints[i]);
//                } else {
//                    rightArray.push_back(dataPoints[i]);
//                }
//            }
//            for (int *point : leftArray) {
//                for (int i = 0; i < NUM_DIMENSIONS; i++) {
//                    printf(", %d", point[i]);
//                }
//
//            }
//
//
//
//
////            findMedian(dataPoints, NUM_POINTS);
//
//
//
//
//
//
//
//
//
//            for (int i = 0; i < NUM_POINTS; i++) {
//                delete[] dataPoints[i];
//            }
//            delete[] dataPoints;
        } else {
            printf("all program paramters must be positive\n");
        }
    }
    return 0;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(int arr[], int low, int high, int pivot) {
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j < high; j++) {
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
