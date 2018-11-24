#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int B_x , B_y , r , c , step;
char map[r][c];
vector<int> step_x;
vector<int> step_y;
void back_to_R(int x , int y)
{
	int n=step_x.size()-1;
	while(1){
		if(x == B_x && y == B_y) break;
		else {
			step_x.push_back(step_x[n]);
			step_y.push_back(step_y[n]);
			step++;
			n--;
		}
	}
	step_x.push_back(B_x);
	step_y.push_back(B_y);
	return;
}	

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
	 
	 int b;
	 int B;
	 int direction=0;
	 int need_clear=0;
	 fin >> r >> c >> B;
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
	 b = B;
	 step = 0;
	 while(need_clear>0){
		if(b < B/2+1){
			back_to_R(now_x , now_y);
			now_x = B_x;
			now_y = B_y;
			b = B;
		}
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
				map[now_x][now_y] = '2';
				if(step == 0) B_x = B_x-1;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
				need_clear--;
			}
			else if(map[now_x][now_y-1] == '0'){
				direction = 0;
				wall_at_right = true;
				now_y = now_y-1;
				map[now_x][now_y] = '2';
				if(step == 0) B_y = B_y-1;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
				need_clear--;
			}
			else if(map[now_x][now_y+1] == '0'){
				direction = 0;
				now_y = now_y+1;
				map[now_x][now_y] = '2';
				if(step == 0) B_y = B_y+1;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
				need_clear--;
			}
			else {
				direction = 1;
				wall_at_right = true;
				now_x = now_x+1;
				map[now_x][now_y] = '2';
				if(step == 0) B_x = B_x+1;
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
				need_clear--;
			}
		}
		if(direction == 0){  //Up
			if(map[now_x-1][now_y] == '0'){
				now_x = now_x-1;
				map[now_x][now_y] = '2';
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
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
				map[now_x][now_y] = '2';
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
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
				map[now_x][now_y] = '2';
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
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
				map[now_x][now_y] = '2';
				step_x.push_back(atoi(now_x));
				step_y.push_back(atoi(now_y));
				step++;
				b--;
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
