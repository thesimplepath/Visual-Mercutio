/**
 * EchoStub.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis Wsdl2java emitter.
 */

package com.ibm.www;

public class EchoStub extends javax.xml.rpc.Stub implements com.ibm.www.Echo_Port {
    private org.apache.axis.client.Service service = null ;
    private org.apache.axis.client.Call call = null ;
    private java.util.Hashtable properties = new java.util.Hashtable();

    public EchoStub(java.net.URL endpointURL) throws org.apache.axis.AxisFault {
         this();
         call.setTargetEndpointAddress( endpointURL );
         call.setProperty(org.apache.axis.transport.http.HTTPTransport.URL, endpointURL.toString());
    }
    public EchoStub() throws org.apache.axis.AxisFault {
        try {
            service = new org.apache.axis.client.Service();
            call = (org.apache.axis.client.Call) service.createCall();
            javax.xml.rpc.namespace.QName qn;
            Class cls;
            qn = new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "SOAPStruct");
            cls = com.ibm.www.SOAPStruct.class;
            call.addSerializer(cls, qn, new org.apache.axis.encoding.BeanSerializer(cls));
            call.addDeserializerFactory(qn, cls, org.apache.axis.encoding.BeanSerializer.getFactory());

            qn = new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "SOAPStructArray");
            cls = com.ibm.www.SOAPStructArray.class;
            call.addSerializer(cls, qn, new org.apache.axis.encoding.BeanSerializer(cls));
            call.addDeserializerFactory(qn, cls, org.apache.axis.encoding.BeanSerializer.getFactory());

        }
        catch(Exception t) {
            throw org.apache.axis.AxisFault.makeFault(t);
        }
    }

    public void _setProperty(String name, Object value) {
        properties.put(name, value);
    }

    // From javax.xml.rpc.Stub
    public Object _getProperty(String name) {
        return properties.get(name);
    }

    // From javax.xml.rpc.Stub
    public void _setTargetEndpoint(java.net.URL address) {
        call.setProperty(org.apache.axis.transport.http.HTTPTransport.URL, address.toString());
    }

    // From javax.xml.rpc.Stub
    public java.net.URL _getTargetEndpoint() {
        try {
            return new java.net.URL((String) call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL));
        }
        catch (java.net.MalformedURLException mue) {
            return null; // ???
        }
    }

    // From javax.xml.rpc.Stub
    public synchronized void setMaintainSession(boolean session) {
        call.setMaintainSession(session);
    }

    // From javax.naming.Referenceable
    public javax.naming.Reference getReference() {
        return null; // ???
    }

    public java.lang.String echoString(java.lang.String inputString) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputString", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "string")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "string")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoString");
        Object resp = call.invoke(new Object[] {inputString});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (java.lang.String) resp;
        }
    }

    public java.lang.String[] echoStringArray(java.lang.String[] inputStringArray) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputStringArray", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfstring")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfstring")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoStringArray");
        Object resp = call.invoke(new Object[] {inputStringArray});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (java.lang.String[]) resp;
        }
    }

    public int echoInteger(int inputInteger) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputInteger", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "int")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "int")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoInteger");
        Object resp = call.invoke(new Object[] {new Integer(inputInteger)});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return ((Integer) resp).intValue();
        }
    }

    public int[] echoIntegerArray(int[] inputIntegerArray) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputIntegerArray", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfint")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfint")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoIntegerArray");
        Object resp = call.invoke(new Object[] {inputIntegerArray});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (int[]) resp;
        }
    }

    public java.math.BigDecimal[] echoDecimalArray(java.math.BigDecimal[] inputIntegerArray) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputIntegerArray", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfdecimal")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfdecimal")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoDecimalArray");
        Object resp = call.invoke(new Object[] {inputIntegerArray});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (java.math.BigDecimal[]) resp;
        }
    }

    public float echoFloat(float inputFloat) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputFloat", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "float")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "float")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoFloat");
        Object resp = call.invoke(new Object[] {new Float(inputFloat)});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return ((Float) resp).floatValue();
        }
    }

    public float[] echoFloatArray(float[] inputFloatArray) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputFloatArray", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOffloat")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOffloat")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoFloatArray");
        Object resp = call.invoke(new Object[] {inputFloatArray});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (float[]) resp;
        }
    }

    public com.ibm.www.SOAPStruct echoStruct(com.ibm.www.SOAPStruct inputStruct) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputStruct", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "SOAPStruct")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "SOAPStruct")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoStruct");
        Object resp = call.invoke(new Object[] {inputStruct});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (com.ibm.www.SOAPStruct) resp;
        }
    }

    public com.ibm.www.SOAPStruct[] echoStructArray(com.ibm.www.SOAPStruct[] inputStructArray) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputStructArray", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfSOAPStruct")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "ArrayOfSOAPStruct")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoStructArray");
        Object resp = call.invoke(new Object[] {inputStructArray});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (com.ibm.www.SOAPStruct[]) resp;
        }
    }

    public void echoVoid() throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoVoid");
        Object resp = call.invoke(new Object[] {});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
    }

    public byte[] echoBase64(byte[] inputBase64) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputBase64", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "base64Binary")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "base64Binary")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoBase64");
        Object resp = call.invoke(new Object[] {inputBase64});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (byte[]) resp;
        }
    }

    public java.util.Date echoDate(java.util.Date inputDate) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputDate", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "dateTime")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "dateTime")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoDate");
        Object resp = call.invoke(new Object[] {inputDate});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (java.util.Date) resp;
        }
    }

    public byte[] echoHexBinary(byte[] inputHexBinary) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputHexBinary", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "hexBinary")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "hexBinary")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoHexBinary");
        Object resp = call.invoke(new Object[] {inputHexBinary});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (byte[]) resp;
        }
    }

    public java.math.BigDecimal echoDecimal(java.math.BigDecimal inputDecimal) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputDecimal", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "decimal")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "decimal")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoDecimal");
        Object resp = call.invoke(new Object[] {inputDecimal});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (java.math.BigDecimal) resp;
        }
    }

    public boolean echoBoolean(boolean inputBoolean) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("inputBoolean", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoBoolean");
        Object resp = call.invoke(new Object[] {new Boolean(inputBoolean)});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return ((Boolean) resp).booleanValue();
        }
    }

    public com.ibm.www.SOAPStructArray echoSoapStructArray(com.ibm.www.SOAPStructArray in) throws java.rmi.RemoteException{
        if (call.getProperty(org.apache.axis.transport.http.HTTPTransport.URL) == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        call.removeAllParameters();
        call.addParameter("in", new org.apache.axis.encoding.XMLType( new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "SOAPStructArray")), org.apache.axis.client.Call.PARAM_MODE_IN);
        call.setReturnType(new org.apache.axis.encoding.XMLType(new javax.xml.rpc.namespace.QName("http://www.ibm.com/wstkwsdl2java/xsd", "SOAPStructArray")));

        call.setProperty(org.apache.axis.transport.http.HTTPTransport.ACTION, "http://www.ibm.com/wsdl2java/echo/");
        call.setProperty(call.NAMESPACE, "http://tempuri.org/wwwibmcom_wsdl2java_echo");
        call.setOperationName( "echoSoapStructArray");
        Object resp = call.invoke(new Object[] {in});

        if (resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)resp;
        }
        else {
             return (com.ibm.www.SOAPStructArray) resp;
        }
    }

}
