#include <iostream>
#include <chrono>
#include <random>


unsigned* generator(unsigned N) {
    unsigned* arr = new unsigned[N];
    for (unsigned i {0}; i < N; i++)
        arr[i] = i;

    return arr;
}


unsigned random(unsigned N)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<unsigned int> dist(0, N-1);

    return dist(rng);
}


unsigned* rand_gen(unsigned N) {
    unsigned* arr = new unsigned[N];
    for (unsigned i = 0; i < N; i++) {
        int x = random(N);
        arr[i] = x;
    }

    return arr;
}


void forward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned i = begin_idx; i < end_idx; i++) {
        if (arr[i] > arr[i + 1]) {
            std::swap(arr[i], arr[i + 1]);
        }
    }
}


void backward_step(unsigned arr[], unsigned const begin_idx, unsigned const end_idx) {
    for (unsigned i = end_idx; i > begin_idx; i--) {
        if (arr[i] < arr[i - 1]) {
            std::swap(arr[i], arr[i - 1]);
        }
    }
}


void shaker_sort(unsigned arr[], unsigned const begin_idx , unsigned const end_idx) {
    for (unsigned i = begin_idx; i <= end_idx; i++) {
        forward_step(arr, i, end_idx);
        backward_step(arr, begin_idx, end_idx - i);
    }
}


int main() {
    for (unsigned i = 5; i < 2000; i += 5) {
        auto begin = std::chrono::steady_clock::now();
        for (int j = 0; j < 50; j++) {
            unsigned* arr = rand_gen(i); 
            shaker_sort(arr, 0, i-1);
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
for (unsigned i = 0; i < N; i++) {
    std::cout << arr[i] << " ";
}
std::cout << std::endl;


*/