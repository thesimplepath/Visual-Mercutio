package samples.weblogic_ejb;

/**
 * This is an Enterprise Java Bean Remote Interface
 */
public interface HelloService extends javax.ejb.EJBObject {

/**
 *
 * @return java.lang.String
 * @param phrase java.lang.String
 * @exception String The exception description.
 */
java.lang.String hello(java.lang.String phrase) throws java.rmi.RemoteException;
}
