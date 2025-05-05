# DrivingConvenience

# MX Cube 설정 가이드 (100kbps CAN 통신 설정)

## 1. Connectivity 설정
- `Connectivity` → `CAN` 클릭
- `Activated` 항목 체크박스 클릭

## 2. Parameter Settings
- **Time Quanta in Bit Segment 1**: `16 times` 로 설정
- **Time Quanta in Bit Segment 2**: `5 times` 로 설정

✅ **100kbps CAN 통신 시작 준비 완료!**

## 3. NVIC Settings
- `USB high priority or CAN RX0 interrupts` 항목의 `Enabled` 체크박스 클릭

✅ **CAN 메시지 수신 인터럽트 설정 완료!**

---

# 코드 이해를 위한 기초 지식

## CAN 필터 동작 원리

CAN 필터는 **마스크(mask)**와 **필터 ID**를 사용하여 수신할 메시지를 선별합니다.

- 마스크의 각 비트가 `1`이면 해당 비트는 필터 ID와 **정확히 일치**해야 수신됩니다.
- 마스크의 각 비트가 `0`이면 해당 비트는 **무시**되며 어떤 값이 와도 수신합니다.

### 예시
해당 마스크/ID 조합에서 수신 가능한 CAN ID들은 다음과 같습니다:

- `0x102`
- `0x106`
- `0x10A`
- `0x10E`
- `0x10E`

➡ 이는 **001 0000 xx10** 형태의 ID가 수신된다는 뜻입니다.

---

✅ 이 문서는 STM32CubeMX 설정과 CAN 필터 동작 원리에 대한 빠른 이해를 돕기 위한 참고 자료입니다.
