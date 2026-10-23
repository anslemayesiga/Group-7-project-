#include "Group-7-project-ridge-lib/gradient_descent.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
int main(){using namespace ridge_ml; Matrix x(3,1,{1,1,1}); GradientDescent gd(.1,200); auto r=gd.fit(x,{2,2,2}); assert(r.parameters.size()==1&&std::abs(r.parameters[0]-2)<1e-5); assert(r.cost_history.size()==200&&r.cost_history.back()<r.cost_history.front()); GradientDescent early(.1,500,0,1e-8); auto er=early.fit(x,{2,2,2}); assert(er.converged&&er.iterations_run<500); bool bad=false; try{(void)gd.fit(x,{1,2});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{GradientDescent invalid(0,1);}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)gd.fit(x,{1,2,3},{1,2});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)gd.fit(x,{1,2,3},{std::numeric_limits<double>::quiet_NaN()});}catch(const std::invalid_argument&){bad=true;} assert(bad);}
