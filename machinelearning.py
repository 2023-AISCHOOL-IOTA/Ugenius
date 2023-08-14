import pandas as pd
import pickle
from sklearn.ensemble import RandomForestRegressor

# 데이터 생성
list1 = []
for i in range(100):
    for j in range(100):
        result = (i + (i-j)) if i > j else (j + (j-i))
        list1.append([i,j,result])

# DataFrame 생성
data1 = pd.DataFrame(list1, columns=['N1', 'N2', 'Result'])

# 문제(X)와 정답(y)으로 분리
X = data1[['N1', 'N2']]
y = data1['Result']

        # 모델 예측
# 모델 생성 및 학습
random_forest = RandomForestRegressor()
random_forest.fit(X, y)

# 모델을 'molla.pkl' 파일로 저장
with open('molla.pkl', 'wb') as f:
    pickle.dump(random_forest, f)