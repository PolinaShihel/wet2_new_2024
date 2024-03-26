#ifndef WET2_RANKNODE_H
#define WET2_RANKNODE_H

#include <iostream>
#include "Node.h"

#define LL 2
#define LR -1
#define RR -2
#define RL 1
#define empty 0
#define null_height -1
#define LEFT 3
#define RIGHT 4

template<class T, class Cond>
class RankNode {
    Cond key;
    RankNode *right;
    RankNode *left;
    int height;
    T data;
    int rank;
    int extra;
    int extraW;
    RankNode *bigExtraW;

public:
    int amount;

    RankNode(Cond key, T data): key(key), right(nullptr),left(nullptr), height(0),
                                data(data), rank(1),extra(0),extraW(key),bigExtraW(this),amount(0){};
    RankNode(Cond key, T data,int rank): key(key), right(nullptr),left(nullptr), height(0),
                                         data(data),rank(rank),extra(0),extraW(key),bigExtraW(this),amount(0){};
    RankNode(Cond key, T data,int rank, int extra): key(key), right(nullptr),left(nullptr), height(0),
                                                    data(data),rank(rank),extra(extra),extraW(key),bigExtraW(this),amount(0){};
    RankNode(Cond key, T data,int rank, int extra, int extraW): key(key), right(nullptr),left(nullptr), height(0),
                                                                data(data),rank(rank),extra(extra),extraW(extraW),amount(0){}; //NOT SURE NEEDED
    RankNode *insertNode(const Cond &key, const T &data, int sum);
    RankNode *deleteNode(const Cond &newKey, int sum);
    RankNode *findNode(const Cond &newKey);
    //Rotations
    RankNode *rotate(int sum);
    RankNode *roll_LL(int sum);
    RankNode *roll_LR(int sum);
    RankNode *roll_RL(int sum);
    RankNode *roll_RR(int sum);
    ~RankNode();
    T getNodeData();
    T *getNodeDataPointer();
    RankNode *getRight();
    RankNode *getLeft();
    void setRight(RankNode *node);
    void setLeft(RankNode *node);
    Cond getKey() const;
    int getHeight() const;  //not sure if needed
    RankNode *findBiggestParent(RankNode *root);
    RankNode *findBiggest();
    RankNode *findSmallest();
    void swap(RankNode *source, RankNode *destination);
    int balanceFactor() const;
    void calcHeight();
    RankNode *isExist(const Cond &newKey);
    void setRank(int rank);
    //int getRank();
    int getWeight();
    void AddExtra(const Cond& end, int toAdd);
    void AddExtraAux(const Cond& end, int toAdd, int prevDirection, int sum);
    void inOrderTraversal(int depth);
    int findSum(const Cond& toFind, int sum);
    T* select(int rank, int sum);
    int Rank(Cond& toFind);
    void addExtraSingle(Cond &end, int toAdd, int sum);
    RankNode<T,Cond>* findClosestSmall(Cond& toFind, RankNode<T,Cond>* current);
    RankNode<T,Cond>* findClosestBig(Cond& toFind, RankNode<T,Cond>* current);
    void findMax(int str, int sum);
    RankNode<T,Cond>* findMaxWins();
    int getMaxRank();
    void setKey(const Cond& newCond);
    int findSumExtras(const Cond &toFind, int sum);
    };

template<class T,class Cond>
void RankNode<T,Cond>::setKey(const Cond &newCond) {
    this->key = newCond;
}

template<class T,class Cond>
int RankNode<T,Cond>::getMaxRank() {
    return this->extraW;
}

template<class T,class Cond>
RankNode<T,Cond>* RankNode<T,Cond>::findMaxWins(){
    return this->bigExtraW;
}
//template<class T,class Cond>
//int RankNode<T,Cond>::findMaxWins(const Cond& toFind, int sum) {
//    if(this== nullptr)
//        throw KeyNotFound();
//    if(this->key < toFind)
//        return this->right->findMaxWins(toFind, sum+this->extra);
//    else if(this->key > toFind)
//        return this->left->findMaxWins(toFind, sum+this->extra);
//    else
//        return this->extraW;
//}

template<class T,class Cond>
RankNode<T,Cond>* RankNode<T,Cond>::findClosestSmall(Cond& toFind, RankNode<T,Cond>* current)
{
    if(this == nullptr && current == nullptr)
        throw KeyNotFound();
    if(this == nullptr)
        return current;
    if(this->key < toFind)
        return this->right->findClosestSmall(toFind, current);
    else
        return this->left->findClosestSmall(toFind, this);
}

template<class T,class Cond>
RankNode<T,Cond>* RankNode<T,Cond>::findClosestBig(Cond& toFind, RankNode<T,Cond>* current)
{
    if(this == nullptr && current == nullptr)
        throw KeyNotFound();
    if(this == nullptr)
        return current;
    if(this->key < toFind)
        return this->right->findClosestBig(toFind, this);
    else
        return this->left->findClosestBig(toFind, current);
}

template<class T,class Cond>
void RankNode<T,Cond>::addExtraSingle(Cond &end, int toAdd, int sum) {
    if(this== nullptr)
        throw KeyNotFound();
    if(this->key < end) {
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
        this->right->addExtraSingle(end, toAdd, this->extra);
    }
    else if(this->key > end) {
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
        this->left->addExtraSingle(end, toAdd, this->extra);
    }
    else{//key found
        this->extra+=toAdd;
        if(this->left!= nullptr)
            this->left->extra-=toAdd;
        if(this->right!= nullptr)
            this->right->extra-=toAdd;

        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
    }
    this->findMax(this->key, this->amount);
}

template<class T,class Cond>
int RankNode<T,Cond>::Rank(Cond &toFind) {
    if(this == nullptr)
        throw KeyNotFound();
    if(this->key < toFind){
        if(this->left!= nullptr)
            return this->left->rank + 1 + this->right->Rank(toFind);
        return 1 + this->right->Rank(toFind);
    }
    else if(this->key > toFind)
        return this->left->Rank(toFind);
    else{
        if(this->left!= nullptr)
            return this->left->rank + 1;
        return 1 ;
    }
}

template<class T,class Cond>
T* RankNode<T,Cond>::select(int rank, int sum)
{
    if(this == nullptr)
        throw KeyNotFound();
    int thisRank = 1 + sum;
    if(this->left != nullptr)
        thisRank+=this->left->rank;
    if(thisRank < rank)
        return this->right->select(rank, thisRank);
    else if (thisRank > rank)
        return this->left->select(rank, sum);
    else
        return this->getNodeDataPointer();
}

template<class T,class Cond>
int RankNode<T,Cond>::findSum(const Cond &toFind, int sum) {
    if(this == nullptr)
        throw KeyNotFound();
    this->amount+= this->extra;
    if(this->right != nullptr)
        this->right->extra += this->extra;
    if(this->left != nullptr)
        this->left->extra += this->extra;
    this->extra = 0;
    if(this->key < toFind)
        return this->right->findSum(toFind, sum);
    else if(this->key > toFind)
        return this->left->findSum(toFind, sum);
    else
        return this->amount;
}

template<class T,class Cond>
int RankNode<T,Cond>::findSumExtras(const Cond &toFind, int sum) {
    if(this == nullptr)
        throw KeyNotFound();
    sum+= this->extra;
    if(this->key < toFind)
        return this->right->findSumExtras(toFind, sum);
    else if(this->key > toFind)
        return this->left->findSumExtras(toFind, sum);
    else
        return sum;
}

template<class T,class Cond>
void RankNode<T,Cond>::inOrderTraversal(int depth) {
    if(this== nullptr)
        return;
    this->left->inOrderTraversal(depth+1);
    std::cout <<"key: " << this->key <<" rank: "<<this->rank <<" extra: "<<this->extra<<" depth: "<<depth <<std::endl;
    this->right->inOrderTraversal(depth+1);
}

template<class T, class Cond>
int RankNode<T,Cond>::getWeight() {
    return this->rank;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::insertNode(const Cond &newKey, const T &newData, int sum)
{
    if(this == nullptr){
        return new RankNode<T, Cond>(newKey, newData, 1, 0);
    }
    this->amount += this->extra;
    if(this->right != nullptr)
        this->right->extra += this->extra;
    if(this->left != nullptr)
        this->left->extra += this->extra;
    this->extra = 0;

    if (this->key < newKey) {

        this->right = this->right->insertNode(newKey, newData, 0);
    } else if (this->key > newKey) {
        this->left = this->left->insertNode(newKey, newData, 0);
    }else
        throw KeyExists();
    this->calcHeight();
    this->rank++;
    this->findMax(this->getKey(), this->amount);
    return this->rotate(0);
}

template<class T, class Cond>
void RankNode<T, Cond>::setRank(int toSet)
{
    this->rank = toSet;
}

//template<class T, class Cond>
//int RankNode<T, Cond>::getRank()
//{
//    if(this->right == nullptr)
//        return this->rank;
//    return (this->rank - this->right->rank);
//}
template<class T, class Cond>
void RankNode<T,Cond>::findMax(int str, int sum)
{
        this->extraW = str + sum;
        this->bigExtraW = this;
//    if(this->left != nullptr && this->left->extraW > this->extraW) {
//        this->extraW = this->left->extraW;
//        this->bigExtraW = this->left->bigExtraW;
//    }
    //if(this->left != nullptr && this->right == nullptr && this->left->extraW + sum > this->extraW ){
    if(this->left != nullptr  && this->left->extraW + this->left->extra > this->extraW ){
    this->extraW = this->left->extraW + this->left->extra ;
        this->bigExtraW = this->left->bigExtraW;
    }
    if(this->right != nullptr && this->right->extraW + this->right->extra  > this->extraW) {
        this->bigExtraW = this->right->bigExtraW + this->right->extra;
        this->extraW = this->right->extraW;
    }
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::deleteNode(const Cond &newKey, int sum)
{
    RankNode<T, Cond> *toSwap;
    if (this == nullptr)
        throw KeyNotFound();
    this->amount += this->extra;
    if(this->right != nullptr)
        this->right->extra += this->extra;
    if(this->left != nullptr)
        this->left->extra += this->extra;
    this->extra = 0;
    if (newKey < this->key) {
        if (this->left == nullptr)
            throw KeyNotFound();
        this->left = this->left->deleteNode(newKey, 0);
    }
    else if (newKey > this->key) {
        if (this->right == nullptr)
            throw KeyNotFound();
        this->right = this->right->deleteNode(newKey, 0);
    }
    else {
        if ((this->left == nullptr) && (this->right == nullptr)) {
            delete this;
            return nullptr;
        } else if ((this->left != nullptr) && (this->right == nullptr)) {
            this->left->extra += this->extra;
            toSwap = this->left;
            this->left = nullptr;
            delete this;
            toSwap->findMax(toSwap->getKey(), toSwap->amount);
            return toSwap;
        } else if ((this->left == nullptr) && (this->right != nullptr)) {
            this->right->extra += this->extra;
            toSwap = this->right;
            this->right = nullptr;
            delete this;
            toSwap->findMax(toSwap->getKey(), toSwap->amount);
            return toSwap;
        } else {
            RankNode<T, Cond> *temp;
            int tempRank;
            if (this->left->right != nullptr) {
                RankNode<T, Cond> *biggestFather = findBiggestParent(this->left);
                toSwap = biggestFather->right;
                temp = toSwap->left;
                if(temp!= nullptr)
                {
                    temp->extra+=toSwap->extra;
                    temp->extra-=this->extra;
                }
                toSwap->extra = this->findSumExtras(toSwap->key,0);
                this->right->extra+=(this->extra - toSwap->extra);
                this->left->extra+=(this->extra - toSwap->extra);
                biggestFather->right = this;
                swap(this, toSwap);
                toSwap->findMax(toSwap->getKey(), toSwap->amount - this->extra + toSwap->extra);
                this->right = nullptr;
                this->left = temp;
                tempRank = this->rank;
                this->rank = toSwap->rank;
                toSwap->rank = tempRank;
            } else {
                this->right->extra-=this->left->extra;
                if(this->left->left!= nullptr)
                    this->left->left->extra-=this->extra;
                this->left->extra+=this->extra;
                toSwap = this->left;
                temp = this->left->left;
                this->left->left = this;
                this->left->right = this->right;
                this->right = nullptr;
                this->left = temp;
                tempRank = toSwap->rank;
                toSwap->rank = this->rank;
                this->rank = tempRank;
                if(toSwap->right->extraW > toSwap->extraW)
                    toSwap->extraW = toSwap->right->extraW;
            }
        }
        int newSum = sum - this->extra + toSwap->extra;
        toSwap->left = toSwap->left->deleteNode(newKey, newSum );
        toSwap->calcHeight();
        toSwap->rank--;
        return toSwap->rotate(newSum );
    }
    this->findMax(this->getKey(), this->amount);
    this->calcHeight();
    this->rank--;
    return this->rotate(sum);
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::findNode(const Cond &newKey)
{
    RankNode *result;
    if (this == nullptr)
        result = nullptr;
    else if (this->key == newKey)
        result = this;
    else if (this->key < newKey)
        result = this->right->findNode(newKey);
    else if (this->key > newKey)
        result = this->left->findNode(newKey);
    if (result == nullptr)
        throw KeyNotFound();
    return result;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::rotate(int sum)
{
    int bf = this->balanceFactor();
    if (bf == LL) {
        if (left->balanceFactor() == LR)
            return this->roll_LR(sum);
        return this->roll_LL(sum);
    } else if (bf == RR) {
        if (right->balanceFactor() == RL)
            return this->roll_RL(sum);
        return this->roll_RR(sum);
    }
    return this;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_LL(int sum)
{
    RankNode<T, Cond> *temp = left;
//    this->amount += this->extra;
//    if(this->right != nullptr)
//        this->right->extra += this->extra;
//    if(this->left != nullptr)
//        this->left->extra += this->extra;
//    this->extra = 0;
//
//    temp->amount += temp->extra;
//    if(temp->right != nullptr)
//        temp->right->extra += temp->extra;
//    if(temp->left != nullptr)
//        temp->left->extra += temp->extra;
//    temp->extra = 0;

    int AL =0, AR = 0, BR = 0;
    if(temp->right != nullptr)
        AR = temp->right->rank;
    if(temp->left != nullptr)
        AL = temp->left->rank;
    if(this->right != nullptr)
        BR = this->right->rank;
    this->rank = BR + AR + 1;
    temp->rank = AL + this->rank + 1;
    int oldTemp = temp->extra;
    temp->extra += this->extra;
    this->extra -= temp->extra;
    if(temp->right != nullptr)
        temp->right->extra -= this->extra;
    this->left = temp->right;
    this->findMax(this->getKey(), this->amount + sum); //NOT SURE IF SUM + TEMP.EXTRA NEEDED
    temp->right = this;
    temp->findMax(temp->getKey(), oldTemp + temp->amount + sum); //NOT SURE
    this->calcHeight();
    temp->calcHeight();
    return temp;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_RR(int sum)
{
    RankNode<T, Cond> *temp = right;
    this->right = temp->left;
    int AL =0, AR = 0, BL = 0;
    if(temp->right != nullptr)
        AR = temp->right->rank;
    if(temp->left != nullptr)
        AL = temp->left->rank;
    if(this->left != nullptr)
        BL = this->left->rank;
    this->rank = AL + BL + 1;
    temp->rank = AR + this->rank + 1;
    int oldTemp = temp->extra;
    temp->extra += this->extra;
    this->extra -= temp->extra;
    if(temp->left != nullptr)
        temp->left->extra -= this->extra;
    temp->left = this;
    this->findMax(this->getKey(),  this->amount + sum);
    temp->findMax(temp->getKey(),  oldTemp + temp->amount + sum);
    this->calcHeight();
    temp->calcHeight();
    return temp;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_LR(int sum)
{
    this->left = this->left->roll_RR(sum + this->left->extra);
    return this->roll_LL(sum);
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_RL(int sum)
{
    this->right = this->right->roll_LL(sum + this->right->extra);
    return this->roll_RR(sum);
}


template<class T, class Cond>
RankNode<T, Cond>::~RankNode() {
    delete this->left;
    delete this->right;
}

template<class T, class Cond>
T RankNode<T, Cond>::getNodeData() {
    return data;
}

template<class T, class Cond>
T *RankNode<T, Cond>::getNodeDataPointer() {
    return &data;
}

template<class T, class Cond>
RankNode<T, Cond> *RankNode<T, Cond>::getLeft() {
    return left;
}

template<class T, class Cond>
RankNode<T, Cond> *RankNode<T, Cond>::getRight() {
    return right;
}

template<class T, class Cond>
void RankNode<T, Cond>::setRight(RankNode<T, Cond> *node) {
    this->right = node;
}

template<class T, class Cond>
void RankNode<T, Cond>::setLeft(RankNode<T, Cond> *node) {
    this->left = node;
}

template<class T, class Cond>
Cond RankNode<T, Cond>::getKey() const {
    return key;
}

template<class T, class Cond>
int RankNode<T, Cond>::getHeight() const {
    if (this == nullptr)
        return null_height;
    return height;
}

template<class T, class Cond>
int RankNode<T, Cond>::balanceFactor() const {
    if (this == nullptr)
        return empty;
    int leftHeight = left->getHeight();
    int rightHeight = right->getHeight();

    return leftHeight - rightHeight;
}

template<class T, class Cond>
void RankNode<T, Cond>::calcHeight() {
    if (this == nullptr)
        this->height = 0;
    int leftHeight = left->getHeight();
    int rightHeight = right->getHeight();

    this->height = std::max(leftHeight, rightHeight) + 1;
}

template <class T, class Cond>
RankNode<T,Cond>* RankNode<T,Cond>::findBiggestParent(RankNode *root)
{
    if(root -> right ->right == nullptr)
        return root;
    return findBiggestParent(root->right);
}

template<class T, class Cond>
void RankNode<T, Cond>::swap(RankNode<T, Cond> *source, RankNode<T, Cond> *destination) {
    destination->right = source->right;
    destination->left = source->left;
}


template<class T, class Cond>
RankNode<T, Cond> *RankNode<T, Cond>::isExist(const Cond &newKey) {
    RankNode *result;
    if (this == nullptr)
        result = nullptr;
    else if (this->key == newKey)
        result = this;
    else if (this->key < newKey)
        result = this->right->isExist(newKey);
    else if (this->key > newKey)
        result = this->left->isExist(newKey);
    return result;
}

template<class T, class Cond>
RankNode<T, Cond> *RankNode<T, Cond>::findBiggest() {
    if (this->right == nullptr)
        return this;
    return this->right->findBiggest();
}

template<class T, class Cond>
RankNode<T, Cond> *RankNode<T, Cond>::findSmallest() {
    if (this->left == nullptr)
        return this;
    return this->left->findSmallest();
}

template<class T, class Cond>
void RankNode<T,Cond>::AddExtra(const Cond& end, int toAdd)
{
    if(this == nullptr)
        throw KeyNotFound();
    if(this->key < end){
        this->extra += toAdd;
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
//        if(this->left!= nullptr)
//            this->left->extraW+=toAdd;
        this->right->AddExtraAux(end,toAdd,RIGHT,this->extra);
    }
    else if(this->key > end){
        this->left->AddExtraAux(end,toAdd,LEFT, this->extra);
    }
    else{//key==end
        if(this->right!= nullptr)
            this->right->extra-=toAdd;
        this->extra += toAdd;
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
//        if(this->left!=nullptr && this->right != nullptr)
//            this->left->extraW+=toAdd;
        this->findMax(this->getKey(), this->amount);
        return;
    }
    this->findMax(this->getKey(), this->amount);
}

template<class T, class Cond>
void RankNode<T,Cond>::AddExtraAux(const Cond& end, int toAdd, int prevDirection, int sum)
{
    if(this == nullptr)
        throw KeyNotFound();
    if(this->key > end)
    {
        if(prevDirection == RIGHT)
            this->extra-=toAdd;
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
        this->left->AddExtraAux(end, toAdd, LEFT, this->extra);
        this->findMax(this->getKey(), this->amount);
    }
    else if(this->key < end)
    {
        if(prevDirection == LEFT)
            this->extra+=toAdd;
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
//        if(this->left!= nullptr)
//            this->left->extraW+=toAdd;
        this->right->AddExtraAux(end, toAdd, RIGHT, this->extra);
        this->findMax(this->getKey(), this->amount);
    }
    else//found
    {
        if(prevDirection == LEFT)
            this->extra+=toAdd;
        if(this->right!= nullptr){
            this->right->extra-=toAdd;
        }
        this->amount += this->extra;
        if(this->right != nullptr)
            this->right->extra += this->extra;
        if(this->left != nullptr)
            this->left->extra += this->extra;
        this->extra = 0;
//        if(this->left!= nullptr && this->right != nullptr)
//            this->left->extraW+=toAdd;
        this->findMax(this->getKey(), this->amount);
    }
}


#endif //WET2_RANKNODE_H



