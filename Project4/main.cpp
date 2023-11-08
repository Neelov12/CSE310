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
    string str; 
	BinarySearchTree()
	{
		root = NULL;
	}
	bool isEmpty() const { return root == NULL; }
    void TREE_INSERT(int );
	string INORDER_TREE_WALK(node*, int );
    string POSTORDER_TREE_WALK(node*, int );
    string PREORDER_TREE_WALK(node*, int ) ;
    string LEVELORDER_TREE_WALK(node*, int );
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

string BinarySearchTree::INORDER_TREE_WALK(node* x, int i)
{
    // Ensures initialization occurs once
    if(i == 0) 
        str = "";
    
	if (x != NULL)
	{
		if (x->left) INORDER_TREE_WALK(x->left, 1);
		    str.append(to_string(x->key)); 
            str.append(" ");
		if (x->right) INORDER_TREE_WALK(x->right, 1);
	}
    return str; 
}

string BinarySearchTree::POSTORDER_TREE_WALK(node* x, int i) {

    // Ensures initialization occurs once
    if(i == 0) 
        str = "";

    if (x != NULL) {
        if (x->left) POSTORDER_TREE_WALK(x->left, 1);
        if (x->right) POSTORDER_TREE_WALK(x->right, 1);
            str.append(to_string(x->key)); 
            str.append(" ");
    }
    return str; 
}

string BinarySearchTree::PREORDER_TREE_WALK(node* x, int i) {

    // Ensures initialization occurs once
    if(i == 0) 
        str = "";

    if (x != NULL) {
            str.append(to_string(x->key)); 
            str.append(" ");
        if (x->left) PREORDER_TREE_WALK(x->left, 1);
        if (x->right) PREORDER_TREE_WALK(x->right, 1);
    }
    return str; 
}

string BinarySearchTree::LEVELORDER_TREE_WALK(node* x, int i) {
    str = "";
    if (x != NULL) {
    
        queue<node*> q;
        q.push(x);

        while (q.empty() == false) {
         
        // Print front of queue and remove it from queue
            node* temp = q.front();
                str.append(to_string(temp->key)); 
                str.append(" ");
            q.pop();
 
        // Enqueue left child
            if (temp->left != NULL)
                q.push(temp->left);
 
        // Enqueue right child
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
    return str; 
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

int main() {
    BinarySearchTree bst;
    string numberString = ""; 
    int n = 0; 
    string query[10000]; 

    cin >> numberString; 
    string numstr = "";
    for (int j = 0; j < numberString.size(); j++) {
                if(isdigit(numberString[j]))
                    numstr += numberString[j];
        }

        
    n = stoi(numstr); 
   
    //numstr = "";

    string input = ""; 
    string input_parsed = ""; 

    int size = 0; // size of outputs that require array storage 
    int num = 0; 
    string num_string = "";

    // Traverses through loop n times, or number of queries

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
            bool neg = false; 

            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
                if(input[j] == '-')
                    neg = true; 
            }
            num = stoi(num_string); 

            if(neg)
                num = -1* num; 
            bst.TREE_INSERT(num);

        }
        // DELETE 
        else if (input_parsed == "DELET") {
            bool neg = false; 

            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
                if(input[j] == '-')
                    neg = true; 
            }
            num = stoi(num_string); 

            if(neg)
                num = -1* num; 

            bst.DELETE(num);
        }

        // Outputs need to be stored in an array 

        // SEARCH
        else if (input_parsed == "SEARC") {
            bool neg = false; 

            for (int j = 0; j < input.size(); j++) {
                if(isdigit(input[j]))
                    num_string += input[j];
                if(input[j] == '-')
                    neg = true; 
            }
            num = stoi(num_string); 

            if(neg)
                num = -1* num; 

            if (bst.contains(num) == 1)
                query[size] = "True"; 
            else 
                query[size] = "False"; 

            size++;     
        // IN ORDER
        }
        else if (input_parsed == "INORD") {
            query[size] = bst.INORDER_TREE_WALK(bst.root, 0);
            size++; 

        // PRE ORDER
        }
        else if (input_parsed == "PREOR") {
            query[size] = bst.PREORDER_TREE_WALK(bst.root, 0);
            size++; 
        }

        // POST ORDER
        else if (input_parsed == "POSTO") {
            query[size] = bst.POSTORDER_TREE_WALK(bst.root, 0);
            size++; 

        // LEVEL ORDER
        }
        else if (input_parsed == "LEVEL") {
            query[size] = bst.LEVELORDER_TREE_WALK(bst.root, 0);
            size++; 
        }
        else {}
    }

    for(int i = 0; i <= size; i++) {
        cout << query[i] << endl;
    }
    return 0; 
}

