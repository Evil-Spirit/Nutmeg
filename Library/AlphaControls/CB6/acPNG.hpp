// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'acPNG.pas' rev: 6.00

#ifndef acPNGHPP
#define acPNGHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sConst.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <acZLibEx.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Acpng
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TColorScheme { csUnknown, csIndexed, csG, csGA, csRGB, csRGBA, csBGR, csBGRA, csCMY, csCMYK, csCIELab, csYCbCr, csPhotoYCC };
#pragma option pop

#pragma option push -b-
enum acPNG__1 { coAlpha, coApplyGamma, coNeedByteSwap, coLabByteRange, coLabChromaOffset };
#pragma option pop

typedef Set<acPNG__1, coAlpha, coLabChromaOffset>  TConvertOptions;

#pragma option push -b-
enum TRawPaletteFormat { pfInterlaced8Triple, pfInterlaced8Quad, pfPlane8Triple, pfPlane8Quad, pfInterlaced16Triple, pfInterlaced16Quad, pfPlane16Triple, pfPlane16Quad };
#pragma option pop

typedef void __fastcall (__closure *TConversionMethod)(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);

typedef DynamicArray<int >  acPNG__3;

class DELPHICLASS TColorManager;
class PASCALIMPLEMENTATION TColorManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	bool FChanged;
	Byte FSourceBPS;
	Byte FTargetBPS;
	Byte FSourceSPP;
	Byte FTargetSPP;
	float FMainGamma;
	float FDisplayGamma;
	Byte FGammaTable[256];
	float FYCbCrCoefficients[3];
	Byte FHSubsampling;
	Byte FVSubSampling;
	DynamicArray<int >  FCrToRedTable;
	DynamicArray<int >  FCbToBlueTable;
	DynamicArray<int >  FCrToGreenTable;
	DynamicArray<int >  FCbToGreenTable;
	TColorScheme FSourceScheme;
	TColorScheme FTargetScheme;
	TConversionMethod FRowConversion;
	TConvertOptions FSourceOptions;
	TConvertOptions FTargetOptions;
	
protected:
	Byte __fastcall ComponentGammaConvert(Byte Value);
	Word __fastcall ComponentNoConvert16(Word Value);
	Byte __fastcall ComponentNoConvert8(Byte Value);
	Byte __fastcall ComponentScaleConvert(Word Value);
	Byte __fastcall ComponentScaleGammaConvert(Word Value);
	Byte __fastcall ComponentSwapScaleGammaConvert(Word Value);
	Byte __fastcall ComponentSwapScaleConvert(Word Value);
	Word __fastcall ComponentSwapConvert(Word Value);
	void __fastcall RowConvertBGR2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertBGR2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCIELAB2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCIELAB2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCMYK2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertCMYK2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertGray(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexed8(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexedBoth16(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexedSource16(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertIndexedTarget16(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertRGB2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertRGB2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertPhotoYCC2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertPhotoYCC2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertYCbCr2BGR(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall RowConvertYCbCr2RGB(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	void __fastcall CreateYCbCrLookup(void);
	Graphics::TPixelFormat __fastcall GetPixelFormat(int Index);
	void __fastcall PrepareConversion(void);
	void __fastcall SetSourceBitsPerSample(const Byte Value);
	void __fastcall SetSourceColorScheme(const TColorScheme Value);
	void __fastcall SetSourceSamplesPerPixel(const Byte Value);
	void __fastcall SetTargetBitsPerSample(const Byte Value);
	void __fastcall SetTargetColorScheme(const TColorScheme Value);
	void __fastcall SetTargetSamplesPerPixel(const Byte Value);
	
public:
	__fastcall TColorManager(void);
	void __fastcall ConvertRow(const void * const * Source, const int Source_Size, void * Target, unsigned Count, Byte Mask);
	HPALETTE __fastcall CreateColorPalette(const void * const * Data, const int Data_Size, TRawPaletteFormat DataFormat, unsigned ColorCount, bool RGB);
	HPALETTE __fastcall CreateGrayscalePalette(bool MinimumIsWhite);
	void __fastcall Error(const AnsiString Msg);
	void __fastcall SetGamma(float MainGamma, float DisplayGamma = 2.200000E+00);
	__property Byte SourceBitsPerSample = {read=FSourceBPS, write=SetSourceBitsPerSample, nodefault};
	__property TColorScheme SourceColorScheme = {read=FSourceScheme, write=SetSourceColorScheme, nodefault};
	__property TConvertOptions SourceOptions = {read=FSourceOptions, write=FSourceOptions, nodefault};
	__property Graphics::TPixelFormat SourcePixelFormat = {read=GetPixelFormat, index=0, nodefault};
	__property Byte SourceSamplesPerPixel = {read=FSourceSPP, write=SetSourceSamplesPerPixel, nodefault};
	__property Byte TargetBitsPerSample = {read=FTargetBPS, write=SetTargetBitsPerSample, nodefault};
	__property TColorScheme TargetColorScheme = {read=FTargetScheme, write=SetTargetColorScheme, nodefault};
	__property TConvertOptions TargetOptions = {read=FTargetOptions, write=FTargetOptions, nodefault};
	__property Graphics::TPixelFormat TargetPixelFormat = {read=GetPixelFormat, index=1, nodefault};
	__property Byte TargetSamplesPerPixel = {read=FTargetSPP, write=SetTargetSamplesPerPixel, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TColorManager(void) { }
	#pragma option pop
	
};


typedef DynamicArray<Byte >  TByteArray;

typedef DynamicArray<unsigned >  TCardinalArray;

typedef DynamicArray<float >  TFloatArray;

class DELPHICLASS TLZ77Decoder;
class PASCALIMPLEMENTATION TLZ77Decoder : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	#pragma pack(push, 1)
	Aczlibex::TZStreamRec FStream;
	#pragma pack(pop)
	
	int FZLibResult;
	int FFlushMode;
	bool FAutoReset;
	int __fastcall GetAvailableInput(void);
	int __fastcall GetAvailableOutput(void);
	
public:
	__fastcall TLZ77Decoder(int FlushMode, bool AutoReset);
	void __fastcall Decode(void * &Source, void * &Dest, int PackedSize, int UnpackedSize);
	void __fastcall DecodeEnd(void);
	void __fastcall DecodeInit(void);
	void __fastcall Encode(void * Source, void * Dest, unsigned Count, unsigned &BytesStored);
	__property int AvailableInput = {read=GetAvailableInput, nodefault};
	__property int AvailableOutput = {read=GetAvailableOutput, nodefault};
	__property int ZLibResult = {read=FZLibResult, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TLZ77Decoder(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum acPNG__5 { ioBigEndian, ioUseGamma };
#pragma option pop

typedef Set<acPNG__5, ioBigEndian, ioUseGamma>  TImageOptions;

#pragma option push -b-
enum TCompressionType { ctUnknown, ctNone, ctLZ77 };
#pragma option pop

struct TImageProperties;
typedef TImageProperties *PImageProperties;

#pragma pack(push, 4)
struct TImageProperties
{
	TImageOptions Options;
	unsigned Width;
	unsigned Height;
	TColorScheme ColorScheme;
	Byte BitsPerSample;
	Byte SamplesPerPixel;
	Byte BitsPerPixel;
	TCompressionType Compression;
	float FileGamma;
	bool Interlaced;
	bool HasAlpha;
	Byte FilterMode;
} ;
#pragma pack(pop)

typedef char TChunkType[4];

#pragma pack(push, 1)
struct TPNGChunkHeader
{
	unsigned Length;
	char ChunkType[4];
} ;
#pragma pack(pop)

class DELPHICLASS TPNGGraphic;
class PASCALIMPLEMENTATION TPNGGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
private:
	TColorManager* FColorManager;
	#pragma pack(push, 1)
	Types::TRect FProgressRect;
	#pragma pack(pop)
	
	unsigned FBasePosition;
	Classes::TStream* FStream;
	TImageProperties FImageProperties;
	TLZ77Decoder* FDecoder;
	int FIDATSize;
	void *FRawBuffer;
	void *FCurrentSource;
	#pragma pack(push, 1)
	TPNGChunkHeader FHeader;
	#pragma pack(pop)
	
	unsigned FCurrentCRC;
	int FSourceBPP;
	HPALETTE FPalette;
	DynamicArray<Byte >  FTransparency;
	Graphics::TColor FTransparentColor;
	Graphics::TColor FBackgroundColor;
	void __fastcall ApplyFilter(Byte Filter, System::PByte Line, System::PByte PrevLine, System::PByte Target, int BPP, int BytesPerRow);
	bool __fastcall IsChunk(const char * ChunkType);
	unsigned __fastcall LoadAndSwapHeader(void);
	void __fastcall LoadBackgroundColor(const void *Description);
	void __fastcall LoadIDAT(const void *Description);
	void __fastcall LoadTransparency(const void *Description);
	void __fastcall ReadDataAndCheckCRC(void);
	void __fastcall ReadRow(void * RowBuffer, int BytesPerRow);
	int __fastcall SetupColorDepth(int ColorType, int BitDepth);
	
public:
	bool Reflected;
	__fastcall virtual TPNGGraphic(void);
	__fastcall virtual ~TPNGGraphic(void);
	virtual void __fastcall Draw(Graphics::TCanvas* ACanvas, const Types::TRect &Rect);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	/*         class method */ static bool __fastcall CanLoad(TMetaClass* vmt, const AnsiString FileName)/* overload */;
	/*         class method */ static bool __fastcall CanLoad(TMetaClass* vmt, Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	bool __fastcall ReadImageProperties(Classes::TStream* Stream, unsigned ImageIndex);
	__property Graphics::TColor BackgroundColor = {read=FBackgroundColor, nodefault};
	__property TByteArray Transparency = {read=FTransparency};
	__property TColorManager* ColorManager = {read=FColorManager};
	__property TImageProperties ImageProperties = {read=FImageProperties, write=FImageProperties};
};


//-- var, const, procedure ---------------------------------------------------
#define DefaultDisplayGamma  (2.200000E+00)
#define gesInvalidImage "Cannot load image. Invalid or unexpected %s image format."\
	""
#define gesInvalidColorFormat "Invalid color format in %s file."
#define gesUnsupportedFeature "Cannot load image. %s not supported for %s files."
#define gesInvalidCRC "Cannot load image. CRC error found in %s file."
#define gesCompression "Cannot load image. Compression error found in %s file."
#define gesExtraCompressedData "Cannot load image. Extra compressed data found in %s file"\
	"."
#define gesInvalidPalette "Cannot load image. Palette in %s file is invalid."
#define gesUnknownCriticalChunk "Cannot load PNG image. Unexpected but critical chunk detec"\
	"ted."
#define gesIndexedNotSupported "Conversion between indexed and non-indexed pixel formats i"\
	"s not supported."
#define gesConversionUnsupported "Color conversion failed. Could not find a proper method."
#define gesInvalidSampleDepth "Color depth is invalid. Bits per sample must be 1, 2, 4, 8"\
	" or 16."
#define gesInvalidPixelDepth "Sample count per pixel does not correspond to the given co"\
	"lor scheme."
#define gesInvalidSubSampling "Subsampling value is invalid. Allowed are 1, 2 and 4."
#define gesVerticalSubSamplingError "Vertical subsampling value must be <= horizontal subsampli"\
	"ng value."
#define gesPreparing "Preparing..."
#define gesLoadingData "Loading data..."
#define gesUpsampling "Upsampling..."
#define gesTransfering "Transfering..."
extern PACKAGE Byte PNGMagic[8];
extern PACKAGE bool UseACPng;
extern PACKAGE void __fastcall SwapLong(System::PInteger P, unsigned Count)/* overload */;
extern PACKAGE unsigned __fastcall SwapLong(unsigned Value)/* overload */;
extern PACKAGE Byte __fastcall ClampByte(int Value);
extern PACKAGE Word __fastcall MulDiv16(Word Number, Word Numerator, Word Denominator);
extern PACKAGE HICON __fastcall MakeIcon32(Graphics::TBitmap* Img, bool UpdateAlphaChannell = false);
extern PACKAGE HICON __fastcall MakeCompIcon(TPNGGraphic* Img, Graphics::TColor BGColor = (Graphics::TColor)(0x1fffffff));
extern PACKAGE void __fastcall UpdateTransPixels(Graphics::TBitmap* Img);

}	/* namespace Acpng */
using namespace Acpng;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// acPNG
