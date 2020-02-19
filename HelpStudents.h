#ifndef CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#define CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;


class HelpStudents{

public:
    int numberOfVertices;
    int destination;
    vector<list< pair<int,int>>> adjacencyLists;
    HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways);
    long long int firstStudent();
    long long int secondStudent();
    long long int thirdStudent();
    long long int fourthStudent();
    long long int fifthStudent();

    // YOU CAN ADD YOUR HELPER FUNCTIONS AND MEMBER FIELDS

};

#endif //CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
