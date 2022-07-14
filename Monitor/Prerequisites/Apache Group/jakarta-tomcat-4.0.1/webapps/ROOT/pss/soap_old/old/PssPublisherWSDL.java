import java.io.*;
import java.util.*;
import java.net.*;
import java.sql.*;

import PsApp;
import PsDebug;
import PsConfig;
import PsDbMgr;
import PsDbConn;

import pmodel;
import pproc;
import pprocattr;
import pdeliv;
import pdelivattr;

public class PssPublisherWSDL {


/*	public int sndEmployee( PsEmployee employee ) {
	}
*/

	public int sndModel2(pmodel model,int procnbr,pproc[] proc)
	{
		System.out.println("Result:");
		System.out.println(model.getModelname());
		System.out.println(model.getModelref());
		System.out.println("-----------");
		for (int i=0;i<procnbr;i++)
		{
			System.out.println("#"+i+"="+proc[i].getProcid());
		}
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////
	//Method sndModel:	publish new process model from conceptor
	//			
	public int pubInit()	
	{
		System.out.println("pubInit...");

		try 
		{
			PsApp.init();
			PsDbConn conn=PsDbMgr.newConnection();	

			//for development purpose, we clean the entire database on publishing
			conn.sqlExec("DELETE FROM pmodel");
			conn.sqlExec("DELETE FROM pproc");
			conn.sqlExec("DELETE FROM pdeliv");
			conn.sqlExec("DELETE FROM pprocattr");
			conn.sqlExec("DELETE FROM pdelivattr");

			conn.sqlExecR("delete from pcase");
			conn.sqlExecR("delete from ptrans");
			conn.sqlExecR("delete from pproctrans");
			conn.sqlExecR("delete from pattrib");
			conn.sqlExecR("delete from pproctransfrom");
			conn.sqlExecR("delete from pdelivlateralstate");
			conn.sqlExecR("delete from pdelivstatus");
			conn.sqlExecR("delete from ptaskstatus");
			conn.sqlExecR("delete from pdecisionstatus");
			conn.sqlExecR("delete from pinfostatus");
		}
		catch (SQLException e)
		{
			PsDebug.log("PssPublisherWSDL.initPublish: SQLException: "+e.getMessage());
			return -1;
		}
		return 0;
	}
	public int pubModel(pmodel model)
	{
		System.out.println("pubModel...");

		int modelid;

		try 
		{
			PsApp.init();
			PsDbConn conn=PsDbMgr.newConnection();	

			//get a new modelid
			ResultSet rs=conn.sqlQueryR("SELECT MAX(modelid)+1 as modelid FROM pmodel");
			rs.next();
			modelid=rs.getInt("modelid");

			//model
			PsDebug.log(">register new model / version");
			conn.sqlExec("INSERT INTO pmodel VALUES ("+modelid+",'"+model.getModelname()+"')");
		}
		catch (SQLException e)
		{
			PsDebug.log("PssPublisherWSDL.pubModel: SQLException: "+e.getMessage());
			return -1;
		}

		return modelid;

	}
	public int pubProc(int modelid,int procnbr,pproc[] proc)
	{
		System.out.println("pubProc...");
		try 
		{
			PsApp.init();
			PsDbConn conn=PsDbMgr.newConnection();	
			
			//proc
			PsDebug.log(">publish procedure table");
			for (int i=0;i<procnbr;i++)
				conn.sqlExec("INSERT INTO pproc VALUES ("+proc[i].getProcid()+","+proc[i].getWkgid()+","+proc[i].getProcattribid()+","+modelid+",-1,"+proc[i].getProctype()+","+proc[i].getDoublesign()+")");
		}
		catch (SQLException e)
		{
			PsDebug.log("PssPublisherWSDL.pubProc: SQLException: "+e.getMessage());
			return -1;
		}

		return 0;
	}
	public int pubDeliv(int modelid,int delivnbr,pdeliv[] deliv)
	{
		System.out.println("pubDeliv...");
		try 
		{
			PsApp.init();
			PsDbConn conn=PsDbMgr.newConnection();	
	
			//deliv
			PsDebug.log(">publish deliverable table");
			for (int i=0;i<delivnbr;i++)
				conn.sqlExec("INSERT INTO pdeliv VALUES ("+deliv[i].getDelivid()+","+deliv[i].getProcidsrc()+","+deliv[i].getProcidtrg()+","+deliv[i].getDelivattribid()+",'"+deliv[i].getDelivname()+"',"+deliv[i].getLateral()+")");
			
		}
		catch (SQLException e)
		{
			PsDebug.log("PssPublisherWSDL.pubDeliv: SQLException: "+e.getMessage());
			return -1;
		}

		return 0;
	}
	public int pubPdattr(int modelid,int pdattrnbr,ppdattr[] pdattr)
	{
		System.out.println("pubPdattr...");
		try 
		{
			PsApp.init();
			PsDbConn conn=PsDbMgr.newConnection();	

			//proc&deliv attributes
			PsDebug.log(">publish attributes tables");
			for (int i=0;i<pdattrnbr;i++)
			{
				//TODO: merge the two table in on pdattr table
				conn.sqlExec("INSERT INTO pprocattr VALUES ("+pdattr[i].getPdattribid()+","+pdattr[i].getProw()+","+pdattr[i].getAttribdefid()+",'"+pdattr[i].getMvalue()+"')");
				conn.sqlExec("INSERT INTO pdelivattr VALUES ("+pdattr[i].getPdattribid()+","+pdattr[i].getProw()+","+pdattr[i].getAttribdefid()+",'"+pdattr[i].getMvalue()+"')");
			}	
		}
		catch (SQLException e)
		{
			PsDebug.log("PssPublisherWSDL.pubPdattr: SQLException: "+e.getMessage());
			return -1;
		}

		return 0;
	}

	public int pubDone()
	{
		System.out.println("pubDone...");
		return 0;
	}

	public int sndModelOld(pmodel model, int procnbr, pproc [] proc, int delivnbr, pdeliv [] deliv, int pdattrnbr, ppdattr [] pdattr  ) 
	{

		int i;
		try 
		{
			PsApp.init();
			PsDebug.log("PssPublisherWSDL.sndModel");
			PsDbConn conn=PsDbMgr.newConnection();	

			//for development purpose, we clean the entire database on publishing
			conn.sqlExec("DELETE FROM pmodel");
			conn.sqlExec("DELETE FROM pproc");
			conn.sqlExec("DELETE FROM pdeliv");
			conn.sqlExec("DELETE FROM pprocattr");
			conn.sqlExec("DELETE FROM pdelivattr");

			conn.sqlExecR("delete from pcase");
			conn.sqlExecR("delete from ptrans");
			conn.sqlExecR("delete from pproctrans");
			conn.sqlExecR("delete from pattrib");
			conn.sqlExecR("delete from pproctransfrom");
			conn.sqlExecR("delete from pdelivlateralstate");
			conn.sqlExecR("delete from pdelivstatus");
			conn.sqlExecR("delete from ptaskstatus");
			conn.sqlExecR("delete from pdecisionstatus");
			conn.sqlExecR("delete from pinfostatus");

			//get a new modelid
			ResultSet rs=conn.sqlQueryR("SELECT MAX(modelid)+1 as modelid FROM pmodel");
			rs.next();
			int modelid=rs.getInt("modelid");

			//model
			PsDebug.log(">register new model / version");
			conn.sqlExec("INSERT INTO pmodel VALUES ("+modelid+",'"+model.getModelname()+"')");

			//proc
			PsDebug.log(">publish procedure table");
			for (i=0;i<procnbr;i++)
				conn.sqlExec("INSERT INTO pproc VALUES ("+proc[i].getProcid()+","+proc[i].getWkgid()+","+proc[i].getProcattribid()+","+modelid+",-1,"+proc[i].getProctype()+","+proc[i].getDoublesign()+")");

			//deliv
			PsDebug.log(">publish deliverable table");
			for (i=0;i<delivnbr;i++)
				conn.sqlExec("INSERT INTO pdeliv VALUES ("+deliv[i].getDelivid()+","+deliv[i].getProcidsrc()+","+deliv[i].getProcidtrg()+","+deliv[i].getDelivattribid()+",'"+deliv[i].getDelivname()+"',"+deliv[i].getLateral()+")");

			//proc&deliv attributes
			PsDebug.log(">publish attributes tables");
			for (i=0;i<pdattrnbr;i++)
			{
				//TODO: merge the two table in on pdattr table
				conn.sqlExec("INSERT INTO pprocattr VALUES ("+pdattr[i].getPdattribid()+","+pdattr[i].getProw()+","+pdattr[i].getAttribdefid()+",'"+pdattr[i].getMvalue()+"')");
				conn.sqlExec("INSERT INTO pdelivattr VALUES ("+pdattr[i].getPdattribid()+","+pdattr[i].getProw()+","+pdattr[i].getAttribdefid()+",'"+pdattr[i].getMvalue()+"')");
			}
		}
		catch (SQLException e)
		{
			PsDebug.log("PssPublisherWSDL: SQLException: "+e.getMessage());
			return 1;
		}

		return 0;
	}


}