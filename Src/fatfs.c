/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "fatfs.h"

uint8_t retUSER;    /* Return value for USER */
char USERPath[4];   /* USER logical drive path */
FATFS USERFatFS;    /* File system object for USER logical drive */
FIL USERFile;       /* File object for USER */

/* USER CODE BEGIN Variables */
#include "board.h"
/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the USER driver ###########################*/
  retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);

  /* USER CODE BEGIN Init */
	/* additional user code for init */
  /* USER CODE END Init */
}


/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
	return 0;
  /* USER CODE END get_fattime */  
}

/* USER CODE BEGIN Application */
bool FATFS_CreateFileSystem(void)
{
	uint8_t workBuffer[_MAX_SS];

	// FIXME: f_mkfs may fail to compute proper FAT table size.
	if(f_mkfs(USERPath, FM_FAT, 4096, workBuffer, sizeof(workBuffer))== FR_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#if UNIT_TEST
void FATFS_UnitTest(void)
{
	uint8_t wbuff[] = "Lorem ipsum dolor sit amet, consectetur adipisciing elit";
	uint8_t rbuff[100];
	uint32_t no_bytes;

	// mount the file system
	if(f_mount(&USERFatFS, (TCHAR const*)USERPath, 0) == FR_OK)
	{
		DbgPrintf("\r\n...File system mount success");
		// write test
		if(f_open(&USERFile, "TEST.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
		{
			// write data
			f_write(&USERFile, wbuff, sizeof(wbuff), (void*)&no_bytes);
			DbgPrintf("\r\n...A new text file created");
			// close file
			f_close(&USERFile);

			// read test
			if(f_open(&USERFile, "TEST.TXT", FA_READ) == FR_OK)
			{
				f_read(&USERFile, rbuff, sizeof(rbuff), (void*)&no_bytes);
				DbgPrintf("\r\n...File opend successfully:\r\n%s", rbuff);
				// close file
				f_close(&USERFile);
			}
			else
			{
				DbgPrintf("\r\n<ERR> failed to open the file");
			}
		}
		else
		{
			DbgPrintf("\r\n<ERR> failed to create a file");
		}
	}
	else
	{
		DbgPrintf("\r\n<ERR> failed to mount the file system");
	}
}
#endif

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
