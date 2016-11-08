#include"head.h"
/**
 * ��������: DealString
 * ��������: �������Ļ�϶����ַ�������\0.
 * �������: str Ҫ������ַ���
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void DealString(char *str)//�������Ļ�϶����ַ�������\0
{
    int i=0;
    while(1)
    {
        if(str[i]==' ')
        {
            str[i]='\0';
            break;
        }
        i++;
    }
}
/**
 * ��������: TestProv
 * ��������: ����ʡ����Ϣ�Ƿ����.
 * �������: str Ҫ���Ե�ʡ������
 * �������: ��
 * �� �� ֵ: flag 1��ʾ�޸���ʡ���� 0û��
 *
 * ����˵��:
 */
int TestProv(char *str)//����ʡ����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        if(!strcmp(str,tail->ProvProv))
        {
            flag=1;
            break;
        }
    }
    return flag;
}

/**
 * ��������: TestProvForChange
 * ��������: ����ʡ����Ϣ�Ƿ���ڲ�����ʡ����Ϣ.
 * �������: str Ҫ���Ե�ʡ������
 * �������: output ָ���������ʡ����Ϣ
 * �� �� ֵ: flag 1��ʾ�޸���ʡ���� 0û��
 *
 * ����˵��:
 */
int TestProvForChange(char *str,char **output)//����ʡ����Ϣ�Ƿ���ڲ�����ʡ����Ϣ
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        if(!strcmp(str,tail->ProvProv))
        {
            flag=1;
            sprintf(output[0],"%s",tail->ProvProv);
            sprintf(output[1],"%s",tail->ProvLeader);
            sprintf(output[2],"%s",tail->ProvTel);
            break;
        }
    }
    return flag;
}

/**
 * ��������: TestCase
 * ��������: ���԰�����Ϣ�Ƿ����.
 * �������: str Ҫ���Եİ������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestCase(char *str)//���԰�����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if(!strcmp(str,tail1->CaseId))
            {
                flag=1;
                return flag;
            }
        }
    }
    return flag;
}

/**
 * ��������: TestCaseForChange
 * ��������: ���԰�����Ϣ�Ƿ����.
 * �������: str Ҫ���Եİ������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestCaseForChange(char *str,char **output)//���԰�����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if(!strcmp(str,tail1->CaseId))
            {
                flag=1;
                sprintf(output[0],"%s",tail1->CaseProv);
                sprintf(output[1],"%s",tail1->CaseId);
                sprintf(output[2],"%s",tail1->CaseDate);
                sprintf(output[3],"%s",tail1->CaseName);
                *output[4]=tail1->CaseLevel;
                *output[5]=tail1->CaseCharge;
                sprintf(output[6],"%f",tail1->CaseMoney);
                sprintf(output[7],"%d",tail1->CaseJudge);
                return flag;
            }
        }
    }
    return flag;
}

/**
 * ��������: TestRepo
 * ��������: ����ý����Ϣ�Ƿ����.
 * �������: str Ҫ���Եı������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestRepo(char *str)//����ý����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
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
                if(!strcmp(str,tail2->RepoId))
                {
                    flag=1;
                    return flag;
                }
            }
        }
    }
    return flag;
}

/**
 * ��������: TestRepoForChange
 * ��������: ����ý����Ϣ�Ƿ����.
 * �������: str Ҫ���Եı������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestRepoForChange(char *str,char **output)//����ý����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
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
                if(!strcmp(str,tail2->RepoId))
                {
                    flag=1;
                    sprintf(output[0],"%s",tail2->RepoCaseId);
                    sprintf(output[1],"%s",tail2->RepoId);
                    sprintf(output[2],"%s",tail2->RepoDate);
                    sprintf(output[3],"%s",tail2->RepoFirm);
                    sprintf(output[4],"%s",tail2->RepoIndex);
                    *output[5]=tail2->RepoField;
                    return flag;
                }
            }
        }
    }
    return flag;
}

/**
 * ��������: TestLeader
 * ��������: ��ʡ�ݸ����˲���ʡ����Ϣ�Ƿ����.
 * �������: str Ҫ���Եĸ�����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestLeader(char *str)//��ʡ�ݸ����˲���ʡ����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        if(!strcmp(str,tail->ProvLeader))
        {
            flag=1;
            break;
        }
    }
    return flag;
}

/**
 * ��������: TestYear
 * ��������: ����ĳ��ݰ�����Ϣ�Ƿ����.
 * �������: str Ҫ���Ե����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestYear(char *str)//����ĳ��ݰ�����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if(strstr(tail1->CaseDate,str))
            {
                flag=1;
                return flag;
            }
        }

    }
    return flag;
}

/**
 * ��������: TestBEDate
 * ��������: ����ĳʱ��ΰ�����Ϣ�Ƿ����.
 * �������: begin ��ʼʱ�䣻end ��ֹʱ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestBEDate(char *begin,char *end)//����ĳʱ��ΰ�����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            int temp=atoi(tail1->CaseDate);
            if(temp>=atoi(begin)&&temp<=atoi(end))
            {
                flag=1;
                return flag;
            }
        }

    }
    return flag;
}

/**
 * ��������: TestNL
 * ��������: ����������������������԰�����Ϣ�Ƿ����.
 * �������: str ����������c ��������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestNL(char *str,char c)//����������������������԰�����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
    while(tail->next!=NULL)
    {
        tail=tail->next;
        Case *tail1=tail->ProvCase;
        while(tail1->next!=NULL)
        {
            tail1=tail1->next;
            if((!strcmp(str,tail1->CaseName))&&(c==tail1->CaseLevel))
            {
                flag=1;
                return flag;
            }
        }

    }
    return flag;
}

/**
 * ��������: TestRepoByIF
 * ��������: ��������ź�ý������������ý����Ϣ�Ƿ����.
 * �������: str1 ������ţ�str2 ý������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestRepoByIF(char *str1,char *str2)//��������ź�ý������������ý����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
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
                if((!strcmp(str1,tail2->RepoCaseId))&&(!strcmp(str2,tail2->RepoFirm)))
                {
                    flag=1;
                    return flag;
                }
            }
        }
    }
    return flag;
}

/**
 * ��������: TestRepoByDF
 * ��������: ���������ں�ý������������ý����Ϣ�Ƿ����.
 * �������: str1 �������ڣ�str2 ý������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
int TestRepoByDF(char *str1,char *str2)//���������ں�ý������������ý����Ϣ�Ƿ����
{
    Province *tail=head;
    int flag=0;
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
                if((!strcmp(str1,tail2->RepoDate))&&strstr(tail2->RepoFirm,str2))
                {
                    flag=1;
                    return flag;
                }
            }
        }
    }
    return flag;
}
