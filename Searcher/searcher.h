#ifndef SEARCHER_H
#define SEARCHER_H
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
#include "boolean.h"
#include "vectorModel.h"
#include "pageRank.h"
#include "anchorRank.h"

using namespace std;


class Searcher{

private:
	int num_docs;
	ifstream index_file;
	ifstream anchor_index_file;
	ifstream urls_file;
	ifstream vocabulary_file;
	ifstream seeks_file;
	ifstream anchor_seeks_file;
	unordered_map<int, unsigned long long> term_seek;
	unordered_map<int, unsigned long long> anchor_seek;
	unordered_map<int,double> pageRank;
	unordered_map<string, int> vocabulary;
	vector<string> stopwords;
	Boolean* boolean;
	VectorModel* vectorModel;
	AnchorRank* anchorRank;
	
public:

	Searcher();
	~Searcher();
	unordered_map<int, string> urls;
	unordered_map<int,double> search(const string& s);
	unordered_map<int,double> boolean_search(const string& s);
	unordered_map<int,double> vectorModel_search(const string& s);
	unordered_map<int,double> anchor_search(const string& s);
	unordered_map<int,double> pageRank_search(const string& s);

	void load_pageRank();
	void load_vocabulary();
	void load_seeks();
	void anchor_load_seeks();
	void load_urls();
	void load_stopwords();

};



#endif
