import xgboost as xgb
import pandas as pd
from sklearn.datasets import load_boston
from sklearn.model_selection import train_test_split
from sklearn.model_selection import cross_val_score, KFold
from sklearn.metrics import mean_squared_error
from sklearn.metrics import accuracy_score
#import matplotlib.pyplot as plt 
import sys
 
# boston = load_boston()
# X, y = boston.data, boston.target

dataframe = pd.read_csv("/mnt/storage/andre/GA-CNN/datasets/For_modeling.csv")
data = dataframe.values
#split data into input and output columns
X, y = data[:, :-1], data[:, -1]
xtrain, xtest, ytrain, ytest = train_test_split(X, y, test_size=0.15)

xgbr = xgb.XGBRegressor(verbosity=1, max_depth=int(sys.argv[1]), learning_rate=float(sys.argv[2]), n_jobs=int(sys.argv[3]), n_estimators=int(sys.argv[4]), 
                        colsample_bytree=1, tree_method = 'hist', predictor = 'cpu_predictor')
#print(xgbr)
# xgbr = xgb.XGBRegressor(base_score=0.5, booster='gbtree', colsample_bylevel=1,
#        colsample_bynode=1, colsample_bytree=1, gamma=0,
#        importance_type='gain', learning_rate=0.1, max_delta_step=0,
#        max_depth=3, min_child_weight=1, missing=None, n_estimators=100,
#        n_jobs=1, nthread=None, objective='reg:linear', random_state=0,
#        reg_alpha=0, reg_lambda=1, scale_pos_weight=1, seed=None,
#        silent=None, subsample=1, verbosity=1)
# print(xgbr)
xgbr.fit(xtrain, ytrain)
 
score = xgbr.score(xtrain, ytrain)   
#print("Training score: ", score) 

 
# # - cross validataion 
# scores = cross_val_score(xgbr, xtrain, ytrain, cv=5)
# print("Mean cross-validation score: %.2f" % scores.mean())

# kfold = KFold(n_splits=10, shuffle=True)
# kf_cv_scores = cross_val_score(xgbr, xtrain, ytrain, cv=kfold, n_jobs=-1)
# print("K-fold CV average score: %.2f" % kf_cv_scores.mean())
# print(kf_cv_scores)
 
ypred = xgbr.predict(xtest)
mse = mean_squared_error(ytest, ypred)
#accuracy = accuracy_score(ytest, ypred)
#print("MSE: %.6f" % mse)
#print("RMSE: %.6f" % (mse**(1/2.0)))
#print("Accuracy %.6f"% accuracy)

f = open("accuracy.dat", "a")
print('MSE:', mse, file=f)
f.close

# x_ax = range(len(ytest))
# plt.scatter(x_ax, ytest, s=5, color="blue", label="original")
# plt.plot(x_ax, ypred, lw=0.8, color="red", label="predicted")
# plt.legend()
# plt.show()
