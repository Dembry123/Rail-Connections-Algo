//
// Created by Dylan Embry on 3/27/23.
//

#include "MyGraph.h"
#include <set>
#include <stack>

MyGraph::MyGraph(const MyGraph &g) {
    this->map = g.map;
    this->numV = g.numV;
}

MyGraph::MyGraph(int n) {
    this->numV = n;
}

bool MyGraph::AddEdge(int a, int b, float w) {
    edge temp(a, b, w);
    edge temp2(b, a, w);

    auto it = std::find(edges.begin(), edges.end(), temp);
    auto it2 = std::find(edges.begin(), edges.end(), temp2);

    if(it == edges.end() && it2 == edges.end()){
        edges.push_back(temp);
        map[a].push_back(temp);
        map[b].push_back(temp2);
        return true;
    }
    else{
        return false;
    }
}

void MyGraph::output(ostream &os) {
    os << map.size() << endl;
    for (int i = 0; i < edges.size(); ++i) {
        os << min(edges.at(i).getBegin(),edges.at(i).getAnEnd()) <<  " " << max(edges.at(i).getBegin(),edges.at(i).getAnEnd()) << " " << edges.at(i).getWeight() << endl;
    }
}

pair<vector<int>, float> MyGraph::HW2Prog(int s, int t, bool printMST) {
    std::sort(edges.begin(), edges.end(), [](const edge& lhs, const edge& rhs) {
        return lhs.getWeight() > rhs.getWeight();
    });
    vector<set<int>> sets;
    for (auto& it : map) {
        set<int> temp;
        temp.insert(it.first);
        sets.push_back(temp);
    }

    MyGraph MST(numV);
    for(auto& e: edges){
        bool in_same_set = false;
        for (auto& s : sets) {
            // if we found both the verteces in the same set
            if (s.find(e.getBegin()) != s.end() && s.find(e.getAnEnd()) != s.end()) {
                in_same_set = true;
            }
        }

        if(in_same_set) {
            continue;
        }
        else {
            MST.AddEdge(e.getBegin(), e.getAnEnd(), e.getWeight());
            vector<set<int>> newSets(sets.size() - 1);
            set<int> beginVertexSet;
            set<int> endVertexSet;
            for (auto& s : sets) {
                // if we found both the verteces in the same set
                if (s.find(e.getBegin()) != s.end()) {
                    beginVertexSet = s;
                }
                else if(s.find(e.getAnEnd()) != s.end()){
                    endVertexSet = s;
                }
                else{
                    newSets.push_back(s);
                }
            }
            beginVertexSet.merge(endVertexSet);
            newSets.push_back(beginVertexSet);
            sets = newSets;
        }
    }
    stack<int> path;
    stack<float> weight;
    path.push(s);
    weight.push(2147483647);
    set<int> visited;
    visited.insert(s);
    while(path.top() != t){
        //loop over every possible edge our current vertex can get to
        bool noPossibleEdges = true;
        for(auto& possibleEdge: MST.map[path.top()]){
            if(visited.find(possibleEdge.getAnEnd()) != visited.end()){
                continue;
            }
            else{
                noPossibleEdges = false;
                visited.insert(possibleEdge.getAnEnd());
                path.push(possibleEdge.getAnEnd());
                weight.push(possibleEdge.getWeight());
                break;
            }
        }
        if(noPossibleEdges){
            path.pop();
            weight.pop();
        }
    }
    vector<int> returnPath;
    float capacity = weight.top();
    while(!path.empty()){
        returnPath.push_back(path.top());
        path.pop();
    }
    reverse(returnPath.begin(), returnPath.end());

    while(!weight.empty()){
        if(capacity > weight.top()){
            capacity = weight.top();
        }
        weight.pop();
    }
    if(printMST){
        MST.output(cout);
    }
    return {returnPath,capacity};
}
int edge::getBegin() const {
    return begin;
}

void edge::setBegin(int begin) {
    edge::begin = begin;
}

int edge::getAnEnd() const {
    return end;
}

void edge::setAnEnd(int anEnd) {
    end = anEnd;
}

float edge::getWeight() const {
    return weight;
}

void edge::setWeight(float weight) {
    edge::weight = weight;
}

edge::edge(int begin, int anEnd, float weight) : begin(begin), end(anEnd), weight(weight) {}

bool edge::operator==(const edge &rhs) const {
    if (begin == rhs.begin &&
        end == rhs.end &&
        weight == rhs.weight) return true;
    else if (end == rhs.begin &&
             begin == rhs.end &&
             weight == rhs.weight) return true;
    return false;
}

bool edge::operator!=(const edge &rhs) const {
    return !(rhs == *this);
}
