#include <stdio.h>
int main(){
	int x =0x01234567;
	unsigned char *p = (unsigned char *)&x;
	for(int i = 0;i < sizeof(int); i++)
		printf("%.2x ",p[i]);
	printf("\n如果最前面是 67 ->小端\n");
	return 0;
}
