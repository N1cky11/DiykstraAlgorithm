#include "Dijkstra.h"

Dijkstra::Dijkstra(const std::string &fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Could not open file\n" ;
        std::cout << "Matrix initialized to default state\n" ;
    }
    else {
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

}
int Dijkstra::indexOfMin(const std::vector<int> &vec,const std::vector<int> &visitedNodes) const {
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

std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> Dijkstra::adjacentElements(int beginningNode,std::vector<int> &visitedNodes) const {
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> distance_node;

    for (size_t i = 0; i != matrix.size(); ++i) {
        if (matrix[beginningNode][i]!= 0 && visitedNodes[i]==0) {
            distance_node.push(std::make_pair(matrix[beginningNode][i], i));
        }
    }
    return distance_node;
}

bool Dijkstra::setDistance(int node, std::vector<int> &distance) {
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

std::vector<int> Dijkstra::findShortestPath(int node) {
    auto n=matrix.size() ;
    std::vector<int> distance(n, std::numeric_limits<int>::max() );
    std::vector<int> visitedNodes(n,0);

    if (!setDistance(node, distance)) throw std::out_of_range("Invalid node input\n") ;

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
