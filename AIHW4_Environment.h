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
    int total_ponies;
    map<pair<int, int>, char> locations_copy;

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
        total_ponies = num_ponies;

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


        locations_copy = map<pair<int, int>, char>(locations);
    }

    /**
     *  @brief  Get the reward value for the given a state
     *  @param  x:  The x value for the state
     *  @param  y:  The y value for the state
     */

    double get_reward(int x, int y) {
        pair<int, int> l(x, y);
        switch (locations[l]) {
            case 'X':
                return 0;
            case '-':
                locations[l] = 'X';
                return 1;
            case 'P':
                num_ponies--;
                locations[l] = 'X';
                return 10;
            case 'T':
                return -11;
            case 'E':
                return 11;
            case 0:
                locations[l] = 'X';
                return 1;
            default:
                return 0;
        }
    }

    string pony_report() {
        return num_ponies + " / " + total_ponies;
    }

    void reset() {
        locations = map<pair<int, int>, char>(locations_copy);
        num_ponies = total_ponies;
    }

    int get_dimension() {
        return grid_dimension;
    }

    /**
     *  @brief  Find out what is in a space in the grid given (x, y)
     *  @param  x:  The x value in question
     *  @param  y:  The y value in question
     */
    char check_location(int x, int y) {
        if (x < 0 or x >= grid_dimension or y < 0 or y >= grid_dimension)
            return '#';

        pair<int, int> l(x, y);
        char output = locations[l];
        if (output != 0)
            return output;
        else
            return '-';
    }

    /**
     *  @brief  Return string with a visualization of the grid
     */
    string to_string(int x, int y) {
        stringstream ss;

        ss << "##";
        for (int i = 0; i < grid_dimension; i++) {
            ss << "##";
        }
        ss << "###" << endl;

        for (int i = 0; i < grid_dimension; i++) {
            ss << "##" << " ";
            for (int j = 0; j < grid_dimension; j++) {
                map<pair<int, int>, char>::iterator it = locations.find(pair<int, int>(j, i));
                if (x == j && y == i) {
                    ss << 'B' << " ";
                }
                else if (it != locations.end()) {
                    char c = it->second;
                    if (c == 0)
                        c = 'X';
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
