#pragma once

#include <boost\shared_ptr.hpp>

///
///\class ScriptEngineMain 
///\brief This class is responsible for all connection with the rest of the framework. Using signals/callbacks scheme.
///

class ScriptEngineMain {

public:
	void initializeEngine();
	void testEngine();
	static ScriptEngineMain& instance();
private:

	ScriptEngineMain();

	class ScriptEngine;
	typedef boost::shared_ptr<ScriptEngine> SPScriptEngine;
	SPScriptEngine _spScriptEngine;

};