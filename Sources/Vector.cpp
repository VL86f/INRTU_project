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

int vectors_angle(int sum_x, int sum_y) {
	float answer;
	int answer_out;
	if(sum_x == 0) {
		if(sum_y>0) {
			answer_out = 0;
		}
		else if(sum_y<0) {
			answer_out = 180;
		}
		else {
			answer_out = -1;
		}
	}
	else {
		answer = (atan(sum_y/sum_x))/(M_PI/180);

		if(abs(answer) < 22.5) {
			answer = 0;
		}
		else if((abs(answer) > 22.5)&&(abs(answer) < 67.5)) {
			answer = 45 * (sum_y/abs(sum_y));
		}
		else {
			answer = 90 * (sum_y/abs(sum_y));
		}


		if(sum_x > 0) {
			answer_out = 270 + answer;
		}
		else {
			answer_out = 90 + answer;
		}
		if(answer_out == 360) {
			answer_out = 0;
		}
	}


	return answer_out;
}

int main(int argc, char** argv) {
//	cout<<"hello"<<endl;
	string line;
	ifstream in;
	ofstream output;
	ofstream vector_out;
	int mas;
	char cmas;
	string outs[2] = {"-Sobel.txt", "-Vector.txt"};
	string file_in, file_out, file_v;
	cout<<"Enter file name"<<endl;
	getline(cin, file_in);
	int x1,y1;
	file_out = file_in;
	int dots = file_in.find('.');
	if (dots > 0){
		file_out.erase(dots,4);
	}
	file_v = file_out + outs[1];
	file_out = file_out + outs[0];
	in.open(file_in);
	if (in.is_open()) {
	getline(in, line, '\0');
	}
	else {
	cout<<"Error. File not found."<<endl;
	in.close();
	exit(1);
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

/*	int** vector = new int*[height];
	for (int x=0; x<height; x++) {
		vector[x] = new int [width];
	} */

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

			zz=0;
		}

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

		}
	}
	image[0][0]=(image[1][0]+image[0][1])/2;
	image[0][width+1]=(image[0][width]+image[1][width+1])/2;
	image[height+1][0]=(image[height+1][1]+image[height][0])/2;
	image[height+1][width+1]=(image[height][width+1]+image[height+1][width])/2;

int mask[3] = {1, 2, 1};


int form[3][3];
output.open(file_out);
vector_out.open(file_v);

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
		sum_x = (form[2][0]*mask[0]+form[2][1]*mask[1]+form[2][2]*mask[2])-(form[0][0]*mask[0]+form[0][1]*mask[1]+form[0][2]*mask[2]);
		sum_y = (form[2][2]*mask[0]+form[1][2]*mask[1]+form[0][2]*mask[2])-(form[0][0]*mask[0]+form[1][0]*mask[1]+form[2][0]*mask[2]);
		sum_al = abs(sum_x)+abs(sum_y);
		//vector[x][y] = vectors_angle(sum_x,sum_y);

		if (sum_al>255) {
			sum_al=255;
		}
		else if (sum_al<0) {
			sum_al=0;
		}
		output<<sum_al<<" "<<sum_al<<" "<<sum_al<<" 255;";
		vector_out<<vectors_angle(sum_x,sum_y)<<"; ";
	}
	output<<endl;
	vector_out<<endl;
}
cout<<"Closing"<<endl;
	in.close();
	output.close();
	vector_out.close();
	return 0;
}
