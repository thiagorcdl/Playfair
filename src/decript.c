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
		a = tolower(a);			// Forces lowercase
		text[i++] = (a == 'i'?'j': a);	// Turns 'i' into 'j'
	}
	//fprintf(stderr,"%s\n\n",text);
}

void rmChar(){		// Removes filling character 'x'
	int i, j;
	
	for(i=1; i < strlen(text)-1; i++){
		if(text[i] == 'x' && text[i-1] == text[i+1]){
			for(j=i; j <= strlen(text); j++)
				text[j]=text[j+1];
		}
	}
}

void write(){		// Prints the resulting text
	int i, j, k;

	for(k =0 ; k < strlen(text); k+=2){	
		for(j=0; j < 25 ; j++)
			if(keymat[j/5][j%5] == text[k] )
				break;
		for(i=0; i < 25 ; i++)
			if(keymat[i/5][i%5] == text[k+1] )
				break;
		if(j%5 == i%5){		// If same column, shifts up
			text[k] = keymat[(j/5 +4)%5][j%5];
			text[k+1] = keymat[(i/5 +4)%5][i%5];
		} else if(i/5 == j/5){	// If same row, shifts left
			text[k] = keymat[j/5][(j+4)%5];
			text[k+1] = keymat[i/5][(i+4)%5];
		} else {
			text[k] = keymat[j/5][i%5];
			text[k+1] = keymat[i/5][j%5];
		}
	}
	//rmChar();
	printf("%s",text);
}

int main(int argc, char *argv[]){
	if(argc !=2){
		fprintf(stderr,"Modo de uso:\n\t$ ./decript chave [< n.in]\n");
		return 1;
	}
	memset(text, '\0', sizeof(text));
	genKey(argv[1]);
	read();
	write();
	return 0;
}
