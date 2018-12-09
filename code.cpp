#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

struct vec {
	int x , y;
	int g , h , f;
	vec* last;
};

char map[1010][1010];
int B_x , B_y , r , c , step , b;
vector<int> step_x;
vector<int> step_y;
vector<struct vec*> fi;
vector<int> go_back;
queue<int> temp;
vector<struct vec*> opened;

bool check(vec* A)
{
	int i=0;
	while(i < opened.size()){
		if(opened[i]->x == A->x && opened[i]->y == A->y) {
			return true;
		}
		i++;
	}
	return false;
}

int check_fi(vec* A)
{
	int i=0;
	while(i < fi.size()){
		if(fi[i]->x == A->x && fi[i]->y == A->y) {
			return i;
		}
		i++;
	}
	return 0;
}

vec* find_shortest(int end_x , int end_y , vec* start)
{
	if(map[start->x][start->y] != '1'){
		if((start->x) > 0 && (start->y) > 0 && (start->x) < (r+1) && (start->y) < (c+1)){
			if(map[(start->x)+1][start->y] != '1' && (start->x) < r){ //A
				vec* A = new vec;
				A->last = start;
				A->x = (start->x)+1;
				A->y = start->y;
				A->g = (A->last->g) + 1;
				A->h = end_x + end_y - (A->x) - (A->y);
				if (A->h > 0) A->f = (A->g) + (A->h);
				else A->f = (A->g) - (A->h);
				if((A->x) == end_x && (A->y) == end_y) return A;
				if(!check(A)){
					if(fi.empty()) fi.push_back(A);
					else {
						int x = check_fi(A);
						if(x != 0){
							if((fi[x]->f) > (A->f)) {
								fi.erase(fi.begin()+x , fi.begin()+x+1);
								int i = fi.size()-1;
								vec* X = fi[i];
								while((X->f) < (A->f)){
									i--;
									if(i == -1) break;
									else X = fi[i];
								}
								if(i == -1) fi.insert(fi.begin() , A);
								else fi.insert(fi.begin()+i , A);
							}
						}
						else {
							int i = fi.size()-1;
							vec* X = fi[i];
							while((X->f) < (A->f)){
								i--;
								if(i == -1) break;
								else X = fi[i];
							}
							if(i == -1) fi.insert(fi.begin() , A);
							else fi.insert(fi.begin()+i , A);
						}
					}
				}
			}
			if(map[(start->x)-1][start->y] != '1' && (start->x) > 1){ //B
				vec* B = new vec;
				B->last = start;
				B->x = (start->x)-1;
				B->y = start->y;
				B->g = (B->last->g) + 1;
				B->h = end_x + end_y - (B->x) - (B->y);
				if(B->h > 0) B->f = (B->g) + (B->h);
				else B->f = (B->g) - (B->h);
				if((B->x) == end_x && (B->y) == end_y) return B;
				if(!check(B)){
					if(fi.empty()) fi.push_back(B);
					else {
						int x = check_fi(B);
						if(x != 0){
							if((fi[x]->f) > (B->f)) {
								fi.erase(fi.begin()+x , fi.begin()+x+1);
								int i = fi.size()-1;
								vec* X = fi[i];
								while((X->f) < (B->f)){
									i--;
									if(i == -1) break;
									else X = fi[i];
								}
								if(i == -1) fi.insert(fi.begin() , B);
								else fi.insert(fi.begin()+i , B);
							}
						}
						else {
							int i=fi.size()-1;
							vec* X = fi[i];
							while((X->f) < (B->f)){
								i--;
								if(i == -1) break;
								else X = fi[i];
							}
							if(i == -1) fi.insert(fi.begin() , B);
							else fi.insert(fi.begin()+i , B);
						}
					}
				}
			}
			if(map[start->x][(start->y)+1] != '1' && (start->y) < c){ //C
				vec* C = new vec;
				C->last = start;
				C->x = start->x;
				C->y = (start->y)+1;
				C->g = (C->last->g) + 1;
				C->h = end_x + end_y - (C->x) - (C->y);
				if(C->h > 0) C->f = (C->h) + (C->g);
				else C->f = (C->g) - (C->h);
				if(C->x == end_x && C->y == end_y) return C;
				if(!check(C)){
					if(fi.empty()) fi.push_back(C);
					else {
						int x = check_fi(C);
						if(x != 0){
							if((fi[x]->f) > (C->f)) {
								fi.erase(fi.begin()+x , fi.begin()+x+1);
								int i=fi.size()-1;
								vec* X = fi[i];
								while((X->f) < (C->f)){
									i--;
									if(i == -1) break;
									else X = fi[i];
								}
								if(i == -1) fi.insert(fi.begin() , C);
								else fi.insert(fi.begin()+i , C);
							}
						}
						else {
							int i=fi.size()-1;
							vec* X = fi[i];
							while((X->f) < (C->f)){
								i--;
								if(i == -1) break;
								else X = fi[i];
							}
							if(i == -1) fi.insert(fi.begin() , C);
							else fi.insert(fi.begin()+i , C);
						}
					}
				}
			}
			if(map[start->x][(start->y)-1] != '1' && (start->y) > 1){ //D
				vec* D = new vec;
				D->last = start;
				D->x = start->x;
				D->y = (start->y)-1;
				D->g = (D->last->g) + 1;
				D->h = end_x + end_y - (D->x) - (D->y);
				if(D->h > 0) D->f = (D->g) + (D->h);
				else D->f = (D->g) - (D->h);
				if(D->x == end_x && D->y == end_y) return D;
				if(!check(D)){
					if(fi.empty()) fi.push_back(D);
					else {
						int x = check_fi(D);
						if(x != 0){
							if((fi[x]->f) > (D->f)) {
								fi.erase(fi.begin()+x , fi.begin()+x+1);
								int i=fi.size()-1;
								vec* X = fi[i];
								while((X->f) < (D->f)){
									i--;
									if(i == -1) break;
									else X = fi[i];
								}
								if(i == -1) fi.insert(fi.begin() , D);
								else fi.insert(fi.begin()+i , D);
							}
						}
						else {
							int i=fi.size()-1;
							vec* X = fi[i];
							while((X->f) < (D->f)){
								i--;
								if(i == -1) break;
								else X = fi[i];
							}
							if(i == -1) fi.insert(fi.begin() , D);
							else fi.insert(fi.begin()+i , D);
						}
					}
				}
			}
			vec* X = fi.back();
			opened.push_back(X);
			fi.pop_back();
			find_shortest(end_x , end_y , X);
		}
		else { //out of the map
			if(fi.empty()){
				vec* Y;
				cout << "find shortest failed";
				return Y;
			}
			else {
				vec* X = fi.back();
				opened.push_back(X);
				fi.pop_back();
				find_shortest(end_x , end_y , X);
			}
		}
	}
}

int count_step(int now_x , int now_y , int end_x , int end_y , vec* root)
{
	fi.clear();
	opened.clear();
	opened.push_back(root);
	vec* X = find_shortest(end_x , end_y , root);
	int cou=0;
	go_back.clear();
	while(1){
		cou++;
		go_back.push_back(X->x);
		go_back.push_back(X->y);
		if(X->last != root)X = X->last;
		else break;
	}
	return cou;
}

void moveto()
{
	while(!go_back.empty()){
		step++;
		b++;
		step_y.push_back(go_back.back());
		go_back.pop_back();
		step_x.push_back(go_back.back());
		go_back.pop_back();
	}
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
	
	 int B;
	 int direction=0;
	 int need_clear=0;
	 cin >> r >> c >> B;
	 for (int i=0 ; i<=r+1 ; i++){
		for (int j=0 ; j<=c+1 ; j++){
			if(i==0 || j == 0 || i==r+1 || j == c+1) map[i][j] = '1';
			else {
				cin >> map[i][j];
				if(map[i][j] == 'R'){
					B_x = i;
					B_y = j;
					map[i][j] = '1';
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
	 b = 0;
	 step = 0;
	 while(need_clear>0){
		if(2*b >= B-1){
			vec* root = new vec;
			root->x = now_x;
			root->y = now_y;
			root->g = 0;
			root->h = B_x + B_y - now_x - now_y;
			if(root->h > 0) root->f = root->g + root->h;
			else root->f = root->g - root->h;
			int x = count_step(now_x , now_y , B_x , B_y , root);
			if(x+b <= B && x+b > B-2) {
				moveto();
				int i=step-2;
				while(x--){
					step++;
					b++;
					step_y.push_back(step_y[i]);
					step_x.push_back(step_x[i]);
					i--;
				}
				b = x;
			}
		}
		if(map[now_x-1][now_y]!='0' && map[now_x+1][now_y]!='0' && map[now_x][now_y-1]!='0' && map[now_x][now_y+1]!='0'){
			vec* root = new vec;
			root->x = now_x;
			root->y = now_y;
			root->g = 0;
			root->h = B_x + B_y - now_x - now_y;
			if(root->h > 0) root->f = root->g + root->h;
			else root->f = root->g - root->h;
			int x = count_step(now_x , now_y , B_x , B_y , root);
			moveto();
			b = 0;
			int next_x , next_y;
			while(1){
				next_x = temp.front();
				temp.pop();
				next_y = temp.front();
				temp.pop();
				if (map[next_x][next_y] == '0') break;
			}
			root->x = B_x;
			root->y = B_y;
			root->g = 0;
			root->h = next_x + next_y - B_x - B_y;
			if(root->h > 0) root->f = root->g + root->h;
			else root->f = root->g - root->h;
			x = count_step(B_x , B_y , next_x , next_y , root);
			moveto();
			now_x = next_x;
			now_y = next_y;
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
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
			}
			else if(map[now_x][now_y-1] == '0'){
				direction = 0;
				wall_at_right = true;
				now_y = now_y-1;
				map[now_x][now_y] = '2';
				if(step == 0) B_y = B_y-1;
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
			}
			else if(map[now_x][now_y+1] == '0'){
				direction = 0;
				now_y = now_y+1;
				map[now_x][now_y] = '2';
				if(step == 0) B_y = B_y+1;
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
			}
			else {
				direction = 1;
				wall_at_right = true;
				now_x = now_x+1;
				map[now_x][now_y] = '2';
				if(step == 0) B_x = B_x+1;
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
			}
		}
		if(direction == 0){  //Up
			if(map[now_x-1][now_y] == '0'){
				now_x = now_x-1;
				map[now_x][now_y] = '2';
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
				if(wall_at_right) {
					if(map[now_x][now_y+1] == '0') {
						direction = 2;
						if(map[now_x][now_y-1] == '0'){
							temp.push(now_x);
							temp.push(now_y-1);
						}
					}
				}
				else if(!no_wall){
					if(map[now_x][now_y-1] == '0') {
						direction = 1;
						if(map[now_x][now_y+1] == '0'){
							temp.push(now_x);
							temp.push(now_y+1);
						}
					}
				}
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
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
				if(wall_at_right) {
					if(map[now_x-1][now_y] == '0') {
						direction = 0;
						if(map[now_x+1][now_y] == '0'){
							temp.push(now_x+1);
							temp.push(now_y);
						}
					}
				}
				else {
					if(map[now_x+1][now_y] == '0') {
						direction = 3;
						if(map[now_x-1][now_y] == '0'){
							temp.push(now_x-1);
							temp.push(now_y);
						}
					}
				}
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
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
				if(wall_at_right) {
					if(map[now_x+1][now_y] == '0') {
						direction = 3;
						if(map[now_x-1][now_y] == '0'){
							temp.push(now_x-1);
							temp.push(now_y);
						}
					}
				}
				else {
					if(map[now_x-1][now_y] == '0') {
						direction = 0;
						if(map[now_x+1][now_y] == '0'){
							temp.push(now_x+1);
							temp.push(now_y);
						}
					}
				}
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
				step_x.push_back(now_x);
				step_y.push_back(now_y);
				step++;
				b++;
				need_clear--;
				if(wall_at_right) {
					if(map[now_x][now_y-1] == '0') {
						direction = 1;
						if(map[now_x][now_y+1] == '0'){
							temp.push(now_x);
							temp.push(now_y+1);
						}
					}
				}
				else {
					if(map[now_x][now_y+1] == '0') {
						direction = 2;
						if(map[now_x][now_y-1] == '0'){
							temp.push(now_x);
							temp.push(now_y-1);
						}
					}
				}
			}
			else {
				if(wall_at_right) direction = 2;
				else direction = 1;
			}
		}
	}
	
	vec* root = new vec;
	root->x = step_x.back();
	root->y = step_y.back();
	root->g = 0;
	root->h = B_x + B_y - root->x - root->y;
	if(root->h > 0) root->f = root->g + root->h;
	else root->f = root->g - root->h;
	int x = count_step(step_x.back() , step_y.back() , B_x , B_y , root);
	moveto();
	
	fout << step << endl;
	for(int i=0 ; i<step ; i++){
		fout << step_x[i]-1 << ' ';
	 	fout << step_y[i]-1 << endl; 
	}
	fin.close();
    fout.close();
    return 0;
 }
