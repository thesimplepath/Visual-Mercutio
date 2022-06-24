package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class index$jsp extends HttpJspBase {


    static {
    }
    public index$jsp( ) {
    }

    private static boolean _jspx_inited = false;

    public final void _jspx_init() throws org.apache.jasper.runtime.JspException {
    }

    public void _jspService(HttpServletRequest request, HttpServletResponse  response)
        throws java.io.IOException, ServletException {

        JspFactory _jspxFactory = null;
        PageContext pageContext = null;
        HttpSession session = null;
        ServletContext application = null;
        ServletConfig config = null;
        JspWriter out = null;
        Object page = this;
        String  _value = null;
        try {

            if (_jspx_inited == false) {
                synchronized (this) {
                    if (_jspx_inited == false) {
                        _jspx_init();
                        _jspx_inited = true;
                    }
                }
            }
            _jspxFactory = JspFactory.getDefaultFactory();
            response.setContentType("text/html;charset=ISO-8859-1");
            pageContext = _jspxFactory.getPageContext(this, request, response,
			"", true, 8192, true);

            application = pageContext.getServletContext();
            config = pageContext.getServletConfig();
            session = pageContext.getSession();
            out = pageContext.getOut();

            // HTML // begin [file="/index.jsp";from=(0,53);to=(1,0)]
                out.write("\r\n");

            // end
            // begin [file="/index.jsp";from=(1,0);to=(1,32)]
                /* ----  logic:redirect ---- */
                org.apache.struts.taglib.logic.RedirectTag _jspx_th_logic_redirect_0 = new org.apache.struts.taglib.logic.RedirectTag();
                _jspx_th_logic_redirect_0.setPageContext(pageContext);
                _jspx_th_logic_redirect_0.setParent(null);
                _jspx_th_logic_redirect_0.setForward("main");
                try {
                    int _jspx_eval_logic_redirect_0 = _jspx_th_logic_redirect_0.doStartTag();
                    if (_jspx_eval_logic_redirect_0 == javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_BUFFERED)
                        throw new JspTagException("Since tag handler class org.apache.struts.taglib.logic.RedirectTag does not implement BodyTag, it can't return BodyTag.EVAL_BODY_TAG");
                    if (_jspx_eval_logic_redirect_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                        do {
                        // end
                        // begin [file="/index.jsp";from=(1,0);to=(1,32)]
                        } while (_jspx_th_logic_redirect_0.doAfterBody() == javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN);
                    }
                    if (_jspx_th_logic_redirect_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE)
                        return;
                } finally {
                    _jspx_th_logic_redirect_0.release();
                }
            // end
            // HTML // begin [file="/index.jsp";from=(1,32);to=(3,0)]
                out.write("\r\n\r\n");

            // end
            // HTML // begin [file="/index.jsp";from=(8,4);to=(9,0)]
                out.write("\r\n");

            // end

        } catch (Throwable t) {
            if (out != null && out.getBufferSize() != 0)
                out.clearBuffer();
            if (pageContext != null) pageContext.handlePageException(t);
        } finally {
            if (_jspxFactory != null) _jspxFactory.releasePageContext(pageContext);
        }
    }
}
