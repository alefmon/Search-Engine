#include "searcher.h"

Searcher::Searcher(){

  cout << "Loading Index Files..." << endl;
  anchor_load_seeks();
  cout << "[1/6] Done" << endl;
  load_seeks();
  cout << "[2/6] Done" << endl;
  load_urls();
  cout << "[3/6] Done" << endl;
  load_vocabulary();
  cout << "[4/6] Done" << endl;
  load_stopwords();
  cout << "[5/6] Done" << endl;
  load_pageRank();
  vectorModel = new VectorModel(num_docs, vocabulary, urls, stopwords, term_seek);
  anchorRank = new AnchorRank(num_docs, vocabulary, urls, stopwords, anchor_seek);
  boolean = new Boolean(vocabulary, urls, stopwords, term_seek);
  cout << "[6/6] Done !" << endl;
}

Searcher::~Searcher(){
  vocabulary_file.close();
  urls_file.close();
  seeks_file.close();
  anchor_seeks_file.close();
  delete vectorModel;
  delete anchorRank;
  delete boolean;
}


void Searcher::load_vocabulary(){
	vocabulary_file.open("Searcher/util/vocabulary.txt");
  int termId;
  string term;

	while(vocabulary_file >> termId >> term){

  	if(vocabulary.find(term) == vocabulary.end()){
		  vocabulary.insert(make_pair(term, termId));    
  	} else{
  		vocabulary[term] = termId;
  	}
  } 
}

void Searcher::load_pageRank(){
    seeks_file.open("Searcher/util/pagerank.txt");
    int termId;
    double pg;
    while(seeks_file >> termId >> pg){
      pageRank.insert(make_pair(termId, pg));    
    }
}

void Searcher::load_seeks(){
    seeks_file.open("Searcher/util/term_pos.txt");
    int termId;
    unsigned long long pos_seek;
    while(seeks_file >> termId >> pos_seek){
      term_seek.insert(make_pair(termId, pos_seek));    
    }
}

void Searcher::anchor_load_seeks(){
    anchor_seeks_file.open("Searcher/util/anchor_pos.txt");
    int termId;
    unsigned long long pos_seek;
    while(anchor_seeks_file >> termId >> pos_seek){
      anchor_seek.insert(make_pair(termId, pos_seek));    
    }

}

void Searcher::load_urls(){
	urls_file.open("Searcher/util/doc_url.txt");
	string url;
  int docId;

	while(urls_file >> docId >> url){
  	if(urls.find(docId) == urls.end()){
		  urls.insert(make_pair(docId, url));   
  	} else{
  		urls[docId] = url;
  	}
	}
  num_docs = urls.size();
}

void Searcher::load_stopwords(){
  string stopword;
  ifstream f;
  f.open("Searcher/util/stopwords/portuguese.txt");
  while (getline(f, stopword)){
    stopwords.push_back(stopword);
  }
  f.close();
  ifstream f2;
  f2.open("Searcher/util/stopwords/english.txt");
  while (getline(f2, stopword)){
    stopwords.push_back(stopword);
  }
  f2.close();
};

unordered_map<int,double> Searcher::search(const string& s){
  unordered_map<int,double> result = vectorModel->search(s);
  unordered_map<int,double> ancMod = anchorRank->search(s);
  for(auto it = result.begin(); it != result.end(); it++){
    it->second = 0.85*it->second;
    if(ancMod.find(it->first) != ancMod.end()){
      it->second += 0.15*ancMod[it->first];
    }
    if(pageRank.find(it->first) != pageRank.end()){
      it->second += 10000*pageRank[it->first];
    }
  }
  for(auto it : ancMod){
    if(result.find(it.first) == result.end()){
      result.insert(make_pair(it.first, 0.15*it.second));
    }
  }
  return result;

}
unordered_map<int,double> Searcher::boolean_search(const string& s){
  return boolean->search(s);
}

unordered_map<int,double> Searcher::vectorModel_search(const string& s){
  return vectorModel->search(s);
}

unordered_map<int,double> Searcher::anchor_search(const string& s){
  return anchorRank->search(s);
}

unordered_map<int,double> Searcher::pageRank_search(const string& s){
  unordered_map<int,double> result = vectorModel->search(s);
  for(auto it : result){
    if(pageRank.find(it.first) != pageRank.end()){
      it.second += 10000*pageRank[it.first];
    }
  }
  return result;
}




