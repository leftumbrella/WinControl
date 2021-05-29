#include "CmdCore.h"

CmdCore::CmdCore():_type(lfu::CmdType::NONE){

}

CmdCore::CmdCore(const std::string& type_str, const std::string& data_str) : _type(lfu::CmdType::NONE){
	if (type_str == "SHUTDOWN") {
		_type = lfu::CmdType::SHUTDOWN;
	}else if (type_str == "CANCEL_SHUTDOWN") {
		_type = lfu::CmdType::CANCEL_SHUTDOWN;
	}else if (type_str == "VOLUME_SET") {
		_type = lfu::CmdType::VOLUME_SET;
	}else if (type_str == "SEND_NOW_VOLUME") {
		_type = lfu::CmdType::SEND_NOW_VOLUME;
	}

	_data = data_str;
}

CmdCore::~CmdCore(){
}

CmdCore& CmdCore::operator=(const CmdCore& rst){
	_type = rst._type;
	_data = rst._data;
	return *this;
}

bool CmdCore::operator==(const CmdCore& rst) const{
	return _type == rst._type && _data == rst._data;
}
