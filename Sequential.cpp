#include <algorithm>
#include <unordered_map>
#include <omp.h>
#include <fstream>
#include "Sequential.h"

Sequential::Sequential(vector<string> text, int n) {
    texts = text;
    n_book = n;
}

bool sortbysec(const pair<string, int> &a, const pair<string, int> &b) {
    return (a.second > b.second);
}

string Sequential::read_file(string title) {
    string text;
    ifstream newfile;
    newfile.open(title, ios::in);
    if (newfile.is_open()) {
        string currentLine;
        while (getline(newfile, currentLine)) {
            if (!currentLine.empty()) {
                text += currentLine;
                text += "\n";
            }
        }
        newfile.close();
    }
    return text;
}

void Sequential::load_file(vector<string> &texts, int n) {
    string t;
    for (int i = 0; i < n; i++) {
        t = "./Testi/book" + to_string(i) + ".txt";
        texts.push_back(read_file(t));
    }
}

void Sequential::generateNgrams(const std::string &text, map<std::string, int> &ngramCounts, int n) {
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
            ngramCounts[ngram]++;
        }
    }
}

void Sequential::printHistogram(map<string, int> &ngramCounts, int n, int i) {
    vector<pair<string, int> > A;
    string title_o = "./histogram/sequential/output" + std::to_string(i) + "_" + std::to_string(n) + ".txt";
    ofstream outputFile(title_o);
    for (auto &it: ngramCounts) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), sortbysec);
    if (outputFile.is_open()) {
        for (auto &it: A) {
            outputFile << it.first << ' ' << it.second << endl;
        }
        outputFile.close();
    }
}

void Sequential::sequential_function() {
    double start_time, end_time;
    int n, i = 0;
    map<string, int> ngramCounts;
    for (const auto &text: texts) {
        n = 2;
        start_time = omp_get_wtime();
        generateNgrams(text, ngramCounts, n);
        end_time = omp_get_wtime();
        time.push_back(end_time - start_time);
        printHistogram(ngramCounts, n, i);
        ngramCounts.clear();
        n = 3;
        start_time = omp_get_wtime();
        generateNgrams(text, ngramCounts, n);
        end_time = omp_get_wtime();
        time.push_back(end_time - start_time);
        printHistogram(ngramCounts, n, i);
        ngramCounts.clear();
        i = i + 1;
    }
}

void printHistogram(map<string, int> &ngramCounts) {
    vector<pair<string, int> > A;
    ofstream outputFile("./histogram/sequential/output.txt");
    for (auto &it: ngramCounts) {
        A.push_back(it);
    }
    sort(A.begin(), A.end());
    if (outputFile.is_open()) {
        for (auto &it: A) {
            outputFile << it.first << ' ' << it.second << endl;
        }
        outputFile.close();
    }
}

vector<double> Sequential::getTime() {
    load_file(texts, n_book);
    sequential_function();
    return time;
}

