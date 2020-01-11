/****************************************************************************
 * ==> PSS_SelectableDefs --------------------------------------------------*
 ****************************************************************************
 * Description : Provides the selectable definitions                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectableDefsH
#define PSS_SelectableDefsH

#if _MSC_VER > 1000
    #pragma once
#endif

const int g_Selectable_Symbol     = 0x0001;
const int g_Selectable_LinkSymbol = 0x0002;
const int g_Selectable_GraphPage  = 0x0004;
const int g_Selectable_Model      = 0x0008;
const int g_Selectable_RootModel  = 0x0010;
const int g_Selectable_Document   = 0x0020;
const int g_Selectable_Door       = 0x0040;
const int g_Selectable_Process    = 0x0080;
const int g_Selectable_Procedure  = 0x0080;
const int g_Selectable_All        = 0xFFFF;

#endif
