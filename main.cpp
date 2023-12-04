#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "Sequential.h"
#include "Parallel.h"

using namespace std;

int main() {
    vector<double> sequential_time, parallel_time;
    double sequential_time_med = 0, parallel_time_med = 0;
    vector<string> texts;
    int n_book = 15;
    Sequential s = *new Sequential(texts, n_book);
    Parallel p = *new Parallel(texts, n_book);
    sequential_time = s.getTime();
    parallel_time = p.getTime();
    cout << "Tempi di esecuzione Sequenziali:" << endl;
    for (double i: sequential_time) {
        cout << i << endl;
        sequential_time_med += i;
    }
    sequential_time_med = sequential_time_med / n_book;
    cout << "Tempi di esecuzione Paralleli:" << endl;
    for (double i: parallel_time) {
        cout << i << endl;
        parallel_time_med += i;
    }
    parallel_time_med = parallel_time_med / n_book;
    cout << "Tempi di esecuzione Sequenziali medio: " + to_string(sequential_time_med) << endl;
    cout << "Tempi di esecuzione Paralleli medio: " + to_string(parallel_time_med) << endl;
    float approx = round((sequential_time_med / parallel_time_med) * 100) / 100;
    cout << "Il tempo parallelo risulta " << approx << " più veloce" << endl;
}