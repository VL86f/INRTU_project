#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int sim(string in, char ss) {
	int co = count(in.begin(), in.end(), ss);

	return co;
}


int median(int form[9]) {
	int ans, max, z;
	for (int x=8;x>0;x--) {
		max = 0;
		z = 0;
		for (int y=0;y<=x;y++) {
			if (max<=form[y]) {
				max=form[y];
				z=y;
			}
		}
		swap(form[x],form[z]);
	}
	ans = form[4];
return ans;
}

int main(int argc, char** argv) {
//	cout<<"hello"<<endl;
	string line;
	ifstream in;
	ofstream output;
	int mas;
	char cmas;
	string file_in, file_out;
	cout<<"Enter file name"<<endl;
	getline(cin, file_in);
	file_out = file_in;
	int dots = file_in.find('.');
	if (dots > 0){
		file_out.erase(dots,4);
	}
	file_out = file_out + "-Filter.txt";
	in.open(file_in);
	if (in.is_open()) {
	getline(in, line, '\0');
	}
	else {
	cout<<"Error. File not found."<<endl;
	in.close();
	exit(1);
	}
	cout<<"1"<<endl;
	int count = strlen(line.c_str());
	char sin[count];
	line.copy(sin, count);
	cout<<"2 "<<count<<endl;
	int height = sim(line.c_str(), '\n');
	//height++;
	int width = sim(line.c_str(), ';');
	width=width/height;
	cout<<width<<" "<<height<<endl;
	//int input[height][width*3];
	int** input = new int*[height+2];
	for (int x=0; x<height+2; x++) {
		input[x] = new int[(width+2)*3];
	}
	for (int x=0; x<height+2; x++) {
		for (int y=0; y<(width+2)*3; y++) {
			/*if ((x==0)||(x==(height+1))||(y<3)||(y>=(width*3+3))) {
					input[x][y]=127;
			}
			else {
				input[x][y]=0;
			} */
			input[x][y]=0;
		}
	}
	int w=3;
	int h=1;
	int y=0;
	int z=0;
	int zz=0;
	char simb;
	for (int x=0;x<count;x++) {
		if (isdigit(sin[x])) {
			//cout<<"chislo"<<endl;
			z = sin[x]-'0';
			zz=zz*10+z;
		}
		else if (sin[x]==' ') {
			input[h][w]=zz;
			zz=0;
				//cout<<"Enter "<<endl;
				//cout<<"X= "<<x<<endl;
				//input[h][w]=y;
				//cout<<"Y "<<y<<endl;
				//y=0;
				w++;
		}
		else if (sin[x]=='\n') {
			//input[h][w]=y;
			//y=0;
			zz=0;
			w=3;
			h++;
		}
		else {
			//cout<<"Other"<<endl;
			zz=0;
		}
		//cout<<"W= "<<w<<"H= "<<h<<endl;
	}

int form[9];
output.open(file_out);

int sub;
int x1;
int y1;
int out;
int sum_x = 0, sum_y = 0, sum_al;
for (int x = 0; x < height; x++) {
	for (int y = 0 ; y < width*3; y++) {
		x1 = x+1;
		y1 = y+3;
		sub = input[x1][y1];
		form[1] = input[x1-1][y1];
		form[7] = input[x1+1][y1];
		form[0] = input[x1-1][y1-3];
		form[3] = input[x1][y1-3];
		form[6] = input[x1+1][y1-3];
		form[2] = input[x1-1][y1+3];
		form[5] = input[x1][y1+3];
		form[8] = input[x1+1][y1+3];
		form[4] = input[x1][y1];
		out = median(form);
		output<<out<<" ";
		if (y%3==2) {
			output<<"255;";
		}

	}
	output<<endl;
}
	in.close();
	output.close();


	return 0;
}



