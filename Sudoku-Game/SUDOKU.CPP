#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
int a[9][9],b[9][9],r[60][2];
int row, col, icount, mode;
char solh;
void main()
{
void readvalues(void), display(void),generate(void);
int solve(),checkmat()
, checkrow()
 checkcolumn()
check()
isfixed();
int i,j,error;
char c;
	generate();
	for(i=0;i<9;i++)
	for(j=0;j<9;j++)
	a[i][j]=b[i][j];
}
/*FUNCTION TO CHECK CONSISTENCY OF AN ELEMENT*/
solve()
{
int i,m=0,n=0,number,c,fixed;
mainallot:
for(m=row;m<9;m++)
	{
	n=col;
	while(n<9)
		{
		number=1;
		fixed=isfixed(icount,m,n);
		if(fixed==0)
			{
			allot:
			a[m][n]=number;
			c=check(m,n);
			if(c==0)
				{
				number++;
				if(number>9)
					{
					a[m][n]=0;
					if(n==0)
						{
						row=m-1; col=8;
						if(row<0)
						return(0);
						goto backadjust;
						}
					else
						{
						row=m; col=n-1;
						if(row<0 || col<0)
						return(0);
						goto backadjust;
						}
					}
				goto allot;
				}
			}
		n++;
		if(n>8)
		col=0;
		}
	}
return(1);

backadjust:

fixed=isfixed(icount,row,col);
if(fixed==0)
	{
	number=a[row][col];
	allot1:
	number++;
	a[row][col]=number;
	if(number>9)
		{
		a[row][col]=0;
		if(col==0)
			{
			row--; col=8;
			if(row<0)
			return(0);
			goto backadjust;
			}
		else
			{
			col--;
			if(col<0)
			return(0);
			goto backadjust;
			}
		}
	c=check(row,col);
	if(c==0)
	goto allot1;
	else
		{
		if(col==8)
			{
			row++;
			if(row>8)
			return(0);
			col=0;
			goto mainallot;
			}
		else
			{
			col++;
			if(col>8)
			return(0);
			goto mainallot;
			}
		}
	}
else
	{
	if(col==0)
		{
		row--; col=8;
		if(row<0)
		return(0);
		goto backadjust;
		}
	else
		{
		col--;
		if(col<0)
		return(0);
		goto backadjust;
		}
	}
}

/*FUNCTION TO GENERATE SODOKU*/

void generate(int choice)
{
int c,i,m,n,count=1,fixed,error;
generate:
for(m=0;m<9;m++)
for(n=0;n<9;n++)
a[m][n]=0;
for(i=0;i<60;i++)
	{
	r[i][0]=20; r[i][1]=20;
	}
switch(choice)
	{
	case '1': mode=34+random(4);
		  break;
	case '2': mode=29+random(4);
		  break;
	case '3': mode=27+random(2);
		  break;
	case '4': mode=25+random(2);
		  break;
	default : mode=27+random(2);
		  break;

	}
a[0][0]=1+random(8); r[0][0]=0; r[0][1]=0;
for(count=1;count<10;count++)
	{
	choose:
	m=random(9); n=random(9);
	fixed=isfixed(icount,m,n);
	if(fixed==1)
	goto choose;
	r[count][0]=m; r[count][1]=n;
	allot:
	a[m][n]=1+random(9);
	if(a[m][n]==0)
	goto allot;
	c=check(m,n);
	if(c==0)
	goto allot;
	}
icount=count;
error=solve();
for(m=0;m<9;m++)
for(n=0;n<9;n++)
b[m][n]=a[m][n];
row=0; col=0;
for(i=0;i<60;i++)
	{
	r[i][0]=20; r[i][1]=20;
	}
if(error==0)
goto generate;
for(count=0;count<mode/2;count++)
	{
	choose2:
	m=random(9); n=random(5);
	fixed=isfixed(count,m,n);
	if(fixed==1)
	goto choose2;
	r[count][0]=m; r[count][1]=n;
	r[count+mode/2][0]=8-m;
	r[count+mode/2][1]=8-n;
	}
for(m=0;m<9;m++)
for(n=0;n<9;n++)
	{
	fixed=isfixed(mode,m,n);
	if(fixed!=1)
	a[m][n]=0;
	}
icount=mode;
}

