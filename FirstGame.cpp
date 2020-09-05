#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Board{
    string name;
    int s_horse;
    int num;
};
Board comp[10];
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

    bool putHorse(int num, int horse, string p) {
        if(u_horse[horse] <= 0) {
            printf("말이 부족합니다.\n");
            return false;
        }
        if(comp[num].s_horse != 0) { // 비어있지 않다면 확인
            if(comp[num].name.compare(p) == 0) return false; // 내가 놓으려는 곳에 또 놓았던 곳에 놓을라고 해
            if(comp[num].s_horse < horse) { // 내 말이 크다면 놓을 수 있어.
                // 덮어씌웠으니, 그 전에 있던 값들을 저장해놓아야 한다.
                store.push_back(comp[num]);
                comp[num].name = p;
                comp[num].s_horse = horse;
                u_horse[horse]--;
            } else { // 놓을 수 없어.
                return false;
            }
        } else { // 비어있는 경우
            comp[num].name = p;
            comp[num].s_horse = horse;
            u_horse[horse]--;
        }
        return true;
    }
    bool moveHorse(int num, int move_num, string p) {
        if(comp[num].name.compare(p) == 0) { 
            // 내 말인지 확인부터
            if(comp[move_num].name.compare(p) == 0 || 
               comp[move_num].s_horse >= comp[num].s_horse) { 
                // 내 말쪽으로 옮기려해
                // 옮기려는 곳이 내 말보다 크다면
                return false;
            }
            // 일단 말을 옮긴다.
            if(comp[move_num].s_horse != 0) {
                // 비어있는 공간이 아니라면
                store.push_back(comp[move_num]);
                comp[move_num] = comp[num];
            } else {
                // 비어있는 공간이라면
                comp[move_num] = comp[num];
            }
            // 옮기고나서, 덮여씌여졌던 말을 보여준다.
            vector<Board>::reverse_iterator rIter;
            for(rIter = store.rbegin(); rIter != store.rend(); rIter++) {
                if(rIter->num == num) {
                    comp[num].name = rIter->name;
                    comp[num].s_horse = rIter->s_horse;
                    store.erase((rIter+1).base());
                    return true;
                }
            }
            // 만약 덮여씌여져있던 말이 없다면
            comp[num].name = " ";
            comp[num].s_horse = 0;
            return true;
        } else {
            // 내 말이 아닌 곳이라면
            return false;
        }
    }
};

int check() {
    for(int i=1; i<=7; i+=3) {
        // 가로부분 3개 일치하는지
        if(comp[i].name.compare("A") == 0 && comp[i+1].name.compare("A") == 0 && comp[i+2].name.compare("A") == 0) {
            return 1;
        } else if (comp[i].name.compare("B") == 0 && comp[i+1].name.compare("B") == 0 && comp[i+2].name.compare("B") == 0) {
            return 2;
        }
    }
    for(int i=1; i<=3; i++) {
        // 세로부분 3개 일치하는지
        if(comp[i].name.compare("A") == 0 && comp[i+3].name.compare("A") == 0 && comp[i+6].name.compare("A") == 0) {
            return 1;
        } else if (comp[i].name.compare("B") == 0 && comp[i+3].name.compare("B") == 0 && comp[i+6].name.compare("B") == 0) {
            return 2;
        }
    }
    // 대각선 부분 3개 일치하는지
    if((comp[1].name.compare("A") == 0 && comp[5].name.compare("A") == 0 && comp[9].name.compare("A") == 0) ||
       (comp[3].name.compare("A") == 0 && comp[5].name.compare("A") == 0 && comp[7].name.compare("A") == 0)) {
            return 1;
    } else if((comp[1].name.compare("B") == 0 && comp[5].name.compare("B") == 0 && comp[9].name.compare("B") == 0) ||
              (comp[3].name.compare("B") == 0 && comp[5].name.compare("B") == 0 && comp[7].name.compare("B") == 0)) {
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
        for(int j=2; j>=0; j--) {
            cout << "|    " << comp[3*i-j].name << "   ";
        }
        printf("|\n");
        for(int j=2; j>=0; j--) {
            printf("|    %d   ", comp[3*i-j].s_horse);
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
    int num,m_num,horse;
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
                printf("좌표를 입력해주세요. : ");
                scanf("%d", &num);
                printf("놓을 말을 선택해주세요. : ");
                scanf("%d", &horse);
                system("clear");
                if(user1.putHorse(num,horse,"A")) {
                    p++;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            } else if(way==2){ // 옮기는 방법
                printf("옮길 말의 좌표를 선택해주세요. : ");
                scanf("%d", &num);
                printf("옮길 좌표를 입력해주세요. : ");
                scanf("%d", &m_num);
                system("clear");
                if(user1.moveHorse(num, m_num, "A")) {
                    p++;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            } else {
                printf("오류입니다. 다시 입력해주세요.\n");
                continue;
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
                printf("좌표를 입력해주세요. : ");
                scanf("%d", &num);
                printf("놓을 말을 선택해주세요. : ");
                scanf("%d", &horse);
                system("clear");
                if(user2.putHorse(num,horse,"B")) {
                    p--;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            } else if(way==2){ // 옮기는 방법
                printf("옮길 말의 좌표를 선택해주세요 : ");
                scanf("%d", &num);
                printf("옮길 좌표를 입력해주세요 : ");
                scanf("%d", &m_num);
                system("clear");
                if(user2.moveHorse(num, m_num, "B")) {
                    p--;
                } else {
                    pan();
                    printf("오류입니다. 다시 입력해주세요.\n");
                    continue;
                }
            } else {
                printf("오류입니다. 다시 입력해주세요.\n");
                continue;
            }
        }
        vector<Board>::iterator it;
        printf("덮여져 있는 말들\n");
        for(it = store.begin(); it != store.end(); it++) {
            cout << it->name;
            printf(": [%d] ", it->num);
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
    for(int i=1; i<=9; i++) {
        comp[i].num = i;
        comp[i].name = " ";
    }
    start();
    return 0;
}