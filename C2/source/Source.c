#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct clientdata
{
	int acctnum;
	char lastname[15];
	char firstname[10];
	double balance;
};

int main()
{
	FILE *pread, *pwrite, *cfptr;
	int cnt = 0;
	struct clientdata client = { 0,"","",0.0 };
	pread = fopen("D://credit.txt", "r");
	if (NULL == pread)
	{
		return 0;
	}
	pwrite = fopen("D://output.txt", "wb");
	if (NULL == pwrite)
	{
		fclose(pread);
		return 0;
	}
	while (!feof(pread))
	{
		fscanf(pread, "%d", &client.acctnum);
		fscanf(pread, "%s", client.lastname,15);
		fscanf(pread, "%s", client.firstname,11);
		fscanf(pread, "%lf", &client.balance);
		fwrite(&client, sizeof(struct clientdata), 1, pwrite);
		printf("%-6d%-16s%-11s%10.2f\n", client.acctnum, client.lastname, client.firstname, client.balance);

	}
	fclose(pread);
	fclose(pwrite);
	printf("以讀取文字檔的ASCLL資料，並轉存成二進位資料檔案\n\n");
	system("pause");
	printf("\n讀取二進位資料檔案，並格式化輸出如下：\n");
	if ((cfptr = fopen("D://output.txt", "rb")) == NULL)
	{
		printf("File could not be opened.\n");
	}
	else
	{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name","Firstname", "Balance");
		cnt = fread(&client, sizeof(struct clientdata), 1, cfptr);
		while (cnt > 0)
		{
			printf("%-6d", client.acctnum);
			printf("%-16s", client.lastname,7);
			printf("%-11s", client.firstname,7);
			printf("%10.2f\n", client.balance);
			cnt = fread(&client, sizeof(struct clientdata), 1, cfptr);
		}
		fclose(cfptr);
	}
	system("pause");
}