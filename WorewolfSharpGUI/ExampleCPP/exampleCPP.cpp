#include<iostream>

extern "C" __declspec(dllexport) int __stdcall Test(int a, int b) {
	return a + b;
}