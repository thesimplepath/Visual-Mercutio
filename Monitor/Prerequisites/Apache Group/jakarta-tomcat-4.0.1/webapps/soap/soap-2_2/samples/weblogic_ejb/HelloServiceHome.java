package samples.weblogic_ejb;

/**
 * This is a Home interface for the Session Bean
 */
public interface HelloServiceHome extends javax.ejb.EJBHome {

/**
 * create method for a session bean
 * @return samples.HelloService
 * @exception javax.ejb.CreateException The exception description.
 * @exception java.rmi.RemoteException The exception description.
 */
HelloService create() throws javax.ejb.CreateException, java.rmi.RemoteException;
}
