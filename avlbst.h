#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value>& new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void add(const std::pair<const Key, Value>& keyValuePair); 
    void updateHeights(AVLNode<Key,Value>* newNode); 
    AVLNode<Key,Value>* findImbalance(AVLNode<Key,Value>* newNode); 
    void checkImbalance(AVLNode<Key,Value>*& z, AVLNode<Key,Value>*&y, AVLNode<Key,Value>*&x); 
    int imbalanceType(AVLNode<Key,Value>*& z, AVLNode<Key,Value>*&y, AVLNode<Key,Value>*&x);
    void zigzigRight(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    void zigzigLeft(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x); 
    void zigzagRight(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    void zigzagLeft(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    AVLNode<Key, Value>* getTallerChild(AVLNode<Key,Value>* node); 
    AVLNode<Key,Value>* breakTies(AVLNode<Key,Value>* y, AVLNode<Key,Value>* z);
    void changeHeights(AVLNode<Key,Value>*z, AVLNode<Key,Value>*y);


};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item)
{
    // TODO
    add(new_item); 
    Node<Key, Value>* newNode = BinarySearchTree<Key,Value>::internalFind(new_item.first);
    static_cast<AVLNode<Key, Value>*>(newNode)->setHeight(0);
    updateHeights(static_cast<AVLNode<Key, Value>*>(newNode)); 

    if (BinarySearchTree<Key,Value>::isBalanced() == true) {
        return;
    }

    AVLNode<Key, Value>* z = findImbalance(static_cast<AVLNode<Key, Value>*>(newNode));
    AVLNode<Key, Value>* y;
    AVLNode<Key, Value>* x; 
    checkImbalance(z, y, x);
    int imbalance = imbalanceType(z, y, x); 
    if (imbalance == 1) {
        zigzigRight(z, y, x);
    }
    else if (imbalance == 2) {
        zigzigLeft(z, y, x); 
    }
    else if (imbalance == 3) {
        zigzagLeft(z, y, x);
    }
    else {
        zigzagRight(z,y,x);
    }
}

template<class Key, class Value>
void
AVLTree<Key, Value>::add(const pair<const Key, Value>& keyValuePair)
{
    // TODO
    if (BinarySearchTree<Key,Value>::root_ == NULL) {
        BinarySearchTree<Key,Value>::root_ = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
        return; 
    }

    // if key already exists 
    Node<Key, Value>* x = BinarySearchTree<Key,Value>::internalFind(keyValuePair.first);
    if (x != NULL) {
        x->setValue(keyValuePair.second); 
        return;
    }

    // find where the node fits  
    AVLNode<Key, Value>* root = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::root_); 
    AVLNode<Key, Value>* parent = root; 
    Key curr = keyValuePair.first;
    while (root != NULL) {
        if (root->getKey() > curr) {
            parent = root; 
            root = root->getLeft();
        }
        else {
            parent = root; 
            root = root->getRight(); 
        }
    }
    AVLNode<Key, Value>* node = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    if (parent->getKey() > curr) parent->setLeft(node);
    else parent->setRight(node);
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


template<class Key, class Value>
void AVLTree<Key, Value>::updateHeights(AVLNode<Key,Value>* newNode)
{
    // cout << "updating heights" << endl;
    while (newNode != NULL)
    {
        int lh = 0;
        if (newNode->getLeft() != NULL) lh = newNode->getLeft()->getHeight();

        int rh = 0;
        if (newNode->getRight() != NULL) rh = newNode->getRight()->getHeight();

        int h = std::max(lh, rh) + 1;
        newNode->setHeight(h);
        newNode = newNode->getParent();
    }
}


template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::findImbalance(AVLNode<Key,Value>* newNode) 
{   
    if (newNode->getParent() == NULL) return newNode; 

    while (newNode->getParent() != NULL) {
        AVLNode<Key, Value>* parent = newNode->getParent();
        int thisHeight = newNode->getHeight();
        int otherHeight; 
        if (parent->getRight() == NULL) otherHeight = 0; 
        else if (parent->getRight() != newNode) otherHeight = parent->getRight()->getHeight();
        else if (parent->getLeft() == NULL) otherHeight = 0;
        else if (parent->getLeft() != newNode) otherHeight = parent->getLeft()->getHeight(); 
        if (abs(thisHeight - otherHeight) > 1) return parent; 
        newNode = newNode->getParent(); 
    }
    return 0; 
}

template<class Key, class Value>
void AVLTree<Key, Value>::checkImbalance(AVLNode<Key,Value>*& z, AVLNode<Key,Value>*&y, AVLNode<Key,Value>*&x) 
{
    // cout << "calculating y and x" << endl;
    AVLNode<Key,Value>* left = z->getLeft();
    AVLNode<Key,Value>* right = z->getRight();
    // finding y - child with greatest height 
    if (left != NULL && right != NULL) {
        if (left->getHeight() > right->getHeight()) y = left; 
        else y = right;
    }
    else if (left != NULL && right == NULL) y = left; 
    else if (left == NULL && right != NULL) y = right; 

    AVLNode<Key,Value>* gleft = y->getLeft(); 
    AVLNode<Key,Value>* gright = y->getRight();
    // finding x - grandchild with greatest height 
    if (gleft != NULL && gright != NULL) {
        if (gleft->getHeight() > gright->getHeight()) x = gleft; 
        else x = gright;
    }
    else if (gleft != NULL && gright == NULL) x = gleft; 
    else if (gleft == NULL && gright != NULL) x = gright; 
}

template<class Key, class Value>
int AVLTree<Key, Value>::imbalanceType(AVLNode<Key,Value>*& z, AVLNode<Key,Value>*& y, AVLNode<Key,Value>*& x) 
{
    int type = 0;  

    if (z->getRight() == y) {
        if (y->getRight() == x) {
            type = 1; 
        } 
        else if (y->getLeft() == x) {
            type = 3;
        }
    } 
    else if (z->getLeft() == y) {
        if (y->getLeft() == x) {
            type = 2;
        } 
        else if (y->getRight() == x) {
            type = 4;
        }
    }
    return type; 
}

template<class Key, class Value>
void AVLTree<Key, Value>::zigzigRight(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x) 
{
    y->setParent(z->getParent()); 
    // if z has a parent, update it 
    if (z->getParent() != nullptr) {
        if (z->getParent()->getLeft() == z) z->getParent()->setLeft(y);
        else z->getParent()->setRight(y);
    } 
    // if z is the root
    else BinarySearchTree<Key,Value>::root_ = y;

    z->setParent(y);
    AVLNode<Key,Value>* left = y->getLeft();
    z->setRight(left);
    if (left != nullptr) left->setParent(z);
    y->setLeft(z);

    //changeHeights(z, y); 
 
    int zh = 1;
    if (getTallerChild(z) != NULL) {
        zh = getTallerChild(z)->getHeight() + 1;
    }
    // cout << "changing height" << endl;
    z->setHeight(zh);
    int yh = getTallerChild(y)->getHeight() + 1;
    y->setHeight(yh);
}

template<class Key, class Value>
void AVLTree<Key, Value>::changeHeights(AVLNode<Key,Value>*z, AVLNode<Key,Value>*y) 
{
    int zh = 1;
    if (getTallerChild(z) != NULL) zh = getTallerChild(z)->getHeight() + 1;
    // cout << "changing height" << endl;
    z->setHeight(zh);
    int yh = getTallerChild(y)->getHeight() + 1;
    y->setHeight(yh);
}

template<class Key, class Value>
void AVLTree<Key, Value>::zigzigLeft(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x) 
{
    // cout << "zigzig left" << endl; 
    y->setParent(z->getParent()); 
    // if z has a parent, update it 
    if (z->getParent() != nullptr) {
        if (z->getParent()->getRight() == z) z->getParent()->setRight(y);
        else z->getParent()->setLeft(y);
    } 
    // if z is the root
    else BinarySearchTree<Key,Value>::root_ = y;

    z->setParent(y);
    AVLNode<Key,Value>* right = y->getRight();
    z->setLeft(right);
    if (right != nullptr) right->setParent(z);
    y->setRight(z);

    //changeHeights(z, y);
    int zh = 1;
    if (getTallerChild(z) != NULL) zh = getTallerChild(z)->getHeight() + 1;
    z->setHeight(zh);
    int yh = getTallerChild(y)->getHeight() + 1;
    y->setHeight(yh);
    // int zh = z->getHeight()-2; 
    // z->setHeight(zh);
}

template<class Key, class Value>
void AVLTree<Key, Value>::zigzagLeft(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x)
{
    // cout << "zigzag left" << endl;
    if (z == BinarySearchTree<Key,Value>::root_) BinarySearchTree<Key,Value>::root_ = x;


    x->setParent(z->getParent());
    if (x->getLeft() != NULL) {
        AVLNode<Key,Value>* temp = x->getLeft();
        z->setRight(temp);
        temp->setParent(z);
    }
    else z->setRight(NULL);

    if (x->getRight()) {
        AVLNode<Key,Value>* temp = x->getRight();
        y->setLeft(temp);
        temp->setParent(y);
    }
    else y->setLeft(NULL);

    int zh = 1;
    if (getTallerChild(z)) zh = getTallerChild(z)->getHeight() + 1;
    z->setHeight(zh);
    int yh = 1;
    if (getTallerChild(y) != NULL) yh = getTallerChild(y)->getHeight() + 1;
    y->setHeight(yh);
    //changeHeights(z, y);

    x->setLeft(z);
    x->setRight(y);
    if (z->getParent() != NULL) {
        if (z->getParent()->getLeft() == z) z->getParent()->setLeft(x);
        else z->getParent()->setRight(x);
    }
    z->setParent(x);
    y->setParent(x);
    int xh = std::max(z->getHeight(), y->getHeight()) + 1;
    x->setHeight(xh);
}

template<class Key, class Value>
void AVLTree<Key, Value>::zigzagRight(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x)
{
    if (z == BinarySearchTree<Key,Value>::root_) BinarySearchTree<Key,Value>::root_ = x;

    AVLNode<Key,Value>* parent = z->getParent(); 
    x->setParent(parent);
    if(x->getLeft() != NULL) {
        AVLNode<Key,Value>* temp = x->getLeft();
        y->setRight(temp);
        temp->setParent(y);
    }
    else y->setRight(NULL);

    if (x->getRight()) {
        AVLNode<Key,Value>* temp = x->getRight();
        z->setLeft(temp);
        temp->setParent(z);
    }
    else z->setLeft(NULL);

    int zh = 1;
    if (getTallerChild(z)) zh = getTallerChild(z)->getHeight() + 1;
    z->setHeight(zh);
    int yh = 1;
    if (getTallerChild(y)) yh = getTallerChild(y)->getHeight() + 1;
    y->setHeight(yh);
    //changeHeights(z, y);

    x->setLeft(y);
    x->setRight(z);
    if (z->getParent() != NULL) {
        if (z->getParent()->getLeft() == z) z->getParent()->setLeft(x);
        else z->getParent()->setRight(x);
    }
    z->setParent(x);
    y->setParent(x);
    int xh = std::max(z->getHeight(), y->getHeight()) + 1;
    x->setHeight(xh);
}


template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // cout << "removing " << key << endl; 
    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
    AVLNode<Key, Value>* succ;

    // if the node doesn't exist 
    if (node == NULL) return;

    AVLNode<Key,Value>* left = node->getLeft();
    AVLNode<Key,Value>* right = node->getRight(); 
    // if it has two children 
    if (left != NULL && right != NULL) {   
        succ = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::successor(node));
        nodeSwap(node, succ);
        if (node->getRight() != NULL) {
            nodeSwap(node, node->getRight());
            node->getParent()->setRight(NULL); 
        }
        else if (node->getParent() == succ) succ->setRight(NULL);
        else node->getParent()->setLeft(NULL); 
        updateHeights(succ);
        delete node;
    }

    // if it only has a left child 
    else if (left != NULL) {
        succ = left;
        if (node == BinarySearchTree<Key,Value>::root_) {
            BinarySearchTree<Key,Value>::root_ = succ;
            succ->setParent(NULL); 
        }
        else if (node->getParent()->getLeft() == node){
            succ->setParent(node->getParent());
            node->getParent()->setLeft(succ);
        }
        else {
            succ->setParent(node->getParent());
            node->getParent()->setRight(succ);
        }
        updateHeights(succ);
        delete node;
    }

    // if it only has a right child 
    else if (right != NULL) {
        succ = node->getRight();
        if (node == BinarySearchTree<Key,Value>::root_) {
            BinarySearchTree<Key,Value>::root_ = succ;
            succ->setParent(NULL);
        }
        else if (node->getParent()->getLeft() == node) {
            succ->setParent(node->getParent());
            node->getParent()->setLeft(succ);
        }
        else {
            succ->setParent(node->getParent());
            node->getParent()->setRight(succ);
        }
        updateHeights(succ);
        delete node;
    }
    
    // if it is the root 
    else if (node == BinarySearchTree<Key,Value>::root_)
    {
        BinarySearchTree<Key,Value>::root_ = nullptr;
        delete node;
    }

    // if it is a leaf node 
    else {
        // cout << "no children" << endl;
        succ = node->getParent();
        if (succ->getLeft() == node) succ->setLeft(NULL);
        else succ->setRight(NULL);
        updateHeights(succ);
        delete node;
    }

    while (this->isBalanced() == false)
    {
        AVLNode<Key, Value>* z = findImbalance(succ);
        // cout << z << endl;
        // cout << "test" << endl;
        AVLNode<Key, Value>* y = getTallerChild(z);
        AVLNode<Key, Value>* x = breakTies(y, z);
        int imbalance = imbalanceType(z, y, x);
        if (imbalance == 1) {
            zigzigRight(z, y, x);
            // cout << "z" << z->getKey() << " new height " << z->getHeight() << endl;
        }
        else if (imbalance == 2) {
            zigzigLeft(z, y, x); 
            // cout << "z" << z->getKey() << " new height " << z->getHeight() << endl;
        }
        else if (imbalance == 3) {
            zigzagLeft(z, y, x);
            // cout << "z" << z->getKey() << " new height " << z->getHeight() << endl;
        }
        else {
            zigzagRight(z,y,x);
            // cout << "z" << z->getKey() << " new height " << z->getHeight() << endl;
        }
    }
}

template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::breakTies(AVLNode<Key,Value>* y, AVLNode<Key,Value>* z)
{
    AVLNode<Key,Value>* left = y->getLeft(); 
    AVLNode<Key,Value>* right = y->getRight(); 
    if (left == NULL) return right;
    else if (right == NULL) return left; 
    else {
        if (left->getHeight() > right->getHeight()) return left;
        else if (left->getHeight() < right->getHeight())return right;
        else {
            if (z->getLeft() == y) return left; 
            else return right;
        }
    }
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getTallerChild(AVLNode<Key,Value>* currNode) 
{   
    // cout << "getting taller child of " << currNode->getKey() << endl;
    if (currNode->getLeft() == NULL) return currNode->getRight();
    else if (currNode->getRight() == NULL) return currNode->getLeft();
    else {
        if (currNode->getLeft()->getHeight() < currNode->getRight()->getHeight()) return currNode->getRight();
        else return currNode->getLeft();
    }
}

#endif
