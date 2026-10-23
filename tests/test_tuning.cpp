#include "Group-7-project-ridge-lib/tuning.hpp"
#include "Group-7-project-ridge-lib/ridge_regression.hpp"
#include "Group-7-project-ridge-lib/metrics.hpp"
#include <cassert>
#include <memory>
int main(){using namespace ridge_ml; GridSearchTuner tuner([](double l){return std::make_unique<RidgeRegression>(l);}); Matrix x(4,1,{1,2,3,4}); auto r=tuner.fit(x,{3,5,7,9},x,{3,5,7,9},{0.0,.1,1.0}); assert(r.best_model&&r.best_parameter==0.0); auto pred=r.best_model->predict(x); assert(RegressionMetrics::mean_squared_error({3,5,7,9},pred)<1e-10); bool bad=false; try{(void)tuner.fit(x,{3,5,7,9},x,{3},{.1});}catch(const std::invalid_argument&){bad=true;} assert(bad); bad=false; try{(void)tuner.fit(x,{3,5,7,9},x,{3,5,7,9},{});}catch(const std::invalid_argument&){bad=true;} assert(bad); GridSearchTuner null_factory([](double)->std::unique_ptr<Regressor>{return {};}); bad=false; try{(void)null_factory.fit(x,{3,5,7,9},x,{3,5,7,9},{1});}catch(const std::runtime_error&){bad=true;} assert(bad);}
