#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct myGrade {
	char *name;
	int korean;
	int english;
	int math;
};

int main(int argc, char *argv[]) {
	/*
	struct myGrade myClass[20];
	myClass[0].name = "����";
	myClass[1].name	= "���뿵";
	myClass[0].korean = 100;
	myClass[1].math = 84;
	
	printf("%s�� ���� ������ %d\n", myClass[0].name, myClass[0].korean);
	printf("%s�� ���� ������ %d\n", myClass[1].name, myClass[1].math);
	*/
	/*
	FILE *fp = NULL;
	fp = fopen("charsample.txt", "w");
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 1;
	}
	fputc('l', fp);
	fputc('o', fp);
	fputc('v', fp);
	fputc('e', fp);
	fclose(fp);
	*/
	/*
	FILE *fp = NULL;
	int a;
	fp = fopen("charsample.txt", "r");
	if (fp == NULL)
	{
		printf("���� ���� ����");
		return 1;
	}
	while ((a = fgetc(fp))!= EOF) putchar(a);
	fclose(fp);
	*/
	/*
	FILE *fp;
	int age = 18;
	char name[10] = "ȫ�浿";
	fp = fopen("formsample.txt", "w");
	if (fp == NULL)
	{
		printf("���� ���� ����");
		return 1;
	}
	fprintf(fp, "%d %s \n", age, name);
	fclose(fp);
	*/
	FILE *fp;
	int age;
	char name[10];
	fp = fopen("formsample.txt", "r");
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 1;
	}
	fscanf(fp, "%d %s \n", &age, name);
	printf("%d %s", age, name);
	fclose(fp);
	
	printf("\n210508 ���� 1-8 12�� Ȳ�ο�");
	return 0;
} 
