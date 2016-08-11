//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include "glFramework.h"

int main( int argc, char *argv[] )
{
	GlFramework* framework = GlFramework::createInstance();
	GlFramework::InitArg arg;
	{
		arg.argc = argc;
		arg.argv = argv;
	}
	framework->initialize( arg );
	framework->mainLoop();
	framework->finalize();
	GlFramework::deleteInstance();
	return 0;
}
