// ZBSymbolLabel.h: interface for the ZBSymbolLabel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSymbolLabel_H__86F89ED1_2090_4F65_8977_AA7C1277980E__INCLUDED_)
#define AFX_ZBSymbolLabel_H__86F89ED1_2090_4F65_8977_AA7C1277980E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif




class AFX_EXT_CLASS ZBSymbolLabel : public CODLabelComponent  
{
	DECLARE_SERIAL(ZBSymbolLabel)

public:
	//@cmember
	/* Constructor. */
	ZBSymbolLabel( bool NotifyParent = false );
	//@cmember
	/* Constructor. */
	ZBSymbolLabel(CODSymbolComponent* pOwner, bool NotifyParent = false);
	//@cmember
	/* Constructor. */
	ZBSymbolLabel(const OD_CONTROL_POINT ctlPoint, bool NotifyParent = false);

	virtual ~ZBSymbolLabel();

	/* Copy constructor. */
	ZBSymbolLabel(const ZBSymbolLabel& src);
	/* Assignment operator. */
	ZBSymbolLabel& operator=(const ZBSymbolLabel& src);
	/* Create a duplicate copy of this object. */
	virtual CODComponent* Dup() const;


	bool GetNotifyParent() const;
	void SetNotifyParent( bool value );

	// Called by the framework, when the label move
	virtual void OnMove();

	/* Serializes the symbol. */
	virtual void Serialize(CArchive& ar);

private:
	bool m_NotifyParent;

};



inline bool ZBSymbolLabel::GetNotifyParent() const 
{
	return m_NotifyParent;
}
inline void ZBSymbolLabel::SetNotifyParent( bool value )
{
	m_NotifyParent = value;
}

inline void ZBSymbolLabel::OnMove()
{
	CODLabelComponent::OnMove();

	if (m_NotifyParent)
	{
		CODSymbolComponent* pComp = GetOwner();
		if (pComp)
			// call the function to adjust 
			// the position of embedded elements
			pComp->OnMove();
	}
}

#endif // !defined(AFX_ZBSymbolLabel_H__86F89ED1_2090_4F65_8977_AA7C1277980E__INCLUDED_)


