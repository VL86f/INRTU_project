#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int sim(string in, char ss) {
	int co = count(in.begin(), in.end(), ss);

	return co;
}



int main(int argc, char** argv) {
//	cout<<"hello"<<endl;
	string line;
	ifstream in;
	ofstream output;
	int mas;
	char cmas;
	string outs[3] = {"-Previtt.txt", "-Sobel.txt", "-Shaar.txt"};
	string file_in, file_out;
	cout<<"Enter file name"<<endl;
	getline(cin, file_in);
	int x1,y1;
	bool inf = false;
	while(inf != true) {
		cout<<"Enter type of mask: "<<endl;
		cout<<"1) Previtt's mask"<<endl;
		cout<<"2) Sobel's mask"<<endl;
		cout<<"3) Shaar's mask"<<endl;
		cin>>cmas;
		switch(cmas) {
			case '1':
				mas = 0;
				inf = true;
			break;
			case '2':
				mas = 1;
				inf = true;
			break;
			case '3':
				mas = 2;
				inf = true;
			break;
			default:
				cout<<"Error. Try again"<<endl;
			break;
		}
	}
	file_out = file_in;
	int dots = file_in.find('.');
	if (dots > 0){
		file_out.erase(dots,4);
	}
	file_out = file_out + outs[mas];
	in.open(file_in);
	if (in.is_open()) {
	getline(in, line, '\0');
	}
	else {
	cout<<"Error. File not found."<<endl;
	}
	cout<<"Reading"<<endl;
	int count = strlen(line.c_str());
	char sin[count];
	line.copy(sin, count);
	cout<<"Converting "<<endl;
	int height = sim(line.c_str(), '\n');
	//height++;
	int width = sim(line.c_str(), ';');
	width=width/height;
	cout<<width<<" "<<height<<endl;
	//int image[height][width*3];
	int** input = new int*[height];
	for (int x=0; x<height; x++) {
		input[x] = new int[width*3];
	}

	int** image = new int*[height+2];
	for (int x=0; x<height+2; x++) {
		image[x] = new int[width+2];
	}

	int w=0;
	int h=0;
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
			w=0;
			h++;
		}
		else {
			//cout<<"Other"<<endl;
			zz=0;
		}
		//cout<<"W= "<<w<<"H= "<<h<<endl;
	}
	cout<<"Convert to Grey"<<endl;
	for(int x=1; x<height+1; x++) {
		for(int y=1; y<width+1; y++) {
			x1 = x-1;
			y1 = y-1;
			image[x][y] = ceil((double(input[x1][3*y1])*0.2126)+(double(input[x1][3*y1+1])*0.7152)+(double(input[x1][3*y1+2])*0.0722)+0.5);
		}
	}
	cout<<"Create the ram"<<endl;
		for (int x=0; x<height+2; x++) {
		for (int y=0; y<width+2; y++) {
			if ((x==0)||(x==(height+1))) {
				//cout<<"x= "<<x<<" 1"<<endl;
					if (x==0) {
						image[x][y]=image[x+1][y];
						//image[x][y]=127;
					}
					else {
						image[x][y]=image[x-1][y];
						//image[x][y]=127;
					}
			}
			else if ((y==0)||(y==width+1)) {
				//cout<<"y= "<<y<<" 2"<<endl;
					if(y==0) {
						image[x][y]=image[x][y+1];
						//image[x][y]=127;
					}
					else {
						image[x][y]=image[x][y-1];
						//image[x][y];
					}
			}
			//image[x][y]=0;
		}
	}
	image[0][0]=(image[1][0]+image[0][1])/2;
	image[0][width+1]=(image[0][width]+image[1][width+1])/2;
	image[height+1][0]=(image[height+1][1]+image[height][0])/2;
	image[height+1][width+1]=(image[height][width+1]+image[height+1][width])/2;

int mask[3][3] = {
	{1, 1, 1},
	{1, 2, 1},
	{3, 10, 3}
};


int form[3][3];
output.open(file_out);

cout<<"Calculating & out"<<endl;

int sub;
int sum_x = 0, sum_y = 0, sum_al;
for (int x = 0; x < height; x++) {
	for (int y = 0 ; y < width; y++) {
		x1 = x+1;
		y1 = y+1;
		sub = image[x1][y1];
		form[0][1] = image[x1-1][y1];
		form[2][1] = image[x1+1][y1];
		form[0][0] = image[x1-1][y1-1];
		form[1][0] = image[x1][y1-1];
		form[2][0] = image[x1+1][y1-1];
		form[0][2] = image[x1-1][y1+1];
		form[1][2] = image[x1][y1+1];
		form[2][2] = image[x1+1][y1+1];
		sum_x = (form[0][0]*mask[mas][0]+form[0][1]*mask[mas][1]+form[0][2]*mask[mas][2])-(form[2][0]*mask[mas][0]+form[2][1]*mask[mas][1]+form[2][2]*mask[mas][2]);
		sum_y = (form[0][0]*mask[mas][0]+form[1][0]*mask[mas][1]+form[2][0]*mask[mas][2])-(form[2][2]*mask[mas][0]+form[1][2]*mask[mas][1]+form[0][2]*mask[mas][2]);
		sum_al = abs(sum_x)+abs(sum_y);
		if (sum_al>255) {
			sum_al=255;
		}
		else if (sum_al<0) {
			sum_al=0;
		}
		output<<sum_al<<" "<<sum_al<<" "<<sum_al<<" 255;";
	}
	output<<endl;
}
cout<<"Closing"<<endl;
	in.close();
	output.close();
	return 0;
}
