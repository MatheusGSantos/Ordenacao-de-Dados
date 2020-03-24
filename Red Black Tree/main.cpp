#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

using namespace std;

struct Node{
    char color; //r ou b
    int value;
    struct Node *parent,
                *left,
                *right;
};


void setColor(struct Node* n, char color)
{
    if(n == NULL)
        return;

    n->color = color;
}


char getColor(struct Node*n)
{
    if(!n)
        return 'b';
    return n->color;
}


void SwapColor(struct Node* a, struct Node* b)
{
    char aux = a->color;
    setColor(a, b->color);
    setColor(b, aux);
}


struct Node* new_node(int v)
{
    struct Node* n = new struct Node;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->color = 'r';
    n->value = v;
    return n;
}


struct Node* GetParent(struct Node* n)
{
    return n == NULL ? NULL : n->parent; //NULL para raiz e vazia, pai para os demais
}


struct Node* GetGrandParent(struct Node* n)
{
    return GetParent(GetParent(n)); //retorna avô do nó
}


void treeInsert(struct Node *&n, struct Node* n_node)
{
    if(!n)
    {
        n = n_node; //settando a raiz da árvore
        //cout << "Root is " << n_node->value << endl;
    }
    else
    {
        struct Node* aux = n;
        while(1)
        {
            if( n_node->value > aux->value ) //caso valor seja maior que o valor do nó atual, vá para a direita
            {
                if( aux->right )
                {
                    //cout << "Went to the right\n";
                    aux = aux->right;
                }
                else
                {
                    aux->right = n_node;
                    n_node->parent = aux;
                    //cout << "Added " << n_node->value << " to the right of " << n_node->parent->value << endl;
                    break;
                }
            }
            else    //caso contrário, vá para a esquerda
            {
                if( aux->left )
                {
                    //cout << "Went to the left\n";
                    aux = aux->left;
                }
                else
                {
                    aux->left = n_node;
                    n_node->parent = aux;
                    //cout << "Added " << n_node->value << " to the left of " << n_node->parent->value << endl;
                    break;
                }
            }
        }

    }
}


void RotateLeft(struct Node *&root, struct Node *&n)
{
    struct Node *right_child = n->right;
    n->right = right_child->left;

    if (n->right != NULL)
        n->right->parent = n;

    right_child->parent = GetParent(n);

    if (GetParent(n) == NULL)
        root = right_child;
    else if (n == n->parent->left)
        n->parent->left = right_child;
    else
        n->parent->right = right_child;

    right_child->left = n;
    n->parent = right_child;
}


void RotateRight(struct Node *&root, struct Node *&n) //igual ao RotateLeft, mas trocando os left por right
{
    struct Node *left_child = n->left;
    n->left = left_child->right;

    if (n->left != NULL)
        n->left->parent = n;

    left_child->parent = GetParent(n);

    if (n->parent == NULL)
        root = left_child;
    else if (n == n->parent->left)
        n->parent->left = left_child;
    else
        n->parent->right = left_child;

    left_child->right = n;
    n->parent = left_child;
}


void InsertRepair(struct Node *&root, struct Node *&n)
{
    struct Node *parent = NULL;
    struct Node *grandparent = NULL;
    while ( (n != root) && getColor(n) == 'r' && getColor(n->parent) == 'r')
    {
        parent = GetParent(n);
        grandparent = GetGrandParent(n);
        if (parent == grandparent->left) {
            struct Node *uncle = grandparent->right;
            if (getColor(uncle) == 'r') {
                setColor(uncle, 'b');
                setColor(parent, 'b');
                setColor(grandparent, 'r');
                n = grandparent;
            } else {
                if (n == parent->right) {
                    RotateLeft(root, parent);
                    n = parent;
                    parent = n->parent;
                }
                RotateRight(root, grandparent);
                SwapColor(parent, grandparent);
                n = parent;
            }
        } else {
            struct Node *uncle = grandparent->left;
            if (getColor(uncle) == 'r') {
                setColor(uncle, 'b');
                setColor(parent, 'b');
                setColor(grandparent, 'r');
                n = grandparent;
            } else {
                if (n == parent->left) {
                    RotateRight(root, parent);
                    n = parent;
                    parent = n->parent;
                }
                RotateLeft(root, grandparent);
                SwapColor(parent, grandparent);
                n = parent;
            }
        }
    }
    setColor(root, 'b');
}


void RBTree_Insert(struct Node *&n, struct Node *&n_node)
{
    //cout << "Insertion Process Start\n";
    treeInsert(n, n_node);
    InsertRepair(n, n_node);
    //cout << "Node color: "<< n_node->color << endl;
}


struct Node* Search(struct Node* root, int v)
{
    struct Node* aux = root;
    while(aux)
    {
        if(aux->value == v)
            return aux;
        else if(v > aux->value)
            aux = aux->right;
        else
            aux = aux->left;
    }
    return aux;
}


void Search_RBT(struct Node* root, int v)
{
    struct Node* found = Search(root, v);
    if(found)
    {
        cout <<  "Description\n{\nColor: " << found->color << endl;
        cout << "Value: " << found->value << endl;
        cout << "Parent: " << (found->parent == NULL ? -1: found->parent->value) << endl;
        cout << "Left: " << (found->left == NULL ? -1: found->left->value) << endl;
        cout << "Right: " << (found->right == NULL ? -1: found->right->value) << "\n}\n\n";
    }
    else
        cout << "Value not found: " << v << "\n\n";
}


int main() {
    srand (time(NULL));
    int rand_ar[MAX];
    cout << "Setting up the " << MAX << " element(s) array..." << endl;
    for(int i = 0; i<MAX; i++)
    {
        rand_ar[i] = rand() % MAX+30+1;
        //cout << rand_ar[i] << endl;
    }

    struct Node *root = NULL;
    cout << "Inserting nodes...\n";
    for(int i = 0; i<MAX; i++)
    {
        struct Node* n = new_node(rand_ar[i]);
        RBTree_Insert(root, n);
    }
    cout << "Finished inserting nodes\n\n";
    for(int j=0; j < MAX+30+1; j+=20000)
        Search_RBT(root, j);
    return 0;
}
