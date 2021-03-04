#define WALL_WRN_PUSH				  \
	__pragma(warning( push ))		  \
	__pragma(warning(disable : 4005)) \
	__pragma(warning(disable : 4100)) \
	__pragma(warning(disable : 4365)) \
	__pragma(warning(disable : 4514)) \
	__pragma(warning(disable : 4515)) \
	__pragma(warning(disable : 4571)) \
	__pragma(warning(disable : 4625)) \
	__pragma(warning(disable : 4626)) \
	__pragma(warning(disable : 4668)) \
	__pragma(warning(disable : 4710)) \
	__pragma(warning(disable : 4711)) \
	__pragma(warning(disable : 4774)) \
	__pragma(warning(disable : 4820)) \
	__pragma(warning(disable : 4996)) \
	__pragma(warning(disable : 5026)) \
	__pragma(warning(disable : 5027)) \
	__pragma(warning(disable : 5039)) \
	__pragma(warning(disable : 5045)) \

#define WALL_WRN_POP \
	__pragma(warning( pop ))