# Code Structure
```
├── code/                   
│   ├── webserver.py
│   ├── utils.py                                
│   ├── data_processing.py                               
│   ├── inference.py                            
│   └── train.py                    
│
├── model/                     
│     ├── tesk1.dat
│     └── tesk2.dat                         
├── result/                     
│     ├── tesk1.txt
│     └── tesk2.txt
└── templates/                        
      └── class.html
    
```

# 실행 방법
  * Train Model
  ``` 
    python train.py --tesk_number [input] --output_modelname [input]

  ```
testk_number: 몇번 째, Tesk인지 지정하여 Tesk에 맞는 Model을 학습합니다.
 
output_modelname: 저장될 Model의 Name을 정합니다.

  * Inference
  ``` 
    python inference.py --model_path [input] --tesk_number [input] --save_text_name [input]

  ```
model_path : 학습한 Model이 저장된 Path를 입력합니다.
 
tesk_number : 몇번 째, Tesk를 inference 할 것인지 입력합니다.

save_text_name : Testdataset의 Class를 예측 한, Text 파일의 이름을 입력합니다.
  
  * Webserver
  ``` 
    python webserver.py 
  
  ```
 
# 데이터 탐색
## Sparse Dataset
![Data불균형](https://user-images.githubusercontent.com/59689327/142750853-e3a022e9-d3b7-4aef-992f-517c369b1e37.PNG)
- class가 매우 불균형하게 분포되어 있음
- Column[1]의 경우 무언가를 embedding 한 것같은 자료형
- 결측치는 없음
- 날짜데이터를 전처리해야할 필요성
- Data의 Size는 10만 개 Column은 총 8개
- Column[2]와 Class의 상관관계는 0.4로 Column들 중 가장 높았음

## Dense Dastaset
- Data의 Size는 10만 개 Column은 총 200개
- 결측치는 없음
- 데이터값들의 차이가 크지 않음
- class가 불균형하게 불포되어 있음

# Data_processing
## Sparse Dataset
- 날짜 데이터를 연도,달,날짜,시간으로 나눠준후 Column에 추가
- Colunm[1]의 경우 최대 길이가 64라는 것을 확인
- 모든 Colunm[1]의 값들을 64만큼 padding 하여, Column에 추가

## Dense Dataset
- 특별한 전처리를 해주지 않았음

# Model 탐색
***
  주어진 feature로 Class를 분류하는 문제로 판단하여 분류 모델을 적용하였습니다.
***
## Random forest
### DataProcessing 적용 전 결과
![랜덤 포레스트 전처리 전 score](https://user-images.githubusercontent.com/59689327/142750842-b98fc94d-3d96-4a4c-8d08-9498511bc6ed.PNG)
### DataProcessing 적용 후 결과
![랜덤 포레스트 전처리 후 score](https://user-images.githubusercontent.com/59689327/142750843-7d64d706-d116-4c48-bc82-df926a60157a.PNG)
### Feature 중요도
#### 전처리 전
![랜덤 포레스트 전처리전 피처 중요도](https://user-images.githubusercontent.com/59689327/142750846-eba192f9-0798-4761-ab1b-f8cb44b58fce.PNG)
#### 전처리 후
![랜덤 포레스트 전처리 후 피처 중요도](https://user-images.githubusercontent.com/59689327/142750844-26e3f22f-6cbf-4996-84ef-f4c867a27580.PNG)

- Model의 학습이 빠르다는 장점을 이용하여,  전처리 후 와 전처리 전의 성능을 확인 해봤으나 오히려 떨어진 것을 확인했습니다.

- 상관계수가 낮은 Featrue들이 많이 늘어나면서 오히려 성능이 감소된것으로 예상됨

## XGboost

### DataProcessing 적용 전 결과
![xgboost 전처리전 score](https://user-images.githubusercontent.com/59689327/142750841-0c3b5f71-9199-44dd-b9c8-296cd96c17ce.PNG)

### DataProcessing 적용 후 결과
![xgboost 전처리 후 score](https://user-images.githubusercontent.com/59689327/142750838-12fdbdc2-70d1-405a-96e7-9f1e60ef366b.PNG)

### Feature 중요도

#### 전처리 전 

![xgboost 전처리 전 피처중요도](https://user-images.githubusercontent.com/59689327/142750835-9381604b-5097-4dfd-a0e1-6f8b85d44d83.PNG)

#### 전처리 후

![xgboost 전처리 후 피처중요도](https://user-images.githubusercontent.com/59689327/142750839-cadc8208-85f1-40f1-ae1f-f16ed7444c2f.PNG)

- 약한 분류기를 강화하며 앙상블하는 XGboost의 모델의 특성 덕분에 Feature가 늘어났을 때, 성능의 향상을 확인할 수 있었음
- 하지만 학습시간이 너무 오래걸리기 때문에 하이퍼파라미터를 찾는데 너무 긴 시간이 소요되어 최종 Model 선택에서 배제

## lightGBM

### DataProcessing 적용 전 결과
![LGBM 전처리 전 score](https://user-images.githubusercontent.com/59689327/142750829-9199f9a7-1e9f-4185-bec9-20f4781fb04a.PNG)

### DataProcessing 적용 후 결과
![LGBM 전처리후 score](https://user-images.githubusercontent.com/59689327/142750833-b074ca9b-64f6-4664-92a9-ad905cd1e2e2.PNG)

### Feature 중요도
#### 전처리 전
![전처리x_lightgbm feacture 중요도](https://user-images.githubusercontent.com/59689327/142750852-033f7b80-169f-409e-bea6-7cfb9daa9733.PNG)
#### 전처리 후
![전처리o_lightgbm feacuture 중요도](https://user-images.githubusercontent.com/59689327/142750850-dc8fdb5d-c05d-4232-96d9-47032ff7abb1.PNG)

- xgboost에 비해서 엄청나게 학습시간을 단축할 수 있었음
- 전처리 후, 성능의 향상을 확인할 수 있었음
- 하이퍼 파라미터 서치, 상관계수가 낮은 Feature를 제거하는 방식으로 성능을 향상을 시도함

# Model 선택 및 하이퍼 파라미터 서치

***
  위와 같은 시험 결과로 최종적으로 lightgbm model을 선택했습니다.
***
## 하이퍼 파라미터 서치
![lgbm 하이퍼파라미터](https://user-images.githubusercontent.com/59689327/142750834-1aa485ad-c5b8-4b65-b134-f85ba60cf342.PNG)

# 평가 및 분석
- Data의 예측 Calss 불균형이 심했기 때문에, 정확도보다 F1 Score macro가 평가지표로 타당하다고 판단함
- LightGBM Model을 이용해, Tesk1 과 Tesk2의 Class 분류 모델을 만든 결과 F1 Score macro 기준 0.85,0.79의 성능을 나타내는 것을 확인 할 수 있었음


