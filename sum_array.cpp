#include <iostream>
#include <thread>
#include <chrono>

const int N = 100000000;        //размер массива                
const int M = 10;               //количество потоков
int result = 0;                 //сумма элементов массива
int* array = new int[N] {};     //массив значений

// функция сложения элементов массива
void sumArray(int start, int stop)
{
    int res = 0;
    for (auto i = start; i < stop; ++i)
        res += array[i];
    result += res;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    for (auto i = 0; i < N; ++i)
        array[i] = rand() % N;
    auto timeGo = std::chrono::system_clock::now();
    for (auto i = 0; i < M; ++i)
        sumArray(N / M * i, N / M * (i + 1));
    auto timeFinal = std::chrono::system_clock::now();
    auto timeUsed = std::chrono::duration_cast<std::chrono::milliseconds>
        (timeFinal - timeGo).count();
    std::cout << "Сумма всех элементов массива равна " << result << ", вычислена"
        " без использования потоков за " << timeUsed << " мс." << std::endl;
    timeGo = std::chrono::system_clock::now();
    result = 0;
    std::thread* threads = new std::thread[M]{};
    for (auto i = 0; i < M; ++i)
        threads[i] = std::thread(sumArray, N / M * i, N / M * (i + 1));
    for (auto i = 0; i < M; ++i)
        if (threads[i].joinable())
            threads[i].join();
    timeFinal = std::chrono::system_clock::now();
    timeUsed = std::chrono::duration_cast<std::chrono::milliseconds>
        (timeFinal - timeGo).count();
    std::cout << "Сумма всех элементов массива равна " << result << ", вычислена"
        " с использованием " << M << " потоков за " << timeUsed << " мс." << std::endl;
    std::cout << "Количество ядер процессора - 3" << std::endl;
    delete[]array;
    delete[]threads;
    return 0;
}
