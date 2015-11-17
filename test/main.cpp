/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <vector>
#include <gtest/gtest.h>
#include <etk/etk.h>

#undef __class__
#define __class__ "esvg::test"

int main(int _argc, const char *_argv[]) {
	::testing::InitGoogleTest(&_argc, const_cast<char **>(_argv));
	etk::init(_argc, _argv);
	//etk::initDefaultFolder("esvg-test");
	return RUN_ALL_TESTS();
}
