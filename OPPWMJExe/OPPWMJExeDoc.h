// OPPWMJExeDoc.h : interface of the COPPWMJExeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPPWMJEXEDOC_H__83C490BA_C99D_40DD_9363_12922AD598A3__INCLUDED_)
#define AFX_OPPWMJEXEDOC_H__83C490BA_C99D_40DD_9363_12922AD598A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COPPWMJExeDoc : public CDocument
{
protected: // create from serialization only
	COPPWMJExeDoc();
	DECLARE_DYNCREATE(COPPWMJExeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPPWMJExeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COPPWMJExeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COPPWMJExeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPPWMJEXEDOC_H__83C490BA_C99D_40DD_9363_12922AD598A3__INCLUDED_)
