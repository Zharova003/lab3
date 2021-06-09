#ifndef LAB3_HEAP_H
#define LAB3_HEAP_H

#include <iostream>
#include <string>
#include<stdio.h>
using namespace std;

template<typename T>
class Item {
public:
    int key;
    T data;
};

template<typename T>
class Heap {
private:
    Item<T>* items;
    size_t size;

    void checkupd(int c) {
        int p;
        p = c / 2;
        if( p == 0 )return;
        if(items[p].data > items[c].data) {
            Item<T> tmp;
            tmp = items[p]; items[p] = items[c]; items[c] = tmp;
            checkupd(p);
        }
    }

    void checkupk(int c) {
        int p;
        p = c / 2;
        if( p == 0 )return;
        if(items[p].key > items[c].key) {
            Item<T> tmp;
            tmp = items[p]; items[p] = items[c]; items[c] = tmp;
            checkupk(p);
        }
    }

    int index(T x) {
        for (int i = 0; i < size; i++) {
            if (x == items[i].data) {return i;}
        }
        return NULL;
    }

    int indexk(int x) {
        for (int i = 0; i < size; i++) {
            if (x == items[i].key) {return i;}
        }
        return NULL;
    }
public:
    Heap() {
        size = 0;
        items = 0;
    }

    Heap(int n) {
        size = n;
        items = (Item<T>*) malloc(sizeof(Item<T>*) * n);
    }

    int getSize(){
        return size;
    }

    Heap(int* n, T* d, int len) {
        size = len;
        items = (Item<T>*) malloc(sizeof(Item<T>*) * size);
        for (int i = 0; i < size; i++) {
            items[i].key = n[i];
            items[i].data = d[i];
            checkupk(i);
        }
    }

    Heap(T* d, int len) {
        size = len;
        items = (Item<T>*) malloc(sizeof(Item<T>*) * size);
        for (int i = 0; i < len; i++) {
            items[i].key = 0;
            items[i].data = d[i];
            checkupd(i);
        }

    }

    ~Heap() {
        if(items) free(items);
    }

    int Add(T x, int y) {
        size++;
        items = (Item<T>*)realloc(items, size);
        items[size-1].key = y;
        items[size-1].data = x;
        checkupd(size-1);
        return 1;
    }

    int Add(T x) {
        size++;
        items = (Item<T>*)realloc(items, size);
        items[size-1].key = 0;
        items[size-1].data = x;
        checkupd(size-1);
        return 1;
    }

    Item<T>* Find(T x) {
        for (int i = 0; i < size; i++) {
            if (x == items[i].data) {return &items[i];}
        }
        return NULL;
    }

    Item<T>* Findk(int x) {
        for (int i = 0; i < size; i++) {
            if (x == items[i].key) {return &items[i];}
        }
        return NULL;
    }

    Item<T>* FindMin() {
        int y = items[0].key, j = 0;
        for (int i = 0; i < size; i++) {
            if (items[i].key < y) {j = i;}
        }
        return &items[j];
    }

    void Remote(T x) {
        if (!items) {throw out_of_range("heap is empty");}
        if (Find(x)) {
            size -= 1;
            Item<T>* newItems = new Item<T>[size];
            int i = 0;
            while ((items[i].data != x) && (i < size)) {
                newItems[i] = items[i];
                i++;
            }
            while (i<size) {
                newItems[i] = items[i+1];
                i++;
            }
            delete []items;
            items = newItems;
        }
    }

    void Remotek(int x) {
        if (!items) {throw out_of_range("heap is empty");}
        if (Findk(x)) {
            Item<T>* newItems = new Item<T>[size-1];
            int i = 0;
            while ((items[i].key != x) && (i < size-1)) {
                newItems[i] = items[i];
                i++;
            }
            while (i+1<size) {
                newItems[i] = items[i+1];
                i++;
            }
            delete []items;
            items = newItems;
            size--;
        }
    }

    int subtree(int index, int newIndex, Item<T>* newItem) {
        if (index < size) {
            newItem[newIndex] = items[index];
            newIndex++;
            newIndex += subtree(2*index+1, newIndex, newItem);
            newIndex += subtree(2*index+2, newIndex, newItem);
            return newIndex;
        } else {return 0;}
    }

    Heap<T> Subtree(T x) {
        if (Find(x)) {
            Item<T>* newItems = new Item<T>[size];
            int newIndex = subtree(index(x), 0, newItems);
            newItems = (Item<T>*)realloc(newItems, newIndex * sizeof(Item<T>));
            Heap<T> result;
            result.size = newIndex;
            result.items = newItems;
            for (int i = newIndex; i > 0; i--) {
                result.checkupd(i);
            }
            return result;
        }
        return Heap<T>();
    }

    Heap<T> Subtreek(int x) {
        if (Findk(x)) {
            Item<T>* newItems = new Item<T>[size];
            int newIndex = subtree(index(x), 0, newItems);
            newItems = (Item<T>*)realloc(newItems, newIndex * sizeof(Item<T>));
            Heap<T> result;
            result.size = newIndex;
            result.items = newItems;
            for (int i = newIndex; i > 0; i--) {
                result.checkupk(i);
            }
            return result;
        }
        return Heap<T>();
    }

    bool findSubTree(Heap<T> A) {
        for (int i = 0; i < A.size; i++) {
            if (!Find(A.items[i].data) || !Findk(A.items[i].key) || Find(A.items[i].data) != Findk(A.items[i].key) ) {return false;}
        }
        return true;
    }

    string toString() {
        string heap;
        for (int i = 0; i < size; i++) {
            heap+= to_string(items[i].data) + " ";
        }
        return heap;
    }

    void fromString(string heap) {
        size = heap.length();
        items = new Item<T>[size];
        for (int i = 0; i < size; i++) {
            items[i].data = (T)heap[i];
        }
        for (int i = size; i > 0; i--) {
            this->checkupd(i);
        }
    }

    void Map(T (*func)(T)) {
        for (int i = 0; i < size; i++) {
            items[i].data = func(items[i].data);
            this->checkupd(i);
        }
    }

    T Reduce(T (*func)(T, T), T c) {
        T result = func(items[0].data, c);
        for (int i = 1; i < size; i++) {
            result = func(items[i].data, result);
        }
        return result;
    }

    Heap<T> where(bool (*func)(T)) {
        Heap<T> result;
        for (int i = 1; i < size; i++) {
            if (func(items[i].data)) {
                result.Add(items[i].data, items[i].key);
            }
        }
        int f = 0;
        for (int i = result.size; i > 0; i--) {
            if (result.items[i].key != 0) {
                f = 1; break;
            }
        }
        if (!f) {
            for (int i = size; i > 0; i--) {
                result.checkupd(i);
            }
        }
        return result;
    }

    Heap<T> subHeap(int start, int final) {
        if (size == 0) {throw out_of_range("queue is empty");}
        if (start < 0 || final < 0) {throw out_of_range("Index must be >0");}
        if (start > size || final > size) {throw out_of_range("Index out of range");}
        if (final < start) {
            int temp = start; start = final; final = temp;
        }
        Heap<T> result;
        result.size = final-start;
        for (int i = 0; i < result.size; i++)
            result.items[i] = result.items[i+start];
        return result;
    }


};

#endif //LAB3_HEAP_H
