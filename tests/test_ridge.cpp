#include "Group-7-project-ridge-lib/ridge_regression.hpp"
#include "Group-7-project-ridge-lib/ridge_cost.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
int main(){using namespace ridge_ml; Matrix x(4,1,{1,2,3,4}); Vector y{3,5,7,9}; RidgeRegression m(.01); bool bad=false; try{(void)m.predict(x);}catch(const std::logic_error&){bad=true;} assert(bad); m.fit(x,y); auto pred=m.predict(x); assert(pred.size()==4&&std::abs(pred[0]-3)<.1); assert(m.lambda()==.01); assert(std::abs(ridge_cost({1,2},{1,2},{0,1},1)-.25)<1e-12); bad=false; try{RidgeRegression invalid(-1);}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)m.predict(Matrix(2,2));}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)ridge_cost({1},{1},{0},-1);}catch(const std::invalid_argument&){bad=true;} assert(bad);}
