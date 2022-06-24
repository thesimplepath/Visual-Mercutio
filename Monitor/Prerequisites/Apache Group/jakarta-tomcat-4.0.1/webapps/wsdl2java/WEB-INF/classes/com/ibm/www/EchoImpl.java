/**
 * EchoImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis Wsdl2java emitter.
 */

package com.ibm.www;

public class EchoImpl implements com.ibm.www.Echo_Port {
    public java.lang.String echoString(java.lang.String inputString) throws java.rmi.RemoteException {
        return inputString;
    }
    public java.lang.String[] echoStringArray(java.lang.String[] inputStringArray) throws java.rmi.RemoteException {
        return inputStringArray;
    }
    public int echoInteger(int inputInteger) throws java.rmi.RemoteException {
        return inputInteger;
    }
    public int[] echoIntegerArray(int[] inputIntegerArray) throws java.rmi.RemoteException {
        return inputIntegerArray;
    }
    public java.math.BigDecimal[] echoDecimalArray(java.math.BigDecimal[] inputArray) throws java.rmi.RemoteException {
        return inputArray;
    }
    public float echoFloat(float inputFloat) throws java.rmi.RemoteException {
        return inputFloat;
    }
    public float[] echoFloatArray(float[] inputFloatArray) throws java.rmi.RemoteException {
        return inputFloatArray;
    }
    public com.ibm.www.SOAPStruct echoStruct(com.ibm.www.SOAPStruct inputStruct) throws java.rmi.RemoteException {
        return inputStruct;
    }
    public com.ibm.www.SOAPStruct[] echoStructArray(com.ibm.www.SOAPStruct[] inputStructArray) throws java.rmi.RemoteException {
        return inputStructArray;
    }
    public void echoVoid() throws java.rmi.RemoteException {
        System.err.println( this + ".echoVoid()");
    }
    public byte[] echoBase64(byte[] inputBase64) throws java.rmi.RemoteException {
        return inputBase64;
    }
    public java.util.Date echoDate(java.util.Date inputDate) throws java.rmi.RemoteException {
        return inputDate;
    }
    public byte[] echoHexBinary(byte[] inputHexBinary) throws java.rmi.RemoteException {
        return inputHexBinary;
    }
    public java.math.BigDecimal echoDecimal(java.math.BigDecimal inputDecimal) throws java.rmi.RemoteException {
        return inputDecimal;
    }
    public boolean echoBoolean(boolean inputBoolean) throws java.rmi.RemoteException {
        return inputBoolean;
    }
    public com.ibm.www.SOAPStructArray echoSoapStructArray(com.ibm.www.SOAPStructArray in) throws java.rmi.RemoteException {
        return in;
    }
}
