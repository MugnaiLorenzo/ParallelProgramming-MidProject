#include <map>
#include <algorithm>
#include <omp.h>
#include <fstream>
#include "Parallel.h"


Parallel::Parallel(vector<string> text, int n) {
    texts = text;
    n_book = n;
}

string Parallel::read_file(string title) {
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

void Parallel::load_file(vector<string> &texts, int n) {
    string t;
    for (int i = 0; i < n; i++) {
        t = "./Testi/book" + to_string(i) + ".txt";
        texts.push_back(read_file(t));
    }
}

void Parallel::countCharacterBigrams(const std::string &text, map<std::string, int> &ngramCounts, int n) {
#pragma omp parallel for default(none) shared(text, ngramCounts, n, std::cout)
    for (int i = 0; i < text.length() - n + 1; ++i) {
        string ngram = text.substr(i, n);
        transform(ngram.begin(), ngram.end(), ngram.begin(), ::tolower);
        if (all_of(ngram.begin(), ngram.end(), ::isalpha)) {
#pragma omp atomic
            ngramCounts[ngram]++;
        }
    }
}

void Parallel::printHistogram(map<string, int> &ngramCounts, int n, int i) {
    vector<pair<string, int> > A;
    string title_o = "./histogram/parallel/output" + std::to_string(i) + "_" + std::to_string(n) + ".txt";
    ofstream outputFile(title_o);
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

void Parallel::parallel_function() {
    double start_time, end_time;
    map<string, int> ngramCounts;
    int n, i = 0;
    for (const auto &text: texts) {
        n = 2;
        start_time = omp_get_wtime();
        countCharacterBigrams(text, ngramCounts, n);
        end_time = omp_get_wtime();
        time.push_back(end_time - start_time);
        printHistogram(ngramCounts, n, i);
//        ngramCounts.clear();
        n = 3;
        start_time = omp_get_wtime();
        countCharacterBigrams(text, ngramCounts, n);
        end_time = omp_get_wtime();
        time.push_back(end_time - start_time);
        printHistogram(ngramCounts, n, i);
//        ngramCounts.clear();
        i = i + 1;
    }
}

vector<double> Parallel::getTime() {
    load_file(texts, n_book);
    parallel_function();
    return time;
}