#include "Group-7-project-ridge-lib/linear_regression.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
int main(){using namespace ridge_ml; Matrix x(3,1,{1,2,3}); Vector y{3,5,7}; LinearRegression m; bool bad=false; try{m.predict(x);}catch(const std::logic_error&){bad=true;} assert(bad); m.fit(x,y); auto p=m.predict(x); assert(std::abs(p[1]-5)<1e-8); assert(m.coefficients().size()==2);}
