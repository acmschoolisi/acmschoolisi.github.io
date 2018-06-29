
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ul unsigned int
#define ull unsigned long long 

#define rotateleft(x, n) (((x) << (n)) ^ ((x) >> (32-n)))
#define update(a, b, c, n) ((a)^(rotateleft(((b)+(c)),(n))))
#define myrand32 ((ul) (4294967296.0*drand48()))

#define LOOP ((1024*1024*1024ULL)*1024ULL)
#define BIASMAXLIMIT 0.51
#define BIASMINLIMIT 0.49

void initializeR(ul *x){
	int i;
	for (i = 0; i < 16; i++)
		x[i] = myrand32;

	x[0] = 0x61707865;
	x[5] = 0x3320646e;
	x[10] = 0x79622d32;
	x[15] = 0x6b206574;
}

void copystate(ul *x1, ul *x){
	int i;
	for (i = 0; i < 16; i++)
		x1[i] = x[i];
}

void print(ul *x){
	int i;
	for (i = 0; i < 16; i++){
		printf("%8x ", x[i]);
		if (i > 0 && i%4 == 3)
			printf("\n");
	}
	printf("\n");
}

void qr(ul *x0, ul *x1, ul *x2, ul *x3){
	
	ul z0, z1, z2, z3;

	z1 = update(*x1, *x3, *x0, 7);
	z2 = update(*x2, *x0, z1, 9);
	z3 = update(*x3, z1, z2, 13);
	z0 = update(*x0, z2, z3, 18);

	*x0 = z0; *x1 = z1, *x2 = z2, *x3 = z3;
}

void transpose(ul *x){
  	ul temp;
  	temp=x[1]; x[1]=x[4]; x[4]=temp;
  	temp=x[2]; x[2]=x[8]; x[8]=temp;
  	temp=x[3]; x[3]=x[12]; x[12]=temp;
  	temp=x[6]; x[6]=x[9]; x[9]=temp;
  	temp=x[7]; x[7]=x[13]; x[13]=temp;
  	temp=x[11]; x[11]=x[14]; x[14]=temp;
}

void rounds(ul *x){

	qr(&(x[0]), &(x[4]), &(x[8]), &(x[12]));
	qr(&(x[5]), &(x[9]), &(x[13]), &(x[1]));
	qr(&(x[10]), &(x[14]), &(x[2]), &(x[6]));
	qr(&(x[15]), &(x[3]), &(x[7]), &(x[11]));
	transpose(x);
}

int main(){
	ul x[16], x1[16], pattern, pt;
	int i, j, k, kmin, jmin, kmax, jmax, cntm, cntp, round; 
	ull loop = 0;
	double cnt=0;
	
	srand48(time(NULL));
	pt = 0x80000000;
	
	while (loop < LOOP){
	
		initializeR(x);	copystate(x1, x);
		x1[7] = x[7] ^ pt;
		for (i = 0; i < 4; i++){ rounds(x); rounds(x1); }

			pattern = 0x00000001<<14;
				if (((x[1] ^ x1[1]) & pattern) == 0) cnt = cnt+ 1.0;
				
		loop++;
		if (loop > 0 && loop%(1024*1024) == 0)
			
			printf(" %llu   %0.10f\n",  loop/(1024*1024), cnt/loop);
			
			
	}
}
