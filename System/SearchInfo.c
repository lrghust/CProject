#include"head.h"
/**
 * ��������: SearchProvInfo
 * ��������: ����ʡ����Ϣ.
 * �������: head ������ͷ���ָ�룻tempnum ���ҷ�ʽ��0ֱ�ӷ��أ�1��ʡ�����ƣ�2��������
 *           temp ƥ����Ϣ��ʡ�����ƻ����ˣ�
 * �������: str ָ��洢���ҵ�����Ϣ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void SearchProvInfo(Province *head,int tempnum,char *temp,char **str)
{
	if(tempnum==0)
		return;
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		if(tempnum==1)//��ʡ����������
		{
			if(!strcmp(tail->ProvProv,temp))
			{
				sprintf(str[0],"ʡ������:%s",tail->ProvProv);
				sprintf(str[1],"������:%s",tail->ProvLeader);
				sprintf(str[2],"��ϵ�绰:%s",tail->ProvTel);
				break;
			}
		}
		else if(tempnum==2)//������������
		{
			if(!strcmp(tail->ProvLeader,temp))
			{
				sprintf(str[0],"ʡ������:%s",tail->ProvProv);
				sprintf(str[1],"������:%s",tail->ProvLeader);
				sprintf(str[2],"��ϵ�绰:%s",tail->ProvTel);
				break;
			}
		}
	}
}

/**
 * ��������: SearchCaseInfo
 * ��������: ���Ұ�����Ϣ.
 * �������: head ������ͷ���ָ�룻tempnum ���ҷ�ʽ��0ֱ�ӷ��أ�1��������ţ�2��������������������
 *           temp ƥ����Ϣ��������Ż򱻸����� temp2 ƥ����Ϣ���ջ���������
 * �������: str ָ��洢���ҵ�����Ϣ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void SearchCaseInfo(Province *head,int tempnum,char *temp1,char temp2,char **str)
{
	if(tempnum==0)return;
	if(tempnum==1)
	{
		Province *tail=head;
		while(tail->next!=NULL)
		{
			tail=tail->next;
			Case *tail1=tail->ProvCase;
			while(tail1->next!=NULL)
			{
				tail1=tail1->next;
				if(!strcmp(temp1,tail1->CaseId))
				{
					sprintf(str[0],"����ʡ��:%s",tail1->CaseProv);
					sprintf(str[1],"�������:%s",tail1->CaseId);
					sprintf(str[2],"��������:%s",tail1->CaseDate);
					sprintf(str[3],"����������:%s",tail1->CaseName);
					sprintf(str[4],"��������:%s",LEVEL[tail1->CaseLevel-'A']);
					sprintf(str[5],"��Ҫ����:%s",CHARGE[tail1->CaseCharge-'1']);
					sprintf(str[6],"�永���:%f",tail1->CaseMoney);
					if(tail1->CaseJudge<0)
                    {
                        char JUDGE[]="����";
                        sprintf(str[7],"���´���:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=100)
                    {
                        char JUDGE[]="����ͽ��";
                        sprintf(str[7],"���´���:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=1&&tail1->CaseJudge<=99)
                    {
                        sprintf(str[7],"���´���:����ͽ��%d��",tail1->CaseJudge);
                    }
					return;
				}
			}
		}
	}
	else if(tempnum==2)
	{
		Province *tail=head;
		while(tail->next!=NULL)
		{
			tail=tail->next;
			Case *tail1=tail->ProvCase;
			while(tail1->next!=NULL)
			{
				tail1=tail1->next;
				if((!strcmp(temp1,tail1->CaseName))&&temp2==tail1->CaseLevel)
				{
					sprintf(str[0],"����ʡ��:%s",tail1->CaseProv);
					sprintf(str[1],"�������:%s",tail1->CaseId);
					sprintf(str[2],"��������:%s",tail1->CaseDate);
					sprintf(str[3],"����������:%s",tail1->CaseName);
					sprintf(str[4],"��������:%s",LEVEL[tail1->CaseLevel-'A']);
					sprintf(str[5],"��Ҫ����:%s",CHARGE[tail1->CaseCharge-'1']);
					sprintf(str[6],"�永���:%f",tail1->CaseMoney);
					if(tail1->CaseJudge<0)
                    {
                        char JUDGE[]="����";
                        sprintf(str[7],"���´���:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=100)
                    {
                        char JUDGE[]="����ͽ��";
                        sprintf(str[7],"���´���:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=1&&tail1->CaseJudge<=99)
                    {
                        sprintf(str[7],"���´���:����ͽ��%d��",tail1->CaseJudge);
                    }
					return;
				}
			}
		}
	}
}

/**
 * ��������: SearchRepoInfo
 * ��������: ����ý����Ϣ.
 * �������: head ������ͷ���ָ�룻tempnum ���ҷ�ʽ��0ֱ�ӷ��أ�1�����������ý�����ƣ�2������������ý������
 *           temp ƥ����Ϣ��������Ż򱨵����� temp2 ƥ����Ϣ��ý������
 * �������: str ָ��洢���ҵ�����Ϣ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void SearchRepoInfo(Province *head,int tempnum,char *temp1,char *temp2,char **str)
{
	if(tempnum==0)return;
	if(tempnum==1)
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
				while(tail2->next!=NULL)
				{
					tail2=tail2->next;
					if((!strcmp(temp1,tail2->RepoCaseId))&&(!strcmp(temp2,tail2->RepoFirm)))
					{
                        sprintf(str[0],"�������:%s",tail2->RepoId);
                        sprintf(str[1],"�������:%s",tail2->RepoCaseId);
                        sprintf(str[2],"��������:%s",tail2->RepoDate);
                        sprintf(str[3],"ý�����:%s",FIELD[tail2->RepoField-'1']);
                        sprintf(str[4],"ý������:%s",tail2->RepoFirm);
                        sprintf(str[5],"��������:%s",tail2->RepoIndex);
					}
				}
			}
		}
	}
	else if(tempnum==2)
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
				while(tail2->next!=NULL)
				{
					tail2=tail2->next;
					if((!strcmp(temp1,tail2->RepoDate))&&strstr(tail2->RepoFirm,temp2))
					{
                        sprintf(str[0],"�������:%s",tail2->RepoId);
                        sprintf(str[1],"�������:%s",tail2->RepoCaseId);
                        sprintf(str[2],"��������:%s",tail2->RepoDate);
                        sprintf(str[3],"ý�����:%s",FIELD[tail2->RepoField-'1']);
                        sprintf(str[4],"ý������:%s",tail2->RepoFirm);
                        sprintf(str[5],"��������:%s",tail2->RepoIndex);
					}
				}
			}
		}
	}
}
