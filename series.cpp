#include "series.h"

Series::Series(string name, string dir, int ep, int r)
: TV_Name(name), Director(dir), Episodes(ep), Rating(r)
{ 

}

void Series::set_TV_Name(string s){
    TV_Name = s;
}

void Series::set_Director(string s){
    Director = s;
}

void Series::set_Episodes(int i){
    Episodes = i;
}

void Series::set_Rating(int i){
    Rating = i;
}

string Series::get_TV_Name() const{
    return TV_Name;
}

string Series::get_Director() const{
    return Director;
}

int Series::get_Episodes() const{
    return Episodes;
}

int Series::get_Rating() const{
    return Rating;
}

Series::~Series(){

}