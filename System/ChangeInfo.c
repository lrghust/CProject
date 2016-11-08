#include"head.h"
/**
 * ��������: ChangeProvInfo
 * ��������: �޸�ʡ����Ϣ�����û�������޸ĺ����Ϣ���ص�������.
 * �������: head ����ͷ���ָ�룻match �����û���ʡ�����ƣ�str�����û����޸ĺ����Ϣ
 * �������: ��
 * �� �� ֵ: flag ����ֵΪ1������ʡ�����ƽ������޸ģ�0��ʾû��
 *
 * ����˵��: ���޸���ʡ�����ƣ�����µİ�����ý����Ϣ����ʧ
 */
int ChangeProvInfo(Province *head,char *match,char **str)
{
	Province *tail=head;
	int flag=0;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		if(!strcmp(tail->ProvProv,match))
		{
			if(strcmp(str[0],tail->ProvProv))
            {
                strcpy(tail->ProvProv,str[0]);
                tail->ProvCase=(Case *)malloc(sizeof(Case));
                tail->ProvCase->next=NULL;
                flag=1;
            }
            strcpy(tail->ProvLeader,str[1]);
            strcpy(tail->ProvTel,str[2]);
		}
	}
	return flag;
}
/**
 * ��������: ChangeCaseInfo
 * ��������: �޸İ�����Ϣ�����û�������޸ĺ����Ϣ���ص�������.
 * �������: head ����ͷ���ָ�룻match �����û��İ�����ţ�str�����û����޸ĺ����Ϣ
 * �������: ��
 * �� �� ֵ: flag ����ֵΪ1�����԰�����Ž������޸ģ�0��ʾû��
 *
 * ����˵��: ���޸��˰�����ţ��ڵ��µ�ý����Ϣ����ʧ
 */
int ChangeCaseInfo(Province *head,char *match,char **str)
{
	Province *tail=head;
	int flag=0;//��־�Ƿ��޸��˰������
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
		Case *tail1old=tail->ProvCase;
        while(tail1->next!=NULL)
        {
			tail1old=tail1;
            tail1=tail1->next;
            if(!strcmp(tail1->CaseId,match))
            {
                strcpy(tail1->CaseProv,str[2]);
                Province *tailnew=head;//Ҫ�Ѹı���ʡ�ݵİ�����Ϣ�ҵ��ĺ��ʡ������
                while(tailnew->next!=NULL)
                {
                    tailnew=tailnew->next;
                    if(!strcmp(tailnew->ProvProv,tail1->CaseProv))
                    {
                        Case *tail1new=tailnew->ProvCase;
                        while(tail1new->next!=NULL)
                            tail1new=tail1new->next;
                        tail1new->next=tail1;//ԭ��������ʡ�ݵİ���������
                        tail1old->next=tail1->next;//ԭ����ǰһ���ڵ�ָ��ԭ�����һ���ڵ�
                        tail1->next=NULL;//ԭ���Ϊ��ʡ���°�������ĩ�ˣ�next��ΪNULL
                        break;
                    }
                }
                //��������Ϣ��Ϊ�գ����ص�������
				if(strcmp(str[0],tail1->CaseId))
                {
                    flag=1;
                    strcpy(tail1->CaseId,str[0]);
                    tail1->CaseRepo=(Report *)malloc(sizeof(Report));
                    tail1->CaseRepo->next=NULL;
                }
                strcpy(tail1->CaseDate,str[1]);
                strcpy(tail1->CaseName,str[3]);
                tail1->CaseLevel=*str[4];
                tail1->CaseCharge=*str[5];
                tail1->CaseMoney=atof(str[6]);
                tail1->CaseJudge=*str[7];
                return flag;
            }
        }
    }
    return flag;
}
/**
 * ��������: ChangeRepoInfo
 * ��������: �޸�ý����Ϣ�����û�������޸ĺ����Ϣ���ص�������.
 * �������: head ����ͷ���ָ�룻match �����û��ı�����ţ�str�����û����޸ĺ����Ϣ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ChangeRepoInfo(Province *head, char *match, char **str)
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
				if(!strcmp(tail2->RepoId,match))
				{
				    if(strcmp(str[0],tail2->RepoCaseId))
                    {
                        strcpy(tail2->RepoCaseId,str[0]);
                        Province *tailnew=head;
                        int flag=0;
                        while(tailnew->next!=NULL)
                        {
                            tailnew=tailnew->next;
                            Case *tail1new=tailnew->ProvCase;
                            while(tail1new->next!=NULL)
                            {
                                tail1new=tail1new->next;
                                if(!strcmp(tail1new->CaseId,tail2->RepoCaseId))
                                {
                                    flag=1;
                                    Report *tail2new=tail1new->CaseRepo;
                                    while(tail2new->next!=NULL)
                                        tail2new=tail2new->next;
                                    tail2new->next=tail2;
                                    tail2old->next=tail2->next;
                                    tail2->next=NULL;
                                    break;
                                }
                            }
                            if(flag)break;
                        }
                    }
                    strcpy(tail2->RepoId,str[1]);
                    strcpy(tail2->RepoDate,str[2]);
                    tail2->RepoField=*str[2];
                    strcpy(tail2->RepoFirm,str[4]);
                    strcpy(tail2->RepoIndex,str[5]);
				}
			}
		}
	}
}
