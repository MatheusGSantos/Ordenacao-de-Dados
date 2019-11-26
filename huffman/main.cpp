#include <iostream>
#include <queue>
#include <fstream>
#include <locale>
#include <tuple>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class node{
    public:
        unsigned frequency;
        wchar_t character;
        node* left;
        node* right;
        
        node(int f, wchar_t c){
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

/*

Compression

*/

node buildHuffmanTree(unsigned bytes[256])
{
    // priority queue < frequencia, identificador >
    priority_queue< 
        tuple <unsigned, wchar_t>, 
        vector< tuple <unsigned, wchar_t> >, 
        greater<tuple <unsigned, wchar_t> > 
        > pq;

    // dando enqueue
    for(int i=0; i < 256; i++)
    {
        if(bytes[i] != 0)
        {
            wchar_t c;
            pq.push( make_tuple( bytes[i], c) );
        }
    }
    
    //return node();
}




int main() {
    int operation = 0;
    // read UNICODE
    locale::global(std::locale("")); // activate user-preferred locale

    if(operation == 0) //compression
    {
        wifstream wf("test.txt", ios::in | ios::binary); // test.txt contains utf-8 text
        //get every byte frequency
        wchar_t c;
        unsigned bytes[256] = {0};
        while(wf.get(c))
            bytes[c]+= 1;
        
        //buildHuffmanTree(bytes);
        //node tree = buildHuffmanTree(wf);
    }
    
    //std::ofstream output;

}