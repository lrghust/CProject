#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//媒体报道基本信息
typedef struct Report{
	char RepoId[12];
	char RepoDate[10];
	char RepoFirm[20];
	char RepoIndex[50];
	char RepoField;
	Report *next;
}Report;
//贪腐案件基本信息
typedef struct Case{
	char CaseProv[8];
	char CaseId[12];
	char CaseDate[10];
	char CaseName[15];
	char CaseLevel;
	char CaseCharge;
	char CaseMoney;
	int CaseJudge;
	Case *next;
	Report *CaseReport;
}Case;
//所属省份监管信息
typedef struct Province{
	char ProvProv[8];
	char ProvLeader[15];
	char ProvTel[15];
	Province *next;
	Case *ProvCase;
}Province;

//函数原型声明

//信息初始化函数
Province * Init(void);

//信息录入函数：
//省份信息录入函数
void InputProvInfo(Province *);
//案件信息录入函数
void InputCaseInfo(Province *);
//媒体信息录入函数
void InputReportInfo(Province *);

//信息修改函数：
//省份信息修改函数
void ChangeProvInfo(Province *);
//案件信息修改函数
void ChangeCaseInfo(Province *);
//媒体信息修改函数
void ChangeReportInfo(Province *);