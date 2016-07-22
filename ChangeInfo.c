#include"head.h"
//信息修改函数：
//省份信息修改函数
void ChangeProvInfo(Province *head)
{
	Province *tail=head;
	printf("Province:");
	char temp[50];
	scanf("%s",temp);
	while(tail->next!=NULL)
	{
		tail=tail->next;
		if(!strcmp(tail->ProvProv,temp))
		{
			while(1)
			{
				printf("1-manincharge 2-telephone 3-exit:");
				int a;
				scanf("%d",&a);
				if(a==3)
					break;
				else
				{
					printf("New info:");
					if(a==1)
						scanf("%s",tail->ProvLeader);
					else if(a==2)
						scanf("%s",tail->ProvTel);
				}
			}
			break;
		}
	}
}
//案件信息修改函数
void ChangeCaseInfo(Province *head)
{
	Province *tail=head;
	printf("ID:");
	
}
//媒体信息修改函数
void ChangeReportInfo(Province *head)
{
	
}