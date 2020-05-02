namespace CapsulesTravailDLL
{
    [System.Web.Services.WebServiceBindingAttribute(Name="capsulesSOAP",
                                                    Namespace="urn:capsulesSOAP"),
                                                    System.ComponentModel.DesignerCategoryAttribute("code")]
    public class capsulesSOAP: System.Web.Services.Protocols.SoapHttpClientProtocol
    {
        public capsulesSOAP(string serveur)
        {
            if (serveur == "")
                Url = "http://wrkmora04:8080/soap/servlet/rpcrouter";
            else
                Url = serveur ;
        }

        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("",
                                                                   RequestNamespace="urn:capsulesSOAP",
                                                                   ResponseNamespace="urn:capsulesSOAP",
                                                                   Use=System.Web.Services.Description.SoapBindingUse.Encoded,
                                                                   ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        [return: System.Xml.Serialization.SoapElementAttribute("return")]
        public long processCapsule(string capsuleAsXML)
        {
            object[] results = this.Invoke("processCapsule", new object[] {capsuleAsXML});
            return ((long)(results[0]));
        }
    }
}
