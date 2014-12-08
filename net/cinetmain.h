#ifndef __CINETMAIN_H__
#define __CINETMAIN_H__

class CiNetMain
{
public:
	CiNetMain();
	~CiNetMain();

	int Init();
	int Uninit();
	int Release();

	// ���� 1���ṩ IP ��ַ�Ͷ˿�
	int Dial(const char* szIP, int nPort);
	// todo ���� 2���ṩ�������ͷ�����
	
	// �Ͽ�
	int HangOut(int nConnectId);

	// ���� 1:
	int Listen(const char* szIP, int nPort);
	// todo ���� 2��
	
	// ֹͣ����
	int StopListen(const char* szIP, int nPort);

	// ����һ������ 1��
	int SendData(int nConnectId, const char* szBuff);
	// todo ���� 2���������� 3

	// ȡ��ǰ�� Event
	int GetEventNotify();

	// ��
	int Run();

protected:
private:
	// һ�� EventList������֤�̰߳�ȫ��

	// һ�� ActionList���Լ���֤�̰߳�ȫ��

	// һ�� Listen Socket Fd List������һ���̴߳���

	// һ����� Listent Socket Fd List �� epoll fd 

	// һ�� Connect Socket Fd List������һ���̴߳���

	// һ����� Connect Socket Fd List �� epoll fd

};

#endif // __cinetmain_h__
