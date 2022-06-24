/**
 * EchoSkeleton.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis Wsdl2java emitter.
 */

package com.ibm.www;

public class EchoSkeleton {
    private com.ibm.www.Echo_Port impl;

    public EchoSkeleton() {
        this.impl = new com.ibm.www.EchoImpl();
    }

    public EchoSkeleton(com.ibm.www.Echo_Port impl) {
        this.impl = impl;
    }

    public Object echoString(java.lang.String inputString) throws java.rmi.RemoteException
    {
        Object ret = impl.echoString(inputString);
        return ret;
    }

    public Object echoStringArray(java.lang.String[] inputStringArray) throws java.rmi.RemoteException
    {
        Object ret = impl.echoStringArray(inputStringArray);
        return ret;
    }

    public Object echoInteger(int inputInteger) throws java.rmi.RemoteException
    {
        Object ret = new Integer(impl.echoInteger(inputInteger));
        return ret;
    }

    public Object echoIntegerArray(int[] inputIntegerArray) throws java.rmi.RemoteException
    {
        Object ret = impl.echoIntegerArray(inputIntegerArray);
        return ret;
    }

    public Object echoDecimalArray(java.math.BigDecimal[] inputIntegerArray) throws java.rmi.RemoteException
    {
        Object ret = impl.echoDecimalArray(inputIntegerArray);
        return ret;
    }

    public Object echoFloat(float inputFloat) throws java.rmi.RemoteException
    {
        Object ret = new Float(impl.echoFloat(inputFloat));
        return ret;
    }

    public Object echoFloatArray(float[] inputFloatArray) throws java.rmi.RemoteException
    {
        Object ret = impl.echoFloatArray(inputFloatArray);
        return ret;
    }

    public Object echoStruct(com.ibm.www.SOAPStruct inputStruct) throws java.rmi.RemoteException
    {
        Object ret = impl.echoStruct(inputStruct);
        return ret;
    }

    public Object echoStructArray(com.ibm.www.SOAPStruct[] inputStructArray) throws java.rmi.RemoteException
    {
        Object ret = impl.echoStructArray(inputStructArray);
        return ret;
    }

    public void echoVoid() throws java.rmi.RemoteException
    {
        impl.echoVoid();
    }

    public Object echoBase64(byte[] inputBase64) throws java.rmi.RemoteException
    {
        Object ret = impl.echoBase64(inputBase64);
        return ret;
    }

    public Object echoDate(java.util.Date inputDate) throws java.rmi.RemoteException
    {
        Object ret = impl.echoDate(inputDate);
        return ret;
    }

    public Object echoHexBinary(byte[] inputHexBinary) throws java.rmi.RemoteException
    {
        Object ret = impl.echoHexBinary(inputHexBinary);
        return ret;
    }

    public Object echoDecimal(java.math.BigDecimal inputDecimal) throws java.rmi.RemoteException
    {
        Object ret = impl.echoDecimal(inputDecimal);
        return ret;
    }

    public Object echoBoolean(boolean inputBoolean) throws java.rmi.RemoteException
    {
        Object ret = new Boolean(impl.echoBoolean(inputBoolean));
        return ret;
    }

    public Object echoSoapStructArray(com.ibm.www.SOAPStructArray in) throws java.rmi.RemoteException
    {
        Object ret = impl.echoSoapStructArray(in);
        return ret;
    }

}
