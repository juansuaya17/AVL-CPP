#include <iostream>
using namespace std;

template <class T>
class AVL{
    public:
        AVL (int (*compareNodes) (T* , T*)){
            root = NULL;
            cantElem = 0;
            deleteValues = false;
            this -> compareNodes = compareNodes;
        }

        ~AVL (){
            deleteTree(root);
        }

       int size(){
            return cantElem;
        }

        bool isEmpty(){
            return size() == 0;
        }

        bool contains(T * value){
            return contains(root , value);
        }
        
        bool insert(T * value){
            if(value == NULL) return false; // can't insert
            if(!contains(value)){
                root = insert(root , value);
                cantElem ++;
                return true; // was able to insert 
            }
            return false; // already exists in tree
        }

        bool remove (T * value){
            if(value == NULL) return false;
            if(contains(value)){
                root = remove(root , value);
                cantElem --;
                return true;
            }
            return false;
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
        int (*compareNodes) (T* , T*);
        
        bool deleteValues;

        void deleteTree(Node & node){
            if(node == NULL) return;
            deleteTree(node -> left);
            deleteTree(node -> right);
            if(deleteValues) delete node -> val;
            delete node;
        }

        bool contains(Node * node , T * value){
            if(node == NULL) return false;
            int compare = compareNodes(value , node -> val);
            if(compare == -1) {
                return contains(node -> left , value); // value is less than node, search left subtree
            }else if (compare == 1){
                return contains(node -> right , value); // value is greater than node, search right subtree
            }
            return true; // value equals node. Return true
        }

        Node *  insert (Node * node , T * value){
            if(node == NULL) return new Node(value , NULL , NULL);

            int compare (value , node -> val);

            if(compare == -1) {
                return insert (node -> left , value);
            }else{
                return insert (node -> right , value);
            }

            update (node);

            return balance (node);
        }

        int max (int a , int b){
            if(a > b) return a;
            return b;
        }

        // if null, we put null so that they cancel out with the +1, and height can be zero if node has no subTrees.
        void update (Node * node){
            int leftNodeHeight = (node -> left == NULL) ? : -1 , node -> left -> height; 
            int rightNodeHeight = (node -> right == NULL) ? : -1 , node -> right -> height;

            node -> height = 1 + max (leftNodeHeight , rightNodeHeight); // actual node's height
            node -> bf = rightNodeHeight - leftNodeHeight; // update balance factor
        }

        Node * balance (Node * node) {
            if(node -> bf == -2){

                if(node -> left != NULL && node -> left -> bf <= 0){    
                    return leftLeftCase(node); // left left rotation case
                }else{
                    return leftRightCase (node); // left right rotation case
                }
            
            }else if (node -> bf == 2){

                if(node -> right != NULL && node -> right -> bf >= 0){
                    return rightRightCase (node); // right right rotation case
                }else{
                    return rightLeftCase (node); // right left rotation case
                }

            }

            return node; // this means balance factor is -1 , 0 , 1. Which is okey
        }

        // simple Rotations: 
        Node * leftLeftCase (Node * node){
            return rightRotation (node);
        }

        Node * rightRightCase (Node * node){
            return leftRotation (node);
        }

        // complex Rotations: 
        Node * leftRightCase (Node * node){
            node -> left = leftRotation(node -> left);
            return leftLeftCase (node);
        }
       
        Node * rightLeftCase (Node * node){
            node -> right = rightRotation(node -> right);
            return rightRightCase (node);
        }

        Node * rightRotation (Node * node){
            Node * new_root = node -> left;
            node -> left = new_root -> right;
            new_root -> right = node;
            update (node);
            update (new_root);
            return new_root;
        }

        Node * leftRotation (Node * node){
            Node * new_root = node -> right;
            node -> right = new_root -> left;
            new_root -> left = node;
            update (node);
            update (new_root);
            return new_root;
        }

        Node * remove (Node * node , T * value){
            if (node == NULL) return ;

            int compare = compareNodes(value , node -> val);
            if(compare == -1 ){
                 return remove (node -> left , value);
            }else if (compare == 1){
                return remove (node -> right , value);
            }else if (node -> right == NULL || node -> left == NULL){
                Node * ret = node;
                if(node -> left == NULL){
                    ret = node -> right;
                }else if (node -> right == NULL){
                    ret = node -> left;
                }
                if(deleteValues) delete node -> value;
                delete node;
                return ret;
            }else{
                bool changeDelMethod = false;
                if(deleteValues) deleteValues = false; changeDelMethod = true;

                if(node -> left -> height < node -> right -> height){
                    Node * max_node = maximum(node -> left);
                    delete node -> val;
                    node -> val = max_node -> val;
                    node -> left = remove (node -> left , max_node -> val);
                }else{
                    Node * min_node = minimum(node -> right);
                    delete node -> val;
                    node -> val = min_node -> val;
                    node -> right = remove (node -> right , min_node -> val);
                }
                if(changeDelMethod) deleteValues = true;
            }
            
            update (node);
            return balance (node);
        }

        Node * minimum (Node * node){
            Node * ret = node;
            while(ret -> left != NULL){
                ret = ret -> left;
            }
            return ret;
        }

        Node * maximum (Node * node){
            Node * ret = node;
            while(ret -> right != NULL){
                ret = ret -> right;
            }
            return ret;
        }

};