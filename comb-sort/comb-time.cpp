#include <iostream>
#include <chrono>
#include <random>


int* generator(int N) {
    int* arr = new int[N];
    for (int i {0}; i < N; i++)
        arr[i] = i;

    return arr;
}


int random(int N) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, N-1);

    return dist(rng);
}


int* rand_gen(int N) {
    int* arr = new int[N];
    for (int i = 0; i < N; i++) {
        int x = random(N);
        arr[i] = x;
    }

    return arr;
}


void step(int arr[], int N, int step) {
    for (int i = 0; i < N - step + 1; i++) {
        if (arr[i] > arr[i + step]) {
            std::swap(arr[i], arr[i + step]);
        }
    }
}


void comb_sort(int arr[], int N) {
    int i = N/2;
    while (i > 1) {
        step(arr, N, i);
        i = i/2;
    }

    bool sorted = false;
    while (sorted == false) {
        for (int i = 0; i < N; i++) {
            if (arr[i] > arr[i+1]) {
                sorted = false;
                step(arr, N, 1);
                break;
            }
            else {
                sorted = true;
            }
        }
    }
}


int main() {
    for (int N = 5; N < 2000; N += 5) {
        auto begin = std::chrono::steady_clock::now();
        for (int j = 0; j < 50; j++) {
            int* arr = rand_gen(N); 
            comb_sort(arr, N);
            delete arr;
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span =
        std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin)/50);
        std::cout << time_span.count() << std::endl;
    }

    return 0;
}


/*  
std::cout << "Array before/after sorting:" << std::endl;
for (int i = 0; i < N; i++) {
    std::cout << arr[i] << " ";
}
std::cout << std::endl;


*/