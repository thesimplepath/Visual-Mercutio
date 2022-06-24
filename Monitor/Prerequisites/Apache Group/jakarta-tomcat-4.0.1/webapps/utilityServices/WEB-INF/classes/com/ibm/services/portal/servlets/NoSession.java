package com.ibm.services.portal.servlets;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class NoSession extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		performTask(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		performTask(request, response);
	}

	public void performTask(HttpServletRequest request,HttpServletResponse response) throws IOException {
		String targetPage ="";
		
       	HttpSession session = request.getSession(false);
   		if (session == null) {								
        	targetPage = "no_session.html";
        	response.sendRedirect(targetPage);
        }
	}
}
