#include"head.h"
/**
 * 函数名称: DeleteProvInfo
 * 函数功能: 删除省份信息.
 * 输入参数: head 链表头结点指针；str 用户输入的省份名称
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明: 原省份下的案件及媒体信息将丢失
 */
void DeleteProvInfo(Province *head,char *str)
{
	Province *tail=head;
	Province *tailold=head;
	while(tail->next!=NULL)
	{
		tailold=tail;
		tail=tail->next;
		if(!strcmp(tail->ProvProv,str))
		{
			tailold->next=tail->next;
			tail->next=NULL;
			break;
		}
	}
}
/**
 * 函数名称: DeleteCaseInfo
 * 函数功能: 删除案件信息.
 * 输入参数: head 链表头结点指针；str 用户输入的案件编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明: 原省份下的媒体信息将丢失
 */
void DeleteCaseInfo(Province *head,char *str)
{
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		Case *tail1=tail->ProvCase;
		Case *tail1old=tail1;
		while(tail1->next!=NULL)
		{
			tail1old=tail1;
			tail1=tail1->next;
			if(!strcmp(tail1->CaseId,str))
			{
				tail1old->next=tail1->next;
				tail1->next=NULL;
				return;
			}
		}
	}
}
/**
 * 函数名称: DeleteRepoInfo
 * 函数功能: 删除媒体信息.
 * 输入参数: head 链表头结点指针；str 用户输入的报道编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void DeleteRepoInfo(Province *head, char *str)
{
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			Report *tail2=tail1->CaseRepo;
			Report *tail2old=tail2;
			while(tail2->next!=NULL)
			{
				tail2old=tail2;
				tail2=tail2->next;
				if(!strcmp(tail2->RepoId,str))
				{
					tail2old->next=tail2->next;
					tail2->next=NULL;
					return;
				}
			}
		}
	}
}
