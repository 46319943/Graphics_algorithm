#include "stdafx.h"
#include "MapProjection.h"


CMapProjection::CMapProjection(float a)
	: a(a)
	, e(0)
{
	L0 = 0.0f;
	L1 = 0.0f;
	B0 = 0.0f;
	B1 = 0.0;
}

CMapProjection::CMapProjection(float L0, float L1, float B0, float B1, float a)
{
	this->L0 = L0;
	this->L1 = L1;
	this->B0 = B0;
	this->B1 = B1;
	this->a = a;
}


CMapProjection::~CMapProjection()
{
}

void CMapProjection::Draw(CDC * pDC, double delta, int interval)
{
	// 开始经度
	int L0 = ceil(this->L0);
	// 结束经度
	int L1 = floor(this->L1);
	// 开始纬度
	int B0 = ceil(this->B0);
	// 结束纬度
	int B1 = floor(this->B1);

	float x, y;
	CString str;
	pDC->SetBkMode(TRANSPARENT);
	// 调整纬度，画下一条纬线
	for (int B = B0; B <= B1; B += interval)
	{
		// 根据delta增加经度，画纬线
		// 控制一条线
		for (double L = L0; L <= L1; L += delta)
		{
			getXY(L, B, &x, &y);
			if (L == L0)
			{
				pDC->MoveTo(CPoint(x, y));
			}
			else
			{
				pDC->LineTo(CPoint(x, y));
			}

		}
		// 在终点画线
		if (B > B1 - interval && B < B1) {
			// 因为循环之后，B 会增加。因此如果要让B = B1再循环一次，就要让B = B1 - interval
			B = B1 - interval;
		}
		// 不在第一个线画字
		if (B == B0) {
			continue;
		}
		str.Format("%d", B);
		pDC->TextOutA(x, y, str);
	}

	// 调整经度，画下一条经线
	for (int L = L0; L <= L1; L += interval)
	{
		// 根据delta增加纬度，画经线
		// 控制一条线
		for (double B = B0; B <= B1; B += delta)
		{
			getXY(L, B, &x, &y);
			if (B == B0)
			{
				pDC->MoveTo(CPoint(x, y));
				// 在头处画字
				str.Format("%d", L);
				pDC->TextOutA(x, y, str);
			}
			else
			{
				pDC->LineTo(CPoint(x, y));
			}
		}
		if (L > L1 - interval && L < L1) {
			// 因为循环之后，L会增加。因此如果要让L = L1再循环一次，就要让L = L1 - interval
			L = L1 - interval;
		}

	}


}
