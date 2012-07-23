// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acZLibEx.pas' rev: 6.00

#ifndef acZLibExHPP
#define acZLibExHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Aczlibex
{
//-- type declarations -------------------------------------------------------
typedef void * __fastcall (*TZAlloc)(void * opaque, int items, int size);

typedef void __fastcall (*TZFree)(void * opaque, void * block);

#pragma option push -b-
enum TZCompressionLevel { zcNone, zcFastest, zcDefault, zcMax, zcLevel1, zcLevel2, zcLevel3, zcLevel4, zcLevel5, zcLevel6, zcLevel7, zcLevel8, zcLevel9 };
#pragma option pop

#pragma option push -b-
enum TZStrategy { zsDefault, zsFiltered, zsHuffman, zsRLE, zsFixed };
#pragma option pop

#pragma option push -b-
enum TZError { zeError, zeStreamError, zeDataError, zeMemoryError, zeBufferError, zeVersionError };
#pragma option pop

#pragma pack(push, 1)
struct TZStreamRec
{
	char *next_in;
	int avail_in;
	int total_in;
	char *next_out;
	int avail_out;
	int total_out;
	char *msg;
	void *state;
	TZAlloc zalloc;
	TZFree zfree;
	void *opaque;
	int data_type;
	int adler;
	int reserved;
} ;
#pragma pack(pop)

class DELPHICLASS TCustomZStream;
class PASCALIMPLEMENTATION TCustomZStream : public Classes::TStream 
{
	typedef Classes::TStream inherited;
	
private:
	Classes::TStream* FStream;
	__int64 FStreamPos;
	Classes::TNotifyEvent FOnProgress;
	#pragma pack(push, 1)
	TZStreamRec FZStream;
	#pragma pack(pop)
	
	char FBuffer[65536];
	
protected:
	__fastcall TCustomZStream(Classes::TStream* stream);
	DYNAMIC void __fastcall DoProgress(void);
	__property Classes::TNotifyEvent OnProgress = {read=FOnProgress, write=FOnProgress};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomZStream(void) { }
	#pragma option pop
	
};


class DELPHICLASS TZCompressionStream;
class PASCALIMPLEMENTATION TZCompressionStream : public TCustomZStream 
{
	typedef TCustomZStream inherited;
	
private:
	float __fastcall GetCompressionRate(void);
	
public:
	__fastcall TZCompressionStream(Classes::TStream* dest, TZCompressionLevel compressionLevel)/* overload */;
	__fastcall TZCompressionStream(Classes::TStream* dest, TZCompressionLevel compressionLevel, int windowBits, int memLevel, TZStrategy strategy)/* overload */;
	__fastcall virtual ~TZCompressionStream(void);
	virtual int __fastcall Read(void *buffer, int count);
	virtual int __fastcall Write(const void *buffer, int count);
	virtual int __fastcall Seek(int offset, Word origin)/* overload */;
	__property float CompressionRate = {read=GetCompressionRate};
	__property OnProgress ;
	
/* Hoisted overloads: */
	
public:
	inline __int64 __fastcall  Seek(const __int64 Offset, Classes::TSeekOrigin Origin){ return TStream::Seek(Offset, Origin); }
	
};


class DELPHICLASS TZDecompressionStream;
class PASCALIMPLEMENTATION TZDecompressionStream : public TCustomZStream 
{
	typedef TCustomZStream inherited;
	
public:
	__fastcall TZDecompressionStream(Classes::TStream* source)/* overload */;
	__fastcall TZDecompressionStream(Classes::TStream* source, int windowBits)/* overload */;
	__fastcall virtual ~TZDecompressionStream(void);
	virtual int __fastcall Read(void *buffer, int count);
	virtual int __fastcall Write(const void *buffer, int count);
	virtual int __fastcall Seek(int offset, Word origin)/* overload */;
	__property OnProgress ;
	
/* Hoisted overloads: */
	
public:
	inline __int64 __fastcall  Seek(const __int64 Offset, Classes::TSeekOrigin Origin){ return TStream::Seek(Offset, Origin); }
	
};


typedef TMetaClass*EZLibErrorClass;

class DELPHICLASS EZLibError;
class PASCALIMPLEMENTATION EZLibError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
private:
	int FErrorCode;
	
public:
	__fastcall EZLibError(int code, const AnsiString dummy)/* overload */;
	__fastcall EZLibError(TZError error, const AnsiString dummy)/* overload */;
	__property int ErrorCode = {read=FErrorCode, write=FErrorCode, nodefault};
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EZLibError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EZLibError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EZLibError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EZLibError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EZLibError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EZLibError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EZLibError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EZLibError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EZCompressionError;
class PASCALIMPLEMENTATION EZCompressionError : public EZLibError 
{
	typedef EZLibError inherited;
	
public:
	#pragma option push -w-inl
	/* EZLibError.Create */ inline __fastcall EZCompressionError(int code, const AnsiString dummy)/* overload */ : EZLibError(code, dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EZCompressionError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EZLibError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EZCompressionError(int Ident)/* overload */ : EZLibError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EZCompressionError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EZLibError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EZCompressionError(const AnsiString Msg, int AHelpContext) : EZLibError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EZCompressionError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EZLibError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EZCompressionError(int Ident, int AHelpContext)/* overload */ : EZLibError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EZCompressionError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EZLibError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EZCompressionError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EZDecompressionError;
class PASCALIMPLEMENTATION EZDecompressionError : public EZLibError 
{
	typedef EZLibError inherited;
	
public:
	#pragma option push -w-inl
	/* EZLibError.Create */ inline __fastcall EZDecompressionError(int code, const AnsiString dummy)/* overload */ : EZLibError(code, dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EZDecompressionError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EZLibError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EZDecompressionError(int Ident)/* overload */ : EZLibError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EZDecompressionError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EZLibError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EZDecompressionError(const AnsiString Msg, int AHelpContext) : EZLibError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EZDecompressionError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EZLibError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EZDecompressionError(int Ident, int AHelpContext)/* overload */ : EZLibError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EZDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EZLibError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EZDecompressionError(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define ZLIB_VERSION "1.2.3"
static const Word ZLIB_VERNUM = 0x1230;
static const Shortint Z_DEFLATED = 0x8;
static const Shortint Z_NO_FLUSH = 0x0;
static const Shortint Z_PARTIAL_FLUSH = 0x1;
static const Shortint Z_SYNC_FLUSH = 0x2;
static const Shortint Z_FULL_FLUSH = 0x3;
static const Shortint Z_FINISH = 0x4;
static const Shortint Z_BLOCK = 0x5;
static const Shortint Z_OK = 0x0;
static const Shortint Z_STREAM_END = 0x1;
static const Shortint Z_NEED_DICT = 0x2;
static const Shortint Z_ERRNO = 0xffffffff;
static const Shortint Z_STREAM_ERROR = 0xfffffffe;
static const Shortint Z_DATA_ERROR = 0xfffffffd;
static const Shortint Z_MEM_ERROR = 0xfffffffc;
static const Shortint Z_BUF_ERROR = 0xfffffffb;
static const Shortint Z_VERSION_ERROR = 0xfffffffa;
extern PACKAGE int __fastcall InflateInit(TZStreamRec &stream);
extern PACKAGE void __fastcall ZCompress(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, TZCompressionLevel level = (TZCompressionLevel)(0x2));
extern PACKAGE void __fastcall ZCompress2(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, TZCompressionLevel level, int windowBits, int memLevel, TZStrategy strategy);
extern PACKAGE void __fastcall ZDecompress(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, int outEstimate = 0x0);
extern PACKAGE void __fastcall ZDecompress2(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, int windowBits, int outEstimate = 0x0);
extern PACKAGE AnsiString __fastcall ZCompressStr(const AnsiString s, TZCompressionLevel level = (TZCompressionLevel)(0x2));
extern PACKAGE AnsiString __fastcall ZCompressStrEx(const AnsiString s, TZCompressionLevel level = (TZCompressionLevel)(0x2));
extern PACKAGE AnsiString __fastcall ZCompressStr2(const AnsiString s, TZCompressionLevel level, int windowBits, int memLevel, TZStrategy strategy);
extern PACKAGE AnsiString __fastcall ZCompressStrWeb(const AnsiString s);
extern PACKAGE AnsiString __fastcall ZDecompressStr(const AnsiString s);
extern PACKAGE AnsiString __fastcall ZDecompressStrEx(const AnsiString s);
extern PACKAGE AnsiString __fastcall ZDecompressStr2(const AnsiString s, int windowBits);
extern PACKAGE void __fastcall ZCompressStream(Classes::TStream* inStream, Classes::TStream* outStream, TZCompressionLevel level = (TZCompressionLevel)(0x2));
extern PACKAGE void __fastcall ZCompressStream2(Classes::TStream* inStream, Classes::TStream* outStream, TZCompressionLevel level, int windowBits, int memLevel, TZStrategy strategy);
extern PACKAGE void __fastcall ZCompressStreamWeb(Classes::TStream* inStream, Classes::TStream* outStream);
extern PACKAGE void __fastcall ZDecompressStream(Classes::TStream* inStream, Classes::TStream* outStream);
extern PACKAGE void __fastcall ZDecompressStream2(Classes::TStream* inStream, Classes::TStream* outStream, int windowBits);
extern PACKAGE int __fastcall ZAdler32(int adler, const void *buffer, int size);
extern PACKAGE int __fastcall ZCrc32(int crc, const void *buffer, int size);
extern PACKAGE int __fastcall inflateReset(TZStreamRec &strm);
extern PACKAGE int __fastcall inflate(TZStreamRec &strm, int flush);
extern PACKAGE int __fastcall inflateEnd(TZStreamRec &strm);

}	/* namespace Aczlibex */
using namespace Aczlibex;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acZLibEx
