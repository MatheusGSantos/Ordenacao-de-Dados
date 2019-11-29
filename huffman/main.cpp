/* C++ Libraries*/
#include <iostream>
#include <queue>
#include <fstream>
#include <tuple>
#include <vector>
#include <string>

/* C Libraries */
#include <stdio.h>
#include <stdlib.h>


using namespace std;



// tree node
class node{
    public:
        unsigned frequency;
        char character;
        node* left;
        node* right;
        
        node(){}
        ~node(){}
};


// classe para comparar os nós na priority queue
class compare{
    public:
        bool operator()(const node* n1, const node* n2) const{
            return n1->frequency > n2->frequency;
        }
};


//writing a character into a file
void write_byte(ofstream file, char c)
{
    file.put(c);
}


/* Compression */

node* buildHuffmanTree(unsigned bytes[256])
{
    priority_queue<node*, vector< node* >, compare> pq; // fila de prioridade
    // dando enqueue
    for(int i=0; i < 256; i++)
    {
        if(bytes[i] != 0)
        {
            node* n = (node*) malloc(sizeof(node));
            n->frequency = bytes[i];
            n->character = i;
            n->left = NULL;
            n->right = NULL;
            pq.push(n);
        }
    }
    int n = pq.size();

    //build tree
    for(int i = 0; i < (n-1); i++)   // tamanho de nós menos 1 vezes
    {
        node* z = (node*) malloc(sizeof(node));
        z->character = 0;
        z->left = pq.top(); pq.pop();
        z->right = pq.top(); pq.pop();
        z->frequency = z->left->frequency + z->right->frequency;
        //cout << pq.top()->frequency << " ," << pq.top()->character << " popped\n";
        pq.push(z);
    }
    
    return pq.top();
}


void getCodes(node* n, string (&c)[256], string buf)
{
    if( !(n->left) && !(n->right) )
    {
        c[n->character] = buf;
    }
    else
    {
        getCodes(n->left, c, buf+'0');
        getCodes(n->right, c, buf+'1');
    }
}


int main() {
    int operation = 0;

    if(operation == 0) //compression
    {
        ifstream file("test.bin", ios::in | ios::binary);

        /* get every byte frequency */
        unsigned bytes[256] = {0};
        char c;
        do
        {
            c = file.get();
            bytes[c]+= 1;
        } while( !file.eof() );
        file.close();
        /*
        for(int i = 0; i < 256; i++)
        {
            if(bytes[i] > 0)
                cout << i << " : " << bytes[i] << endl;
        }
        */
        node* tree = buildHuffmanTree(bytes);
        string codes[256];
        string buffer = "";
        getCodes(tree, codes, buffer);
        for(int i = 0; i < 256; i++)
        {
            if(codes[i] !=  "")
                cout << codes[i] << endl;
        }



        //cout << tree->left->frequency << endl;

        FILE* output_f = fopen("test_out.txt", "wb");
        fwrite(&c, 1, sizeof(c), output_f);
    }
    
    cout << "end\n";
    //std::ofstream output;
    return 0;
}
