#include <vector>
#include <queue>
#include <exception>
#include <algorithm>
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>

class Dijkstra {
    std::vector<std::vector<int>> matrix{};

public:
    Dijkstra(std::vector<std::vector<int>> &m) : matrix(std::move(m)) {};
    Dijkstra() = default;
    Dijkstra(const std::string &fileName) ;
    ~Dijkstra() = default;
    Dijkstra& operator=(Dijkstra &obj) = default;
    Dijkstra(const Dijkstra &obj) = default;

    std::vector<int> findShortestPath(int beginningNode = 0);
    int indexOfMin(const std::vector<int> &vec,const std::vector<int> &visitedNodes) const;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> adjacentElements(int beginningNode,std::vector<int> &visitedNodes) const ;
    bool setDistance(int node, std::vector<int> &distance);
};

