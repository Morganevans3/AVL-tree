//
// Created by Morgan Evans on 9/29/23.
//

#include <iostream>
#include <vector>
using namespace std;

class avl {
    struct Node {
        string name;
        int id;
        Node* left;
        Node* right;
    };

    Node* root;
public:


    avl();
    ~avl();
    void recursive_delete(Node*& node);
    int balance_factor(Node* node);
    Node* insert(Node* node, string name, int id);
    Node* remove(Node* node, int id, bool& success);
    Node* remove_successor(Node* node);
    Node* l_rotation(Node* node);
    Node* r_rotation(Node* node);
    Node* rl_rotation(Node* node);
    Node* lr_rotation(Node* node);
    bool search_id(Node* node, int id);
    bool search_name(Node* node, string name, bool& found);
    void inorder(Node* node, vector<int>& vec, bool& print, bool& comma);
    void preorder(Node* node, bool& comma);
    void postorder(Node* node, bool& comma);
    int level_count(Node* node);
    //void remove_inorder(Node*& node, int n, vector<int>& vec);
    Node* get_root();
    void set_root(Node* node);


};


