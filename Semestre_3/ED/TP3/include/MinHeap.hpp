#include <iostream>

using namespace std;


template <class T>
class MinHeap {
    private:
        T* v;
        int maxSize = 1000000;
        int size = 0;

        void Troca(T* a, T* b){
            T aux = *a;
            *a = *b;
            *b = aux;
        };
        
        void Heapify(T* v, int t, int i){
            int menor = i;
            int esq = i*2 + 1;
            int dir = i*2 + 2;
            
            if(esq < t and v[menor] > v[esq])
                menor = esq;
            if(dir < t and v[menor] > v[dir])
                menor = dir;
            if(menor != i){
                Troca(&v[i],&v[menor]);
                Heapify(v, t, menor);
            }
        }
        
        int Parent(int i){
            return (i-1)/2;
        }

        void IncreaseKey(T* v, int i, T key){
            v[i] = key;
            while(i > 0 and i < size and v[Parent(i)] > v[i]){
                Troca(&v[i], &v[Parent(i)]);
                i = Parent(i);
            }
        }

        void Build(T* v, int t){
            for(int i = t/2 - 1; i >= 0; i--)
                Heapify(v, t, i);
        }

    public:
        MinHeap(T* v, int t){
            if(t > maxSize) throw "Tamanho do vetor excede o limite";
            
            this->v = new T[maxSize];
            for (int i = 0; i < t; i++)
                this->v[i] = v[i];
            Build(this->v, t);
            size = t;
        };

        T ExtractMin(){
            if(size <= 0) throw "Heap underflow";
            T min = v[0];
            v[0] = v[--size];
            Heapify(v, size, 0);
            return min;
        }
        
        
        void Insert(T key){
            if (size == maxSize) throw "Heap overflow";
            IncreaseKey(v,size,key);
            size++;
        }
        void print(){
            for(int i = 0; i < size; i++)
                cout << v[i] << " ";
            cout << endl;
        }
        int getSize(){return size;}
        ~MinHeap(){delete[] v;}
};
