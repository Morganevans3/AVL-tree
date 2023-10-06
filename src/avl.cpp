//
// Created by Morgan Evans on 9/29/23.
//
#include <iostream>
#include <vector>
#include "avl.h"
using namespace std;

avl::avl() {
    // constructor
    this->root = nullptr;
}

avl::~avl() {
    // destructor
    if (root != nullptr) {
        recursive_delete(root);
    }

    root = nullptr;
}

void avl::recursive_delete(Node*& node) {
    // recursively deletes the entire tree for the destructor
    if (node != nullptr) {
        recursive_delete(node->left);
        recursive_delete(node->right);
        delete node;
        node = nullptr;
    }
}

int avl::balance_factor(Node* node) {
    // used project 1 breakdown
    // left - right on the tree
    // will never be greater than 2
    return level_count(node->left) - level_count(node->right);
}

avl::Node* avl::insert(Node* node, string name, int id) {
    // passes in string and id entered in
    if (node == nullptr) {
        Node* new_node = new Node();
        new_node->name = name;
        new_node->id = id;
        new_node->left = nullptr;
        new_node->right = nullptr;

        if (root == nullptr) {
            // set root with info passed in
            root = new_node;
        }

        cout << "successful" << endl;
        return new_node;
    }

    if (id < node->id) {
        // recursively find where to insert it
        // inserts on the left
        node->left = insert(node->left, name, id);
    }

    else if (id > node->id) {
        // inserts on the right side
        node->right = insert(node->right, name, id);
    }

    else {
        // if id is already in the tree
        cout << "unsuccessful" << endl;
    }

    /*
     * from lecture slides
    IF tree is right heavy {
        IF tree's right subtree is left heavy {
            (parent = -2 and child = +1)
            Perform Right Left rotation & update height }
        ELSE {
            (parent = -2 and child = -1)
            Perform Left rotation & update height }
    }
    ELSE IF tree is left heavy {
        IF tree's left subtree is right heavy {
            (parent = +2 and child = -1)
            Perform Left Right rotation & update height }
        ELSE {
            (parent = +2 and child = +1)
            Perform Right rotation & update height }
    }

     */
    if (balance_factor(node) == -2 && balance_factor(node->right) == 1) {
        node = rl_rotation(node);
    }

    else if (balance_factor(node) == -2 && balance_factor(node->right) == -1) {
        node = l_rotation(node);
    }

    else if (balance_factor(node) == 2 && balance_factor(node->left) == -1) {
        node = lr_rotation(node);
    }

    else if (balance_factor(node) == 2 && balance_factor(node->left) == 1) {
        node = r_rotation(node);
    }

    return node;
}

avl::Node* avl::remove(Node* node, int id, bool& success) {
    // removes node based only on id
    // used project 1 breakdown
    if (node == nullptr) {
        if (!success) {
            cout << "unsuccessful" << endl;
            success = true;
        }
        return node;
    }

    else if (node->id == id) {
        // if node to remove
        if (!success) {
            cout << "successful" << endl;
            success = true;
        }

        if (node->left == nullptr || node->right == nullptr) {
            // if node has 0 or 1 child
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        }

        else {
            // if there are both a left and a right node
            Node* temp = remove_successor(node->right);

            node->id = temp->id;
            node->name = temp->name;
            //delete temp;
            node->right = remove(node->right, temp->id, success);
        }
    }

    else if (id < node->id) {
        // check left
        node->left = remove(node->left, id, success);
    }

    else {
        // check right
        node->right = remove(node->right, id, success);
    }


    if (!success ) {
        success = !success;
        cout << "unsuccessful" << endl;
    }

    return node;
}

avl::Node* avl::remove_successor(Node* node) {
    Node* curr = node;
    while (curr->left != nullptr)
        curr = curr->left;
    return curr;
}

avl::Node* avl::l_rotation(Node* node) {
    // aligned right right
    // node
    //     x
    //        y
    Node* n1 = node;
    Node* n2 = n1->right;
    n1->right = n2->left;
    n2->left = n1;
    return n2;
}

avl::Node* avl::r_rotation(Node* node) {
    // aligned left left
    //       node
    //     x
    //  y
    Node* n1 = node;
    Node* n2 = n1->left;
    n1->left = n2->right;
    n2->right = n1;
    return n2;
}

avl::Node* avl::rl_rotation(Node* node) {
    // aligned right left
    // node
    //     x
    //   y
    Node* n1;
    Node* n2;
    Node* n3;

    n1 = node;
    n2 = n1->right;
    n3 = n1->right->left;

    n1->right = n3->left;
    n2->left = n3->right;
    n3->left = n1;
    n3->right = n2;
    return n3;
}

avl::Node* avl::lr_rotation(Node* node) {
    // aligned left right
    //    node
    //  x
    //     y
    Node* n1;
    Node* n2;
    Node* n3;

    n1 = node;
    n2 = n1->left;
    n3 = n1->left->right;

    n1->left = n3->right;
    n2->right = n3->left;
    n3->right = n1;
    n3->left = n2;
    return n3;
}

bool avl::search_id(Node* node, int id) {
    // finds name based on id
    if (node == nullptr) {
        // id is not found
        return false;
    }

    if (node->id == id) {
        // found the id
        cout << node->name << endl;
        return true;
    }

    if (id < node->id) {
        // check left node for id
        return search_id(node->left, id);
    }

    else if (id > node->id) {
        // check right node for id
        return search_id(node->right, id);
    }
    return false;
}

bool avl::search_name(Node* node, string name, bool& found) {
    // If more than 1 with the same NAME, print each ID in pre-order traversal
    if (node != nullptr) {

        // node first
        if (node->name == name) {
            cout << node->id << endl;
            found = true;
        }

        // left nodes next
        search_name(node->left, name, found);

        // right nodes last
        search_name(node->right, name, found);
    }

    return found;
}

void avl::inorder(Node* node, vector<int>& vec, bool& print, bool& comma) {
    // left root right
    if (node != nullptr) {

        inorder(node->left, vec, print, comma);
        vec.push_back(node->id);

        if (print) {

            if (comma) {
                // comma passed in as false to not print it before beginning or after end
                cout << ", ";
            }

            else {
                comma = true;
            }

            cout << node->name;
        }

        inorder(node->right, vec, print, comma);
    }
    // comma separated
}

void avl::preorder(Node* node, bool& comma) {
    // root left right
    if (node != nullptr) {
        if (comma) {
            cout << ", ";
        }


        else {
            comma = true;
        }

        cout << node->name;
        preorder(node->left, comma);
        preorder(node->right, comma);
    }
}

void avl::postorder(Node* node, bool& comma) {
    // left right root
    if (node != nullptr) {
        postorder(node->left, comma);
        postorder(node->right, comma);

        if (comma) {
            cout << ", ";
        }

        else {
            comma = true;
        }

        cout << node->name;
    }
}

int avl::level_count(Node* node) {
    if (node == nullptr) {
        // if nullptr it returns 0
        return 0;
    }

    else {
        // counts each side and returns the max
        int l = level_count(node->left);
        int r = level_count(node->right);

        return 1 + max(l, r);
    }
}
/*
void avl::remove_inorder(Node*& node, int n) {
    vector<int> remove_vec;
    bool print = false;
    bool comma = false;

    // remove_vec needs to have all ids inorder then remove the specific id at index N
    inorder(node, remove_vec, print, comma);
    // ensure n is an index in remove_vec or else print unsuccessful
    if (n >= 0 && n < remove_vec.size()) {
        // remove node with specified id
        bool success = false;
        node = remove(node, remove_vec[n], success);
    }

    else {
        cout << "unsuccessful" << endl;
    }
}*/

avl::Node* avl::get_root() {
    return root;
}

void avl::set_root(Node* node) {
    root = node;
}
