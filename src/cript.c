#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IJ(a) ('a' + a > 'h'?'b':'a')	// Enables skipping the char 'i'

char keymat[5][5], text[1 << 16];

void genKey(char *keyword){ 
	int i, j,k, exists;
	
	for(i=k=0; i < strlen(keyword); i++){
		keyword[i]= (keyword[i] == 'i'?'j':keyword[i] ); // Turns 'i' into 'j' in the keyword
		exists=0;
		for(j=k-1; j >= 0; j--)	// Checks doubled chars
			if( keymat[j/5][j%5] == keyword[i] ){ 
				exists=1;
				break;
			}
		if(!exists){
			keymat[k/5][k%5] = keyword[i];
			k++;
		}
	}
	for(i=0; i < 25; i++){ // Fills the remaining cells of the matrix
		exists=0;
		for(j=k-1; j >= 0; j--)
			if( keymat[j/5][j%5] == IJ(i)+i ){
				exists=1;
				break;
			}
		if(!exists){
			keymat[k/5][k%5] = IJ(i) + i;
			k++;
		}
	}
	/*for(i=0; i < 5; i++){
		for(j=0; j < 5; j++)
			fprintf(stderr,"%c ",keymat[i][j]);
		fprintf(stderr,"\n");
	}*/
}

void read(){
	int i=0;
	char a;

	while(scanf("%c", &a) == 1 && a != EOF){
		if( (a < 'a' || a > 'z') && (a < 'A' || a > 'Z'))
			continue;
		a = tolower(a);		// Forces lowercase
		a = (a == 'i'?'j': a);	// Turns 'i' into 'j'
		if(i > 0 && text[i-1] == a){
			fprintf(stderr,"x");
			text[i++]='x';  // Insert filling character 'x'
		}	
		fprintf(stderr,"%c",a);
		text[i++] = tolower(a);
	}
	if(strlen(text) % 2){		// If odd number of chars, insert trailing 'x'
		text[i]='x';
		fprintf(stderr,"x");
	}
}

void write(){
	int i, j, k;

	for(k =0 ; k < strlen(text); k+=2){
		for(j=0; j < 25 ; j++)
			if(keymat[j/5][j%5] == text[k] )
				break;
		for(i=0; i < 25 ; i++)
			if(keymat[i/5][i%5] == text[k+1] )
				break;
		if(j%5 == i%5)		// If same column, shifts down
			printf("%c%c",keymat[(j/5 + 1)%5][j%5], keymat[(i/5 + 1)%5][i%5]);
		else if(i/5 == j/5)	// If same row, shifts right
			printf("%c%c",keymat[j/5][(j+1)%5], keymat[i/5][(i+1)%5]);
		else
			printf("%c%c",keymat[j/5][i%5], keymat[i/5][j%5]);
	}
}

int main(int argc, char *argv[]){
	if(argc !=2 ){
		fprintf(stderr,"Modo de uso:\n\t$ ./cript chave\n");
		return 1;
	}
	memset(text, '\0', sizeof(text));
	genKey(argv[1]);
	read();
	write();
	return 0;
}
