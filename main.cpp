#include <iostream>
#include <stdio.h>
#include <ios>
#include <filesystem>
#include <windows.h>
#include <psapi.h>
#include <string>
#include <ctime>
#include <cwctype>
#include <algorithm>
#include <fstream>

const char* GetExecutingFilename( ) {
        char execFileName[ MAX_PATH ];
    if ( !GetModuleFileNameExA( GetCurrentProcess( ), // hProcess
        NULL, // hModule (specifying NULL) here returns the executable path of hProcess
        execFileName, // lpFilename
        MAX_PATH // nSize
    ) ) {
        printf( "Unable to get this application's executing path.\n" );
        return nullptr;
    }
        return execFileName;
}

#define MIN_STRLEN 8
int main( int argc, char* argv[ ] ) {
        srand( time(NULL) );

        if ( argc < 2 ) {
                //printf( "Invalid number of arguments provided.\n" );
                printf( "Dummy application executing.\n" );

                unsigned char count = 0;
                while (true) {
                        Sleep( 250 );
                        count++;
                        if (count >= 20) {
                                printf( "\n" );
                                count = 0;
                                continue;
                        }
                        else {
                                printf( "%c", ( rand( ) % 93 ) + 33 );
                        }
                }
                return 0;
        }

        FILE* fHandle = fopen( argv[ 1 ], "r" );
        if ( !fHandle ) {
                printf( "Unable to open file '%s'.\n", argv[ 1 ] );
                return 0;
        }

        std::vector<std::wstring> wstringList;
        std::wstring curWString(L"");
        while ( !feof( fHandle ) ) {
                const wchar_t wcBuf = fgetwc( fHandle );
                if ( !std::iswprint( wcBuf ) ) {
                        if ( curWString.length( ) >= MIN_STRLEN ) {
                                wstringList.push_back( curWString );
                        }
                        curWString = L"";
                        continue;
                }
                else {
                        curWString += wcBuf;
                }
        }
        fclose( fHandle );
        printf( "Found %d strings in '%s'.\n", wstringList.size( ), argv[ 1 ] );

        std::string output_filestr = ( argc == 3 ) ? argv[ 2 ] : ( "output_" + std::to_string( rand( ) % 13337 ) + ".exe" );

        if ( !(fHandle = fopen( output_filestr.c_str( ), "ab" )) ) {
                printf( "Unable to open file '%s'.\n", output_filestr.c_str( ) );
                return 0;
        }

        // Write our program to that file.
        const char* execFilename = GetExecutingFilename( );
        if ( execFilename == nullptr ) {
                return 0;
        }
        CopyFile( argv[ 0 ], output_filestr.c_str( ), FALSE );

        // Write all of the strings to that file.
        for ( std::wstring iStr : wstringList ) {
                fwprintf( fHandle, L"\n'%s' @ %d\n", iStr.c_str( ), iStr.length( ) );
        }
        fprintf( fHandle, "\x01\x03\x03\x07" ); // So that we/antiviruses are able to identify these files (I doubt that there are many legitimate executables ending in 0x1, 0x3, 0x3, 0x7).

        fclose( fHandle );
        printf( "Finished writing to '%s'.\n", output_filestr.c_str( ));

        return 1;
}
