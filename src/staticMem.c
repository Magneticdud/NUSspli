/***************************************************************************
 * This file is part of NUSspli.                                           *
 * Copyright (c) 2022 V10lator <v10lator@myway.de>                         *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.             *
 ***************************************************************************/

#include <wut-fixups.h>

#include <coreinit/memdefaultheap.h>
#include <coreinit/memory.h>

#include <renderer.h>
#include <staticMem.h>

void *pointers[3];

bool initStaticMem()
{
	pointers[0] = MEMAllocFromDefaultHeap(TO_FRAME_BUFFER_SIZE);
	if(pointers[0] != NULL)
	{
		pointers[1] = MEMAllocFromDefaultHeap(TO_FRAME_BUFFER_SIZE);
		if(pointers[1] != NULL)
		{
			pointers[2] = MEMAllocFromDefaultHeap(0x27F);
			if(pointers[2] != NULL)
			{
				return true;
			}

			MEMFreeToDefaultHeap(pointers[1]);
		}
		MEMFreeToDefaultHeap(pointers[0]);
	}
	return false;
}

void shutdownStaticMem()
{
	for(int i = 0; i < 3; i++)
		MEMFreeToDefaultHeap(pointers[i]);
}

void *getStaticScreenBuffer()
{
	return pointers[0];
}

void *getStaticLineBuffer()
{
	return pointers[1];
}

void *getStaticInstallerPathArea()
{
	return pointers[3];
}