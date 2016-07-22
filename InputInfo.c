#include"head.h"
//信息录入函数：
//省份信息录入函数
void InputProvInfo(Province *head)
{
	Province *phead = head;
	while (phead->next != NULL)
		phead = phead->next;
	phead->next = (Province *)malloc(sizeof(Province));
	phead = phead->next;
	printf("province person_in_charge phone:");
	scanf("%s%s%s", phead->ProvProv, phead->ProvLeader, phead->ProvTel);
	phead->ProvCase = (Case *)malloc(sizeof(Case));
	phead->ProvCase->next = NULL;
}

//案件信息录入函数
void InputCaseInfo(Province *head)
{
	char temp[50];
	printf("province id date name level charge money judgement:");
	scanf("%s", temp);
	Province *tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
		if (!strcmp(temp, tail->ProvProv))
		{
			Case *tail1 = tail->ProvCase;
			while (tail1->next != NULL)
				tail1 = tail1->next;
			tail1->next = (Case *)malloc(sizeof(Case));
			tail1 = tail1->next;
			strcpy(tail1->CaseProv, temp);
			scanf("%s%s%s%c%c%c%d", tail1->CaseId, tail1->CaseDate, tail1->CaseName, &tail1->CaseLevel, &tail1->CaseCharge, &tail1->CaseMoney, &tail1->CaseJudge);
			tail1->CaseReport = (Report *)malloc(sizeof(Report));
			tail1->CaseReport->next = NULL;
			break;
		}
	}
}


//媒体信息录入函数
void InputReportInfo(Province *head)
{
	char temp[50];
	printf("id date firm index field:");
	scanf("%s", temp);
	Province *tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
		Case *tail1 = tail->ProvCase;
		while (tail1->next != NULL)
		{
			tail1 = tail1->next;
			if (!strcmp(tail1->CaseId, temp))
			{
				break;
			}
		}
		Report *tail2 = tail1->CaseReport;
		while (tail2->next != NULL)tail2 = tail2->next;
		tail2->next = (Report *)malloc(sizeof(Report));
		tail2 = tail2->next;
		strcpy(tail2->ReportId, temp);
		scanf("%s%s%s%c", tail2->ReportDate, tail2->ReportFirm, tail2->ReportIndex, &tail2->ReportField);
		tail2->next = NULL;
		tail = head;
		break;
	}
}