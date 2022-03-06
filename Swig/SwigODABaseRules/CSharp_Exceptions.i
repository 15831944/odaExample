/* File : CSharp_Exceptions.i */
#if defined(SWIGCSHARP)
%insert(runtime)
%{
	typedef void (SWIGSTDCALL* CSharpExceptionCallback_t)(OdErrorContext*);
	CSharpExceptionCallback_t OdErrorExceptionCallback = NULL;
	extern "C" SWIGEXPORT
	void SWIGSTDCALL CustomExceptionRegisterCallback(CSharpExceptionCallback_t customCallback) 
	{
		OdErrorExceptionCallback = customCallback;
	}
	
	// addref injection
	static void AddContextRef(OdErrorContext* Context)
	{
		Context->addRef();
	}

	static void ReleaseContextRef(OdErrorContext* Context)
	{
		Context->release();
	}
	
	// Note that SWIG detects any method calls named starting with
	// SWIG_CSharpSetPendingException for warning 845
	static void SWIG_CSharpSetPendingExceptionCustom(OdErrorContext* NewContext) 
	{
		AddContextRef(NewContext);
		OdErrorExceptionCallback(NewContext);
	}
%}

%pragma(csharp) imclasscode=
%{
	class CustomExceptionHelper 
	{
		// C# delegate for the C/C++ customExceptionCallback
		public delegate void CustomExceptionDelegate(IntPtr NewContext);
		static CustomExceptionDelegate customDelegate = new CustomExceptionDelegate(SetPendingCustomException);
		[DllImport("$dllimport", EntryPoint="CustomExceptionRegisterCallback")]
		public static extern
		void CustomExceptionRegisterCallback(CustomExceptionDelegate customCallback);
		static void SetPendingCustomException(IntPtr NewContext) 
		{
			SWIGPendingException.Set(new Teigha.Core.OdError(new Teigha.Core.OdErrorContext(NewContext, true)));
		}
		static CustomExceptionHelper() 
		{
			CustomExceptionRegisterCallback(customDelegate);
		}
	}
	static CustomExceptionHelper exceptionHelper = new CustomExceptionHelper();
%}

%exception 
{
	try 
	{
		$action
	}
	catch (OdError& Err) 
	{
		SWIG_CSharpSetPendingExceptionCustom(Err.context());
		return $null;
	}
}
#endif
