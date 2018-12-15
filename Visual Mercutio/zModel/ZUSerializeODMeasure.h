// ZUSerializeODMeasure.h: interface for the ZUSerializeODMeasure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSERIALIZEODMEASURE_H__F2584E07_0478_11D4_96F4_0000B45D7C6F__INCLUDED_)
#define AFX_ZUSERIALIZEODMEASURE_H__F2584E07_0478_11D4_96F4_0000B45D7C6F__INCLUDED_

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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZUSerializeODMeasure  
{
public:
    ZUSerializeODMeasure();
    virtual ~ZUSerializeODMeasure();

    static void SerializeReadODMeasure(CArchive& ar, CODMeasure& Measure);
    static void SerializeWriteODMeasure(CArchive& ar, CODMeasure& Measure);

};

#endif // !defined(AFX_ZUSERIALIZEODMEASURE_H__F2584E07_0478_11D4_96F4_0000B45D7C6F__INCLUDED_)
