#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

 int main(int argc , char *argv[])
 {
     ifstream fin;
     ofstream fout;
     
     string in_com , out_com;
     in_com = "./";
     in_com += argv[1];
     out_com = in_com;
     in_com += "/floor.data";
     out_com += "/final.path";
     fin.open(in_com);
     fout.open(out_com);
	 
	 int B_x , B_y;
	 int r , c , B;
	 int direction=0;
	 int need_clear=0;
	 vector<int> step_x;
	 vector<int> step_y;
	 fin >> r >> c >> B;
	 char map[r][c];
	 for (int i=0 ; i<=r+1 ; i++){
		for (int j=0 ; j<=c+1 ; j++){
			if(i==0 || j == 0 || i==r+1 || j == c+1) map[i][j] = 3;
			else {
				fin >> map[i][j];
				if(map[i][j] == 'R'){
					B_x = i;
					B_y = j;
				}
				else if(map[i][j] == '0'){
					need_clear++;
				}
			}
		}
	 }
	 step_x.clear();
	 step_y.clear();
	 int now_x = B_x;
	 int now_y = B_y;
	 while(need_clear>0){
		if(now_x == B_x && now_y == B_y){
			if()
		if(direction == 0){  //Up
			if(map[now_x-1][now_y] == '0'){
				if(map[now])
				now_x = now_x-1;
				map[now_x][now_y] = 2;
				need_clear--;
			}
			else if(map[now_x-1][now_y] == '1'|| map[now_x-1][now_y] == '2'){
				direction = 1;
		}
		else if(direction == 1){ //Left
			
		}
		else if(direction == 2){ //Right
		}
		else { //Down
		}
	 }
	 fin.close();
     fout.close();
     return 0;
 }
