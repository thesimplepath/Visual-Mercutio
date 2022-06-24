import java.*;

public class pproc {
	private int procid;
	private int wkgid;
	private int procattribid;

	/**
	 * 0=start
	 * 1=stop
	 * 2=normal
	 */
	private int proctype;

	/**
	 * 0=no
	 * 1=yes, by any employee of this group
	 * 2=yes, by chief of this group
	 */
	private int doublesign;


	public pproc() {};
	public void setProcid(int procid) {this.procid=procid;}
	public int  getProcid() {return procid;}
	public void setWkgid(int procid) {this.wkgid=wkgid;}
	public int  getWkgid() {return wkgid;}
	public void setProcattribid(int procattribid) {this.procattribid=procattribid;}
	public int  getProcattribid() {return procattribid;}
	public void setProctype(int proctype) {this.proctype=proctype;}
	public int  getProctype() {return proctype;}
	public void setDoublesign(int doublesign) {this.doublesign=doublesign;}
	public int  getDoublesign() {return doublesign;}
	public String toString() {return (String)""+procid+"-"+wkgid+"-"+procattribid;}
}
