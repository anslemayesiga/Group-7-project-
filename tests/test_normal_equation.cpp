#include "Group-7-project-ridge-lib/normal_equation.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
int main(){using namespace ridge_ml; Matrix a(2,2,{0,1,1,1}); auto x=gaussian_solve(a,{2,3}); assert(std::abs(x[0]-1)<1e-10&&std::abs(x[1]-2)<1e-10); Matrix f(3,2,{1,1,1,2,1,3}); auto w=fit_normal_equation(f,{5,8,11}); assert(std::abs(w[0]-2)<1e-9&&std::abs(w[1]-3)<1e-9); bool bad=false; try{(void)fit_normal_equation(Matrix(2,1),{1});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)gaussian_solve(Matrix(2,2,{1,2,2,4}),{3,6});}catch(const std::runtime_error&){bad=true;} assert(bad); bad=false; try{(void)gaussian_solve(Matrix(2,1),{1,2});}catch(const std::invalid_argument&){bad=true;} assert(bad);}
