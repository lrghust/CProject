#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//媒体报道基本信息
typedef struct Report{
	char r_id[12];
	char r_date[10];
	char r_firm[20];
	char r_index[50];
	char r_field;
	Report *next;
}report;
//贪腐案件基本信息
typedef struct Cases{
	char c_prov[8];
	char c_id[12];
	char c_date[10];
	char c_name[15];
	char c_level;
	char c_charge;
	char c_money;
	int c_judge;
	Cases *next;
	Report *c_report;
}cases;
//所属省份监管信息
typedef struct Prov{
	char p_prov[8];
	char p_man[15];
	char p_tel[15];
	Prov *next;
	Cases *p_cases;
}prov;

//函数原型声明

//信息初始化函数
prov * init(void);

//信息录入函数：
//省份信息录入函数
void in_prov(prov *);
//案件信息录入函数
void in_cases(prov *);
//媒体信息录入函数
void in_report(prov *);

//信息修改函数：
//省份信息修改函数
void ch_prov(prov *);
//案件信息修改函数
void ch_cases(prov *);
//媒体信息修改函数
void ch_report(prov *);