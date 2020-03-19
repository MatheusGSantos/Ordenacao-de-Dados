#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX 5

using namespace std;

//ok
struct Node{
    char color; //r ou b
    int value;
    struct Node *parent,
                *left,
                *right;
};


void setColor(struct Node* n, char color) //ok
{
    if(n == NULL)
        return;

    n->color = color;
}


void SwapColor(struct Node* a, struct Node* b) //ok
{
    char aux = a->color;
    setColor(a, b->color);
    setColor(b, aux);
}

struct Node* new_node(int v) //ok
{
    struct Node* n = new struct Node;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->color = 'r';
    n->value = v;
    return n;
}


struct Node* GetParent(struct Node* n) //ok
{
    return n == NULL ? NULL : n->parent; //NULL para raiz e vazia, pai para os demais
}


struct Node* GetGrandParent(struct Node* n) //ok
{
    return GetParent(GetParent(n)); //retorna avô do nó
}


void treeInsert(struct Node *&n, struct Node* n_node) //ok
{
    if(!n)
    {
        n = n_node; //settando a raiz da árvore
        cout << "Root is " << n_node->value << endl;
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
                    cout << "Went to the right\n";
                    aux = aux->right;
                }
                else
                {
                    aux->right = n_node;
                    n_node->parent = aux;
                    cout << "Added " << n_node->value << " to the right of " << n_node->parent->value << endl;
                    break;
                }
            }
            else    //caso contrário, vá para a esquerda
            {
                if( aux->left )
                {
                    cout << "Went to the left\n";
                    aux = aux->left;
                }
                else
                {
                    aux->left = n_node;
                    n_node->parent = aux;
                    cout << "Added " << n_node->value << " to the left of " << n_node->parent->value << endl;
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
    while ( (n != root) && n->color == 'r' && n->parent->color == 'r')
    {
        parent = GetParent(n);
        grandparent = GetGrandParent(n);
        if (parent == grandparent->left) {
            struct Node *uncle = grandparent->right;
            if (uncle->color == 'r') {
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
            if (uncle->color == 'r') {
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
    cout << "Insertion Process Start\n";
    treeInsert(n, n_node);
    InsertRepair(n, n_node);
    cout << "Node color: "<< n_node->color << endl;
}


int main() {
    srand (time(NULL));
    int rand_ar[MAX];
    for(int i = 0; i<MAX; i++)
    {
        rand_ar[i] = rand() % MAX+30+1;
        cout << rand_ar[i] << endl;
    }

    struct Node *root = NULL;
    for(int i = 0; i<MAX; i++)
    {
        struct Node* n = new_node(rand_ar[i]);
        RBTree_Insert(root, n);
    }

    return 0;
}
