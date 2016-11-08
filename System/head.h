//防止头文件重复引用
#ifndef _HEAD_H_
#define _HEAD_H_
//头文件引入
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//屏幕缓冲区行数与列数
#define SCR_ROW 28
#define SCR_COL 120

//媒体报道基本信息
typedef struct Report{
	char RepoCaseId[12];//对应案件ID
	char RepoId[14];//报道标识
	char RepoDate[10];
	char RepoFirm[20];
	char RepoIndex[50];
	char RepoField;
	struct Report *next;
}Report;
//贪腐案件基本信息
typedef struct Case{
	char CaseProv[9];//对应省份
	char CaseId[12];//案件标识
	char CaseDate[10];
	char CaseName[15];
	char CaseLevel;
	char CaseCharge;
	float CaseMoney;
	int CaseJudge;
	struct Case *next;
	Report *CaseRepo;
}Case;
//所属省份监管信息
typedef struct Province{
	char ProvProv[9];
	char ProvLeader[15];
	char ProvTel[15];
	struct Province *next;
	Case *ProvCase;
}Province;

//屏幕窗口信息链结点结点结构
typedef struct layer_node {
    char LayerNo;            //弹出窗口层数
    SMALL_RECT rcArea;       //弹出窗口区域坐标
    CHAR_INFO *pContent;     //弹出窗口区域字符单元原信息存储缓冲区
    char *pScrAtt;           //弹出窗口区域字符单元原属性值存储缓冲区
    struct layer_node *next; //指向下一结点的指针
} LAYER_NODE;

//标签束结构
typedef struct labe1_bundle {
    char **ppLabel;        //标签字符串数组首地址
    COORD *pLoc;           //标签定位数组首地址
    int num;               //标签个数
} LABEL_BUNDLE;

//热区结构
typedef struct hot_area {
    SMALL_RECT *pArea;     //热区定位数组首地址
    char *pSort;           //热区类别(按键、文本框、选项框)数组首地址
    char *pTag;            //热区序号数组首地址
    int num;               //热区个数
} HOT_AREA;

//变量外部引用
extern char *ga_main_menu[];     //主菜单项
extern char *ga_sub_menu[];      //子菜单项
extern int ga_sub_menu_count[];  //各主菜单项下子菜单的个数
extern int gi_sel_menu;          //被选中的主菜单项号,初始为1
extern int gi_sel_sub_menu;      //被选中的子菜单项号,初始为0,表示未选中
extern CHAR_INFO *gp_buff_menubar_info;     //存放菜单条屏幕区字符信息的缓冲区
extern CHAR_INFO *gp_buff_stateBar_info;    //存放状态条屏幕区字符信息的缓冲区
extern char *gp_scr_att;    //存放屏幕上字符单元属性值的缓冲区
extern char gc_sys_state;   //用来保存系统状态的字符
extern HANDLE gh_std_out;          //标准输出设备句柄
extern HANDLE gh_std_in;           //标准输入设备句柄
extern LAYER_NODE *gp_top_layer;   //弹出窗口信息链链头

extern char *LEVEL[];//行政级别对应中文字符串
extern char *CHARGE[];//主要罪名对应中文字符串
extern char *FIELD[];//媒体类型对应中文字符串
extern unsigned long ul;//补足函数参数
extern Province *head;//链表头结点指针

//函数原型声明
Province *InitInfo(void);//信息初始化函数
void SaveInfo(Province *);//信息保存函数
void BackupInfo(Province *);//信息备份函数
void RestoreInfo(Province **,char *);//信息恢复函数

//信息录入函数
void InputProvInfo(Province *, char **);//省份信息录入函数
void InputCaseInfo(Province *, char **);//案件信息录入函数
void InputRepoInfo(Province *, char **);//媒体信息录入函数

//信息修改函数
int ChangeProvInfo(Province *, char *, char **);//省份信息修改函数
int ChangeCaseInfo(Province *, char *, char **);//案件信息修改函数
void ChangeRepoInfo(Province *, char *, char **);//媒体信息修改函数

//信息删除函数
void DeleteProvInfo(Province *, char *);//省份信息删除函数
void DeleteCaseInfo(Province *, char *);//案件信息删除函数
void DeleteRepoInfo(Province *, char *);//媒体信息删除函数

//信息查询函数
void SearchProvInfo(Province *, int, char *, char **);//省份信息查询函数
void SearchCaseInfo(Province *, int, char *, char, char **);//案件信息查询函数
void SearchRepoInfo(Province *, int, char *, char *, char **);//媒体信息查询函数

//信息统计函数
void CountByCaseCharge(Province *, char **);//以主要罪名为条件分别统计历年来各种罪名贪腐案件的发生数、涉案金额，按案件发生数降序排序后，输出统计结果
void CountByCaseLevel(Province *, char *, char **);//以行政级别为条件分别统计某年度内各种行政级别贪腐案件的发生数，其中刑事处罚为死刑、无期徒刑、有期徒刑1-5年、有期徒刑6-10及有期徒刑11年以上的案件分别是多少起
void CountByCaseProv(Province *, char *, char *);//以案件发生地所属省份为条件分别统计某个时间段内各省份贪腐案件的发生数，涉案金额总数，按案件发生数降序排序后输出统计结果
void CountByRepoNum(Province *, char **);//统计媒体报道数最多的10个贪腐案件，按报道数降序排序后输出案件编号、被告行政级别、主要罪名、涉案金额、刑事处罚和媒体报道次数
void CountByLevelCharge(Province *, char **);//以行政级别为条件统计各主要罪名案件数量

//界面函数
BOOL ShowModule(char **, int);//简单界面模板
BOOL ExeFunction(int, int);//执行由主菜单号和子菜单号确定的功能函数
void ClearScreen(void);//清除屏幕信息
void ShowMenu(void);//显示主菜单
void ShowState(void);
void TagMainMenu(int);//在指定主菜单项上置选中标志
void PopOff(void);//关闭顶层弹出窗口, 恢复覆盖区域原外观和字符单元原属性
void PopMenu(int);//弹出指定主菜单项对应的子菜单
void TagSubMenu(int);//在指定子菜单项上做选中标记
void LocSubMenu(int, SMALL_RECT *);//计算弹出子菜单区域左上角和右下角的位置
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);//在指定区域输出弹出窗口信息, 同时设置热区, 将弹出窗口位置信息入栈
void DrawBox(SMALL_RECT *);//在指定区域画边框
void SetHotPoint(HOT_AREA *, int);//设置热区激活与未激活的状态
void InitInterface(void);//初始化界面
void RunSys(Province **);//运行系统, 在系统主界面下运行用户所选择的功能模块
int DealInput(HOT_AREA *, int *);//在弹出窗口区域设置热区, 等待并相应用户输入

//菜单项对应功能面板
BOOL SysSaveInfo(void);//数据保存
BOOL SysBackupInfo(void);//数据备份
BOOL SysRestoreInfo(void);//数据恢复
BOOL ExitSys(void);//退出
BOOL MaintainProvInfo(void);//省份信息录入、修改、删除
BOOL MaintainCaseInfo(void);//案件信息录入、修改、删除
BOOL MaintainRepoInfo(void);//媒体信息录入、修改、删除
BOOL SysSearchProvInfo(void);//省份信息查询
BOOL SysSearchCaseInfo(void);//案件信息查询
BOOL SysSearchRepoInfo(void);//媒体信息查询
BOOL SysCountByCaseName(void);//按主要罪名统计
BOOL SysCountByCaseLevel(void);//按行政级别统计刑事处罚
BOOL SysCountByCaseProv(void);//按案件发生地所属省份统计
BOOL SysCountByRepoNum(void);//按媒体报道数量统计
BOOL SysCountLevelCharge(void);//按行政级别统计主要罪名
BOOL HelpTopic(void);//帮助主题
BOOL About(void);//关于
BOOL ExeFunction(int, int);//执行由主菜单号和子菜单号确定的功能函数

//功能界面函数相关
void DealString(char *);//处理从屏幕上读的字符串，加\0
void PanelInputProvInfo(void);//用于录入省份信息的窗口
void PanelChangeProvInfo(void);//用于修改省份信息的窗口
void PanelChangeProvInfo1(char **);//用于修改省份信息中输入信息的窗口
void PanelDeleteProvInfo(void);//用于删除省份信息的窗口
void PanelInputCaseInfo(void);//用于录入案件信息的窗口
void PanelChangeCaseInfo(void);//用于修改案件信息的窗口
void PanelChangeCaseInfo1(char **);//用于输入修改案件信息的窗口
void PanelDeleteCaseInfo(void);//用于删除案件信息的窗口
void PanelInputRepoInfo(void);//用于录入媒体信息的窗口
void PanelChangeRepoInfo(void);//用于修改媒体信息的窗口
void PanelChangeRepoInfo1(char **);//用于输入修改媒体信息的窗口
void PanelDeleteRepoInfo(void);//用于删除媒体信息的窗口
void PanelSearchProvInfoByProv(void);//用于按省份名称搜索省份信息的窗口
void PanelSearchProvInfoByLeader(void);//用于按负责人名称搜索省份信息的窗口
void PanelSearchCaseInfoById(void);//用于按案件编号搜索案件信息的窗口
void PanelSearchCaseInfoByNL(void);//用于按被告姓名和行政级别搜索案件信息的窗口
void PanelSearchRepoInfoByIF(void);//用于按案件编号和媒体名称搜索媒体信息的窗口
void PanelSearchRepoInfoByDF(void);//用于按报道日期和媒体名称搜索媒体信息的窗口

//测试函数
int TestCase(char *);//测试案件信息是否存在
int TestProv(char *);//测试省份信息是否存在
int TestProvForChange(char *,char **);//测试省份信息是否存在并传出省份信息
int TestCaseForChange(char *,char **);//测试案件信息是否存在并传出信息
int TestRepoForChange(char *,char **);//测试媒体信息是否存在并传出信息
int TestRepo(char *);//测试媒体信息是否存在
int TestLeader(char *);//按省份负责人测试省份信息是否存在
int TestYear(char *str);//测试某年份案件信息是否存在
int TestBEDate(char *,char *);//测试某时间段案件信息是否存在
int TestNL(char *, char);//按被告姓名和行政级别测试案件信息是否存在
int TestRepoByIF(char *, char *);//按案件编号和媒体名称来测试媒体信息是否存在
int TestRepoByDF(char *, char *);//按报道日期和媒体名称来测试媒体信息是否存在

#endif // _HEAD_H_
