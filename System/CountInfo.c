#include"head.h"
/**
 * ��������: CountByCaseCharge
 * ��������: ����Ҫ����Ϊ�����ֱ�ͳ����������������̰�������ķ��������永��������������������������ͳ�ƽ��.
 * �������: head ����ͷ���ָ��
 * �������: str �洢ͳ�ƽ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CountByCaseCharge(Province *head,char **str)
{
	typedef struct CountCharge{    //��㱣���������̰�������ķ��������永����������
		int num;
		float money;
	}CountCharge;
	CountCharge count[7];
	int i;
	for(i=1;i<7;i++)//i��ʾ��Ҫ����
	{
		count[i].num=0;
		count[i].money=0;
	}
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			count[tail1->CaseCharge-'0'].num++;
			count[tail1->CaseCharge-'0'].money+=tail1->CaseMoney;
		}
	}
	//����
	int j;
	for(i=1;i<7;i++)
	{
		for(j=1;j<7-i;j++)
		{
			if(count[j].num<count[j+1].num)
			{
				CountCharge temp;
				temp=count[j];
				count[j]=count[j+1];
				count[j+1]=temp;
			}
		}
	}
	for(i=1;i<7;i++)
	{
		sprintf(str[i-1],"%-12s%-12d%-12f",CHARGE[i-1],count[i].num,count[i].money);
	}
}

/**
 * ��������: CountByCaseLevel
 * ��������: ����������Ϊ�����ֱ�ͳ��ĳ����ڸ�����������̰�������ķ�������
 *           �������´���Ϊ1���̡�2����ͽ�̡�3����ͽ��1-5�ꡢ4����ͽ��6-10��5����ͽ��11�����ϵİ����ֱ��Ƕ�����.
 * �������: head ����ͷ���ָ�룻year �û��������ͳ�Ƶ����
 * �������: str �洢ͳ�ƽ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CountByCaseLevel(Province *head,char *year,char **str)
{
	int count[9][6];//��ά�����ʾ8�����������5�����´���
	int i;
	memset(count,0,sizeof(count));
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			if(strstr(tail1->CaseDate,year))
			{
				if(tail1->CaseJudge<0)count[tail1->CaseLevel-'A'+1][1]++;
				else if(tail1->CaseJudge>=100)count[tail1->CaseLevel-'A'+1][2]++;
				else if(tail1->CaseJudge<=5&&tail1->CaseJudge>=1)count[tail1->CaseLevel-'A'+1][3]++;
				else if(tail1->CaseJudge<=10&&tail1->CaseJudge>=6)count[tail1->CaseLevel-'A'+1][4]++;
				else if(tail1->CaseJudge<100&&tail1->CaseJudge>=11)count[tail1->CaseLevel-'A'+1][5]++;
			}
		}
	}
	for(i=1;i<9;i++)
	{
		sprintf(str[i-1],"%-14s%-12d%-12d%-17d%-17d%-14d",LEVEL[i-1],count[i][1],count[i][2],count[i][3],count[i][4],count[i][5]);
	}
}

/**
 * ��������: CountByCaseProv
 * ��������: �԰�������������ʡ��Ϊ�����ֱ�ͳ��ĳ��ʱ����ڸ�ʡ��̰�������ķ��������永���������������������������������ͳ�ƽ��.
 * �������: head ����ͷ���ָ�룻begin �û��������ͳ�ƵĿ�ʼ���ڣ�end �û��������ͳ�ƵĽ�ֹ����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CountByCaseProv(Province *head,char *begin,char *end)
{
	typedef struct CountProv{  //���洢��ʡ�ݰ��������永���������������
		char provname[9];
		int casenum;
		float casemoney;
	}CountProv;

	int len=0;//ʡ������
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		len++;
	}
	CountProv count[len];//�ýṹ������ͳ�ƽ��
	tail=head;
	int i=0;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		strcpy(count[i].provname,tail->ProvProv);
		count[i].casenum=0;
		count[i].casemoney=0;
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			int tempnum=atoi(tail1->CaseDate);
			if(tempnum>=atoi(begin)&&tempnum<=atoi(end))
			{
				count[i].casenum++;
				count[i].casemoney+=tail1->CaseMoney;
			}
		}
		i++;
	}
	//����
	int j;
	for(i=0;i<len;i++)
	{
		for(j=0;j<len-i-1;j++)
		{
			if(count[j].casenum<count[j+1].casenum)
			{
				CountProv temp;
				temp=count[j];
				count[j]=count[j+1];
				count[j+1]=temp;
			}
		}
	}
	//���ͳ�ƽ��
	char output[len+2][100];
	for(i=0;i<len;i++)
	{
		sprintf(output[i+1],"%-12s%-12d%-12f\n",count[i].provname,count[i].casenum,count[i].casemoney);
	}
	strcpy(output[0],"ʡ������    ��������    �永���    ");
	strcpy(output[len+1],"ȷ��");
	//������Ŀ�������Ȳ�ȷ�����ڹ��ܺ����н������
    char *plabel_name[len+2];
    for(i=0;i<len+2;i++)
        plabel_name[i]=output[i];
    ShowModule(plabel_name, len+2);
}

/**
 * ��������: CountByRepoNum
 * ��������: ͳ��ý�屨��������10��̰����������������������������������š���������������Ҫ�������永�����´�����ý�屨������.
 * �������: head ����ͷ���ָ�룻
 * �������: str �洢ͳ�ƽ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CountByRepoNum(Province *head,char **str)
{
	typedef struct Data{  //�ýṹ��װ��������򣬱�����������ʱ���������򽻻�
		char id[12];
		char level;
		char charge;
		float money;
		int judge;
		int reponum;
	}Data;
	typedef struct CountRepo{  //������ṹ
		Data data;
		struct CountRepo *next;
	}CountRepo;
	CountRepo *fhead=(CountRepo *)malloc(sizeof(CountRepo));
	CountRepo *ftail=fhead;
	Province *tail=head;
	int len=0;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			ftail->next=(CountRepo *)malloc(sizeof(CountRepo));
			ftail=ftail->next;
			len++;
			//���ư�����Ϣ��������
			strcpy(ftail->data.id,tail1->CaseId);
			ftail->data.level=tail1->CaseLevel;
			ftail->data.charge=tail1->CaseCharge;
			ftail->data.money=tail1->CaseMoney;
			ftail->data.judge=tail1->CaseJudge;

			ftail->data.reponum=0;

			Report *tail2=tail1->CaseRepo;
			while(tail2->next!=NULL)
			{
				tail2=tail2->next;
				ftail->data.reponum++;
			}
		}
	}
	ftail->next=NULL;
	//����
	int i,j;
	for(i=1;i<=len;i++)
	{
	    ftail=fhead->next;
		for(j=1;j<=len-i;j++)
		{
			if(ftail->data.reponum<ftail->next->data.reponum)
			{
				Data temp;
				temp=ftail->data;
				ftail->data=ftail->next->data;
				ftail->next->data=temp;
			}
			ftail=ftail->next;
		}
	}
	ftail=fhead->next;
	if(len>10)len=10;
	for(i=1;i<=len;i++)
	{
	    char sjudge[12];
	    if(ftail->data.judge<0)sprintf(sjudge,"����");
	    else if(ftail->data.judge>=100)sprintf(sjudge,"����ͽ��");
	    else if(ftail->data.judge<100&&ftail->data.judge>0)sprintf(sjudge,"����ͽ��%d��",ftail->data.judge);
		sprintf(str[i-1],"%-12d%-12s%-12s%-12s%-12f%-14s%-12d\n",i,ftail->data.id,LEVEL[ftail->data.level-'A'],CHARGE[ftail->data.charge-'1'],ftail->data.money,sjudge,ftail->data.reponum);
		ftail=ftail->next;
	}
	if(len<10)
    {
        for(i=len+1;i<=10;i++)
            sprintf(str[i-1],"NULL");
    }
}

/**
 * ��������: CountByLevelCharge
 * ��������: ����������Ϊ����ͳ�Ƹ���Ҫ������������.
 * �������: head ����ͷ���ָ�룻
 * �������: str �洢ͳ�ƽ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CountByLevelCharge(Province *head,char **str)
{
	int count[9][7];//��ά�����ʾ8����������6����Ҫ����
	memset(count,0,sizeof(count));
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)
		{
			tail1=tail1->next;
			int level,charge;
			level=tail1->CaseLevel-'A'+1;
			charge=tail1->CaseCharge-'0';
			count[level][charge]++;
		}
	}
	int i;
	for(i=1;i<=8;i++)
	{
		sprintf(str[i-1],"%-20s%-10d%-10d%-10d%-10d%-12d%-10d",LEVEL[i-1],count[i][1],count[i][2],count[i][3],count[i][4],count[i][5],count[i][6]);
	}
}
