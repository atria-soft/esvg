/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license MPL v2.0 (see license file)
 */

#include <test-debug/debug.hpp>
#include <vector>
#include <etk/etk.hpp>
#include <esvg/esvg.hpp>

static void usage() {
	TEST_PRINT(etk::getApplicationName() << " - help : ");
	TEST_PRINT("    " << etk::getApplicationName() << " [options]");
	TEST_PRINT("        --file=xxx   convert file in the same file.bmp");
	TEST_PRINT("        --visual     Enable visual display for debugging the lib");
	exit(-1);
}

int main(int _argc, const char *_argv[]) {
	etk::init(_argc, _argv);
	std::string inputFile;
	bool visualTest = false;
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (etk::start_with(data, "--file=") == true) {
			inputFile = std::string(&data[7]);
			TEST_PRINT("file='" << inputFile << "'");
		} else if (data == "--visual") {
			visualTest = true;
			TEST_PRINT("Set visual debug");
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
	doc.generateAnImage(ivec2(512, 512), inputFile + ".bmp", visualTest);
}

