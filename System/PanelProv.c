#include"head.h"
/**
 * ��������: PanelInputProvInfo
 * ��������: ��ʾ¼��ʡ����Ϣ�Ĵ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelInputProvInfo(void)//����¼��ʡ����Ϣ�Ĵ���
{
    char *plabel_name[] = {"ʡ������",       //���û�������Ϣ�Ĵ����ϵı�ǩ
                           "         ",
                           "����������",
						   "               ",
						   "��ϵ�绰",
						   "               ",
                           "ȷ��"
                          };
    char **pString=plabel_name;
	int n=7;//7����ǩ
	LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {//��ȡ���ǩ�����������ô����С
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }
    //���ô���λ�����С
    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  //�̵׺���
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];//���б�ǩ��λ��

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);//���һ��ȷ����λ��
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 4;//������
    //��������λ���������ĸ������λ��
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 9, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 15, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,
                           aLoc[5].X + 15, aLoc[5].Y},
						   {aLoc[6].X, aLoc[6].Y,
                           aLoc[6].X + 3, aLoc[6].Y}
                           };

    char aSort[] = {1,1,1,0};//�������� 1Ϊ�ı��� 0Ϊ��ť
    char aTag[] = {1,2,3,4};//�������

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);//��ʾ����

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);//�ú��߰�ȷ�������������

    HOT_AREA *pHotArea=&areas;
    int *piHot=&iHot;//����ָʾ��ǰ����������
    INPUT_RECORD inRec;
    DWORD res;
    pos.X=0;
    pos.Y=0;
    int num, arrow;
    int cNo, cTag, cSort;//cNo:���, cTag:�������, cSort: ��������
    char vkc, asc;       //vkc:���������, asc:�ַ���ASCII��ֵ

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    //ѭ����ÿ�δӼ��̻�ȡһ������
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&(inRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))
        {//���������¼�
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {//�����ť��ʾ����ȷ��������
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {//����Ǽ����¼�
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  //�����(���ϡ��ҡ���)�Ĵ���
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
                        *piHot = num;//���ݷ����ת����������
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  //ESC��������
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  //�س�����ո��ʾ����ȷ��
                char *input[3],prov[9],leader[16],tel[16];
                input[0]=prov;
                input[1]=leader;
                input[2]=tel;
                //���ı����ȡ�û�����
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,leader,16,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,tel,16,aLoc[5],&ul);
                //�����ַ�������\0
                DealString(prov);
                DealString(leader);
                DealString(tel);
                PopOff();
                if(input[0][0]=='\0'||input[1][0]=='\0'||input[2][0]=='\0')//����û����벻ȫ���ջ�����ǰ�пո��¸�ʽ����
                {
                    char *plabel_name[] = {"������Ϣ������������",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(TestProv(prov))//����
                {
                    char *plabel_name[] = {"ʡ����Ϣ�Ѵ��ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    InputProvInfo(head,input);
                    char *plabel_name[] = {"¼��ɹ���",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  //�ı���س�����ʾ����һ����
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
}
/**
 * ��������: PanelChangeProvInfo
 * ��������: ��ʾ�޸�ʡ����Ϣ�Ĵ��ڣ�����ʡ������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelChangeProvInfo(void)//�����޸�ʡ����Ϣ�Ĵ���
{
    char *plabel_name[] = {"ʡ������",
                           "        ",
                           "ȷ��"
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

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*�س�����ո��ʾ����ȷ��*/
                //iRet = 13;
                char prov[9],leader[16],tel[16];
                char *output[3]={prov,leader,tel};
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[1],&ul);
                DealString(prov);
                if(!TestProvForChange(prov,output))//���������ʡ��
                {
                    PopOff();
                    char *plabel_name[] = {"ʡ����Ϣ�����ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else//�������ʡ��
                {
                    PopOff();
                    PanelChangeProvInfo1(output);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    //PopOff();
}

/**
 * ��������: PanelChangeProvInfo1
 * ��������: ��ʾ���û�����ʡ���޸���Ϣ�Ĵ���.
 * �������: match �û������ʡ������
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelChangeProvInfo1(char **match)//�����޸�ʡ����Ϣ��������Ϣ�Ĵ���
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"ʡ������",
                           match[0],//8
                           "����������",
						   match[1],//15
						   "��ϵ�绰",
						   match[2],//15
                           "ȷ��"
                          };
    char **pString=plabel_name;
	int n=7;
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
    maxlen+=6;
    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    SMALL_RECT aArea[] = {{aLoc[1].X, aLoc[1].Y,
                           aLoc[1].X + 8, aLoc[1].Y},
						   {aLoc[3].X, aLoc[3].Y,
                           aLoc[3].X + 15, aLoc[3].Y},
						   {aLoc[5].X, aLoc[5].Y,
                           aLoc[5].X + 15, aLoc[5].Y},
						   {aLoc[6].X, aLoc[6].Y,
                           aLoc[6].X + 3, aLoc[6].Y}
                           };

    char aSort[] = {1,1,1,0};
    char aTag[] = {1,2,3,4};

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
    int num, arrow;// iRet = 0;
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*�س�����ո��ʾ����ȷ��*/
                //iRet = 13;
                char *input[3],prov[9],leader[16],tel[16];
                input[0]=prov;
                input[1]=leader;
                input[2]=tel;
                ReadConsoleOutputCharacter(gh_std_out,prov,9,aLoc[1],&ul);
                ReadConsoleOutputCharacter(gh_std_out,leader,16,aLoc[3],&ul);
                ReadConsoleOutputCharacter(gh_std_out,tel,16,aLoc[5],&ul);
                DealString(prov);
                DealString(leader);
                DealString(tel);
                PopOff();
                if(prov[0]=='\0'||leader[0]=='\0'||tel[0]=='\0')
                {
                    char *plabel_name[] = {"��Ϣ������������!",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else if(ChangeProvInfo(head,match[0],input)==1)
                {
                    char *plabel_name[] = {"�޸ĳɹ�!",
                                           "ԭʡ���°�����ý����Ϣ����ʧ��",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 3);
                }
                else
                {
                    char *plabel_name[] = {"�޸ĳɹ���",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                    //WriteConsole(gh_std_out,stdin,20,&ul,NULL);
                }
            }
        }
    }
    //PopOff();
}

/**
 * ��������: PanelDeleteProvInfo
 * ��������: ��ʾɾ��ʡ����Ϣ�Ĵ���.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PanelDeleteProvInfo(void)//����ɾ��ʡ����Ϣ�Ĵ���
{
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"ʡ������",
                           "        ",
                           "ȷ��"
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

    att =  BACKGROUND_GREEN ;  /*�̵׺���*/
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
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                //iRet = 27;
                break;
            }
            else if ((vkc == 13 || vkc == 32)&&pHotArea->pSort[*piHot-1]==0)
            {  /*�س�����ո��ʾ����ȷ��*/
                //iRet = 13;
                char prov[9];
                ReadConsoleOutputCharacter(gh_std_out,prov,8,aLoc[1],&ul);
                DealString(prov);
                PopOff();
                if(!TestProv(prov))
                {
                    char *plabel_name[] = {"ʡ����Ϣ�����ڣ�",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 2);
                }
                else
                {
                    DeleteProvInfo(head,prov);
                    char *plabel_name[] = {"ɾ���ɹ���",
                                           "ԭʡ���°�����ý����Ϣ����ʧ��",
                                           "ȷ��"
                                          };
                    ShowModule(plabel_name, 3);
                }
                break;
            }
            else if (vkc == 13&&pHotArea->pSort[*piHot-1]==1)
            {  /*�ı���س�����ʾ����һ����*/
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
                if(vkc==8)//�˸�
                {
                    if(bInfo.dwCursorPosition.X>pHotArea->pArea[*piHot-1].Left)
                    {
                        bInfo.dwCursorPosition.X--;//�ı���λ��
                        SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);//���ù��λ��
                        FillConsoleOutputCharacter(gh_std_out,' ',1,bInfo.dwCursorPosition,&ul);//�ַ���Ϊ�ո�
                    }

                }
                else if(bInfo.dwCursorPosition.X<pHotArea->pArea[*piHot-1].Right)
                {
                    FillConsoleOutputCharacter(gh_std_out,asc,1,bInfo.dwCursorPosition,&ul);//��ʾ�ַ�
                    bInfo.dwCursorPosition.X++;//�ı���λ��
                    SetConsoleCursorPosition(gh_std_out, bInfo.dwCursorPosition);
                }
            }
        }
    }
    //PopOff();
}
