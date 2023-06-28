#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <ncurses.h>

class Menu{
    private:
    char option;
    Database dt;
    
    public:
    Menu();
    void start_program();
    void add_series();
    void find_series();
    void delete_series();
    void list_series();
    ~Menu();

};

#endif