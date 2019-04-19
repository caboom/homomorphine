#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/config/user.hpp>
#include <boost/program_options.hpp>

#include "info.h"
#include "config.h"

using namespace std;
using namespace Morphine;
 
void init()
{
  static const std::string COMMON_FMT("[%TimeStamp%][%Severity%]:  %Message%");

  boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

  // Just a very simple console log
  boost::log::add_console_log(
    std::cout,
    boost::log::keywords::format = COMMON_FMT,
    boost::log::keywords::auto_flush = true
  );

  boost::log::add_common_attributes();

  // Don't output anything below INFO severity for release
#ifndef _DEBUG
  boost::log::core::get()->set_filter(
    boost::log::trivial::severity >= boost::log::trivial::info
  );
#endif
}

unordered_map<string, string>* parseCommandLine(int argc, char *argv[]) 
{
  unordered_map<string, string>* options = new unordered_map<string, string>();

  namespace po = boost::program_options;

  // atm only parameter we are using is --config
  // otherwise we're returning emtpy option
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "help infomation")
    ("config", po::value<string>(), "configuration file")
  ;

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);
  po::notify(vm);   

  if (vm.count("help")) {
    BOOST_LOG_TRIVIAL(info) << desc;
  }
  if (vm.count("config")) {
    (*options)["config"] = vm["config"].as<string>();
  }

  return options;
}


int main (int argc, char *argv[])
{
  Config* config = new Config();
  unordered_map<string, string>* options;

  // initialize logger 
  init();

  // parse command line arguments
  options = parseCommandLine(argc, argv); 

  if (!options->count("config")) {
    BOOST_LOG_TRIVIAL(fatal) << "Configuration file not set - exiting";
    return EXIT_FAILURE;
  }

  // parse configuration 

  // start morphine
  BOOST_LOG_TRIVIAL(info) << "Starting Morphine version " << MORPHINE_VERSION_MAJOR << "." << MORPHINE_VERSION_MINOR;  

  return EXIT_SUCCESS;
}