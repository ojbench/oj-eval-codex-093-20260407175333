#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 10;
    vector<vector<int>> grid(N, vector<int>(N));
    int si=-1, sj=-1;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(!(cin>>grid[i][j])) return 0; // invalid input
            if(grid[i][j]==4){ si=i; sj=j; }
        }
    }
    if(si==-1){
        return 0;
    }
    // Directions: 0: up, 1: right, 2: down, 3: left
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};

    int dir = 0; // start facing up
    long long score = 0;

    // Track visited state (pos,dir) to detect cycles. Movement depends only on walls.
    bool vis[N][N][4];
    memset(vis, 0, sizeof(vis));
    vis[si][sj][dir] = true;

    int i = si, j = sj;
    while(true){
        int cand[4];
        cand[0] = (dir + 1) & 3; // right
        cand[1] = dir;           // straight
        cand[2] = (dir + 3) & 3; // left
        cand[3] = (dir + 2) & 3; // back

        bool moved = false;
        for(int k=0;k<4;k++){
            int nd = cand[k];
            int ni = i + di[nd];
            int nj = j + dj[nd];
            if(ni<0 || ni>=N || nj<0 || nj>=N) continue; // treat out-of-bounds as wall
            if(grid[ni][nj] == 0) continue; // wall
            i = ni; j = nj; dir = nd;
            moved = true;
            if(grid[i][j] == 3){
                score -= 500;
                cout << score << "\n";
                return 0;
            }
            if(grid[i][j] == 2){
                score += 2;
                grid[i][j] = 1;
            }
            break;
        }
        if(!moved){
            cout << "Silly Pacman\n";
            return 0;
        }
        if(vis[i][j][dir]){
            cout << "Silly Pacman\n";
            return 0;
        }
        vis[i][j][dir] = true;
    }
}
