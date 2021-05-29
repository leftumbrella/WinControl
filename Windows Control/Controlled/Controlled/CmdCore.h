#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDCORE_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDCORE_H_
/*
* ��������������ĳ�����
*/
#include "CmdStructs.h"
#include <utility>
#include <memory>
#include <string>
//��������
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
