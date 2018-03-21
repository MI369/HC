﻿/**
	Auto generated by xproto.exe
@author
	Dany
*/


/*::STDAFX_H::*/
/*::ACE_MESSAGE_BLOCK_H::*/
#include "/*::PROTOCLASSNAME::*/.h"
#include "StringHlp.h"
#ifdef WIN32
#include <Windows.h>
#else
#include <stdio.h>
#include <string.h>
#endif

/*::NAME_SPACE_USING::*/


/*::PROTOCLASSNAME::*/::_TOPCODEHANDLER 
/*::PROTOCLASSNAME::*/::_s_OpHandlers[]=
{
&/*::PROTOCLASSNAME::*/::NullActionHandler,
/*::OPHANDLER_ENTRY::*/
};

//const char**	  /*::PROTOCLASSNAME::*/::_s_SendOpcodeNames = /*::SEND_OPCODE_ENUM_NAME::*/::s_szEnumNames;
//const char**	  /*::PROTOCLASSNAME::*/::_s_RecvOpcodeNames = /*::RECV_OPCODE_ENUM_NAME::*/::s_szEnumNames;


std::map<long,long>	/*::PROTOCLASSNAME::*/::_s_msg_index_map;

int /*::PROTOCLASSNAME::*/::init_static_map()
{
/*::MSG_INDEX_MAP_ENTRIES::*/
	return TRUE;
}

static int dummyi=/*::PROTOCLASSNAME::*/::init_static_map();


long /*::PROTOCLASSNAME::*/::get_index_of_msg(long msg)
{
	std::map<long,long>::iterator iter = _s_msg_index_map.find( msg);
	if(iter!=_s_msg_index_map.end())
	{
		return iter->second;
	}
	return 0;
}



/*::PROTOCLASSNAME::*/::/*::PROTOCLASSNAME::*/()
{
	_m_pendingPacket=NULL;
	_m_bEnableNetworksDebugOutput=false;
	_m_bPending = false;

	ResetInternalData();

}

void /*::PROTOCLASSNAME::*/::ResetInternalData()
{
	if(_m_pendingPacket)
	{
		delete _m_pendingPacket;
		_m_pendingPacket    = NULL;
	}

	_m_remainingPacketLen     = 0;
	_m_PacketHeaderSize = 0;
	while(!_m_PacketQueue.empty())
	{
		TXPROTO_RAWDATA_BLOCK *pPacket =_m_PacketQueue.front();
		delete pPacket;
		_m_PacketQueue.pop_front();
	}
}

/*::PROTOCLASSNAME::*/::~/*::PROTOCLASSNAME::*/()
{
	ResetInternalData();
}

INT  /*::PROTOCLASSNAME::*/::DispAction(XPROTO_PACKET_HEADER *phdr)
{
	INT res = 0;
	//dispactch it 
	//
	try
	{
		INT action = XPROTO_DISP_ACTION_CONTINUE;
		
		res = HookReceivedPacket((char*)phdr, (INT)phdr->len,&action);
		if(res >=0)
		{
			if(action==XPROTO_DISP_ACTION_CONTINUE)
			{
				INT msg_idx = /*::GET_INDEX_OF_MSG::*/(phdr->cmd);
				
				if(msg_idx >0)
				{
					//here should be a complete packet.
					//
					/*::PROTOCLASSNAME::*/::_TOPCODEHANDLER & opHandler = _s_OpHandlers[msg_idx];
					res =(this->*opHandler)((char*)phdr, (INT)phdr->len);
				}
			}
			else if(action==XPROTO_DISP_ACTION_QUEUE)
			{
				enqueue((char*)phdr, (INT)phdr->len);
			}
		}
	}
	catch(...)
	{
		printf("dispactch exception");
		res = XPROTO_DISPATCH_EXCEPTION;
	}
	return res;
}

INT /*::PROTOCLASSNAME::*/::CheckPacketHeader(XPROTO_PACKET_HEADER *phdr)
{
	//
	//overflow?
	//
	if(((int)phdr->len)<0 || (int)phdr->len > MaxPacketLength())
	{
		return XPROTO_PACKET_LENGTH_OVERFLOW;
	}
#ifndef NO_MESSAGE_ID_MAPPING_CHECK_/*::PROTOCLASSNAME::*/

	if(phdr->cmd<=0 || phdr->cmd > /*::ENUM_EVENT_MSG_MAX::*/ || phdr->cmd < /*::ENUM_EVENT_MSG_MIN::*/)
	{
		return XPROTO_XCMD_OUT_OF_RANGE;
	}
	INT msg_idx = /*::GET_INDEX_OF_MSG::*/(phdr->cmd);
	if(msg_idx<=0)
	{
		return XPROTO_XCMD_OUT_OF_RANGE;
	}
#endif	

	return 0;
}

INT /*::PROTOCLASSNAME::*/::HandleReceiveDataAndDispatch(char *buf,INT len)
{
	XPROTO_PACKET_HEADER *phdr = NULL;
	if(_m_pendingPacket==NULL)
	{
		try
		{
			_m_pendingPacket = new TXPROTO_RAWDATA_BLOCK(MaxPacketLength());
		}
		catch(...)
		{
			printf("no memory for _m_pendingPacket");
			return -1;
		}
	}

	int byteAvailable = len;
	const char *pCurrentBuf=buf;

	char *pPendingPacket = (char *)&(*_m_pendingPacket)[0];

	INT res =0;

	while(byteAvailable>0)
	{
		if(!_m_bPending)
		{
			//new packet
			//
			_m_FinishedPacketLen =0;

			
			if(byteAvailable<PACKET_HEADER_SIZE)
			{
				//header  not completed
				//
				memcpy(pPendingPacket+_m_FinishedPacketLen ,pCurrentBuf,byteAvailable);
				
				_m_FinishedPacketLen = byteAvailable;
				_m_bPending = true;

				return byteAvailable;
			}

			phdr = (XPROTO_PACKET_HEADER *)pCurrentBuf;

			if((res = CheckPacketHeader(phdr))!=0)
			{
				return res;
			}
			
			if((UINT)byteAvailable < phdr->len)
			{
				//header  not completed
				//
				memcpy(pPendingPacket+_m_FinishedPacketLen ,pCurrentBuf,byteAvailable);
				_m_FinishedPacketLen = byteAvailable;
				_m_bPending = true;
				return len;
			}

			//Use it with no copy immediately
			//
			pCurrentBuf += phdr->len;
			byteAvailable -= phdr->len;
		
			if((res = DispAction(phdr))<0)
			{
				return res;
			}

		}//if pending?
		else
		{
			//packet pending 
			//
			if(_m_FinishedPacketLen<PACKET_HEADER_SIZE)
			{
				int hdrLeft = (PACKET_HEADER_SIZE -_m_FinishedPacketLen);
				if(byteAvailable < hdrLeft)
				{
					//header still not completed .
					memcpy( pPendingPacket + _m_FinishedPacketLen,
						pCurrentBuf,
						byteAvailable);

					_m_FinishedPacketLen += byteAvailable;
					_m_bPending =true;
					return byteAvailable;
				}

				//head completed.
				//
				memcpy(pPendingPacket + _m_FinishedPacketLen,
					pCurrentBuf,hdrLeft);

				//update current position
				//
				pCurrentBuf +=hdrLeft;
				byteAvailable -=hdrLeft;

				_m_FinishedPacketLen = PACKET_HEADER_SIZE;
			}

			phdr =  (XPROTO_PACKET_HEADER *)pPendingPacket;

			if((res = CheckPacketHeader(phdr))!=0)
			{
				return res;
			}
			
			int remainLen = phdr->len - _m_FinishedPacketLen;
			if(byteAvailable < remainLen)
			{
				//not completed
				//copy and return
				//
				memcpy(pPendingPacket+ _m_FinishedPacketLen,  pCurrentBuf,byteAvailable);
				_m_FinishedPacketLen += byteAvailable;
				_m_bPending = true;
				return byteAvailable;
			}

		
			memcpy(pPendingPacket+ _m_FinishedPacketLen, pCurrentBuf,remainLen);

			pCurrentBuf += remainLen;
			byteAvailable -= remainLen;

			_m_bPending = false;//pakcet completed


			//here should be a complete packet.
			//
			
			//dispactch it 
			//
			if((res = DispAction(phdr))<0)
			{
				return res;
			}
		}
	}//while
	return len;
}


INT /*::PROTOCLASSNAME::*/::DispatchReceivedPacket()
{
	while(!_m_PacketQueue.empty())
	{
		TXPROTO_RAWDATA_BLOCK *pPacket = _m_PacketQueue.front();
		_m_PacketQueue.pop_front();

		XPROTO_PACKET_HEADER *phdr =(XPROTO_PACKET_HEADER *)(&(*pPacket)[0]);
		long msg_idx = /*::GET_INDEX_OF_MSG::*/(phdr->cmd);
		if(msg_idx<=0)
		{
			return XPROTO_XCMD_OUT_OF_RANGE;
		}

		/*::PROTOCLASSNAME::*/::_TOPCODEHANDLER & opHandler = _s_OpHandlers[msg_idx];

		//dispath by table;
		//

		INT res = (this->*opHandler)((const char*)phdr, phdr->len);
		
		//delete this pPacket;
		//
		delete pPacket;

		if(res<0)
		{
			return res;
		}
	}

	return 0;
}

INT /*::PROTOCLASSNAME::*/::HandleReceivedData(char *buf, INT len)
{
	int offset = 0;

	while(offset<len)
	{
		

		//check if pending data
		//
		if(_m_remainingPacketLen==0)
		{
			//Start with new Packet
			//Check 
			//
			if(_m_PacketHeaderSize<8)
			{
				int iHdrRemain = 8-_m_PacketHeaderSize;
				int nLeft = (len-offset);
				if(iHdrRemain<=nLeft)
				{
					
					offset+=_xmemcpy(&_m_PacketHeader[_m_PacketHeaderSize],buf+offset,iHdrRemain);
					_m_PacketHeaderSize = 8;
				}
				else
				{
					
					offset+=_xmemcpy(&_m_PacketHeader[_m_PacketHeaderSize],buf+offset,nLeft);
					_m_PacketHeaderSize +=nLeft;
					
				}
			}

			//
			//Check whether Header is received over.
			//
			if(_m_PacketHeaderSize!=8)
			{
				//Header is not ok, return, wait for more buf;
				//
				return offset;
			}

			//Got Packet LENGTH, CLEAR HEADER ;
			//
			memcpy(&_m_remainingPacketLen,&_m_PacketHeader,4);
			_m_PacketHeaderSize = 0;
			
			INT xcmd = -1;
			memcpy(&xcmd,&_m_PacketHeader[4],4);
			
			//return ERROR, if xcmd and length is bad
			//
			if(_m_remainingPacketLen<8 || xcmd<=0 || xcmd>=/*::ENUM_EVENT_MSG_MAX::*/ || xcmd < /*::ENUM_EVENT_MSG_MIN::*/)
			{
				return XPROTO_XCMD_OUT_OF_RANGE;
			}

			INT msg_idx = /*::GET_INDEX_OF_MSG::*/(xcmd);
			if(msg_idx<=0)
			{
				return XPROTO_XCMD_OUT_OF_RANGE;
			}

			_m_pendingPacket = new TXPROTO_RAWDATA_BLOCK(_m_remainingPacketLen);
			memcpy(&(*_m_pendingPacket)[0],&_m_PacketHeader[0],8);
			_m_remainingPacketLen-=8;
		}
		
		if(_m_pendingPacket==NULL)
		{
			return offset;
		}
		
		if(_m_remainingPacketLen>0)
		{
			if(_m_remainingPacketLen > len-offset)
			{
				INT tlen = len-offset;
				offset  +=_xmemcpy(& (*_m_pendingPacket)[_m_pendingPacket->size()-_m_remainingPacketLen],buf+offset,tlen);
				_m_remainingPacketLen -= tlen;
				
			}
			else
			{
				offset+=_xmemcpy(&(*_m_pendingPacket)[_m_pendingPacket->size()-_m_remainingPacketLen],buf+offset,_m_remainingPacketLen);
				_m_remainingPacketLen =  0;
			}
		}

		if(_m_remainingPacketLen==0 && _m_pendingPacket)
		{
	
			if(_m_bEnableNetworksDebugOutput)
			{
				INT xcmd = -1;
				memcpy(&xcmd,&((*_m_pendingPacket)[4]),4);

				OutputNetworkDetails(false,xcmd, &((*_m_pendingPacket)[0]), (INT)_m_pendingPacket->size());
			}

			BOOL bContinue = TRUE;
			int res = HookReceivedPacket((char *)&((*_m_pendingPacket)[0]), (INT)_m_pendingPacket->size(),&bContinue);
			if(bContinue && res >=0)
			{
				_m_PacketQueue.push_back(_m_pendingPacket);
			}

			_m_pendingPacket = NULL;
			if(res<0)
			{
				return res;
			}
		}

	}

	return offset;
	
}


void /*::PROTOCLASSNAME::*/::OutputNetworkDetails(bool bSend, INT xcmd, const UCHAR *buf, int len)
{
	char szHeader[255];
	if(bSend)

		sprintf(szHeader,"%8d SEND %04X %s ",this, len,  

		/*::SEND_OPCODE_ENUM_NAME::*/::GetName((/*::SEND_OPCODE_ENUM_NAME::*/::E)xcmd)
		);
	else
		sprintf(szHeader,"%8d RECV %04X %s ",this, len,  
		/*::RECV_OPCODE_ENUM_NAME::*/::GetName((/*::RECV_OPCODE_ENUM_NAME::*/::E)xcmd)
		);

	STRINGA szOuput = szHeader;

	int outlen =0x400;
	if(len < 0x400)
	{
		outlen = len;
	}

	char *szDetails=NULL;
	BytesToStringA(szDetails,buf,len);
	
	if(szDetails)
	{
		szOuput+=szDetails;
		delete []szDetails;
	}

	if(len >= 0x400)
	{
		szOuput+="...\n";
	}
	else
	{
		szOuput+="\n";
	}
#ifdef WIN32	
	OutputDebugStringA(szOuput.c_str());
#else
	printf("%s",szOuput.c_str());
#endif
}

//SAMPLE:
//
INT /*::PROTOCLASSNAME::*/::NullActionHandler(const char *__src,INT    __len)
{
	return 0;
}

//
//ORIGINALHANDLER_IMPLEMENTS
//
/*::ORIGINALHANDLER_IMPLEMENTS::*/


//
//SEND_METHODS_IMPLEMENTS
//
/*::SEND_METHODS_IMPLEMENTS::*/


