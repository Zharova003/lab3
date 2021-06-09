#include <gtest/gtest.h>
#include "tree.h"
#include "queue.h"

using namespace std;
int n[] = {1, 2, 3, 4, 5};
int n1[] = {6, 7, 8, 9, 10};

bool wherefunc (int x) {
    return x > 1;
}

int reduce(int x, int y) {
    return x+y;
}

int mup(int x) {
    return x+3;
}


TEST(tree, constructor1) {
    BinTree<int> A = BinTree<int>();
    EXPECT_EQ(!(A.GetRoot()), true);
}

TEST(tree, add) {
    BinTree<int> A = BinTree<int>();
    A.Add(1);
    EXPECT_EQ(!(A.GetRoot()), false);
    EXPECT_EQ(A.GetRoot()->Value, 1);
    A.Add(2);
    EXPECT_EQ(A.GetRoot()->Right->Value, 2);
}

TEST(tree, remote) {
    BinTree<int> A = BinTree<int>();
    EXPECT_THROW(A.Remove(1), out_of_range);
    A.Add(1);
    A.Add(2);
    A.Add(3);
    A.Remove(2);
    EXPECT_EQ(A.GetRoot()->Right->Value, 3);
    EXPECT_THROW(A.Remove(2), out_of_range);
}

TEST(tree, find) {
    BinTree<int> A = BinTree<int>();
    EXPECT_EQ(A.Find(1), false);
    A.Add(1);
    EXPECT_EQ(A.Find(1), true);
}

TEST(tree, where) {
    BinTree<int> A = BinTree<int>();
    A.Add(2);
    A.Add(3);
    A.Add(1);
    A.Where(wherefunc);
    EXPECT_EQ(!(A.GetRoot()), false);
    EXPECT_EQ(A.GetRoot()->Value, 2);
    EXPECT_EQ(A.GetRoot()->Right->Value, 3);
}

TEST(tree, map) {
    BinTree<int> A = BinTree<int>();
    A.Add(2);
    A.Add(3);
    A.Add(1);
    A.Map(mup);
    EXPECT_EQ(!(A.GetRoot()), false);
    EXPECT_EQ(A.GetRoot()->Value, 5);
}

TEST(tree, tostr) {
    BinTree<int> A = BinTree<int>();
    A.Add(1);
//    A.Add(1);
    A.Add(2);
    A.Add(3);
    string a = A.toString();
    EXPECT_EQ(a, "321");
//    (node, toList)
//    BinTree<int> A = BinTree<int>();
//    A.Add(2);
//    A.Add(3);
//    A.Add(1);
//
//    list<Node<int>*> *result_list = nullptr;
//    A.GetRoot()->toList(result_list, A.GetRoot());
//    EXPECT_EQ(result_list->front(), 1);
}

TEST(tree, sub_tree) {
//    BinTree<int> A = BinTree<int>();
//    A.readString("1 2 3 ");
//    EXPECT_EQ(!(A.GetRoot()), false);
    BinTree<int> A = BinTree<int>();
    A.Add(2);
    A.Add(3);
    A.Add(1);
    BinTree<int> B = A.GetSubTree(3);
    EXPECT_EQ(!(B.GetRoot()), false);
    EXPECT_EQ(B.GetRoot()->Value, 3);

}

TEST(tree, findSubTree) {
    BinTree<int> A = BinTree<int>();
    A.Add(2);
    A.Add(3);
    A.Add(1);
    BinTree<int> B = BinTree<int>();
    B.Add(1);
    EXPECT_EQ(A.FindSubTree(B), true);
}

TEST(heap, conctructor1) {
    Heap<int> A = Heap<int>();
    EXPECT_EQ(A.getSize(), 0);
}

TEST(heap, constructor2) {
    Heap<int> A = Heap<int>(3);
    EXPECT_EQ(A.getSize(), 3);
}

TEST(heap, constructor3) {
    Heap<int> A = Heap<int>(n, 5);
    EXPECT_EQ(A.getSize(), 5);
}
TEST(heap, add) {
    Heap<int> A = Heap<int>();
    A.Add(1);
    EXPECT_EQ(A.getSize(), 1);
}
TEST(heap, find) {
    Heap<int> A = Heap<int>();
    EXPECT_EQ(!(A.Find(1)), true);
    A.Add(1);
    Item<int>* x = A.Find(1);
    EXPECT_EQ(x->data, 1);
}
TEST(heap, remote) {
    Heap<int> A = Heap<int>();
    EXPECT_THROW(A.Remote(1), out_of_range);
    A.Add(1);
    A.Add(2);
    EXPECT_EQ(A.getSize(), 2);
    A.Remote(1);
    EXPECT_EQ(!(A.Find(1)), true);
    int b = A.getSize();
    EXPECT_EQ(A.getSize(), b);
    Item<int>* x = A.Find(2);
    EXPECT_EQ(x->data, 2);
}
TEST(heap, subtree) {
    Heap<int> A = Heap<int>();
    A.Add(1);
    A.Add(2);
    Heap<int> B = A.Subtree(1);
    int b = B.getSize();
    EXPECT_EQ(B.getSize(), b);
}
TEST(heap, findSubTree) {
    Heap<int> A = Heap<int>();
    A.Add(2);
    Heap<int> B = Heap<int>();
    B.Add(2);
    EXPECT_EQ(A.findSubTree(B), true);
}
TEST(heap, toString) {
    Heap<int> A = Heap<int>();
    A.Add(1);
    EXPECT_EQ(A.toString(), "1 ");
}
TEST(heap, readString) {
    Heap<int> A = Heap<int>();
    A.fromString("123");
    EXPECT_EQ(A.getSize(), 3);
}
TEST(queue, constructor1) {
    Queue<int> A = Queue<int>();
    EXPECT_EQ(A.Size(), 0);
}
TEST(queue, constructor2) {
    Queue<int> A = Queue<int>(n, n1, 5);
    EXPECT_EQ(A.Size(), 5);
}
TEST(queue, add) {
    Queue<int> A = Queue<int>();
    A.Add(1, 1);
    EXPECT_EQ(A.Size(), 1);
}
TEST(queue, pop) {
    Queue<int> A = Queue<int>();
    A.Add(1, 1);
    A.Pop();
    EXPECT_EQ(A.Size(), 0);
}
//TEST(queue, subQ) {
//    Queue<int> A = Queue<int>();
//    A.Add(1, 1);
//    A.Add(2, 2);
//    Queue<int> B = A.subQueue(0, 1);
//    EXPECT_EQ(B.Size(), 1);
//}
TEST(queue, findSubQ) {
    Queue<int> A = Queue<int>();
    A.Add(1, 1);
    Queue<int> B = Queue<int>();
    EXPECT_EQ(A.findSUbQueue(B), true);
}
TEST(queue, map) {
    Queue<int> A = Queue<int>();
    A.Add(1, 1);
    A.Map(mup);
    EXPECT_EQ(A.FindPriority(4), 1);
}
TEST(queue, reduce) {
    Queue<int> A = Queue<int>();
    A.Add(1, 1);
    EXPECT_EQ(A.Reduce(reduce, 1), 2);
}
TEST(queue, where) {
    Queue<int> A = Queue<int>();
    A.Add(1, 1);
    A.Add(2, 2);
    Queue<int> B = A.Where(wherefunc);
    EXPECT_EQ(B.Size(), 1);
}
//TEST(t, t) {
//
//}