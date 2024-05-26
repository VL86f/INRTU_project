#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <ostream>

#include "Canny.h"

//using namespace std;

int sim(std::string in, char ss) {
	int co = count(in.begin(), in.end(), ss);

	return co;
}





int main(int argc, char** argv) {
//	cout<<"hello"<<endl;
	std::string line;
	std::ifstream in;
	std::ofstream output;
	int mas;
	double sigma;
	std::string min, max;
	int min_porog, max_porog, numb;
	char cmas;
	std::string file_in, file_out, file_s;
	std::cout<<"Enter file name"<<std::endl;
	std::getline(std::cin, file_in);
	std::cout<<file_in<<std::endl;
    std::cout<<"Enter the sigma value:"<<std::endl;
	std::cin>>sigma;
	std::cout<<sigma<<std::endl;

//	std::cout<<std::flush;
	std::cout<<"Enter minimum value for thresholding function"<<std::endl;
	//std::getline(std::cin, min);
	std::cin>>min_porog;
	std::cout<<min_porog<<std::endl;
	std::cout<<"Enter maximum value for thresholding function"<<std::endl;
	std::cin>>max_porog;
	//std::getline(std::cin, max);
	std::cout<<max_porog<<std::endl;
/*
	numb = min.length();
	for(int x; x< numb; x++) {
		min_porog = min_porog + min[x]-'0';
		min_porog = min_porog*10;
	}
	min_porog = min_porog/10;

	numb = max.length();
	for(int x; x< numb; x++) {
		max_porog = max_porog + max[x]-'0';
		max_porog = max_porog*10;
	}
	max_porog = max_porog/10;
*/

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
	std::cout<<"Error. File not found."<<std::endl;
	in.close();
	exit(1);
	}
	std::cout<<"Reading"<<std::endl;
	int count = strlen(line.c_str());
	char sin[count];
	line.copy(sin, count);
	std::cout<<"Converting "<<std::endl;
	int height = sim(line.c_str(), '\n');
	//height++;
	int width = sim(line.c_str(), ';');
	width=width/height;
	std::cout<<width<<" "<<height<<std::endl;
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

	int** text_gauss = new int*[height];
	for (int x=0; x<height; x++) {
		text_gauss[x] = new int[width];
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
	std::cout<<"Convert to Grey"<<std::endl;
	for(int x=0; x<height; x++) {
		for(int y=0; y<width; y++) {
			image[x][y] = ceil((double(input[x][3*y])*0.2126)+(double(input[x][3*y+1])*0.7152)+(double(input[x][3*y+2])*0.0722)-0.5);
			//cout<<image[x][y]<<" ";

		}
	}

    gauss_fliter_func(width, height, image, text_gauss, sigma);

	int** text_sob = new int*[height];
	for (int x=0; x<height; x++) {
		text_sob[x] = new int[width];
	}

	int** text_vec = new int*[height];
	for (int x=0; x<height; x++) {
		text_vec[x] = new int[width];
	}

	int** text_cont = new int*[height];
	for (int x=0; x<height; x++) {
		text_cont[x] = new int[width];
	}

    sobel_vectors_func(width, height, text_gauss, text_sob, text_vec);
    vectors_check(text_sob, height, width, text_vec, text_cont);


    int** text_doub = new int*[height];
	for (int x=0; x<height; x++) {
		text_doub[x] = new int[width];
	}
    Double_porog(height, width, text_cont, text_doub, min_porog, max_porog);

    border_track(text_doub, text_out, height, width);

	file_out = file_s + "-Finals.txt";
	output.open(file_out);

	for (int x=0; x<height; x++) {
		for (int y=0; y<width; y++) {
			output<<text_out[x][y]<<" "<<text_out[x][y]<<" "<<text_out[x][y]<<" 255;";
		}
		output<<std::endl;
	}

	output.close();

    std::cout<<"Closing"<<std::endl;
	in.close();
	//output.close();
	return 0;
}
