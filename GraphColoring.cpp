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
#include<algorithm>
#include<sys/time.h>

using namespace std;

long gettime(){
    struct timeval start;
    gettimeofday(&start,NULL);
    return start.tv_sec*1000000+start.tv_usec;
}


class Graph
{
	int V; 
	list<int> *adj;
	Graph(int V) { this->V = V; adj = new list<int>[V]; }
	~Graph()	 { delete [] adj; }

	void addEdge(int v, int w);
	void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void Graph::greedyColoring()
{
	int result[V];
	result[0] = 0;
	for (int u = 1; u < V; u++)
		result[u] = -1;
	bool available[V];
	for (int cr = 0; cr < V; cr++)
		available[cr] = false;
	for (int u = 1; u < V; u++)
	{
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = true;
		int cr;
		for (cr = 0; cr < V; cr++)
			if (available[cr] == false)
				break;

		result[u] = cr;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = false;
	}
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
int main()
{
	ifstream in("class.csv");

    string line, field;

    vector< vector<string> > array;
    vector<string> v;              
	long start = gettime();
	solveKT();

    while ( getline(in,line) ) 
    {
        v.clear();
        stringstream ss(line);
        while (getline(ss,field,','))  
        {v.push_back(field);}
        array.push_back(v);
    }
    for (size_t i=0; i<array.size(); ++i)
    {for (size_t j=0; j<array[i].size(); ++j)
        {cout << array[i][j] << "|";}
        cout << "\n";}
		
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

	long end = gettime();
	cout << "\n";
	cout << "Time for execution: " << end-start << " ms";
    return 0;
}
