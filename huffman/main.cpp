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
        unsigned char character;
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
unsigned char getByte(unsigned char buf[8])
{
    unsigned char byte = 0;
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
        unsigned char c;
        while( in.peek() != EOF ){
            c = in.get();
            bytes[c]+= 1;
            //cout << c << " : " << bytes[c] << endl;
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

        /* write byte frequency array into output file */
        FILE* fp_out = fopen("teste_c.bin", "wb");
        fwrite(&bytes, sizeof(bytes), 1, fp_out);
        //fclose(fp_out);

        /* start compression */
        //ofstream out("teste_c.bin", ios::app | ios::binary);
        unsigned char byte_buffer[8];
        int buf_index = 0;
        
        while ( in.peek() != EOF )
        {
            c = in.get();
            //cout << c << " read from file\n";
            int code_size = codes[c].size(); // huffman code size of the byte read
            for(int i = 0; i < code_size; i++)
            {
                byte_buffer[buf_index++] = codes[c][i];
                cout << codes[c][i] << " bit evaluated\n";
                if(buf_index == 8)
                {
                    buf_index = 0;
                    // write byte
                    unsigned char w_byte = getByte(byte_buffer);
                    fwrite(&w_byte, sizeof(w_byte), 1, fp_out);
                }
            }
        }
        /* completing the last byte */
        while ( buf_index < 8 )
            byte_buffer[buf_index++] = '0';
        if(buf_index == 8)
        {
            buf_index = 0;
            // write byte
            unsigned char w_byte = getByte(byte_buffer);
            fwrite(&w_byte, sizeof(w_byte), 1, fp_out);
        }
        in.close();
        fclose(fp_out);
        //out.close();

        cout << "Finished compression.\n";
    }
    else    // decompression
    {
        FILE* fp = fopen("teste_c.bin", "rb");

        /* get every byte frequency */
        unsigned bytes[256] = {0};
        fread(&bytes, sizeof(bytes), 1, fp);
        int code_start = ftell(fp);
        fclose(fp);

        /* continue reading file */
        ifstream in("teste_c.bin", ios::in | ios::binary);
        in.seekg(code_start);

        /* build the huffman tree */
        node* tree = buildHuffmanTree(bytes);

        /* start decompression */
        unsigned char r_byte;
        ofstream out("teste_d.bin", ios::out | ios::binary);
        
        while(in.peek() != EOF)
        {
            r_byte = in.get();
            unsigned char comparator = 128;
            node* aux = tree;

            for(int i = 0; i < 8; i++)
            {
                if(!(aux->left) && !(aux->right))
                {
                    aux = tree;
                    out.put(aux->character);
                    cout << aux->character << " in the file\n";
                }
                if(r_byte & (comparator >> i) ) // bit = 1, direita
                {
                    aux = aux->right;
                }
                else    //bit = 0
                {
                    aux = aux->left;
                }
            }
        }
        in.close();
        out.close();
        
    }
    
    
    return 0;
}

// MUDAR TODOS OS CHAR PARA UNSIGNED CHAR

/*
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int main() {
    ofstream out("test_out.bin", ios::out | ios::binary);
    unsigned char c = 129;
    unsigned int arr[256] = {0};
    arr[c]++;
    out << c;
    out.close();
    FILE* fp = fopen("test_out.bin", "rb");
    unsigned char b;
    fscanf(fp, "%c", &b);
    arr[b]++;
    cout << arr[b] << endl;
}
*/