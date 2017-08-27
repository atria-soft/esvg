/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <test-debug/debug.hpp>
#include <etk/Vector.hpp>
#include <gtest/gtest.h>
#include <etk/etk.hpp>

bool g_visualDebug = false;


int main(int _argc, const char *_argv[]) {
	::testing::InitGoogleTest(&_argc, const_cast<char **>(_argv));
	etk::init(_argc, _argv);
	for (int32_t iii=0; iii<_argc ; ++iii) {
		etk::String data = _argv[iii];
		#ifdef DEBUG
		if (data == "--visual-test") {
			TEST_PRINT("visual-test=enable");
			g_visualDebug = true;
		} else 
		#endif
		if (    data == "-h"
		     || data == "--help") {
			TEST_PRINT("esvg-test - help : ");
			TEST_PRINT("    " << _argv[0] << " [options]");
			#ifdef DEBUG
				TEST_PRINT("        --visual-test   Enable decoration in logged file in debug mode only");
			#else
				TEST_PRINT("        No optiions ...");
			#endif
			return -1;
		}
	}
	//etk::initDefaultFolder("esvg-test");
	return RUN_ALL_TESTS();
}
