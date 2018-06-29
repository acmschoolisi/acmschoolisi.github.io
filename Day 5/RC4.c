

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 256
#define klen 16

int main() {
       
       
	   unsigned int i,j,i1,j1,s[N],k[N], key[klen], ktemp, temp,sum=0, z;
	                          
        srand(time(NULL));
   

    for(j1=0; j1<1;j1++){
        
        
         for(i1 = 0; i1 < klen; i1++){
				ktemp = (((double) N)*rand()/(RAND_MAX+1.0));
				key[i1] = ktemp;
                                    }
		
		   
                  

		for (i1 = 0; i1 < N; i1++)
                           {
			   k[i1] = key[i1%klen ];
                           }
                
                        
			

			for (i1 = 0; i1 < N; i1++)
				s[i1] =  i1;
		
			j = 0;	
		        for (i1 = 0; i1 < N; i1++) {
                               j = (j + s[i1] + k[i1])%N;
                               
                                   
                               
                         	   temp = s[i1];
				   s[i1] = s[j];
				   s[j] = temp;
                                             }

                     
                      
                      j=0;
                      i=0;

 
                      for(i1=0;i1<3;i1++){
                                         i=i+1;
                                         j=(j+s[i])%N;
                                         temp = s[i];
				         s[i] = s[j];
				         s[j] = temp;
                                          
                                         temp=(s[i]+s[j])%N;
                                         z=s[temp];
                                         printf("%u\n", z);

                                         }
                                         if(z==0)
                                              sum++;
                                            
                                  } 


printf("%lf   %lf\n", (double)sum/j1, 1.0/256);                         	
}
