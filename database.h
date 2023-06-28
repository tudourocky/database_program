#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <ncurses.h>
#include <algorithm>
#include "series.h"

using namespace std;

class Database{
    private:
    string filename = "database.txt";
    ifstream input;
    ofstream output;
    string line;
    Series show;
    vector<Series> series;

    public:
    Database();
    void update_database();
    vector<Series> get_all_series();
    Series get_serie_with_index(int n);
    void print_serie(Series show);
    void println_serie(Series show);
    
    void add_new_serie(Series show);
    
    void find_serie_by_name(const string name);
    void find_serie_by_name_exact(const string name);
    void find_serie_by_director(const string dir);
    void find_serie_by_director_exact(const string dir);
    void find_serie_by_episodes(const int epi);
    void find_serie_by_episodes(const int begin, const int end);
    void find_serie_by_rating(const int rating);
    void find_serie_by_rating(const int begin, const int end);
    
    void delete_serie(const int position);
    void delete_serie_by_name(const string name);
    void delete_serie_by_name_exact(const string name);

    void delete_serie_by_director_exact(const string dir);
    void delete_serie_by_director(const string dir);

    void delete_serie_by_rating(const int n);
    void delete_serie_by_rating(const int begin, const int end);

    void list_alpha_name();
    void list_reverse_alpha_name();
    void list_alpha_director();
    void list_reverse_alpha_director();
    void list_ascending();
    void list_descending();

    ~Database();

};

#endif