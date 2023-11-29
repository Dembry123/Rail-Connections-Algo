//
// Created by Dylan Embry on 3/27/23.
//

#ifndef PROGRAM3_MYGRAPH_H
#define PROGRAM3_MYGRAPH_H


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class edge {
private:
    int begin;
    int end;
    float weight;
public:
    int getBegin() const;

    bool operator==(const edge &rhs) const;

    bool operator!=(const edge &rhs) const;

    edge(int begin, int anEnd, float weight);

    void setBegin(int begin);

    int getAnEnd() const;

    void setAnEnd(int anEnd);

    float getWeight() const;

    void setWeight(float weight);
};
class MyGraph {
public:
    MyGraph(const MyGraph& g);
    MyGraph(int n);
    bool AddEdge(int a, int b, float w);
    void output(ostream& os);
    pair<vector<int>, float> HW2Prog(int s, int t, bool printMST);
private:
    unordered_map<int,vector<edge>> map;
    int numV;
    vector<edge> edges;
};


#endif //PROGRAM3_MYGRAPH_H
