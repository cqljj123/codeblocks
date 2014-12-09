
#include "comm.h"
MYCOMM::MYCOMM()
{
	buffer = new char[bufferlen];
	lpInBuffer = new char[bufferlen];
}
bool MYCOMM::open(char * comport)
{
	hCom =CreateFileA(comport,  //COM��  
		GENERIC_READ|GENERIC_WRITE, //�������д  
		0,  //��ռ��ʽ  
		NULL,  
		OPEN_EXISTING,  //�򿪶����Ǵ���  
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�ص���ʽ  
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
	isok = SetupComm(hCom,1024,1024); //���뻺����������������Ĵ�С����1024   
	if(!isok) return false;
	COMMTIMEOUTS TimeOuts;  	//�趨����ʱ  
	TimeOuts.ReadIntervalTimeout=1000;  
	TimeOuts.ReadTotalTimeoutMultiplier=500;  
	TimeOuts.ReadTotalTimeoutConstant=5000;  	//�趨д��ʱ  
	TimeOuts.WriteTotalTimeoutMultiplier=500;  
	TimeOuts.WriteTotalTimeoutConstant=2000;  
	SetCommTimeouts(hCom,&TimeOuts); //���ó�ʱ  	 
	DCB dcb;  
	isok = GetCommState(hCom,&dcb);  
	if(!isok) return false;
	dcb.BaudRate=9600; //������Ϊ9600  
	dcb.ByteSize=8; //ÿ���ֽ���8λ  
	dcb.Parity=NOPARITY; //����żУ��λ  
	dcb.StopBits=TWOSTOPBITS; //����ֹͣλ  
	isok = SetCommState(hCom,&dcb);  
	if(!isok) return false;
	isok = PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);  //�ڶ�д����֮ǰ����Ҫ��PurgeComm()������ջ��������ú���ԭ�ͣ�
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
	if(!bReadStatus) //���ReadFile��������FALSE  
	{  
		if(GetLastError()==ERROR_IO_PENDING)  
			//GetLastError()��������ERROR_IO_PENDING,�����������ڽ��ж�����      
		{  
			WaitForSingleObject(m_osRead.hEvent,1000);  	        //ʹ��WaitForSingleObject�����ȴ���ֱ����������ɻ���ʱ�Ѵﵽ2����  
			//�����ڶ�����������Ϻ�m_osRead��hEvent�¼����Ϊ���ź�  
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