#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void s_bubble(int *, int);
void p_bubble(int *, int);
void swap(int &, int &);

void s_bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void p_bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
#pragma omp parallel for shared(a, first) num_threads(16)
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int n, rand_max;
    cout << "Enter array length: ";
    cin >> n;
    cout << "Enter maximum random value: ";
    cin >> rand_max;

    int *a = new int[n];
    int *b = new int[n];

    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < n; i++) {
        a[i] = rand() % rand_max;
    }
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }

    cout << "Generated random array of length " << n << " with elements between 0 to " << rand_max << "\n\n";

    clock_t start, end;

    start = clock();
    s_bubble(a, n);
    end = clock();
    cout << "Sequential Bubble sort: " << (end - start) * 1000 / CLOCKS_PER_SEC << " ms\n";

    omp_set_num_threads(16);

    start = clock();
    p_bubble(b, n);
    end = clock();
    cout << "Parallel (16) Bubble sort: " << (end - start) * 1000 / CLOCKS_PER_SEC << " ms\n";

    delete[] a;
    delete[] b;
    return 0;
}

