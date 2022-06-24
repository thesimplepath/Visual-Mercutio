public class pmodel{
	private String modelname; //name of the model
	private String modelref;  //model ref (GIID) used to group versions

	public pmodel() {};

	public String getModelref() {return modelref;}
	public void setModelref(String modelref) {this.modelref=modelref;}
	public String getModelname() {return modelname;}
	public void setModelname(String modelname) {this.modelname=modelname;}

	public String toString() {return (String)(modelref+"="+modelname);}

}
