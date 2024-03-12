#include <iostream>

#ifndef WET1_NODE_H
#define WET1_NODE_H

#define LL 2
#define LR -1
#define RR -2
#define RL 1
#define empty 0
#define null_height -1

//AVL tree exception classes //NEED TO RECHECK
class KeyExists : public std::exception {
};
class KeyNotFound : public std::exception {
};

template<class T, class Cond>
class Node {
    Cond key;
    Node *right;
    Node *left;
    int height;
    T data;
public:
    //Constructors/Destructors
    Node(Cond key, T data) : key(key), right(nullptr),
                             left(nullptr), height(0),
                             data(data) {}

    Node(const Node &node);

    Node &operator=(const Node &node) = default;

    //~Node();
    ~Node();

    //Getters - NOT SURE IF NEEDED
    T getNodeData();

    T *getNodeDataPointer();

    Node *getRight();

    Node *getLeft();

    void setRight(Node *node);

    void setLeft(Node *node);

    Cond getKey() const;

    int getHeight() const;  //not sure if needed
    //Rotations
    Node *rotate();

    Node *roll_LL();

    Node *roll_LR();

    Node *roll_RL();

    Node *roll_RR();

    Node *findBiggestParent(Node *root);

    Node *findBiggest();

    Node *findSmallest();

    void swap(Node *source, Node *destination);

    Node *insertNode(const Cond &key, const T &data);

    Node *deleteNode(const Cond &key);

    int balanceFactor() const;

    void calcHeight();

    Node *findNode(const Cond &newKey);

    Node *isExist(const Cond &newKey);
};

template<class T, class Cond>
Node<T, Cond>::Node(const Node<T, Cond> &node) {
    this->key = node.key;
    this->right = node.right;
    this->left = node.left;
    this->height = node.height;
    this->data = node.data;
}

template<class T, class Cond>
Node<T, Cond>::~Node() {
    delete this->left;
    delete this->right;
}

template<class T, class Cond>
T Node<T, Cond>::getNodeData() {
    return data;
}

template<class T, class Cond>
T *Node<T, Cond>::getNodeDataPointer() {
    return &data;
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::getLeft() {
    return left;
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::getRight() {
    return right;
}

template<class T, class Cond>
void Node<T, Cond>::setRight(Node<T, Cond> *node) {
    this->right = node;
}

template<class T, class Cond>
void Node<T, Cond>::setLeft(Node<T, Cond> *node) {
    this->left = node;
}

template<class T, class Cond>
Cond Node<T, Cond>::getKey() const {
    return key;
}

template<class T, class Cond>
int Node<T, Cond>::getHeight() const {
    if (this == nullptr)
        return null_height;
    return height;
}

template<class T, class Cond>
int Node<T, Cond>::balanceFactor() const {
    if (this == nullptr)
        return empty;
    int leftHeight = left->getHeight();
    int rightHeight = right->getHeight();

    return leftHeight - rightHeight;
}

template<class T, class Cond>
void Node<T, Cond>::calcHeight() {
    if (this == nullptr)
        this->height = 0;
    int leftHeight = left->getHeight();
    int rightHeight = right->getHeight();

    this->height = std::max(leftHeight, rightHeight) + 1;
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::rotate() {
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
Node<T, Cond> *Node<T, Cond>::roll_LL() {
    Node<T, Cond> *temp = left;
    this->left = temp->right;
    temp->right = this;
    this->calcHeight();
    temp->calcHeight();
    return temp;
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::roll_RR() {
    Node<T, Cond> *temp = right;
    this->right = temp->left;
    temp->left = this;
    this->calcHeight();
    temp->calcHeight();
    return temp;
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::roll_LR() {
    this->left = this->left->roll_RR();
    return this->roll_LL();
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::roll_RL() {
    this->right = this->right->roll_LL();
    return this->roll_RR();
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::insertNode(const Cond &newKey, const T &newData) {
    if (this == nullptr) {
        return new Node<T, Cond>(newKey, newData);
    }
    if (this->key < newKey) {
        this->right = this->right->insertNode(newKey, newData);
    } else if (this->key > newKey) {
        this->left = this->left->insertNode(newKey, newData);
    }else
        throw KeyExists();
    this->calcHeight();
    return this->rotate();
}

template <class T, class Cond>
Node<T,Cond>* Node<T,Cond>::findBiggestParent(Node *root)
{
    if(root -> right ->right == nullptr)
        return root;
    return findBiggestParent(root->right);
}

template<class T, class Cond>
void Node<T, Cond>::swap(Node<T, Cond> *source, Node<T, Cond> *destination) {
    destination->right = source->right;
    destination->left = source->left;
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::deleteNode(const Cond &newKey) {
    Node<T, Cond> *toSwap;
    if (this == nullptr)
        throw KeyNotFound();
    if (newKey < this->key) {
        if (this->left == nullptr)
            throw KeyNotFound();
        this->left = this->left->deleteNode(newKey);
        this->calcHeight();
        return this->rotate();
    } else if (newKey > this->key) {
        if (this->right == nullptr)
            throw KeyNotFound();
        this->right = this->right->deleteNode(newKey);
        this->calcHeight();
        return this->rotate();
    } else {
        if ((this->left == nullptr) && (this->right == nullptr)) {
            delete this;
            return nullptr;
        } else if ((this->left != nullptr) && (this->right == nullptr)) {
            toSwap = this->left;
            this->left = nullptr;
            delete this;
            return toSwap;
        } else if ((this->left == nullptr) && (this->right != nullptr)) {
            toSwap = this->right;
            this->right = nullptr;
            delete this;
            return toSwap;
        } else {
            Node<T, Cond> *temp;
            if (this->left->right != nullptr) {
                Node<T, Cond> *biggestFather = findBiggestParent(this->left);
                toSwap = biggestFather->right;
                temp = toSwap->left;
                biggestFather->right = this;
                swap(this, toSwap);
                this->right = nullptr;
                this->left = temp;
            } else {
                toSwap = this->left;
                temp = this->left->left;
                this->left->left = this;
                this->left->right = this->right;
                this->right = nullptr;
                this->left = temp;
            }
        }
        toSwap->left = toSwap->left->deleteNode(newKey);
        toSwap->calcHeight();
        return toSwap->rotate();
    }
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::findNode(const Cond &newKey) {
    Node *result;
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
Node<T, Cond> *Node<T, Cond>::isExist(const Cond &newKey) {
    Node *result;
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
Node<T, Cond> *Node<T, Cond>::findBiggest() {
    if (this->right == nullptr)
        return this;
    return this->right->findBiggest();
}

template<class T, class Cond>
Node<T, Cond> *Node<T, Cond>::findSmallest() {
    if (this->left == nullptr)
        return this;
    return this->left->findSmallest();
}

#endif //WET1_NODE_H



