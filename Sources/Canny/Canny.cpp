#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>


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

void gauss_fliter_func( int width, int height, int** input, int** output, double sigma) {
//	cout<<"hello"<<endl;


	int mas;
	char cmas;
	int sigmasize;

	//sigma = 0.84089642;
	int x1,y1;

	sigmasize = ceil(sigma*6);
	if(sigmasize%2==0) {
		sigmasize++;
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

	//cout<<"extend"<<endl;
	for(int x=0; x<height; x++) {
		for(int y=0; y<width; y++) {
			x1 = x+sigmasize/2;
			y1 = y+sigmasize/2;
			image[x1][y1] = input[x][y];
		}
	}
	//cout<<"Create the ram"<<endl;
	int halfsize = sigmasize/2;
	int allsizex = height+sigmasize-1;
	int allsizey = width+sigmasize-1;
	x1 = 1;

	for (int x=0; x<halfsize+1; x++) {//work
		for(int y=halfsize;y<allsizey-sigmasize+halfsize+1;y++) {
			image[x][y] = image[sigmasize-1-x][y];
		}

	}
	for (int x=halfsize; x<allsizex-sigmasize+halfsize+1; x++) {
		for(int y=0;y<halfsize+1;y++) {//work
			image[x][y] = image[x][sigmasize-1-y];
		}

	}
	for(int x = allsizex-halfsize;x<allsizex;x++){ // work
		for(int y=halfsize;y<allsizey-sigmasize+halfsize+1;y++){
			image[x][y] = image[allsizex-halfsize-x1][y];
		}
		x1++;
	}

	for(int x = halfsize;x<allsizex-sigmasize+halfsize+1;x++){
		y1=1;
		for(int y=allsizey-halfsize;y<allsizey+1;y++){
			image[x][y] = image[x][allsizey-halfsize-y1];
			y1++;
		}
	}


	for(int x=0; x<halfsize; x++) {
		for(int y=0; y<halfsize; y++) {
			image[x][y] = image[sigmasize-1-x][sigmasize-1-y];
		}
	}

	x1=1;

	for(int x=allsizex-halfsize;x<allsizex;x++) {
		y1=1;
		for(int y=allsizey-halfsize;y<allsizey;y++) {
			image[x][y] = image[allsizex-halfsize-x1][allsizey-halfsize-y1];
			y1++;
		}
		x1++;
	}

	for(int x=0; x<halfsize; x++) {
		y1=1;
		for(int y=allsizey-halfsize;y<allsizey;y++) {
			image[x][y] = image[sigmasize-1-x][allsizey-halfsize-y1];
			y1++;
		}
	}

	x1 = 1;

	for(int x=allsizex-halfsize;x<allsizex;x++) {
		for(int y=0; y<halfsize; y++) {
			image[x][y] = image[allsizex-halfsize-x1][sigmasize-1-y];
		}
		x1++;
	}


    //cout<<"Calculating"<<endl;

    calculate_picture(sigmasize, width, height, image, output, sigma);


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

	//cout<<"Create the ram"<<endl;
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


//cout<<"Calculating & out"<<endl;

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

void border_track (int** input, int** image, int height, int width){

	for (int x = 1; x<height-1; x++) {
		for (int y = 1; y<width-1; y++) {
			if (input[x][y] == 127) {
					if((input[x-1][y-1] == 255) || (input[x-1][y] == 255) || (input[x-1][y+1] == 255) || (input[x][y-1] == 255) || (input[x][y+1] == 255) || (input[x+1][y-1] == 255) || (input[x+1][y] == 255) || (input [x+1][y+1] == 255)) {
						image [x][y] = 255;
					}
					else {
						image [x][y] = 0;
					}
			}
			else {
				image[x][y] = input[x][y];
			}
		}
	}
}
