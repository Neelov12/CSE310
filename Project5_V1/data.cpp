#include <iostream>
#include <string>
#include <bits/stdc++.h>



using namespace std;

struct predecessor {
    int p; 
    int d; 
    float w; 

    predecessor(int p_arg, int d_arg, float w_arg) : p(p_arg), d(d_arg), w(w_arg) {}
};

struct edge {
    int edgeID; 
    int u;
    int v; 
    float weight;
    float wFromSource; 
    edge* next;

    edge(int id, int u_, int v_, float w) : edgeID(id), u(u_), v(v_), weight(w), wFromSource(-1.0), next(nullptr) {}
};

// STORES PATH
struct path {
    int vertex; 
    float wFromSource;
    int destination; 
    path* next;
    path* prev; 

    path(int v, float w, int i) : vertex(v), wFromSource(w), destination(i), next(nullptr), prev(nullptr) {}
};

struct DereferenceCompareNode {
    bool operator()(const edge* lhs, const edge* rhs) const
    {
        return lhs->wFromSource > rhs->wFromSource;
    }
};

struct PredDereferenceCompareNode {
    bool operator()(const predecessor* lhs, const predecessor* rhs) const
    {
        return lhs->w > rhs->w;
    }
};

class adjList {
    public:
        int size; 
        edge** array;
        predecessor** pred; 
        path* head;
        path* tail; 
        priority_queue<edge*, vector<edge*>, DereferenceCompareNode> pq;
        priority_queue<predecessor*, vector<predecessor*>, PredDereferenceCompareNode> ppq;

        adjList(int n) : size(n), head(nullptr), tail(nullptr) {
            array = new edge*[size]();
            pred = new predecessor*[size](); 
        }

        // Destructor to free memory
        ~adjList() {
            for (int i = 0; i < size; i++) {
                edge* current = array[i];
                    while (current != nullptr) {
                    edge* temp = current;
                    current = current->next;
                delete temp;
            }
        }
        delete[] array;
    }
    
    void insert(int index, int id, int u, int v, float w) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }

        edge* newedge = new edge(id, u, v, w);
        newedge->next = array[index];
        array[index] = newedge;
    }

    void insertPred(int index, int p, float w) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }

        predecessor* newNode = new predecessor(p, index + 1, w);
        pred[index] = newNode;
    }

    void printList(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds!" << std::endl;
            return;
        }

        edge* current = array[index];
        while (current != nullptr) {
            cout << "ID: " << current->edgeID 
                 << " u: " << current->u 
                 << " v: " << current->v 
                 << " weight: " << current->weight << endl;
            current = current->next;
        }
        cout << endl;
        cout << endl;
    }

    void printPredecessors(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds!" << std::endl;
            return;
        }

        predecessor* current = pred[index];
        cout << index + 1 << ": " << current->p << ", " << current->w << endl;
        cout << endl;
    }

    void addNode(path* newNode) {
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void createPath() {
        for(int i = 0; i < sizeof(pred); i++) {
            if(pred[i]->w != -1)
                ppq.push(pred[i]);
        }
        /*
        while(ppq.empty() == false) {
            cout << ppq.top() << endl; 
            ppq.pop(); 
        }
        */

        while(ppq.empty() == false) {
            addNode(new path(ppq.top()->p, ppq.top()->w, ppq.top()->d));
            ppq.pop();
        }
        deleteFromList();
    }

    void deleteNode(path* head_ref, path* del) {

        if (head_ref == NULL || del == NULL) {
            return;
        }
        if (head_ref == del) {
            head_ref = del->next;
        }
        if (del->next != NULL) {
            del->next->prev = del->prev;
        }
        if (del->prev != NULL) {
            del->prev->next = del->next;
        }
        free(del);
        return;
    }

    /*
    void addDestinationToVertex(int vertexToFind, path* destinationNode, edge* p, int s, int flag) {
        path* current = tail;

        while (current && current->vertex != vertexToFind) {
            path* temp = current;
            current = current->predecessor;

            if (flag == 1) cout << "deleted" << endl; 
            
            delete temp;
        }

        tail = current; 

        // IF CURRENT NODE IS EMPTY, OR IF WE HAVE GONE BACK TO SOURCE
        if(tail == nullptr) {
            head = tail;

            // ADD SOURCE NODE
            addNode(new path(s, 0.0));

            // ADD EDGE FROM SOURCE TO PREDECESSOR OF DESTINATION
            path* newNode = new path(p->u, p->weight);
            tail->destination = newNode;
            newNode->predecessor = tail; 
            tail = newNode;
        }

        // ADD DESTINATION NODE
        tail->destination = destinationNode;
        destinationNode->predecessor = tail;
        tail = destinationNode;       
    }
    */

    void deleteList() {
        while (head) {
            path* temp = head;
            head = head->prev;
            delete temp;
        }
        head = tail = nullptr; 
    }

    void displayPathList() {
        path* current = head;
        float w = 0.0; 
        while (current) {
            cout << current->destination << " "; 
            w = current->wFromSource; 
            current = current->next;
        }
        printf("\nThe path weight is: %12.4f\n", w);
    }

    void deleteFromList() {
        path* current = head; 
        while(current && current->next) {
            if(current->destination != current->next->vertex) {
                deleteNode(head, current->next);
            }
            else {
            current = current->next;
            }
        }
    }

    void checkForReturns(int vertex) {
        for(int i = 0; i < sizeof(pred); i++) {
            if(pred[i]->p == vertex) {
                pred[i]->p = -1; pred[i]->w = -1; 
            }
        }
    }

    /*
    void createPath(int i, int v, int d) {
        if(v == d) {
            path* newNode = new path(v, pred[i]->w, i);
            addNode(newNode);
            return; 
        }
        if(pred[i]->p == v) {
            path* newNode = new path(v, pred[i]->w, i);
            addNode(newNode);
            v = i + 1; 
            createPath(0, v, d);
        }
        else {
            if(i == sizeof(pred)) {
                if(tail == nullptr)
                    return;

                i = head->index + 1; 
                v = head->vertex;
                while(tail) {
                    path* temp = tail;
                    tail = tail->prev;
                    delete temp; 
                }
                head = tail = nullptr; 
                createPath(i, v, d);   
            }
            else {
                createPath(i + 1, v, d);
            }
        }  
    }
    */


    /*
    bool nodeWithPredecessorExists(int vertexToFind) {
        path* current = tail;

        while (current && current->vertex != vertexToFind) {
            current = current->predecessor;
        }

        return (current && current->predecessor != nullptr);
    }
    */

    
    /*
    // FINDS PATH FROM SOURCE TO DESTINATION 
    void find(int source, int dest, int flag) {
        deletePath();
        cout << "ran";
        
        int d = source; 
        float pWeight = 0.0; // Total weight of path

        bool predExists = false; 

        // ADD SOURCE VERTEX TO QUE THEN REMOVE
        if(flag == 1) {
            printf("Insert vertex %d, key=%12.4f\n", d, 0.0000);
            printf("Delete vertex %d, key=%12.4f\n", d, 0.0000);
        }


        // ITERATES THRU LOOP UNTIL D IS EQUAL TO THE DESTINATION
        while(d != dest) {

            if(!predExists) {
                edge* current = array[d]; // The edge(s) at destination d 
                    // PUSHES ALL VERTEXES FROM d (DESITNATION) TO V (pq SORTS MIN WEIGHTS AT TOP OF QUEUE)
                    while (current != nullptr) {
                    pq.push(current);

                    // Prints insertion if flag is equal to 1
                    if(flag == 1) printf("Insert vertex %d, key=%12.4f\n", current->v, current->weight);

                    current = current->next;
                }
            }

            edge* p = pq.top();

            // CHECKS IF NEW DESTINATION ALREADY HAS A PREDECESSOR
            if(!hasPredecessor(p->v)) {
                // SET NEW DESTINATION AS DESTINATION 
                d = p->v;
                // ADD TO PATH
                addToPath(p, flag);
                // POP QUEUE AT TOP
                pq.pop();
                // PRINT IF FLAG IS 1
                if(flag == 1) printf("Delete vertex %d, key=%12.4f\n", p->v, p->weight);
                // SET predExists AS FALSE SINCE PREDECESSOR DID NOT EXIST
                predExists = false; 
            }
            else {
                pq.pop();
                // SET predExists AS TRUE SINCE PREDECESSOR EXISTED
                predExists = true; 
            }

        }
        

         while (pq.empty() == false) { 
            edge* p = pq.top(); 
            cout << "ID: " << p->edgeID 
                 << " u: " << p->u 
                 << " v: " << p->v 
                 << " weight: " << p->weight << endl;
            pq.pop(); 
    } 
    */




};
