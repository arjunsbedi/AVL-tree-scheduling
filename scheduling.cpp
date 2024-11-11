#include "avlbst.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
using namespace std; 

void backtrack(vector<set<string>*> schedule, vector<string> courses, AVLTree<string, int>& avl, bool& check, int classes, int students, int slots, int x);
void helper(AVLTree<string,int>::iterator it, int i, int students, vector<set<string>*>& schedule, vector<string>& courses, string course, bool& insert);

int main(int argc, char* argv[]){

    // reading the input file and other data       
    ifstream ifstr;
    string file = argv[1];
    ifstr.open(file);

	if (!ifstr) {
		cout << "Cannot open " << file << "!" << endl;
		return 1;
	}

    int classes, students, slots;
    ifstr >> classes >> students >> slots;

    vector<set<string>*> schedule;
    vector<string> courses;
    AVLTree<string, int> avl;
    bool check = false;

    // reading in the classes 
    string temp;
    getline(ifstr, temp);

    int i = 0; 
    while (i < students) {
        getline(ifstr, temp);
        stringstream ss(temp);
        string studentClass;
        set<string>* student = new set<string>;
        string studentName;
        ss >> studentName;
        while (ss >> studentClass) {
            if (find(courses.begin(), courses.end(), studentClass) == courses.end()) {
                courses.push_back(studentClass);
            }
            student->insert(studentClass);
        }
        schedule.push_back(student);
        i++; 
    }

    backtrack(schedule, courses, avl, check, classes, students, slots, 0);

    if (check == false) {
        cout << "No Valid Solution." << endl;
    }

    return 0;
}

void backtrack(vector<set<string>*> schedule, vector<string> courses, AVLTree<string, int>& avl, bool& check, int classes, int students, int slots, int x) {
    
    if (check == true) return;

    if (x == classes) {
        check = true;
        for (auto it = avl.begin(); it != avl.end(); ++it) {
            string first = it->first;
            int second = it->second; 
            cout << first << " " << second << endl; 
        }
        return;
    }

    string course = courses[x];
    slots++; 
    for (int i = 1; i < slots; i++) {
        bool insert = true;
        for (auto it = avl.begin(); it!=avl.end(); ++it) {
            helper(it, i, students, schedule, courses, course, insert); 
        }
        
        if (insert == true) {
            pair<string, int> item(course, i); 
            avl.insert(item);
            backtrack(schedule, courses, avl, check,  classes, students, slots, x+1);
            avl.remove(course);
        }   
    }
}

void helper(AVLTree<string,int>::iterator it, int i, int students, vector<set<string>*>& schedule, vector<string>& courses, string course, bool& insert) {
    string curr = it->first;
    int sec = it->second; 
    if (sec == i) {
        for (int j = 0; j < students; j++) {
            bool has_course = false; // if it already has course 
            bool has_curr = false; // if it already has curr 
            for (auto it = schedule[j]->begin(); it != schedule[j]->end(); ++it) {
                if (*it == course) has_course = true;
                if (*it == curr) has_curr = true;
            }
            if (has_course == true && has_curr == true) insert = false;
        } 
    }
}
