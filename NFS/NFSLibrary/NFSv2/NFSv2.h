/*
 * NekoDrive
 * 2010 by Mirko Gatto
 * mirko.gatto@gmail.com
 *
 * NFS V2 Wrapper
 *
 * Users may use, copy or modify this library 
 * according GNU General Public License v3 (http://www.gnu.org/licenses/gpl.html)
 */

#ifndef __IncNFSV2h
#define __IncNFSV2h

#pragma pack(8) //alignemnt 8 bytes

#ifdef NFSV2_EXPORTS
#define NFSV2_API __declspec(dllexport)
#else
#define NFSV2_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>
#include <string>
#include <rpc/rpc.h>
#include "NFSv2Protocol.h"

#define MAX_FILE_NAME 255
#define NFS_SUCCESS 0
#define NFS_ERROR -1


struct NFSData
{
	unsigned long DateTime;
	unsigned int Type;
	unsigned int Size;
	unsigned int Blocks;
	unsigned int BlockSize;
	char Handle[FHSIZE];
};


class NFSV2_API CNFSv2
{
private:
	//server address
	unsigned int uiServer;
	//server name
	std::string strServer;
	//nfs mount client v2
	CLIENT* clntMountV2;
	//nfs client v2
	CLIENT* clntV2;
	//main socket
	SOCKET sSocket;
	//server address structure
	struct sockaddr_in sSrvAddr;
	//clients timeout
	struct timeval timeOut;
	//current connected device
	std::string strCurrentDevice;
	//last error string
	std::string strLastError;
	//handle of the current directory
	nfshandle nfsCurrentDirectory;
	//functions
	void InitStructure(NFSData* pNfsData);
public:
	CNFSv2();
	~CNFSv2();
	//Connect to a server
	int Connect(unsigned int ServerAddress);
	//Disconnect from a server
	int Disconnect();
	//Get the exported devices
	char** GetExportedDevices(int* pnSize);
	//Get the items of the current directory
	char** GetItemsList(int* pnSize);
	//Release the strings buffer
	void ReleaseBuffer(char** pBuffer);
	//Release the structure
	void ReleaseBuffer(char* pBuffer);
	//Mount the remote device
	int MountDevice(char* pDevice);
	//Unmount the remote device
	int UnMountDevice();
	//Get the item attributes
	void* GetItemAttributes(char* pItem);
	//Change the current directory
	void ChangeCurrentDirectory(char* pHandle);
	//Create a directory
	int CreateDirectory(char* pName);
	//Delete a directory
	int DeleteDirectory(char* pName);
	//Delete a file
	int DeleteFile(char* pName);
	//Create a new file
	int CreateFile(char* pName);
	//Read a file
	int Read(char* pHandle, u_int Offset, u_int Count, char* pBuffer, u_long* pSize);
	//Write a file
	int Write(char* pHandle, u_int Offset, u_int Count, char* pBuffer, u_long* pSize);
	//Rename a file or directory
	int Rename(char* pOldName, char* pNewName);
};

#endif