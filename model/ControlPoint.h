/**
 * @author Sargis S Yonan
 * @date 11 November 2018
 * @brief Definition of a control point, and everything you need to modify one.
 */

#pragma once

#include <cmath>
#include <cstdint>

/*
 * A target field. The field domain and co-domain states are labeled x, y 
 * respectively. The magnitude of the velocity of the control point (cp), v, is 
 * label. The angle at which the direction of the vector v makes with the
 * x state axis is the heading angle, theta.
 *
 *                   +------------------------+
 *                   |                        |
 *                   |                        |
 *                   |                        |
 *                   |                        |
 *                 y |                        |
 *                   |    __   v              |
 *                   |   |cp| --->            |
 *                   |                        |
 *                   |                        |
 *                   +------------------------+
 *                               x
 */

/*
 * Discrete State Vector := X
 *      _      _
 *     |        |
 *     |   x    |
 * X = |   y    |
 *     |   v    |
 *     | \theta |
 *     |_      _|
 */

/* Nonlinear Propagation Function := f(X[k]) 
 *
 *                 _                  _
 *                |                    |
 *                | v[k]*cos(theta[k]) |
 *                | v[k]*sin(theta[k]) |
 * f(X[k]) = dt * |         0          |
 *                |         0          |
 *                |_                  _|
 */

/* Control Input := U[k] 
 *
 *         _         _
 *        |           |
 *        |    0      |
 *        |    0      |
 * U[k] = |   v[k]    |
 *        | \theta[k] |
 *        |_         _|
 */

/*
 * Propagation model := X[k+1] = X[K] + f(X[k]) + U[k]
 */

/**
 * A class to describe, propagate, and update state space dynamics for control 
 * point models.
 *
 * @note All angles in degrees.
 */
class ControlPoint {

/**
 * Error codes for control point modification functions.
 */
 typedef enum : int8_t {
    SUCCESS = 0,
    ERROR = -1
 } ErrorCode;

public:
    /**
     * Class constructor.
     *
     * @param x0 The initial x position state.
     * @param y0 The initial y position state.
     * @param v0 The initial velocity state.
     * @param theta0 The initial heading angle state.
     */
    ControlPoint(
        const double x0, 
        const double y0, 
        const double v0, 
        const double theta0);

    static const uint8_t n_states = 4u;

    /**
     * Control update.
     *
     * @brief Updates the control input vector, U.
     *
     * @param v_in The control velocity of the control input.
     * @param theta_in The control heading angle of the control input.
     *
     * @return SUCCESS in the control input was valid. FAILURE is returned upon
     * control input failure.
     */
    ErrorCode control(const double v_in, const double theta_in);

    /**
     * Propagate the model.
     *
     * @param dt The time step since the last propagation.
     *
     * @return SUCCESS on success, ERROR on failure.
     */
    ErrorCode propagate(const double dt);

    /**
     * Getter for the control point's current state vector.
     *
     * @param[out] x The x position state.
     * @param[out] y The y position state.
     * @param[out] v The velocity state.
     * @param[out] theta The heading angle state.
     *
     * @return SUCCESS on success, ERROR on failure.
     */
    ErrorCode state(
        double &x_out,
        double &y_out,
        double &v_out,
        double &theta_out) const;

private:
    double deg_to_rad(const double deg) const;

    /**
     * The control point states.
     * @{
     */
    double x;
    double y;
    double v;
    double theta;
    /**
     * }@
     */
};