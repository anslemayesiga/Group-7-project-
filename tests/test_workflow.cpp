#include "Group-7-project-ridge-lib/data_loader.hpp"
#include "Group-7-project-ridge-lib/MinMaxScaler.hpp"
#include "Group-7-project-ridge-lib/ridge_regression.hpp"
#include "Group-7-project-ridge-lib/metrics.hpp"
#include <cassert>
#include <cmath>
int main(){using namespace ridge_ml; Matrix x(5,1,{1,2,3,4,5}); MinMaxScaler scaler; Vector raw{1,2,3,4,5}; auto scaled=scaler.fit_transform(raw); Matrix sx(5,1); for(std::size_t i=0;i<5;++i)sx(i,0)=scaled[i]; RidgeRegression model(0.0); model.fit(sx,{3,5,7,9,11}); auto yhat=model.predict(sx); assert(RegressionMetrics::mean_squared_error({3,5,7,9,11},yhat)<1e-10);}
