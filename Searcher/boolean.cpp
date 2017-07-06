#include "boolean.h"

Boolean::Boolean(unordered_map<string, int>& vocabulary, unordered_map<int, string>& urls, 
  vector<string>& stopwords, unordered_map<int, unsigned long long>& term_seek){
      
      this->urls = urls;
      this->vocabulary = vocabulary;
      this->stopwords = stopwords;
      this->term_seek = term_seek;
}

Boolean::~Boolean(){

}

bool Boolean::is_stopword(const string& word){
  if( find(stopwords.begin(), stopwords.end(), word) != stopwords.end()){
    return true;
  }
  return false;
}


bool Boolean::indexable(const string& word){
  if(word.empty()){
    return false;
  }
  if(word.length() > 50 || word.length() <=1){
    return false;
  }
  if(is_stopword(word)){
    return false;
  }
  if (word.find_first_of("0123456789") != string::npos ) {
      return false;
  }
  for (int i = 0; i < word.length(); ++i){
    if(!isprint(word[i])){
      return false;
    }
  }
  return true;
}

unordered_map<int, int> Boolean::get_docsList(int term_id){
  unordered_map<int, int> result;
  unsigned long long pos;
  pos = term_seek[term_id];
  index_file.open("Searcher/util/Final_Index.txt");
  index_file.seekg(pos);
  string line;

  while(getline(index_file, line)){
    string delimiter = ",";
    int pos_delimiter = line.find(delimiter);   
    int termId = atoi(line.substr(0, pos_delimiter).c_str());

    int pos_delimiter2 = line.find(delimiter, pos_delimiter + 1);
    int docId = atoi(line.substr(pos_delimiter + 1, pos_delimiter2 - pos_delimiter).c_str());

    int pos_delimiter3 = line.find(delimiter, pos_delimiter2 + 1);
    int freq = atoi(line.substr(pos_delimiter2 + 1, pos_delimiter3 - pos_delimiter2).c_str());

    if(termId != term_id){
      break;
    }

    result[docId] = freq;
  }
  index_file.close();
  return result;
}


unordered_map<int,double> Boolean::search(const string& s){
  size_t i = 0, j = 0; // pointers to delimiter position
  string delimiter = " ,./)(}{\n\r\0\t";
  vector<string> qWords;

  // Get query terms
  while((j = s.find_first_of(delimiter, i)) != string::npos) {
    cout << s << endl;
    cout << i << " <- i,  j -> "<< j << endl;
    string word = s.substr(i, j - i);
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Remove stopwords from query
    if(!is_stopword(word) && indexable(word)){
      qWords.push_back(word);
    }

    i = j + 1;
  }
  string word = s.substr(i);
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  if(!is_stopword(word) && indexable(word)){
    qWords.push_back(word);
  }

  unordered_map<int, int> result;
  unordered_map<int,double> acc;
  bool first = true;
  for(auto term : qWords){
    int termId;
    if(vocabulary.find(term) != vocabulary.end()){
      termId = vocabulary[term];
    } else{
      cout << "No results" << endl;
      return acc;
    }

    unordered_map<int, int> docs;
    docs = get_docsList(termId);
    if(first){
      result = docs;
      first = false;
    } else{
      auto it = result.begin();
      while(it != result.end()){
        int docId = it->first;
        it++;
        if(docs.find(docId) == docs.end()){
          result.erase(docId);
        }
      }
    }

  }
    
  for(auto it : result){
    acc.insert(make_pair(it.first, it.second));
  }
  return acc;

}


