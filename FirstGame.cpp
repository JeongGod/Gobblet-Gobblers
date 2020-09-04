#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Board{
    string name = "X";
    int s_horse;
};
Board comp[5][5];
vector <Board> store;
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

    bool putHorse(int x, int y, int horse, string p) {
        if(u_horse[horse] <= 0) {
            printf("말이 부족합니다.\n");
            return false;
        }
        if(comp[x][y].s_horse != 0) { // 비어있지 않다면 확인
            if(comp[x][y].name.compare(p) == 0) return false; // 내가 놓으려는 곳에 또 놓았던 곳에 놓을라고 해
            if(comp[x][y].s_horse < horse) { // 내 말이 크다면 놓을 수 있어.
                // 덮어씌웠으니, 그 전에 있던 값들을 저장해놓아야 한다.
                // vector로 사용하자.
                store.push_back(comp[x][y]);
                comp[x][y].name = p;
                comp[x][y].s_horse = horse;
                u_horse[horse]--;
            } else { // 놓을 수 없어.
                return false;
            }
        } else { // 비어있는 경우
            comp[x][y].name = p;
            comp[x][y].s_horse = horse;
            u_horse[horse]--;
        }
        return true;
    }
    bool moveHorse(int x, int y, int move_x, int move_y, string p) {
        if(comp[x][y].name.compare(p) == 0) { // 내 말인지 확인부터
            if(comp[move_x][move_y].name.compare(p) == 0) { // 내 말쪽으로 옮기려해
                printf("실화입니까? 안됩니다.\n");
                return false;
            }
            if(comp[move_x][move_y].s_horse >= comp[x][y].s_horse) { // 옮기려는 곳이 내 말보다 크다면
                return false;
            }
            comp[move_x][move_y] = comp[x][y];
            comp[x][y].name = "X";
            comp[x][y].s_horse = 0;
            return true;
        } else {
            return false;
        }
    }
};


void pan() {
    for(int i=1; i<=4; i++) {
        printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
        if(i==4) return;
        for(int j=1; j<4; j++) {
            cout << "|    " << comp[i][j].name << "   ";
        }
        printf("|\n");
        for(int j=1; j<4; j++) {
            printf("|    %d   ", comp[i][j].s_horse);
        }
        printf("|\n");
        for(int j=1; j<4; j++) {
            printf("|        ");
        }
        printf("|\n");
    }
}

void start() {
    User user1 = User(1); // 첫번째 플레이어
    User user2 = User(2); // 두번째 플레이어
    int m_x,m_y,x,y,horse;
    int way;
    int p=1;
    system("clear");
    pan();
    while(true) {
        if(p==1){
            printf("\"Player1\"의 차례입니다.\n");
            printf("1. 놓기, 2. 옮기기\n");
            scanf("%d", &way);
            if(way==1){ // 놓는 방법
                printf("좌표를 입력해주세요.\n");
                printf("x : ");
                scanf("%d", &x);
                printf("y : ");
                scanf("%d", &y);
                printf("놓을 말을 선택해주세요.\n");
                printf("1 : %d, 2 : %d, 3 : %d\n", user1.getHorse(1), user1.getHorse(2), user1.getHorse(3));
                scanf("%d", &horse);
                system("clear");
                if(user1.putHorse(x,y,horse,"A")) {
                    p++;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            } else { // 옮기는 방법
                printf("옮길 말의 좌표를 선택해주세요.\n");
                printf("x : ");
                scanf("%d", &x);
                printf("y : ");
                scanf("%d", &y);
                printf("옮길 좌표를 입력해주세요.\n");
                printf("x : ");
                scanf("%d", &m_x);
                printf("y : ");
                scanf("%d", &m_y);
                system("clear");
                if(user1.moveHorse(x,y, m_x, m_y, "A")) {
                    p++;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            }
        } else {
            printf("\"Player2\"의 차례입니다.\n");
            printf("1. 놓기, 2. 옮기기\n");
            scanf("%d", &way);
            if(way==1) {
                printf("좌표를 입력해주세요.\n");
                printf("x : ");
                scanf("%d", &x);
                printf("y : ");
                scanf("%d", &y);
                printf("놓을 말을 선택해주세요.\n");
                printf("1 : %d, 2 : %d, 3 : %d\n", user2.getHorse(1), user2.getHorse(2), user2.getHorse(3));
                scanf("%d", &horse);
                system("clear");
                if(user2.putHorse(x,y,horse,"B")) {
                    p--;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            } else { // 옮기는 방법
                printf("옮길 말의 좌표를 선택해주세요.\n");
                printf("x : ");
                scanf("%d", &x);
                printf("y : ");
                scanf("%d", &y);
                printf("옮길 좌표를 입력해주세요.\n");
                printf("x : ");
                scanf("%d", &m_x);
                printf("y : ");
                scanf("%d", &m_y);
                system("clear");
                if(user2.moveHorse(x,y, m_x, m_y, "B")) {
                    p--;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            }
        }
        vector<Board>::iterator it;
        for(it = store.begin(); it != store.end(); it++) {
            cout << it->name << '\n';
            printf("%d\n", it->s_horse);
        }
        pan();
    }
}

int main() {
    start();
    return 0;
}