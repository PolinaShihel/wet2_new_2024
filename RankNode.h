#ifndef WET2_RANKNODE_H
#define WET2_RANKNODE_H

#include <iostream>

#define LL 2
#define LR -1
#define RR -2
#define RL 1
#define empty 0
#define null_height -1
#define LEFT 3
#define RIGHT 4
#define NO_DIRECT 5


template<class T, class Cond>
class RankNode {
    Cond key;
    RankNode *right;
    RankNode *left;
    int height;
    T data;
    int rank;
    int extra;

public:
    RankNode(Cond key, T data): key(key), right(nullptr),left(nullptr), height(0),
                                data(data), rank(1),extra(0){};
    RankNode(Cond key, T data,int rank): key(key), right(nullptr),left(nullptr), height(0),
                                         data(data),rank(rank),extra(0){};
    RankNode(Cond key, T data,int rank, int extra): key(key), right(nullptr),left(nullptr), height(0),
                                         data(data),rank(rank),extra(extra){};
    RankNode *insertNode(const Cond &key, const T &data, int sum);
    RankNode *deleteNode(const Cond &newKey);
    RankNode *findNode(const Cond &newKey);
    //Rotations
    RankNode *rotate();
    RankNode *roll_LL();
    RankNode *roll_LR();
    RankNode *roll_RL();
    RankNode *roll_RR();
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
    //void setRank(int rank);
    int getRank();
    void AddExtra(int end, int toAdd);
    void AddExtraAux(int end, int toAdd, int prevDirection);
};

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::insertNode(const Cond &newKey, const T &newData, int sum)
{
    if(this == nullptr){
        return new RankNode<T, Cond>(newKey, newData, 1, -sum);
    }
    if (this->key < newKey) {
        this->right = this->right->insertNode(newKey, newData);
    } else if (this->key > newKey) {
        this->left = this->left->insertNode(newKey, newData);
    }else
        throw KeyExists();
    this->calcHeight();
    this->rank++;
    return this->rotate();
}

//template<class T, class Cond>
//void RankNode<T, Cond>::setRank(int toSet)
//{
//    this->rank = toSet;
//}
//
template<class T, class Cond>
int RankNode<T, Cond>::getRank()
{
    if(this->right == nullptr)
        return this->rank;
    return (this->rank - this->right->rank);
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::deleteNode(const Cond &newKey)
{
    RankNode<T, Cond> *toSwap;
    if (this == nullptr)
        throw KeyNotFound();
    if (newKey < this->key) {
        if (this->left == nullptr)
            throw KeyNotFound();
        this->left = this->left->deleteNode(newKey);
        this->calcHeight();
        this->rank--;
        return this->rotate();
    } else if (newKey > this->key) {
        if (this->right == nullptr)
            throw KeyNotFound();
        this->right = this->right->deleteNode(newKey);
        this->calcHeight();
        this->rank--;
        return this->rotate();
    } else {
        if ((this->left == nullptr) && (this->right == nullptr)) {
            delete this;
            return nullptr;
        } else if ((this->left != nullptr) && (this->right == nullptr)) {
            this->left->extra += this->extra;
            toSwap = this->left;
            this->left = nullptr;
            delete this;
            return toSwap;
        } else if ((this->left == nullptr) && (this->right != nullptr)) {
            this->right->extra += this->extra;
            toSwap = this->right;
            this->right = nullptr;
            delete this;
            return toSwap;
        } else {
            RankNode<T, Cond> *temp;
            int tempRank;
            if (this->left->right != nullptr) {
                this->right->extra+=this->extra;
                this->left->extra+=this->extra;
                RankNode<T, Cond> *biggestFather = findBiggestParent(this->left);
                toSwap = biggestFather->right;
                temp = toSwap->left;
                this->right->extra-=toSwap->extra;
                this->left->extra-=toSwap->extra;
                temp->extra+=toSwap->extra;
                temp->extra-=this->extra;
                biggestFather->right = this;
                swap(this, toSwap);
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
                thas->rank = tempRank;
            }
        }
        toSwap->left = toSwap->left->deleteNode(newKey);
        toSwap->calcHeight();
        toSwap->rank--;
        return toSwap->rotate();
    }
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
RankNode<T,Cond> *RankNode<T,Cond>::rotate()
{
    int bf = this->balanceFactor();
    if (bf == LL) {
        if (left->balanceFactor() == LR)
            return this->roll_LR();
        return this->roll_LL();
    } else if (bf == RR) {
        if (right->balanceFactor() == RL)
            return this->roll_RL();
        return this->roll_RR();
    }
    return this;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_LL()
{
    RankNode<T, Cond> *temp = left;
    int AL =0, AR = 0, BR = 0;
    if(temp->right != nullptr)
        AR = temp->right->rank;
    if(temp->left != nullptr)
        AL = temp->left->rank;
    if(this->right != nullptr)
        BR = this->right->rank;
    this->rank = BR + AR + 1;
    temp->rank = AL + this->rank + 1;
    temp->extra += this->extra;
    this->extra -= temp->extra;
    if(temp->right != nullptr)
        temp->right->extra -= this->extra;
    this->left = temp->right;
    temp->right = this;
    this->calcHeight();
    temp->calcHeight();
    return temp;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_RR()
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
    temp->extra += this->extra;
    this->extra -= temp->extra;
    if(temp->left != nullptr)
        temp->left->extra -= this->extra;
    temp->left = this;
    this->calcHeight();
    temp->calcHeight();
    return temp;
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_LR()
{
    this->left = this->left->roll_RR();
    return this->roll_LL();
}

template<class T, class Cond>
RankNode<T,Cond> *RankNode<T,Cond>::roll_RL()
{
    this->right = this->right->roll_LL();
    return this->roll_RR();
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
void RankNode<T,Cond>::AddExtra(int end, int toAdd)
{
    if(this->root == nullptr)
        throw KeyNotFound();
    if(this->key < end){
        this->extra += toAdd;
        this->right->AddExtraAux(end,toAdd,RIGHT);
    }
    else if(this->key > end){
        this->left->AddExtraAux(end,toAdd,LEFT);
    }
    else{//key==end
        this->extra += toAdd;
        if(this->right!= nullptr)
            this->right->extra-=toAdd;
    }
}

template<class T, class Cond>
void RankNode<T,Cond>::AddExtraAux(int end, int toAdd, int prevDirection)
{
    if(this == nullptr)
        throw KeyNotFound();
    if(this->key > end)
    {
        if(prevDirection == RIGHT)
            this->extra-=toAdd;
        this->left->AddExtraAux(end, toAdd, LEFT);
    }
    else if(this->key < end)
    {
        if(prevDirection == LEFT)
            this->extra+=toAdd;
        this->right->AddExtraAux(end, toAdd, RIGHT);
    }
    else//found
    {
        if(prevDirection == LEFT)
            this->key+=toAdd;
        if(this->right!= nullptr)
            this->right->extra-=toAdd;
    }
}


#endif //WET2_RANKNODE_H



