#include"head.h"
/**
 * 函数名称: 17个菜单项界面函数统一说明，名称见函数定义
 * 函数功能: 显示对应菜单项的窗口.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: bRet 仅在执行函数ExitSys时, 才可能返回FALSE, 其他情况下总是返回TRUE
 *
 * 调用说明:
 */

BOOL SysSaveInfo(void)
{
    BOOL bRet = TRUE;
    SaveInfo(head);
    char *plabel_name[] = {"保存成功！",
                           "确定"
                          };
    ShowModule(plabel_name, 2);
    return bRet;
}
BOOL SysBackupInfo(void)
{
    BOOL bRet = TRUE;
    BackupInfo(head);
    char *plabel_name[] = {"备份成功！",
                           "确定"
                          };
    ShowModule(plabel_name, 2);
    return bRet;
}
BOOL SysRestoreInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"请输入文件路径",
                           "                    ",//20
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
                           aLoc[1].X + 20, aLoc[1].Y},
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
    int num, arrow;
    //int iRet = 0;
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
                char path[21];
                ReadConsoleOutputCharacter(gh_std_out,path,21,aLoc[1],&ul);
                DealString(path);
                PopOff();
                if(path[0]=='\0')
                {
                    char *plabel_name[] = {"路径为空！",
                                           "确定"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else RestoreInfo(&head,path);
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
    //PopOff();
    return bRet;
}
BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"确认退出系统吗？", "确定    取消"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_GREEN ;
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        SaveInfo(head);//自动保存
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}

BOOL MaintainProvInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"录入省份信息",
                           "修改省份信息",
                           "删除省份信息",
                           "关闭"
                          };
    //ShowModule(plabel_name, 2);
    char **pString=plabel_name;
    int n=4;
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {  //确定最大宽度
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;                  //设置小窗口大小
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

    areas.num = 4;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                           aLoc[0].X + 11, aLoc[0].Y},
                           {aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X+ 11, aLoc[1].Y},
                            {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 11, aLoc[2].Y},
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X+ 3, aLoc[n-1].Y}
                           };

    char aSort[] = {0,0,0,0};
    char aTag[] = {1,2,3,4};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    //DealInput(&areas, &iHot);
    //处理操作
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
                if (cSort == 0&&cTag==1)
                {
                    //iRet = 13;
                    PopOff();
                    PanelInputProvInfo();
                    break;
                }
                else if (cSort == 0&&cTag==2)
                {
                    //iRet = 13;
                    PopOff();
                    PanelChangeProvInfo();
                    break;
                }
                else if (cSort == 0&&cTag==3)
                {
                    //iRet = 13;
                    PopOff();
                    PanelDeleteProvInfo();
                    break;
                }
                else if (cSort == 0&&cTag==4)
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
            else if (vkc == 13 &&*piHot==1)//若按下第一个按钮 录入
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelInputProvInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==2)//若按下第二个按钮 修改
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelChangeProvInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==3)//若按下第三个按钮 删除
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelDeleteProvInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==4)//若按下第四个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
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
    //ShowModule(plabel_name, 4);
    return bRet;
}
BOOL MaintainCaseInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"录入案件信息",
                           "修改案件信息",
                           "删除案件信息",
                           "关闭"
                          };
    //ShowModule(plabel_name, 2);
    char **pString=plabel_name;
    int n=4;
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {  //确定最大宽度
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;                  //设置小窗口大小
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

    areas.num = 4;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                           aLoc[0].X + 11, aLoc[0].Y},
                           {aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X+ 11, aLoc[1].Y},
                            {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 11, aLoc[2].Y},
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X+ 3, aLoc[n-1].Y}
                           };

    char aSort[] = {0,0,0,0};
    char aTag[] = {1,2,3,4};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    //DealInput(&areas, &iHot);
    //处理操作
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
                if (cSort == 0&&cTag==1)
                {
                    //iRet = 13;
                    PopOff();
                    PanelInputCaseInfo();
                    break;
                }
                else if (cSort == 0&&cTag==2)
                {
                    //iRet = 13;
                    PopOff();
                    PanelChangeCaseInfo();
                    break;
                }
                else if (cSort == 0&&cTag==3)
                {
                    //iRet = 13;
                    PopOff();
                    PanelDeleteCaseInfo();
                    break;
                }
                else if (cSort == 0&&cTag==4)
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
            else if (vkc == 13 &&*piHot==1)//若按下第一个按钮 录入
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelInputCaseInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==2)//若按下第二个按钮 修改
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelChangeCaseInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==3)//若按下第三个按钮 删除
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelDeleteCaseInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==4)//若按下第四个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
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
    //ShowModule(plabel_name, 4);
    return bRet;
}
BOOL MaintainRepoInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"录入媒体信息",
                           "修改媒体信息",
                           "删除媒体信息",
                           "关闭"
                          };
    //ShowModule(plabel_name, 2);
    char **pString=plabel_name;
    int n=4;
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {  //确定最大宽度
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;                  //设置小窗口大小
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

    areas.num = 4;
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                           aLoc[0].X + 11, aLoc[0].Y},
                           {aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X+ 11, aLoc[1].Y},
                            {aLoc[2].X, aLoc[2].Y,
                           aLoc[2].X + 11, aLoc[2].Y},
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X+ 3, aLoc[n-1].Y}
                           };

    char aSort[] = {0,0,0,0};
    char aTag[] = {1,2,3,4};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    //DealInput(&areas, &iHot);
    //处理操作
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
                if (cSort == 0&&cTag==1)
                {
                    //iRet = 13;
                    PopOff();
                    PanelInputRepoInfo();
                    break;
                }
                else if (cSort == 0&&cTag==2)
                {
                    //iRet = 13;
                    PopOff();
                    PanelChangeRepoInfo();
                    break;
                }
                else if (cSort == 0&&cTag==3)
                {
                    //iRet = 13;
                    PopOff();
                    PanelDeleteRepoInfo();
                    break;
                }
                else if (cSort == 0&&cTag==4)
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
            else if (vkc == 13 &&*piHot==1)//若按下第一个按钮 录入
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelInputRepoInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==2)//若按下第二个按钮 修改
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelChangeRepoInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==3)//若按下第三个按钮 删除
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelDeleteRepoInfo();
                break;
            }
            else if (vkc == 13 &&*piHot==4)//若按下第四个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
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
    //ShowModule(plabel_name, 4);
    return bRet;
}

BOOL SysSearchProvInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"按省份名称搜索",
                           "按省份负责人搜索",
                           "关闭"
                          };
    //ShowModule(plabel_name, 2);
    char **pString=plabel_name;
    int n=3;
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {  //确定最大宽度
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;                  //设置小窗口大小
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
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                           aLoc[0].X + 14, aLoc[0].Y},
                           {aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X+ 16, aLoc[1].Y},
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X+ 3, aLoc[n-1].Y}
                           };

    char aSort[] = {0,0,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    //DealInput(&areas, &iHot);
    //处理操作
    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;// iRet = 0;
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
                if (cSort == 0&&cTag==1)
                {
                    //iRet = 13;
                    PopOff();
                    PanelSearchProvInfoByProv();
                    break;
                }
                else if (cSort == 0&&cTag==2)
                {
                    //iRet = 13;
                    PopOff();
                    PanelSearchProvInfoByLeader();
                    break;
                }
                else if (cSort == 0&&cTag==3)
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
            else if (vkc == 13 &&*piHot==1)//若按下第一个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelSearchProvInfoByProv();
                break;
            }
            else if (vkc == 13 &&*piHot==2)//若按下第二个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelSearchProvInfoByLeader();
                break;
            }
            else if (vkc == 13 &&*piHot==3)//若按下第三个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
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
    //ShowModule(plabel_name, 4);
    return bRet;
}
BOOL SysSearchCaseInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"按案件编号搜索",
                           "按被告姓名和行政级别搜索",
                           "关闭"
                          };
    //ShowModule(plabel_name, 2);
    char **pString=plabel_name;
    int n=3;
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {  //确定最大宽度
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;                  //设置小窗口大小
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
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                           aLoc[0].X + 14, aLoc[0].Y},
                           {aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X+ 24, aLoc[1].Y},
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X+ 3, aLoc[n-1].Y}
                           };

    char aSort[] = {0,0,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    //DealInput(&areas, &iHot);
    //处理操作
    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;// iRet = 0;
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
                if (cSort == 0&&cTag==1)
                {
                    //iRet = 13;
                    PopOff();
                    PanelSearchCaseInfoById();
                    break;
                }
                else if (cSort == 0&&cTag==2)
                {
                    //iRet = 13;
                    PopOff();
                    PanelSearchCaseInfoByNL();
                    break;
                }
                else if (cSort == 0&&cTag==3)
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
            else if (vkc == 13 &&*piHot==1)//若按下第一个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelSearchCaseInfoById();
                break;
            }
            else if (vkc == 13 &&*piHot==2)//若按下第二个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelSearchCaseInfoByNL();
                break;
            }
            else if (vkc == 13 &&*piHot==3)//若按下第三个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
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
    //ShowModule(plabel_name, 4);
    return bRet;
}
BOOL SysSearchRepoInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"按案件编号和媒体名称搜索",
                           "按报道日期和媒体名称搜索",
                           "关闭"
                          };
    //ShowModule(plabel_name, 2);
    char **pString=plabel_name;
    int n=3;
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {  //确定最大宽度
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;                  //设置小窗口大小
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
    SMALL_RECT aArea[] = {{aLoc[0].X, aLoc[0].Y,
                           aLoc[0].X + 24, aLoc[0].Y},
                           {aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X+ 24, aLoc[1].Y},
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X+ 3, aLoc[n-1].Y}
                           };

    char aSort[] = {0,0,0};
    char aTag[] = {1,2,3};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    //DealInput(&areas, &iHot);
    //处理操作
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
                if (cSort == 0&&cTag==1)
                {
                    //iRet = 13;
                    PopOff();
                    PanelSearchRepoInfoByIF();
                    break;
                }
                else if (cSort == 0&&cTag==2)
                {
                    //iRet = 13;
                    PopOff();
                    PanelSearchRepoInfoByDF();
                    break;
                }
                else if (cSort == 0&&cTag==3)
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
            else if (vkc == 13 &&*piHot==1)//若按下第一个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelSearchRepoInfoByIF();
                break;
            }
            else if (vkc == 13 &&*piHot==2)//若按下第二个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
                PopOff();
                PanelSearchRepoInfoByDF();
                break;
            }
            else if (vkc == 13 &&*piHot==3)//若按下第三个按钮
            {  /*回车键表示按下当前按钮*/
                //iRet = 13;
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
    //ShowModule(plabel_name, 4);
    return bRet;
}

BOOL SysCountByCaseName(void)
{
    BOOL bRet = TRUE;
    char crime1[100],crime2[100],crime3[100],crime4[100],crime5[100],crime6[100];
    char *output[6]={crime1,crime2,crime3,crime4,crime5,crime6};
    CountByCaseCharge(head,output);
    char *plabel_name[] = {"主要罪名    案件数目    涉案金额    ",
                           output[0],
                           output[1],
                           output[2],
                           output[3],
                           output[4],
                           output[5],
                           "确定"
                          };
    ShowModule(plabel_name, 8);
    return bRet;
}
BOOL SysCountByCaseLevel(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"年份",
                           "    ",//4
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
                           aLoc[1].X + 4, aLoc[1].Y},
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
                char year[5];
                ReadConsoleOutputCharacter(gh_std_out,year,5,aLoc[1],&ul);
                DealString(year);
                PopOff();
                if(year[0]=='\0')
                {
                    char *plabel_name[] = {"请输入信息！",
                                            "确定"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                if(!TestYear(year))
                {
                    char *plabel_name[] = {"该年份下无记录！",
                                            "确定"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                char level1[100],level2[100],level3[100],level4[100],level5[100],level6[100],level7[100],level8[100];
                char *output[]={level1,level2,level3,level4,level5,level6,level7,level8};
                CountByCaseLevel(head,year,output);
                char *plabel_name[] = {"行政级别      死刑        无期徒刑    有期徒刑1-5年    有期徒刑6-10年   有期徒刑11年以上   ",
                                        output[0],
                                        output[1],
                                        output[2],
                                        output[3],
                                        output[4],
                                        output[5],
                                        output[6],
                                        output[7],
                                        "确定"
                          };
                ShowModule(plabel_name, 10);
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
    return bRet;
}
BOOL SysCountByCaseProv(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"起始时间",
                           "        ",//8
                           "截止时间",
                           "        ",//8
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
                           aLoc[1].X + 8, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 8, aLoc[3].Y},
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
                char begin[9];
                char end[9];
                ReadConsoleOutputCharacter(gh_std_out,begin,9,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,end,9,aLoc[3],&ul);
                DealString(begin);
                DealString(end);
                PopOff();
                if(begin[0]=='\0'||end[0]=='\0')
                {
                    char *plabel_name[] = {"请输入完整信息！",
                                            "确定"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                if(!TestBEDate(begin,end))
                {
                    char *plabel_name[] = {"该时间段内无记录！",
                                            "确定"
                                          };
                    ShowModule(plabel_name, 2);
                    break;
                }
                CountByCaseProv(head,begin,end);
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
    return bRet;
}
BOOL SysCountByRepoNum(void)
{
    BOOL bRet = TRUE;
    char case1[1000],case2[1000],case3[1000],case4[1000],case5[1000],case6[1000],case7[1000],case8[1000],case9[1000],case10[1000];
    char *output[10]={case1,case2,case3,case4,case5,case6,case7,case8,case9,case10};
    CountByRepoNum(head,output);
    char *plabel_name[] = {"案件排序    案件编号    行政级别    主要罪名    涉案金额    刑事处罚      报道次数    ",
                           output[0],
                           output[1],
                           output[2],
                           output[3],
                           output[4],
                           output[5],
                           output[6],
                           output[7],
                           output[8],
                           output[9],
                           "确定"
                          };
    ShowModule(plabel_name, 12);
    return bRet;
}

BOOL SysCountLevelCharge(void)
{
    BOOL bRet = TRUE;
    char level1[100],level2[100],level3[100],level4[100],level5[100],level6[100],level7[100],level8[100];
    char *output[8]={level1,level2,level3,level4,level5,level6,level7,level8};
    CountByLevelCharge(head,output);
    char *plabel_name[] = {"行政级别\\主要罪名   受贿      贪污     挪用公款   渎职      滥用职权    其他",
                           output[0],
                           output[1],
                           output[2],
                           output[3],
                           output[4],
                           output[5],
                           output[6],
                           output[7],
                           "确定"
                          };
    ShowModule(plabel_name, 10);
    return bRet;
}

BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"欢迎与作者联系",
                           "邮箱：lrghust@gmail.com",
                           "确定"
                          };
    ShowModule(plabel_name, 3);
    return bRet;
}
BOOL About(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"作者：李睿光",
                           "华中科技大学计算机学院CSEE1501班",
                           "确定"
                          };
    ShowModule(plabel_name, 3);
    return bRet;
}
/**
 * 函数名称: ExeFunction
 * 函数功能: 执行由主菜单号和子菜单号确定的功能函数.
 * 输入参数: m 主菜单项号
 *           s 子菜单项号
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明: 仅在执行函数ExitSys时, 才可能返回FALSE, 其他情况下总是返回TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*函数指针数组，用来存放所有功能函数的入口地址*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*将功能函数入口地址存入与功能函数所在主菜单号和子菜单号对应下标的数组元素*/
    pFunction[0] = SysSaveInfo;
    pFunction[1] = SysBackupInfo;
    pFunction[2] = SysRestoreInfo;
    pFunction[3] = ExitSys;

    pFunction[4] = MaintainProvInfo;
    pFunction[5] = MaintainCaseInfo;
    pFunction[6] = MaintainRepoInfo;

    pFunction[7] = SysSearchProvInfo;
    pFunction[8] = SysSearchCaseInfo;
    pFunction[9] = SysSearchRepoInfo;

    pFunction[10] = SysCountByCaseName;
    pFunction[11] = SysCountByCaseLevel;
    pFunction[12] = SysCountByCaseProv;
    pFunction[13] = SysCountByRepoNum;
    pFunction[14] = SysCountLevelCharge;

    pFunction[15] = HelpTopic;
    pFunction[16] = About;

    for (i=1,loc=0; i<m; i++)  /*根据主菜单号和子菜单号计算对应下标*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*用函数指针调用所指向的功能函数*/
    }

    return bRet;
}
