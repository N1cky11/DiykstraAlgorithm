#include <vector>
#include <queue>
#include <exception>
#include <algorithm>
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>

class dijkstra {
    std::vector<std::vector<int>> matrix;

public:
    dijkstra(std::vector<std::vector<int>> &m) : matrix(std::move(m)) {};
    dijkstra() = default;
    ~dijkstra() = default;
    dijkstra& operator=(dijkstra &obj) = default;
    dijkstra(const dijkstra &obj) = default;

    std::vector<int> shortestPath(int beginningNode = 0);
    int indexOfMin(const std::vector<int> &vec,const std::vector<int> &visitedNodes) const;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> adjacentElements(int beginningNode,std::vector<int> &visitedNodes) const ;
    bool setDistance(int node, std::vector<int> &distance);
};

int dijkstra::indexOfMin(const std::vector<int> &vec,const std::vector<int> &visitedNodes) const {
    int minValue = std::numeric_limits<int>::max();
    int minIndex = -1 ;
    for (int i = 0; i != vec.size() ; ++i) {
        if (vec[i] <= minValue && visitedNodes[i]==0) {
            minValue = vec[i];
            minIndex = i;
        }
    }
    return minIndex;
}

std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> dijkstra::adjacentElements(int beginningNode,std::vector<int> &visitedNodes) const {
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> distance_node;

    for (size_t i = 0; i != matrix.size(); ++i) {
        if (matrix[beginningNode][i]!= 0 && visitedNodes[i]==0) {
            distance_node.push(std::make_pair(matrix[beginningNode][i], i));
        }
    }
    return distance_node;
}

bool dijkstra::setDistance(int node, std::vector<int> &distance) {
    auto n = matrix.size();
    try {
        for (size_t i = 0; i != n; ++i) {
            distance[i] = std::numeric_limits<int>::max();
        }
        distance.at(node) = 0;
    } catch (std::out_of_range &error) {
        std::cerr << "Error:" << error.what() << "\n";
        return false;
    }
    return true;
}

std::vector<int> dijkstra::shortestPath(int node) {
    auto n=matrix.size() ;
    std::vector<int> distance(n, std::numeric_limits<int>::max() );
    std::vector<int> visitedNodes(n,0);

    if (!setDistance(node, distance)) throw std::runtime_error("Invalid node input\n") ;

    while( std::find(visitedNodes.begin(),visitedNodes.end() , 0)!=visitedNodes.end() ) {
        int currentVertex=indexOfMin(distance,visitedNodes);
        if(currentVertex==-1) return distance ;

        visitedNodes[currentVertex]=1;
        auto adjacent = adjacentElements(currentVertex,visitedNodes);

        while (!adjacent.empty()) {
            auto p = adjacent.top();
            adjacent.pop();
            if(visitedNodes[p.second]) continue ;

            auto distanceSum = distance[currentVertex] + matrix[currentVertex][p.second];

            if (distance[p.second] > distanceSum) {
                distance[p.second] = distanceSum;
                //std::cout << "Updated path to vertex " << p.second << " to " <<distanceSum <<"\n" ;
            }
        }
     }

    return distance;
}

void openAndRead(std::vector<std::vector<int> > &matrix) {
   std::ifstream file("input.txt");

    if (!file.is_open()) {
        throw std::runtime_error("Can't open file\n") ;
    }

    std::string line{};

    while (getline(file, line)) {
        std::vector<int> lineNumbers{};
        std::istringstream is(line);
        int number{};
        while (is >> number) {
            lineNumbers.push_back(number);
        }
        matrix.push_back(lineNumbers);
    }

    file.close();

}

int main(int argc, char **argv) {
    std::vector<std::vector<int> > matrix{} ;
    std::vector<int> resVec{} ;

    try {
        openAndRead(matrix) ;
        dijkstra res(matrix);
        resVec=res.shortestPath(7) ;
        for (const auto &i : resVec) std::cout << i << " ";
    } catch(std::runtime_error &e) {
     std::cout << "Error:" << e.what() <<"\n" ;
    }

    return 0;
}
