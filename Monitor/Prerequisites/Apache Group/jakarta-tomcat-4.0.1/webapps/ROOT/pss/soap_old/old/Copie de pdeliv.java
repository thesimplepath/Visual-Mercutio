import java.*;

public class pdeliv {
	private int delivid;
	private int procidsrc;
	private int procidtrg;
	private int delivattribid;
	private String delivname;

	/**
	 * 0=normal
	 * 1=lateral
	 */
	private int lateral;
	private int lateraldirection; //0:top,1:right,2:bottom,3:left
	private int doublesign; //0:no,1:employees,2:chiefs

	public pdeliv() {};
	public void setDelivid(int delivid) {this.delivid=delivid;}
	public int  getDelivid() {return delivid;}
	public void setProcidsrc(int procidsrc) {this.procidsrc=procidsrc;}
	public int  getProcidsrc() {return procidsrc;}
	public void setProcidtrg(int procidtrg) {this.procidtrg=procidtrg;}
	public int  getProcidtrg() {return procidtrg;}
	public void setDelivattribid(int delivattribid) {this.delivattribid=delivattribid;}
	public int  getDelivattribid() {return delivattribid;}
	public void setDelivname(String delivname) {this.delivname=delivname;}
	public String getDelivname() {return delivname;}
	public void setLateral(int lateral) {this.lateral=lateral;}
	public int  getLateral() {return lateral;}
	public void setLateraldirection(int lateraldirection) {this.lateraldirection=lateraldirection;}
	public int  getLateraldirection() {return lateraldirection;}
	public void setDoublesign(int doublesign) {this.doublesign=doublesign;}
	public int  getDoublesign() {return doublesign;}

	public String toString() {return (String)""+delivid+"-"+procidsrc+"-"+procidtrg;}
}
