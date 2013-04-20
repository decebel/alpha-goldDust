#include "ScriptEngineBridger.h"
#include <vector>
#include <boost/python.hpp>

namespace python = boost::python;

// An abstract base class
class Base : public boost::noncopyable
{
public:
  virtual ~Base() {};
  virtual std::string hello() = 0;
};

// C++ derived class
class CppDerived : public Base
{
public:
  virtual ~CppDerived() {}
  virtual std::string hello() { return "Hello from C++!";}
};



// Familiar Boost.Python wrapper class for Base
struct BaseWrap : Base, python::wrapper<Base>
{
  virtual std::string hello() 
  {
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    // workaround for VC++ 6.x or 7.0, see
    // http://boost.org/libs/python/doc/tutorial/doc/html/python/exposing.html#python.class_virtual_functions
    return python::call<std::string>(this->get_override("hello").ptr());
#else
	std::string s("hello");
	return python::call<std::string>(this->get_override("hello").ptr());
	//return this->get_override("hello")();
#endif
  }
};

// Pack the Base class wrapper into a module
BOOST_PYTHON_MODULE(embedded_hello)
{
  python::class_<BaseWrap, boost::noncopyable> base("Base");
}

/// 
/// \TODO: move to appropriate header
struct DataSchema {

};


class DataDriver {

};

class DataDriverStats {

};



struct SpringBoardDataManager {


	std::string version() const {
		return "0.1";
	}

	///
	/// \brief plugins can use this method to perform app logging 
	///
	/// \param[in] msg_ message to log
	/// \return void
	///

	void log_message(const std::string& msg_) const {

	}

	///
	/// \brief plugins can use this method to display an error message
	///
	/// \param[in] msg_ message to display
	/// \param[in] sender_ sender name. usually the plugin name
	///

	void error_message(const std::string& msg_, const std::string& sender_) {

	}
	
	std::vector<std::string> get_all_market_names() {

		std::vector<std::string> v;
		return v;
	}


	std::vector<std::string> get_market_streams(const std::string& marketname_) {
		std::vector<std::string> v;
		return v;
	}


	DataSchema get_stream_schema(const std::string& stream_) {
		return DataSchema();
	}

	DataDriver* get_input_datadriver(const std::string& driver_) {
		return 0;
	}

	DataDriver* get_output_datadriver(const std::string& driver_) {
		return 0;
	}

	DataDriverStats  get_stream_stats(const std::string& stream_) {
		return DataDriverStats ();
	}


	bool set_new_stream(const std::string& streamname_, const DataSchema& schema_) {
		return true;
	}

	void bind(const std::string& stream_, DataDriver* driver_, const std::string& filter_) {

	}

	void unbind(const std::string& stream_, const DataDriver* driver_, const std::string& filter_) {

	}

	void onData(const std::string& stream_, const std::string& tuple) {

	}




};


void exec_test()
{
    std::cout << "registering extension module embedded_hello..." << std::endl;
  
  // Initialize the interpreter
  Py_Initialize();

  // Register the module with the interpreter
  if (PyImport_AppendInittab("embedded_hello", initembedded_hello) == -1)
    throw std::runtime_error("Failed to add embedded_hello to the interpreter's "
                 "builtin modules");

  std::cout << "defining Python class derived from Base..." << std::endl;
  
  // Retrieve the main module
  python::object main = python::import("__main__");
  
  // Retrieve the main module's namespace
  python::object global(main.attr("__dict__"));

  // Define the derived class in Python.
  python::object result = python::exec(
    "from embedded_hello import *        \n"
    "class PythonDerived(Base):          \n"
    "    def hello(self):                \n"
    "        return 'Hello from Python!' \n",
    global, global);

  python::object PythonDerived = global["PythonDerived"];

  // Creating and using instances of the C++ class is as easy as always.
  CppDerived cpp;
  //BOOST_TEST(cpp.hello() == "Hello from C++!");

  std::cout << "testing derived class from C++..." << std::endl;
  
  // But now creating and using instances of the Python class is almost
  // as easy!
  python::object py_base = PythonDerived();
  Base& py = python::extract<Base&>(py_base) BOOST_EXTRACT_WORKAROUND;

  // Make sure the right 'hello' method is called.
  //BOOST_TEST(py.hello() == "Hello from Python!");

  std::cout << "success!" << std::endl;
}

ScriptEngineBridger& ScriptEngineBridger::instance() {
	static ScriptEngineBridger instance;
	return instance;
}

class Scope {

public:
	
	python::object scope;
	python::object scope_dict;

	void initialize(const std::string& module = "__main__") {

		// Retrieve the module
		scope = python::import(module.c_str());
  
		// Retrieve the module's namespace
		scope_dict  = (scope.attr("__dict__"));
	
	}

	void loadPluginManagerModule() {


	}

	void loadPlugins() {



	}




};

class ScriptEngineBridger::ScriptEngine {

public:
	ScriptEngine() {}

	void initialize() {
		
	}

	void testEngine() {
		exec_test();
	}
};

ScriptEngineBridger::ScriptEngineBridger() {
	initializeEngine();
}

void ScriptEngineBridger::initializeEngine() {

	_spScriptEngine.reset(new ScriptEngineBridger::ScriptEngine());
}

void ScriptEngineBridger::testEngine() {
	if(_spScriptEngine) 
		_spScriptEngine->testEngine();
}

