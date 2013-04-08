
#pragma once

#if defined(DATAFLOW_EXPORTS)
#define DATAFLOW_API_EXPORTS __declspec(dllexport)
#else
#define DATAFLOW_API_EXPORTS __declspec(dllimport)
#endif

namespace DF
{
	/// Initialize the library
void DATAFLOW_API_EXPORTS initializeDataFlow();

	/// UnInitialize the library
void DATAFLOW_API_EXPORTS unInitializeDataFlow();

}