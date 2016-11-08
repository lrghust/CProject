#include"head.h"
/**
 * 函数名称: SearchProvInfo
 * 函数功能: 查找省份信息.
 * 输入参数: head 主链表头结点指针；tempnum 查找方式：0直接返回，1按省份名称，2按负责人
 *           temp 匹配信息（省份名称或负责人）
 * 输出参数: str 指向存储查找到的信息
 * 返 回 值: 无
 *
 * 调用说明:
 */
void SearchProvInfo(Province *head,int tempnum,char *temp,char **str)
{
	if(tempnum==0)
		return;
	Province *tail=head;
	while(tail->next!=NULL)
	{
		tail=tail->next;
		if(tempnum==1)//按省份名称搜索
		{
			if(!strcmp(tail->ProvProv,temp))
			{
				sprintf(str[0],"省份名称:%s",tail->ProvProv);
				sprintf(str[1],"负责人:%s",tail->ProvLeader);
				sprintf(str[2],"联系电话:%s",tail->ProvTel);
				break;
			}
		}
		else if(tempnum==2)//按负责人搜索
		{
			if(!strcmp(tail->ProvLeader,temp))
			{
				sprintf(str[0],"省份名称:%s",tail->ProvProv);
				sprintf(str[1],"负责人:%s",tail->ProvLeader);
				sprintf(str[2],"联系电话:%s",tail->ProvTel);
				break;
			}
		}
	}
}

/**
 * 函数名称: SearchCaseInfo
 * 函数功能: 查找案件信息.
 * 输入参数: head 主链表头结点指针；tempnum 查找方式：0直接返回，1按案件编号，2按被告姓名与行政级别
 *           temp 匹配信息：案件编号或被告姓名 temp2 匹配信息：空或行政级别
 * 输出参数: str 指向存储查找到的信息
 * 返 回 值: 无
 *
 * 调用说明:
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
					sprintf(str[0],"所属省份:%s",tail1->CaseProv);
					sprintf(str[1],"案件编号:%s",tail1->CaseId);
					sprintf(str[2],"立案日期:%s",tail1->CaseDate);
					sprintf(str[3],"被告人姓名:%s",tail1->CaseName);
					sprintf(str[4],"行政级别:%s",LEVEL[tail1->CaseLevel-'A']);
					sprintf(str[5],"主要罪名:%s",CHARGE[tail1->CaseCharge-'1']);
					sprintf(str[6],"涉案金额:%f",tail1->CaseMoney);
					if(tail1->CaseJudge<0)
                    {
                        char JUDGE[]="死刑";
                        sprintf(str[7],"刑事处罚:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=100)
                    {
                        char JUDGE[]="无期徒刑";
                        sprintf(str[7],"刑事处罚:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=1&&tail1->CaseJudge<=99)
                    {
                        sprintf(str[7],"刑事处罚:有期徒刑%d年",tail1->CaseJudge);
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
					sprintf(str[0],"所属省份:%s",tail1->CaseProv);
					sprintf(str[1],"案件编号:%s",tail1->CaseId);
					sprintf(str[2],"立案日期:%s",tail1->CaseDate);
					sprintf(str[3],"被告人姓名:%s",tail1->CaseName);
					sprintf(str[4],"行政级别:%s",LEVEL[tail1->CaseLevel-'A']);
					sprintf(str[5],"主要罪名:%s",CHARGE[tail1->CaseCharge-'1']);
					sprintf(str[6],"涉案金额:%f",tail1->CaseMoney);
					if(tail1->CaseJudge<0)
                    {
                        char JUDGE[]="死刑";
                        sprintf(str[7],"刑事处罚:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=100)
                    {
                        char JUDGE[]="无期徒刑";
                        sprintf(str[7],"刑事处罚:%s",JUDGE);
                    }
                    else if(tail1->CaseJudge>=1&&tail1->CaseJudge<=99)
                    {
                        sprintf(str[7],"刑事处罚:有期徒刑%d年",tail1->CaseJudge);
                    }
					return;
				}
			}
		}
	}
}

/**
 * 函数名称: SearchRepoInfo
 * 函数功能: 查找媒体信息.
 * 输入参数: head 主链表头结点指针；tempnum 查找方式：0直接返回，1按案件编号与媒体名称，2按报道日期与媒体名称
 *           temp 匹配信息：案件编号或报道日期 temp2 匹配信息：媒体名称
 * 输出参数: str 指向存储查找到的信息
 * 返 回 值: 无
 *
 * 调用说明:
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
                        sprintf(str[0],"报道编号:%s",tail2->RepoId);
                        sprintf(str[1],"案件编号:%s",tail2->RepoCaseId);
                        sprintf(str[2],"报道日期:%s",tail2->RepoDate);
                        sprintf(str[3],"媒体类别:%s",FIELD[tail2->RepoField-'1']);
                        sprintf(str[4],"媒体名称:%s",tail2->RepoFirm);
                        sprintf(str[5],"内容索引:%s",tail2->RepoIndex);
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
                        sprintf(str[0],"报道编号:%s",tail2->RepoId);
                        sprintf(str[1],"案件编号:%s",tail2->RepoCaseId);
                        sprintf(str[2],"报道日期:%s",tail2->RepoDate);
                        sprintf(str[3],"媒体类别:%s",FIELD[tail2->RepoField-'1']);
                        sprintf(str[4],"媒体名称:%s",tail2->RepoFirm);
                        sprintf(str[5],"内容索引:%s",tail2->RepoIndex);
					}
				}
			}
		}
	}
}
