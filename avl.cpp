#include <iostream>
using namespace std;

template <class T>
class AVL{
    public:
        AVL (){
            root = NULL;
            cantElem = 0;
            deleteValues = false;
        }

        ~AVL (){
            deleteTree(root);
        }

        


        void changeDelete (bool deleteAll){
            deleteValues = deleteAll;
        }

    private:

        struct Node{
            T * val;
            int bf;
            int height;
            Node * left;
            Node * right;
            Node(T * val , Node * left , Node * right):val(val) , left(left) , right(right) , height(0) , bf(0){}
        };

        int cantElem;
        Node * root;

        bool deleteValues;

        void deleteTree(Node & node){
            if(node == NULL) return;
            deleteTree(node -> left);
            deleteTree(node -> right);
            if(deleteValues) delete node -> val;
            delete node;
        }
};