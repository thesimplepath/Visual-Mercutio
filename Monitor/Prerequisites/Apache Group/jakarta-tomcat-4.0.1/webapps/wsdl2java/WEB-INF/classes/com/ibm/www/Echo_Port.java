/**
 * Echo_Port.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis Wsdl2java emitter.
 */

package com.ibm.www;

public interface Echo_Port extends java.rmi.Remote {
    public com.ibm.www.SOAPStruct[] echoStructArray(com.ibm.www.SOAPStruct[] inputStructArray) throws java.rmi.RemoteException;
    public void echoVoid() throws java.rmi.RemoteException;
    public float echoFloat(float inputFloat) throws java.rmi.RemoteException;
    public byte[] echoBase64(byte[] inputBase64) throws java.rmi.RemoteException;
    public int[] echoIntegerArray(int[] inputIntegerArray) throws java.rmi.RemoteException;
    public com.ibm.www.SOAPStructArray echoSoapStructArray(com.ibm.www.SOAPStructArray in) throws java.rmi.RemoteException;
    public byte[] echoHexBinary(byte[] inputHexBinary) throws java.rmi.RemoteException;
    public com.ibm.www.SOAPStruct echoStruct(com.ibm.www.SOAPStruct inputStruct) throws java.rmi.RemoteException;
    public float[] echoFloatArray(float[] inputFloatArray) throws java.rmi.RemoteException;
    public java.lang.String[] echoStringArray(java.lang.String[] inputStringArray) throws java.rmi.RemoteException;
    public java.math.BigDecimal[] echoDecimalArray(java.math.BigDecimal[] inputIntegerArray) throws java.rmi.RemoteException;
    public java.util.Date echoDate(java.util.Date inputDate) throws java.rmi.RemoteException;
    public java.math.BigDecimal echoDecimal(java.math.BigDecimal inputDecimal) throws java.rmi.RemoteException;
    public int echoInteger(int inputInteger) throws java.rmi.RemoteException;
    public boolean echoBoolean(boolean inputBoolean) throws java.rmi.RemoteException;
    public java.lang.String echoString(java.lang.String inputString) throws java.rmi.RemoteException;
}
