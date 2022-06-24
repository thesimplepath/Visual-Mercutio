/**
 * SOAPStruct.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis Wsdl2java emitter.
 */

package com.ibm.www;

public class SOAPStruct implements java.io.Serializable {
    private java.lang.String varString;
    private int varInt;
    private float varFloat;
    private byte[] varBase64;
    private java.util.Date varDateTime;
    private java.math.BigDecimal varDecimal;
    private boolean varBoolean;

    public SOAPStruct() {
    }

    public SOAPStruct(java.lang.String varString, int varInt, float varFloat, byte[] varBase64, java.util.Date varDateTime, java.math.BigDecimal varDecimal, boolean varBoolean) {
        this.varString = varString;
        this.varInt = varInt;
        this.varFloat = varFloat;
        this.varBase64 = varBase64;
        this.varDateTime = varDateTime;
        this.varDecimal = varDecimal;
        this.varBoolean = varBoolean;
    }

    public java.lang.String getVarString() {
        return varString;
    }

    public void setVarString(java.lang.String varString) {
        this.varString = varString;
    }

    public int getVarInt() {
        return varInt;
    }

    public void setVarInt(int varInt) {
        this.varInt = varInt;
    }

    public float getVarFloat() {
        return varFloat;
    }

    public void setVarFloat(float varFloat) {
        this.varFloat = varFloat;
    }

    public byte[] getVarBase64() {
        return varBase64;
    }

    public void setVarBase64(byte[] varBase64) {
        this.varBase64 = varBase64;
    }

    public java.util.Date getVarDateTime() {
        return varDateTime;
    }

    public void setVarDateTime(java.util.Date varDateTime) {
        this.varDateTime = varDateTime;
    }

    public java.math.BigDecimal getVarDecimal() {
        return varDecimal;
    }

    public void setVarDecimal(java.math.BigDecimal varDecimal) {
        this.varDecimal = varDecimal;
    }

    public boolean getVarBoolean() {
        return varBoolean;
    }

    public void setVarBoolean(boolean varBoolean) {
        this.varBoolean = varBoolean;
    }

}
