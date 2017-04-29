#include "config.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace http {
namespace server {

using namespace std;

config::config(string filename) {
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(filename, pt);

	update_refresh_rate_ = pt.get<float>("ServerSettings.update_refresh_rate");
	welcome_message_ = pt.get<string>("ServerSettings.welcome_message");
	server_name_ = pt.get<string>("ServerSettings.server_name");
	remove_delay_ = pt.get<double>("ServerSettings.remove_delay");
	allow_teleport_ = pt.get<bool>("ServerSettings.allow_teleport");
	debug_ = pt.get<bool>("ServerSettings.debug");
	log_file_ = pt.get<string>("ServerSettings.log_file");
	
	allow_other_maps_ = pt.get<bool>("ServerSettings.allow_other_maps");
	boost::property_tree::ptree children = pt.get_child("Maps");
	for (const auto& v : children) {
		map_list_.push_back(make_pair(v.first.data(), v.second.data()));
	}
}

vector<pair<string,string>> config::get_map_list() {
	return map_list_;
}

float config::get_update_refresh_rate() {
	return update_refresh_rate_;
}

string config::get_welcome_message() {
	return welcome_message_;
}

string config::get_server_name() {
	return server_name_;
}

double config::get_remove_delay() {
	return remove_delay_;
}

bool config::get_allow_teleport() {
	return allow_teleport_;
}

bool config::get_debug() {
	return debug_;
}

bool config::get_allow_other_maps() {
	return allow_other_maps_;
}

string config::get_log_file() {
	return log_file_;
}

} // namespace server
} // namespace http
