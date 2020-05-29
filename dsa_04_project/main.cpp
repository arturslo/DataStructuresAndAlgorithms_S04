using namespace std;

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Graph
{
public:
	// edges
	static const int E_0_1 = 0;
	static const int E_0_5 = 1;
	static const int E_2_3 = 2;
	static const int E_2_5 = 3;
	static const int E_2_7 = 4;
	static const int E_4_8 = 5;
	static const int E_4_9 = 6;
	static const int E_5_6 = 7;
	static const int E_5_10 = 8;
	static const int E_6_9 = 9;
	static const int E_6_11 = 10;
	static const int E_7_11 = 11;
	static const int E_8_9 = 12;
	static const int E_10_11 = 13;

	static vector<vector<int>> makeGraph()
	{
		vector<vector<int>> graph(12);

		graph[0] =  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		graph[1] =  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		graph[2] =  { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		graph[3] =  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		graph[4] =  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
		graph[5] =  { 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 };
		graph[6] =  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0 };
		graph[7] =  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
		graph[8] =  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 };
		graph[9] =  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 };
		graph[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		graph[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 };

		return graph;
	}

	static string toString(vector<vector<int>> graph)
	{
		ostringstream os;

		vector<string> headings = {"V", "(0-1)", "(0-5)", "(2-3)", "(2-5)", "(2-7)", "(4-8)", "(4-9)", "(5-6)", "(5-10)", "(6-9)", "(6-11)", "(7-11)", "(8-9)", "(10-11)"};
		const int width = 8;

		for (auto& heading : headings)
		{
			os << setw(width) << heading;
		}

		os << endl;

		for (int vertex = 0; vertex < graph.size(); vertex++)
		{
			os << setw(width) << vertex;
			for (auto& belongsToEdge : graph[vertex])
			{
				os << setw(width) << belongsToEdge;
			}
			os << endl;
		}

		return os.str();
	}

	static bool isVertexVisited(vector<int>& visitedVertices, int vertex)
	{
		return find(visitedVertices.begin(), visitedVertices.end(), vertex) != visitedVertices.end();
	}

	static int chooseMinUnvisitedVertex(vector<vector<int>>& graph, vector<int>& visitedVertices)
	{
		int chosenVertex = -1;
		for (int vertex = 0; vertex < graph.size(); vertex++)
		{
			if (!Graph::isVertexVisited(visitedVertices, vertex))
			{
				chosenVertex = vertex;
				visitedVertices.push_back(chosenVertex);
				break;
			}
		}

		return chosenVertex;
	}

	static int chooseUnexploredVertex(vector<int>& visitedVertices, int lastExploredVertex)
	{
		int chosenVertex = -1;
		bool pickNext = false;
		for (int i = 0; i < visitedVertices.size(); i++)
		{
			int visitedVertex = visitedVertices[i];

			if (lastExploredVertex == -1)
			{
				chosenVertex = visitedVertex;
				break;
			}

			if (visitedVertex == lastExploredVertex)
			{
				pickNext = true;
				continue;
			}

			if (pickNext)
			{
				chosenVertex = visitedVertex;
				break;
			}
		}

		return chosenVertex;
	}

	static int exploreVertex(vector<vector<int>>& graph, vector<int>& visitedVertices, int vertexToExplore)
	{
		if (graph.size() == 0)
		{
			return -1;
		}

		if (vertexToExplore < 0 || vertexToExplore >= graph.size())
		{
			return -1;
		}

		vector<int>& vertexEdges = graph[vertexToExplore];
		vector<int> connectedEdges = {};

		for (int i = 0; i < vertexEdges.size(); i++)
		{
			int isConnectedInt = vertexEdges[i];

			if (isConnectedInt)
			{
				connectedEdges.push_back(i);
			}
		}

		for (int vertex = 0; vertex < graph.size(); vertex++)
		{

			if (vertex == vertexToExplore)
			{
				continue;
			}

			if (Graph::isVertexVisited(visitedVertices, vertex))
			{
				continue;
			}

			vector<int>& vertexEdges = graph[vertex];
			for (auto& connectedEdge : connectedEdges)
			{
				int isConnectedInt = vertexEdges[connectedEdge];
				if (!isConnectedInt)
				{
					continue;
				}

				visitedVertices.push_back(vertex);
			}
		}

		return vertexToExplore;
	}

	static void breadthFirst(vector<vector<int>>& graph, vector<int>& outVisitedVertices)
	{
		int lastExploredVertex = -1;
		int unexploredVertex = -1;

		while (Graph::chooseMinUnvisitedVertex(graph, outVisitedVertices) != -1)
		{
			do
			{
				unexploredVertex = Graph::chooseUnexploredVertex(outVisitedVertices, lastExploredVertex);
				lastExploredVertex = Graph::exploreVertex(graph, outVisitedVertices, unexploredVertex);
			} while (unexploredVertex != -1);
		}
	}

	static unordered_map<int, char> mapVertices(vector<int>& vertices, vector<char>& charList)
	{
		unordered_map<int, char> map;
		pair<int, char> keyVal;

		for (int i = 0; i < vertices.size(); i++)
		{
			keyVal.first = vertices[i];
			keyVal.second = charList[i];
			map.insert(keyVal);
		}

		return map;
	}

	static void printMapping(unordered_map<int, char>& map)
	{
		for (auto& keyVal : map)
		{
			cout << " " << keyVal.first << " => " << keyVal.second;
		}
		cout << endl;
	}
};

int main()
{
	vector<vector<int>> graph = Graph::makeGraph();
	cout << "incidence matrix:" << endl;
	cout << Graph::toString(graph);
	cout << endl;

	vector<int> visitedVertices = {};
	Graph::breadthFirst(graph, visitedVertices);

	vector<char> surnameAndName = {'L', 'o', 'c', 'm', 'e', 'l', 'i', 's', 'A', 'r', 't', 'u', 'r', 's'};

	vector<int> vertices;
	for (int i = 0; i < graph.size(); i++)
	{
		vertices.push_back(i);
	}

	unordered_map<int, char> map1 = Graph::mapVertices(vertices, surnameAndName);

	cout << "vertices mapping:" << endl;
	Graph::printMapping(map1);
	cout << endl;

	cout << "breadth first traversal:" << endl;
	for (auto vertex : visitedVertices)
	{
		cout << " " << vertex << " (" << map1.at(vertex) << ")";
	}
	cout << endl << endl;

	unordered_map<int, char> map2 = Graph::mapVertices(visitedVertices, surnameAndName);

	cout << "reorder mapping:" << endl;
	Graph::printMapping(map2);
	cout << endl;

	cout << "breadth first traversal:" << endl;
	for (auto vertex : visitedVertices)
	{
		cout << " " << vertex << " (" << map2.at(vertex) << ")";
	}
	cout << endl << endl;

	return 0;
}
