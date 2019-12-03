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


// returns the accumulative sum of frequencies
unsigned int getMaxNFreq(unsigned b[256])
{
    unsigned long int f_sum = 0;     
    for(int i = 0; i < 256; i++)
    {
        f_sum+=b[i];
    }
    return f_sum;
}


int main() {
    int operation = 1;
    if(operation == 0) // compression
    {
        ifstream in("teste.bin", ios::in | ios::binary);

        /* get every byte frequency */
        unsigned bytes[256] = {0};
        unsigned char c;
        while( in.peek() != EOF ){
            c = in.get();
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

        /* write byte frequency array into output file */
        FILE* fp_out = fopen("teste_c.bin", "wb");
        for(int i = 0; i < 256; i++) fwrite(&bytes[i], sizeof(unsigned), 1, fp_out);

        /* start compression */
        unsigned char byte_buffer[8];
        int buf_index = 0;
        
        while ( in.peek() != EOF )
        {
            c = in.get();
            int code_size = codes[c].size(); // huffman code size of the byte read
            for(int i = 0; i < code_size; i++)
            {
                byte_buffer[buf_index++] = codes[c][i];
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

        cout << "Finished compression.\n";
    }
    else    // decompression
    {
        FILE* fp = fopen("teste_c.bin", "rb");

        /* get every byte frequency */
        unsigned bytes[256] = {0};
        for(int i = 0; i < 256; i++) fread(&bytes[i], sizeof(unsigned), 1, fp);
        int code_start = ftell(fp);
        fclose(fp);

        /* continue reading file */
        ifstream in("teste_c.bin", ios::in | ios::binary);
        in.seekg(code_start);

        /* build the huffman tree */
        node* tree = buildHuffmanTree(bytes);

        /* start decompression */
        unsigned char r_byte;
        FILE* out = fopen("teste_d.bin", "wb");
        
        const unsigned long max_n_bytes = getMaxNFreq(bytes);
        unsigned long counted = 0;
        while(in.peek() != EOF)
        {
            r_byte = in.get();
            unsigned char comparator = 128;
            node* aux = tree;

            for(int i = 0; i < 8; i++)
            {
                if(!(aux->left) && !(aux->right))
                {
                    fwrite(&(aux->character), sizeof(aux->character), 1, out);
                    aux = tree;
                    counted++;
                    if(counted == max_n_bytes) break;
                    
                }
                if( r_byte & (comparator >> i) ) // bit = 1, direita
                {
                    aux = aux->right;
                }
                else    // bit = 0, esquerda
                {
                    aux = aux->left;
                }
            }
        }
        in.close();
        fclose(out);
        cout << "Finished decompression.\n";
    }

    return 0;
}
