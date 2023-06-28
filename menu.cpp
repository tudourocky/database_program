#include "series.h"
#include "database.h"
#include "menu.h"

Menu::Menu(){

}

void Menu::start_program(){
    bool quit = false;
    while(quit == false){
        cout << "Welcome to the TV Series Database!" << endl 
            << "-----------------------------" << endl
            << "(A)dd a TV Serie." << endl
            << "(F)ind a TV Serie." << endl
            << "(D)elete a TV Serie." << endl
            << "(L)ist TV Series." << endl
            << "(Q)uit." << endl
            << "Enter the letter of your choice:" << endl;
        cin >> option;
        option = toupper(option);
        while (option != 'A' && option != 'F' && option != 'D' && option != 'L' && option != 'Q') {
            cout << "Please selection one of the options listed above!" << endl;
            cout << "Enter the letter of your choice:" << endl;
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        switch(option){
            case 'A':
            add_series();
            break;
            case 'F':
            find_series();
            break;
            case 'D':
            delete_series();
            break;
            case 'L':
            list_series();
            break;
            case 'Q':
            quit = true;
            break;
        }
    }
}

void Menu::add_series(){
    Series se;
    string temp1 = "";
    string temp2 = "";
    int n1 = 0;
    int n2 = 0;
    cout << "Add a new TV serie!" << endl
        << "-------------------" << endl
        << "Please enter the name of the TV serie: " << endl;
    cin.ignore();
    getline(cin, temp1);
    se.set_TV_Name(temp1);
    cout << "Please enter the director of the TV serie: " << endl;
    getline(cin, temp2);
    se.set_Director(temp2);
    cout << "Please enter the number of episodes:" << endl;
    cin >> n1;
    while (n1 < 1 || n1 > 635) // the longest TV series has 635 episodes according to Google
    {
        cout << "Please enter a valid episode number:" << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        cin >> n1;
    }
    se.set_Episodes(n1);
    cout << "Please enter the rating of the TV serie: (an interger between 1 to 5) " << endl;
    cin >> n2;
    while (n2 < 1 || n2 > 5){
        cout << "Please enter a valid rating: " << endl;
        cin.clear();
        cin.ignore( 1000, '\n' );
        cin >> n2;
    }
    vector<Series> s = dt.get_all_series();
    for (int i = 0; i < s.size(); i++){
        if (s[i].get_TV_Name() == se.get_TV_Name() && s[i].get_Director() == se.get_Director()) {
            cout << "This TV Serie has been entered before! \n";
            return;
        }
    }
    se.set_Rating(n2);
    dt.add_new_serie(se);
    dt.update_database();
}

void Menu::find_series(){
    cout << "Find a Song" << endl
        << "-----------" << endl
        << "You can search by:" << endl
        << "(N)ame of the TV Serie" << endl
        << "(E)xact name of the TV Serie" << endl
        << "(D)irector of the TV Serie" << endl
        << "(T)he exact director of the TV Serie" << endl
        << "(L)ength of the TV serie" << endl
        << "(R)ating of the TV serie" << endl << endl
        << "(G)o back to main menu" << endl
        << "\nEnter the letter of your choice:"<< endl;
    cin >> option;
    option = toupper(option);
    while(option != 'N' && option != 'D' && option != 'L' && option != 'R' && option != 'G' && option != 'E' && option != 'T'){
        cout << "Please enter one of the above choices: ";
        cin.clear();
        cin.ignore( 1000, '\n' );
        cin >> option;
        option = toupper(option);
    }
    if(option == 'N'){
        cout << "Please enter the name of the TV Series: \n";
        string temp;
        cin.ignore();
        getline(cin, temp);
        cout << "\nSearch Results" << endl
            << "----------------" << endl;
        dt.find_serie_by_name(temp);
        cout << "----------------\n" << endl << endl;
    }else if(option == 'E'){
        cout << "Please enter the exact name of the TV Series: \n";
        string temp;
        cin.ignore();
        getline(cin, temp);
        cout << "\nSearch Results" << endl
            << "----------------" << endl;
        dt.find_serie_by_name_exact(temp);
        cout << "----------------\n" << endl << endl;
    }else if(option == 'D'){
        cout << "Please enter the name of the Director: \n";
        string temp;
        cin.ignore();
        getline(cin, temp);
        cout << "\nSearch Results" << endl
            << "----------------" << endl;
        dt.find_serie_by_director(temp);
        cout << "----------------\n" << endl << endl;
    }else if(option == 'T'){
        cout << "Please enter the name of the Director: \n";
        string temp;
        cin.ignore();
        getline(cin, temp);
        cout << "\nSearch Results" << endl
            << "----------------" << endl;
        dt.find_serie_by_director_exact(temp);
        cout << "----------------\n" << endl << endl;
    }else if(option == 'L'){
        cout << "Find series by episodes" << endl
            << "------------------------" << endl
            << "(A) Find series by one number" << endl
            << "(B) Find series by range" << endl;
        cin.ignore();
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'B'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if (option == 'A'){
        cout << "Please enter the number of episodes: \n";
        int temp = 0;
        cin >> temp;
        while (temp < 1 || temp > 635) // the longest TV series has 635 episodes according to Google
        {
            cout << "Please enter a valid episode number:" << endl;
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> temp;
        }
        cout << "\nSearch Results" << endl
            << "----------------" << endl;
        dt.find_serie_by_episodes(temp);
        cout << "----------------\n" << endl << endl;
        }else if (option == 'B'){
            cout << "Please enter the starting number: \n";
            cin.ignore();
            int n1 = 0;
            int n2 = 0;
            cin >> n1;
            while (n1 < 1 || n1 > 635) // the longest TV series has 635 episodes according to Google
            {
                cout << "Please enter a valid episode number:" << endl;
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> n1;
            }
            cout << "Please enter the ending number\n";
            cin >> n2;
            while (n2 < 1 || n2 > 635) // the longest TV series has 635 episodes according to Google
            {
                cout << "Please enter a valid episode number:" << endl;
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> n2;
            }
            cout << "\nSearch Results" << endl
                << "----------------" << endl;
            dt.find_serie_by_episodes(n1, n2);
            cout << "----------------\n" << endl << endl;
            }
    }else if(option == 'R'){
        cout << "Find series by rating" << endl
            << "------------------------" << endl
            << "(A) Find series by one number" << endl
            << "(B) Find series by range" << endl;
        cin.ignore();
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'B'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if (option == 'A'){
        cout << "Please enter the rating: \n";
        int temp = 0;
        cin >> temp;
        while (temp < 1 || temp > 5) // the longest TV series has 635 episodes according to Google
        {
            cout << "Please enter a valid rating number:" << endl;
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> temp;
        }
        cout << "\nSearch Results" << endl
            << "----------------" << endl;
        dt.find_serie_by_rating(temp);
        cout << "----------------\n" << endl << endl;
        }else if (option == 'B'){
            cout << "Please enter the starting number: \n";
            cin.ignore();
            int n1 = 0;
            int n2 = 0;
            cin >> n1;
            while (n1 < 1 || n1 > 5)
            {
                cout << "Please enter a valid rating number:" << endl;
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> n1;
            }
            cout << "Please enter the ending number\n";
            cin >> n2;
            while (n2 < 1 || n2 > 5)
            {
                cout << "Please enter a valid rating number:" << endl;
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> n2;
            }
            cout << "\nSearch Results" << endl
                << "----------------" << endl;
            dt.find_serie_by_rating(n1, n2);
            cout << "----------------\n" << endl << endl;
        }
    }else if(option == 'G'){
        return;
    }
}

void Menu::delete_series(){
    cout << "Delete a TV series" << endl
        << "------------------" << endl
        << "Delete by (N)ame" << endl
        << "Delete by (D)irector" << endl
        << "Delete by (R)ating" << endl
        << "(G)o Back to main menu" << endl;
    cin >> option;
    option = toupper(option);
    while(option != 'N' && option != 'D' && option != 'R' && option != 'G'){
        cout << "Please enter one of the above choices: ";
        cin.clear();
        cin.ignore( 1000, '\n' );
        cin >> option;
        option = toupper(option);
    }
    if (option == 'N'){
        cout << "Delete TV series by name" << endl
            << "------------------------" << endl
            << "(A) Delete the series with the exact name" << endl
            << "(B) Delete all series that include the word" << endl;
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'B'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if (option == 'A'){
            string temp;
            cout << "Please enter the name of the TV series that you wanted to delete:\n";
            cin.ignore();
            getline(cin, temp);
            cout << "\nPending Delete" << endl
                << "----------------" << endl;
            dt.find_serie_by_name_exact(temp);
            cout << "----------------\n";
            dt.delete_serie_by_name_exact(temp);
        }else if (option == 'B'){
            string temp;
            cout << "Please enter the name of the TV series that you wanted to delete:\n";
            cin.ignore();
            getline(cin, temp);
            cout << "\nPending Delete" << endl
                << "----------------" << endl;
            dt.find_serie_by_name(temp);
            cout << "----------------\n";
            dt.delete_serie_by_name(temp);
        }
    }else if (option == 'D'){
        cout << "Delete TV series by director" << endl
            << "------------------------" << endl
            << "(A) Delete the series with the exact director" << endl
            << "(B) Delete all series that include the word" << endl;
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'B'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if (option == 'A'){
            string temp;
            cout << "Please enter the name of the TV series that you wanted to delete:\n";
            cin.ignore();
            getline(cin, temp);
            cout << "\nPending Delete" << endl
                << "----------------" << endl;
            dt.find_serie_by_director_exact(temp);
            cout << "----------------\n";
            dt.delete_serie_by_director_exact(temp);
        }else if (option == 'B'){
            string temp;
            cout << "Please enter the name of the TV series that you wanted to delete:\n";
            cin.ignore();
            getline(cin, temp);
            cout << "\nPending Delete" << endl
                << "----------------" << endl;
            dt.find_serie_by_director(temp);
            cout << "----------------\n";
            dt.delete_serie_by_director(temp);
        }
    }else if(option == 'R'){
        cout << "Delete series by rating" << endl
            << "------------------------" << endl
            << "(A) Delete series by one number" << endl
            << "(B) Delete series by range" << endl;
        cin.ignore();
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'B'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if (option == 'A'){
        cout << "Please enter the rating: \n";
        int temp = 0;
        cin >> temp;
        while (temp < 1 || temp > 5)
        {
            cout << "Please enter a valid rating number:" << endl;
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> temp;
        }
        cout << "\nPending Delete" << endl
            << "----------------" << endl;
        dt.find_serie_by_rating(temp);
        cout << "----------------\n";
        dt.delete_serie_by_rating(temp);
        }else if (option == 'B'){
            cout << "Please enter the starting number: \n";
            cin.ignore();
            int n1 = 0;
            int n2 = 0;
            cin >> n1;
            while (n1 < 1 || n1 > 5)
            {
                cout << "Please enter a valid rating number:" << endl;
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> n1;
            }
            cout << "Please enter the ending number\n";
            cin >> n2;
            while (n2 < 1 || n2 > 5)
            {
                cout << "Please enter a valid rating number:" << endl;
                cin.clear();
                cin.ignore( 1000, '\n' );
                cin >> n2;
            }
            cout << "\nPending Delete" << endl
            << "----------------" << endl;
            dt.find_serie_by_rating(n1, n2);
            cout << "----------------\n";
            dt.delete_serie_by_rating(n1, n2);
        }
    }
}

void Menu::list_series(){
    cout << "List TV series" << endl
        << "--------------" << endl
        << "List by (N)ame" << endl
        << "List by (D)irector" << endl
        << "List by (R)ating" << endl
        << "(G)o Back to main menu" << endl;
    cin >> option;
    option = toupper(option);
    while(option != 'N' && option != 'D' && option != 'R' && option != 'G'){
        cout << "Please enter one of the above choices: ";
        cin.clear();
        cin.ignore( 1000, '\n' );
        cin >> option;
        option = toupper(option);
    }
    if (option == 'N'){
        cout << "List by name" << endl
            << "--------------" << endl
            << "(A)lphabetical order" << endl
            << "(R)everse alphabetical order" << endl;
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'R'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if(option == 'A'){
            dt.list_alpha_name();
        }else{ // option == 'R
            dt.list_reverse_alpha_name();
        }
    }else if(option == 'D'){
        cout << "List by director" << endl
            << "--------------" << endl
            << "(A)lphabetical order" << endl
            << "(R)everse alphabetical order" << endl;
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'R'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if(option == 'A'){
            dt.list_alpha_director();
        }else{ // option == 'R
            dt.list_reverse_alpha_director();
        }
    }else if(option == 'R'){
        cout << "List by rating" << endl
            << "--------------" << endl
            << "(A)scending order" << endl
            << "(D)escending order" << endl;
        cin >> option;
        option = toupper(option);
        while(option != 'A' && option != 'D'){
            cout << "Please enter one of the above choices: ";
            cin.clear();
            cin.ignore( 1000, '\n' );
            cin >> option;
            option = toupper(option);
        }
        if(option == 'A'){
            dt.list_ascending();
        }else{ // option == 'R
            dt.list_descending();
        }
    }else if(option == 'G'){
        return;
    }
}

Menu::~Menu(){

}