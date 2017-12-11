# Arduino-Videochanger
Using TCS3200 Color sensor and Ultrasonic distance sonsor, change video by interaction.

0. 개요
 - 아두이노 컬러센서와 거리센서 그리고 프로세싱 프로그램을 사용하여 인터렉션에 따라 영상이 바뀌는 것을 구현하였다.

1. 작동순서
 - Red color 인식
 - Green color 인식
 - Blue color 인식
 - 거리센서 거리값 증가
 - 거리센서 거리값 감소
 
2. 사용방법
 - 주석으로 표기된 값들을 전부 수정해 주어야한다.
 - Arduino -> RGB값 범위, Distance 범위
 - Processing ->Serial Port
 - 아두이노를 실행시킨다
 - 아두이노 시리얼 모니터를 반드시 종료시킨다.
 - 프로세싱에서 영상을 실행한다.
 - R->G->B-> Far distance -> Near Distance 순으로 인터랙션 진행
 - 영상이 바뀌는 것을 확인한다.
