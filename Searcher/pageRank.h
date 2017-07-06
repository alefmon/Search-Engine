#ifndef PAGERANK_H
#define PAGERANK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;


class PageRank{

private:
	int num_docs;

public:
	ifstream pageRank_file;
	unordered_map<int, double> doc_pageRank;


	unordered_map<int, unsigned long long> anchor_seek;
	unordered_map<int, double> IDF;
	unordered_map<string, int> vocabulary;
	unordered_map<int, string> urls;
	vector<string> stopwords;
	
	PageRank();
	~PageRank();
	void load_pageRanks();
	double get_pageRank(int docID);

};



#endif
