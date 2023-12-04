#ifndef MIDPROJECT_SEQUENTIAL_H
#define MIDPROJECT_SEQUENTIAL_H
#include <string>
#include <vector>
#include <iostream>
#include <map>


using namespace std;
class Sequential {
public:
    explicit Sequential(vector<string> text, int n);
    void generateNgrams(const std::string &text, map<string, int> &ngramCounts, int n);
    void printHistogram(map<string, int> &ngramCounts, int n, int i);
    void sequential_function();
    string read_file(string title);
    void load_file(vector<string> &texts, int n);
    vector<double> getTime();
private:
    int n_book;
    vector<string> texts;
    vector<double> time;
};


#endif //MIDPROJECT_SEQUENTIAL_H
