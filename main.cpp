// COMSC210 | Lab 28 | Winston Jose
// IDE Used: Visual Studio Code
// Github link: https://github.com/winstonjose01/COMSC210-lab-28-stl 


#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <numeric>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;
// Function Prototype
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);                     // Deletes a goat from the list
void add_goat(list<Goat> &trip, string [], string []);  // Adds a goat to a list
void display_trip(list<Goat> trip);                     // Prints the list of goats         
bool find_goat(list<Goat> &trip, string);               // Finds a goat from the list
void ave_age_goat(list<Goat> &trip);                    // Gets the average age of goats from the list
void sort_goat(list<Goat> &trip);                       // Sorts the goats ascending on the list
void reverse_goat(list<Goat> &trip);                    // Reverse the order of the goats
void merge_goat_trips(list<Goat> &, list<Goat> &);      // Merges 2 list of goats
void move_goats(list<Goat> &, list<Goat> &, int);       // Move a group of goats from one list to the other
void transform_goats(list<Goat> &, list<Goat> &);       // Increases the age of the goats on the list
void partition_goats(list<Goat> &, list<Goat> &);       // Partitions the list of goats based > 10 yrs ages
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
            case 1:// Adds a goat on the list to either trip1 or trip2
                {
                    int direction;
                    cout << "Adding a goat.\n";
                    cout << "Which trip do you want to add the goat? [Enter 1 or 2]: ";
                    cin >> direction;
                    while (direction < 1 || direction > 2){
                        cout << "Invalid input. Enter 1 or 2 ->";
                        cin >>  direction;
                    }
                    if (direction == 1)
                        add_goat(trip, names, colors); // Insert goat to Trip1
                    else 
                        add_goat(trip2, names, colors); // Insert goat to Trip2
                    break;
                }
            case 2: // Deletes a goat on the list from either trip1 or trip2
                {    
                    int direction;
                    cout << "Removing a goat.\n";
                    cout << "Which trip do you want to delete the goat? [Enter 1 or 2]: ";
                    cin >> direction;
                    while (direction < 1 || direction > 2){
                        cout << "Invalid input. Enter 1 or 2 ->";
                        cin >>  direction;
                    }
                    if (direction == 1)
                        delete_goat(trip);
                    else
                        delete_goat(trip2);
                    break;
                }
            case 3:  // Prints the list of goats for both trip1 and trip2    
                cout << "Displaying goat data.\n";
                cout << "\nTRIP 1 -->\n";
                display_trip(trip);
                cout << "\nTRIP 2 -->\n";
                display_trip(trip2);
                cout << endl;
                break;
            case 4: //Find a goat form 
                {
                    string name;
                    bool goat_found1 = false;
                    bool goat_found2 = false;
                    cin.clear();
                    cout << "Name of the goat you are looking for?: ";  // Prompt goat name
                    cin >> name; // Store goat name
                    cin.ignore();
                    goat_found1 = find_goat(trip,name); // Call find_goat fn passing trip1 and name
                    if (goat_found1)
                        cout << name << " is part of the Trip-1\n"; // Found goat on trip1
                    else
                        cout << name << " is not on the goat Trip-1\n";
                    goat_found2 = find_goat(trip2,name); // Call find_goat fn passing trip2 and name
                    if (goat_found2)
                        cout << name << " is part of the Trip-2\n"; // Found goat on trip2
                    else
                        cout << name << " is not on the goat Trip-2\n";
                    cout << endl;
                    break;
                }
            case 5: //Average age of goats on the trip
                cout << "\nAVERAGE AGE OF GOATS ON THE TRIP:\n";
                cout << "\nFOR TRIP-1: ";
                ave_age_goat(trip);     // Get average age for trip1
                cout << "\nFOR TRIP-2: ";
                ave_age_goat(trip2);    // Get average age for trip2
                cout << endl;
                break;
            case 6: //Sort the goats ascending by name
                cout << "\nSORTING GOATS";
                cout << "\nFOR TRIP-1: ";
                sort_goat(trip);        // Sort the goats on trip1
                display_trip(trip);     // Print the goat list of trip1 after sorting
                cout << "\nFOR TRIP-2: ";
                sort_goat(trip2);       // Sort the goats on trip2
                display_trip(trip2);    // Print the goat list of trip2 after sorting
                cout << endl;
                break;
            case 7: //Replace a goat
                cout << "\nREVERSING GOATS";
                cout << "\nFOR TRIP-1: ";
                reverse_goat(trip);     // Reverse the order of goats on trip1
                display_trip(trip);     // Print the goat list on trip1 after reversing
                cout << "\nFOR TRIP-2: ";
                reverse_goat(trip2);    // Reverse the order of goats on trip2
                display_trip(trip2);    // Print the goat list on trip2 after reversing
                cout << endl;
                break;
            case 8: // Merge goat trips for both trip1 and trip2
                cout << "\nMERGING GOAT TRIPS";
                cout << "\nTRIP 1 -->\n";
                display_trip(trip);     // Print the goat list of trip1 before merging
                cout << "\nTRIP 2 -->\n";
                display_trip(trip2);    // Print the goat list of trip2 before merging
                merge_goat_trips(trip,trip2);   // Merge goat trip1 and trip2
                break;
            case 9:// Moving a portion of goats from one trip to the other
                {
                    int direction, n;
                    cout << "\nMOVING GOATS ";
                    // Display the counts of goats from each trip
                    cout << "\nTHERE ARE " << trip.size() << " GOATS IN TRIP-1 AND " << trip2.size() << " GOATS IN TRIP-2";
                    cout << "\nMOVING FROM TRIP-1 OR TRIP-2? (Enter 1 or 2): "; // Which trip to remove goats
                    cin >> direction; // Store the goat source
                    while (direction < 1 || direction > 2) {  // Validate the selection
                        cout << "Invalid, Enter 1 or 2 --> ";
                        cin >> direction;
                     }
                    cin.ignore();
                    // Prompt how many goats will be moved
                    cout << "How many goats are moving from Trip-" << direction << "? ";
                    cin >> n;
                    cin.ignore();
                    if (direction == 1)
                        move_goats(trip,trip2,n); // Move n goats from trip1 to trip2
                    else
                        move_goats(trip2, trip, n); // Move n goats from trip2 to trip1
                    cout << "\nTHERE ARE NOW " << trip.size() << " GOATS IN TRIP-1 AND " << trip2.size() << " GOATS IN TRIP-2\n";
                    cout << endl;
                    break;
                }
            case 10: // All goats had a birthday, increase their age by 1
                cout << "\nGOATS ON TRIP-1: ";
                ave_age_goat(trip);  // Display the average age of goats on trip1
                cout << "GOATS ON TRIP-2: ";
                ave_age_goat(trip2);    // Display the average ge of goats on trip1
                cout << "\n**INCREASING THE AGE OF ALL GOATS BY 1**\n";
                transform_goats(trip,trip2); // Increase the age of all goats on both trips
                cout << "\nGOATS ON TRIP-1 AFTER INCREASING: ";
                ave_age_goat(trip); // Display the average age on trip1 after increasing 
                cout << "GOATS ON TRIP-2 AFTER INCREASING: ";
                ave_age_goat(trip2);  // Display the average age on trip2 after increasing
                break;
            case 11: // Partition the goats, group goats age > 10
                cout << "\nSEPARATING GOATS WITH AGE > 10\n";
                partition_goats(trip,trip2); // Partition goats with age > 10 on both trips
                cout << "\nTRIP 2 -->\n";
                display_trip(trip);     // Display trip1 after partitioning
                cout << "\nTRIP 2 -->\n";
                display_trip(trip2);    // Display trip2 after partitioning
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
// Main Menu functon
// arguments: No arguments
// returns: No returns
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
    cout << "[11] Partition the goats with age > 10\n";
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
// This function deletes a goat from the list
// arguments: A list of Goat objects 
// returns: No returns
void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip); // Select goat from the list and store the index
    auto it = trip.begin(); // Start iterator from the beginning of the list
    advance(it, index-1);   // Advance the iterator
    trip.erase(it);     // Use erase() method to remove the goat form the list
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

// This function adds a goat to the list
// arguments: A list of Goat objects, an array of goat names, and an array goat colors
// returns: No returns
void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES]; // generate random names
    string cl = cls[rand() % SZ_COLORS]; // generate random colors
    Goat tmp(nm, age, cl);  // Create a Goat object for adding
    trip.push_back(tmp);  // Add the goat to the trip
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

// This fuctions displays the list of goats on the trip
// arguments: A list of Goat objects
// returns: No returns
void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name()   // Use Goat get_name() method
             << " (" << gt.get_age() // Use Goat get_age() method
             << ", " << gt.get_color() << ")\n"; // Use Goat get_color() method
}
// This functions allows the user to select a goat from the list
// arguments: A list of Goat objects
// returns: An int, the position index of the goat on the list
int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp); // Displays the trip for the user to select
    cout << "Choice --> ";
    cin >> input;  // Save hte goat 
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input; 
    }
    return input;
}
// This functions finds a goat called 'name' on the goat list
// arguments: A list of Goat objects and the string 'name' of the goat
// returns: A boolean, true if the goat is found, false is not found
bool find_goat(list<Goat> &trip, string name){
    for (auto goat : trip){
        if (goat.get_name() == name) // Use Goat method get_name();
            return true;
    }
    return false;
}
// This function gets the average of the goats on the list
// arguments: A list of Goat objects
// returns: No returns
void ave_age_goat(list<Goat> &trip){
    // Use accumulate method and lambda function to total the goat ages
    int total = std::accumulate(trip.begin(), trip.end(), 0,[](int sum, const Goat& goat) {
                                    return sum + goat.get_age();
                                });
     // Output the average of the goats on the list using total / size of the list                               
    cout << "Average age: " << total/trip.size() << endl;
}

// This function sorts the goat on the list
// arguments: A list of Goat objects
// returns : No returns
void sort_goat(list<Goat> &trip){
    trip.sort(); // Use the sort method
    cout << endl;
}
// This function reverses the order of the goats on the list
// arguments: A list of Goat objects
// returns: No returns
void reverse_goat(list<Goat> &trip){
    reverse(trip.begin(),trip.end());
    cout << endl;
}
// This function merges two lists of goat trips
// arguments: Two lists of Goat objects
// returns: No returns
void merge_goat_trips(list<Goat> &trip, list<Goat> &trip2){
    // Create a a new list combining size of trip1 and trip1
    list <Goat> merged_trip(trip.size() + trip2.size());
    //Use merge method to combine both trip1 and tirp2
    merge(trip.begin(),trip.end(),trip2.begin(),trip2.end(),merged_trip.begin());
    cout << "\nMERGED TRIP --> \n";
    display_trip(merged_trip); // Display the new merged list

}
// This function moves goats a group of goats from one trip to another
// arguments: Two lists of Goat objects, trip1 and trip2 and the size of the group 'n'
// returns: No returns
void move_goats(list<Goat> &trip_from, list<Goat> &trip_to, int n){
    // Validate the size of the group to move
    if (n > trip_from.size()){
        cout << "\nUNABLE TO MOVE GOATS. THE NUMBER OF GOATS TO MOVE IS MORE THAN GOATS ON THE TRIP!";
        return;
    }

    auto it = trip_from.begin(); // Create iterator and point to the beginning of the list
    advance(it, n);  // Advance the iterator to from the beginning + n
    trip_to.splice(trip_to.end(), trip_from, trip_from.begin(), it); // Use splice() method to move the new groups
    cout << "\nGOATS MOVED SUCCESSFULLY!";

}
// This function increases the age of all goats on both trips
// arguments: Two lists of Goat objects, trip1 and trip2
// returns: No returns
void transform_goats(list<Goat> &trip, list<Goat> &trip2){
    // Use transform method() and lambda funciton to add 1 to the goats age in trip1
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat &g){ 
                                g.set_age(g.get_age() + 1); 
                                return g; });
    // Use transform method() and lambda funciton to add 1 to the goats age in trip2                         
    transform(trip2.begin(), trip2.end(), trip2.begin(), [](Goat &g2){
                                g2.set_age(g2.get_age() + 1); 
                                return g2; });

    cout << "Ages of all goats increased by 1 year.\n";
}
// This function partitions the goats list based on the condition age>10
// arguments: Two lists of Goat objects, trip1 and trip2
// returns: No returns
void partition_goats(list<Goat> &trip, list<Goat> &trip2){
    // Use partition() method and lambda function to group goats > 10 for trip1
    partition(trip.begin(), trip.end(), [](Goat &g){return g.get_age() > 10;});
    // Use partition() method and lambda function to group goats > 10 for trip1
    partition(trip2.begin(), trip2.end(), [](Goat &g2){return g2.get_age() > 10;});
    cout << "Goats older than 10 are at the beginning of the list.\n";
}