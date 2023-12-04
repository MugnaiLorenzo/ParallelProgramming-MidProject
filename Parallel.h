#ifndef MIDPROJECT_PARALLEL_H
#define MIDPROJECT_PARALLEL_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Parallel {
public:
    explicit Parallel(vector<string> text, int n);
    void countCharacterBigrams(const std::string& text, map<std::string, int>& ngramCounts, int n);
    void parallel_function();
    void printHistogram(map<string, int> &ngramCounts, int n, int i);
    string read_file(string title);
    void load_file(vector<string> &texts, int n);
    vector<double> getTime();
private:
    int n_book;
    vector<string> texts;
    vector<double> time;
};


#endif //MIDPROJECT_PARALLEL_H
