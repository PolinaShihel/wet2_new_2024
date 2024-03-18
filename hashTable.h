#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "AVL_tree.h"
#include <math.h>
#include <iostream>

using namespace std;

int const INITIAL_SIZE = 1;
double const MAX_LOAD_COUNT = 1;
double const BETA = (sqrt(5) - 1) / 2;

template<class T, class Cond>
class hashTable {
private:
    int size;
    int elementsCount;
    int getHashCode(Cond key);
    double getLoadFactor() const;
    void relocateMembersImpl(Node<T, Cond> *currentNode, AVLTree<T, Cond> *arr);
    void rehash();
public:
    AVLTree<T, Cond>* members;
    hashTable() : members(new AVLTree<T, Cond>[INITIAL_SIZE]()), size(INITIAL_SIZE), elementsCount(0) {}
    ~hashTable();
    int getSize();
    T* find(Cond key);
    void insert( Cond key, T& element);
    void remove( Cond key);

    //void print_hash();
};

template<class T, class Cond>
int hashTable<T, Cond>::getSize() {
    return this->size;
}

template<class T, class Cond>
hashTable<T,Cond>::~hashTable()
{

    delete[] members;
}

template<class T, class Cond>
int hashTable<T, Cond>::getHashCode(Cond key) {
    double integer;
    return (int)floor(size * modf(BETA * key, &integer));
}

template<class T, class Cond>
double hashTable<T, Cond>::getLoadFactor() const {
    return ( elementsCount / size );
}

template<class T, class Cond>
void hashTable<T, Cond>::rehash() {
    AVLTree<T, Cond> *tmp;
    if(getLoadFactor() >= MAX_LOAD_COUNT) {
        size *= 2;
        tmp = new AVLTree<T, Cond>[size];

        for (int i = 0; i < size / 2; ++i) {
            relocateMembersImpl(members[i].getRoot(), tmp);
        }
    } else {
        size = size / 2;
        tmp = new AVLTree<T, Cond>[size];

        for (int i = 0; i < size*2 ; ++i) {
            relocateMembersImpl(members[i].getRoot(), tmp);
        }
    }
        delete[] members;
        members = tmp;

}

template<class T, class Cond>
void hashTable<T, Cond>::relocateMembersImpl(Node<T, Cond> *currentNode, AVLTree<T, Cond> *arr) {
    if(currentNode != nullptr) {
        arr[getHashCode(currentNode->getKey())].insert(currentNode->getKey(), currentNode->getNodeData());
        relocateMembersImpl(currentNode->getRight(), arr);
        relocateMembersImpl(currentNode->getLeft(), arr);
    }
}

template<class T, class Cond>
T *hashTable<T, Cond>::find(Cond key) {
    return members[getHashCode(key)].find(key);
}

template<class T, class Cond>
void hashTable<T, Cond>::insert( Cond key,  T& element) {
    if(getLoadFactor() >= MAX_LOAD_COUNT){
        rehash();
    }
    int hashCode = getHashCode(key);

    members[hashCode].insert(key, element);
    elementsCount++;
}

template<class T, class Cond>
void hashTable<T, Cond>::remove( Cond key) {
    if(getLoadFactor() <= MAX_LOAD_COUNT/2){
        rehash();
    }
    int hashCode = getHashCode(key);
    members[hashCode].remove(key);
    elementsCount--;
}
/*
template<class T,class Cond>
void hashTable<T,Cond>::print_hash() {
    int i =0;
    cout << "Size of the tree array: " << this->size << endl;
    cout << "number of elements:" << this->elementsCount <<endl;

    for(i=0; i< size ; i++)
    {
        cout << "in members["<< i <<"]:" ;
        members[i].printInOrderTrees(members[i].getRoot());
        cout << endl;
    }
}*/

#endif //WET2_HASHTABLE_H
