# Driving Convenience 요구사항 정의서


## 프로젝트 설명
주행 시 운전자 보조 및 편의 기능 개발


## 이해관계자와 중요도 관리

<table>
  <thead>
    <tr style="background-color:#e0e0e0;">
      <th>이해관계자</th>
      <th>목표</th>
      <th>중요도</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>승용차 운전자</td>
      <td>다양한 상황에서 시각적으로 도로 정보를 잘 파악할 수 있어야 함</td>
      <td>1 (제일 높음)</td>
    </tr>
    <tr>
      <td>차량 제조업체</td>
      <td>기능을 모듈화하여 어느 차종에도 쉽게 적용할 수 있어야 함</td>
      <td>2</td>
    </tr>
  </tbody>
</table>


## 새로운 요구사항 토의

1. 밤에 스텔스 차량도 잘 보이도록 했으면 좋겠다.
2. 어두운 정도에 따라서 시야가 더 밝게 확보되었으면 좋겠다.
3. 코너길에서 라이트가 코너도 비춰줬으면 좋겠다.
4. 상향등을 켜서 멀리까지 보고 싶은데 앞 사람에게 피해를 주고 싶진 않다.
5. 시동을 걸 때 라이트가 예쁘게 켜졌으면 좋겠다.
6. 라이트로 앞 사람에게 메세지를 보냈으면 좋겠다.
7. 운전 중에 몸의 자세를 잡아주면 좋겠다.
8. 안개등이 자동으로 켜졌으면 좋겠다.


## Kano 모델 적용
<table>
  <thead>
    <tr style="background-color: #e0e0e0;">
      <th>요구사항</th>
      <th>결과</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><span style="background-color:#e0e0ff;">밤에 스텔스 차량도 잘 보이도록 했으면 좋겠다</span></td>
      <td>P</td>
    </tr>
    <tr>
      <td><span style="background-color: #ffff99;">어두운 정도에 따라서 시야가 더 밝게 확보되었으면 좋겠다</span></td>
      <td>E</td>
    </tr>
    <tr>
      <td><span style="background-color: #e0e0ff;">코너길에서 라이트가 코너도 비춰줬으면 좋겠다</span></td>
      <td>P</td>
    </tr>
    <tr>
      <td>상향등을 켜서 멀리까지 보고 싶은데 앞 사람에게 피해를 주고 싶진 않다</td>
      <td>E</td>
    </tr>
    <tr>
      <td>시동을 걸 때 라이트가 예쁘게 켜졌으면 좋겠다</td>
      <td>I</td>
    </tr>
    <tr>
      <td>라이트로 앞 사람에게 메시지를 보냈으면 좋겠다</td>
      <td>I</td>
    </tr>
    <tr>
      <td><span style="background-color: #ffff99;">운전 중에 몸의 자세를 잡아주면 좋겠다</span></td>
      <td>E</td>
    </tr>
    <tr>
      <td>안개등이 자동으로 켜졌으면 좋겠다</td>
      <td>E</td>
    </tr>
  </tbody>
</table>


## 유스케이스 식별

<table>
  <thead>
    <tr style="background-color:#e0e0e0;">
      <th>기능 범주</th>
      <th>사용자(USER)</th>
      <th>기능 -> <u>구현하는 기능을 말하는 것</u></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>모드 설정 (날씨, 속도)</td>
      <td>운전자</td>
      <td>
        1. 도심모드, 국도모드, 고속도로모드<br>
        2. 비오는 날, 맑은 날
      </td>
    </tr>
    <tr>
      <td>각도 설정 (핸들)</td>
      <td></td>
      <td>직진, 좌회전, 우회전</td>
    </tr>
    <tr>
      <td>auto light</td>
      <td></td>
      <td>
        하향등 킴(밤), 하향등 끔(밝으면)<br>
        상향등 킴(밤인데 어두움), 상향등 끔(밤인데 가로등이 있는 상황)<br>
        코너링시 해당 방향의 코너링 라이트 작동<br>
        안개가 꼈을 때 안개등 작동 등
      </td>
    </tr>
    <tr>
      <td>객체 인식 (자동차)</td>
      <td></td>
      <td>자동차라면 (해당 위치의 라이트를 끔)</td>
    </tr>
    <tr>
      <td>시트 사이드볼스터 조절</td>
      <td></td>
      <td>
        우측 조임(좌회전시) 좌측 조임(우회전시),<br>
        양쪽 조임(고속도로 모드시)
      </td>
    </tr>
  </tbody>
</table>