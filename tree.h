#ifndef LAB3_TREE_H
#define LAB3_TREE_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

template<typename T>
class Node {
public:
    T Value;
    Node<T>* Left;
    Node<T>* Right;
    //Node<T>* Parent;

    Node() {
        Value = 0;
        Left = 0;
        Right = 0;
    }

    Node(T key) {
        Value = key;
        Left = 0;
        Right = 0;
    }

    Node<T>* add(Node<T>* node, T key){
        if (!node) {
            node = new Node<T>;
            node->Value = key;
            node->Left = 0;
            node->Right = 0;
            return node;
        } else {
            if (key < Value) {
                node->Left = add(node->Left, key);
            }
            else {
                node->Right = add(node->Right, key);
            }
        }
    }

    Node<T>* remote(Node<T>* node, T key){
        if (!node) {throw out_of_range("Not this key!");}
        if (key == node->Value) {
            Node<T>* tempBranch = 0;
            if (!node->Right) {
                tempBranch = node->Left;
            }
            else {
                Node* ptr = node->Right;
                if (!ptr->Left) {
                    ptr->Left = node->Left;
                    tempBranch = ptr;
                }
                else {

                    Node* free_left = ptr->Left;
                    while (free_left->Left) {
                        ptr = free_left;
                        free_left = ptr->Left;
                    }
                    ptr->Left = free_left->Right;
                    free_left->Left = node->Left;
                    free_left->Right = node->Right;
                    tempBranch = free_left;
                }
            }

            delete node;
            node = tempBranch;
            return node;
        } else if (key < node->Value) {node->Left = node->remote(node->Left, key);} else {node->Right = node->remote(node->Right, key);}
    }

    Node<T>* find(T key){
        if (!this) {return NULL;}
        else {
            if (key == Value) {
                return this;
            }
            else if (key < Value)
                Left->find(key);
            else
                Right->find(key);
        }
    }

    Node<T>* map(T (*func)(T), Node<T>* node) {
        if (!node) {return NULL;}
        else {
            node->Value = func(Value);
            node->Left = node->map(func, node->Left);
            node->Right = node->map(func, node->Right);
        }
    }

    void where(bool (*func)(T), Node<T>* node) {
        if (!func(node->Value)) {
            node = node->remote(node, node->Value);
            if (!node) return;
            where(func, node);
            return;
        }

        if (!(node->Left) && !(node->Right)) {
            return;
        }
        if (node->Left) {
            where(func, node->Left);
        }
        if (node->Right) {
            where(func, node->Right);
        }
//        if (!this) {node = 0; return;}
//        else {
//            if (func(Value)) {
//                node->add(node, Value);
//                Left->where(func, node->Left);
//                Right->where(func, node->Right);
//            } else {
//                Left->where(func, node);
//                Right->where(func, node);
//            }
//        }
    }

//    void toList(list<Node<T>*>* result,  Node<T>* node) {
//        if (!node) {return;}
//        if (node->Left) {node->toList(result,node->Left);}
//        result->push_back(node->Value);
//        if (node->Right) {node->toList(result,node->Right);}
//    }

    string toStr(string result) {
        if (Left) {result+=Left->toStr(result);}
        if (Right) {result+=Right->toStr(result);}
        result += to_string(Value);
        return result;
    }

    void copy(const Node<T>* from_tree, Node<T>*& to_tree) {
        if (!from_tree) return;
        to_tree = new Node<T>;
        to_tree->Value = from_tree->Value;
        to_tree->Left = 0;
        to_tree->Right = 0;
        if (from_tree->Left) {copy(from_tree->Left, to_tree->Left);}
        if (from_tree->Right) {copy(from_tree->Right, to_tree->Right);}
    }

    bool Same(Node<T>* root1) {
        /* base cases */
        if (root1 == NULL && this == NULL)
            return true;

        if (root1 != NULL && this != NULL) {
            if (root1->Value == Value && Left->Same(root1->Left) && Right->Same(root1->Right)) {
                return true;
            }

        }
        return false;
    }

    int height()
    {
        if (this == NULL)
            return 0;
        return 1 + max(Left->height(), Right->height());
    }

    void concat(Node<T>* node) {
        if (!node) {return;}
        Left->concat(node->Left);
        this->add(this, node->Value);
        Right->concat(node->Right);
    }


};


template<typename T>
class BinTree {
private:
    Node<T>* root;
public:
    BinTree() {root = 0;}

    void Add(T key) {
        root = root->add(GetRoot(), key);
    }

    void Remove(T key) {
        if (!root) {throw out_of_range("Tree is empty!");}
        root = root->remote(root, key);
    }

    bool Find(T key){
        if(root->find(key)) {return true;} else {return false;}
    }

    void Map(T (*func)(T)){
        root->map(func, root);
    }

    void Where(bool (*func)(T)) {
        root->where(func, root);
    }

//    T Reduce(T (*func)(T, T), T c) {
//        if (!root) {throw out_of_range("Tree is empty!");}
//        T result;
//        list<T>* result_list;
//        root->toList(result_list);
//        result = func(result_list->front(), c);
//        result_list->pop_front();
//        while (result_list->size() > 0) {
//            result = func(result, result_list->front());
//            result_list->pop_front();
//        }
//        delete result_list;
//        return result;
//    }

//    T Reduce(T (*func)(T, T),  T start) {
//        if (!root) {
//            return 0;
//        }
//        list<Node<T>*>* list=this->Threading();
//        T result;
//        auto list_front = list->begin();
//        result = func(list_front->Value, start);
//        advance(list_front,1);
//        for (size_t i = 1; i < list->size(); i++) {
//            result = func(list_front->Value, result);
//            advance(list_front, 1);
//        }
//        return result;
//    }
//
//    list<Node<T>*> *Threading(string method) {
//        list<Node<T>*> *list =new ::list<Node<T>*>;
//        if (!root) {
//            return list;
//        }
//        tothread(root, list, method);
//        return list;
//    }

    string toString() {
        if (!root) {throw out_of_range("Tree is empty!");}
        string tree;
        tree = root->toStr(tree);
        return tree;
    }

    BinTree<T> GetSubTree(T key) {
        BinTree<T> result = BinTree<T>();
        if (!root) {
            return result;
        }
        result.root = root->find(key);
//        copy(root->find(key), result.root);
        return result;
    }

    bool FindSubTree(BinTree<T> sub_tree) {
        if (!sub_tree.root) {return true;}
        if (!root) {return false;}
        if (this->Find(sub_tree.root->Value)) {
            if (root->find(sub_tree.root->Value)->Same(sub_tree.root)) {return true;} else {return false;}
        } else {return false;}
    }

    Node<T>* GetRoot() {return root;}

    void Print() {
        if (!root) {cout << "tree is empty" << endl;}
        else {
            cout << root->Value << endl;
            int len = 2;
            list<Node<T>*> nodes;
            nodes.push_back(root->Left);
            nodes.push_back(root->Right);
            for (int h = root->height(); h > 0; h--) {
                for (int i = len; i < 0; i-=2) {
                    cout << "l " << (nodes.front())->Value;
                    nodes.push_back((nodes.front())->Left);
                    nodes.push_back((nodes.front())->Right);
                    nodes.pop_front();
                    cout << " r " << (nodes.front())->Value;
                    nodes.push_back((nodes.front())->Left);
                    nodes.push_back((nodes.front())->Right);
                    nodes.pop_front();
                }
                len+=2;
            }
        }
    }

    void readString(string tree) {
        int i = 0;
        while (tree.find(' ')) {
            string n = " ";
            while (tree[i] != ' ') {
                n+= tree[i];
                i++;
            }
            this->Add(root, (T)n);
            i++;
        }
        string n = " ";
        while (tree[i]) {
            n+= tree[i];
            i++;
        }
        this->Add((T)n);
   }

    void Concat(BinTree<T> A) {
        root->concat(A.root);
    }



};

#endif //LAB3_TREE_H
