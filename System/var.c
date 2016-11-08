#include"head.h"
char *ga_main_menu[] = {"文件(F)",             /*系统主菜单名*/
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计(S)",
                        "帮助(H)"
                       };

char *ga_sub_menu[] = {"[S] 数据保存",          /*系统子菜单名*/
                       "[B] 数据备份",
                       "[R] 数据恢复",
                       "[X] 退出    Alt+X",/*空串用来在弹出菜单中分隔子菜单项，下同*/
                       "[D] 省份信息",
                       "[P] 案件信息",
                       "[C] 媒体信息",
                       "[D] 省份信息查询",
                       "[P] 案件信息查询",
                       "[C] 媒体信息查询",
                       "[I] 按主要罪名统计",
                       "[T] 按行政级别统计刑事处罚",
                       "[C] 按案件发生地所属省份统计",
                       "[U] 按媒体报道数量统计",
                       "[L] 按行政级别统计主要罪名",
                       "[T] 帮助主题",
                       "[A] 关于..."
                      };
char *LEVEL[]={"副科级","正科级","副处级","正处级","副厅级","正厅级","副部级","正部级及以上"};
char *CHARGE[]={"受贿","贪污","挪用公款","渎职","滥用职权","其他"};
char *FIELD[]={"报纸","广播","电视","互联网"};

int ga_sub_menu_count[] = {4, 3, 3, 5, 2};  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/
CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/
char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/
HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/
LAYER_NODE *gp_top_layer = NULL;               /*弹出窗口信息链链头*/

unsigned long ul;
Province *head=NULL;
