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

double create_gauss_kernel(int sigmasize, double** GaussKernel, double sigma) {
	int a,b;
	double sum=0;
	double sigma2 = 2 * pow(sigma, 2);
	double res1,res2;
	res1 = 1/(M_PI*sigma2);
	for(int x=0;x<sigmasize;x++) {
		a = x - (sigmasize/2);
		for(int y=0;y<sigmasize;y++) {
			b = y - (sigmasize/2);
			res2 =  exp(-(a*a+b*b) / sigma2);
			GaussKernel[x][y] = res1*res2;
			sum+= GaussKernel[x][y];
		}

	}
return sum;
}


void calculate_picture (int sigmasize, int width, int height, int** input, int** output, double sigma) {
	double** GaussKernel = new double*[sigmasize];
	for(int x=0; x<sigmasize; x++) {
		GaussKernel[x] = new double[sigmasize];
	}
	double sum = create_gauss_kernel(sigmasize, GaussKernel, sigma);
	cout<<"sum = "<<sum<<endl;

	int k,l,al_sum,a1,b1;
	//create_gauss_kernel(sigmasize, GaussKernel, sigma);
	for(int x=0;x<height;x++){
		k = x + sigmasize/2;
		for(int y=0;y<width;y++){
			al_sum=0;
			l = y + sigmasize/2;
			for(int a=0;a<sigmasize;a++) {
				a1 = a - (sigmasize/2);
				for(int b=0;b<sigmasize;b++) {
					b1 = b - (sigmasize/2);
					al_sum+=GaussKernel[a][b]*input[k+a1][l+b1];
				}
			}
			output[x][y] = floor(0.5+(al_sum/sum));

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
	double sigma;
	int sigmasize;
	string outs = "-Gauss.txt";
	string file_in, file_out;
	cout<<"Enter file name"<<endl;
	getline(cin, file_in);
	cout<<"Enter the sigma value:"<<endl;
	cin>>sigma;
	//sigma = 0.84089642;
	int x1,y1;

	sigmasize = ceil(sigma*6);
	if(sigmasize%2==0) {
		sigmasize++;
	}

	file_out = file_in;
	int dots = file_in.find('.');
	if (dots > 0){
		file_out.erase(dots,4);
	}
	file_out = file_out + outs;
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

	int** image = new int*[height+sigmasize-1];
	for (int x=0; x<height+sigmasize-1; x++) {
		image[x] = new int[width+sigmasize-1];
	}
	for(int x=0;x<height+sigmasize-1;x++){
		for(int y=0;y<width+sigmasize-1;y++) {
			image[x][y] = 127;
		}
	}
	int** image_out = new int*[height];
	for (int x=0; x<height; x++) {
		image_out[x] = new int[width];
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
			x1 = x+sigmasize/2;
			y1 = y+sigmasize/2;
			image[x1][y1] = ceil((double(input[x][3*y])*0.2126)+(double(input[x][3*y+1])*0.7152)+(double(input[x][3*y+2])*0.0722)+0.5);
		}
	}
	cout<<"Create the ram : DISABLED"<<endl;
	/*	for (int x=0; x<height+2; x++) {
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
	image[height+1][width+1]=(image[height][width+1]+image[height+1][width])/2; */

cout<<"Calculating"<<endl;

calculate_picture(sigmasize, width, height, image, image_out, sigma);




cout<<"Create output file"<<endl;

output.open(file_out);

cout<<"Write file"<<endl;
for(int x=0;x<height;x++) {
	for(int y=0;y<width;y++) {
		output<<image_out[x][y]<<" "<<image_out[x][y]<<" "<<image_out[x][y]<<" 255;";
	}
	output<<endl;
}

cout<<"Closing files"<<endl;
	in.close();
	output.close();
	return 0;
}
