#include <iostream>
#include <queue>
#include <fstream>

class node{
    public:
        int value;
        node* left;
        node* right;
        
        node(int v){
            value = v;
            left = NULL;
            right = NULL;
        }

        ~node(){}
};


// reading a character from file
char read_byte(std::ifstream file)
{
    return file.get();
}


//writing a character into a file
void write_byte(std::ofstream file, char c)
{
    file.put(c);
}


int main() {
    node *n0 = NULL;
    std::priority_queue<int> pq;
    std::ifstream arq;
    std::ofstream output;

}