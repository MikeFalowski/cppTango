//=============================================================================
//
// file :               DServerClass.h
//
// description :        Include for the DServerClass class. This class is a 
//                      singleton class i.e only one object of this class
//			can be created.
//			It contains all properties and methods
//			which the DServer requires only once e.g. the
//			commands.
//			This file also includes class declaration for all the 
//			commands available on device of the DServer class
//
// project :            TANGO
//
// author(s) :          A.Gotz + E.Taurel
//
// $Revision$
//
// $Log$
// Revision 2.7  2002/12/16 10:16:21  taurel
// - New method get_device_list() in Util class
// - Util::get_class_list takes DServer device into account
// - Util::get_device_by_name() takes DServer device into account
// - Util::get_device_list_by_class() takes DServer device into account
// - New parameter to the attribute::set_value() method to enable CORBA to free
// memory allocated for the attribute
//
// Revision 2.6  2002/10/17 07:43:06  taurel
// Fix bug in history stored by the polling thread :
// - We need one copy of the attribute data to build an history!!! It is true
// also for command which return data created by the DeviceImpl::create_xxx
// methods. Chnage in pollring.cpp/pollring.h/dserverpoll.cpp/pollobj.cpp
// and pollobj.h
//
// Revision 2.5  2002/10/15 11:27:19  taurel
// Fix bugs in device.cpp file :
// - Protect the state and status CORBA attribute with the device monitor
// Add the "TgLibVers" string as a #define in tango_config.h
//
// Revision 2.4  2002/08/12 15:06:54  taurel
// Several big fixes and changes
//   - Remove HP-UX specific code
//   - Fix bug in polling alogorithm which cause the thread to enter an infinite
//     loop (pollthread.cpp)
//   - For bug for Win32 device when trying to set attribute config
//     (attribute.cpp)
//
// Revision 2.3  2002/07/02 15:22:24  taurel
// Miscellaneous small changes/bug fixes for Tango CPP release 2.1.0
//     - classes reference documentation now generated using doxygen instead of doc++
//     - A little file added to the library which summarizes version number.
//       The RCS/CVS "ident" command will now tells you that release library x.y.z is composed
//       by C++ client classes set release a.b and C++ server classes set release c.d
//     - Fix incorrect field setting for DevFailed exception re-thrown from a CORBA exception
//     - It's now not possible to poll the Init command
//     - It's now possible to define a default class doc. per control system
//       instance (using property)
//     - The test done to check if attribute value has been set before it is
//       returned to caller is done only if the attribute quality is set to VALID
//     - The JTCInitialize object is now stored in the Util
//     - Windows specific : The tango.h file now also include winsock.h
//
// Revision 2.2  2002/04/30 10:50:41  taurel
// Don't check alarm on attribute if attribute quality factor is INVALID
//
// Revision 2.1  2002/04/29 12:24:03  taurel
// Fix bug in attribute::set_value method and on the check against min and max value when writing attributes
//
// Revision 2.0  2002/04/09 14:45:10  taurel
// See Tango WEB pages for list of changes
//
// Revision 1.6  2001/10/08 09:03:13  taurel
// See tango WEB pages for list of changes
//
// Revision 1.5  2001/07/04 12:27:10  taurel
// New methods re_throw_exception(). Read_attributes supports AllAttr mnemonic A new add_attribute()method in DeviceImpl class New way to define attribute properties New pattern to prevent full re-compile For multi-classes DS, it is now possible to use the Util::get_device_by_name() method in device constructor Adding << operator ovebloading Fix devie CORBA ref. number when device constructor sends an excep.
//
// Revision 1.4  2001/05/04 09:28:13  taurel
// Fix bugs in DServer::restart() method and in Util::get_device_by_name() method
//
// Revision 1.3  2001/03/30 08:03:45  taurel
// Fix bugs in attributes. For linux, add signal_handler in its own thread, change the way to kill server. For all system, change DevRestart philosophy.
//
// Revision 1.2  2001/03/09 08:20:16  taurel
// Fix bug in the MultiClassAttribute::init_class_attribute() method. Also remove the DbErr_DeviceNotDefined define.
//
// Revision 1.1.1.1  2001/02/27 08:46:20  taurel
// Imported sources
//
// Revision 1.3  2000/04/13 10:40:41  taurel
// Added attribute support
//
// Revision 1.2  2000/02/04 11:00:14  taurel
// Just update revision number
//
// Revision 1.1.1.1  2000/02/04 10:58:28  taurel
// Imported sources
//
//
// copyleft :           European Synchrotron Radiation Facility
//                      BP 220, Grenoble 38043
//                      FRANCE
//
//=============================================================================

#ifndef _DSERVERCLASS_H
#define _DSERVERCLASS_H

#include <tango.h>

namespace Tango
{

//=============================================================================
//
//			The DevRestart class
//
// description :	Class to implement the DevRestart command. This command
//			needs one input argument and no outout argument.
//			The input argument is the name of the device to be
//			re-started.
//			This class delete and re-create a device
//
//=============================================================================

 
class DevRestartCmd : public Command
{
public:


	DevRestartCmd(const char *cmd_name,
		      Tango::CmdArgType in,
		      Tango::CmdArgType out,
		      const char *desc);	
	~DevRestartCmd() {};
	
	virtual CORBA::Any *execute(DeviceImpl *device, const CORBA::Any &in_any);
};

//=============================================================================
//
//			The DevRestartServerCmd class
//
// description :	Class to implement the DevKill command. This 
//			command does not take any input argument. It simply
//			kills the device server.
//
//=============================================================================

 
class DevRestartServerCmd : public Command
{
public:

	DevRestartServerCmd(const char *cmd_name,
		   	    Tango::CmdArgType in,Tango::CmdArgType out);
		   
	~DevRestartServerCmd() {};
	
	virtual CORBA::Any *execute (DeviceImpl *, const CORBA::Any &);
};

//=============================================================================
//
//			The DevQueryClassCmd class
//
// description :	Class to implement the DevQueryClass command. This 
//			command does not take any input argument and return a 
//			list of all the classes created inside the device
//			server process
//
//=============================================================================

 
class DevQueryClassCmd : public Command
{
public:

	DevQueryClassCmd(const char *cmd_name,
			 Tango::CmdArgType in,
			 Tango::CmdArgType out,
			 const char *desc);
			 
	~DevQueryClassCmd() {};
	
	virtual CORBA::Any *execute(DeviceImpl *device, const CORBA::Any &in_any);
};

//=============================================================================
//
//			The DevQueryDeviceCmd class
//
// description :	Class to implement the DevQueryDevice command. This 
//			command does not take any input argument and return a 
//			list of all the devices created inside the device
//			server process
//
//=============================================================================

 
class DevQueryDeviceCmd : public Command
{
public:

	DevQueryDeviceCmd(const char *cmd_name,
			  Tango::CmdArgType in,Tango::CmdArgType out,
			  const char *desc);
			  
	~DevQueryDeviceCmd() {};
	
	virtual CORBA::Any *execute(DeviceImpl *device, const CORBA::Any &in_any);
};


//=============================================================================
//
//			The DevKillCmd class
//
// description :	Class to implement the DevKill command. This 
//			command does not take any input argument. It simply
//			kills the device server.
//
//=============================================================================

 
class DevKillCmd : public Command
{
public:

	DevKillCmd(const char *cmd_name,
		   Tango::CmdArgType in,Tango::CmdArgType out);
		   
	~DevKillCmd() {};
	
	virtual CORBA::Any *execute (DeviceImpl *, const CORBA::Any &);
};

//=============================================================================
//
//			The DevSetTraceLevelCmd class
//
// description :	Class to implement the DevSetTracelevel command.
//			It updates device server trace level with the input 
//			argument
//
//=============================================================================

 
class DevSetTraceLevelCmd : public Command
{
public:

	DevSetTraceLevelCmd(const char *cmd_name,
			    Tango::CmdArgType in,
			    Tango::CmdArgType out,
			    const char *desc);
			    
	~DevSetTraceLevelCmd() {};
	
	virtual CORBA::Any *execute(DeviceImpl *device, const CORBA::Any &in_any);
};

//=============================================================================
//
//			The DevGetTraceLevel class
//
// description :	Class to implement the DevGetTracelevel command.
//			It simply returns the device server trace level
//
//=============================================================================

 
class DevGetTraceLevelCmd : public Command
{
public:

	DevGetTraceLevelCmd(const char *cmd_name,
			    Tango::CmdArgType in,
			    Tango::CmdArgType out,
			    const char *desc);
			    
	~DevGetTraceLevelCmd() {};
	
	virtual CORBA::Any *execute (DeviceImpl *device, const CORBA::Any &in_any);
};

//=============================================================================
//
//			The DevSetTraceOutputCmd class
//
// description :	Class to implement the DevSetTraceOutput command.
//			It set the server output to the input parameter
//
//=============================================================================

 
class DevSetTraceOutputCmd : public Command
{
public:

	DevSetTraceOutputCmd(const char *cmd_name,
			     Tango::CmdArgType in,
			     Tango::CmdArgType out,
			     const char *desc);
			     
	~DevSetTraceOutputCmd() {};
	
	virtual CORBA::Any *execute (DeviceImpl *device, const CORBA::Any &in_any);
};

//=============================================================================
//
//			The DevGetTraceOutputCmd class
//
// description :	Class to implement the DevGetTracelevel command.
//			It simply returns the device server trace level
//
//=============================================================================

 
class DevGetTraceOutputCmd : public Command
{
public:

	DevGetTraceOutputCmd(const char *cmd_name,
			     Tango::CmdArgType in,
			     Tango::CmdArgType out,
			     const char *desc);
			     
	~DevGetTraceOutputCmd() {};
	
	virtual CORBA::Any *execute (DeviceImpl *device, const CORBA::Any &in_any);
};


//=============================================================================
//
//			The DServerClass class
//
// description :	This class is a singleton ( The constructor is 
//			protected and the _instance data member is static)
//			It contains all properties and methods
//			which the DServer objects requires only once e.g. the
//			commands. 
//
//=============================================================================

 
class DServerClass : public DeviceClass
{
public:

	static DServerClass *instance();
	static DServerClass *init();
	
	~DServerClass() {};
	
	void command_factory();
	void device_factory(const Tango::DevVarStringArray *devlist);
	
protected:
	DServerClass(string &);
	static DServerClass *_instance;	
};

} // End of Tango namespace

#endif // _DSERVERCLASS_H