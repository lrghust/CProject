#include"head.h"
/**
 * ��������: DeleteProvInfo
 * ��������: ɾ��ʡ����Ϣ.
 * �������: head ����ͷ���ָ�룻str �û������ʡ������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ԭʡ���µİ�����ý����Ϣ����ʧ
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
 * ��������: DeleteCaseInfo
 * ��������: ɾ��������Ϣ.
 * �������: head ����ͷ���ָ�룻str �û�����İ������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ԭʡ���µ�ý����Ϣ����ʧ
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
 * ��������: DeleteRepoInfo
 * ��������: ɾ��ý����Ϣ.
 * �������: head ����ͷ���ָ�룻str �û�����ı������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
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
