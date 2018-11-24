#include<iostream>
#include<fstream>

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
	 
	 
	 
	 fin.close();
     fout.close();
     return 0;
 }
