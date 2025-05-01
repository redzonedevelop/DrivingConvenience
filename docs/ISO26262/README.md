# ISO 26262

소프트웨어 안전 확보 컨셉 

- 예방 ← Misra Rule && Strong Typed Programming Language 사용
- 검출 ← 정적/동적 테스팅  && 코드 리뷰
- 제거 ← 디버깅
- 허용 ← Redundancy Design  && Diversity Design


## Hazardous Event 분석 및 ASIL 등급

> 각 기능에 대해 위험 시나리오, 심각도, 발생 가능성, 제어 가능성에 기반한 ASIL 등급과 예방 방법을 정리하였습니다.

---

### Adaptive Light 모드 설정 기능

- **Hazardous Event**: 하향등이 켜지지 않아 시야 확보가 안 돼서 도심 주행 중 장애물과 충돌
  - **Severity**: S2
  - **Exposure**: E1
  - **Controllability**: C2
  - **ASIL 등급**: QM
  - **예방 방법**: 피드백 회로를 구성해 고장 유무를 판단한다.

- **Hazardous Event**: 하향등이 켜지지 않아 시야 확보가 안 돼서 도심 주행 중 튀어나온 장애물과 충돌
  - **Severity**: S2
  - **Exposure**: E1
  - **Controllability**: C3
  - **ASIL 등급**: QM
  - **예방 방법**: UI를 이용해 수동으로 하향등 작동 후 HW 문제인지 판단하고 HW 문제 시 상향등을 점등

- **Hazardous Event**: 상향등이 켜지지 않아 앞 차량을 뒤늦게 발견하여 충돌
  - **Severity**: S3
  - **Exposure**: E1
  - **Controllability**: C2
  - **ASIL 등급**: QM
  - **예방 방법**: 피드백 회로를 구성해 고장 유무를 판단한다.

- **Hazardous Event**: 상향등이 켜지지 않아 도로로 뛰어든 고라니를 발견하지 못해 충돌
  - **Severity**: S2
  - **Exposure**: E1
  - **Controllability**: C3
  - **ASIL 등급**: QM
  - **예방 방법**: UI를 이용해 수동으로 상향등 작동 후 HW 문제인지 판단하고 HW 문제 시 하향등의 각도 및 밝기를 조정한다.

---

### 주행 모드 설정 기능

- **Hazardous Event**: 의도한 모드로 변경되지 않아 다른 조명 상태가 활성화되어 시야 확보에 실패
  - **Severity**: S3
  - **Exposure**: E1
  - **Controllability**: C2
  - **ASIL 등급**: QM
  - **예방 방법**: 동일한 failure rate를 갖는 MCU에서 동일한 알고리즘으로 모드를 비교하여 오작동 여부를 판단한다.

---

### 코너등 기능

- **Hazardous Event**: 코너등이 켜지지 않아 코너링 시 보이지 않는 각도에 있는 차량을 확인하지 못해 충돌
  - **Severity**: S3
  - **Exposure**: E1
  - **Controllability**: C2
  - **ASIL 등급**: QM
  - **예방 방법**: 피드백 회로를 구성해 고장 유무를 판단한다.

- **Hazardous Event**: 코너링 중 장애물과 충돌
  - **Severity**: S1
  - **Exposure**: E2
  - **Controllability**: C3
  - **ASIL 등급**: QM
  - **예방 방법**: UI를 이용해 수동으로 하향등 작동 후 HW 문제인지 판단하고 HW 문제 시 상향등을 점등

---

### 젖은도로 모드 기능

- **Hazardous Event**: 젖은 길 모드가 변경되지 않아 라인 인식에 불편, 비 오는 날 도심 주행 중 차선을 침범
  - **Severity**: S2
  - **Exposure**: E1
  - **Controllability**: C3
  - **ASIL 등급**: QM
  - **예방 방법**: 동일한 failure rate를 갖는 MCU에서 동일한 알고리즘으로 모드를 비교하여 오작동 여부를 판단한다.
