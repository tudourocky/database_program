#include "series.h"
#include "database.h"

Database::Database(){
    update_database();
}

void Database::update_database(){
    input.open(filename);
    string temp;
    int period = 0;
    series.clear();
    
    while(getline(input, line)){
        for(int i = 0; i < line.size(); i++) {
            if(line[i]=='|' || i == line.size()-1){
                period++;

                if (period == 1){
                    show.set_TV_Name(temp);
                }
                else if (period ==2) {
                    show.set_Director(temp);
                }
                else if (period == 3) {
                    show.set_Episodes(stoi(temp));
                }
                else{
                    temp += line[i];
                    show.set_Rating(stoi(temp));
                }
                i++;
                temp="";
            }
            else{
                temp += line[i];
            }
        }
        period = 0;
        series.push_back(show);                                                              
    }
    input.close();
}

vector<Series> Database::get_all_series(){
    return series;
}

Series Database::get_serie_with_index(int n){
    return series[n];
}

void Database::print_serie(Series show){
    string temp;
    int i;
    temp = show.get_TV_Name();
    cout << temp << ", ";
    temp = show.get_Director();
    cout << temp << ", ";
    i = show.get_Episodes();
    cout << i << ", ";
    i = show.get_Rating();
    cout << i;
}

void Database::println_serie(Series show){
    print_serie(show);
    cout << "\n";
}

void Database::add_new_serie(Series show){
    output.open(filename, ios_base::app);
    Series temp = show;
    output << "\n" + show.get_TV_Name() + "| " + show.get_Director() + "| " 
    << show.get_Episodes() << "| " << show.get_Rating();
    output.close();
    update_database();
}

void Database::find_serie_by_name_exact(const string name){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_TV_Name() == name){
            println_serie(series[i]);
            found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_name(const string name){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_TV_Name().find(name) != string::npos){
            println_serie(series[i]);
            if(found == false) found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_director(const string dir){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Director().find(dir) != string::npos){
            println_serie(series[i]);
            if(found == false) found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_director_exact(const string dir){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Director() == dir){
            println_serie(series[i]);
            found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_episodes(const int epi){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Episodes() == epi){
            println_serie(series[i]);
            found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_episodes(const int begin, const int end){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Episodes() >= begin && series[i].get_Episodes() <= end){
            println_serie(series[i]);
            found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_rating(const int rating){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Rating() == rating){
            println_serie(series[i]);
            found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::find_serie_by_rating(const int begin, const int end){
    bool found = false;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Rating() >= begin && series[i].get_Rating() <= end){
            println_serie(series[i]);
            found = true;
        }
    }
    if(found == false){
        cout << "No Match Results Found\n";
    }
}

void Database::delete_serie(const int position){
    string line;
    int firstline = 0;
    ifstream input("database.txt");
    ofstream output("temp.txt");
    int count = 0;
    while(getline(input, line)){
        if(count != position){
            if (firstline == 0){
                output << line;
                firstline++;
            }
            else output << endl << line;

        }
        ++count;
    }
    input.close();
    output.close();    
    remove("database.txt");
    rename("temp.txt","database.txt");

    update_database();
}

void Database::delete_serie_by_name_exact(const string name){
    bool found = false;
    char c;
    
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_TV_Name() == name){
            cout << "Are you sure you want to delete this TV series? (y/n)\n";
            cin >> c;
            c = tolower(c);
            while (c != 'y' && c != 'n'){
                cout << "Please enter one of the above choices: ";
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> c;
                c = tolower(c);
            }
            if(c == 'y') {
                delete_serie(i);
                i--;
            }
            found = true;
        }
    }
    if(found == false){
        cout << "---------------------------\n"
            << "No Match Results Found\n"
            << "---------------------------\n";
    }else cout << "---------------------------" << endl
                << "Deleted the selected series" << endl
                << "---------------------------" << endl;
}

void Database::delete_serie_by_name(const string name){
    bool found = false;
    bool confirmed = false;
    char c;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_TV_Name().find(name) != string::npos){
            if (confirmed == true) {
                delete_serie(i);
                i--;
            }
            else if (confirmed == false){
                cout << "Are you sure you want to delete these TV series? (y/n)\n";
                cin >> c;
                c = tolower(c);
                while (c != 'y' && c != 'n'){
                    cout << "Please enter one of the above choices: ";
                    cin.clear();
                    cin.ignore( 1000, '\n' );
                    cin >> c;
                    c = tolower(c);
                }
            if(c == 'y') {
                delete_serie(i);
                i--;
                confirmed = true;
            }
            if(found == false) found = true;
            }
            if(confirmed == false) return;
        }
    }
    if(found == false){
        cout << "---------------------------\n"
            << "No Match Results Found\n"
            << "---------------------------\n";
    }else cout << "---------------------------" << endl
                << "Deleted the selected series" << endl
                << "---------------------------" << endl;
}


void Database::delete_serie_by_director_exact(const string dir){
    bool found = false;
    char c;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Director() == dir){
            cout << "Are you sure you want to delete this TV series? (y/n)\n";
            cin >> c;
            c = tolower(c);
            while (c != 'y' && c != 'n'){
                cout << "Please enter one of the above choices: ";
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> c;
                c = tolower(c);
            }
            if(c == 'y') {
                delete_serie(i);
                i--;
            }
            found = true;
        }
    }
    if(found == false){
        cout << "---------------------------\n"
            << "No Match Results Found\n"
            << "---------------------------\n";
    }else cout << "---------------------------" << endl
                << "Deleted the selected series" << endl
                << "---------------------------" << endl;
}

void Database::delete_serie_by_director(const string dir){
    bool found = false;
    bool confirmed = false;
    char c;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Director().find(dir) != string::npos){
            if (confirmed == true){
                delete_serie(i);
                i--;
            }
            else if (confirmed == false){
                cout << "Are you sure you want to delete these TV series? (y/n)\n";
                cin >> c;
                c = tolower(c);
                while (c != 'y' && c != 'n'){
                    cout << "Please enter one of the above choices: ";
                    cin.clear();
                    cin.ignore( 1000, '\n' );
                    cin >> c;
                    c = tolower(c);
                }
                if(c == 'y') {
                    delete_serie(i);
                    i--;
                    confirmed = true;
                }
                if(found == false) found = true;
            }
            if(confirmed == false) return;
        }
    }
    if(found == false){
        cout << "---------------------------\n"
            << "No Match Results Found\n"
            << "---------------------------\n";
    }else cout << "---------------------------" << endl
                << "Deleted the selected series" << endl
                << "---------------------------" << endl;
}

void Database::delete_serie_by_rating(const int n){
    bool found = false;
    char c;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Rating() == n){
            cout << "Are you sure you want to delete this TV series? (y/n)\n";
            cin >> c;
            c = tolower(c);
            while (c != 'y' && c != 'n'){
                cout << "Please enter one of the above choices: ";
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> c;
                c = tolower(c);
            }
            if(c == 'y') {
                delete_serie(i);
                i--;
            }
            found = true;
        }
    }
    if(found == false){
        cout << "---------------------------\n"
            << "No Match Results Found\n"
            << "---------------------------\n";
    }else cout << "---------------------------" << endl
                << "Deleted the selected series" << endl
                << "---------------------------" << endl;
}

void Database::delete_serie_by_rating(const int begin, const int end){
    bool found = false;
    bool confirmed = false;
    char c;
    for(int i = 0; i < series.size(); i++){
        if(series[i].get_Rating() >= begin && series[i].get_Rating() <= end){
            if (confirmed == true){
                delete_serie(i);
                i--;
            }else if (confirmed == false){
                cout << "Are you sure you want to delete this TV series? (y/n)\n";
                cin >> c;
                c = tolower(c);
                while (c != 'y' && c != 'n'){
                    cout << "Please enter one of the above choices: ";
                    cin.clear();
                    cin.ignore( 1000, '\n' );
                    cin >> c;
                    c = tolower(c);
                }
                if(c == 'y') {
                    delete_serie(i);
                    i--;
                    confirmed = true;
                }
                found = true;
            }
            if(confirmed == false) return;
        }
    }
    if(found == false){
        cout << "---------------------------\n"
            << "No Match Results Found\n"
            << "---------------------------\n";
    }else cout << "---------------------------" << endl
                << "Deleted the selected series" << endl
                << "---------------------------" << endl;
}

void Database::list_alpha_name(){
    cout << "Listing all TV series" << endl
        << "======================================" << endl;
    string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string name;
    vector<Series> notprinted;
    notprinted = series;
    for (char c: alphabets){
        for (int i = 0; i < series.size(); i++){
            name = series[i].get_TV_Name();
            if(c == name[0]){
                println_serie(series[i]);
                notprinted[i].set_TV_Name("empty");
            }
        }
    }
    for(int i = 0; i < notprinted.size(); i++){
        if(notprinted[i].get_TV_Name() != "empty"){
            println_serie(notprinted[i]);
        }
    }
    cout << "=====================================" << endl;
}

void Database::list_reverse_alpha_name(){
    cout << "Listing all TV series" << endl
        << "======================================" << endl;
    string alphabets = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    string name;
    vector<Series> notprinted;
    notprinted = series;
    for (char c: alphabets){
        for (int i = 0; i < series.size(); i++){
            name = series[i].get_TV_Name();
            if(c == name[0]){
                notprinted[i].set_TV_Name("empty");
            }
        }
    }
    for (int i = 0; i < notprinted.size(); i++){
        if(notprinted[i].get_TV_Name() != "empty"){
            println_serie(series[i]);
        }
    }
    for (char c: alphabets){
        for (int i = 0; i < series.size(); i++){
            name = series[i].get_TV_Name();
            if(c == name[0]){
                println_serie(series[i]);
            }
        }
    }
    cout << "=====================================" << endl;
}

void Database::list_alpha_director(){
    cout << "Listing all TV series" << endl
        << "======================================" << endl;
    string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string name;
    vector<Series> notprinted;
    notprinted = series;
    for (char c: alphabets){
        for (int i = 0; i < series.size(); i++){
            name = series[i].get_Director();
            if(c == name[0]){
                println_serie(series[i]);
                notprinted[i].set_Director("empty");
            }
        }
    }
    for(int i = 0; i < notprinted.size(); i++){
        if(notprinted[i].get_Director() != "empty"){
            println_serie(notprinted[i]);
        }
    }
    cout << "=====================================" << endl;
}

void Database::list_reverse_alpha_director(){
    cout << "Listing all TV series" << endl
        << "======================================" << endl;
    string alphabets = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    string name;
    vector<Series> notprinted;
    notprinted = series;
    for (char c: alphabets){
        for (int i = 0; i < series.size(); i++){
            name = series[i].get_Director();
            if(c == name[0]){
                notprinted[i].set_Director("empty");
            }
        }
    }
    for (int i = 0; i < notprinted.size(); i++){
        if(notprinted[i].get_Director() != "empty"){
            println_serie(series[i]);
        }
    }
    for (char c: alphabets){
        for (int i = 0; i < series.size(); i++){
            name = series[i].get_Director();
            if(c == name[0]){
                println_serie(series[i]);
            }
        }
    }
    cout << "=====================================" << endl;
}

void Database::list_ascending(){
    cout << "Listing all TV series" << endl
        << "======================================" << endl;
    for(int i = 1; i <= 5; i++){
        for(int j = 0; j < series.size(); j++){
            if (i == series[j].get_Rating()){
                println_serie(series[j]);
            }
        }
    }
    cout << "=====================================" << endl;
}

void Database::list_descending(){
    cout << "Listing all TV series" << endl
        << "======================================" << endl;
    for(int i = 5; i > 0; i--){
        for(int j = 0; j < series.size(); j++){
            if (i == series[j].get_Rating()){
                println_serie(series[j]);
            }
        }
    }
    cout << "=====================================" << endl;
}

Database::~Database(){

}
