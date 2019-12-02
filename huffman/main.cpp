/* C++ Libraries*/
#include <iostream>
#include <queue>
#include <fstream>
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


class compare{
    public:
        bool operator()(const node* n1, const node* n2) const{
            return n1->frequency > n2->frequency;
        }
};


/* Compression */

// builds the huffman tree
node* buildHuffmanTree(unsigned bytes[256])
{
    priority_queue<node*, vector< node* >, compare> pq; // priority queue
    // enqueue
    for(int i=0; i < 256; i++)
    {
        if(bytes[i] != 0)
        {
            node* n = (node*) malloc(sizeof(node));
            n->frequency = bytes[i];
            n->character = i;
            n->left = NULL;
            n->right = NULL;
            //cout << "enqueueing: " << i << endl;
            pq.push(n);
        }
    }
    int n = pq.size();

    //build tree
    for(int i = 0; i < (n-1); i++)   // n_nodes - 1
    {
        node* z = (node*) malloc(sizeof(node));
        z->character = 0;
        z->left = pq.top(); pq.pop();
        z->right = pq.top(); pq.pop();
        z->frequency = z->left->frequency + z->right->frequency;
        //cout << z->frequency << " : " << z->character << ", left: { " << z->left->character << " : " << z->left->frequency << "}, right: { " << z->right->character<< " : " << z->right->frequency << "}"<< endl;
        pq.push(z);
    }
    
    return pq.top();
}


// prints the tree
void printTree(node* tree)
{
    if (!tree)
    {
        return;
    }
    
    cout << tree->character << " : " << tree->frequency << endl;
    printTree(tree->left);
    printTree(tree->right);
}


// gets the huffman code for every byte
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


// returns the byte equivalent to the byte sequence (bit manipulation)
char getByte(char buf[8])
{
    char byte = 0;
    for(int i = 0; i < 8; i++)
    {
        if (buf[7-i] == '1')
        {
            byte = (byte | (1 << i) );
        }
    }
    return byte;
}


int main() {
    int operation = 0;

    if(operation == 0) // compression
    {
        ifstream in("teste.bin", ios::in | ios::binary);

        /* get every byte frequency */
        unsigned bytes[256] = {0};
        char c;
        while( in.get(c) )
        {
            bytes[c]+= 1;
        }
        
        /* build the huffman tree */
        node* tree = buildHuffmanTree(bytes);

        /* get huffman code for every byte */
        string codes[256];
        string buffer = "";
        getCodes(tree, codes, buffer);

        /* parse the file and write the compressed bytes into output */
        in.clear(); // rewind
        in.seekg(0); // the file pointer
        ofstream out("teste_c.bin", ios::out | ios::binary);

        // write byte frequency array into output file
        for(int i = 0; i < 256; i++)
        {
            out << bytes[i];
        }
        char byte_buffer[8];
        int buf_index = 0;
        while (in.get(c))
        {
            int code_size = codes[c].size(); // huffman code size of the byte read
            for(int i = 0; i < code_size; i++)
            {
                byte_buffer[buf_index++] = codes[c][i]; 
                if(buf_index == 8)
                {
                    buf_index = 0;
                    // write byte
                    char w_byte = getByte(byte_buffer);
                    out.write(&w_byte,1);
                }
            }
        }
        // completing the last byte
        while ( buf_index < 8 )
            byte_buffer[buf_index++] = '0';
        if(buf_index == 8)
        {
            buf_index = 0;
            // write byte
            char w_byte = getByte(byte_buffer);
            out.write(&w_byte,1);
        }
        in.close();
        out.close();

        cout << "Finished compression.\n";
    }
    else    // decompression
    {
        ifstream in("teste_c.bin", ios::in | ios::binary);
        
        /* get every byte frequency */
        unsigned bytes[256] = {0};
        char c;
        for(int i = 0; i < 256; i++)
        {
            in.get(c);
            bytes[i] = (unsigned) atoi(&c);
        }
        /* build the huffman tree */
        node* tree = buildHuffmanTree(bytes);
        
    }
    
    
    return 0;
}
