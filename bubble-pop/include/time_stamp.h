/* 
Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _VX_EXT_TIME_STAMP_H_
#define _VX_EXT_TIME_STAMP_H_

#include <string.h>
#include <sys/time.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define TIMESTAMP_MAX 32
#define TIMESTAMP_POS_MAX_LEN 32

struct timeStamp {
	long timeS;
	long timeNS;
	char postion[TIMESTAMP_POS_MAX_LEN];
};

int g_timeStampIdx = 0;
struct timeStamp g_timestamps[TIMESTAMP_MAX];


void inline AddTimeStamp(char *pos)
{
	timespec time;
	if (g_timeStampIdx >= TIMESTAMP_MAX) {
		return;
	}

	clock_gettime(CLOCK_MONOTONIC, &time);
	g_timestamps[g_timeStampIdx].timeS = time.tv_sec;
	g_timestamps[g_timeStampIdx].timeNS = time.tv_nsec;
	strcpy(g_timestamps[g_timeStampIdx].postion, pos);
	g_timeStampIdx++;
}

void PrintTimeStamp()
{
	printf("=======================================\r\n");
	printf("%-32s\t", g_timestamps[0].postion);
	printf("%3ld s: %3ld ms\r\n", g_timestamps[0].timeS, g_timestamps[0].timeNS / 1000000);
	
	for(int i = 1; i < g_timeStampIdx; ++i) {
		printf("%-32s\t", g_timestamps[i].postion);
		printf("%3ld s: %3ld ms\t", g_timestamps[i].timeS, g_timestamps[i].timeNS / 1000000);
		printf("TimeUsage: %3ld ms\r\n", (g_timestamps[i].timeS - g_timestamps[i - 1].timeS) * 1000 + (g_timestamps[i].timeNS - g_timestamps[i - 1].timeNS) / 1000000);
	}
	printf("=======================================\r\n");
	g_timeStampIdx = 0;
}

#ifdef  __cplusplus
}
#endif

#endif

