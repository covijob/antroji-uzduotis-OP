#pragma once
#pragma once

#ifdef STUDENTU_DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

extern "C" {
    DLL_API double dll_vidurkis(const int* arr, int n);
}
