#include <time.h>


class Sorts{
private:
    void Faz(int arr[], int n, int i);
    void HeapSort(int *A, int n);
    void ShellSort(int* v, int n);
    void Troca(int* a, int* b);
public:
    Sorts();
    ~Sorts();
    double getTimeHeap(int *A, int n);
    double getTimeShell(int* v, int n);
};
