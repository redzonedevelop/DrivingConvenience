# 요구사항 분석

## 도출
- 브레인 스토밍
- 유스 케이스

## 분석 

- 구조적 분석 <- data flow diagram
- 운용 관점 분석 <- state machine diagram


## 기능 요구사항 

Informal Notation <- EARS 

### REQ-1
- WHEN 시간 IS 낮, THEN 시스템은 헤드 라이트를를 켜지 않아야 한다.

### REQ-2
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 도심 AND 날씨 IS 비가 안 오는 날 AND 핸들 IS 직진, THEN 시스템은 하향등을 밝기 70%, 각도 -5도로 켜야 한다.

### REQ-3
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 도심 AND 날씨 IS 비가 안 오는 날 AND 핸들 IS 좌회전, THEN 시스템은 하향등을 밝기 70%, 각도 -5도로 켜고, left 코너등을 켜야 한다.

### REQ-4
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 도심 AND 날씨 IS 비가 안 오는 날 AND 핸들 IS 우회전, THEN 시스템은 하향등을 밝기 70%, 각도 -5도로 켜고, right 코너등을 켜야 한다.

### REQ-5
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 도심 AND 날씨 IS 비오는날 AND 핸들 IS 직진, THEN 시스템은 하향등을 밝기 100%, 각도 -5도로 켜야 한다.

### REQ-6
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 도심 AND 날씨 IS 비오는날 AND 핸들 IS 좌회전, THEN 시스템은 하향등을 밝기 100%, 각도 -5도로 켜고, left 코너등을 켜야 한다.

### REQ-7
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 도심 AND 날씨 IS 비오는날 AND 핸들 IS 우회전, THEN 시스템은 하향등을 밝기 100%, 각도 -5도로 켜고, right 코너등을 켜야 한다.

### REQ-8
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 국도 AND 날씨 IS 안오는날 AND 핸들 IS 직진, THEN 시스템은 하향등을 켜짐 (밝기 70%, 각도 -5도)로 켜야 한다.

### REQ-9
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 국도 AND 날씨 IS 안오는날 AND 핸들 IS 좌회전, THEN 시스템은 하향등을 켜짐 (밝기 70%, 각도 -5도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-10
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 국도 AND 날씨 IS 안오는날 AND 핸들 IS 우회전, THEN 시스템은 하향등을 켜짐 (밝기 70%, 각도 -5도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-11
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 국도 AND 날씨 IS 비오는날 AND 핸들 IS 직진, THEN 시스템은 하향등을 켜짐 (밝기 100%, 각도 -5도)로 켜야 한다.

### REQ-12
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 국도 AND 날씨 IS 비오는날 AND 핸들 IS 좌회전, THEN 시스템은 하향등을 켜짐 (밝기 100%, 각도 -5도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-13
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 국도 AND 날씨 IS 비오는날 AND 핸들 IS 우회전, THEN 시스템은 하향등을 켜짐 (밝기 100%, 각도 -5도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-14
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 안오는날 AND 핸들 IS 직진, THEN 시스템은 하향등을 켜짐 (밝기 70%, 각도 -2도)로 켜야 한다.

### REQ-15
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 안오는날 AND 핸들 IS 좌회전, THEN 시스템은 하향등을 켜짐 (밝기 70%, 각도 -2도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-16
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 안오는날 AND 핸들 IS 우회전, THEN 시스템은 하향등을 켜짐 (밝기 70%, 각도 -2도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-17
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 비오는날 AND 핸들 IS 직진, THEN 시스템은 하향등을 켜짐 (밝기 100%, 각도 -2도)로 켜야 한다.

### REQ-18
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 비오는날 AND 핸들 IS 좌회전, THEN 시스템은 하향등을 켜짐 (밝기 100%, 각도 -2도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-19
- WHEN 시간 IS 밤(밝은 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 비오는날 AND 핸들 IS 우회전, THEN 시스템은 하향등을 켜짐 (밝기 100%, 각도 -2도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-20
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 국도 AND 날씨 IS 안오는날 AND 핸들 IS 직진, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 70%, 각도 -5도)로 켜야 한다.

### REQ-21
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 국도 AND 날씨 IS 안오는날 AND 핸들 IS 좌회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 70%, 각도 -5도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-22
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 국도 AND 날씨 IS 안오는날 AND 핸들 IS 우회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 70%, 각도 -5도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-23
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 국도 AND 날씨 IS 비오는날 AND 핸들 IS 직진, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 100%, 각도 -5도)로 켜야 한다.

### REQ-24
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 국도 AND 날씨 IS 비오는날 AND 핸들 IS 좌회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 100%, 각도 -5도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-25
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 국도 AND 날씨 IS 비오는날 AND 핸들 IS 우회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 100%, 각도 -5도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-26
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 안오는날 AND 핸들 IS 직진, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 70%, 각도 -2도)로 켜야 한다.

### REQ-27
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 안오는날 AND 핸들 IS 좌회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 70%, 각도 -2도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-28
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 안오는날 AND 핸들 IS 우회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 70%, 각도 -2도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-29
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 비오는날 AND 핸들 IS 직진, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 100%, 각도 -2도)로 켜야 한다.

### REQ-30
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 비오는날 AND 핸들 IS 좌회전, THEN 시스템은 상향등을 켜짐 하향등을 (밝기 100%, 각도 -2도)로 켜야 한다 그리고 left 코너등을 켜야 한다.

### REQ-31
- WHEN 시간 IS 밤 (어두운 도로) AND 운전 모드 IS 고속도로 AND 날씨 IS 비오는날 AND 핸들 IS 우회전, THEN 시스템은 상향등을 키고 하향등을을 (밝기 100%, 각도 -2도)로 켜야 한다 그리고 right 코너등을 켜야 한다.

### REQ-32
- WHEN 날씨 IS 안개낀날, THEN 시스템은 안개등을 켜야 한다.

### REQ-33
- WHEN 차량 속력 IS 100km미만 AND 핸들 IS 기본, THEN 시스템은 좌석의 왼쪽 모터를 각도 0도로, 오른쪽 모터를 각도 0도로 설정해야 한다.

### REQ-34
- WHEN 차량 속력 IS 100km미만 AND 핸들 IS 오른쪽, THEN 시스템은 좌석의 왼쪽 모터를 각도 0도로, 오른쪽 모터를 각도 -30도로 설정해야 한다.

### REQ-35
- WHEN 차량 속력 IS 100km미만 AND 핸들 IS 왼쪽, THEN 시스템은 좌석의 왼쪽 모터를 각도 30도로, 오른쪽 모터를 각도 0도로 설정해야 한다.

### REQ-36
- WHEN 차량 속력 IS 100km이상, THEN 시스템은 좌석의 왼쪽 모터를 각도 30도로, 오른쪽 모터를 각도 -30도로 설정해야 한다.


## 비기능 요구사항

- **프로그래밍 언어**
  - C 언어 사용

- **주석**
  - 모든 함수의 시작 부분에 기능 설명 주석 작성
  - 복잡한 비트 조작이나 레지스터 설정 시 반드시 설명 주석 추가

- **Branch Convention**
  - 영어는 소문자를 사용하고 단어는 언더스코어(_)로 구분
  - 계층 구조는 슬래시(/)로 연결  
    예시: `ADAP-{issue number}-{issue category}/{issue name}/{담당자}`

- **Commit Convention**
  - 형식: `ADAP-{issue number}-{issue category}/{source depth1}/{source depth2}/.../{담당자}: 제목`
  - 커밋 메시지에는 간략히 어떤 기능을 개발/수정했는지 설명

- **개발 방법론**
  - V-Model 기반 개발 방식 적용
  - ISO 26262를 통해 체계적인 테스트 및 결함 예방, 조기 발견 가능

- **버전 관리**
  - 기능이 수정될 때마다 버전 숫자 증가  
    예시: `ver1` → `ver2`

- **Code Convention**
  - `barr c` 스타일 가이드 준수

- **Issue Category**
  - 각 패널의 **상위 계층**만 사용하고, 하위 계층은 상위에 귀속됨

  - **Feat: 새로운 기능 추가**
    - `Design`: CSS 등 사용자 UI 디자인 변경

  - **Fix: 버그 수정**
    - `!BREAKING CHANGE`: 커다란 API 변경의 경우
    - `!HOTFIX`: 급하게 치명적인 버그를 고쳐야 하는 경우

  - **Docs: 문서 업로드 및 수정**

  - **Refactor: 코드 리팩토링**
    - `Style`: 코드 formatting, 세미콜론 누락 등 코드 자체 변경이 없는 경우
    - `Comment`: 필요한 주석 추가 및 변경
    - `Rename`: 파일/폴더 이름 수정 또는 이동
    - `Remove`: 파일 삭제 작업만 수행한 경우

  - **Test: 테스트 코드 또는 리팩토링된 테스트 코드 추가**

  - **Chore: 패키지 매니저 수정, 기타 설정 파일 수정 (예: .gitignore)`




## 검증 기준

요구사항은 다음의 기준에 따라 검증되어야 합니다:

- **Correct (정확성)**  
  - 상위의 요구사항이 명확하게 작성되어 있는가?

- **Elementary (단일성)**  
  - 하나의 요구사항이 하나의 개체로 간결하고 명료하게 기술되었는가?

- **Unambiguous (명확성)**  
  - 작성한 요구사항이 단일한 의미로만 해석될 수 있는가?

- **Feasible (실현 가능성)**  
  - 기술적으로 구현 가능한가?

- **Traceable (추적 가능성)**  
  - GitHub 및 Jira를 활용하여 요구사항과 코드가 연결되고, 네이밍 규칙이 적용되어 있는가?

- **Modifiable (수정 가능성)**  
  - 요구사항을 일관성 있게 변경할 수 있는가?  
    *(EARS 형식을 적용하여 가독성과 수정 용이성을 확보함)*
