#include "vectorModel.h"

bool VectorModel::cmp(pair <int, double> a, pair<int, double> b){
  return a.second > b.second;
}

VectorModel::VectorModel(int num_docs, unordered_map<string, int>& vocabulary, unordered_map<int, string>& urls, 
  vector<string>& stopwords, unordered_map<int, unsigned long long>& term_seek){
      
      this->urls = urls;
      this->vocabulary = vocabulary;
      this->stopwords = stopwords;
      this->term_seek = term_seek;
      this->num_docs = num_docs;
}

VectorModel::~VectorModel(){

}

bool VectorModel::is_stopword(const string& word){
  if( find(stopwords.begin(), stopwords.end(), word) != stopwords.end()){
    return true;
  }
  return false;
}

bool VectorModel::indexable(const string& word){
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

double VectorModel::similarity(const vector<double>& a, const vector<double>& b){
  double result = 0, dotProduct = 0, norm1 = 0, norm2 = 0;
  for(int i = 0; i < a.size(); i++){
    dotProduct += a[i] * b[i];        
  }
  for(double w1 : a){
    norm1 += w1 * w1;
  }
  for(double w2 : b){
    norm2 += w2 * w2;
  }
  norm1 = sqrt(norm1);
  norm2 = sqrt(norm2);
  result = dotProduct / (norm1 * norm2);
  return result;
}

unordered_map<int, int> VectorModel::get_docsList(int term_id){
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

unordered_map<int,double> VectorModel::search(const string& s){
  size_t i = 0, j = 0; // pointers to delimiter position
  string delimiter = " ,./)(}{\n\r\0\t";
  vector<string> qWords;
  unordered_map<int,double> accumulators;

  // Get query terms
  while((j = s.find_first_of(delimiter, i)) != string::npos) {
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



  // Calculate similarity between vectors
  for(auto term : qWords){
    if(vocabulary.find(term) != vocabulary.end()){
      int termId = vocabulary[term];
      unordered_map<int, int> docsList;
      docsList = get_docsList(termId);
      double term_weight = 1 + log(num_docs/docsList.size());
      for(auto doc : docsList){
        int docId = doc.first;
        int freq = doc.second;
        if (accumulators.find(docId) == accumulators.end()){
            accumulators[docId] = 0;
        }
        accumulators[docId] += log(1 + freq)*term_weight;
      }
    } else{
      continue;
    }
  }

  return accumulators;

}

