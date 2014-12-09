
#include "comm.h"
MYCOMM::MYCOMM()
{
	buffer = new char[bufferlen];
	lpInBuffer = new char[bufferlen];
}
bool MYCOMM::open(char * comport)
{
	hCom =CreateFileA(comport,  //COM口  
		GENERIC_READ|GENERIC_WRITE, //允许读和写  
		0,  //独占方式  
		NULL,  
		OPEN_EXISTING,  //打开而不是创建  
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //重叠方式  
		NULL);  
	if(hCom ==INVALID_HANDLE_VALUE)  
	{  
		if(MessageBoxA(nullptr,"open comm failed","message",MB_OKCANCEL)) exit(-1);
		return false;
	} 
	return true;
}
bool MYCOMM::set()
{
	bool isok;
	isok = SetupComm(hCom,1024,1024); //输入缓冲区和输出缓冲区的大小都是1024   
	if(!isok) return false;
	COMMTIMEOUTS TimeOuts;  	//设定读超时  
	TimeOuts.ReadIntervalTimeout=1000;  
	TimeOuts.ReadTotalTimeoutMultiplier=500;  
	TimeOuts.ReadTotalTimeoutConstant=5000;  	//设定写超时  
	TimeOuts.WriteTotalTimeoutMultiplier=500;  
	TimeOuts.WriteTotalTimeoutConstant=2000;  
	SetCommTimeouts(hCom,&TimeOuts); //设置超时  	 
	DCB dcb;  
	isok = GetCommState(hCom,&dcb);  
	if(!isok) return false;
	dcb.BaudRate=9600; //波特率为9600  
	dcb.ByteSize=8; //每个字节有8位  
	dcb.Parity=NOPARITY; //无奇偶校验位  
	dcb.StopBits=TWOSTOPBITS; //两个停止位  
	isok = SetCommState(hCom,&dcb);  
	if(!isok) return false;
	isok = PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);  //在读写串口之前，还要用PurgeComm()函数清空缓冲区，该函数原型：
	if(!isok) return false;
	return true;
}

DWORD MYCOMM::read()
{
	//char lpInBuffer[1024]; 
	memset(lpInBuffer,0,bufferlen*sizeof(char));
	DWORD dwBytesRead=1024;  
	COMSTAT ComStat;  
	DWORD dwErrorFlags;  
	OVERLAPPED m_osRead;  
	memset(&m_osRead,0,sizeof(OVERLAPPED));  
	m_osRead.hEvent=CreateEventA(NULL,TRUE,FALSE,NULL);  	 
	ClearCommError(hCom,&dwErrorFlags,&ComStat);  
	dwBytesRead=min(dwBytesRead,(DWORD)ComStat.cbInQue);  
	if(!dwBytesRead)   return 0 ;  
	BOOL bReadStatus;  
	DWORD debread;
	bReadStatus=ReadFile(hCom,lpInBuffer, dwBytesRead,&debread,&m_osRead); 
	if(!bReadStatus) //如果ReadFile函数返回FALSE  
	{  
		if(GetLastError()==ERROR_IO_PENDING)  
			//GetLastError()函数返回ERROR_IO_PENDING,表明串口正在进行读操作      
		{  
			WaitForSingleObject(m_osRead.hEvent,1000);  	        //使用WaitForSingleObject函数等待，直到读操作完成或延时已达到2秒钟  
			//当串口读操作进行完毕后，m_osRead的hEvent事件会变为有信号  
			PurgeComm(hCom, PURGE_TXABORT|  PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);  
			return dwBytesRead;  
		}  
		return 0;  
	}  
	PurgeComm(hCom, PURGE_TXABORT|     PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR); 
	return dwBytesRead;
}

DWORD MYCOMM::write(string &send)
{
	//PurgeComm(hCom, PURGE_TXABORT|     PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR); 
	BOOL bWriteStat;  
	DWORD dwBytesWritten=1024;//1024; 
	DWORD dwBytesWritten2=1;
	DWORD dwErrorFlags;  
	COMSTAT ComStat;  
	OVERLAPPED m_osWrite; 
	dwBytesWritten = send.length()+1;
	memset(&m_osWrite,0,sizeof(OVERLAPPED));  
	m_osWrite.hEvent=CreateEventA(NULL,TRUE,FALSE,NULL); 
	bWriteStat = ClearCommError(hCom,&dwErrorFlags,&ComStat);  
	//memcpy(buffer,&send[0],send.length()-1);
	for(int i = 0;i<send.length();++i)
	{
		buffer[i] = send[i];
	}
	buffer[send.length()] = '\0';
	Sleep(300);
	bWriteStat=WriteFile(hCom,buffer,dwBytesWritten, &dwBytesWritten,&m_osWrite);  
	if(!bWriteStat)  
	{  
		if(GetLastError()==ERROR_IO_PENDING)  
		{  
			WaitForSingleObject(m_osWrite.hEvent,1000);  
			return dwBytesWritten;  
		}  
		return 0;  
	} 
	return 1;

}

void MYCOMM::showread(string &reader)
{
	read();
	Sleep(100);
	reader = (char *)lpInBuffer;
}
MYCOMM::~MYCOMM()
{
	if(buffer!=nullptr) delete buffer;	
	if(lpInBuffer!=nullptr) delete lpInBuffer;
	CloseHandle(hCom);
}