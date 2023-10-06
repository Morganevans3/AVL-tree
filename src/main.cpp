#include <iostream>
#include <vector>
#include "avl.h"
using namespace std;
/* Note:
     1. You will have to comment main() when unit testing your code because catch uses its own main()
     2. You will submit this main.cpp file and any header files you have on Gradescope.
 */

bool verify_name(string name) {
    for (char c : name) {

        // verify it is either a letter or space
        if (!isalpha(c)) {
            if (!isspace(c)) {
                return false;

            }
        }
    }

    return true;
}

bool verify_id(string id) {
    // verify that the id is an 8 digit int
    if (id.length() != 8) {
        return false;
    }

    for (char c : id) {

        // verify it is a digit
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}


int main() {
    string n_com;
    getline(cin, n_com);
    int num_commands;

    try {
        // make sure num_commands is an int
        num_commands = stoi(n_com);
    }
    catch (const std::exception& e) {
        return 0;
    }

    if (num_commands < 1 || num_commands > 1000) {
        // out of bounds
        return 0;
    }

    vector<string> commands;
    string com;
    bool too_long = false;

    for (int i = 0; i < num_commands; i++) {
        getline(cin, com);
        if (com.length() < 6 || com.length() > 1000) {
            // out of bounds
            too_long = true;
            break;
        }
        // add commands to vector
        commands.push_back(com);
    }

    if (too_long == true) {
        return 0;
    }

    // set up the avl tree
    avl tree;

    // command 1, 2, and 3
    // 1 is string
    // 2 is either string or int
    // 3 is int
    string c1, c2;
    int c3;
    int space;
    bool print = true;
    bool comma = false;

    for (int j = 0; j < num_commands; j++) {
        // redefine each command
        c1 = "";
        c2 = "";
        // c2 can be string or id but if id put in c3
        c3 = 0;
        // c3 is id

        com = commands.at(j);
        space = com.find(" ");

        if (space != string::npos) {
            // function name id
            // c1 = function
            c1 = com.substr(0, space);
            com = com.substr(space + 1, com.length());

            // find if there is a " which means it is string/c2
            space = com.find("\"");
            if (space != string::npos) {
                com = com.substr(space + 1, com.length());

                // find where second " is to find where c2 ends
                space = com.find("\"");
                if (space != string::npos) {
                    c2 = com.substr(0, space);
                    com = com.substr(space, com.length());
                }

                // find if there is a space again with the id behind
                // store as int in c3
                space = com.find(" ");
                if (space != string::npos) {
                    c3 = stoi(com.substr(space + 1, com.length()));
                }
            }

            else {
                // if function followed by id will print unsuccessful
                if (verify_name(com)) {
                    c1 = "";
                }

                else {
                    // store 2nd command as c3 if remove (id) or etc
                    c3 = stoi(com);
                }
            }
        }

        else {
            // set c1 as function since it has nothing else in command
            c1 = com;
        }

        if (c1 == "insert") {
            // Add a Student object into the tree with the specified name, NAME and GatorID number, ID
            // Balance the tree automatically if necessary
            // The ID must be unique
            // The ID and NAME must satisfy the constraints stated below
            // Also, prints “successful” if insertion is successful and prints “unsuccessful” otherwise
            // NAME identifier will be separated by double inverted commas for parsing, e.g. "Josh Smith"
            if (verify_name(c2) && verify_id(to_string(c3))) {
                tree.set_root(tree.insert(tree.get_root(), c2, c3));
            }

            else {
                // if invalid name or id
                cout << "unsuccessful" << endl;
            }
        }

        else if (c1 == "printInorder") {
            // Print out a comma separated inorder traversal of the names in the tree
            vector<int> inorder_vec;
            comma = false;
            print = true;

            tree.inorder(tree.get_root(), inorder_vec, print, comma);
            cout << endl;
        }

        else if (c1 == "remove") {
            // Find and remove the account with the specified ID from the tree
            // [Optional: Balance the tree automatically if necessary. We will test your code only on cases where the tree will be balanced before and after the deletion. So you can implement a BST deletion and still get full credit]
            // If deletion is successful, print “successful”
            // If the ID does not exist within the tree, print “unsuccessful”
            // You must prioritize replacing a removed node with its inorder successor for the case where the deleted node has two children
            comma = false;
            tree.set_root(tree.remove(tree.get_root(), c3, comma));
        }

        else if (c1 == "search") {
            // passed in with name or id
            if (verify_id(to_string(c3))) {
                // Search for the student with the specified ID from the tree
                // If the ID was found, print out their NAME
                // If the ID does not exist within the tree, print “unsuccessful”
                bool found = tree.search_id(tree.get_root(), c3);

                if (!found) {
                    cout << "unsuccessful" << endl;
                }
            }

            else if (verify_name(c2)) {
                // Search for the student with the specified name, NAME in the tree
                // If the student name was found, print the associated ID
                // If more than 1 with the same NAME, print each ID on a new line with no other spaces and in the same relative order as a pre-order traversal
                // If the name does not exist within the tree, print “unsuccessful”
                bool found = false;
                found = tree.search_name(tree.get_root(), c2, found);

                if (!found) {
                    cout << "unsuccessful" << endl;
                }
            }
        }

        else if (c1 == "printPreorder") {
            // Print out a comma separated preorder traversal of the names in the tree
            comma = false;
            tree.preorder(tree.get_root(), comma);
            cout << endl;
        }

        else if (c1 == "printPostorder") {
            // Print out a comma separated postorder traversal of the names in the tree
            comma = false;
            tree.postorder(tree.get_root(), comma);
            cout << endl;
        }

        else if (c1 == "printLevelCount") {
            // Prints the number of levels that exist in the tree
            int levels = tree.level_count(tree.get_root());
            cout << levels << endl;
        }

        else if (c1 == "removeInorder") {
            // Nth gator id is removed
            // N is passed in
            // print successful or unsuccessful
            //tree.remove_inorder(tree.get_root_ptr(), c3);
            vector<int> vec_id;
            print = false;
            comma = false;
            tree.inorder(tree.get_root(), vec_id, print, comma);

            if (c3 >= 0 && c3 < vec_id.size()) {
                // remove node with specified id
                print = false;
                tree.set_root(tree.remove(tree.get_root(), vec_id[c3], print));
            }

            else {
                cout << "unsuccessful" << endl;
            }
        }

        else {
            // if 1st command is misspelled or invalid
            cout << "unsuccessful" << endl;
        }
    }



    return 0;
}
