#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace chrono;

// Сортировка выбором
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

// Разделение массива
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
        int p = partition(arr, low, high);
        quickSortHelper(arr, low, p - 1);
        quickSortHelper(arr, p + 1, high);
    }
}

// Быстрая сортировка
void quickSort(vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}

// Замер времени
double timeSort(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count() / 1000.0;
}

void run(int size) {
    vector<int> a(size), b(size);

    // случайный массив
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 10000;
        b[i] = a[i];
    }

    // полностью отсортированный массив
    /*
    for (int i = 0; i < size; ++i) {
        a[i] = i;
        b[i] = i;
    }
    */

    // неотсортированный массив
    /*
    for (int i = 0; i < size; ++i) {
        a[i] = size - i;
        b[i] = size - i;
    }
    */

    // частично отсортированный массив (50%)
    /*
    for (int i = 0; i < size; ++i) {
        a[i] = i;
        b[i] = i;
    }
    for (int i = 0; i < size / 2; ++i) {
        int x = rand() % size;
        int y = rand() % size;
        swap(a[x], a[y]);
        swap(b[x], b[y]);
    }
    */

    double tSel = timeSort(selectionSort, a);
    double tQuick = timeSort(quickSort, b);

    cout << setw(19) << tSel
        << "    " << setw(15) << tQuick << endl;
}

int main() {
    srand(time(nullptr));

    int sizes[] = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

    cout << fixed << setprecision(3);
    cout << "Selection Sort (ms)    Quicksort (ms)" << endl;
    cout << "-------------------    ---------------" << endl;

    for (int n : sizes) {
        run(n);
    }

    return 0;
}
