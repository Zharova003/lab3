#ifndef LAB3_QUEUE_H
#define LAB3_QUEUE_H

#include "heap.h"

template<typename T>
class Queue{
private:
    Heap<T> queue;
public:
    Queue() {
        queue = Heap<T>();
    }

    Queue(T* d, int *n, int len) {
        queue = Heap<T>(d, n, len);
    }

    int Size() {
        return queue.getSize();
    }

    void Add(T x, int y) {
        queue.Add(x, y);
    }

    void Pop() {
        int x = queue.FindMin()->key;
        queue.Remotek(x);
    }

    T Find(int x) {
        if (queue.Findk(x)) {
            return queue.Findk(x)->data;
        } else {return 0;}
    }

    int FindPriority(T x) {
        if (queue.Find(x)) {
            return queue.Find(x)->key;
        } else {return 0;}
    }

    Queue<T> subQueue(int start, int finish) {
        Queue<T> result = Queue<T>();
        result.queue = queue.subHeap(start, finish);
        return result;
    }

    bool findSUbQueue(Queue<T> A) {
        return queue.findSubTree(A.queue);
    }

    void Map(T (*func)(T)) {
        queue.Map(func);
    }

    T Reduce(T (*func)(T, T), T c) {
        return queue.Reduce(func, c);
    }

    Queue<T> Where(bool (*func)(T)) {
        Queue<T> result = Queue<T>();
        result.queue = queue.where(func);
        return result;
    }



};

#endif //LAB3_QUEUE_H
