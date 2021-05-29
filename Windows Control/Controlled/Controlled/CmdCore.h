#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDCORE_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDCORE_H_
/*
* 此类是网络命令的抽象类
*/
#include "CmdStructs.h"
#include <utility>
#include <memory>
#include <string>
//最大包长度
constexpr std::size_t Max_Net_Size = 512;

class CmdCore{
public:
	typedef unsigned int CmdType;


public:
	CmdCore();
	CmdCore(const std::string& type_str ,const std::string& data_str);
	~CmdCore();

	CmdCore& operator=(const CmdCore& rst);
	bool operator==(const CmdCore& rst) const;

	lfu::CmdType Type() const {
		return _type;
	}
	const std::string& Data() const {
		return _data;
	}

private:
	lfu::CmdType _type;
	std::string _data;
};

#endif
