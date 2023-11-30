#include "main.h"

// Huffman tree node abstract base class
int MAXSIZE;

class HuffNode
{
public:
    virtual ~HuffNode() {}     // Base destructor
    virtual int weight() = 0;  // Return frequency
    virtual bool isLeaf() = 0; // Determine type
    virtual int& height() = 0;
};
// Leaf node subclass
class LeafNode : public HuffNode
{
private:
    char it; // Value
    int wgt; // Weight
    int ht;
public:
    LeafNode(const char &val, int freq) // Constructor
    {
        it = val;
        wgt = freq;
        ht = 1;
    }
    int& height(){return ht;}
    int weight() { return wgt; }
    char val() { return it; }
    bool isLeaf() { return true; }
};
// Internal node subclass
class IntlNode : public HuffNode
{
private:
    HuffNode *lc; // Left child
    HuffNode *rc; // Right child
    int wgt;      // Subtree weight
    int ht;

public:
    IntlNode(HuffNode *l, HuffNode *r)
    {
        wgt = l->weight() + r->weight();
        lc = l;
        rc = r;
        ht = 1 + max(l->height(), r->height()); 
    }
    int weight() { return wgt; }
    int& height() {return ht;}
    bool isLeaf() { return false; }
    HuffNode *left() const { return lc; }
    void setLeft(HuffNode *b)
    {
        lc = (HuffNode *)b;
    }
    HuffNode *right() const { return rc; }
    void setRight(HuffNode *b)
    {
        rc = (HuffNode *)b;
    }
};
// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.

class HuffTree
{
private:
    HuffNode *Root; // Tree root
public:
    HuffTree(char &val, int freq) // Leaf constructor
    {
        Root = new LeafNode(val, freq);
    }
    // Internal node constructor
    int getBalance(HuffNode* node){
        if(node->isLeaf()) return 0;
        return height(((IntlNode*)node)->left()) - height(((IntlNode*)node)->right());
    }
    HuffTree(HuffTree *l, HuffTree *r)
    {
        Root = new IntlNode(l->root(), r->root());
        int balance = getBalance(Root);
        if(balance > 1){                    //lech trai
            // HuffNode* leftChild = ((IntlNode*) l->root())->left();
            if(getBalance(l->root()) >= 0){ //L-L
                Root = rightRotate(Root);
                Root->height() --;
            }
            else {
                l->Root = leftRotate(l->root());    //L-R
                l->Root->height()++;
                (((IntlNode*)l->Root)->left())->height()--;
                Root = rightRotate(Root);
                Root->height() --;
            }
        }
        else if(balance < -1){              //lech phai 
            if(getBalance(r->root()) <=0){  //R-R
                Root = leftRotate(Root);
                Root->height()--;
            }
            else {
                r->Root = rightRotate(r->root());   //R-L
                l->Root->height()++;
                (((IntlNode*)l->Root)->right())->height()--;
                Root = leftRotate(Root);
                Root->height()--;
            }
        }
        // UPDATE HEIGHT

    }
    ~HuffTree() {}                          // Destructor
    HuffNode *root() { return Root; }       // Get root
    int weight() { return Root->weight(); } // Root weight
    int height(HuffNode* node){             //get height of node 
        if(!node) return 0;
        return node->height();
    }
    void print(HuffNode* node){
        if(!node) return;
        cout<<node->weight()<<" ";
        if(node->isLeaf()) return;
        else{
           print(((IntlNode*)node)->left());
           print(((IntlNode*)node)->right());
        }
    }
    HuffNode *rightRotate(HuffNode *node)
    {
        if(!node) return 0;
        if(node->isLeaf()) return node;
        HuffNode* temp;
        HuffNode* lChild = ((IntlNode*)node)->left();
        if(!lChild->isLeaf()){
            temp = ((IntlNode*)lChild)->right();
        }
        ((IntlNode*)lChild)->setRight(node);
        ((IntlNode*)node)->setLeft(temp);
        return lChild;
    }
    HuffNode *leftRotate(HuffNode *node)
    {
        if(!node) return 0;
        if(node->isLeaf()) return node;
        HuffNode* temp;
        HuffNode* rChild = ((IntlNode*)node)->right();
        if(!rChild->isLeaf()){
            temp = ((IntlNode*)rChild)->left();
        }
        ((IntlNode*)rChild)->setLeft(node);
        ((IntlNode*)node)->setRight(temp);
        return rChild;
    }
};

// Build a Huffman tree from a collection of frequencies


// class BSTree
// {
//     BSTNode *root;
// public:
//     BSTNode *insert(BSTNode *node, int val)
//     {
//         if (!node)
//             return new BSTNode(val);
//         if (node->val < val)
//         {
//             node->right = insert(node->right, val);
//         }
//         else if (node->val > val)
//         {
//             node->left = insert(node->left, val);
//         }
//         return node;
//     }
//     void insert(int val){
//         root = insert(root, val);
//     }
//     // Function to calculate the factorial of a number
//     unsigned long long factorial(int num)
//     {
//         if (num == 0 || num == 1)
//         {
//             return 1;
//         }
//         else
//         {
//             return num * factorial(num - 1);
//         }
//     }

//     // Function to calculate n choose k (nCk)
//     unsigned long long nChooseK(int n, int k)
//     {
//         if (k < 0 || k > n)
//         {
//             return 0; // Invalid input, as k should be between 0 and n (inclusive)
//         }

//         // Calculate nCk using the factorial function
//         unsigned long long result = factorial(n) / (factorial(k) * factorial(n - k));
//         return result;
//     }

//     int count(vector<int>::iterator begin, int n)
//     {
//         if (n == 1 || n == 0)
//             return 1;
//         int i = 1;
//         for (; i < n; i++)
//         {
//             if (*(begin + i) > *begin)
//             {
//                 break;
//             }
//         }
//         int cnt = nChooseK(n - 1, i - 1);
//         return cnt * count(begin + 1, i - 1) * count(begin + i, n - i);
//     }
//     void preorder(vector<int> &v, BSTNode *root)
//     {
//         if (!root)
//             return;
//         v.push_back(root->val);
//         preorder(v, root->left);
//         preorder(v, root->right);
//     }
//     int countBST(BSTNode *root)
//     {
//         // TODO
//         vector<int> v;
//         preorder(v, root);
//         for (auto node : v)
//         {
//             cout << node << " ";
//         }
//         cout << endl;
//         return count(v.begin(), (int)v.size());
//     }
// };

// class BSTNode
// {
// public:
//     int val;
//     BSTNode *left;
//     BSTNode *right;
//     BSTNode()
//     {
//         this->left = this->right = nullptr;
//     }
//     BSTNode(int val)
//     {
//         this->val = val;
//         this->left = this->right = nullptr;
//     }
//     BSTNode(int val, BSTNode *&left, BSTNode *&right)
//     {
//         this->val = val;
//         this->left = left;
//         this->right = right;
//     }
// };

// class Restaurant
// {
// public:
//     virtual void insert(int result) = 0;
//     virtual void remove() = 0;
// };
// class Gojo : public Restaurant
// {
//     BSTree **area;
// public:
//     Gojo()
//     {
//         area = new BSTree *[MAXSIZE];
//     }
//     void insert(int result)
//     {
//         area[result % MAXSIZE + 1]->insert(result);
//     }
// };

// BSTTREE FOR KOKUSEN
