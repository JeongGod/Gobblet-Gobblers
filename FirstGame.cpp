#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

struct Board{
    string name;
    int s_horse;
};
Board comp[4][4];

class User {
private:
    int u_turn;
    int u_horse[4];
public:
    User(int turn) {
        u_turn = turn;
        for(int i=1; i<=3; i++) {
            u_horse[i] = 2;
        }
    }

    int getTurn() {return u_turn;} // turn (Name대체)
    int getHorse() { // 전체 말 개수
        int total=0;
        for(int i=1; i<=3; i++) total += u_horse[i];
        return total;
    }
    int getHorse(int i) {return u_horse[i];} // i사이즈의 말 개수

    void putHorse(int x, int y, int horse, string p) {
        comp[x][y].name = p;
        comp[x][y].s_horse = horse;
        if(u_horse[horse] <= 0) {
            printf("말이 부족합니다.\n");
            return;
        }
        u_horse[horse]--;
    }
};


void pan() {
    for(int i=0; i<4; i++) {
        printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
        if(i==3) return;
        for(int j=0; j<4; j++) {
            printf("|        ");
        }
        printf("\n");
        for(int j=0; j<4; j++) {
            printf("|        ");
        }
        printf("\n");
        for(int j=0; j<4; j++) {
            printf("|        ");
        }
        printf("\n");
    }
}

void start() {
    User user1 = User(1); // 첫번째 플레이어
    User user2 = User(2); // 두번째 플레이어
    int x,y,horse;
    int p=1;
    // while(true) {
        system("clear");
        pan();
        if(p==1){
            printf("Player1의 차례입니다.\n");
            printf("좌표를 입력해주세요.\n");
            printf("x : ");
            scanf("%d", &x);
            printf("y : ");
            scanf("%d", &y);
            printf("놓을 말을 선택해주세요.\n");
            printf("1 : %d, 2 : %d, 3 : %d\n", user1.getHorse(1), user1.getHorse(2), user1.getHorse(3));
            scanf("%d", &horse);
            user1.putHorse(x,y,horse,"a");
            printf("1 : %d, 2 : %d, 3 : %d\n", user1.getHorse(1), user1.getHorse(2), user1.getHorse(3));
            p++;
        } else {
            printf("Player2의 차례입니다.\n");
            printf("좌표를 입력해주세요.\n");
            printf("x : ");
            scanf("%d", &x);
            printf("y : ");
            scanf("%d", &y);
            printf("놓을 말을 선택해주세요.\n");
            printf("1 : %d, 2 : %d, 3 : %d\n", user1.getHorse(1), user1.getHorse(2), user1.getHorse(3));
            scanf("%d", &horse);
            user1.putHorse(x,y,horse,"a");
            printf("1 : %d, 2 : %d, 3 : %d\n", user1.getHorse(1), user1.getHorse(2), user1.getHorse(3));
            p++;
        }
    // }
}

int main() {
    
    
    start();
    return 0;
}

/*
러시안 장기의 룰
    1:1 매치로 진행한다.
    나, 상대방은 각각 1,2,3의 크기를 가진 말이 2개씩 존재한다.
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
    판은 이런 식으로 되어있다.

    ----------------규칙----------------
    1. 빈 칸에는 어떤 말이든 놓을 수 있다.
    2. 만약 놓으려는 칸에 상대 말이 있다면 놓을 수 없다.
       하지만, 상대 말보다 숫자가 크다면 그 말을 덮어 씌울 수 있다.
    3. 한 턴에는 자신이 가지고 있는 말이나, 판에 놓여져 있는 말을 옮기면서 턴을 소모한다.
       만약, 자신의 말이 상대의 말로 덮어져있는 상태면 옮길 수 없다.
    4. 같은 크기의 말은 같은 곳에 놓을 수 없다.
    
    ----------------승리조건--------------
    자신의 말로 한 줄의 빙고를 만든다면 승리다.

    ----------------패배조건--------------
    상대의 말이 한 줄의 빙고를 만든다면 패배다.
*/