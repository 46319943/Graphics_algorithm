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
	// ��ʼ����
	int L0 = ceil(this->L0);
	// ��������
	int L1 = floor(this->L1);
	// ��ʼγ��
	int B0 = ceil(this->B0);
	// ����γ��
	int B1 = floor(this->B1);

	float x, y;
	CString str;
	pDC->SetBkMode(TRANSPARENT);
	// ����γ�ȣ�����һ��γ��
	for (int B = B0; B <= B1; B += interval)
	{
		// ����delta���Ӿ��ȣ���γ��
		// ����һ����
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
		// ���յ㻭��
		if (B > B1 - interval && B < B1) {
			// ��Ϊѭ��֮��B �����ӡ�������Ҫ��B = B1��ѭ��һ�Σ���Ҫ��B = B1 - interval
			B = B1 - interval;
		}
		// ���ڵ�һ���߻���
		if (B == B0) {
			continue;
		}
		str.Format("%d", B);
		pDC->TextOutA(x, y, str);
	}

	// �������ȣ�����һ������
	for (int L = L0; L <= L1; L += interval)
	{
		// ����delta����γ�ȣ�������
		// ����һ����
		for (double B = B0; B <= B1; B += delta)
		{
			getXY(L, B, &x, &y);
			if (B == B0)
			{
				pDC->MoveTo(CPoint(x, y));
				// ��ͷ������
				str.Format("%d", L);
				pDC->TextOutA(x, y, str);
			}
			else
			{
				pDC->LineTo(CPoint(x, y));
			}
		}
		if (L > L1 - interval && L < L1) {
			// ��Ϊѭ��֮��L�����ӡ�������Ҫ��L = L1��ѭ��һ�Σ���Ҫ��L = L1 - interval
			L = L1 - interval;
		}

	}


}
