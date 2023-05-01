#ifndef _BREAKABLES_H_
#define _BREAKABLES_H_
#include <map>
#include <string>

using namespace std;

const map<string,string> breakable1 = {
	{"32,48", "c60"}, {"64,48", "c60"}, {"96,48", "c60"}, {"128,48", "c60"},
	{"144,64", "c60"}, {"224,64", "c60"},
	{"96,80", "c60"}, {"224,80", "c60"},
	{"48,96", "c60"}, {"144,96", "c60"},
	{"80,128", "c60"}, {"96,128", "c60"}, {"112,128", "c60"}, {"144,128", "c60"}, {"160,128", "c60"}, {"176,128", "c60"},
	{"96,144", "c60"}, {"160,144", "c60"},
	{"96,160", "c60"}, {"160,160", "c60"},
	{"96,176", "c60"}, {"128,176", "c60"}, {"160,176", "c60"},
	{"32,192", "c60"}, {"48,192", "c60"}, {"64,192", "c60"}, {"192,192", "c60"}, {"208,192", "c60"}, {"224,192", "c60"}
};

#endif