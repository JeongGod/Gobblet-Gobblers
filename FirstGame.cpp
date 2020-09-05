#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Board{
    string name;
    int s_horse;
    int x,y;
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
        if(comp[x][y].name.compare(p) == 0) { 
            // 내 말인지 확인부터
            if(comp[move_x][move_y].name.compare(p) == 0 || 
               comp[move_x][move_y].s_horse >= comp[x][y].s_horse) { 
                // 내 말쪽으로 옮기려해
                // 옮기려는 곳이 내 말보다 크다면
                return false;
            }
            // 일단 말을 옮긴다.
            if(comp[move_x][move_y].s_horse != 0) {
                // 비어있는 공간이 아니라면
                store.push_back(comp[move_x][move_y]);
                comp[move_x][move_y] = comp[x][y];
            } else {
                // 비어있는 공간이라면
                comp[move_x][move_y] = comp[x][y];
            }
            // 옮기고나서, 덮여씌여졌던 말을 보여준다.
            vector<Board>::reverse_iterator rIter;
            for(rIter = store.rbegin(); rIter != store.rend(); rIter++) {
                if(rIter->x == x && rIter->y == y) {
                    comp[x][y].name = rIter->name;
                    comp[x][y].s_horse = rIter->s_horse;
                    store.erase((rIter+1).base());
                    return true;
                }
            }
            // 만약 덮여씌여져있던 말이 없다면
            comp[x][y].name = " ";
            comp[x][y].s_horse = 0;
            return true;
        } else {
            // 내 말이 아닌 곳이라면
            return false;
        }
    }
};

int check() {
    for(int i=1; i<=3; i++) {
        // 가로부분 3개 일치하는지
        if(comp[i][1].name.compare("A") == 0 && comp[i][2].name.compare("A") == 0 && comp[i][3].name.compare("A") == 0) {
            return 1;
        } else if (comp[i][1].name.compare("B") == 0 && comp[i][2].name.compare("B") == 0 && comp[i][3].name.compare("B") == 0) {
            return 2;
        }
    }
    for(int i=1; i<=3; i++) {
        // 세로부분 3개 일치하는지
        if(comp[1][i].name.compare("A") == 0 && comp[2][i].name.compare("A") == 0 && comp[3][i].name.compare("A") == 0) {
            return 1;
        } else if (comp[1][i].name.compare("B") == 0 && comp[2][i].name.compare("B") == 0 && comp[3][i].name.compare("B") == 0) {
            return 2;
        }
    }
    // 대각선 부분 3개 일치하는지
    if((comp[1][1].name.compare("A") == 0 && comp[2][2].name.compare("A") == 0 && comp[3][3].name.compare("A") == 0) ||
       (comp[1][3].name.compare("A") == 0 && comp[2][2].name.compare("A") == 0 && comp[3][1].name.compare("A") == 0)) {
            return 1;
    } else if((comp[1][1].name.compare("B") == 0 && comp[2][2].name.compare("B") == 0 && comp[3][3].name.compare("B") == 0) ||
              (comp[1][3].name.compare("B") == 0 && comp[2][2].name.compare("B") == 0 && comp[3][1].name.compare("B") == 0)) {
                return 2;
    }
    return 0;
}

void pan() {
    for(int i=1; i<=4; i++) {
        if(i==4) {
            printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
            return;
        }
        printf("ㅡㅡ %d ㅡㅡㅡ %d ㅡㅡㅡ %d ㅡㅡㅡ\n", 3*i-2, 3*i-1, 3*i);
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
            printf("남은 말 : [");
            for(int i=1; i<=3; i++) {
                for(int j=0; j<user1.getHorse(i); j++) {
                    printf("%d", i);
                }
            }
            printf("]\n");
            printf("1. 놓기, 2. 옮기기\n");
            scanf("%d", &way);
            if(way==1){ // 놓는 방법
                printf("좌표를 입력해주세요.\n");
                printf("x : ");
                scanf("%d", &x);
                printf("y : ");
                scanf("%d", &y);
                printf("놓을 말을 선택해주세요.\n");
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
            printf("남은 말 : [");
            for(int i=1; i<=3; i++) {
                for(int j=0; j<user2.getHorse(i); j++) {
                    printf("%d", i);
                }
            }
            printf("]\n");
            printf("1. 놓기, 2. 옮기기\n");
            scanf("%d", &way);
            if(way==1) {
                printf("좌표를 입력해주세요.\n");
                printf("x : ");
                scanf("%d", &x);
                printf("y : ");
                scanf("%d", &y);
                printf("놓을 말을 선택해주세요.\n");
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
            printf("덮여져 있는 말들\n");
            cout << it->name << '\n';
            printf("[%d][%d] ", it->x, it->y);
            printf("size = %d\n", it->s_horse);
        }
        if(check() == 1) {
            printf("Player1(A) 승리!\n");
            pan();
            break;
        } else if(check() == 2) {
            printf("Player2(B) 승리!\n");
            pan();
            break;
        }
        pan();
    }
}

int main() {
    for(int i=1; i<=3; i++) {
        for(int j=1; j<=3; j++) {
            comp[i][j].x = i;
            comp[i][j].y = j;
            comp[i][j].name = " ";
        }
    }
    start();
    return 0;
}