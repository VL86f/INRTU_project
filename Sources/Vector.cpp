#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
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

	float sum_x1 = abs(sum_x);
	float sum_y1 = abs(sum_y);

	if(sum_x !=0){
		answer = atan(sum_y1/sum_x1)/(M_PI/180);
	}
	else {
		answer_out = 90;
	}
	if(answer<22.5) {
		answer_out = 0;
	}
	else if((answer >= 22.5)&&(answer < 67.5)) {
		answer_out = 45;
	}
	else {
		answer_out = 90;
	}

	if(sum_x < 0){
		answer_out = answer_out+90;
	}


/*		if(abs(answer) < 22.5) {
			answer = 0;
		}
		else if((abs(answer) > 22.5)&&(abs(answer) < 67.5)) {
			answer = 45 * (sum_y/abs(sum_y));
		}
		else {
			answer = 90 * (sum_y/abs(sum_y));
		} */


	return answer_out;
}

void vectors_check(int** image, int height, int width, int** vector_in, int** output) {
	int form[3][3];
	int answer;
	for(int x = 1;x<height-1;x++) {
		for(int y=1;y<width-1;y++) {


		form[0][1] = image[x-1][y];
		form[2][1] = image[x+1][y];
		form[0][0] = image[x-1][y-1];
		form[1][0] = image[x][y-1];
		form[2][0] = image[x+1][y-1];
		form[0][2] = image[x-1][y+1];
		form[1][2] = image[x][y+1];
		form[2][2] = image[x+1][y+1];
		form[1][1] = image[x][y];
		answer = image[x][y];

			switch(vector_in[x][y]) {
				case 0:
				case 180:
					if((form [1][1] < form[1][0]) || form[1][1] < form[1][2]) {
						answer = 0;
					}
				break;
				case 90:
					if((form [1][1] < form[0][1]) || form[1][1] < form[2][1]) {
						answer = 0;
					}
				break;
				case 135:
					if((form [1][1] < form[0][0]) || form[1][1] < form[2][2]) {
						answer = 0;
					}
				break;
				case 45:
					if((form [1][1] < form[0][2]) || form[1][1] < form[2][1]) {
						answer = 0;
					}
				break;
			}
		output[x][y] = answer;
		}
	}



}



void sobel_vectors_func(int width, int height, int** input, int** output, int** vector_tt) {



	int** image = new int*[height+2];
	for (int x=0; x<height+2; x++) {
		image[x] = new int[width+2];
	}

	for (int x=0; x<height; x++) {
		for(int y=0; y<width; y++) {
			image[x+1][y+1] = input[x][y];
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


cout<<"Calculating & out"<<endl;

int sub;
int sum_x = 0, sum_y = 0, sum_al;
int x1, y1, text_out;
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
		sum_y = (form[2][0]*mask[0]+form[2][1]*mask[1]+form[2][2]*mask[2])-(form[0][0]*mask[0]+form[0][1]*mask[1]+form[0][2]*mask[2]);
		sum_x = (form[2][2]*mask[0]+form[1][2]*mask[1]+form[0][2]*mask[2])-(form[0][0]*mask[0]+form[1][0]*mask[1]+form[2][0]*mask[2]);
		sum_al = sqrt((sum_x*sum_x)+(sum_y*sum_y));
		vector_tt[x][y] = vectors_angle(sum_x,sum_y);

		if (sum_al>255) {
			sum_al=255;
		}
		else if (sum_al<0) {
			sum_al=0;
		}
		output[x][y] = sum_al;


}
}
}
int main(int argc, char** argv) {
//	cout<<"hello"<<endl;
	string line;
	ifstream in;
	ofstream output;
	int mas;
	char cmas;
	string file_in, file_out, file_s;
	cout<<"Enter file name"<<endl;
	getline(cin, file_in);


	file_s = file_in;
	int dots = file_in.find('.');
	if (dots > 0){
		file_s.erase(dots,4);
	}
	//file_out = file_out + outs[mas];
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

	int** image = new int*[height];
	for (int x=0; x<height; x++) {
		image[x] = new int[width];
	}

	int** text_out = new int*[height];
	for (int x=0; x<height; x++) {
		text_out[x] = new int[width];
	}

	int** text_sob = new int*[height];
	for (int x=0; x<height; x++) {
		text_sob[x] = new int[width];
	}

	int** text_vec = new int*[height];
	for (int x=0; x<height; x++) {
		text_vec[x] = new int[width];
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
	for(int x=0; x<height; x++) {
		for(int y=0; y<width; y++) {
			image[x][y] = ceil((double(input[x][3*y])*0.2126)+(double(input[x][3*y+1])*0.7152)+(double(input[x][3*y+2])*0.0722)-0.5);
			//cout<<image[x][y]<<" ";

		}
		cout<<endl;
	}

sobel_vectors_func(width, height, image, text_sob, text_vec);
vectors_check(text_sob, height, width, text_vec, text_out);

	file_out = file_s + "-Vectors.txt";
	output.open(file_out);

	for (int x=0; x<height; x++) {
		for (int y=0; y<width; y++) {
			output<<text_out[x][y]<<" "<<text_out[x][y]<<" "<<text_out[x][y]<<" 255;";
		}
		output<<endl;
	}

	output.close();

cout<<"Closing"<<endl;
	in.close();
	//output.close();
	return 0;
}
