// Neelov Alam CSE 310

#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

class BinarySearchTree
{
private:
	class node
	{
	public:
		node* left;
		node* right;
		node* parent;
		int key;
	};


public:
	node* root;
	BinarySearchTree()
	{
		root = NULL;
	}
	bool isEmpty() const { return root == NULL; }
    void TREE_INSERT(int );
	void INORDER_TREE_WALK(node*);
    void POSTORDER_TREE_WALK(node*);
    void PREORDER_TREE_WALK(node*);
    void LEVELORDER_TREE_WALK(node*);
    void DELETE(int );
    bool contains(int ); 

    node* SEARCH(int n) {
        node* x = root;
        
        while(x->key != n) {
            if (n < x->key) {
                if (x-> left) x = x->left;
                else return NULL;
            }
            else {
                if (x-> right) x = x->right;
                else return NULL;
            }
        }
        return x;
    }
};

void BinarySearchTree::TREE_INSERT(int d)
{
	// This implements the algorithm in page 261 of the textbook
	node* z = new node();
	z->key = d;
	z->left = NULL;
	z->right = NULL;

	node* y = NULL;
	node* x = root;

	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (y == NULL)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
		
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
    string str = "";
	if (x != NULL)
	{
		if (x->left) INORDER_TREE_WALK(x->left);
		    cout << x->key << " ";
		if (x->right) INORDER_TREE_WALK(x->right);
	}
}

void BinarySearchTree::POSTORDER_TREE_WALK(node* x) {
    if (x != NULL) {
        if (x->left) POSTORDER_TREE_WALK(x->left);
        if (x->right) POSTORDER_TREE_WALK(x->right);
        cout << x->key << " ";
    }
}

void BinarySearchTree::PREORDER_TREE_WALK(node* x) {
    if (x != NULL) {
        cout << x->key << " ";
        if (x->left) PREORDER_TREE_WALK(x->left);
        if (x->right) PREORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::LEVELORDER_TREE_WALK(node* x) {
    if (x != NULL) {
    
        queue<node*> q;
        q.push(x);

        while (q.empty() == false) {
         
        // Print front of queue and remove it from queue
            node* temp = q.front();
            cout << temp->key << " ";
            q.pop();
 
        // Enqueue left child
            if (temp->left != NULL)
                q.push(temp->left);
 
        // Enqueue right child
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
}

bool BinarySearchTree::contains (int n) {
    if(SEARCH(n) != NULL) 
        return true;
    else 
        return false; 
}

void BinarySearchTree::DELETE (int n) {
    node* x = root;
    node* parent = nullptr;
    
    x = SEARCH(n);
    
    if(x == NULL) {
        cout << "Key not in list ";
        return;
    }
    
    parent = x->parent;
    
    // Case 1: Node has no children
    
    if (x->left == NULL && x->right == NULL) {
        if (x != root) {
            if (parent->left == x) {
                parent->left = nullptr;
            }
            if (parent->right == x) {
                parent->right = nullptr;
                }
            }
            
            else {
                root = nullptr;
            }
    }
    
    // Case 2: Node has one child
    
    else if (x->left == NULL || x->right == NULL) {
        node* child = (x->left)? x->left: x->right;
        
        if (x != root) {
            if (x == parent->left) {
                parent->left = child;
            }
            else{
                parent->right = child;
            }
        }
         
        else {
            root = child;
            }
        
    // Case 3: Node has two children
        
    }
    else {
        node* y = x->right;
        
        while(y->left != NULL)
            y = y->left;
        
        if (x != root) {
                if (parent->left == x) {
                    if (x->left) {
                        node* ytemp = y;
                        ytemp->left = x->left;
                        parent->left = ytemp;
                    }
                    else
                        parent->left = y;
                }
                if (parent->right == x) {
                    if (x->left) {
                        node* ytemp = y;
                        ytemp->left = x->left;
                        parent->right = ytemp;
                    }
                    else
                        parent->right = y;
                }
            }
          
        // If node is root
        
        else {
            if (x->left) {
                node* ytemp = y;
                ytemp->left = x->left;
                root = ytemp;
            }
            else
                root = y;
        }
    }
}
/*
int main()
{
	BinarySearchTree bst;
	int choice, key;
    int choice2; // Im not very creative with names
    int number;
    int k;
    string name;
    bool case10 = true;
    
	while (true)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Example " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insertion " << endl;
		cout << " 2. In-Order Traversal " << endl;
        cout << " 3. Post-Order Traversal " << endl;
        cout << " 4. Pre-Order Traversal " << endl;
        cout << " 5. Find Minimum " << endl;
        cout << " 6. Find Maximum " << endl;
        cout << " 7. Find Successor " << endl;
        cout << " 8. Delete " << endl;
        cout << " 9. Remove Min " << endl;
        cout << " 10. Enter Flight Time Simulator " << endl;
		cout << " 11. Exit " << endl;
        cout << " 12. Level Order "  << endl; 
        cout << " 13. Search "  << endl; 
        cout << " Enter your choice : ";
		cin >> choice;
		switch (choice)
        {
            case 1: cout << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
            case 2: cout << endl;
                cout << " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
            case 3:
                cout << " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POSTORDER_TREE_WALK(bst.root);
                break;
            case 4:
                cout << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PREORDER_TREE_WALK(bst.root);
                break;
            case 8:
                cout << " Enter key (int value) that you would like to delete :  ";
                cin >> key;
                bst.DELETE(key);
                cout << " Deleted " << endl;
                cout << " -------" << endl;
                break;
		case 11: system("pause");
			return 0;
			break;
        case 12: 
            cout << " Level-Order Traversal " << endl;
            cout << " -------------------" << endl;
            bst.LEVELORDER_TREE_WALK(bst.root);
            break;
        case 13: 
            cout << " Enter key (int value) that you would like to search :  ";
                cin >> key;
                if(bst.contains(key) == 1)
                    cout << "True" << endl; 
                else 
                    cout << "False" << endl;
            break; 
		default:
			cout << "Invalid choice";
		}
	}
} */

int main() {
    BinarySearchTree bst;
    string numberString = ""; 
    int n = 0; 

    cout << "Enter queries:" << endl;
    cin >> numberString; 
    string numstr = "";
    for (int j = 0; j < numberString.size(); j++) {
                if(isdigit(numberString[j]))
                    numstr += numberString[j];
        }

        
    n = stoi(numstr); 
   
    //numstr = "";
    cout << endl;

    string input = ""; 
    string input_parsed = ""; 

    int size = 0; // size of outputs that require array storage 
    int num = 0; 
    string num_string = "";

    for (int i = 0; i < n + 1; i++) {
        input = "";
        input_parsed = "";
        num = 0; 
        num_string = "";

        getline(cin, input); 
        //cin >> input; 

        input_parsed = input.substr(0, 5);

        // INSERT 
        if (input_parsed == "INSER") {
            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
            }
            num = stoi(num_string); 
            bst.TREE_INSERT(num);
        }
        // DELETE 
        else if (input_parsed == "DELET") {
            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
            }
            num = stoi(num_string); 
            bst.DELETE(num);
        }

        // Outputs need to be stored in an array 

        // SEARCH
        else if (input_parsed == "SEARC") {
            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
            }
            num = stoi(num_string); 
            if (bst.contains(num) == 1)
                cout << "True" << endl;
            else 
                cout << "False" << endl;
        }
        else if (input_parsed == "INORD") {
            bst.INORDER_TREE_WALK(bst.root);
        }
        else if (input_parsed == "PREOR") {
            bst.PREORDER_TREE_WALK(bst.root);
        }
        else if (input_parsed == "POSTO") {
            bst.POSTORDER_TREE_WALK(bst.root);
        }
        else if (input_parsed == "LEVEL") {
            bst.LEVELORDER_TREE_WALK(bst.root);
        }
        else {
            
        }
    }
    return 0; 
}

