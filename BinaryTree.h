//
//  BinaryTree.h
//  BinaryTreeEx
//
//  Created by Anders Akesson on 2/6/13.
//  Copyright (c) 2013 Anders Akesson. All rights reserved.
//

#ifndef BinaryTreeEx_BinaryTree_h
#define BinaryTreeEx_BinaryTree_h
using namespace std;

template<typename T>
class BinaryTree
{
private:
    class TreeNode
    {
        friend class BinaryTree;
        T value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(T value1, TreeNode* left1 = NULL, TreeNode* right1 = NULL)
        {
            value = value1;
            left = left1;
            right = right1;
        }
        
    };
    TreeNode* root;

        // helper member functions
    void insertNode(TreeNode*&, T);
    void destroySubtree(TreeNode*);
    void remove(TreeNode*&, T);
    void makeDeletion(TreeNode*&);
    void displayInOrder(TreeNode*) const;
    void displayPreOrder(TreeNode*) const;
    void displayPostOrder(TreeNode*) const;
    
    public:
    BinaryTree();
    void insert(T value);
    bool search(T value) const;
    void remove(T value);
    void showInOrder(void) const;
    void showPreOrder() const;
    void showPostOrder() const;
    ~BinaryTree();
};
template<typename T>
void BinaryTree<T>::insertNode(TreeNode*& tree, T value)
{
    if (!tree)
    {
        tree = new TreeNode(value);
        return;
    }
    if (tree->value == value)
        return;
    
    if (value < tree->value)
    {
        insertNode(tree->left, value);
    }
    else
        insertNode(tree->right, value);
}
template<typename T>
void BinaryTree<T>::destroySubtree(TreeNode* tree)
{
    if (!tree)
        return;
    
    destroySubtree(tree->left);
    destroySubtree(tree->right);
    
        // delete the node at the root
    delete tree;
}
template<typename T>
void BinaryTree<T>::remove(TreeNode*& tree, T value)
{
    if (tree == NULL)
        return;
    
    if(value < tree->value)
        remove(tree->left, value);
    
    else if(value > tree->value)
        remove(tree->right, value);
    
    else
        makeDeletion(tree);
}

template<typename T>
void BinaryTree<T>::makeDeletion(TreeNode*& tree)
{
    TreeNode* nodeToDelete = tree;
    
    TreeNode* attachPoint;
    
    if (tree->right == NULL)
    {
            // replace tree with its left subtree
        tree = tree->left;
    }
    
    else if(tree->left == NULL)
    {
            // replace tree with its right subtree
        tree = tree->right;
    }
    else // the node has two children
    {
            // move to right subtree
        attachPoint = tree->right;
        
            // locate the smallest node in the right subtree
        while (attachPoint->left != NULL)
        {
            attachPoint = attachPoint->left;
        }
        
            // attach the left subtree of the original tree
            // as the left subtree of the smallest node in the right subtree
        attachPoint->left = tree->left;
        
            // replace the original tree with its right subtree
        tree = tree->right;
    }
        // delete root of the original tree
    delete nodeToDelete;
}

template<typename T>
void BinaryTree<T>::displayInOrder(TreeNode* tree) const
{
    if(tree)
    {
        displayInOrder(tree->left);
        cout << tree->value << "\t";
        displayInOrder(tree->right);
    }
}

template<typename T>
void BinaryTree<T>::displayPreOrder(TreeNode* tree) const
{
    if(tree)
    {
        cout << tree->value << "\t";
        displayPreOrder(tree->left);
        displayPreOrder(tree->right);
    }
}

template<typename T>
void BinaryTree<T>::displayPostOrder(TreeNode* tree) const
{
    if(tree)
    {
        displayPostOrder(tree->left);
        displayPostOrder(tree->right);
        cout << tree->value << "\t";
    }
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
    this->root = NULL;
}

template<typename T>
void BinaryTree<T>::insert(T value)
{
    insertNode(root, value);
}

template<typename T>
bool BinaryTree<T>::search(T value) const
{
    TreeNode* tree = root;
    
    while (tree)
    {
        if (tree->value == value)
            return true;
        
        else if(value < tree->value)
            tree = tree->right;
        
        else
            tree = tree->right;
    }
    return false;
}

template<typename T>
void BinaryTree<T>::remove(T value)
{
    remove(root, value);
}

template<typename T>
void BinaryTree<T>::showInOrder(void) const
{
    displayInOrder(root);
}

template<typename T>
void BinaryTree<T>::showPreOrder() const
{
    displayPreOrder(root);
}

template<typename T>
void BinaryTree<T>::showPostOrder() const
{
    displayPostOrder(root);
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
}

#endif
