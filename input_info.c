#include"head.h"
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