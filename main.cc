#define EXIT_SUCCESS (0)
#define EXIT_FAILURE (1)

#include <iostream>

#include "ControlPoint.h"

int main (void) {
    double X[ControlPoint::n_states] = {0, 0, 1, 45};

    ControlPoint cp1 = ControlPoint(X[0], X[1], X[2], X[3]);
    
    for (int i = 0; i < 100; i++) {
        cp1.propagate(.01);
        cp1.state(X[0], X[1], X[2], X[3]);
        printf("X = {%f %f %f %f}\n", X[0], X[1], X[2], X[3]);
    }

    return EXIT_SUCCESS;
}