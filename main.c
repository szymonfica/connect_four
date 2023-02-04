#include <stdio.h>
#include <stdlib.h>

void color(int c){
    if(c == 0) printf("\033[0m");
    if(c == 1) printf("\033[1;33m");
    if(c == 2) printf("\033[1;31m");
    if(c == 3) printf("\033[0;34m");
}

// 0 - empty, 1 - yellow, 2 - red
int tab[6][7], idx[7], n = 6, m = 7, D = 6;

void show(){
    for(int i=1; i<=m; i++){
        printf("  %d  ", i);
    }
    printf("\n\n");
    for(int i=n-1; i>=0; i--){
        printf("| ");
        for(int j=0; j<m; j++){
            color(tab[i][j]);
            if(tab[i][j] == 1){
                printf("/\\ ");
            }
            else if(tab[i][j] == 2){
                printf("\\/ ");
            }
            else{
                printf("   ");
            }
            color(0);
            printf("| ");
        }
        printf("\n");
        printf("| ");
        for(int j=0; j<m; j++){
            color(tab[i][j]);
            if(tab[i][j] == 1){
                printf("\\/ ");
            }
            else if(tab[i][j] == 2){
                printf("/\\ ");
            }
            else{
                printf("   ");
            }
            color(0);
            printf("| ");
        }
        printf("\n\n");
    }
}

// 0 - no winner, otherwise nr of a winning player
int winner(){
    int ans = 0;
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<m; j++){
            if(tab[i][j] == 0) continue;
            if(j+3 < m){
                if(tab[i][j] == tab[i][j+1] && tab[i][j+1] == tab[i][j+2] && tab[i][j+2] == tab[i][j+3]){
                    ans = tab[i][j];
                }
                if(i+3 < n){
                    if(tab[i][j] == tab[i+1][j+1] && tab[i+1][j+1] == tab[i+2][j+2] && tab[i+2][j+2] == tab[i+3][j+3]){
                        ans = tab[i][j];
                    }
                }
                if(i-3 >= 0){
                    if(tab[i][j] == tab[i-1][j+1] && tab[i-1][j+1] == tab[i-2][j+2] && tab[i-2][j+2] == tab[i-3][j+3]){
                        ans = tab[i][j];
                    }
                }
            }
            if(j-3 >= 0){
                if(tab[i][j] == tab[i][j-1] && tab[i][j-1] == tab[i][j-2] && tab[i][j-2] == tab[i][j-3]){
                    ans = tab[i][j];
                }
                if(i+3 < n){
                    if(tab[i][j] == tab[i+1][j-1] && tab[i+1][j-1] == tab[i+2][j-2] && tab[i+2][j-2] == tab[i+3][j-3]){
                        ans = tab[i][j];
                    }
                }
                if(i-3 >= 0){
                    if(tab[i][j] == tab[i-1][j-1] && tab[i-1][j-1] == tab[i-2][j-2] && tab[i-2][j-2] == tab[i-3][j-3]){
                        ans = tab[i][j];
                    }
                }
            }
            if(i+3 < n){
                if(tab[i][j] == tab[i+1][j] && tab[i+1][j] == tab[i+2][j] && tab[i+2][j] == tab[i+3][j]){
                    ans = tab[i][j];
                }
            }
            if(i-3 >= 0){
                if(tab[i][j] == tab[i-1][j] && tab[i-1][j] == tab[i-2][j] && tab[i-2][j] == tab[i-3][j]){
                    ans = tab[i][j];
                }
            }
        }
    }
    return ans;
}

void endgame(int loser){
    if(loser != 0){
        loser = (loser%2)+1;
        color(winner());
        printf("Player #%d won!\n", winner());
        return;
    }
    if(winner() == 0){
        color(3);
        printf("Draw!\n");
        color(0);
    }
    else{
        color(winner());
        printf("Player #%d won!\n", winner());
    }
}

typedef struct _pair{
    int st; // score
    int nd; // column with last drop
}pair;

int eval(int player){
    int enemy = (player%2)+1;
    int two = 0, three = 0;
    for(int i=0; i<n; i++){
        for(int k=0; k<m; k++){
            int p = i, q = k;
            // two
            if(p >= 0 && q+3 < m){
                int cnt = 0, en = 0;
                for(int j=0; j<4; j++){
                    if(tab[p][q+j] == player) cnt++;
                    else if(tab[p][q+j] == enemy) en++;
                }
                if(cnt == 2 && en == 0) two++;
                if(cnt == 3 && en == 0) three++;
            }
            if(p-3 >= 0 && q+3 < m){
                int cnt = 0, en = 0;
                for(int j=0; j<4; j++){
                    if(tab[p-j][q+j] == player) cnt++;
                    else if(tab[p-j][q+j] == enemy) en++;
                }
                if(cnt == 2 && en == 0) two++;
                if(cnt == 3 && en == 0) three++;
            }
            if(p-3 >= 0 && q < m){
                int cnt = 0, en = 0;
                for(int j=0; j<4; j++){
                    if(tab[p-j][q] == player) cnt++;
                    else if(tab[p-j][q] == enemy) en++;
                }
                if(cnt == 2 && en == 0) two++;
                if(cnt == 3 && en == 0) three++;
            }
            if(p-3 >= 0 && q-3 >= 0){
                int cnt = 0, en = 0;
                for(int j=0; j<4; j++){
                    if(tab[p-j][q-j] == player) cnt++;
                    else if(tab[p-j][q-j] == enemy) en++;
                }
                if(cnt == 2 && en == 0) two++;
                if(cnt == 3 && en == 0) three++;
            }
        }
    }
    return 100*three + two;
}



pair dfs(int depth, int col, int player){
    int win = winner();
    if(win != 0){
        pair a;
        if(win == 1) a.st = 1000;
        else a.st = -1000;
        a.nd = col;
        return a;
    }
    if(depth == D){
        pair a;
        int pp = eval(1);
        int ee = eval(2);
        a.st = pp-ee;
        a.nd = col;
        return a;
    }
    pair a = {0, 0};
    if(player == 1) a.st = -1000000;
    else a.st = 1000000;
    for(int i=0; i<m; i++){
        if(idx[i] == n) continue;
        
        tab[idx[i]][i] = player;
        idx[i]++;
        pair b = dfs(depth+1, i, (player%2)+1);
        idx[i]--;
        tab[idx[i]][i] = 0;
        if(player == 1){ // max
            if(b.st > a.st){
                a = b;
                a.nd = i;
            }
        }
        else{ // min
            if(b.st < a.st){
                a = b;
                a.nd = i;
            }
        }
    }
    return a;
}

int bot(){
    pair a = dfs(0, 0, 2);
    return a.nd+1;
}

int main(void){

    for(int i=0; i<m; i++) idx[i] = 0;
    int cnt = 7*6;
    int loser = 0;
    while(cnt--){
        int player = ((cnt+1)%2)+1;
        int x = system("clear");
        color(player);
        printf("Player #%d move\n\n", player);
        color(0);
        show();
        int col = 0;
        if(player == 1){
            if(scanf("%d", &col) != 1) return 0;
        }
        else{
            col = bot();
        }
        if(col < 1 || col > 7){
            loser = player;
            break;
        }
        col--;
        if(idx[col] == n){
            loser = player;
            break;
        }
        tab[idx[col]][col] = player;
        idx[col]++;
        if(winner() != 0) break;
        x -= x;
    }
    show();
    endgame(loser);
    

    return 0;
}
