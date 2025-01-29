#pragma once

//
// Memory Tools Internal by foxcheatsid@gmail.com
// Created on Tue Apr 4 13:03:13 2023
//

/*
* Type
*/
enum Type {
    TYPE_DWORD,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_QWORD,
};

/*
* Maps, Semua hasil pencarian ada di sini 
*/
struct Maps_t {
    uintptr_t start, end;
	Type type;
    struct Maps_t *next;
};

#define SIZE sizeof(struct Maps_t)

/*
* List Memori Region 
*/
enum RegionType {
    ALL,
    JAVA_HEAP,
    C_HEAP,
    C_ALLOC,
    C_DATA,
    C_BSS,
    PPSSPP,
    ANONYMOUS,
    JAVA,
    STACK,
    ASHMEM,
    VIDEO,
    OTHER,
    BAD,
    CODE_APP,
    CODE_SYS
};

namespace kFox 
{
    /*
    * Mendapatkan PackageName
    */
	const char *GetPackageName();
	
    /*
    * Mendapatkan semua hasil pencarian memori
    */
	extern Maps_t* GetResult();
	
    /*
    * Menghapus semua hasil pencarian memori
    */
	extern void ClearResult();
	
    /*
    * Set maximal hasil pencarian
    */
	extern void SetMaxResult(int max_result);
	
    /*
    * Set Region
    */
	extern int SetSearchRange(RegionType type);
	
    /*
    * Mencari value berdasarkan Region dan Type
    */
    extern void MemorySearch(char* value, Type type);
	
    /*
    * Mencari value offset berdasarkan Region dan Type
    */
	extern void MemoryOffset(char *value, long int offset, Type type);
	
    /*
    * Write value berdasarkan offset
    */
	extern void MemoryWrite(char *value, long int offset, Type type);
	
    /*
    * Write value
    */
	extern void WriteValues(uintptr_t address, void *value, ssize_t size);
	
    /*
    * Read value
    */
	extern long ReadValues(uintptr_t address, void *buffer, ssize_t size);
}
