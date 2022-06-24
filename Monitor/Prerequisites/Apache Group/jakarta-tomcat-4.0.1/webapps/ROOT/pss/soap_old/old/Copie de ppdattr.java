public class ppdattr {
	private int pdattribid;
	private int prow;
	private int attribdefid;
	private String mvalue;

	public ppdattr() {};
	public void setPdattribid(int pdattribid) {this.pdattribid=pdattribid;}
	public int  getPdattribid() {return pdattribid;}
	public void setProw(int prow) {this.prow=prow;}
	public int  getProw() {return prow;}
	public void setAttribdefid(int attribdefid) {this.attribdefid=attribdefid;}
	public int  getAttribdefid() {return attribdefid;}
	public void setMvalue(String mvalue) {this.mvalue=mvalue;}
	public String getMvalue() {return mvalue;}
	public String toString() {return (String)""+pdattribid+"-"+prow+"-"+mvalue;}  
}
