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
	 
	 int B_x , B_y , B_dir;
	 int r , c , B , step=0;
	 int direction=0;
	 int need_clear=0;
	 vector<int> step_x;
	 vector<int> step_y;
	 fin >> r >> c >> B;
	 char map[r][c];
	 for (int i=0 ; i<=r+1 ; i++){
		for (int j=0 ; j<=c+1 ; j++){
			if(i==0 || j == 0 || i==r+1 || j == c+1) map[i][j] = 1;
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
	 bool wall_at_right = false;
	 bool no_wall = false;
	 while(need_clear>0){
		if(now_x == B_x && now_y == B_y){
			if(map[now_x-1][now_y] == '0'){
				if(map[now_x][now_y+1] == '1') {
					direction = 2;
					wall_at_right = true;
				}
				else if(map[now_x][now_y-1] == '1') direction = 1;
				else {
					direction = 0;
					no_wall = true;
				}
				now_x = now_x-1;
				B_dir = 0;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else if(map[now_x][now_y-1] == '0'){
				direction = 0;
				wall_at_right = true;
				now_y = now_y-1;
				B_dir = 1;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else if(map[now_x][now_y+1] == '0'){
				direction = 0;
				now_y = now_y+1;
				B_dir = 2;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else {
				direction = 1;
				wall_at_right = true;
				now_x = now_x+1;
				B_dir = 3;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
		if(direction == 0){  //Up
			if(map[now_x-1][now_y] == '0'){
				now_x = now_x-1;
				map[now_x][now_y] = 2;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else {
				if(wall_at_right) direction = 1;
				else if (no_wall){
					direction = 1;
					no_wall = false;
					wall_at_right = true;
				}
				else direction = 2;
			}
		}
		else if(direction == 1){ //Left
			if(map[now_x][now_y-1] == '0'){
				now_y = now_y-1;
				map[now_x][now_y] = 2;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else {
				if(wall_at_right) direction = 3;
				else direction = 0;
			}
		}
		else if(direction == 2){ //Right
			if(map[now_x][now_y+1] == '0'){
				now_y = now_y+1;
				map[now_x][now_y] = 2;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else {
				if(wall_at_right) direction = 0;
				else direction = 3;
			}
		}
		else { //Down
			if(map[now_x+1][now_y] == '0'){
				now_x = now_x+1;
				map[now_x][now_y] = 2;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				need_clear--;
			}
			else {
				if(wall_at_right) direction = 2;
				else direction = 1;
			}
		}
	 }
	 fout << step << endl;
	 for(int i=0 ; i<step ; i++){
		 fout << step_x[i] << ' ';
		 fout << step_y[i] << endl; 
	 }
	 fin.close();
     fout.close();
     return 0;
 }
