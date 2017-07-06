#include <iostream>
#include "searcher.h"

using namespace std;

int main(int argc, char const *argv[]){

	string model = argv[1];
	Searcher searcher;
	string query;
	cout << "Type your search: " << endl;
	while(getline(cin, query)){
		if(query[0] == 0){
			break;
		}
		if(model == "-b" || model == "-boolean"){
			searcher.boolean_search(query);
		}
		else if (model == "-pg" || model == "-pageRank"){
			searcher.pageRank_search(query);
		}
		else if(model == "-a" || model == "-anchorRank"){
			searcher.anchor_search(query);
		}
		else if(model == "-v" || model == "-vectorModel"){
			searcher.vectorModel_search(query);
		}
		else{
			searcher.search(query);
		}
		cout << "Type your search: " << endl;
	}

	return 0;
}
