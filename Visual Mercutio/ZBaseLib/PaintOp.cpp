/****************************************************************************
 * ==> PSS_PaintOperations -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a paint operations helper class                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PaintOp.h"

 //---------------------------------------------------------------------------
 // Static variables
 //---------------------------------------------------------------------------
CSize PSS_PaintOperations::m_LogicalBasicUnits;
//---------------------------------------------------------------------------
// PSS_PaintOperations
//---------------------------------------------------------------------------
PSS_PaintOperations::PSS_PaintOperations()
{}
//---------------------------------------------------------------------------
PSS_PaintOperations::PSS_PaintOperations(const PSS_PaintOperations& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_PaintOperations::~PSS_PaintOperations()
{}
//---------------------------------------------------------------------------
const PSS_PaintOperations& PSS_PaintOperations::operator = (const PSS_PaintOperations& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
