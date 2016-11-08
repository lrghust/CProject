#include"head.h"
/**
 * 函数名称: PanelInputRepoInfo
 * 函数功能: 显示录入媒体信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelInputRepoInfo(void)//用于录入媒体信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           "            ",//12
                           "报道编号",
                           "              ",//14
                           "报道日期",
						   "          ",//10
                           "媒体类别",
"报纸","广播","电视","互联网",
                           "媒体名称",
                           "                    ",//20
                           "内容索引",
"                                                 ",//50
                           "确定"
                          };
    char **pString=plabel_name;
	int n=16;
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

    pos.X = 70;
    pos.Y = n + 1;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X ;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<=6; i+=2) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 1 + i;

        aLoc[i+1].X = aLoc[i].X+10;
        aLoc[i+1].Y = aLoc[i].Y;
    }
    for(i=8;i<=10;i++)
    {
        aLoc[i].X=aLoc[i-1].X+7;
        aLoc[i].Y=aLoc[i-1].Y;
    }
    aLoc[i].X = rcPop.Left + 3;
    aLoc[i].Y = rcPop.Top + 1 + 8;
    for(i=12;i<=14;i++)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = aLoc[i-1].Y+1;
    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = (rcPop.Left + rcPop.Right)/2-1 ;//+ (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-2].Y + 4;

    labels.pLoc = aLoc;

    areas.num = 10;
    SMALL_RECT aArea[] = { {aLoc[1].X, aLoc[1].Y,aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,aLoc[3].X + 14, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,aLoc[5].X + 10, aLoc[5].Y},
						   {aLoc[7].X, aLoc[7].Y,aLoc[7].X + 3, aLoc[7].Y},
						   {aLoc[8].X, aLoc[8].Y,aLoc[8].X + 3, aLoc[8].Y},
                           {aLoc[9].X, aLoc[9].Y,aLoc[9].X + 3, aLoc[9].Y},
                           {aLoc[10].X, aLoc[10].Y,aLoc[10].X + 5, aLoc[10].Y},
                           {aLoc[12].X, aLoc[12].Y,aLoc[12].X + 20, aLoc[12].Y},
                           {aLoc[14].X, aLoc[14].Y,aLoc[14].X + 50, aLoc[14].Y},
                           {aLoc[15].X, aLoc[15].Y,aLoc[15].X + 3, aLoc[15].Y},
                         };

    char aSort[] = {1,1,1,0,0,0,0,1,1,0};
    char aTag[10];
    int k;
    for(k=0;k<10;k++)
        aTag[k]=k+1;

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
    COORD record1={0,0};
    int flag1=0;
    char *input[6];
    char field;
    input[3]=&field;

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
            else if(vkc==13&&(*piHot>=4&&*piHot<=7))//4 行政级别
            {
                if(flag1)
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record1,&ul);
                }
                COORD pos1={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos1,&ul);
                record1=pos1;
                flag1=1;
                field=*piHot-4+'1';

                num=8;
                if (num > 0 && num <= pHotArea->num)//回车后跳转下一信息框
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if ((vkc == 13 || vkc == 32)&&*piHot==10)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char caseid[13],id[15],date[11],firm[21],index[51];
                input[0]=caseid;
                input[1]=id;
                input[2]=date;
                input[4]=firm;
                input[5]=index;
                ReadConsoleOutputCharacter(gh_std_out,caseid,13,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,id,15,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,date,11,aLoc[5],&ul);
                ReadConsoleOutputCharacter(gh_std_out,firm,21,aLoc[12],&ul);
                ReadConsoleOutputCharacter(gh_std_out,index,51,aLoc[14],&ul);
                DealString(caseid);
                DealString(id);
                DealString(date);
                DealString(firm);
                DealString(index);
                PopOff();
                if(input[0][0]=='\0'||input[1][0]=='\0'||input[2][0]=='\0'||input[4][0]=='\0'||input[5][0]=='\0')
                {
                    char *plabel_name[] = {"输入信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(TestRepo(id))
                {
                    char *plabel_name[] = {"媒体信息已存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestCase(caseid))
                {
                    char *plabel_name[] = {"案件信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    InputRepoInfo(head,input);
                    char *plabel_name[] = {"录入成功！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
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
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    PopOff();
}

/**
 * 函数名称: PanelChangeRepoInfo
 * 函数功能: 显示修改媒体信息的窗口，输入报道编号.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelChangeRepoInfo(void)//用于修改媒体信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"报道编号",
                           "              ",//14
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
                           aLoc[1].X + 14, aLoc[1].Y},
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
                char repoid[15],caseid[13],date[11],firm[21],index[51],field;
                char *output[]={caseid,repoid,date,firm,index,&field};
                ReadConsoleOutputCharacter(gh_std_out,repoid,15,aLoc[1],&ul);
                DealString(repoid);
                if(!TestRepoForChange(repoid,output))//不存在这个报道
                {
                    PopOff();
                    char *plabel_name[] = {"媒体信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else//存在这个报道
                {
                    PopOff();
                    PanelChangeRepoInfo1(output);
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
 * 函数名称: PanelChangeRepoInfo1
 * 函数功能: 显示供用户输入媒体修改信息的窗口.
 * 输入参数: match 用户输入的报道编号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelChangeRepoInfo1(char **str)//用于输入修改媒体信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"案件编号",
                           str[0],//12
                           "报道编号",
                           str[1],//14
                           "报道日期",
						   str[2],//10
                           "媒体类别",
                "报纸","广播","电视","互联网",
                           "媒体名称",
                           str[3],//20
                           "内容索引",
                           str[4],//50
                           "确定"
                          };
    char **pString=plabel_name;
	int n=16;
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

    pos.X = 70;
    pos.Y = n + 1;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X ;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y;

    att =  BACKGROUND_GREEN ;  /*绿底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<=6; i+=2) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 1 + i;

        aLoc[i+1].X = aLoc[i].X+10;
        aLoc[i+1].Y = aLoc[i].Y;
    }
    for(i=8;i<=10;i++)
    {
        aLoc[i].X=aLoc[i-1].X+7;
        aLoc[i].Y=aLoc[i-1].Y;
    }
    aLoc[i].X = rcPop.Left + 3;
    aLoc[i].Y = rcPop.Top + 1 + 8;
    for(i=12;i<=14;i++)
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = aLoc[i-1].Y+1;
    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = (rcPop.Left + rcPop.Right)/2-1 ;//+ (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-2].Y + 4;

    labels.pLoc = aLoc;

    areas.num = 10;
    SMALL_RECT aArea[] = { {aLoc[1].X, aLoc[1].Y,aLoc[1].X + 12, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,aLoc[3].X + 14, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,aLoc[5].X + 10, aLoc[5].Y},
						   {aLoc[7].X, aLoc[7].Y,aLoc[7].X + 3, aLoc[7].Y},
						   {aLoc[8].X, aLoc[8].Y,aLoc[8].X + 3, aLoc[8].Y},
                           {aLoc[9].X, aLoc[9].Y,aLoc[9].X + 3, aLoc[9].Y},
                           {aLoc[10].X, aLoc[10].Y,aLoc[10].X + 5, aLoc[10].Y},
                           {aLoc[12].X, aLoc[12].Y,aLoc[12].X + 20, aLoc[12].Y},
                           {aLoc[14].X, aLoc[14].Y,aLoc[14].X + 50, aLoc[14].Y},
                           {aLoc[15].X, aLoc[15].Y,aLoc[15].X + 3, aLoc[15].Y},
                         };

    char aSort[] = {1,1,1,0,0,0,0,1,1,0};
    char aTag[10];
    int k;
    for(k=0;k<10;k++)
        aTag[k]=k+1;

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
    COORD record1={0,0};
    int flag1=1;
    char *input[6];
    char field=*str[5];
    input[3]=&field;

    record1=aLoc[7+*str[5]-'1'];
    record1.X--;
    FillConsoleOutputCharacter(gh_std_out, '*', 1 , record1 , &ul);

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
            else if(vkc==13&&(*piHot>=4&&*piHot<=7))//4 媒体类别
            {
                if(flag1)
                {
                    FillConsoleOutputCharacter(gh_std_out,' ',1,record1,&ul);
                }
                COORD pos1={pHotArea->pArea[*piHot-1].Left-1,pHotArea->pArea[*piHot-1].Top};
                FillConsoleOutputCharacter(gh_std_out,'*',1,pos1,&ul);
                record1=pos1;
                flag1=1;
                field=*piHot-4+'1';

                num=8;
                if (num > 0 && num <= pHotArea->num)//回车后跳转下一信息框
                {
                    *piHot = num;
                    SetHotPoint(pHotArea, *piHot);
                }
            }
            else if ((vkc == 13 || vkc == 32)&&*piHot==10)
            {  /*回车键或空格表示按下确定*/
                //iRet = 13;
                char caseid[13],id[15],date[11],firm[21],index[51];
                input[0]=caseid;
                input[1]=id;
                input[2]=date;
                input[4]=firm;
                input[5]=index;
                ReadConsoleOutputCharacter(gh_std_out,caseid,13,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,id,15,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,date,11,aLoc[5],&ul);
                ReadConsoleOutputCharacter(gh_std_out,firm,21,aLoc[12],&ul);
                ReadConsoleOutputCharacter(gh_std_out,index,51,aLoc[14],&ul);
                DealString(caseid);
                DealString(id);
                DealString(date);
                DealString(firm);
                DealString(index);
                PopOff();
                if(caseid[0]=='\0'||id[0]=='\0'||date[0]=='\0'||firm[0]=='\0'||index[0]=='\0'||field==0)
                {
                    char *plabel_name[] = {"信息不完整或有误！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(!TestCase(caseid))
                {
                    char *plabel_name[] = {"案件信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    ChangeRepoInfo(head,str[1],input);
                    char *plabel_name[] = {"修改成功！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
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
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    PopOff();
}

/**
 * 函数名称: PanelDeleteRepoInfo
 * 函数功能: 显示删除媒体信息的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PanelDeleteRepoInfo(void)//用于删除媒体信息的窗口
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"报道编号",
                           "              ",//14
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
                           aLoc[1].X + 14, aLoc[1].Y},
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
                char id[15];
                ReadConsoleOutputCharacter(gh_std_out,id,15,aLoc[1],&ul);
                DealString(id);
                PopOff();
                if(!TestRepo(id))
                {
                    char *plabel_name[] = {"媒体信息不存在！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    DeleteRepoInfo(head,id);
                    char *plabel_name[] = {"删除成功！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 3);
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
