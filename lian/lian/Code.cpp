#include "stdafx.h"
#include "Code.h"


CCode::CCode()
{
	lines = 14;
	rows = 10;
	nPic = 10;
	IsFirst = false;
	nPosState = NULL;
	pCode = NULL;
}


CCode::~CCode()
{
}

void CCode::SetSize(int lines, int rows, int nPic)	//rows������lines������nPicͼƬ��
{
	this->lines = lines;
	this->rows = rows;
	if (lines % 2 == 1 || rows % 2 == 1 || lines < 0 || rows < 0)
		return;
	if (pCode)
		delete[]pCode;
	this->pCode = new POINT_LINE[lines*rows / 2];
	this->nPic = nPic;
}

void CCode::SetCode()
{
	int i, j, m, n, k = 0, l = lines * rows / 2;

	char **num = new char *[rows];

	for (i = 0; i < rows; ++i)		//��̬����ն�ά��
		num[i] = new char[lines];

	for (i = 0; i < rows; ++i)
		memset(num[i], 0, sizeof(char)*lines);	//��������

	srand((unsigned)time(NULL));
	while (true)
	{
		m = rand() % lines;	//�����ֵ
		n = rand() % lines;

		if (m != n)
		{
			for (i = 0; i < rows; ++i)	//�ӵ�һ���������m�е�ֵ
			if (num[i][m])				//����Ϊ������˴��ѷ���
				continue;
			else
				break;					//���˴�Ϊ��˵��û���ʣ�����ѭ��
			for (j = 0; j < rows; ++j)	//�ӵ�һ���������n�е�ֵ
			if (num[j][n])
				continue;
			else
				break;
			if (i < rows && j < rows)	//�����m�еĵ�i�е�Ԫ�أ����n�еĵ�j�е�Ԫ�� ��û����
			{

				num[i][m] = 1;		//���øô�����
				num[j][n] = 1;
				pCode[k].x1 = m;		//��¼����
				pCode[k].y1 = i;
				pCode[k].x2 = n;
				pCode[k].y2 = j;
				++k;
				if (l == k)			//��������������г˻���һ�룬����ѭ��ÿ������2������
					break;
			}
		}
		m = rand() % lines;		//�����һ�п�ʼ
		n = rand() % lines;

		if (m != n)
		{
			for (i = 0; i < rows; ++i)
			if (num[rows - 1 - i][m])
				continue;
			else
				break;
			for (j = 0; j < rows; ++j)
			if (num[rows - 1 - j][n])
				continue;
			else
				break;
			if (i < rows && j < rows)
			{
				num[rows - 1 - i][m] = 1;
				num[rows - 1 - j][n] = 1;
				pCode[k].y1 = rows - 1 - i;
				pCode[k].x1 = m;
				pCode[k].y2 = rows - 1 - j;
				pCode[k].x2 = n;
				++k;
				if (l == k)
					break;
			}
		}
		m = rand() % rows;	//�ӵ�һ�п�ʼ
		n = rand() % rows;

		if (m != n)
		{
			for (i = 0; i < lines; ++i)
			if (num[m][i])
				continue;
			else
				break;
			for (j = 0; j < lines; ++j)
			if (num[n][j])
				continue;
			else
				break;
			if (i < lines && j < lines)
			{
				num[m][i] = 1;
				num[n][j] = 1;
				pCode[k].x1 = i;
				pCode[k].y1 = m;
				pCode[k].x2 = j;
				pCode[k].y2 = n;
				++k;
				if (l == k)
					break;
			}
		}
		m = rand() % rows;		//�����һ�п�ʼ
		n = rand() % rows;

		if (m != n)
		{
			for (i = 0; i < lines; ++i)
			if (num[m][lines - 1 - i])
				continue;
			else
				break;
			for (j = 0; j < lines; ++j)
			if (num[n][lines - 1 - j])
				continue;
			else
				break;
			if (i < lines && j < lines)
			{
				num[m][lines - 1 - i] = 1;
				num[n][lines - 1 - j] = 1;
				pCode[k].x1 = lines - 1 - i;
				pCode[k].y1 = m;
				pCode[k].x2 = lines - 1 - j;
				pCode[k].y2 = n;
				++k;
				if (l == k)
					break;
			}
		}
	}
	if (nPosState)
	{
		for (int i = 0; i < rows + 2; ++i)
			delete[]nPosState[i];
		delete[]nPosState;
	}

	nPosState = new char *[rows + 2];

	for (int i = 0; i < rows + 2; ++i)		//��̬����ն�ά��
		nPosState[i] = new char[lines + 2];

	memset(nPosState[0], 0, sizeof(char)*(lines + 2));
	memset(nPosState[rows + 1], 0, sizeof(char)*(lines + 2));
	for (int i = 0; i < rows; ++i)
	{
		nPosState[i + 1][0] = 0;
		nPosState[i + 1][lines + 1] = 0;
	}
	for (int i = 0; i < rows*lines / 2; ++i)
	{
		char temp = i % nPic + 1;
		nPosState[pCode[i].y1 + 1][pCode[i].x1 + 1] = temp;
		nPosState[pCode[i].y2 + 1][pCode[i].x2 + 1] = temp;
	}

	delete[]pCode;
	pCode = NULL;

	for (i = 0; i < rows; ++i)		//�ͷ�����ռ�
		delete[]num[i];
	delete[]num;
}


void CCode::DrawPic()
{
	if (m_pic.IsNull())
		m_pic.Load("res\\bk.jpg");
	if (m_pic.IsNull())
		return;

	HDC hdc = ::GetDC(AfxGetMainWnd()->m_hWnd);
	SetStretchBltMode(hdc, COLORONCOLOR);
	CRect rect;
	GetClientRect(AfxGetMainWnd()->m_hWnd, &rect);
	cx_pic_desk = rect.Width() / (lines + 2);
	cy_pic_desk = rect.Height() / (rows + 2);
	int cx_pic_src = m_pic.GetWidth() / nPic;
	int cy_pic_src = m_pic.GetHeight();

	for (int i = 0; i < rows + 2; ++i)
	{
		for (int j = 0; j < lines + 2; ++j)
		{
			if (nPosState[i][j])
			{
				m_pic.StretchBlt(hdc, j * cx_pic_desk, i * cy_pic_desk, cx_pic_desk, cy_pic_desk,
					(nPosState[i][j] - 1) * cx_pic_src, 0, cx_pic_src, cy_pic_src, SRCCOPY);
			}
		}
	}
	DeleteDC(hdc);
}

bool CCode::updirect(PT ptStart, PT ptEnd, int sum)
{
	PT temp;
	pt_path.push(ptStart);

	if (nPosState[ptStart.y][ptStart.x] || sum > 2)
	{
		pt_path.pop();
		return false;
	}
	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y &&
		nPosStateFirest == nPosStateSecond)
		return true;
	if (ptStart.y > 0)
	{
		temp.x = ptStart.x;
		temp.y = ptStart.y - 1;
		if (updirect(temp, ptEnd, sum))
			return true;
	}
	if (ptStart.x > 0)
	{
		temp.x = ptStart.x - 1;
		temp.y = ptStart.y;
		if (leftdirect(temp, ptEnd, sum + 1))
			return true;
	}
	if (ptStart.x < lines + 1)
	{
		temp.x = ptStart.x + 1;
		temp.y = ptStart.y;
		if (rightdirect(temp, ptEnd, sum + 1))
			return true;
	}
	pt_path.pop();
	return false;
}
bool CCode::downdirect(PT ptStart, PT ptEnd, int sum)
{
	PT temp;
	pt_path.push(ptStart);

	if (nPosState[ptStart.y][ptStart.x] || sum > 2)
	{
		pt_path.pop();
		return false;
	}

	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y &&
		nPosStateFirest == nPosStateSecond)
		return true;
	if (ptStart.y<rows + 1)
	{
		temp.x = ptStart.x;
		temp.y = ptStart.y + 1;
		if (downdirect(temp, ptEnd, sum))
			return true;
	}
	if (ptStart.x > 0)
	{
		temp.x = ptStart.x - 1;
		temp.y = ptStart.y;
		if (leftdirect(temp, ptEnd, sum + 1))
			return true;
	}
	if (ptStart.x < lines + 1)
	{
		temp.x = ptStart.x + 1;
		temp.y = ptStart.y;
		if (rightdirect(temp, ptEnd, sum + 1))
			return true;
	}
	pt_path.pop();
	return false;
}
bool CCode::rightdirect(PT ptStart, PT ptEnd, int sum)
{
	PT temp;
	pt_path.push(ptStart);

	if (nPosState[ptStart.y][ptStart.x] || sum > 2)
	{
		pt_path.pop();
		return false;
	}
	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y &&
		nPosStateFirest == nPosStateSecond)
		return true;
	if (ptStart.y<rows + 1)
	{
		temp.x = ptStart.x;
		temp.y = ptStart.y + 1;
		if (downdirect(temp, ptEnd, sum + 1))
			return true;
	}
	if (ptStart.y>0)
	{
		temp.x = ptStart.x;
		temp.y = ptStart.y - 1;
		if (updirect(temp, ptEnd, sum + 1))
			return true;
	}
	if (ptStart.x < lines + 1)
	{
		temp.x = ptStart.x + 1;
		temp.y = ptStart.y;
		if (rightdirect(temp, ptEnd, sum))
			return true;
	}
	pt_path.pop();
	return false;
}
bool CCode::leftdirect(PT ptStart, PT ptEnd, int sum)
{
	PT temp;
	pt_path.push(ptStart);

	if (nPosState[ptStart.y][ptStart.x] || sum > 2)
	{
		pt_path.pop();
		return false;
	}
	if (ptStart.x == ptEnd.x && ptStart.y == ptEnd.y &&
		nPosStateFirest == nPosStateSecond)
		return true;
	if (ptStart.y<rows + 1)
	{
		temp.x = ptStart.x;
		temp.y = ptStart.y + 1;
		if (downdirect(temp, ptEnd, sum + 1))
			return true;
	}
	if (ptStart.x > 0)
	{
		temp.x = ptStart.x - 1;
		temp.y = ptStart.y;
		if (leftdirect(temp, ptEnd, sum))
			return true;
	}
	if (ptStart.y > 0)
	{
		temp.x = ptStart.x;
		temp.y = ptStart.y - 1;
		if (updirect(temp, ptEnd, sum + 1))
			return true;
	}
	pt_path.pop();
	return false;
}

void CCode::KeyDown(CPoint pt)
{
	static PT ptFirst;

	IsFirst = !IsFirst;

	int x = pt.x / cx_pic_desk;
	int y = pt.y / cy_pic_desk;
	if (IsFirst)
	{
		ptFirst.x = x;
		ptFirst.y = y;
	}
	else
	{
		if (x == ptFirst.x && y == ptFirst.y)
			return;

		PT ptSecond;
		ptSecond.x = x;
		ptSecond.y = y;
		CRect rect_S(ptFirst.x*cx_pic_desk, ptFirst.y*cy_pic_desk,
			ptFirst.x*cx_pic_desk + cx_pic_desk, ptFirst.y*cy_pic_desk + cy_pic_desk);
		CRect rect_E(ptSecond.x*cx_pic_desk, ptSecond.y*cy_pic_desk,
			ptSecond.x*cx_pic_desk + cx_pic_desk, ptSecond.y*cy_pic_desk + cy_pic_desk);

		nPosStateFirest = nPosState[ptFirst.y][ptFirst.x];
		nPosStateSecond = nPosState[ptSecond.y][ptSecond.x];
		nPosState[ptFirst.y][ptFirst.x] = 0;
		nPosState[ptSecond.y][ptSecond.x] = 0;
		if (updirect(ptFirst, ptSecond, 0) || downdirect(ptFirst, ptSecond, 0) ||
			leftdirect(ptFirst, ptSecond, 0) || rightdirect(ptFirst, ptSecond, 0))
		{
			while (!pt_path.empty())
				pt_path.pop();
			InvalidateRect(AfxGetMainWnd()->m_hWnd, &rect_S, true);
			InvalidateRect(AfxGetMainWnd()->m_hWnd, &rect_E, true);
		}
		else
		{
			nPosState[ptFirst.y][ptFirst.x] = nPosStateFirest;
			nPosState[ptSecond.y][ptSecond.x] = nPosStateSecond;
		}
	}
}