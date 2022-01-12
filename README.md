# 제출 파일
```
├── 카카오뱅크.ipynb                                                                                        
├── result.csv                     
└── README.md                  
    
```

# 실행 방법
  * 쥬피터 노트북을 사용했기 때문에 처음부터 처음 쉘부터 실행하면 됩니다.
 
# 데이터 탐색

## train.csv , validatio.csv
- lable 0 이 label 1보다 약 3배 많음
- 결측치가 많음
- categorical_feature_9,6 integer_feature 4,1 은 약 80% 이상이 결측치
- categorical_feature 4, interger_feature 8,7,6,2 결측치 대체가 필요

![train 결측치](https://user-images.githubusercontent.com/59689327/149055518-81f3082a-097d-48aa-bb5e-c18c3108c8c5.PNG)

## test.csv
- 결측치가 많음
- categorical_feature_9,6 integer_feature 4,1 은 약 80% 이상이 결측치
- categorical_feature 4, interger_feature 8,7,6,2 결측치 대체가 필요
- categorical_feautre에 str 형태가 아닌 int 형태의 큰 수가 들어 있음

![train_label 불균형](https://user-images.githubusercontent.com/59689327/149055522-e153aca6-17e3-422e-952d-5145b0939b47.PNG)


# data_processing
## frist_data_processing
- 분류 model을 찾기 위해, 결측치를 row 단위로 전부 제거하여 약 8000개의 dataset을 얻음

## second_data_processing
- categorical_feature_9,6 integer_feature 4,1 를 제거함
- 나머지 column들의 결측치에 대해 row 단위로 전부 제거하여 약 5.9만개의 dataset을 얻음

## third_data_processing
- categorical_feature_9,6 integer_feature 4,1 를 제거함
- categorical_feature 4, interger_feature 8,7,6,2 결측치를 대체 하기 위해 선형 회귀 모델을 만들어 대체 함
- test.csv의 int 형태의 큰 수를 float 형태로 변환하여 사용함.


# 평가 지표
- label 불균형이 심했고, 물건을 구입하는 고객의 분류하는 task 였기 때문에, 정확도보다 F1 Score 혹은 Recall 이 조금 더
적합한 평가지표라고 생각함. 
- 하지만 시험에 통과하기 위해, 보다 많은 label을 맞출 필요가 있었기에 정확도를 기준으로 모델을 선정하기로 함.

# Model 탐색
***
  주어진 feature로 Class를 분류하는 문제로 판단하여 분류 모델을 적용하였습니다.
***
- 첫 번째, 전처리로 얻은 약 8천개의 데이터를 사용하여, Model을 탐색함

## Random forest

### Random forest 결과
![랜덤포레스트 결과](https://user-images.githubusercontent.com/59689327/149052683-87dfbe9a-f8f5-4dbc-b4fa-6749db7673b1.PNG)
### Feature 중요도
![랜덤포레스트 피처중요도](https://user-images.githubusercontent.com/59689327/149052685-133d26f7-0345-43d2-b951-8110756f1d9c.PNG)

## catboost

### catboost 결과
![catboost 결과](https://user-images.githubusercontent.com/59689327/149052669-74ac5f34-cfbd-4cc5-9b07-9d50c4b99842.PNG)

## costom_neural_network
### 결과
![신경망 결과](https://user-images.githubusercontent.com/59689327/149052665-250c08e0-8b11-4396-91dd-a09601aa6ee9.PNG)

## light GBM
### ligth GBM 결과
![lgbm 결과](https://user-images.githubusercontent.com/59689327/149052673-d8457619-5d5d-46e9-88ca-4d867d7e51ca.PNG)
### ligth GBM 피처 중요도


- 정확도를 기준으로 light GBM이 가장 높았기 때문에, light GBM을 최종 Model로 선정
- 하이퍼파라미터 서치를 진행하여,하이퍼파미터를 확정함.

# second_data_processing 후 LGBM 적용
- categorical_feature_9,6 integer_feature 4,1 를 제거함
- 나머지 column들의 결측치에 대해 row 단위로 전부 제거하여 약 5.9만개의 dataset을 얻음

## 결과
![두번째 전처리후 lgbm 결과](https://user-images.githubusercontent.com/59689327/149052679-9c7ec420-893d-4070-9562-135414088102.PNG)
## 피처중요도
![두번째 전처리후 lgbm 피처중요도 결과](https://user-images.githubusercontent.com/59689327/149052681-119fed55-e550-41da-b04c-2c5ed1e4aa34.PNG)

# third_data_processing 후 LGBM 적용

## 결과
![세번째 전처리후 lgbm 결과](https://user-images.githubusercontent.com/59689327/149052689-da99f849-c07e-4dc4-bceb-499c3ebe2158.PNG)
## 피처중요도
![세번째 전처리후 lgbm 피처중요도 결과](https://user-images.githubusercontent.com/59689327/149052691-6febe3a3-dd58-4869-8ce7-fe6622666a26.PNG)

# 최종 평가
- 결측치를 모두 제거하여 약 8000개의 데이터 셋을 사용했을 때보다 선형회귀 모델로 결측치를 예측하여 대체 했을 때,
***정확도 기준 약 20점의 향상을 얻을 수 있었음***
- 결측치를 모두 제거하여 약 8000개의 데이터 셋을 사용했을 때보다 선형회귀 모델로 결측치를 예측하여 대체 했을 때,
재현율이나 F1 score가 떨어진 것을 볼 수 있는데 이것은 데이터 셋이 크기가 8천개에서 6만개로 증가하여 발생한 현상이라고 예측됨

# 해볼만한 시도
- 결측치가 80% 이상이 넘는 feature들을 제거하여 사용했지만, 이 결측치를 정확히 예측할 수 있는 모델을 설계하여
결측치를 대체한다면 더욱 성능향상을 얻을 수 있을 것이라고 기대됨.
- 신경망 모델에 conv layer를 쌓아서 feature간의 관계를 반영하는 model을 시도
- 위에서 만든 여러가지 모델을 voting 하여 최종적인 test.csv를 생성 했다면 더 좋은 결과를 얻을 수 있을것이라고 생각됨.
