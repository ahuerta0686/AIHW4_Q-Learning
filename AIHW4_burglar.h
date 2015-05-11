//
// Created by Alejandro on 5/7/2015.
//

#ifndef AIHW4_Q_LEARNING_AIHW4_BURGLAR_H
#define AIHW4_Q_LEARNING_AIHW4_BURGLAR_H

#include <utility>
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include "AIHW4_Environment.h"

using namespace std;

class AIHW4_burglar {
public:
    enum direction {
        up, right, down, left, upleft, upright, downright, downleft, end
    };
public: // Switch to private after
    typedef pair<int, int> location;
    location current_location;
    map<pair<location, direction>, double> Q_estimates;
    AIHW4_environment *environment;

    /**
     *  @brief  Choose a random real number from min to max
     *  @param  min:    Beginning of range
     *  @param  max:    End of range
     */
    double random_double(double min, double max) {
        double r = (double) rand() / RAND_MAX;
        return min + r * (max - min);
    }

    /**
     *  @brief  Choose random integer [min, max]
     *  @param  min:    Beginning of range
     *  @param  max:    End of range
     */
    int random_int(int min, int max) {
        int r = rand() % (max - min + 1);
        return r + min;
    }

    /**
     *  @brief  Check if a move in a direction is valid
     *  @param  x:          The x value in question
     *  @param  y:          The y value in question
     *  @param  direction:  The direction to check is a valid move
     */
    bool valid_move(int x, int y, direction d) {
        if (x <= 0 && (d == left || d == upleft || d == downleft)) {
            return false;
        }
        else if (y <= 0 && (d == up || d == upleft || d == upright)) {
            return false;
        }
        else if (x >= environment->get_dimension() - 1 && (d == right || d == upright || d == downright)) {
            return false;
        }
        else if (y >= environment->get_dimension() - 1 && (d == down || d == downleft || d == downright)) {
            return false;
        }
        else if (x < 0 || y < 0 || x >= environment->get_dimension() || y >= environment->get_dimension()) {
            return false;
        }
        else {
            return true;
        }
    }

    /**
     *  @brief  Evaluate new Q estimate
     *  @param  x:      The x value for the state
     *  @param  y:      The y value for the state
     *  @param  d:      Direction for action a
     *  @param  alpha:  Learning rate
     *  @param  gamma:  Discount rate
     */
    double Q_update(int x, int y, direction d, double alpha, double gamma) {
        // Get old Q estimate
        location l(x, y);
        pair<location, direction> state_action(l, d);
        double old_Q = Q_estimates[state_action];

        // Get next state based on action of choice
        location l_prime;
        switch (d) {
            case up:
                l_prime.second = l.second - 1;
                break;
            case right:
                l_prime.first = l.first + 1;
                break;
            case down:
                l_prime.second = l.second + 1;
                break;
            case left:
                l_prime.first = l.first - 1;
                break;
            case upleft:
                l_prime.first = l.first - 1;
                l_prime.second = l.second - 1;
                break;
            case upright:
                l_prime.first = l.first + 1;
                l_prime.second = l.second - 1;
                break;
            case downright:
                l_prime.first = l.first + 1;
                l_prime.second = l.second + 1;
                break;
            case downleft:
                l_prime.first = l.first - 1;
                l_prime.second = l.second + 1;
                break;
        }

        // Get maximum Q value of the following state
        pair<location, direction> state_action_prime(l_prime, up);
        double Q_max = Q_estimates[state_action_prime];
        for (direction i = right; i != end; i = static_cast<direction>(static_cast<int>(i) + 1)) {
            pair<location, direction> sap(l_prime, i);
            double Q_temp = Q_estimates[sap];
            if (Q_temp > Q_max) {
                Q_max = Q_temp;
                state_action_prime = sap;
            }
        }

        double output =
                old_Q + alpha * (environment->get_reward(l_prime.first, l_prime.second) + gamma * Q_max - old_Q);
        return output;
    }


    // return true if s1 comes before s2
    struct compare_pair {
        bool operator()(pair<double, direction> const &item1, pair<double, direction> const &item2) {
            if (item1.first < item2.first) {
                return true;
            }
            else return false;
        }
    };

    /**
     *  @brief  Epsilon greedy action selection
     *  @param  x:          The x value of the state
     *  @param  y:          The y value of the state
     *  @param  epsilon:    Probability random option will be selected
     */
    direction action_selction(double epsilon) {
        location l(current_location.first, current_location.second);

        if (random_double(0, 1) < epsilon) {
            // Pick random action to do
            //bool done = false;
            while (true) {
                int random_num = random_int(0, 7);
                direction d = up;
                for (int i = 0; i < random_num; i++) {
                    d = static_cast<direction>(static_cast<int>(d) + 1);
                }
                if (valid_move(current_location.first, current_location.second, d)) {
                    return d;
                }
            }
        }
        else {
            // Greedy selection
            list<pair<double, direction> > Q_vals;
            for (direction i = up; i != end; i = static_cast<direction>(static_cast<int>(i) + 1)) {
                pair<location, direction> state_action_temp(l, i);
                double Q_temp = Q_estimates[state_action_temp];
                Q_vals.push_back(pair<double, direction>(Q_temp, i));
            }
            Q_vals.sort(compare_pair());
            for (list<pair<double, direction> >::iterator it = Q_vals.begin(); it != Q_vals.end(); ++it) {
                pair<double, direction> p = *it;
                if (valid_move(current_location.first, current_location.second, p.second)) {
                    return p.second;
                }
            }
        }
    }



public:
    AIHW4_burglar(int x, int y, AIHW4_environment &e) {
        current_location = location(x, y);
        environment = &e;
    }

    void set_position(int x, int y) {
        current_location = location(x, y);
    }

    /**
     *  @brief  Update current_location based on a given direction
     *  @param  d:  Direction of movement
     */
    bool move(direction d) {
        switch (d) {
            case up:
                current_location.second--;
                break;
            case right:
                current_location.first++;
                break;
            case down:
                current_location.second++;
                break;
            case left:
                current_location.first--;
                break;
            case upleft:
                current_location.first--;
                current_location.second--;
                break;
            case upright:
                current_location.first++;
                current_location.second--;
                break;
            case downright:
                current_location.first++;
                current_location.second++;
                break;
            case downleft:
                current_location.first--;
                current_location.second++;
                break;
        }

        if (environment->check_location(current_location.first, current_location.second) == 'E')
            return true;
        else return false;
    }

    /**
     *  @brief  Return x value of current_location
     */
    int get_x() {
        return current_location.first;
    }

    /**
     *  @brief  Return y value of current_location
     */
    int get_y() {
        return current_location.second;
    }

    /**
     *  @brief  Get the estimated Q value for Q(s, a)
     *  @param  x:  x for the state
     *  @param  y:  y for the state
     *  @param  d:  direction for the action
     *
     *  Get Q(s, a) for a given s and a. The state s is the
     *  location (x, y). The action a is the direction d.
     */
    double get_Q_estimate(int x, int y, direction d) {
        location l(x, y);
        return Q_estimates[pair<location, direction>(l, d)];
    }

    /**
     *  @brief  Update a q estimate for the burglar
     *  @param  x:  x for the state
     *  @param  y:  y for the state
     *  @param  d:  direction for the action
     *  @param  q:  new Q estimate
     *
     *  Update Q(s, a) with a new q. The state s is the location (x, y)
     *  and the action a is the direction d. The value is updated to q.
     */
    void update_Q_estimates(direction d, double alpha, double gamma) {
        location l(current_location.first, current_location.second);
        pair<location, direction> key(l, d);
        Q_estimates[key] = Q_update(current_location.first, current_location.second, d, alpha, gamma);
    }

    /**
     *  @brief  Print Q estimates, if not printed assume 0.
     */
    void print_Q_estimates() {
        for (map<pair<location, direction>, double>::iterator it = Q_estimates.begin(); it != Q_estimates.end(); ++it) {
            cout << "State: (" << it->first.first.first << ", " << it->first.first.second << "), Action: ";
            cout << it->first.second << ", Q: " << it->second << endl;
        }
    }

    void print_environment() {
        cout << environment->to_string(current_location.first, current_location.second) << endl;
    }


};


#endif //AIHW4_Q_LEARNING_AIHW4_BURGLAR_H
