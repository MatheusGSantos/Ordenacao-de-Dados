/* C++ Libraries*/
#include <iostream>
#include <queue>
#include <fstream>
#include <tuple>
#include <vector>

/* C Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;
//typedef unsigned char byte;

//tree node
class node{
    public:
        unsigned frequency;
        char character;
        node* left;
        node* right;
        
        node(){}
        ~node(){}
};

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
    // priority queue < frequencia, identificador > //mudar
    priority_queue<node*, vector< node* >, compare> pq;

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

    //build tree
    while (pq.size() > 1)   //enquanto a fila não estiver vazia
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




int main() {
    int operation = 0;
    //setlocale(LC_ALL,"");
    if(operation == 0) //compression
    {
        FILE* input_f = fopen("test.bin", "rb");
        //get every byte frequency
        //byte c;
        unsigned bytes[256] = {0};
        char c;

        while( fread(&c, sizeof(char), 1, input_f) == 1)
        {
            //printf("character: %c\n", c);
            bytes[c]+= 1;
        }
        fclose(input_f);
        
        node* tree = buildHuffmanTree(bytes);
        cout << tree->left->frequency << endl;

        FILE* output_f = fopen("test_out.txt", "wb");
        fwrite(&c, 1, sizeof(c), output_f);
    }
    
    cout << "end\n";
    //std::ofstream output;
    return 0;
}
