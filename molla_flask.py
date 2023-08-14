from flask import Flask, request, render_template, jsonify
import numpy as np
from sklearn.ensemble import RandomForestRegressor
import pickle

app = Flask(__name__)

# 머신러닝 모델 로드 (모델 파일 경로는 실제 경로에 맞게 수정해야 합니다.)
with open('molla.pkl', 'rb') as file:
    model = pickle.load(file)

@app.route('/predict_weight', methods=['POST'])
def predict_weight():
    # 아두이노로부터 로드셀의 평균 가중치 데이터를 받습니다.
    data = request.json
    loadcell_value = float(data['currentWeight'])

    # 데이터를 모델 입력에 맞게 변형
    input_data = np.array([loadcell_value]).reshape(1,-1)

    # 모델 예측
    prediction = model.predict(input_data)
    return jsonify({"prediction": prediction[0]})

if __name__ == '__main__':
    app.run(debug=True)
