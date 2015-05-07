//
// Created by Alejandro on 5/7/2015.
//

#ifndef AIHW4_Q_LEARNING_AIHW4_BURGLAR_H
#define AIHW4_Q_LEARNING_AIHW4_BURGLAR_H

#include <utility>
#include <map>

using namespace std;

class AIHW4_burglar {
private:
    typedef pair<int, int> location;
    enum direction {
        up, right, down, left, upleft, upright, downright, downleft
    };
    location current_location;
    map<pair<location, direction>, double> Q_estimates;

public:
};


#endif //AIHW4_Q_LEARNING_AIHW4_BURGLAR_H
