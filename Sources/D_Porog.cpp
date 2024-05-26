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



void Double_porog (int height, int width, int** input, int** output, int porog_min, int porog_max) {

	for(int x=0;x< height; x++) {
		for (int y=0;y<width;y++) {
			if(input[x][y]<=porog_min) {
				output[x][y] = 0;
			}
			else if (input[x][y]>=porog_max) {
				output[x][y] = 255;
			}
			else
				output[x][y] = 127;
		}
	}
}

int main(int argc, char** argv) {
//	cout<<"hello"<<endl;
	string line;
	ifstream in;
	ofstream output;
	int mas, min, max;
	char cmas;
	string file_in, file_out, file_s;
	cout<<"Enter file name"<<endl;
	getline(cin, file_in);
	cout<<"Enter minimum value for thresholding function"<<endl;
	cin>>min;
	cout<<"Enter maximum value for thresholding function"<<endl;
	cin>>max;




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

	Double_porog(height, width, image, text_out, min, max);

	file_out = file_s +"-Double_" + to_string(min) + "x" + to_string(max) + ".txt";
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
