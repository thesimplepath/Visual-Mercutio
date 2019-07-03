// posize.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "PropPage.h"

// Forward declaration
class PlanFinObject;

/////////////////////////////////////////////////////////////////////////////
// ZIPositionSizePropertyPage dialog
#include "zRes32\ZRes.h"


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZIPositionSizePropertyPage : public ZIGenericPropPage
{
// Construction
public:
    ZIPositionSizePropertyPage(PlanFinObject* pObj = NULL);    // standard constructor

    virtual void    SaveValuesToObject();

// Dialog Data
    //{{AFX_DATA(ZIPositionSizePropertyPage)
    enum { IDD = IDD_SIZE_POSITION_PROPERTY };
    double    m_PositionX;
    double    m_PositionY;
    double    m_Width;
    double    m_Height;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIPositionSizePropertyPage)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
