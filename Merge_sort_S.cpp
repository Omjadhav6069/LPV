#include <limits.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void s_avg(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    cout << sum / n;
}

void p_avg(int arr[], int n) {
    long long sum = 0;
#pragma omp parallel for reduction(+ : sum) num_threads(16)
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    cout << sum / n;
}

void s_sum(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    cout << sum;
}

void p_sum(int arr[], int n) {
    long long sum = 0;
#pragma omp parallel for reduction(+ : sum) num_threads(16)
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    cout << sum;
}

void s_max(int arr[], int n) {
    int max_val = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    cout << max_val;
}

void p_max(int arr[], int n) {
    int max_val = INT_MIN;
#pragma omp parallel for reduction(max : max_val) num_threads(16)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    cout << max_val;
}

void s_min(int arr[], int n) {
    int min_val = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    cout << min_val;
}

void p_min(int arr[], int n) {
    int min_val = INT_MAX;
#pragma omp parallel for reduction(min : min_val) num_threads(16)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    cout << min_val;
}

void bench_traverse(void (*traverse_fn)(int*, int), int *a, int n) {
    clock_t start, end;
    start = clock();
    traverse_fn(a, n);
    cout << " (";
    end = clock();
    cout << (end - start) * 1000 / CLOCKS_PER_SEC << "ms)";
}

int main() {
    int n, rand_max;
    cout << "Enter array length: ";
    cin >> n;
    cout << "Enter maximum random value: ";
    cin >> rand_max;

    int *a = new int[n];

    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % rand_max;
    }

    cout << "\nGenerated random array of length " << n << " with elements between 0 to " << rand_max << "\n\n";

    cout << "\n\n";

    omp_set_num_threads(16);

    cout << "Sequential Min: ";
    bench_traverse(s_min, a, n);
    cout << "\n";

    cout << "Parallel (16) Min: ";
    bench_traverse(p_min, a, n);
    cout << "\n\n";

    cout << "Sequential Max: ";
    bench_traverse(s_max, a, n);
    cout << "\n";

    cout << "Parallel (16) Max: ";
    bench_traverse(p_max, a, n);
    cout << "\n\n";

    cout << "Sequential Sum: ";
    bench_traverse(s_sum, a, n);
    cout << "\n";

    cout << "Parallel (16) Sum: ";
    bench_traverse(p_sum, a, n);
    cout << "\n\n";

    cout << "Sequential Average: ";
    bench_traverse(s_avg, a, n);
    cout << "\n";

    cout << "Parallel (16) Average: ";
    bench_traverse(p_avg, a, n);
    cout << "\n";

    delete[] a;
    return 0;
}

