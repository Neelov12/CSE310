#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "data.cpp"
#include "query.h"


using namespace std;




/*
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./dijkstra <graph> <direction>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;

    bool running = true; 

    while(running) {
        string input; 
        cout << "Query: "; 
        getline(cin, input); 

        
    }
    return 0; 
}
*/
int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <txt_file_name> <direction>" << std::endl;
        return 1;
    }
    bool directed;
    string file; 

    const char* txtFileName = argv[1];
    const char* direction = argv[2];

    //CONFIGURES DIRECTION
    if (strcmp(direction, "directed") == 0) {
        directed = true;
    } else if (strcmp(direction, "undirected") == 0) {
        directed = false;
    } else {
        std::cerr << "Invalid direction. Please use 'directed' or 'undirected'." << std::endl;
        return 1;
    }
    // CONFIGURES FILE
    if (strcmp(txtFileName, "network01.txt") == 0) {
        // Use network01.txt
        file = "network01.txt";
    } else if (strcmp(txtFileName, "network02.txt") == 0) {
        // Use network02.txt
        file = "network02.txt";
    } else {
        std::cerr << "Invalid txtFileName. Please use 'network01.txt' or 'network02.txt'." << std::endl;
        return 1;
    }

    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << endl;
        return 1;
    }
     

    int n, m;
    inputFile >> n >> m;

    int id; 
    int u; 
    int v; 
    float w; 
    
    adjList list(n);
    

    for(int i = 0; i < m; i++)  {
        if (directed) {
            inputFile >> id >> u >> v >> w; 
                //cout << id << " " << u << " " << v << " " << w << endl; 
            // Graph is directed
            list.insert(u, id, u + 1, v + 1, w);
        }
        // Undirected
        else {
            inputFile >> id >> u >> v >> w; 
            //cout << id << " " << u << " " << v << " " << w << endl; 
            list.insert(u, id, u + 1, v + 1, w);
            list.insert(v, id, v + 1, u + 1, w);
        }
    }

    // -1 REPRESENTS NO PREDECESSOR FOR VERTEX AND INFINITY FOR WEIGHT
    for(int i = 0; i < n; i++)
        list.insertPred(i, -1, -1.0);
    
    
    // QUERY 
    bool running = true; 
    bool findRan = false;
    string input = "";

    query que;
    string str; 

    string s, d, f, function;
    int source, dest, flag;  
    int currSource; 
    bool pathExists;
    bool outcome2 = false; bool outcome3 = false; bool outcome4 = false; 
    
    // RUNS AN ARBITRARY NUMBER OF TIMES 
    while(running) { 
         
        cout << "Query: "; 
        getline(cin, input); 

        // INTERPRETS USER INPUT 
        str = que.interpret(input, n);
        
        /*
            STORES TYPE OF INPUT
                "find" - find method
                "write" - write method
                "" - invalid 
        */  
        function = que.getNthWord(str, 1);        

        // STORES SOURCE, DESTINATION, AND FLAG
        // source & dest REUSED IN WRITE METHOD 
        source = 0; dest = 0; flag = 0;

    //FIND FUNCTION
    //****************************************************************

        if(function == "find") {
        d = que.getNthWord(str, 3);
        s = que.getNthWord(str, 2);
        f = que.getNthWord(str, 4);
        source = stoi(s);
        currSource = source; 
        dest = stoi(d);
        flag = stoi(f);

        //RESETS LISTS
        list.deleteList();
        for(int i = 0; i < n; i++) {
            list.pred[i]->p = -1; 
            list.pred[i]->w = -1.0; 
        }
        // RESETS EDGES
        while (list.pq.empty() == false) { 
            // RESET WEIGHT FROM SOURCE
            list.pq.top()->wFromSource = -1.0;
            list.pq.pop(); 
        } 


        int d = source; 
        findRan = true; 

        bool predExists = false; 

        // ADD SOURCE VERTEX TO QUE THEN REMOVE
        if(flag == 1) {
            printf("Insert vertex %d, key=%12.4f\n", d, 0.0000);
            printf("Delete vertex %d, key=%12.4f\n", d, 0.0000);
        }
        list.pred[d - 1]->w = 0.0; 

        float pWeight = 0.0; // Total weight of path
        pathExists = true; 
        int limit = 10000; 
        int i = 0; 
        // ITERATES THRU LOOP UNTIL D IS EQUAL TO THE DESTINATION
        while(d != dest) {
            i++; 
            if(!predExists) {
                edge* current = list.array[d - 1]; // The edge(s) at destination d 
                    // PUSHES ALL VERTEXES FROM d (DESITNATION) TO V (pq SORTS MIN WEIGHTS AT TOP OF QUEUE)
                    while (current != nullptr) {
                        
                        // Prints insertion if flag is equal to 1
                        if(flag == 1) printf("Insert vertex %d, key=%12.4f\n", current->v, current->weight);

                        current->wFromSource += 1.0 + current->weight + pWeight;
                        list.pq.push(current);

                        current = current->next;
                }
            }

            edge* p = list.pq.top();

            // CHECKS IF NEW DESTINATION ALREADY HAS A PREDECESSOR
            if(list.pred[p->v - 1]->p == -1) {
                // SET NEW DESTINATION AS DESTINATION 
                d = p->v;
                // FINDS TOTAL WEIGHT OF PATH
                pWeight = p->wFromSource;
                // CHECK FOR RETURNS 
                list.checkForReturns(p->u); 
                // ADD TO PATH
                list.pred[p->v - 1]->p = p->u; list.pred[p->v - 1]->w = pWeight; 
                // RESET WEIGHT FROM SOURCE
                list.pq.top()->wFromSource = -1.0;
                // PRINT IF FLAG IS 1
                if(flag == 1) printf("Delete vertex %d, key=%12.4f\n", p->v, p->weight);
                // POP QUEUE AT TOP
                list.pq.pop();
                // SET predExists AS FALSE SINCE PREDECESSOR DID NOT EXIST
                predExists = false; 
            }
            else {
                // RESET WEIGHT FROM SOURCE
                list.pq.top()->wFromSource = -1.0;
                // PRINT IF FLAG IS 1
                if(flag == 1) printf("Delete vertex %d, key=%12.4f\n", p->v, p->weight);
                // POP QUEUE AT TOP
                list.pq.pop();
                // SET predExists AS TRUE SINCE PREDECESSOR EXISTED
                predExists = true; 
            }

            if(i == limit) {
                pathExists = false; 
                break; 
            }
        }

        
        cout << endl;
        /*
        while (list.pq.empty() == false) { 
            edge* p = list.pq.top();  
            cout << "ID: " << p->edgeID 
                 << " u: " << p->u 
                 << " v: " << p->v 
                 << " weight: " << p->weight << endl;

            // RESET WEIGHT FROM SOURCE
            list.pq.top()->wFromSource = -1.0;
            list.pq.pop(); 
        } 
        */

        // CREATE PATH 
        list.createPath();

        int remEdgesVertex[m];
            for(int i = 0; i < sizeof(remEdgesVertex); i++) {
                remEdgesVertex[m] = 0; 
            }
        int remEdgesWeight[m];
            for(int i = 0; i < sizeof(remEdgesWeight); i++) {
                remEdgesWeight[m] = 0; 
            }

            outcome2 = false; 
            outcome3 = false; 
            outcome4 = false; 
            int j = 0; 

            while (list.pq.empty() == false) { 
            j++; 
            edge* p = list.pq.top();  

            remEdgesVertex[j] = p->v;
            remEdgesWeight[j] = p->wFromSource;

            // RESET WEIGHT FROM SOURCE
            list.pq.top()->wFromSource = -1.0;
            list.pq.pop(); 
            }

        for(int i = 0; i <= j; i++) {
            if(remEdgesVertex[i] == dest) outcome2 = true; 
            if(remEdgesWeight[i] == -1) outcome3 = true; 
            if(pathExists == false) outcome4 = true; 
        }
        



    }

    //WRITE FUNCTION
    //****************************************************************

    else if(function == "write" && findRan) {
        s = que.getNthWord(str, 3);
        d = que.getNthWord(str, 4);
        source = stoi(s);
        dest = stoi(d);

        // CHECKS IF S IS EQUAL TO SOURCE 
        if(source != currSource) {
            cout << "Error: invalid source destination pair\n";
        }
        // WRITE PATH IS VALID 

        if(outcome2) {
            cout << "Path not known to be shortest: "; 
            list.displayPathList(); 
        } 
        else if(outcome3) {
            cout << "No " << source << "-" << dest << " path has been computed." << endl; 
        }
        else if(outcome4) {
            cout << "No " << source << "-" << dest << " path exists." << endl;
        }
        else {
            cout << "Shortest path: "; 
            list.displayPathList();
        }

    }
    

    //INVALID
    //****************************************************************
    
    else if(function == "write" && !findRan)
        cout << "Error: no path computation done\n";
    else if(function == "") {}
    else {}


}
return 0;
}





