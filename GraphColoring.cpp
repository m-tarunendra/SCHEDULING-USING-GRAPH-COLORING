#include <iostream>
#include <list>
#include <fstream>
#include <math.h> 
#include <sstream>
#include <iterator>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Graph
{
	int V; // No. of vertices
	list<int> *adj; // A dynamic array of adjacency lists
public:
	// Constructor and destructor
	Graph(int V) { this->V = V; adj = new list<int>[V]; }
	~Graph()	 { delete [] adj; }

	// function to add an edge to graph
	void addEdge(int v, int w);

	// Prints greedy coloring of the vertices
	void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v); // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
	int result[V];

	// Assign the first color to first vertex
	result[0] = 0;

	// Initialize remaining V-1 vertices as unassigned
	for (int u = 1; u < V; u++)
		result[u] = -1; // no color is assigned to u
	// A temporary array to store the available colors. True
	// value of available[cr] would mean that the color cr is
	// assigned to one of its adjacent vertices
	bool available[V];
	for (int cr = 0; cr < V; cr++)
		available[cr] = false;

	// Assign colors to remaining V-1 vertices
	for (int u = 1; u < V; u++)
	{
		// Process all adjacent vertices and flag their colors
		// as unavailable
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = true;

		// Find the first available color
		int cr;
		for (cr = 0; cr < V; cr++)
			if (available[cr] == false)
				break;

		result[u] = cr; // Assign the found color

		// Reset the values back to false for the next iteration
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = false;
	}

	// print the result
	for (int u = 0; u < V; u++)
		for(int k=0; k< V; k++)
		{
			if(result[k]==u)
			{
				cout << "SEMESTER- " << u << " ---> SUBJECT "
					<< k << endl;
			}
		}
}


// Driver program to test above function
int main()
{
	ifstream in("class.csv");

    string line, field;

    vector< vector<string> > array;  // the 2D array
    vector<string> v;                // array of values for one line only

    while ( getline(in,line) )    // get next line in file
    {
        v.clear();
        stringstream ss(line);

        while (getline(ss,field,','))  // break line into comma delimitted fields
        {
            v.push_back(field);  // add each field to the 1D array
        }

        array.push_back(v);  // add the 1D array to the 2D array
    }

    for (size_t i=0; i<array.size(); ++i)
    {
        for (size_t j=0; j<array[i].size(); ++j)
        {
            cout << array[i][j] << "|"; // (separate fields by |)
        }
        cout << "\n";
    }
    int row = array.size();
    int column = array[0].size();
	 Graph g4(row);
    
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<(column-i);j++)
        {
			int result = 0;
			int a = 1;
			int b = atoi(array[j][i].c_str());

            if(b ==1)
            {
                g4.addEdge(i,j);
            }
        }
    }
    cout << "\nTHE SUBJECTS TO CHOOSE FOR SEMESTERS\n";
    g4.greedyColoring();

    return 0;
}
