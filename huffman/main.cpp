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
typedef unsigned char byte;

//tree node
class node{
    public:
        unsigned frequency;
        byte character;
        node* left;
        node* right;
        
        node(int f, byte c){
            frequency = f;
            character = c;
            left = NULL;
            right = NULL;
        }

        ~node(){}
};


//writing a character into a file
void write_byte(ofstream file, char c)
{
    file.put(c);
}


/* Compression */
/*
node buildHuffmanTree(unsigned bytes[256])
{
    // priority queue < frequencia, identificador >
    priority_queue< 
        tuple <unsigned, byte>, 
        vector< tuple <unsigned, byte> >, 
        greater<tuple <unsigned, byte> > 
        > pq;

    // dando enqueue
    for(int i=0; i < 256; i++)
    {
        if(bytes[i] != 0)
        {
            byte c;
            pq.push( make_tuple( bytes[i], c) );
        }
    }
    
    //return node();
}
*/



int main() {
    int operation = 0;
    setlocale(LC_ALL,"");
    if(operation == 0) //compression
    {
        FILE* input_f = fopen("test.txt", "rb"); // test.txt contains utf-8 text
        //get every byte frequency
        byte c;
        unsigned bytes[256] = {0};
        int temp;
        //char c2;
        /*while(*/fread(&c, sizeof(byte), 1, input_f);//)
        //{
            temp = c;
        //    bytes[temp]+= 1;
            printf("%d\n", temp);
        //}
        FILE* output_f = fopen("test_out.txt", "wb");
        fwrite(&c, 1, sizeof(c), output_f);
/*      
        for(int i =0; i<256; i++)
        {
            if(bytes[i] != 0)
            {
                cout << i << endl;
            }
        }
*/        
        //buildHuffmanTree(bytes);
        //node tree = buildHuffmanTree(wf);
    }
    
    //std::ofstream output;
    return 0;
}