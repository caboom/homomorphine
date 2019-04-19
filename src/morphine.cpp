#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/config/user.hpp>

#include "info.h"
 
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

int main (int argc, char *argv[])
{
  init();

  BOOST_LOG_TRIVIAL(info) << "Starting Morphine version " << MORPHINE_VERSION_MAJOR << "." << MORPHINE_VERSION_MINOR;

  return EXIT_SUCCESS;
}