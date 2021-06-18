
//Yigit Kaleli 2152007
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int roww;
int colm;
int m;
int in_row=0,in_colmn=0;
int d,s;

int **arr;
pthread_mutex_t mutex;

//Shifting left to right(circular)
void* shift_left_to_right(){
	int column,temp,z;
	for(in_row; in_row<m; in_row++){
		pthread_mutex_lock(&mutex);
		for(z=0;z<s;z++){ 		 //To able to make it entered number of shifts
			temp = arr[in_row][m-1];
			for (column=m-1; column>=0; column--){

				arr[in_row][column] = arr[in_row][column-1];

			}
			arr[in_row][0] = temp;
		}
		if(in_row == (m/d)-1){ //Checking where should thread go (when it reach its last point it unlocks the thread)
			in_row++;
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}	
	
}

//Shifting bottom to top(circular)
void* shift_bottom_to_top() {
	int rowww,temp,z;
	for (in_colmn; in_colmn < m; in_colmn++){
		pthread_mutex_lock(&mutex);
		for(z=0;z<s;z++){               //To able to make it entered number of shifts 
			temp = arr[0][in_colmn];
			for (rowww = 1; rowww < m; rowww++){
				arr[rowww-1][in_colmn] = arr[rowww][in_colmn];
			}
			arr[m-1][in_colmn] = temp;
		}
		if (in_colmn == (m/d) - 1){ //Checking where should thread go (when it reach its last point it unlocks the thread)
			in_colmn++;
			pthread_mutex_unlock(&mutex);
			
			break;
		}
		pthread_mutex_unlock(&mutex); 
	}	
}




//Creating map function
void createMAP(void){
	FILE *fp = fopen("map.txt", "r");
	int i,j,number;
	for(i=0; i < roww; i++){
    		for(j=0; j < colm; j++){
        	fscanf(fp,"%d",&number);
        	arr[i][j] = number;
    		}
	}
	fclose(fp);
}

//Printing map function
void showMAP(void){
	int i,j;
	for(i=0; i < 4; i++){
    		for(j=0; j < 4; j++)
        	printf("%d ", arr[i][j]);
        	printf("\n");
    	}
}



int main()
{
    FILE *fp = fopen("map.txt", "r");
    int number;
    char c;
    int temp, col = 0, row =0;
    int i,j;

//CHECK TXT ARRAY DIMENTIONS
    do {  
    c = getc (fp);
    if((temp != 2) && (c == ' ' || c == '\n'))
        col++;
    if(c == '\n'){
        temp =2;
        row++;
    }
} while (c != EOF);
fclose(fp);

arr = (int **)malloc(row * sizeof(int *));
    for (i=0; i<row; i++){
         arr[i] = (int *)malloc(col * sizeof(int));
         }

roww=row; //INITIALIZING GLOBAL VARIABLES
colm=col;
createMAP();

printf("ENTERED(INITIAL) MAP\n");
showMAP();


 
 
 // INITIALIZIN ACCORDING TO ROWS AND COLMNS

m=row;    //Dimension initialized

printf("Please enter 'd'(number of threads)<=%d::",m);
scanf("%d",&d);
while (d>m){
	printf("Please ender 'd' value less than or equal to %d::",m);
	scanf("%d",&d);
}


printf("Please enter 's'(shifts)::");
scanf("%d",&s);




//THREADING
pthread_t th[d];
pthread_mutex_init(&mutex,NULL);

for(i = 0; i<d; i++){ 					//First doing rows in prallel creating Threads to compute them prallel
	if(pthread_create(&th[i],NULL,&shift_left_to_right,NULL) !=0 ){

	}
	printf("Thread %d has started \n",i);	
}

for(i = 0; i<d; i++){ //Then finishing Threads
	if(pthread_join(th[i],NULL)!=0){

	}
	printf("Thread %d has finished \n",i);
}



printf("\nENTERED(AFTER JUST ROW) MAP\n");
showMAP();

//Waiting until the obove threads finish.

for(i = 0; i<d; i++){ 					//THEN doing columns in parallel 
	if(pthread_create(&th[i],NULL,&shift_bottom_to_top,NULL) !=0 ){

	}
}

for(i = 0; i<d; i++){ //Then finishing Threads
	if(pthread_join(th[i],NULL)!=0){

	}
}

pthread_mutex_destroy(&mutex);



printf("\nENTERED(AFTER COLUMN) MAP\n");
showMAP();

return 0;

 }
