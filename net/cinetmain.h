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

	// 连接 1：提供 IP 地址和端口
	int Dial(const char* szIP, int nPort);
	// todo 连接 2：提供主机名和服务名
	
	// 断开
	int HangOut(int nConnectId);

	// 监听 1:
	int Listen(const char* szIP, int nPort);
	// todo 监听 2：
	
	// 停止监听
	int StopListen(const char* szIP, int nPort);

	// 发送一段内容 1：
	int SendData(int nConnectId, const char* szBuff);
	// todo 发送 2：甚至还有 3

	// 取当前的 Event
	int GetEventNotify();

	// 跑
	int Run();

protected:
private:
	// 一组 EventList（自身保证线程安全）

	// 一组 ActionList（自己保证线程安全）

	// 一组 Listen Socket Fd List（单独一个线程处理）

	// 一个配合 Listent Socket Fd List 的 epoll fd 

	// 一组 Connect Socket Fd List（单独一个线程处理）

	// 一个配合 Connect Socket Fd List 的 epoll fd

};

#endif // __cinetmain_h__
