#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <numeric>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
bool find_goat(list<Goat> &trip, string);
void ave_age_goat(list<Goat> &trip);
void sort_goat(list<Goat> &trip);
void reverse_goat(list<Goat> &trip);
void merge_goat_trips(list<Goat> &, list<Goat> &);
void move_goats(list<Goat> &, list<Goat> &, int);
void transform_goats(list<Goat> &, list<Goat> &);
void partition_goats(list<Goat> &, list<Goat> &);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip, trip2;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }

    for (int i = 0; i < tripSize / 2; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip2.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                cout << "\nTRIP 1 -->\n";
                display_trip(trip);
                cout << "\nTRIP 2 -->\n";
                display_trip(trip2);
                cout << endl;
                break;
            case 4: //Find a goat
                {
                    string name;
                    bool goat_found = false;
                    cin.clear();
                    cout << "Name of the goat you are looking for?: ";
                    cin >> name;
                    cin.ignore();
                    goat_found = find_goat(trip,name);
                    if (goat_found)
                        cout << name << " is part of the trip\n";
                    else
                        cout << name << " is not on the goat trip\n";
                    cout << endl;
                    break;
                }
            case 5: //Average age of goats on the trip
                cout << "Average age of goats on the trip\n";
                ave_age_goat(trip);
                cout << endl;
                break;
            case 6: //Sort the goat
                cout << "\nSORTING GOATS";
                sort_goat(trip);
                display_trip(trip);
                cout << endl;
                break;
            case 7: //Replace a goat
                cout << "REVERSING GOATS";
                reverse_goat(trip);
                display_trip(trip);
                cout << endl;
                break;
            case 8: // Merge goat trip
                cout << "\nMERGING GOAT TRIPS";
                cout << "\nTRIP 1 -->\n";
                display_trip(trip);
                cout << "\nTRIP 2 -->\n";
                display_trip(trip2);
                merge_goat_trips(trip,trip2);
                break;
            case 9:
                {
                    int direction, n;
                    cout << "\nMOVING GOATS ";
                    cout << "\nTHERE ARE " << trip.size() << " GOATS IN TRIP-1 AND " << trip2.size() << " GOATS IN TRIP-2";
                    cout << "\nMOVING FROM TRIP-1 OR TRIP-2? (Enter 1 or 2): ";
                    cin >> direction;
                    cin.ignore();
                    cout << "How many goats are moving from Trip-" << direction << "? ";
                    cin >> n;
                    cin.ignore();
                    if (direction == 1)
                        move_goats(trip,trip2,n);
                    else
                        move_goats(trip2, trip, n);
                    cout << "\nTHERE ARE NOW " << trip.size() << " GOATS IN TRIP-1 AND " << trip2.size() << " GOATS IN TRIP-2\n";
                    cout << endl;
                    break;
                }
            case 10: // All goats had a birthday, increase their age by 1
                cout << "\nGOATS ON TRIP-1: ";
                ave_age_goat(trip);
                cout << "GOATS ON TRIP-2: ";
                ave_age_goat(trip2);
                cout << "\n**INCREASING THE AGE OF ALL GOATS BY 1**\n";
                transform_goats(trip,trip2);
                cout << "\nGOATS ON TRIP-1 AFTER INCREASING: ";
                ave_age_goat(trip);
                cout << "GOATS ON TRIP-2 AFTER INCREASING: ";
                ave_age_goat(trip2);
                break;
            case 11: // Partition the goats, group goats age > 10
                cout << "\nSEPARATING GOATS WITH AGE > 10\n";
                partition_goats(trip,trip2);
                cout << "\nTRIP 2 -->\n";
                display_trip(trip);
                cout << "\nTRIP 2 -->\n";
                display_trip(trip2);
                cout << endl;
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find a goat\n"; // 1
    cout << "[5] Get average age of goats\n";    // 2
    cout << "[6] Sort the goats\n"; // 3
    cout << "[7] Reverse the goats\n"; // 4
    cout << "[8] Merge goat trips\n"; // 5
    cout << "[9] Move goats from one trip to another trip\n"; // 6
    cout << "[10] Birthday goats, Increase their age\n";
    cout << "[11] Partition the goats\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

bool find_goat(list<Goat> &trip, string name){
    for (auto goat : trip){
        if (goat.get_name() == name)
            return true;
    }
    return false;
}

void ave_age_goat(list<Goat> &trip){
    int total = std::accumulate(trip.begin(), trip.end(), 0,[](int sum, const Goat& goat) {
                                    return sum + goat.get_age();
                                });
    cout << "Average age: " << total/trip.size() << endl;
}


void sort_goat(list<Goat> &trip){
    trip.sort();
    cout << endl;
}

void reverse_goat(list<Goat> &trip){
    reverse(trip.begin(),trip.end());
    cout << endl;
}

void merge_goat_trips(list<Goat> &trip, list<Goat> &trip2){
    list <Goat> merged_trip(trip.size() + trip2.size());
    merge(trip.begin(),trip.end(),trip2.begin(),trip2.end(),merged_trip.begin());
    cout << "\nMERGED TRIP --> \n";
    display_trip(merged_trip);

}

void move_goats(list<Goat> &trip_from, list<Goat> &trip_to, int n){
    auto it = trip_from.begin();
    advance(it, n);
    trip_to.splice(trip_to.end(), trip_from, trip_from.begin(), it);
    cout << "\nGOATS MOVED SUCCESSFULLY!";

}

void transform_goats(list<Goat> &trip, list<Goat> &trip2){

    transform(trip.begin(), trip.end(), trip.begin(), [](Goat &g){
                                g.set_age(g.get_age() + 1); 
                                return g; });
                                
    transform(trip2.begin(), trip2.end(), trip2.begin(), [](Goat &g2){
                                g2.set_age(g2.get_age() + 1); 
                                return g2; });

    cout << "Ages of all goats increased by 1 year.\n";
}

void partition_goats(list<Goat> &trip, list<Goat> &trip2){
    
    partition(trip.begin(), trip.end(), [](Goat &g){return g.get_age() > 10;});
    partition(trip2.begin(), trip2.end(), [](Goat &g2){return g2.get_age() > 10;});
    cout << "Goats older than 10 are at the beginning of the list.\n";
}