#include"head.h"
/**
 * 函数名称: CountByCaseCharge
 * 函数功能: 以主要罪名为条件分别统计历年来各种罪名贪腐案件的发生数、涉案金额，按案件发生数降序排序后，输出统计结果.
 * 输入参数: head 链表头结点指针
 * 输出参数: str 存储统计结果
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CountByCaseCharge(Province *head,char **str)
{
	typedef struct CountCharge{    //结点保存各种罪名贪腐案件的发生数、涉案金额，用于排序
		int num;
		float money;
	}CountCharge;
	CountCharge count[7];
	int i;
	for(i=1;i<7;i++)//i表示主要罪名
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
	//排序
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
 * 函数名称: CountByCaseLevel
 * 函数功能: 以行政级别为条件分别统计某年度内各种行政级别贪腐案件的发生数，
 *           其中刑事处罚为1死刑、2无期徒刑、3有期徒刑1-5年、4有期徒刑6-10及5有期徒刑11年以上的案件分别是多少起.
 * 输入参数: head 链表头结点指针；year 用户输入的需统计的年份
 * 输出参数: str 存储统计结果
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CountByCaseLevel(Province *head,char *year,char **str)
{
	int count[9][6];//二维数组表示8个行政级别的5种刑事处罚
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
 * 函数名称: CountByCaseProv
 * 函数功能: 以案件发生地所属省份为条件分别统计某个时间段内各省份贪腐案件的发生数，涉案金额总数，按案件发生数降序排序后输出统计结果.
 * 输入参数: head 链表头结点指针；begin 用户输入的需统计的开始日期；end 用户输入的需统计的截止日期
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CountByCaseProv(Province *head,char *begin,char *end)
{
	typedef struct CountProv{  //结点存储各省份案件数、涉案金额数，便于排序
		char provname[9];
		int casenum;
		float casemoney;
	}CountProv;

	int len=0;//省份数量
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		len++;
	}
	CountProv count[len];//用结构数组存放统计结果
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
	//排序
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
	//输出统计结果
	char output[len+2][100];
	for(i=0;i<len;i++)
	{
		sprintf(output[i+1],"%-12s%-12d%-12f\n",count[i].provname,count[i].casenum,count[i].casemoney);
	}
	strcpy(output[0],"省份名称    案件数量    涉案金额    ");
	strcpy(output[len+1],"确定");
	//由于条目数量事先不确定，在功能函数中进行输出
    char *plabel_name[len+2];
    for(i=0;i<len+2;i++)
        plabel_name[i]=output[i];
    ShowModule(plabel_name, len+2);
}

/**
 * 函数名称: CountByRepoNum
 * 函数功能: 统计媒体报道数最多的10个贪腐案件，按报道数降序排序后输出案件编号、被告行政级别、主要罪名、涉案金额、刑事处罚和媒体报道次数.
 * 输入参数: head 链表头结点指针；
 * 输出参数: str 存储统计结果
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CountByRepoNum(Province *head,char **str)
{
	typedef struct Data{  //用结构封装结点数据域，便于链表排序时进行数据域交换
		char id[12];
		char level;
		char charge;
		float money;
		int judge;
		int reponum;
	}Data;
	typedef struct CountRepo{  //链表结点结构
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
			//复制案件信息到新链表
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
	//排序
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
	    if(ftail->data.judge<0)sprintf(sjudge,"死刑");
	    else if(ftail->data.judge>=100)sprintf(sjudge,"无期徒刑");
	    else if(ftail->data.judge<100&&ftail->data.judge>0)sprintf(sjudge,"有期徒刑%d年",ftail->data.judge);
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
 * 函数名称: CountByLevelCharge
 * 函数功能: 以行政级别为条件统计各主要罪名案件数量.
 * 输入参数: head 链表头结点指针；
 * 输出参数: str 存储统计结果
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CountByLevelCharge(Province *head,char **str)
{
	int count[9][7];//二维数组表示8个行政级别，6种主要罪名
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
