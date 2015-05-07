/*
 *  Name:           Alejandro Huerta
 *  Date:           May 10th, 2015
 *  Course:         CSCI 4350 - Artificial Intelligence
 *  Description:    main.cpp runs the Q-Learning algorithm, displays and
 *                      writes to an output file the four requirements
 *                      listed in homework document
 *  Dependencies:   AIHW4_environment.h
 */

#include <iostream>
#include "AIHW4_Environment.h"

using namespace std;

void init_intro();
AIHW4_environment init_environment();

int main() {
    // Setup prompts
    init_intro();
    AIHW4_environment environment = init_environment();
    cout << endl;

    // Display initial state of environment
    cout << "== Initial Environment ==" << endl;
    cout << environment.to_string();

    map<pair<int, int>, string> test;
    test[pair<int, int>(1, 1)] = "Hi1";
    test[pair<int, int>(1, 1)] = "Hi2";

    for (map<pair<int, int>, string>::iterator it = test.begin(); it != test.end(); ++it) {
        cout << it->first.first << ", " << it->first.second << " : " << it->second << endl;
    }

    return 0;
}

void init_intro() {
    cout << "===================================" << endl;
    cout << "= Q-Learning: Trolls and Burglars =" << endl;
    cout << "===================================" << endl;
    cout << endl;
}

AIHW4_environment init_environment() {
    string file_name;
    cout << "Enter input file name: ";
    getline(cin, file_name);
    if (!ifstream(file_name.c_str()))
        cout << "Invalid input file name!" << endl;
    return AIHW4_environment(file_name);
}