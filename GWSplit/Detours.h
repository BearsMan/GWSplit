#pragma once

typedef unsigned char BYTE;

void *DetourFunc(BYTE *src, const BYTE *dst, const int len);
void RetourFunc(BYTE *src, BYTE *restore, const int len);