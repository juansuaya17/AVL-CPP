#include <iostream>
using namespace std;

template <class T>
class AVL{
    public:

    private:

        struct Node{
            T * val;
            int bf;
            int height;
            Node * left;
            Node * right;
            Node(T * val , Node * left , Node * right):val(val) , left(left) , right(right) , height(0) , bf(0){}
        };

        

};