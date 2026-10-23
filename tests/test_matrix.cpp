#include "Group-7-project-ridge-lib/matrix.hpp"
#include <cassert>
#include <stdexcept>
#include <limits>
int main(){using namespace ridge_ml; Matrix a(2,2,{1,2,3,4}); auto t=a.transpose(); assert(t(1,0)==2); auto c=a*a; assert(c(1,1)==22); assert((a+a)(0,0)==2); assert(a.multiply(Vector{1,2})==Vector({5,11})); assert(dot(Vector{1,2},Vector{3,4})==11); bool bad=false; try{(void)a(2,0);}catch(const std::out_of_range&){bad=true;} assert(bad); bad=false; try{(void)(a+Matrix(1,2));}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)a.multiply(Vector{1});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)Matrix(2,2,Vector{1});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)Matrix(std::numeric_limits<std::size_t>::max(),2);}catch(const std::length_error&){bad=true;} assert(bad);}
