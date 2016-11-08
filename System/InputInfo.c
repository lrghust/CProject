#include"head.h"
/**
 * 函数名称: InputProvInfo
 * 函数功能: 录入省份信息.
 * 输入参数: head 主链表头结点指针；str 指向存储用户输入的信息
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void InputProvInfo(Province *head,char **str)
{
	Province *tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = (Province *)malloc(sizeof(Province));
	tail = tail->next;
	strcpy(tail->ProvProv,str[0]);
	strcpy(tail->ProvLeader,str[1]);
	strcpy(tail->ProvTel,str[2]);
	tail->ProvCase = (Case *)malloc(sizeof(Case));
	tail->ProvCase->next = NULL;
	tail->next=NULL;
}

/**
 * 函数名称: InputCaseInfo
 * 函数功能: 录入案件信息.
 * 输入参数: head 主链表头结点指针；str 指向存储用户输入的信息
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void InputCaseInfo(Province *head,char **str)
{
	Province *tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
		if (!strcmp(str[2], tail->ProvProv))
		{
			Case *tail1 = tail->ProvCase;
			while (tail1->next != NULL)
				tail1 = tail1->next;
			tail1->next = (Case *)malloc(sizeof(Case));
			tail1 = tail1->next;
			strcpy(tail1->CaseId, str[0]);
			strcpy(tail1->CaseDate, str[1]);
			strcpy(tail1->CaseProv, str[2]);
			strcpy(tail1->CaseName, str[3]);
			tail1->CaseLevel=*str[4];
			tail1->CaseCharge=*str[5];
			tail1->CaseMoney=atof(str[6]);
			tail1->CaseJudge=*str[7];
			tail1->CaseRepo = (Report *)malloc(sizeof(Report));
			tail1->CaseRepo->next = NULL;
			tail1->next=NULL;
			break;
		}
	}
}

/**
 * 函数名称: InputRepoInfo
 * 函数功能: 录入媒体信息.
 * 输入参数: head 主链表头结点指针；str 指向存储用户输入的信息
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void InputRepoInfo(Province *head,char **str)
{
	Province *tail = head;
	int flag=0;
	while (tail->next != NULL)
	{
		tail = tail->next;
		Case *tail1 = tail->ProvCase;
		while (tail1->next != NULL)
		{
			tail1 = tail1->next;
			if (!strcmp(tail1->CaseId, str[0]))
			{
			    flag=1;
			    Report *tail2 = tail1->CaseRepo;
                while (tail2->next != NULL)
                    tail2 = tail2->next;
                tail2->next = (Report *)malloc(sizeof(Report));
                tail2 = tail2->next;
                strcpy(tail2->RepoCaseId, str[0]);
                strcpy(tail2->RepoId, str[1]);
                strcpy(tail2->RepoDate, str[2]);
                tail2->RepoField=*str[3];
                strcpy(tail2->RepoFirm, str[4]);
                strcpy(tail2->RepoIndex, str[5]);
                tail2->next = NULL;
                tail = head;
				break;
			}
		}
		if(flag)
            break;
	}
}
