#include"head.h"
//信息初始化函数
Province * InitInfo(void)
{
	//初始化省份信息,要求每条信息顺序与结构成员顺序相同
	FILE *pf = fopen("fprov.txt", "r+");
	Province *phead = (Province *)malloc(sizeof(Province));
	Province *tail = phead;
	char temp[50];
	while (fscanf(pf, "%s", temp) != EOF)
	{
		tail->next = (Province *)malloc(sizeof(Province));
		tail = tail->next;
		strcpy(tail->ProvProv, temp);
		fscanf(pf, "%s%s", tail->ProvLeader, tail->ProvTel);
		tail->ProvCase = (Case *)malloc(sizeof(Case));
		tail->ProvCase->next = NULL;
	}
	tail->next = NULL;
	fclose(pf);
	//初始化案件信息，要求每条信息顺序与结构成员顺序相同
	tail = phead;
	Case *tail1 = NULL;
	pf = fopen("fcases.txt", "r+");
	while (fscanf(pf, "%s", temp) != EOF)
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
			if (!strcmp(temp, tail->ProvProv))
			{
				Case *tail1 = tail->ProvCase;
				while (tail1->next != NULL)tail1 = tail1->next;
				tail1->next = (Case *)malloc(sizeof(Case));
				tail1 = tail1->next;
				strcpy(tail1->CaseProv, temp);
				fscanf(pf, "%s%s%s%c%c%c%d", tail1->CaseId, tail1->CaseDate, tail1->CaseName, &tail1->CaseLevel, &tail1->CaseCharge, &tail1->CaseMoney, &tail1->CaseJudge);
				tail1->CaseReport = (Report *)malloc(sizeof(Report));
				tail1->CaseReport->next = NULL;
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
			tail1 = tail->ProvCase;
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
			strcpy(tail2->r_id, temp);
			fscanf(pf, "%s%s%s%c", tail2->ReportDate, tail2->ReportFirm, tail2->ReportIndex, &tail2->ReportField);
			tail2->next = NULL;
			tail = phead;
			break;
		}
	}
	fclose(pf);
	return phead;
}