#include<stdio.h>
#define M 4

char path[M*M];
char dir[]="DLRU";
char dc[4]={0,-1,1,0};
char dr[4]={1,0,0,-1};
int check_valid(int maze[][M],int row, int col) {
	if(row>=0 && col>=0 && row<M && col<M && maze[row][col])
		return 1;
	return 0;
}


void find_path(int maze[][M],int idx,int row, int col) {
	if(maze[row][col]==0 || maze[M-1][M-1]==0)
		return;
	if(row==M-1 && col==M-1) {
		path[idx]='\0';
		printf("%s\n", path);
		return;
	}
	maze[row][col]=0;
	for(int i=0; i<M; i++) {
		int next_row=row+dr[i];
		int next_col=col+dc[i];
		if(check_valid(maze,next_row,next_col)) {
			path[idx]=dir[i];
			find_path(maze,idx+1,next_row,next_col);
		}
	}
	maze[row][col]=1;
}

int main () {
	int maze[][M]={  { 1, 0, 0, 0 },
            	{ 1, 1, 0, 1 },
                { 1, 1, 0, 0 },
                { 0, 1, 1, 1 } };
    find_path(maze,0,0,0);
}