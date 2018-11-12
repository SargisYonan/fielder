/**
 * @author Sargis S Yonan
 * @date 11 November 2018
 * @brief Definition of a control point, and everything you need to modify one.
 */

#include "ControlPoint.h"

#include <cmath>

ControlPoint::ControlPoint(
    const double x0, 
    const double y0, 
    const double v0, 
    const double theta0) :

    x(x0),
    y(y0),
    v(v0),
    theta(theta0) {
}

ControlPoint::ErrorCode ControlPoint::control(const double v_in, const double theta_in) {
    v = v_in;
    theta = theta_in;

    return SUCCESS;
}

ControlPoint::ErrorCode ControlPoint::propagate(const double dt) {
    x = x + v*dt*cos(deg_to_rad(theta));
    y = y + v*dt*sin(deg_to_rad(theta));

    return SUCCESS;
}

ControlPoint::ErrorCode ControlPoint::state(
    double &x_out, 
    double &y_out, 
    double &v_out, 
    double &theta_out) const {
    x_out = x;
    y_out = y;
    v_out = v;
    theta_out = theta;

    return SUCCESS;
}

inline double ControlPoint::deg_to_rad(const double deg) const { 
    return (M_PI * deg) / 180.0; 
}
