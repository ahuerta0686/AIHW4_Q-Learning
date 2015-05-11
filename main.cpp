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
#include "AIHW4_burglar.h"
#include "AIHW4_Environment.h"

using namespace std;

void init_intro();
AIHW4_environment init_environment();

int main() {
    srand(time(NULL));
    // Setup prompts
    init_intro();
    AIHW4_environment environment = init_environment();
    cout << endl;

    // Display initial state of environment
    cout << "== Initial Environment ==" << endl;
    cout << environment.to_string(-1, -1) << endl;

    AIHW4_burglar b(1, 1, environment);

    double alpha = 0.75;
    double gamma = 0.5;
    double epsilon = 0.1;
    int epochs = 10000;

    for (int i = 0; i < epochs; i++) {
        bool exited = false;
        while (!exited) {
            AIHW4_burglar::direction dir = b.action_selction(epsilon);
            b.update_Q_estimates(dir, alpha, gamma);
            exited = b.move(dir);
            //cout << "== Epoch: " << i << endl;
            //cout << environment.to_string(b.get_x(), b.get_y()) << endl;
        }
        if ((i + 1) % 10 == 0) {
            cout << "== Epoch: " << i << endl;
            cout << environment.to_string(b.get_x(), b.get_y()) << endl;
        }
        environment.reset();
        b.set_position(1, 1);
//        if (i != epochs - 1)
//            environment.reset();
    }

    cout << "=== Final Environment ===" << endl;
    cout << environment.to_string(b.get_x(), b.get_y()) << endl;
    cout << "Ponies rescued: " << environment.pony_report() << endl;

    char dumb;
    cin >> dumb;
    //b.print_environment();

    return 0;
}

/*
 *  @brief  Print initial prompt
 */
void init_intro() {
    cout << "===================================" << endl;
    cout << "= Q-Learning: Trolls and Burglars =" << endl;
    cout << "===================================" << endl;
    cout << endl;
}

/*
 *  @brief  Prompt user to enter filename
 */
AIHW4_environment init_environment() {
    string file_name;
    cout << "Enter input file name: ";
    getline(cin, file_name);

    if (file_name == "")
        return AIHW4_environment("trolls1.txt");

    if (!ifstream(file_name.c_str()))
        cout << "Invalid input file name!" << endl;
    return AIHW4_environment(file_name);
}