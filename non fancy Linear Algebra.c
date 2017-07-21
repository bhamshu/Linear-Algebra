#include<stdio.h>
void multiplybyscalar(int n, float arr[][n], float m, float mrr[][n])
{	int i;
	for(i=0;i<n*n;i++)
	mrr[i/n][i%n]=m*arr[i/n][i%n];
}
void multiply(int a, int b, float arr[][b], int c, int d, float brr[][d], float product[a][d])/*If it would just let me to, I'd write int a, int b=a,. . . int c=a, int d=a*/
{
	if(b!=c)
	{printf("Multiplication not possible :(");return;}
	
	float sum(int i, int j)
	{	int I;float sum=0;
		for(I=0;I<b;I++)
		sum+=arr[i][I]*brr[I][j];
		return sum;
	}
	
	const int A=a, D=d;
	int i,j;
	for(i=0;i<a;i++)
	for(j=0;j<d;j++)
	product[i][j]=sum(i,j);
}
void show(int n, float arr[][n])
{	printf("\n");
	int i, j;
	for(i=0;i<n;i++)
	{for(j=0;j<n;j++)
    {if(arr[i][j]<0.0001 && arr[i][j]>-0.0001)printf("0.00 ");else printf("%.2f ", arr[i][j]);}
    printf("\n");} 
}
void minor(int n, float arr[][n], int I, int J, float Minor[][n-1])
{
	int address=0;
	int i, j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{if(i!=I&&j!=J){
	Minor[address/(n-1)][address%(n-1)]=arr[i][j];address++;}}
}
float determinant(int n, float arr[][n])
{
	int i, j;
	float det=0;
	float Minor[n-1][n-1];
	if (n==1)
	return arr[0][0];
	
	i=0;//Or for that matter any no. in [0,n-1]
	for(j=0;j<n;j++)
	{minor(n, arr, i, j, Minor);
	if((i+j)%2)
	det+=(-1)*arr[i][j]*determinant(n-1, Minor);
	else
	det+=arr[i][j]*determinant(n-1, Minor);
	}

	return det; 
}
void transpose(int n, float arr[][n], float trans[][n])
{
	int i, j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	trans[i][j] = arr[j][i];
}
void adjoint(int n, float arr[][n], float adj[][n])
{	if(n==1){adj[0][0]=1; return;}
	float temp[n][n], Minor[n-1][n-1];
	int i, j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{minor(n, arr, i, j, Minor);
	if((i+j)%2)
	temp[i][j]=-determinant(n-1,Minor);
	else
	temp[i][j]=determinant(n-1,Minor);}
	transpose(n, temp, adj);
}
void inverse(int n, float arr[][n], float inv[][n], float *det)
{
	float adj[n][n];
	adjoint(n, arr, adj);
	*det = determinant(n, arr);
	if((*det)!=0)
	multiplybyscalar(n, adj, 1/(*det), inv);	
}
main()
{	
	int i, j;
	int n;
	printf("Number of variables: ");
	scanf("%d",&n);
	float matrix[n][n+1], arr[n][n], val[n][1], sol[n][1];
	for(i=0;i<n;i++)
	{for(j=0;j<n+1;j++)
	{scanf("%f",&matrix[i][j]);
	if(j<n) arr[i][j] = matrix[i][j];
	else val[i][0] = matrix[i][n];}}
	float inv[n][n], det;
	inverse(n, arr, inv, &det);
	if(det!=0)
	multiply(n, n, inv, n, 1, val, sol);
	else 
	{printf("Multiple* solutions. . so unable to find any lol\n*or maybe none");
	return;}
	for(i=0;i<n;i++)
	printf("%0.2f ", sol[i][0]);
	getch();
}
