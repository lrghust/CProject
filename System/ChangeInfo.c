#include"head.h"
/**
 * 函数名称: ChangeProvInfo
 * 函数功能: 修改省份信息，将用户输入的修改后的信息加载到链表中.
 * 输入参数: head 链表头结点指针；match 来自用户的省份名称；str来自用户的修改后的信息
 * 输出参数: 无
 * 返 回 值: flag 返回值为1表明对省份名称进行了修改，0表示没有
 *
 * 调用说明: 若修改了省份名称，结点下的案件及媒体信息将丢失
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
 * 函数名称: ChangeCaseInfo
 * 函数功能: 修改案件信息，将用户输入的修改后的信息加载到链表中.
 * 输入参数: head 链表头结点指针；match 来自用户的案件编号；str来自用户的修改后的信息
 * 输出参数: 无
 * 返 回 值: flag 返回值为1表明对案件编号进行了修改，0表示没有
 *
 * 调用说明: 若修改了案件编号，节点下的媒体信息将丢失
 */
int ChangeCaseInfo(Province *head,char *match,char **str)
{
	Province *tail=head;
	int flag=0;//标志是否修改了案件编号
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
                Province *tailnew=head;//要把改变了省份的案件信息挂到改后的省份下面
                while(tailnew->next!=NULL)
                {
                    tailnew=tailnew->next;
                    if(!strcmp(tailnew->ProvProv,tail1->CaseProv))
                    {
                        Case *tail1new=tailnew->ProvCase;
                        while(tail1new->next!=NULL)
                            tail1new=tail1new->next;
                        tail1new->next=tail1;//原结点挂在新省份的案件链下面
                        tail1old->next=tail1->next;//原结点的前一个节点指向原结点下一个节点
                        tail1->next=NULL;//原结点为新省份下案件链的末端，next置为NULL
                        break;
                    }
                }
                //若传入信息不为空，加载到链表中
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
 * 函数名称: ChangeRepoInfo
 * 函数功能: 修改媒体信息，将用户输入的修改后的信息加载到链表中.
 * 输入参数: head 链表头结点指针；match 来自用户的报道编号；str来自用户的修改后的信息
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
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
