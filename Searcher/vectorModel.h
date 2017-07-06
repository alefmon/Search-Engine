#ifndef VECTORMODEL_H
#define VECTORMODEL_H
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

class VectorModel{

private:
	int num_docs;
	ifstream index_file;
	unordered_map<int, unsigned long long> term_seek;
	unordered_map<string, int> vocabulary;
	unordered_map<int, string> urls;
	vector<string> stopwords;

public:
	
	VectorModel(int num_docs, unordered_map<string, int>& vocabulary, unordered_map<int, string>& urls, 
  		vector<string>& stopwords, unordered_map<int, unsigned long long>& term_seek);
	~VectorModel();
	unordered_map<int, int> get_docsList(int term_id);
	unordered_map<int,double> search(const string& s);
	double similarity(const vector<double>& a, const vector<double>& b);
	bool is_stopword(const string& word);
	bool indexable(const string& word);
	static bool cmp(pair <int, double> a, pair<int, double> b);

};



#endif
