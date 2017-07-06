#ifndef BOOLEAN_H
#define BOOLEAN_H
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


class Boolean{

private:
	ifstream index_file;
	unordered_map<int, set<int> > index;
	unordered_map<string, int> vocabulary;
	unordered_map<int, string> urls;
	vector<string> stopwords;
	unordered_map<int, unsigned long long> term_seek;

public:
	
	Boolean(unordered_map<string, int>& vocabulary, unordered_map<int, string>& urls, 
  		vector<string>& stopwords, unordered_map<int, unsigned long long>& term_seek);	
	~Boolean();
	unordered_map<int,double> search(const string& s);
	bool is_stopword(const string& word);
	bool indexable(const string& word);
	unordered_map<int, int> get_docsList(int term_id);

};




#endif
