
#include "GeoObject.h"
#include "afxtempl.h"
class CGeoAnotation :
	public CGeoObject
{
private:
	CPoint pt;
public:
	CString name;

	void setPoint(CPoint pt);
	void Draw(CDC *pDC);
	CGeoAnotation();
	virtual ~CGeoAnotation();
};
