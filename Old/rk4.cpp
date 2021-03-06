#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

using namespace std;

const double freq = 0.3;
const double mass = 1;

const double tmin = 0.0;
const double tmax = 10.0;
const double dt = 0.0001;

class state {
public:
  double x0, x1;
  state(double a=0.0, double b=0.0){
    x0 = a;
    x1 = b;
  }
};

// state multiplication by a scalar
state operator* (const double a, state x){
  state y;
  y.x0 = a*x.x0;
  y.x1 = a*x.x1;
  return y;
};

// addition of two states
state operator+ (state x, state y){
  state z;
  z.x0 = x.x0 + y.x0;
  z.x1 = x.x1 + y.x1;
  return z;
};

// ***************************************

state derivative(state x, double t) {
  // define the derivative (LHS of differential equation, second order)
  state dxdt;
  dxdt.x0 = x.x1;
  dxdt.x1 = - mass*pow(freq,2)*x.x0;
  return dxdt;
};

int main() {
  // initial state
  state x;
  x.x0 = 1.0;
  x.x1 = 0.0;

  double t;
  for (t=tmin; t<tmax; t+=dt){
    cout << t << " " << x.x0 << endl;

    // calculate new x
    state k1, k2, k3, k4;
    state k1s, k2s, k3s, k4s;
    k1s = x;
    k1 = dt*derivative(k1s,t);

    k2s = x+0.5*k1;
    k2 = dt*derivative(k2s,t+dt/2);

    k3s = x+0.5*k2;
    k3 = dt*derivative(k3s,t+dt/2);

    k4s = x + k3;
    k4 = dt*derivative(k4s,t+dt);

    x = x + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
  }
}
