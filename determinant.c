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
{
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
void inverse(int n, float arr[][n], float inv[][n]) //Added later. Was made specially for the "non fancy linear algebra"
{
	float adj[n][n];
	adjoint(n, arr, adj);
	float det = determinant(n, arr);
	if(det!=0)
	multiplybyscalar(n, adj, 1/det, inv);	
}
main()
{
	int AA;
	printf("Enter length of the square matrix ");
	scanf("%d", &AA);
	const int n = AA;
	float arr[n][n], adj[n][n], inv[n][n], product[n][n];
	int i, j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	scanf("%f",&arr[i][j]);
	float det = determinant(n, arr);
	printf("\nDeterminant = %.2f", det);
	adjoint(n, arr, adj);
	printf("\n\nThe adjoint is:");
	show(n, adj);
	if(det==0)
	{printf("\nInverse doesn't exist\n");return;}
	
	printf("\nThe Inverse is:");
	multiplybyscalar(n, adj, 1/det, inv);
	show(n, inv);

	multiply(n, n, arr, n, n, inv, product);
	printf("\nThe product A*inverseA is:");
	show(n, product);
	printf("\nThis above matrix is supposed to be an identity matrix\n");
}
