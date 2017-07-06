#include "pageRank.h"

PageRank::PageRank(){
	load_pageRanks();
}


PageRank::~PageRank(){

}


void PageRank::load_pageRanks(){
	pageRank_file.open("Searcher/util/pagerank.txt");
	int id;
	double pg;
	while(pageRank_file >> id >> pg){
		doc_pageRank.insert(make_pair(id, pg));
	}
	pageRank_file.close();
}

double PageRank::get_pageRank(int docID){
	return doc_pageRank[docID];
}
