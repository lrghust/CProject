#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//媒体报道基本信息
typedef struct Report{
	char r_id[12];
	char r_date[10];
	char r_firm[20];
	char r_index[50];
	char r_field;
	Report *next;
}report;
//贪腐案件基本信息
typedef struct Cases{
	char c_prov[8];
	char c_id[12];
	char c_date[10];
	char c_name[15];
	char c_level;
	char c_charge;
	char c_money;
	int c_judge;
	Cases *next;
	Report *c_report;
}cases;
//所属省份监管信息
typedef struct Prov{
	char p_prov[8];
	char p_man[15];
	char p_tel[15];
	Prov *next;
	Cases *p_cases;
}prov;



//函数原型声明

//信息初始化函数
prov * init(void);

//信息录入函数：
//省份信息录入函数
void in_prov(prov *);
//案件信息录入函数
void in_cases(prov *);
//媒体信息录入函数
void in_report(prov *);

//信息修改函数：
//省份信息修改函数

int main(void)
{
	prov *head = init();
	return 0;
}

//信息初始化函数
prov * init(void)
{
	//初始化省份信息,要求每条信息顺序与结构成员顺序相同
	FILE *pf = fopen("fprov.txt", "r+");
	prov *phead = (prov *)malloc(sizeof(prov));
	prov *tail = phead;
	char temp[50];
	while (fscanf(pf, "%s", temp) != EOF)
	{
		tail->next = (prov *)malloc(sizeof(prov));
		tail = tail->next;
		strcpy(tail->p_prov, temp);
		fscanf(pf, "%s%s", tail->p_man, tail->p_tel);
		tail->p_cases = (cases *)malloc(sizeof(cases));
		tail->p_cases->next = NULL;
	}
	tail->next = NULL;
	fclose(pf);
	//初始化案件信息，要求每条信息顺序与结构成员顺序相同
	tail = phead;
	cases *tail1 = NULL;
	pf = fopen("fcases.txt", "r+");
	while (fscanf(pf, "%s", temp) != EOF)
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
			if (!strcmp(temp, tail->p_prov))
			{
				cases *tail1 = tail->p_cases;
				while (tail1->next != NULL)tail1 = tail1->next;
				tail1->next = (cases *)malloc(sizeof(cases));
				tail1 = tail1->next;
				strcpy(tail1->c_prov, temp);
				fscanf(pf, "%s%s%s%c%c%c%d", tail1->c_id, tail1->c_date, tail1->c_name, &tail1->c_level, &tail1->c_charge, &tail1->c_money, &tail1->c_judge);
				tail1->c_report = (report *)malloc(sizeof(report));
				tail1->c_report->next = NULL;
				tail = phead;
				break;
			}
		}
	}
	fclose(pf);
	//初始化媒体信息，要求每条信息顺序与结构成员顺序相同
	tail = phead;
	tail1 = NULL;
	pf = fopen("freport.txt", "r+");
	while (fscanf(pf,"%s", temp) != EOF)
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
			tail1 = tail->p_cases;
			while (tail1->next != NULL)
			{
				tail1 = tail1->next;
				if (!strcmp(tail1->c_id, temp))
				{
					break;
				}
			}
			report *tail2 = tail1->c_report;
			while (tail2->next != NULL)tail2 = tail2->next;
			tail2->next = (report *)malloc(sizeof(report));
			tail2 = tail2->next;
			strcpy(tail2->r_id, temp);
			fscanf(pf, "%s%s%s%c", tail2->r_date, tail2->r_firm, tail2->r_index, &tail2->r_field);
			tail2->next = NULL;
			tail = phead;
			break;
		}
	}
	fclose(pf);
	return phead;
}

//信息录入函数：
//省份信息录入函数
void in_prov(prov *head)
{
	prov *phead = head;
	while (phead->next != NULL)
		phead = phead->next;
	phead->next = (prov *)malloc(sizeof(prov));
	phead = phead->next;
	printf("province person_in_charge phone:");
	scanf("%s%s%s", phead->p_prov, phead->p_man, phead->p_tel);
	phead->p_cases = (cases *)malloc(sizeof(cases));
	phead->p_cases->next = NULL;
}

//案件信息录入函数
void in_cases(prov *head)
{
	char temp[50];
	printf("province id date name level charge money judgement:");
	scanf("%s", temp);
	prov *tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
		if (!strcmp(temp, tail->p_prov))
		{
			cases *tail1 = tail->p_cases;
			while (tail1->next != NULL)
				tail1 = tail1->next;
			tail1->next = (cases *)malloc(sizeof(cases));
			tail1 = tail1->next;
			strcpy(tail1->c_prov, temp);
			scanf("%s%s%s%c%c%c%d", tail1->c_id, tail1->c_date, tail1->c_name, &tail1->c_level, &tail1->c_charge, &tail1->c_money, &tail1->c_judge);
			tail1->c_report = (report *)malloc(sizeof(report));
			tail1->c_report->next = NULL;
			break;
		}
	}
}


//媒体信息录入函数
void in_report(prov *head)
{
	char temp[50];
	printf("id date firm index field:");
	scanf("%s", temp);
	prov *tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
		cases *tail1 = tail->p_cases;
		while (tail1->next != NULL)
		{
			tail1 = tail1->next;
			if (!strcmp(tail1->c_id, temp))
			{
				break;
			}
		}
		report *tail2 = tail1->c_report;
		while (tail2->next != NULL)tail2 = tail2->next;
		tail2->next = (report *)malloc(sizeof(report));
		tail2 = tail2->next;
		strcpy(tail2->r_id, temp);
		scanf("%s%s%s%c", tail2->r_date, tail2->r_firm, tail2->r_index, &tail2->r_field);
		tail2->next = NULL;
		tail = head;
		break;
	}
}
