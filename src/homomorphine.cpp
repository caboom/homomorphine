#include <string>
#include <unordered_map>
#include <exception>
#include <iostream>
#include <signal.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/config/user.hpp>
#include <boost/program_options.hpp>

#include "info.hpp"
#include "config.hpp"
#include "server.hpp"

using namespace std;
using namespace homomorphine;

static Server server;
static int s_interrupted = 0;

static void s_signal_handler (int signal_value)
{
    s_interrupted = signal_value;
}

static void s_init()
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

static unordered_map<string, string>* parseCommandLine(int argc, char *argv[]) 
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

static void eventLoop() {
  struct sigaction action;
  action.sa_handler = s_signal_handler;
  action.sa_flags = 0;
  sigemptyset (&action.sa_mask);
  sigaction (SIGINT, &action, NULL);
  sigaction (SIGTERM, &action, NULL);

  while (true) { 
	  if (s_interrupted) {
      server.stop();

	    action.sa_handler = SIG_DFL; 
	    sigaction(SIGINT, &action, NULL);
	    raise(SIGINT);
    }

    sleep(1);
	}
}

int main (int argc, char *argv[])
{
  Config config;
  unordered_map<string, string>* options;

  // initialize logger & signal handler
  s_init();

  // parse command line arguments
  options = parseCommandLine(argc, argv); 

  if (!options->count("config")) {
    BOOST_LOG_TRIVIAL(fatal) << "Configuration file not set - exiting";
    return EXIT_FAILURE;
  }

  // parse configuration 
  config.init((*options)["config"]);

  // start morphine
  BOOST_LOG_TRIVIAL(info) << "Starting Homomorphine version " << HOMOMORPHINE_VERSION_MAJOR << "." << HOMOMORPHINE_VERSION_MINOR;  

  server.init(config);
  server.run();

  // wait for SIGINT or SIGTERM
  eventLoop();  

  return EXIT_SUCCESS;
}