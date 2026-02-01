#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const vector<string> DAYS = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
const vector<string> SHIFTS = {"morning","afternoon","evening"};

struct Employee {
    string name;
    int daysWorked;
    map<string, string> assigned; // day -> shift

    Employee(string n) : name(n), daysWorked(0) {
        for(const auto& d : DAYS) assigned[d] = "";
    }
};

// utility function to check if shift name is valid
bool isValidShift(const string& s) {
    return find(SHIFTS.begin(), SHIFTS.end(), s) != SHIFTS.end();
}

// build empty schedule
map<string, map<string, vector<string>>> buildEmptySchedule() {
    map<string, map<string, vector<string>>> schedule;
    for (auto& d : DAYS) {
        for (auto& s : SHIFTS) {
            schedule[d][s] = vector<string>();
        }
    }
    return schedule;
}

// collect preferences interactively
map<string, map<string, string>> collectPreferences(vector<Employee>& employees) {
    map<string, map<string, string>> prefs;
    for(auto& e : employees) {
        prefs[e.name] = map<string, string>();
        cout << "Enter preferences for " << e.name << endl;
        for(auto& day : DAYS) {
            cout << day << " shift (morning/afternoon/evening or enter to skip): ";
            string s;
            getline(cin, s);
            if(isValidShift(s)) {
                prefs[e.name][day] = s;
            }
        }
    }
    return prefs;
}

// assign employee preferences if space available
void assignPreferences(vector<Employee>& employees, map<string,map<string,string>>& prefs,
                       map<string,map<string,vector<string>>>& schedule) {
    for(auto& e : employees) {
        auto it = prefs.find(e.name);
        if(it == prefs.end()) continue;

        for(auto& p : it->second) {
            string day = p.first;
            string shift = p.second;
            if(e.daysWorked >= 5) continue;
            if(e.assigned[day] != "") continue;
            if(schedule[day][shift].size() < 2) {
                schedule[day][shift].push_back(e.name);
                e.assigned[day] = shift;
                e.daysWorked++;
            }
        }
    }
}

// resolve conflicts by assigning to any available shift
void resolveConflicts(vector<Employee>& employees, map<string,map<string,vector<string>>>& schedule) {
    for(auto& e : employees) {
        if(e.daysWorked >= 5) continue;
        for(auto& day : DAYS) {
            if(e.assigned[day] != "") continue;
            for(auto& s : SHIFTS) {
                if(schedule[day][s].size() < 2) {
                    schedule[day][s].push_back(e.name);
                    e.assigned[day] = s;
                    e.daysWorked++;
                    break;
                }
            }
        }
    }
}

// fill shifts with fewer than 2 employees by random eligible employees
void fillShifts(vector<Employee>& employees, map<string,map<string,vector<string>>>& schedule) {
    srand(time(0));
    for(auto& day : DAYS) {
        for(auto& shift : SHIFTS) {
            while(schedule[day][shift].size() < 2) {
                vector<Employee*> candidates;
                for(auto& e : employees) {
                    if(e.daysWorked < 5 && e.assigned[day] == "") {
                        candidates.push_back(&e);
                    }
                }
                if(candidates.empty()) break;
                int idx = rand() % candidates.size();
                schedule[day][shift].push_back(candidates[idx]->name);
                candidates[idx]->assigned[day] = shift;
                candidates[idx]->daysWorked++;
            }
        }
    }
}

// print schedule
void printSchedule(map<string,map<string,vector<string>>>& schedule) {
    for(auto& day : DAYS) {
        cout << day << endl;
        for(auto& shift : SHIFTS) {
            cout << "  " << shift << " : [";
            auto& names = schedule[day][shift];
            for(size_t i = 0; i < names.size(); i++) {
                cout << names[i];
                if(i != names.size()-1) cout << ", ";
            }
            cout << "]" << endl;
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " employee1 employee2 employee3 ..." << endl;
        return 1;
    }

    vector<Employee> employees;
    for(int i=1; i<argc; i++) {
        employees.push_back(Employee(argv[i]));
    }

    auto prefs = collectPreferences(employees);
    auto schedule = buildEmptySchedule();

    assignPreferences(employees, prefs, schedule);
    resolveConflicts(employees, schedule);
    fillShifts(employees, schedule);
    printSchedule(schedule);

    return 0;
}
