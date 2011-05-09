
/*
	Copyright (c) 2009 by Chad Nelson
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/optional.hpp>
//#include <boost/regex.hpp> // For the 'test' option

#include "markdown.h"

using std::cerr;
using std::cout;
using std::endl;

namespace {

	class Options {
		public:
		Options(): mDebug(false), mTest(false) { }

		bool readOptions(int argc, char *argv[]);

		void showHelp();

		bool debug() const { return mDebug; }
		bool test() const { return mTest; }
		std::string inputFile() const { return mInputFile; }

		private:
		std::string mInputFile;
		bool mDebug, mTest;
	};

	bool Options::readOptions(int argc, char *argv[]) {
		bool help=false, err=false;
		for (int x=1; x<argc && !help && !err; ++x) {
			if (argv[x][0]=='-' && argv[x][1]=='-' && argv[x][2]!=0) {
				// It's a full-word option.
				std::string opt(argv[x]+2);
				if (opt=="debug") {
					mDebug=true;
				} else if (opt=="test") {
					mTest=true;
				} else if (opt=="help") {
					help=true;
				} else {
					err=true;
					cerr << "Unknown option " << argv[x] << ", use -? for help."
						<< endl;
				}
			} else if (argv[x][0]=='-') {
				// It's one or more option flags.
				const char *i=argv[x]+1;
				while (*i!=0 && !help && !err) {
					switch (*i) {
						case '?': help=true; break;
						case 'd': mDebug=true; break;

						default:
						err=true;
						cerr << "Uknown option flag '" << *i << "', use -? for "
							"help." << endl;
					}
					++i;
				}
			} else {
				// It's a parameter.
				if (mInputFile.empty()) {
					mInputFile=argv[x];
				} else {
					err=true;
					cerr << "Too many parameters. Already had '" << mInputFile
						<< "', found '" << argv[x] << "' too. Use -? for help."
						<< endl;
				}
			}
		}

		if (help) {
			showHelp();
			return false;
		} else if (err) {
			return false;
		} else return true;
	}

	void Options::showHelp() {
		const char *cHelpScreen=
			"This program converts input (from an input file or stdin) from Markdown syntax\n"
			"to HTML using the cpp-markdown library.\n"
			"\n"
			"Usage:\n"
			"    cpp-markdown [<option>...] [input-file]\n"
			"\n"
			"Available options are:\n"
			"    -?, --help      Show this screen.\n"
			"    -d, --debug     Show tokens instead of HTML output.\n";
		cerr << endl << cHelpScreen << endl;
	}

} // namespace

int main(int argc, char *argv[]) {
	Options cfg;
	if (!cfg.readOptions(argc, argv)) return 1;

//	if (cfg.test()) {
//		return 1;
//	}

	std::ifstream ifile;

	std::istream *in=&std::cin;
	if (!cfg.inputFile().empty()) {
		cerr << "Reading file '" << cfg.inputFile() << "'..." << endl;
		ifile.open(cfg.inputFile().c_str());
		if (!ifile) {
			cerr << "Error: Can't open file." << endl;
			return 1;
		} else in=&ifile;
	} else cerr << "Reading standard input..." << endl;

	markdown::Document doc;
	doc.read(*in);

	if (cfg.debug()) doc.writeTokens(cout);
	else doc.write(cout);

	return 0;
}
