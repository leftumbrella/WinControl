#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDSTRUCTS_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDSTRUCTS_H_


namespace lfu {
	enum class CmdType {
		NONE = 0,			//������
		SHUTDOWN,			//�ػ�
		CANCEL_SHUTDOWN,	//ȡ���ػ�
		VOLUME_SET,			//��������
		SEND_NOW_VOLUME,	//��ȡ��ǰ���������

	};
}

#endif