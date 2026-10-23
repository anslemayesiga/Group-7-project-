#include "Group-7-project-ridge-lib/MinMaxScaler.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <limits>
int main(){ridge_ml::MinMaxScaler s; bool bad=false; try{(void)s.transform({1,2});}catch(const std::logic_error&){bad=true;} assert(bad); bad=false; try{s.fit({});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{s.fit({std::numeric_limits<double>::quiet_NaN()});}catch(const std::invalid_argument&){bad=true;} assert(bad); auto v=s.fit_transform({2,4,6}); assert(v.size()==3&&v[0]==0&&v[2]==1); auto z=s.transform({3}); assert(std::abs(z[0]-.25)<1e-12); s.fit({5,5}); assert(s.transform({5,6})==std::vector<double>({0,0}));}
