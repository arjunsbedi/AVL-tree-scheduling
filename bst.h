#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
using namespace std; 

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL) 
{


}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value>* getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value>* r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    Node<Key, Value>* add(const std::pair<const Key, Value>& keyValuePair, Node<Key, Value>* parent);
    static Node<Key, Value>* successor(Node<Key, Value>* current);  
    Node<Key, Value>* internalFinder(const Key& key, Node<Key, Value>* curr) const;
    void clearer(Node<Key, Value>* root);
    bool balanced(Node<Key, Value>* root) const;
    int height(Node<Key, Value>* root) const; 
    void AVLinsert(const pair<const Key, Value>& keyValuePair);



protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
    : current_(ptr)
{
    // TODO

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
    : current_(NULL)
{
    // TODO

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ == rhs.current_); 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ != rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
	if (current_->getRight() != NULL) {
		current_ = current_->getRight();
		while (current_->getLeft() != NULL) {
			current_ = current_->getLeft();
		}
	}
	else if(current_->getRight() == NULL)
	{
		Node<Key, Value>* parent = current_->getParent();
		while (parent != NULL && current_ == parent->getRight())
		{
			current_ = parent;
			parent = parent->getParent();
		}
		current_ = parent;
	}
	return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
    : root_(NULL)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    //clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void
BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
    //cout << "BST adding " << keyValuePair.first << endl;
    // TODO
    if (root_ == NULL) {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
        return; 
    }

    // if key already exists 
    Node<Key, Value>* x = internalFind(keyValuePair.first);
    if (x != NULL) {
        x->setValue(keyValuePair.second); 
        return;
    }

    // find where the node fits  
    Node<Key, Value>* root = root_; 
    Node<Key, Value>* parent = root; 
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
    Node<Key, Value>* node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
    if (parent->getKey() > curr) parent->setLeft(node);
    else parent->setRight(node);
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/

// template<typename Key, typename Value>
// void BinarySearchTree<Key, Value>::remove(const Key& key)
// {
    
// }
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //cout << "removing " << key << endl; 
    Node<Key, Value>* removedNode = internalFind(key);
    if (removedNode == NULL) return;  
    Node<Key, Value>* parent = removedNode->getParent(); 
    Node<Key, Value>* left = removedNode->getLeft(); 
    Node<Key, Value>* right = removedNode->getRight(); 

    // if it is the root 
    if (parent == NULL) {
        //cout << "removing root" << endl;
        // if the root has no children 
        if (left == NULL && right == NULL) root_ = NULL; 
        // if the root does have children 
        else if (left != NULL && right == NULL) {
            left->setParent(NULL);
            root_ = left; 
        }
        else if (right != NULL && left == NULL) {
            //cout << "test" << endl;
            right->setParent(NULL);
            root_ = right;
        }

        // if the root has two children 
        else if (left != NULL && right != NULL) {
            //cout << "removing node with two children " << key << endl;
            Node<Key, Value>* succ = successor(removedNode);
            nodeSwap(removedNode, succ);
            //cout << succ->getLeft()->getKey() << " " << succ->getRight()->getKey() << endl;

            // if succ was a leaf node 
            if (removedNode->getLeft() == NULL && removedNode->getRight() == NULL) {
                //cout << removedNode->getParent()->getKey() << endl; 
                if (removedNode->getParent()->getLeft() == removedNode) {
                    removedNode->getParent()->setLeft(removedNode->getRight());
                }
                else if (removedNode->getParent()->getRight() == removedNode) {
                    removedNode->getParent()->setRight(removedNode->getRight());
                }
            }
            // if succ had a child 
            else if (removedNode->getRight() != NULL) {
                //cout << "test " << removedNode->getRight()->getKey() << endl;
                if (removedNode->getParent()->getLeft() == removedNode) {
                    removedNode->getParent()->setLeft(removedNode->getRight());
                    removedNode->getRight()->setParent(removedNode->getParent());
                }
                else if (removedNode->getParent()->getRight() == removedNode) {
                    removedNode->getParent()->setRight(removedNode->getRight());
                    removedNode->getRight()->setParent(removedNode->getParent());
                }
            }
        }
    }

    // if it is a leaf node 
    else if (left == NULL && right == NULL) {
        if (parent != NULL) {
            //cout << "removing leaf node " << key << endl;
            if (parent->getLeft() == removedNode) parent->setLeft(NULL);
            else parent->setRight(NULL); 
        }
    }

    // if it has two children 
    else if (left != NULL && right != NULL) {
        //cout << "removing node with two children " << key << endl;
        Node<Key, Value>* succ = successor(removedNode);
        nodeSwap(removedNode, succ);
        //cout << succ->getKey() << endl;
        //cout << succ->getLeft()->getKey() << " " << succ->getRight()->getKey() << endl;

        // if succ was a leaf node 
        if (removedNode->getLeft() == NULL && removedNode->getRight() == NULL) {
            //cout << removedNode->getParent()->getKey() << endl; 
            if (removedNode->getParent()->getLeft() == removedNode) {
                removedNode->getParent()->setLeft(removedNode->getRight());
            }
            else if (removedNode->getParent()->getRight() == removedNode) {
                removedNode->getParent()->setRight(removedNode->getRight());
            }
        }
        // if succ had a child 
        else if (removedNode->getRight() != NULL) {
            //cout << "test " << removedNode->getRight()->getKey() << endl;
            if (removedNode->getParent()->getLeft() == removedNode) {
                removedNode->getParent()->setLeft(removedNode->getRight());
                removedNode->getRight()->setParent(removedNode->getParent());
            }
            else if (removedNode->getParent()->getRight() == removedNode) {
                removedNode->getParent()->setRight(removedNode->getRight());
                removedNode->getRight()->setParent(removedNode->getParent());
            }
        }
    }

    // if it has one child 
    else {
        //cout << "removing node with one child " << key << endl; 
        if (left != NULL) {
            nodeSwap(removedNode, left);
            if (removedNode->getLeft() == NULL && removedNode->getRight() == NULL) {
                //cout << removedNode->getParent()->getKey() << endl; 
                if (removedNode->getParent()->getLeft() == removedNode) {
                    removedNode->getParent()->setLeft(removedNode->getRight());
                }
                else if (removedNode->getParent()->getRight() == removedNode) {
                    removedNode->getParent()->setRight(removedNode->getRight());
                }
            }
            if (removedNode->getLeft() != NULL) {
                removedNode->getLeft()->setParent(left);
                left->setLeft(removedNode->getLeft()); 
            }
            if (removedNode->getRight() != NULL) {
                removedNode->getRight()->setParent(left);
                left->setRight(removedNode->getRight()); 
            }
        }
        else if (right != NULL) {
            //cout << "removing node with one child " << key << endl; 
            nodeSwap(removedNode, right);
            right->setRight(NULL); 
            
        }

    }
    //cout << "removed" << endl; 
    delete removedNode; 
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //credit: CP Lin
    auto parent = current->getParent();

    while (parent != NULL && current == parent->getLeft()){
        current = parent;
        parent = parent->getParent();
    }

    current = parent;

    return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    //cout << "getting successor of " << current->getKey();
    // TODO
    //Node<Key, Value>* parent = current->getParent(); 
    if (current->getRight() != NULL) {
        current = current->getRight(); 
        while(current->getLeft() != NULL) {
            current = current->getLeft(); 
        }
        //cout << " " << current->getKey() << endl;
        return current; 
    }

    else {
        if (current->getParent() == NULL) {
            //cout << "NULL" << endl; 
            return NULL;
        }
        //current = current->getParent(); 
        while (true) {
            if (current->getParent() == NULL) {
                //cout << "NULL" << endl; 
                return NULL; 
            }
            if (current->getParent()->getLeft() == current) {
                // << " " << current->getParent()->getKey() << endl;
                return current->getParent(); 
            }
            current = current->getParent(); 
        }
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearer(root_); 
    root_ = NULL; 
    
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearer(Node<Key, Value>* root) {
    if (root->getLeft() != NULL) clearer(root->getLeft());
    if (root->getRight() != NULL) clearer (root->getRight());
    delete root; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* min = root_;
    if (min == NULL) return NULL; 
    while (min->getLeft() != NULL) {
        min = min->getLeft();
    }
    return min; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    return internalFinder(key, root_);

}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFinder(const Key& key, Node<Key, Value>* curr) const
{
    // TODO
    if (curr == NULL) return NULL;
    Key currKey = curr->getKey(); 
    if (currKey == key) return curr; 
    if (currKey < key) return internalFinder(key, curr->getRight());
    else return internalFinder(key, curr->getLeft());
}


/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return balanced(root_); 

}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanced(Node<Key, Value>* root) const {
    if (root == NULL) return true;
    if (height(root) == -1) return false;
    else return (balanced(root->getLeft()) && balanced(root->getRight())); 
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* root) const {
    // Credit CP Lin
    if (root == NULL) return 0;
    int leftHeight = height(root->getLeft());
    int rightHeight = height(root->getRight());
    int heightDiff = abs(leftHeight - rightHeight);
    if (heightDiff > 1) return -1; 
    return (max(leftHeight, rightHeight) + 1); 
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
