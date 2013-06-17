#include "ScriptEngineMain.h"
#include <boost\python.hpp>
#include <boost\python\detail\wrap_python.hpp>
#include <iostream>
#include <vector>
#include <string>

///
///\brief minto exposes the minto module for all plugin writers.
/// This module is embedded into the python startup path at startup.
/// 
/// A plugin simply imports the module in the standard way and call its method: 
/// <code>
/// import minto
/// print minto.api_version()
/// </code>
///

class minto {

public:
	static std::string api_version() { return "0.1"; }
	static void log_message(const std::string& sender_, const std::string& msg_) {
		std::cout<<"[minto] "<<sender_<<" : "<<msg_<<std::endl;
	}
};

BOOST_PYTHON_MODULE(minto)
{
	using namespace boost::python;
	def("api_version", &minto::api_version);
	def("log_message", &minto::log_message);

	
}

class ScriptEngineMain::ScriptEngine {

	PyObject* pyPluginManager;

public:
	
	ScriptEngine() {
	
	}

	///
	///\brief 
	///
	void initializePyEngine() {
		Py_Initialize();
	}

	void pre_engine_setup() {
		PyImport_AppendInittab("minto", initminto);
	}

	void set_plugin_HomeBase() {

		PyObject *sys_path; 
		PyObject *path; 

		sys_path = PySys_GetObject("path"); 
		if (sys_path == NULL) 
			return; 
		path = PyString_FromString("C:\\Amit\\dev\\cpp\\of_v0.7.4_vs2010_release\\of_v0.7.4_vs2010_release\\apps\\myApps\\alpha-goldDust\\bin\\plug\\py\\api") ;
		if (path == NULL) 
			return; 
		if (PyList_Append(sys_path, path) < 0) 
			return;

	}

	///
	///\brief imports the main py module we are using for this framework
	///
	void importPluginsController() {
		pyPluginManager = PyImport_ImportModule("drawingboard");

		if(pyPluginManager == NULL) {
			//error - todo
		}
		
		PyObject* pyVer = PyObject_GetAttrString(pyPluginManager, "version");
		if(pyVer == NULL) {
			// todo
		}

		/* convert version info into c string */
		char* verStr = NULL;
		PyArg_Parse(pyVer, "s", &verStr);
		std::cout<<"ctrl module version: "<<verStr<<std::endl;
		Py_DECREF(pyVer);

		// version compatibilty check

	}

	void load_plugins() {

		if(pyPluginManager == NULL) {
			//todo - error
			std::cout<<"plugin manager is null"<<std::endl;
		}

		PyObject* pyload_plugin_method = PyObject_GetAttrString(pyPluginManager, "test_main"); //"load_plugins");
		if(pyload_plugin_method == NULL) {
			std::cout<<"no load_plugins method found "<<std::endl;
		}

		//todo - measure performance 

		PyObject* pycall_result = PyEval_CallObject(pyload_plugin_method, NULL);
		if(pycall_result == NULL) {
			//todo
			std::cout<<"null returned from calling load_plugins"<<std::endl;
		}
		if(PyErr_Occurred()) {

			PyErr_Print();
		}

		PyObject* pyplugin_iterator = PyObject_GetIter(pycall_result);
		if(pyplugin_iterator == NULL) {
			//todo

			// test method


		}

		PyObject* pyplugin_instance;
		while(pyplugin_instance = PyIter_Next(pyplugin_iterator)) {
			
			std::cout<<"found plugin instance"<<std::endl;


			//add to PluginHolder::addPlugin()

		}

		// after all the plugins have been instantiated, we can call a test method an verify
		PyObject* pyload_post_plugin_method = PyObject_GetAttrString(pyPluginManager, "testExecute"); 
		if(pyload_post_plugin_method  == NULL) {
			std::cout<<"no testExecute method found "<<std::endl;
		}

		//todo - measure performance 

		PyObject* pycall_testExecute_result = PyEval_CallObject(pyload_post_plugin_method, NULL);
		if(pycall_testExecute_result == NULL) {
			//todo
			std::cout<<"null returned from calling testExecute"<<std::endl;
		}
		if(PyErr_Occurred()) {

			PyErr_Print();
		}


		Py_DECREF(pycall_testExecute_result); // if the result failed, then freeing causes crash !! Amits
		Py_DECREF(pyload_post_plugin_method);
		
		Py_DECREF(pyplugin_iterator);
		Py_DECREF(pycall_result);
		Py_DECREF(pyload_plugin_method);


	}


	void testEngine() {

	}
};

ScriptEngineMain& ScriptEngineMain::instance() {
	static ScriptEngineMain seMain;
	return seMain;
}

ScriptEngineMain::ScriptEngineMain() {
	_spScriptEngine.reset(new ScriptEngineMain::ScriptEngine());
}

void ScriptEngineMain::initializeEngine() {

	if(!_spScriptEngine) {
		// todo - throw exception
		std::cout<<"ScriptEngine not initialized"<<std::endl;
		return;
	}
		_spScriptEngine->pre_engine_setup();
		_spScriptEngine->initializePyEngine();
		_spScriptEngine->set_plugin_HomeBase();
		_spScriptEngine->importPluginsController();
		_spScriptEngine->load_plugins();

	
}

void ScriptEngineMain::testEngine() {
	if(!_spScriptEngine) {
		//throw error
		return;
	}

		_spScriptEngine->testEngine();
}
