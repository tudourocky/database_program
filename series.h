#ifndef SERIES_H
#define SERIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <ncurses.h>

using namespace std;

class Series {
    private:
    string TV_Name;
    string Director;
    int Episodes;
    int Rating;

    public:

    Series(){
        TV_Name = "unknown";
        Director = "unknown";
        Episodes = 0;
        Rating = 0;
    }

    Series(string name, string cast, int ep, int r);
    
    //setters
    void set_TV_Name(string s);
    void set_Director(string s);
    void set_Episodes(int i);
    void set_Rating(int i);

    //getters
    string get_TV_Name() const;
    string get_Director() const;
    int get_Episodes() const;
    int get_Rating() const;

    ~Series();

};

#endif