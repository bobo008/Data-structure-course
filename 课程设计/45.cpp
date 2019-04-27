#include<math.h>
#include<stdio.h>
int main()
{
	int i,m,n;
	char a;
	m=0;
	n=0;
	printf("请输入五进制");
	for(i=0;;i++)
	{
		scanf("%c",&a);

	if(a==' ')
    break;
	else 
	{
    m=m+(a-'0')*pow(5,i);
	n=n+(a-'0')*pow(10,i);
  }
}
printf("%d %d",m,n);
	return 0;
 } 

