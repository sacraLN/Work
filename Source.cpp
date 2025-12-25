#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <algorithm>
using namespace std;
using namespace chrono;

//СОРТИРОВКА ВЫБОРОМ
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

//БЫСТРАЯ СОРТИРОВКА 
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}

//ВРЕМЯ
double measureTime(void(*sortFunc)(vector<int>&), vector<int> data) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count() / 1000.0;
}

int main() {
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dis(1, 10000);

    vector<int> sizes = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

    cout << fixed << setprecision(3);

    cout << "Selection Sort (ms)    Quicksort (ms)\n";
    cout << "-------------------    ---------------\n";

    for (int size : sizes) {
        vector<int> data1(size);
        vector<int> data2(size);

        //Случайный массив
        for (int i = 0; i < size; ++i) {
            data1[i] = dis(gen);
            data2[i] = dis(gen);
        }

        //Полностью отсортированный массив
        // for (int i = 0; i < size; ++i) {
        //     data1[i] = i;
        //     data2[i] = i;
        // }

        //Неотсортированный массив 
        // for (int i = 0; i < size; ++i) {
        //     data1[i] = size - i;
        //     data2[i] = size - i;
        // }

        //Частично отсортированный массив
        // for (int i = 0; i < size; ++i) {
        //     data1[i] = i;
        //     data2[i] = i;
        // }
        // for (int i = 0; i < size / 2; ++i) {
        //     int idx1 = dis(gen) % size;
        //     int idx2 = dis(gen) % size;
        //     swap(data1[idx1], data1[idx2]);
        //     swap(data2[idx1], data2[idx2]);
        // }

        double time1 = measureTime(selectionSort, data1);
        double time2 = measureTime(quickSort, data2);

        cout << setw(19) << time1 << "    " << setw(15) << time2 << "\n";
    }

    return 0;
}