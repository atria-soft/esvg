/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <vector>
#include <etk/etk.h>
#include <esvg/esvg.h>

#undef __class__
#define __class__ "converter"

static void usage() {
	TEST_PRINT(etk::getApplicationName() << " - help : ");
	TEST_PRINT("    " << etk::getApplicationName() << " [options]");
	TEST_PRINT("        --file=xxx   convert file in the same file.bmp");
	exit(-1);
}

int main(int _argc, const char *_argv[]) {
	etk::init(_argc, _argv);
	std::string inputFile;
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (etk::start_with(data, "--file=") == true) {
			inputFile = std::string(&data[7]);
			TEST_PRINT("file='" << inputFile << "'");
		} else if (    data == "-h"
		            || data == "--help") {
			usage();
		}
	}
	if (inputFile == "") {
		TEST_ERROR("Missing '--file' option");
		usage();
	}
	esvg::Document doc;
	doc.load(inputFile);
	doc.generateAnImage(ivec2(512, 512), inputFile + ".bmp");
}
