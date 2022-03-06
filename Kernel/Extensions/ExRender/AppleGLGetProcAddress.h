#ifdef MAC_OS_X_VERSION_10_3
#include <dlfcn.h>
#else
#include <mach-o/dyld.h>
#endif

static void* AppleGLGetProcAddress (const GLubyte *name)
{
#ifdef MAC_OS_X_VERSION_10_3
  static struct GLLibrary
  {
    void * glLibrary;
    GLLibrary(const char * glLibPath)
    {
      glLibrary = dlopen(glLibPath, RTLD_LAZY);
      if (!glLibrary)
      {
        const char * error = dlerror();
        // handle error
      }
    }
    ~GLLibrary()
    {
      if (glLibrary)
      {
        if (dlclose(glLibrary) != 0)
        {
          // problem...
        }
        glLibrary = NULL;
      }
    }
    operator void *()
    {
      return glLibrary;
    }
  } cGLLibrary("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL");
  if(name == NULL) return NULL;
  if(cGLLibrary == NULL) return NULL;
  return dlsym(cGLLibrary, (const char*)name);
#else
  static const struct mach_header* image = NULL;
  NSSymbol symbol;
  char* symbolName;
  if (NULL == image)
  {
    image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
  }
  /* prepend a '_' for the Unix C symbol mangling convention */
  symbolName = (char*)malloc(strlen((const char*)name) + 2);
  strcpy(symbolName+1, (const char*)name);
  symbolName[0] = '_';
  symbol = NULL;
  /* if (NSIsSymbolNameDefined(symbolName))
  symbol = NSLookupAndBindSymbol(symbolName); */
  symbol = image ? NSLookupSymbolInImage(image, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR) : NULL;
  free(symbolName);
  return symbol ? NSAddressOfSymbol(symbol) : NULL;
#endif
}
