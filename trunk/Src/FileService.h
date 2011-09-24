////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : FileService.h
// Purpose     : Provide some frequently use function
//               This file is copy and modify from Kinksoft safeguard Open source
// Version     : 2011-06-07 (11:39) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file FileService.h */
#pragma once

#include <CmmWinHdr.h>

/**
 * Get the version information of a file
 * @param szPath The path of the file
 * @param lgVersion The version information
 * @return TRUE if successfully get the information, FALSE otherwise
 */
BOOL  GetFileVersion( LPCTSTR szPath, LARGE_INTEGER &lgVersion);
/**
 * Check whether a file exists
 * @param pszFile The file that is being checked.
 * @return TRUE if exists, FALSE otherwise
 */
BOOL  IsFileExist(LPCTSTR pszFile);
/**
 * Check whether a directory exists
 * @param pszDir The directory that is being checked.
 * @return TRUE if exists, FALSE otherwise
 */
BOOL  IsDirExist(LPCTSTR pszDir);
/**
 * Move file/directory to another location
 * @param lpszFileFrom The source
 * @param lpszFileto The target
 * @return TRUE if successfully moved, FALSE otherwise
 */
BOOL  MyMoveFile(LPCTSTR lpszFileFrom, LPCTSTR lpszFileto);
/**
 * Check whether a file is being used
 * @param szFilename The file that is being checked.
 * @return TRUE if being used, FALSE otherwise
 */
BOOL  IsFileUsing(LPCTSTR szFilename);
/**
 * Get the content of the file
 * @param lpszFilename The file
 * @param pCont The content returned
 * @return TRUE if successful, FALSE otherwise
 */
BOOL  GetFileContents( LPCTSTR lpszFilename, BYTE* pCont);
/**
 * Put content into a file
 * @param lpszFilename The file
 * @param pBuffer The content that will be writed into the file
 * @param nLen The lenght of the buffer
 * @return TRUE if successful, FALSE otherwise
 */
BOOL  PutFileContents(LPCTSTR lpszFilename, BYTE *pBuffer, INT nLen);
/**
 * Get the size of a file
 * @param lpszFilename The file
 * @return The size of the file
 */
INT64 MyGetFileSize(LPCTSTR lpszFilename);
/**
 * Get the size of the folder
 * @param szFolder The folder
 * @return The size of the folder
 */
INT64 GetFolderSize(LPCTSTR szFolder);

/**
 * Create nested directory
 * @param lpszDir The path
 * @return TRUE if directory is created, FALSE otherwise
 */
BOOL CreateDirectoryNested( LPCTSTR  lpszDir );
/**
 * Create directory for a file
 * @param lpFileName The fully path of the file
 * @return TRUE if directory is created, FALSE otherwise
 */
BOOL CreateDirs (LPCTSTR lpFileName);