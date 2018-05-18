#ifndef YH_DSAAWS_AVL_TREE
#define YH_DSAAWS_AVL_TREE
#include <algorithm>

namespace weiss_solutions
{
    template <typename Comparable>
    class AvlTree
    {
    private:
        static constexpr int ALLOWED_IMBALANCE = 1;
        struct AvlNode
        {
            Comparable element;
            AvlNode *left;
            AvlNode *right;
            int height;

            AvlNode(const Comparable& ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ ele }, left{ lt }, right{ rt }, height{ h } { }


            AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ std::move(ele) }, left{ lt }, right{ rt }, height{ 0 }
            {
            }

        };

        /* return -1 for nullptr */
        int height(AvlNode *t)
        {
            return (t == nullptr) ? -1 : t->height;
        }

        void insert(const Comparable & x, AvlNode & t)
        {
            if (t == nullptr)
                t = new AvlNode(x, nullptr, nullptr);
            else if (x < t->element)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);

            balance(t);
        }

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

        void rotateWithLeftChild(AvlNode * & root)
        {
            AvlNode *newRoot = root->left;
            root->left = newRoot->right;
            newRoot->right = root;
            root->height = std::max(height(root->left), height(root->right)) + 1;
            newRoot->height = std::max(height(newRoot->left), root->height) + 1;
            root = newRoot;
        }

        void rotateWithRightChild(AvlNode * & root)
        {
            AvlNode *newRoot = root->right;
            root->right = newRoot->left;
            newRoot->left = root;
            root->height = std::max(height(root->left), height(root->right)) + 1;
            newRoot->height = std::max(height(newRoot->right), root->height) + 1;
            root = newRoot;
        }

        void doubleRotateWithLeftChild(AvlNode * & root)
        {
            rotateWithRightChild(root->left);
            rotateWithLeftChild(root);
        }
        void doubleRotateWithRightChild(AvlNode * & root)
        {
            rotateWithLeftChild(root->right);
            rotateWithRightChild(root);
        }

        void remove(const Comparable & x, AvlNode * & t)
        {
            if (t == nullptr)
                return;

            if (x < t->element)
                remove(x, t->left);
            else if (t->element < x)
                remove(x, t->right);
            else if (t->left != nullptr && t->right != nullptr)
            {
                t->element = findMin(t->right)->element;
                remove(t->element, t->right);
            }
            else
            {
                AvlNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }

            balance(t);
        }
    };
}

#endif
