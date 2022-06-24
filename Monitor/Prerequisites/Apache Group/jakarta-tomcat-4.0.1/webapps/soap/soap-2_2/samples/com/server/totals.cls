VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "totals"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' The Apache Software License, Version 1.1
'
'
' Copyright (c) 2001 The Apache Software Foundation.  All rights
' reserved.
'
' Redistribution and use in source and binary forms, with or without
' modification, are permitted provided that the following conditions
' are met:
'
' 1. Redistributions of source code must retain the above copyright
'    notice, this list of conditions and the following disclaimer.
'
' 2. Redistributions in binary form must reproduce the above copyright
'    notice, this list of conditions and the following disclaimer in
'    the documentation and/or other materials provided with the
'    distribution.
'
' 3. The end-user documentation included with the redistribution,
'    if any, must include the following acknowledgment:
'       "This product includes software developed by the
'        Apache Software Foundation (http://www.apache.org/)."
'    Alternately, this acknowledgment may appear in the software itself,
'    if and wherever such third-party acknowledgments normally appear.
'
' 4. The names "SOAP" and "Apache Software Foundation" must
'    not be used to endorse or promote products derived from this
'    software without prior written permission. For written
'    permission, please contact apache@apache.org.
'
' 5. Products derived from this software may not be called "Apache",
'    nor may "Apache" appear in their name, without prior written
'    permission of the Apache Software Foundation.
'
' THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
' WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
' OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
' DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
' ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
' SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
' LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
' USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
' ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
' OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
' OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
' SUCH DAMAGE.
' ====================================================================
'
' This software consists of voluntary contributions made by many
' individuals on behalf of the Apache Software Foundation and was
' originally based on software copyright (c) 2001, International
' Business Machines, Inc., http://www.apache.org.  For more
' information on the Apache Software Foundation, please see
' <http://www.apache.org/>.
 

Private result As Long
Private Const sumfile As String = "apachesum.txt"
Private Const ForReading As Integer = 1
Private Const ForAppending As Integer = 8
Public Property Get total() As Long
total = result
End Property
Public Property Let total(ByVal n As Long)
result = n
End Property
Public Sub sum(ByVal n1 As Long)
result = result + n1
End Sub
Public Sub Class_Initialize()
result = 0
Set fs = CreateObject("Scripting.FileSystemObject")
If fs.FileExists(sumfile) Then
 Set t = fs.OpenTextFile(sumfile, ForReading)
 result = t.readline
 t.Close
 Set t = Nothing
End If
Set fs = Nothing
End Sub
Public Sub Class_Terminate()
Set fs = CreateObject("Scripting.FileSystemObject")
If fs.FileExists(sumfile) Then fs.DeleteFile sumfile, True
Set t = fs.OpenTextFile(sumfile, ForAppending, True)
t.WriteLine (result)
t.Close
Set t = Nothing
Set fs = Nothing
End Sub
