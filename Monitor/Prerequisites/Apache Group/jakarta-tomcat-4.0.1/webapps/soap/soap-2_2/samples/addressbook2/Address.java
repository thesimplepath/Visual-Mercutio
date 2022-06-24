/*
 *This class is automatically generated by schema to Java program.
 *Only a subset of schema is handled and some of the schema information
 *may be lost during translation
 */

package samples.addressbook2;

public class Address{

	//instance variables
	public int	streetNum_Elem;
	public java.lang.String	streetName_Elem;
	public java.lang.String	city_Elem;
	public java.lang.String	state_Elem;
	public int	zip_Elem;
	public Phone	phoneNumber_Elem;

	//constructors
	public Address () { }

	public Address (int streetNum_Elem, java.lang.String streetName_Elem, java.lang.String city_Elem, java.lang.String state_Elem, int zip_Elem, Phone phoneNumber_Elem) {
		this.streetNum_Elem	= streetNum_Elem;
		this.streetName_Elem	= streetName_Elem;
		this.city_Elem	= city_Elem;
		this.state_Elem	= state_Elem;
		this.zip_Elem	= zip_Elem;
		this.phoneNumber_Elem	= phoneNumber_Elem;
	}

}