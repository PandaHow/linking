#pragma once
#include <stack>
typedef struct
{
	char x1, y1, x2, y2;
}POINT_LINE;
typedef struct
{
	int x;
	int y;
}PT;
class CCode
{
public:
	CCode();
	~CCode();
	void KeyDown(CPoint);
	void SetSize(int line = 14, int row = 10, int nPic = 10);
	void SetCode();
	int GetSize(){ return lines*rows / 2; }

	bool updirect(PT ptStart, PT ptEnd, int sum);
	bool downdirect(PT ptStart, PT ptEnd, int sum);
	bool leftdirect(PT ptStart, PT ptEnd, int sum);
	bool rightdirect(PT ptStart, PT ptEnd, int sum);
private:
	bool IsFirst;
	CImage m_pic;
	int lines, rows;
	int nPosStateFirest, nPosStateSecond;
	int nPic;		//ͼƬ��
	int cx_pic_desk, cy_pic_desk;//��ͼ��С
	char **nPosState;	//������״̬��falseΪ��
	POINT_LINE *pCode;	//2������1�飬��ɵ�����
	std::stack<PT> pt_path;
public:
	void DrawPic();
};

