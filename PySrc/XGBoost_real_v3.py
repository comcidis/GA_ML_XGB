import pandas as pd
from sklearn.model_selection import train_test_split
import xgboost as xgb
from sklearn.metrics import accuracy_score
import sys

# print(f"Arguments count: {len(sys.argv)}")
# for i, arg in enumerate(sys.argv):
#     print(f"Argument {i:>6}: {arg}")

df = pd.read_csv('/mnt/storage/andre/BaseReal/HIGGS-5milhoes-28att.csv', sep=',')

x = df.iloc[:,1:].values
y = df.iloc[:,0].values

#separa dados em teste e treino
x_train, x_test, y_train, y_test = train_test_split(x,y,test_size=0.25)

#cria as matrizes para o XGBoost
dtrain = xgb.DMatrix(x_train, y_train)
dtest = xgb.DMatrix(x_test, y_test)

#para execução na CPU
param = {'max_depth':int(sys.argv[1]), 'eta':float(sys.argv[2]), 'n_jobs':int(sys.argv[3]), 'tree_method':'hist', 'objective':'multi:softmax', 'num_class':2, 'eval_metric':'auc'}



#para execução na GPU
#param = {'max_depth':int(sys.argv[1]), 'eta':float(sys.argv[2]), 'n_jobs':int(sys.argv[3]), 'tree_method':'gpu_hist', 'objective':'multi:softmax', 'num_class':2, 'eval_metric':'auc'}
#print(param)
#VALORES DOS PARAMETROS PARA VARIAR 
#max_deph: 3, 6 e 9
#eta: 0.3, 0.5 e 1
#n_jobs: -1 e 1
#n_estimators: 100 e 200   

#treinamento
n_estimators = int(sys.argv[4])
#p= {' n_estimators ', n_estimators}
#print( param, p)

bst = xgb.train(param, dtrain, n_estimators)
#bst = xgb.train(param, dtrain)

#predicao
preds = bst.predict(dtest)

#acuracia
accuracy = accuracy_score(y_test, preds)
#print(accuracy)

f = open("accuracy.dat", "a")
print('Accuarcy:', accuracy, file=f)
f.close