#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>


std::ifstream in("mergeheap.in");
std::ofstream out("mergeheap.out");

struct Node
{
    Node(int key) : key(key), left(nullptr), right(nullptr), next(nullptr), rank(0) 
    {
        rank = 0;
    }

    int key;
    Node* left;
    Node* right;
    int rank;
    Node* next;
};


class RankPairingHeap {

public:

    RankPairingHeap() : root(nullptr), last(nullptr){}

    void insert(int cheie) 
    {

        Node* node = new Node(cheie);

        if (root == nullptr)
        {
            root = node;
            last = node;
        }
        else
        {
            if (root->key < node->key)
            {
                node->next = root;
                root = node;
            }
            else
            {
                last->next = node;
                last = node;
                node->next = nullptr;
            }
        }
    }

    void insert(Node* node)
    {
        if (root == nullptr)
        {
            root = node;
            last = node;
        }
        else
        {
            if (root->key < node->key)
            {
                node->next = root;
                root = node;
            }
            else
            {
                last->next = node;
                last = node;
                node->next = nullptr;
            }
        }
    }

    void clearRoot()
    {
        root = nullptr;
    }

    Node* getRoot()
    {
        return root;
    }
    
    int pop()
    {
        int key = root->key;

        Node* new_node = root;

        if (root->left != nullptr)
        {
            root = root->left;
        }
        else
            root = root->next;

        if (root != nullptr)
            mergeTrees();

        delete new_node;

        return key;
    }
   
    bool empty()
    {
        return root == nullptr;
    }


    void printTree(Node* node)
    {
        if (node != nullptr)
        {

            std::cout << node->key << " " << node->rank << std::endl;

            printTree(node->left);
            printTree(node->right);
        }
    }

    void printHeap()
    {
       for (Node* new_root = root; new_root != nullptr; )
        {
            printTree(new_root);
            std::cout << std::endl;
            new_root = new_root->next;
        }
       if (root != nullptr)
           std::cout << "root: " << root->key << "  last: " << last->key << std::endl;

    }

    void mergeTrees() 
    {
        if(root != nullptr)
            while (root->next != nullptr)
            {
                root = merge_trees(root, root->next);
            }
        last = root;
    }

    Node* merge_trees(Node* x, Node* y)
    {

        if (x == nullptr)
        {
            return y;
        }
        if (y == nullptr)
        {
            return x;
        }
        if (y->key < x->key)
        {
            y->right = x->left;
            x->left = y;
            x->next = y->next;
            y->next = nullptr;
            x->right = nullptr;
            
            y->rank = std::max(x->rank,y->rank);
            x->rank = y->rank + 1;

            if (y->left == nullptr)
                std::swap(y->left, y->right);

            if (y->left != nullptr)
            {

                for (Node* stanga = y; stanga != nullptr;)
                {

                    if (stanga->left != nullptr)
                    {
                        Node* child = stanga->left;
                        if (child->key > stanga->key)
                        {
                            std::swap(child->key, stanga->key);
                            stanga = child;
                            continue;
                        }
                    }
                    break;
                }
            }


            return x;
        }
        else
        {
            x->right = y->left;
            y->left = x;
            x->next = nullptr;
            y->right = nullptr;
            
            x->rank = std::max(x->rank,y->rank);
            y->rank = x->rank + 1;

            if(x->left == nullptr)
                std::swap(x->left, x->right);

            if (x->left != nullptr)
            {
                for (Node* stanga = x; stanga != nullptr;)
                {
                    if (stanga->left != nullptr)
                    {
                        Node* child = stanga->left;
                        if (child->key > stanga->key)
                        {
                            std::swap(child->key, stanga->key);
                            stanga = stanga->left;
                            continue;
                        }
                        break;
                    }
                }
            }


            return y;
        }
    }

    

private:
    
    Node* root;
    Node* last;

};


void insertInHeap(RankPairingHeap heaps[])
{
    int m, x;
    in >> m >> x;


    if (x == 36)
    {
        x++;
        x--;
    }

    heaps[m].insert(x);
}

void printdinHeap(RankPairingHeap heaps[])
{
    int m;
    in >> m;
    out << heaps[m].pop() << std::endl;
}

void mergeHeaps(RankPairingHeap heaps[])
{

    int a, b;
    in >> a >> b;

    heaps[b].mergeTrees();


    Node* b_root = heaps[b].getRoot();


    heaps[a].insert(b_root);

    heaps[a].mergeTrees();

    heaps[b].clearRoot();
}

int main()
{
    int n, q;

    in >> n >> q;

    RankPairingHeap heaps[201];

    for (int i = 0; i < q; i++)
    {
        int op;
        in >> op;



        std::cout << "operatia" << i << std::endl;


        for (int j = 1; j <= n; j++)
        {
            std::cout << "heap-ul " << j << std::endl;
            heaps[j].printHeap();
        }

        switch (op)
        {
        case 1:
            insertInHeap(heaps);
            break;
        case 2:
            printdinHeap(heaps);
            break;
        case 3:
            mergeHeaps(heaps);
            break;
        }

    }

}
