#include"head.h"
/**
 * 函数名称: PanelSearchProvInfoByProv
 * 函数功能: 显示按省份名称搜索省份信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelSearchProvInfoByProv(void)//用于按省份名称搜索省份信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"省份名称",
                           "        ",
                           "确认"
                          };
    char **pString=plabel_name;
	int n=3;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 8, aLoc[1].Y},
						   {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 3, aLoc[2].Y}
                           };

    char aSort[] = {1,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow; //iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char temp[9];
                ReadConsoleOutputCharacter(gh_std_out,temp,9,aLoc[1],&ul);
                DealString(temp);
                PopOff();
                if(temp[0]=='\0')
                {
                    char *plabel_name[] = {"输入的信息为空或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestProv(temp))
                {
                    char *plabel_name[] = {"省份信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    char *output[3];
                    char prov[100],leader[100],tel[100];
                    output[0]=prov;
                    output[1]=leader;
                    output[2]=tel;
                    SearchProvInfo(head,1,temp,output);
                    char *plabel_name[] = {output[0],
                                           output[1],
                                           output[2],
                                           "确定"
                                          };
                    ShowModule(plabel_name, 4);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * 函数名称: PanelSearchProvInfoByLeader
 * 函数功能: 显示按负责人名称搜索省份信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelSearchProvInfoByLeader(void)//用于按负责人名称搜索省份信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"负责人名称",
                           "               ",//15
                           "确认"
                          };
    char **pString=plabel_name;
	int n=3;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 15, aLoc[1].Y},
						   {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 3, aLoc[2].Y}
                           };

    char aSort[] = {1,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow; //iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char temp[16];
                ReadConsoleOutputCharacter(gh_std_out,temp,16,aLoc[1],&ul);
                DealString(temp);
                PopOff();
                if(temp[0]=='\0')
                {
                    char *plabel_name[] = {"输入的信息为空或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestLeader(temp))
                {
                    char *plabel_name[] = {"省份信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    char *output[3];
                    char prov[100],leader[100],tel[100];
                    output[0]=prov;
                    output[1]=leader;
                    output[2]=tel;
                    SearchProvInfo(head,2,temp,output);
                    char *plabel_name[] = {output[0],
                                           output[1],
                                           output[2],
                                           "确定"
                                          };
                    ShowModule(plabel_name, 4);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * 函数名称: PanelSearchCaseInfoById
 * 函数功能: 显示按案件编号搜索案件信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelSearchCaseInfoById(void)//用于按案件编号搜索案件信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           "            ",//12
                           "确认"
                          };
    char **pString=plabel_name;
	int n=3;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 3, aLoc[2].Y}
                           };

    char aSort[] = {1,0};
    char aTag[] = {1,2};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow; //iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char temp[13];
                ReadConsoleOutputCharacter(gh_std_out,temp,13,aLoc[1],&ul);
                DealString(temp);
                PopOff();
                if(temp[0]=='\0')
                {
                    char *plabel_name[] = {"输入的信息为空或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestCase(temp))
                {
                    char *plabel_name[] = {"案件信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    char prov[100],id[100],date[100],name[100],level[100],charge[100],money[100],judge[100];
                    char *output[8]={prov,id,date,name,level,charge,money,judge};
                    SearchCaseInfo(head,1,temp,' ',output);
                    char *plabel_name[] = {output[1],
                                           output[2],
                                           output[0],
                                           output[3],
                                           output[4],
                                           output[5],
                                           output[6],
                                           output[7],
                                           "确定"
                                          };
                    ShowModule(plabel_name, 9);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * 函数名称: PanelSearchCaseInfoByNL
 * 函数功能: 显示按被告姓名和行政级别搜索案件信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelSearchCaseInfoByNL(void)//用于按被告姓名和行政级别搜索案件信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"被告姓名",
                           "               ",//15
                           "行政级别",
"副科级","正科级","副处级","正处级","副厅级","正厅级","副部级","正部级及以上",
                           "确认"
                          };
    char **pString=plabel_name;
	int n=12;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = 8;
    rcPop.Left = (SCR_COL - pos.X) / 2-10;
    rcPop.Right = rcPop.Left + pos.X - 1+50;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1+2;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<4; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    for (i=4; i<11; i++) {
        aLoc[i].X = aLoc[i-1].X+8;
        aLoc[i].Y = aLoc[i-1].Y;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + (maxlen-str_len)/2+25;
    aLoc[n-1].Y = aLoc[n-2].Y +2;

    labels.pLoc = aLoc;

    areas.num = 10;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 15, aLoc[1].Y},
                           {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 5, aLoc[3].Y},
						   {aLoc[4].X, aLoc[4].Y,
                           aLoc[4].X + 5, aLoc[4].Y},
                           {aLoc[5].X, aLoc[5].Y,
                           aLoc[5].X + 5, aLoc[5].Y},
                           {aLoc[6].X, aLoc[6].Y,
                           aLoc[6].X + 5, aLoc[6].Y},
						   {aLoc[7].X, aLoc[7].Y,
                           aLoc[7].X + 5, aLoc[7].Y},
                           {aLoc[8].X, aLoc[8].Y,
                           aLoc[8].X + 5, aLoc[8].Y},
                           {aLoc[9].X, aLoc[9].Y,
                           aLoc[9].X + 5, aLoc[9].Y},
                           {aLoc[10].X, aLoc[10].Y,
                           aLoc[10].X + 11, aLoc[10].Y},
						   {aLoc[11].X, aLoc[11].Y,
                           aLoc[11].X + 3, aLoc[11].Y}
                           };

    char aSort[] = {1,0,0,0,0,0,0,0,0,0};
    char aTag[] = {1,2,3,4,5,6,7,8,9,10};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = aLoc[n-1].Y-1;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow; //iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    char tempc=0;//记录行政级别
    COORD record1={0,0};
    int flag1=0;

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if(vkc==13&&(*piHot>=2&&*piHot<=9))//行政级别
            {
                if(flag1)
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record1,&ul);
                }
                COORD pos1={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos1,&ul);
                record1=pos1;
                flag1=1;
                tempc=*piHot-2+'A';

                num=10;
                if (num > 0 && num <= pHotArea->num)
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if ((vkc == 13 || vkc == 32)&&*piHot==10)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char temp1[16];
                //char temp2[11];
                ReadConsoleOutputCharacter(gh_std_out,temp1,16,aLoc[1],&ul);
                //ReadConsoleOutputCharacter(gh_std_out,temp2,11,aLoc[3],&ul);
                DealString(temp1);
                //DealString(temp2);
                //DealLevel(temp2);
                PopOff();
                if(temp1[0]=='\0'||tempc==0)
                {
                    char *plabel_name[] = {"信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestNL(temp1,tempc))
                {
                    char *plabel_name[] = {"案件信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    char prov[100],id[100],date[100],name[100],level[100],charge[100],money[100],judge[100];
                    char *output[8]={prov,id,date,name,level,charge,money,judge};
                    SearchCaseInfo(head,2,temp1,tempc,output);
                    char *plabel_name[] = {output[1],
                                           output[2],
                                           output[0],
                                           output[3],
                                           output[4],
                                           output[5],
                                           output[6],
                                           output[7],
                                           "确定"
                                          };
                    ShowModule(plabel_name, 9);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * 函数名称: PanelSearchRepoInfoByIF
 * 函数功能: 显示按案件编号和媒体名称搜索媒体信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelSearchRepoInfoByIF(void)//用于按案件编号和媒体名称搜索媒体信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           "            ",//12
                           "媒体名称",
                           "                    ",//20
                           "确认"
                          };
    char **pString=plabel_name;
	int n=5;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 3;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 20, aLoc[3].Y},
                           {aLoc[4].X, aLoc[4].Y,
                           aLoc[4].X + 3, aLoc[4].Y}
                           };

    char aSort[] = {1,1,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow; //iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char temp1[13];
                char temp2[21];
                ReadConsoleOutputCharacter(gh_std_out,temp1,13,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,temp2,21,aLoc[3],&ul);
                DealString(temp1);
                DealString(temp2);
                PopOff();
                if(temp1[0]=='\0'||temp2[0]=='\0')
                {
                    char *plabel_name[] = {"信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestRepoByIF(temp1,temp2))
                {
                    char *plabel_name[] = {"媒体信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    char caseid[100],id[100],date[100],firm[100],index[100],field[100];
                    char *output[8]={caseid,id,date,firm,index,field};
                    SearchRepoInfo(head,1,temp1,temp2,output);
                    char *plabel_name[] = {output[0],
                                           output[1],
                                           output[2],
                                           output[3],
                                           output[4],
                                           output[5],
                                           "确定"
                                          };
                    ShowModule(plabel_name, 7);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}

/**
 * 函数名称: PanelSearchRepoInfoByDF
 * 函数功能: 显示按报道日期和媒体名称搜索媒体信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelSearchRepoInfoByDF(void)//用于按报道日期和媒体名称搜索媒体信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"报道日期",
                           "          ",//10
                           "媒体名称",
                           "                    ",//20
                           "确认"
                          };
    char **pString=plabel_name;
	int n=5;
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 3;
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 10, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 20, aLoc[3].Y},
                           {aLoc[4].X, aLoc[4].Y,
                           aLoc[4].X + 3, aLoc[4].Y}
                           };

    char aSort[] = {1,1,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;//iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    //iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char temp1[11];
                char temp2[21];
                ReadConsoleOutputCharacter(gh_std_out,temp1,11,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,temp2,21,aLoc[3],&ul);
                DealString(temp1);
                DealString(temp2);
                PopOff();
                if(temp1[0]=='\0'||temp2[0]=='\0')
                {
                    char *plabel_name[] = {"信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestRepoByDF(temp1,temp2))
                {
                    char *plabel_name[] = {"媒体信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    char caseid[100],id[100],date[100],firm[100],index[100],field[100];
                    char *output[8]={caseid,id,date,firm,index,field};
                    SearchRepoInfo(head,2,temp1,temp2,output);
                    char *plabel_name[] = {output[0],
                                           output[1],
                                           output[2],
                                           output[3],
                                           output[4],
                                           output[5],
                                           "确定"
                                          };
                    ShowModule(plabel_name, 7);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*文本框回车键表示到下一热区*/
                num=*piHot;
                num++;

                if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
            }
            else
            {
                CONSOLE_SCREEN_BUFFER_INFO bInfo;
                GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
                if(vkc==8)//退格
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//改变光标位置
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//设置光标位置
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//字符置为空格
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//显示字符
                    bInfo.dwCursorPosition.X++;//改变光标位置
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}
