#ifndef YH_DSAAWS_AVL_TREE
#define YH_DSAAWS_AVL_TREE
#include <algorithm>

namespace weiss_solutions
{
    template <typename Comparable>
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable& ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ ele }, left{ lt }, right{ rt }, height{ h } {}

        AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ std::move(ele) }, left{ lt }, right{ rt }, height{0} { }

    };

    /* return -1 for nullptr */
    template <typename Comparable>
    int height(AvlNode<Comparable> *t)
    {
        return (t == nullptr) ? -1 : t->height;
    }

    template <typename Comparable>
    void insert(const Comparable & x, AvlNode<Comparable>* & t)
    {
        if (t == nullptr)
            t = new AvlNode(x, nullptr, nullptr);
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);

        balance(t);
    }

    constexpr int ALLOWED_IMBALANCE = 1;


    template <typename Comparable>
    void balance(AvlNode * & t)
    {
        if (t == nullptr) return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleRotateWithLeftChild(t);
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild();
            else
                doubleRotateWithRightChild();
        }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    template <typename Comparable>
    void rotateWithLeftChild(AvlNode<Comparable> * & root)
    {
        AvlNode<Comparable> *newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        root->height = std::max(height(root->left), height(root->right)) + 1;
        newRoot->height = std::max(height(newRoot->left), root->height) + 1;
        root = newRoot;
    }

    template <typename Comparable>
    void rotateWithRightChild(AvlNode<Comparable> * & root)
    {
        AvlNode<Comparable> *newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        root->height = std::max(height(root->left), height(root->right)) + 1;
        newRoot->height = std::max(height(newRoot->right), root->height) + 1;
        root = newRoot;
    }

    template <typename Comparable>
    void doubleRotateWithLeftChild(AvlNode<Comparable> * & root)
    {
        rotateWithRightChild(root->left);
        rotateWithLeftChild(root);
    }

    template <typename Comparable>
    void doubleRotateWithRightChild(AvlNode<Comparable> * & root)
    {
        rotateWithLeftChild(root->right);
        rotateWithRightChild(root);
    }
}

#endif
