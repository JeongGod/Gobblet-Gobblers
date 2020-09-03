Gobblet-Gobblers
=================
(러시아 장기)
---------

* Language : C++

* ### 러시아 장기
    * 1:1 매치로 진행한다.
    * 나, 상대방은 각각 1,2,3의 크기를 가진 말이 2개씩 존재한다.
    ```
    ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ
    |       |       |       |
    |       |       |       |
    ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ
    |       |       |       |
    |       |       |       |
    ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ
    |       |       |       |
    |       |       |       |
    ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ ㅡ
    ```
    판은 이런 식으로 되어있다.

* ### 규칙
    1. 빈 칸에는 어떤 말이든 놓을 수 있다.
    2. 만약 놓으려는 칸에 상대 말이 있다면 놓을 수 없다.
       하지만, 상대 말보다 숫자가 크다면 그 말을 덮어 씌울 수 있다.
    3. 한 턴에는 자신이 가지고 있는 말이나, 판에 놓여져 있는 말을 옮기면서 턴을 소모한다.
       만약, 자신의 말이 상대의 말로 덮어져있는 상태면 옮길 수 없다.
    4. 같은 크기의 말은 같은 곳에 놓을 수 없다.
    
* ### 승리조건
    - 자신의 말로 한 줄의 빙고를 만든다면 승리다.
* ### 패배조건
    - 상대의 말이 한 줄의 빙고를 만든다면 패배다.
