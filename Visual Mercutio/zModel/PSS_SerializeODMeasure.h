/****************************************************************************
 * ==> PSS_SerializeODMeasure ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an Objective View component measure serializer    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SerializeODMeasureH
#define PSS_SerializeODMeasureH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Objective View component measure serializer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SerializeODMeasure
{
    public:
        PSS_SerializeODMeasure();
        virtual ~PSS_SerializeODMeasure();

        /**
        * Reads the Objective View component measures
        *@param archive - the archive from which the measures should be read
        *@param[out] measure - the measure to read
        */
        static void SerializeReadODMeasure(CArchive& ar, CODMeasure& measure);

        /**
        * Writes the Objective View component measures
        *@param archive - the archive to which the measures should be written
        *@param measure - the measure to write
        */
        static void SerializeWriteODMeasure(CArchive& ar, const CODMeasure& measure);
};

#endif
