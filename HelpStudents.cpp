/*
Student Name:
Student Number:
Project Number: 4
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "HelpStudents.h"

using namespace std;

HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways) {
    this->numberOfVertices=N;//the corresponding fields are initialized.
    this->adjacencyLists;
    this->destination=K;
    for(int i=0;i<N;i++){
        list<pair<int,int>> temp;
        adjacencyLists.push_back(temp);//Adjlist is initially full of empty lists
    }
    for(int i=0;i<M;i++){
        int node1 = ways[i].first.first;// edges are processed and added to adjlist.
        int node2 = ways[i].first.second;
        int weight = ways[i].second;
        adjacencyLists[node1-1].push_back(make_pair(node2,weight));
        adjacencyLists[node2-1].push_back(make_pair(node1,weight));
    }
}

long long int HelpStudents::firstStudent(){
    //I implemented Dijkstra's algorithm for the first type of students
    priority_queue<pair<long long int,int>,vector<pair<long long int,int>>,greater<pair<long long int,int>>> pq;
    //queue to sort edges
    vector<long long int> distances(numberOfVertices,numeric_limits<long long int>::max());
    //distances are initially set to infinity.
    distances[0] = 0;//distance of the source is 0, it is also pushed to the priority queue
    pq.push(make_pair(0,1));
    while(!pq.empty()){//while all vertices are not processed
        pair<long long int,int> temp = pq.top();//take the vertex with minimum distance
        pq.pop();//pop it
        int node = temp.second;
        list< pair<int,int> >::iterator iter;
        for(iter=adjacencyLists[node-1].begin();iter!= adjacencyLists[node-1].end();++iter){
            //for all edges of this node, if an adjacent vertex is closer using this node,add that vertex to the queue
            int node2 = (*iter).first;
            int weight = (*iter).second;
            if(distances[node2-1]>distances[node-1]+weight){//if the node is closer using the current node
                distances[node2-1]=distances[node-1]+weight;//update the distance
                pq.push(make_pair(distances[node2-1],node2));//add it to the queue
            }
        }
    }
    return distances[destination-1];//return the length of the shortest path to the summit
}
long long int HelpStudents::secondStudent(){
    //In this type, I implemented Prim's algorithm to create the MST. Then I found the max weight in the path to the summit
    int* parent = new int[numberOfVertices];//parent array
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> costs;
    //this queue will keep the sorted list of costs
    int* cost = new int[numberOfVertices];//cost array
    bool* known = new bool[numberOfVertices];//known array
    for(int i=0;i<numberOfVertices;i++){
        //initialize all arrays, with no parents, infinite costs and process not known
        parent[i]=-1;
        cost[i] = numeric_limits<int>::max();
        known[i] = false;
    }
    cost[0]=0;//source has 0 cost
    costs.push(make_pair(0,1));
    while(!costs.empty()){
        //while all vertices are not processed
        int index = costs.top().second;//take the current vertex with min cost
        costs.pop();
        known[index-1] = true;//mark it as known
        list<pair<int,int>>::iterator it = adjacencyLists[index-1].begin();
        while(it!=adjacencyLists[index-1].end()){
            int w = (*it).first;
            int weight = (*it).second;
            if(!known[w-1]&&weight<cost[w-1]){//for all unknown neighbors of this node, update their costs,parents
                parent[w-1]=index;
                cost[w-1] =weight;
                costs.push(make_pair(weight,w));//push the neighbor node to be processed
            }
            it++;
        }
    }
    long long int max=0;//max weight on the path
    int node = destination;//start with summit, move to the parent each iteration
    while(node!=1){
        if(cost[node-1]>max){//if cost is higher than max, update the max
            max = cost[node-1];
        }
        node = parent[node-1];
    }
    return max;//return the max weight
};
long long int HelpStudents::thirdStudent() {
    //I implemented a BFS based shortest path finder.
   queue<int> vertices;//will keep the vertices in order
   vector<long long int>distances(numberOfVertices,-1);//distances are all -1 at the beginning
   vertices.push(1);
   distances[0]=0;//source has distance 0
   while(!vertices.empty()){//while all vertices are not processed
       int node = vertices.front();//take the top
       vertices.pop();
       list<pair<int,int>>::iterator iter;
       for(iter=adjacencyLists[node-1].begin();iter!=adjacencyLists[node-1].end();iter++){
           //for all neighbors of the current node
           int node2 = (*iter).first;
           if(distances[node2-1]==-1){//If the node is not processed yet
                distances[node2-1]=distances[node-1]+1;//make its distance one more
                vertices.push(node2);//push it
                if(node2==destination)//if the summit is found
                    return distances[node2-1];//return the distance
           }
       }
   }
   return distances[destination-1];
}
long long int HelpStudents::fourthStudent() {
    vector<set<int>> visited(numberOfVertices);//this will keep the visited edges
    long long int sum = 0;//total cost of the path
    int node = 1;//start with the source
    while(true){
        int weight = numeric_limits<int>::max();
        int next = node;
        list<pair<int,int>>::iterator iter;
        for(iter=adjacencyLists[node-1].begin();iter!=adjacencyLists[node-1].end();iter++){
            //this loop finds the adjacent with the minimum weight while checking if the edge was wisited.
            if(visited[node-1].find((*iter).first)==visited[node-1].end()){
                if((*iter).second<=weight){
                    if((*iter).second==weight&&(*iter).first>next)
                        continue;
                    next = (*iter).first;
                    weight= (*iter).second;
                }
            }

        }
        sum+=weight;//update the sum
        if(node==next||next==destination){//if the node we are considering didn't change or it is the summit
            node=next;//go to the summit,
            break;//break the loop
        }
        visited[node-1].insert(next);//update the visited edges
        visited[next-1].insert(node);
        node = next;
    }
   if(node==destination){
       return sum;//if the node is destination, return the total cost
   }
   else{//we didn't reach the summit
       return -1;//return -1
   }
}
long long int HelpStudents::fifthStudent() {
    return 0;
}

// YOU CAN ADD YOUR HELPER FUNCTIONS