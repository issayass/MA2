#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
using namespace std;


template <typename T>
struct Node {
public:
    T value;
    Node* left;
    Node* right;

    Node(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
};


template <typename T>
class BST {

protected:
    Node<T>* _root; 

    
    void addHelper(Node<T>* root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            }
            else {
                addHelper(root->left, val);
            }
        }
        else {
            if (!root->right) {
                root->right = new Node<T>(val);
            }
            else {
                addHelper(root->right, val);
            }
        }
    }

    
    void printInOrderHelper(Node<T>* root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

   
    int nodesCountHelper(Node<T>* root) {
        if (!root) {
            return 0;
        }
        else {
            return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
        }
    }

    
    int heightHelper(Node<T>* root) {
        if (!root) {
            return -1;
        }
        else {
            return 1 + max(heightHelper(root->left), heightHelper(root->right));
        }
    }

    
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == nullptr || current->right == nullptr) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    }
                    else {
                        parent->right = temp;
                    }
                }
                else {
                    this->_root = temp;
                }
            }
            else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
            deleteValueHelper(current, current->right, value);
    }

   
public:

    BST() : _root(nullptr) { } 

    
    ~BST() {
        destroyTree(this->_root);
    }

   
    void add(T val) {
        if (this->_root) {
            this->addHelper(this->_root, val);
        }
        else {
            this->_root = new Node<T>(val);
        }
    }

    void print() {
        printInOrderHelper(this->_root);
    }

    void printLevelOrder() {
        if (!this->_root) {
            cout << "The tree is empty." << endl;
            return;
        }

        queue<Node<T>*> q;
        q.push(this->_root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node<T>* current = q.front();
                q.pop();
                cout << current->value << endl;

                if (current->left)
                    q.push(current->left);
                if (current->right)
                    q.push(current->right);
            }
        }
    }

    int nodesCount() {
        return nodesCountHelper(this->_root);
    }

    int height() {
        return heightHelper(this->_root);
    }

    
    void printMaxPath() {
        vector<T> path;
        findMaxPath(this->_root, path);
        for (T val : path) {
            cout << val << ' ';
        }
        cout << endl;
    }

    bool deleteValue(T value) {
        return this->deleteValueHelper(nullptr, this->_root, value);
    }

   
    bool contains(T value) {
        return containsHelper(this->_root, value);
    }

private:
    void findMaxPath(Node<T>* root, vector<T>& path) {
        if (!root) return;

        vector<T> leftPath, rightPath;
        findMaxPath(root->left, leftPath);
        findMaxPath(root->right, rightPath);

        vector<T>& maxSubPath = (leftPath.size() > rightPath.size()) ? leftPath : rightPath;
        path = (maxSubPath.size() > path.size()) ? maxSubPath : path;

        path.insert(path.begin(), root->value);
    }

    bool containsHelper(Node<T>* root, T value) {
        if (!root) return false;
        if (root->value == value) return true;

        if (value < root->value)
            return containsHelper(root->left, value);
        else
            return containsHelper(root->right, value);
    }

    void destroyTree(Node<T>* root) {
        if (!root) return;

        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
};

#endif

