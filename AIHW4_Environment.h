//
// Created by Alejandro on 5/3/2015.
//

#ifndef AIHW4_Q_LEARNING_AIHW4_ENVIRONMENT_H
#define AIHW4_Q_LEARNING_AIHW4_ENVIRONMENT_H

#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

class AIHW4_environment {
private:
    bool valid_file;
    map<pair<int, int>, char> locations;
    int grid_dimension;
    int num_trolls;
    int num_ponies;

    /**
     *  @brief  Convert string to vector of tokens
     *  @param  s:  String to tokenize.
     */
    vector<string> tokenize_string(string s) {
        istringstream iss(s);
        vector<string> t;
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(t));
        return t;
    }

public:
    /**
     *  @brief  Loads the initial configuration for an environment
     *  @param  path:    The path to the input file
     *
     *  Loads the initial configuration of an environment using
     *  the input file provided. Boolean valid_file is set true
     *  if the file was properly loaded, false otherwise
     */
    AIHW4_environment(string path) {
        ifstream in_file;
        in_file.open(path.c_str());
        string current_line;
        vector<string> tokens;

        // Read in N, # of trolls, and # of ponies
        getline(in_file, current_line);
        tokens = tokenize_string(current_line);
        grid_dimension = atoi(tokens[0].c_str());
        num_trolls = atoi(tokens[1].c_str());
        num_ponies = atoi(tokens[2].c_str());

        // Read in escape location
        getline(in_file, current_line);
        tokens = tokenize_string(current_line);
        {
            int x = atoi(tokens[0].c_str());
            int y = atoi(tokens[1].c_str());
            locations[pair<int, int>(x, y)] = 'E';
        }

        // Read in pony locations
        getline(in_file, current_line);
        tokens = tokenize_string(current_line);
        for (int i = 0; i < tokens.size(); i += 2) {
            int x = atoi(tokens[i].c_str());
            int y = atoi(tokens[i + 1].c_str());
            locations[pair<int, int>(x, y)] = 'P';
        }

        // Read in obstructions
        getline(in_file, current_line);
        tokens = tokenize_string(current_line);
        for (int i = 0; i < tokens.size(); i += 2) {
            int x = atoi(tokens[i].c_str());
            int y = atoi(tokens[i + 1].c_str());
            locations[pair<int, int>(x, y)] = 'X';
        }

        // Read in troll locations
        getline(in_file, current_line);
        tokens = tokenize_string(current_line);
        for (int i = 0; i < tokens.size(); i += 2) {
            int x = atoi(tokens[i].c_str());
            int y = atoi(tokens[i + 1].c_str());
            locations[pair<int, int>(x, y)] = 'T';
        }
    }

    /**
     *  @brief  Display visualization of the environment
     */
    string to_string() {
        stringstream ss;

        ss << endl << "##";
        for (int i = 0; i < grid_dimension; i++) {
            ss << "##";
        }
        ss << "###" << endl;

        for (int i = 0; i < grid_dimension; i++) {
            ss << "##" << " ";
            for (int j = 0; j < grid_dimension; j++) {
                map<pair<int, int>, char>::iterator it = locations.find(pair<int, int>(j, i));
                if (it != locations.end()) {
                    char c = it->second;
                    ss << c << " ";
                }
                else {
                    ss << "-" << " ";
                }
            }
            ss << "##" << endl;
        }
        ss << "##";
        for (int i = 0; i < grid_dimension; i++) {
            ss << "##";
        }
        ss << "###" << endl;

        return ss.str();
    }
};


#endif //AIHW4_Q_LEARNING_AIHW4_ENVIRONMENT_H
