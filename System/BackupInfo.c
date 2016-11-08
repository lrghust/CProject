#include"head.h"
/**
 * ��������: BackupInfo
 * ��������: ������Ϣ.
 * �������: head ����ͷ���ָ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:����������Ϣ������Backup.txt�ļ����Ա�������ݻָ�
 */
void BackupInfo(Province *head)
{
	FILE *p=fopen("Backup.txt","w+");
	Province *tail=head;
	while(tail->next!=NULL)//��һ��������ʡ����Ϣ
	{
		tail=tail->next;
		fprintf(p,"%d %s %s %s\n",1,tail->ProvProv,tail->ProvLeader,tail->ProvTel);
		Case *tail1=tail->ProvCase;
		while(tail1->next!=NULL)//�ڶ��������永����Ϣ
		{
			tail1=tail1->next;
			fprintf(p,"%d %s %s %s %s %c %c %f %d\n",2,tail1->CaseProv,tail1->CaseId,tail1->CaseDate,tail1->CaseName,tail1->CaseLevel,tail1->CaseCharge,tail1->CaseMoney,tail1->CaseJudge);
			Report *tail2=tail1->CaseRepo;
			while(tail2->next!=NULL)//������������ý����Ϣ
			{
				tail2=tail2->next;
				fprintf(p,"%d %s %s %s %s %s %c\n",3,tail2->RepoCaseId,tail2->RepoId,tail2->RepoDate,tail2->RepoFirm,tail2->RepoIndex,tail2->RepoField);
			}
		}
	}
	fclose(p);
}
