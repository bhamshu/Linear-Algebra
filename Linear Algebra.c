#define MaxVar 9
#include<stdio.h>
#include<math.h>
#include"shubham.c"
struct term{
float coeff;
char var;
};
struct expression{
	struct term t[MaxVar+1];
};
void operate(struct expression *, char *, int);
int check(char *);
void help();
void main(){
	 int x; int i, j;
	 printf("The program solves linear equations in   variables ");gotoxy(39,0);scanf("%d",&x);
	 if(x>MaxVar) {printf("Currently we solve only upto %d variable equations. See you later!",MaxVar);getch();return;}
     struct expression exp[x];
     for(i=0;i<x;i++) for(j=0;j<x+1;j++){
     	exp[i].t[j].coeff=0;
     	exp[i].t[j].var=' ';
	 }
	 char e[80];
     for(i=0;i<x;i++){
         l: printf("Please enter the equation number %d \n",i+1);
  		 do{ fflush(stdin);gets(e); }while(e[0]=='\0');
		 if(!strcmp(e,"help")||!strcmp(e,"docs")) { help(); i=0; goto l;} 
		 if(!check(e)) {printf("Something's not right. Try some other representation or type 'help'(w/o quotes)\n"); goto l;}
 	     printf("\n");
		 operate(&exp[i], e, x);
 	     printf("The equation was interpreted as:\n");                          //                     |                          NOTICE these zeroes  |  . It is deliberate
	     for(j=0;j<x+1;j++){if(exp[i].t[j].coeff>=0&&j!=0)printf("+");printf("%0.2f", exp[i].t[j].coeff);if(exp[0].t[j].var!=' ') {printf("*");printf("%c", exp[0].t[j].var);}}printf("=0\n");
		 if(i!=x-1) printf("If this is not what you intended, please type 'help'(w/o quotes) in the next expression bar\n\n");
	 }   
	float arr[x][x], val[x][1], sol[x][1];
    for(i=0;i<x;i++)
	{for(j=0;j<x+1;j++)
	{
	if(j<x) arr[i][j] = exp[i].t[j].coeff;
	else val[i][0] = -exp[i].t[j].coeff;}}
	float inv[x][x], det;
	inverse(x, arr, inv, &det);
	if(det!=0)
	multiply(x, x, inv, x, 1, val, sol);
	else 
	{printf("Multiple* solutions. . so unable to find any lol\n*or maybe none");
	return;}
	printf("\n");
	for(i=0;i<x;i++)
	printf("%c=%0.2f   ",exp[0].t[i].var, sol[i][0]);	 
	getch(); 
}
void operate(struct expression *exp, char *e, int x){
	int p=-2; int i; 
	int rhs=0;
	if(e[0]=='-'||e[0]=='+') p=-1;
	for(i=0;i<x+1;i++){
		p=p+2;
		if(e[p-1]=='=') rhs=1;
		if(e[p-1]=='=' && ( e[p]=='+' || e[p]=='-' ) ) p++;
		int P=p;
		while('0'<=e[p]&&e[p]<='9'){
			(*exp).t[i].coeff*=10;
			(*exp).t[i].coeff+=e[p]-'0';
			p++;	
		}
		if(e[p]=='.'){
			int n=1; p++;
			while('0'<=e[p]&&e[p]<='9'){
				(*exp).t[i].coeff+=(e[p]-'0')/pow(10,n++);
				p++;
			}
		}
		if(e[p]!=0)(*exp).t[i].var = e[p];
		if(p==P){   (*exp).t[i].coeff=1;}
        if(e[P-1]=='-') (*exp).t[i].coeff*=-1;
    	if(rhs==1) (*exp).t[i].coeff*=-1;
	}
}
int check( char *e){
	omit(e," ");
	int i;
	for(i=0;i<strlen(e);i++){
		if( !(e[i]>='A'&&e[i]<='Z') && !(e[i]>='a'&&e[i]<='z') && !(e[i]>='0'&&e[i]<='9') && e[i]!='+' && e[i]!='-' && e[i]!='=' && e[i]!='*' && e[i]!='.')
		{if(e[i]=='^') printf("It's a \"Linear\" algebra program\n"); return 0;}
	}
	if(omit(e, "**")==1 || omit(e, "^")==1){ printf("It's a \"Linear\" algebra program\n");return 0;}
	omit(e, "*");
	return 1;
}
void help(){
	printf("Hello! I take it as my shortcoming that you ever had to come here :(\n");
	printf("Nevertheless, now that you are here, I assume that you typed something that was not accepted or wrongly interpreted\n");
	printf("So from here, you have these options: \n");
	printf("1. Type the equations the way I expect them to be. I expect that:\n");
	printf("\ta) You type them in most natural way like you do when you write with hand\n");
	printf("\t   What is more natural: -x+32y=1 or -x+32y-1=0 \n");
	printf("\t           and           -x+32y=1 or -1*x+32*y=1 \n");
	printf("\tSPOILER: The answer is the first one in both rows\n");
	printf("\tb) You are mentally fit\n");
	printf("\t   Is it too much to ask? The title says \"Linear Algebra\" loud and clear.Yet if you are like me, you'd be \n");
	printf("\t   surprised to see how many people pester my precious little code with '^'s and '**'s'\n");
	printf("\t   Please don't do that.\n");
	printf("*Exceptions:\nAs with every statement and every discipline(\"except\" perhaps mathematics), the current version of this program has\n");
	printf("excptions regarding the 'natural' way. \nIn a three variable system, if say the coefficient of y is zero you may want to write x+3z=4 rather than x+0y+3z=4\n");
	printf("but you shall have to write the latter one. On similar lines, flexiblity in order of variable has not yet been achieved\n");
	printf("\n2. Leave feedback\n");
	printf("\tI don't know if it makes you happy or sad hopefully not angry, but as you have been reading \n\ttill now you deserve to know that your inputs are already under surveillance");
	printf("Still, you may\n\ttype 'feedback' to leave feedback.\n");
	printf("\n3. Wolfram\n\tIn case you have given up hopes on me, methods better than mine already exist.\n\n");	
}
