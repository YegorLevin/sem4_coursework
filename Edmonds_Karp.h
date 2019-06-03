#pragma once
#include "ListClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>



using namespace std;

class Edmonds_Karp
{
private:
	const int INF = 1e9;
	size_t size;
	ListClass<string> nodes;
	ListClass<vector<int>*> matrix; //matrix of existed edges in residual graph

	void add_new_node(string name);
	ListClass<string> * split(string input);
	ListClass<size_t> * shortest_way(string from, string whereto);
	


public:
	Edmonds_Karp(string file_name);
	int max_flow();
};


Edmonds_Karp::Edmonds_Karp(string file_name)
{
	setlocale(LC_CTYPE, "Russian");
	size = 0;
	ifstream in(file_name); // opening file for reading
	string node1;
	string node2;
	bool has_S = false;
	bool has_T = false;
	int weight;
	if (in.is_open())
	{
		//adding missing nodes
		while (in >> node1)
		{
			in >> node2;
			
			if (node1 == "S" || node2 == "S")
				has_S = true;
			if (node1 == "T" || node2 == "T")
				has_T = true;

			in >> weight;

			bool already_has1 = false;
			bool already_has2 = false;
			for (size_t i = 0; i < nodes.get_size(); i++)
			{

				if (node1 == nodes.at(i))
					already_has1 = true;
				if (node2 == nodes.at(i))
					already_has2 = true;
			}
			if (!already_has1)
			{
				add_new_node(node1);
			}

			if (!already_has2)
			{
				add_new_node(node2);
			}

			//filling the matrix
			size_t row = 0;
			size_t column = 0;

			while (nodes.at(row) != node1)
			{
				row++;
			}
			while (nodes.at(column) != node2)
			{
				column++;
			}

			matrix.at(row)->at(column) = weight;
		}

	}
	else
		throw logic_error("No input file");
	in.close();     // closing file
	
	// if has no source or sink
	if(!has_S)
		throw logic_error("No Source node");
	if (!has_T)
		throw logic_error("No Sink node");
	

}


void Edmonds_Karp::add_new_node(string name)
{
	nodes.push_back(name);
	size++;
	vector<int> * new_row = new vector<int>(size, -1); //matrix expansion
	matrix.push_back(new_row);
	for (size_t i = 0; i < size - 1; i++)
	{
		matrix.at(i)->push_back(-1);
	}
}

ListClass<string> * Edmonds_Karp::split(string input)
{
	ListClass<string> * info = new ListClass<string>;
	string buffer = "";      //buffer string
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] != ' ') {      // "—" splitter
			buffer += input[i];
		}
		else {
			info->push_back(buffer);
			buffer = "";
		}
	}
	info->push_back(buffer);
	return info;
}

ListClass<size_t> * Edmonds_Karp::shortest_way(string from, string whereto)
{
	ListClass<int> arrival_from;
	ListClass<int> distances;
	for (size_t i = 0; i < size; i++)
	{
		distances.push_back(INF);
		arrival_from.push_back(-1);
	}
	size_t index_from = 0;
	size_t index_whereto = 0;

	//searching index of the first node on the way
	while (nodes.at(index_from) != from)
	{
		index_from++;
	}
	//searching index of the last node on the way
	while (nodes.at(index_whereto) != whereto)
	{
		index_whereto++;
	}

	// Ford-Bellman algorithm
	distances.set(index_from, 0);

	for (size_t k = 0; k < size - 1; k++)
		for (size_t i = 0; i < size; i++)
			for (size_t j = 0; j < size; j++)
			{
				if (matrix.at(j)->at(i) == -1)
					continue;
				if (distances.at(j) + 1 < distances.at(i))
				{
					distances.set(i, distances.at(j) + 1);
					arrival_from.set(i, j);
				}
			}


	ListClass<size_t> * path;
	if (distances.at(index_whereto) == INF) // if there is no path
	{
		return nullptr;
	}

	else { // making path
		path = new ListClass<size_t>;
		for (size_t current = index_whereto; current != index_from; current = arrival_from.at(current))
		{
			path->push_front(current);
		}
		path->push_front(index_from);

	}
	return path;
}

int Edmonds_Karp::max_flow()
{
	int maximum_flow = 0;
	
	// finding the shortest way
	ListClass<size_t> * path = shortest_way("S", "T");
	if (path == nullptr)
	{
		throw logic_error("No way to Sink");
	}
	while (path != nullptr) // until the paths are over
	{
		// finding maximum flow through that path
		int min = matrix.at(path->at(0))->at(path->at(1)); 
		for (size_t i = 1; i < path->get_size() - 1; i++)
		{
			if (matrix.at(path->at(i))->at(path->at(i + 1)) < min)
				min = matrix.at(path->at(i))->at(path->at(i + 1));
		}
		// update residual graph
		for (size_t i = 0; i < path->get_size() - 1; i++)
		{
			matrix.at(path->at(i))->at(path->at(i + 1)) = matrix.at(path->at(i))->at(path->at(i + 1)) - min;
			if (matrix.at(path->at(i))->at(path->at(i + 1)) == 0) // remove zero edges
				matrix.at(path->at(i))->at(path->at(i + 1)) = -1;
		}
		maximum_flow += min; // count maximum flow
		path = shortest_way("S", "T"); // the next shortest path
	}
	

	return maximum_flow;
}