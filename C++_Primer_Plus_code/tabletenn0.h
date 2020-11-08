#pragma once
#ifndef TABLETENN0_H_  
#define TABLETENN0_H_  

#include <string> 

using std::string;

class TableTennisPlayer
{
private:
	string firstname;
	string lastname;
	bool hasTable;
public:
	TableTennisPlayer(const string & fn = "none", const string & In = "none", bool ht = false);
	void Name() const;
	bool HasTable() const { return hasTable; };
	void ResetTable(bool v) { hasTable = v; };
};

#endif
