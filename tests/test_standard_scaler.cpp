#include "Group-7-project-ridge-lib/StandardScaler.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
int main(){ridge_ml::StandardScaler s; bool bad=false; try{(void)s.transform({1});}catch(const std::logic_error&){bad=true;} assert(bad); auto z=s.fit_transform({1,2,3}); assert(std::abs(z[1])<1e-12); assert(std::abs(z[0]+1.22474487139)<1e-8); s.fit({4,4}); assert(s.transform({4,5})==std::vector<double>({0,1}));}
