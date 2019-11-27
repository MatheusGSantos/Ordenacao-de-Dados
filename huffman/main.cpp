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
        
        node(int f, char c){
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

node buildHuffmanTree(unsigned bytes[256])
{
    // priority queue < frequencia, identificador > //mudar
    priority_queue< 
        tuple <unsigned, char>, 
        vector< tuple <unsigned, char> >, 
        greater< tuple <unsigned, char> > 
        > pq;

    // dando enqueue    //mudar
    for(int i=0; i < 256; i++)
    {
        if(bytes[i] != 0)
        {
            pq.push( make_tuple( bytes[i], (char) i ) );
        }
    }

    //build tree
    while (pq.size())   //enquanto a fila não estiver vazia
    {
        node z(0,0);    //mudar
        tuple <unsigned, char> temp = pq.top();
        pq.pop();
        cout << get<0>(temp) << " ," << get<1>(temp) << "popped\n";
    }    
    
    //return node();
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
        

/*      
        for(int i =0; i<256; i++)
        {
            if(bytes[i] != 0)
            {
                cout << i << endl;
            }
        }
*/        
        buildHuffmanTree(bytes);
        //node tree = buildHuffmanTree(wf);
        FILE* output_f = fopen("test_out.txt", "wb");
        fwrite(&c, 1, sizeof(c), output_f);
    }
    
    //std::ofstream output;
    return 0;
}
