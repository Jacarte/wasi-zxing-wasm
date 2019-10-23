cmake_minimum_required (VERSION 3.1.3)

project (ZXingExamples)

set (ENABLE_DECODERS ON CACHE BOOL "Check to include decoders")
set (CMAKE_SYSROOT /opt/wasi-sdk/share/wasi-sysroot)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=wasm32-wasi -Wall -Wextra -fno-exceptions")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -D_DEBUG")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

################# Source files

set (COMMON_FILES
    zxing/BarcodeFormat.h
    zxing/BarcodeFormat.cpp
    zxing/BitArray.h
    zxing/BitArray.cpp
    zxing/BitHacks.h
    zxing/BitMatrix.h
    zxing/BitMatrix.cpp
    zxing/ByteArray.h
    zxing/CharacterSet.h
    zxing/CharacterSetECI.h
    zxing/CharacterSetECI.cpp
    zxing/CustomData.h
    zxing/GenericGF.h
    zxing/GenericGF.cpp
    zxing/GenericGFPoly.h
    zxing/GenericGFPoly.cpp
    zxing/TextUtfEncoding.h
    zxing/TextUtfEncoding.cpp
    zxing/ZXBigInteger.h
    zxing/ZXBigInteger.cpp
    zxing/ZXConfig.h
    zxing/ZXFilesystem.h
    zxing/ZXNullable.h
    zxing/ZXNumeric.h
    zxing/ZXContainerAlgorithms.h
    zxing/ZXStrConvWorkaround.h
    zxing/ZXTestSupport.h
)
if (ENABLE_DECODERS)
    set (COMMON_FILES ${COMMON_FILES}
        zxing/BinaryBitmap.h
        zxing/BitSource.h
        zxing/BitSource.cpp
        zxing/DecodeHints.h
        zxing/DecodeHints.cpp
        zxing/DecodeStatus.h
        zxing/DecodeStatus.cpp
        zxing/DecoderResult.h
        zxing/DetectorResult.h
        zxing/GenericLuminanceSource.h
        zxing/GenericLuminanceSource.cpp
        zxing/GlobalHistogramBinarizer.h
        zxing/GlobalHistogramBinarizer.cpp
        zxing/GridSampler.h
        zxing/GridSampler.cpp
        zxing/HybridBinarizer.h
        zxing/HybridBinarizer.cpp
        zxing/LuminanceSource.h
        zxing/LuminanceSource.cpp
        zxing/MultiFormatReader.h
        zxing/MultiFormatReader.cpp
        zxing/PerspectiveTransform.h
        zxing/PerspectiveTransform.cpp
        zxing/Reader.h
        zxing/ReadBarcode.h
        zxing/ReadBarcode.cpp
        zxing/ReedSolomonDecoder.h
        zxing/ReedSolomonDecoder.cpp
        zxing/Result.h
        zxing/Result.cpp
        zxing/ResultMetadata.h
        zxing/ResultMetadata.cpp
        zxing/ResultPoint.h
        zxing/ResultPoint.cpp
        zxing/TextDecoder.h
        zxing/TextDecoder.cpp
        zxing/WhiteRectDetector.h
        zxing/WhiteRectDetector.cpp
    )
endif()

set (AZTEC_FILES
)
if (ENABLE_DECODERS)
    set (AZTEC_FILES ${AZTEC_FILES}
        zxing/aztec/AZDecoder.h
        zxing/aztec/AZDecoder.cpp
        zxing/aztec/AZDetector.h
        zxing/aztec/AZDetector.cpp
        zxing/aztec/AZDetectorResult.h
        zxing/aztec/AZReader.h
        zxing/aztec/AZReader.cpp
    )
endif()

set (DATAMATRIX_FILES
)
if (ENABLE_DECODERS)
    set (DATAMATRIX_FILES ${DATAMATRIX_FILES}
        zxing/datamatrix/DMBitMatrixParser.h
        zxing/datamatrix/DMBitMatrixParser.cpp
        zxing/datamatrix/DMECB.h
        zxing/datamatrix/DMDataBlock.h
        zxing/datamatrix/DMDataBlock.cpp
        zxing/datamatrix/DMDecoder.h
        zxing/datamatrix/DMDecoder.cpp
        zxing/datamatrix/DMDetector.h
        zxing/datamatrix/DMDetector.cpp
        zxing/datamatrix/DMVersion.h
        zxing/datamatrix/DMVersion.cpp
        zxing/datamatrix/DMReader.h
        zxing/datamatrix/DMReader.cpp
    )
endif()

set (MAXICODE_FILES
)
if (ENABLE_DECODERS)
    set (MAXICODE_FILES ${MAXICODE_FILES}
        zxing/maxicode/MCBitMatrixParser.h
        zxing/maxicode/MCBitMatrixParser.cpp
        zxing/maxicode/MCDecoder.h
        zxing/maxicode/MCDecoder.cpp
        zxing/maxicode/MCReader.h
        zxing/maxicode/MCReader.cpp
    )
endif()

set (ONED_FILES
    zxing/oned/ODUPCEANCommon.h
    zxing/oned/ODUPCEANCommon.cpp
    zxing/oned/ODCode128Patterns.h
    zxing/oned/ODCode128Patterns.cpp
)
if (ENABLE_DECODERS)
    set (ONED_FILES ${ONED_FILES}
        zxing/oned/ODCodabarReader.h
        zxing/oned/ODCodabarReader.cpp
        zxing/oned/ODCode39Reader.h
        zxing/oned/ODCode39Reader.cpp
        zxing/oned/ODCode93Reader.h
        zxing/oned/ODCode93Reader.cpp
        zxing/oned/ODCode128Reader.h
        zxing/oned/ODCode128Reader.cpp
        zxing/oned/ODEAN8Reader.h
        zxing/oned/ODEAN8Reader.cpp
        zxing/oned/ODEAN13Reader.h
        zxing/oned/ODEAN13Reader.cpp
        zxing/oned/ODEANManufacturerOrgSupport.h
        zxing/oned/ODEANManufacturerOrgSupport.cpp
        zxing/oned/ODITFReader.h
        zxing/oned/ODITFReader.cpp
        zxing/oned/ODMultiUPCEANReader.h
        zxing/oned/ODMultiUPCEANReader.cpp
        zxing/oned/ODReader.h
        zxing/oned/ODReader.cpp
        zxing/oned/ODRowReader.h
        zxing/oned/ODRowReader.cpp
        zxing/oned/ODRSS14Reader.h
        zxing/oned/ODRSS14Reader.cpp
        zxing/oned/ODRSSExpandedReader.h
        zxing/oned/ODRSSExpandedReader.cpp
        zxing/oned/ODUPCAReader.h
        zxing/oned/ODUPCAReader.cpp
        zxing/oned/ODUPCEANExtensionSupport.h
        zxing/oned/ODUPCEANExtensionSupport.cpp
        zxing/oned/ODUPCEANReader.h
        zxing/oned/ODUPCEANReader.cpp
        zxing/oned/ODUPCEReader.h
        zxing/oned/ODUPCEReader.cpp
    )
endif()

set (ONED_RSS_FILES
)
if (ENABLE_DECODERS)
    set (ONED_RSS_FILES ${ONED_RSS_FILES}
        zxing/oned/rss/ODRSSDataCharacter.h
        zxing/oned/rss/ODRSSExpandedBinaryDecoder.h
        zxing/oned/rss/ODRSSExpandedBinaryDecoder.cpp
        zxing/oned/rss/ODRSSExpandedPair.h
        zxing/oned/rss/ODRSSExpandedRow.h
        zxing/oned/rss/ODRSSFieldParser.h
        zxing/oned/rss/ODRSSFieldParser.cpp
        zxing/oned/rss/ODRSSFinderPattern.h
        zxing/oned/rss/ODRSSGenericAppIdDecoder.h
        zxing/oned/rss/ODRSSGenericAppIdDecoder.cpp
        zxing/oned/rss/ODRSSPair.h
        zxing/oned/rss/ODRSSReaderHelper.h
        zxing/oned/rss/ODRSSReaderHelper.cpp
    )
endif()

set (PDF417_FILES
)
if (ENABLE_DECODERS)
    set (PDF417_FILES ${PDF417_FILES}
        zxing/pdf417/PDFBarcodeMetadata.h
        zxing/pdf417/PDFBarcodeValue.h
        zxing/pdf417/PDFBarcodeValue.cpp
        zxing/pdf417/PDFBoundingBox.h
        zxing/pdf417/PDFBoundingBox.cpp
        zxing/pdf417/PDFCodeword.h
        zxing/pdf417/PDFCodewordDecoder.h
        zxing/pdf417/PDFCodewordDecoder.cpp
        zxing/pdf417/PDFDecodedBitStreamParser.h
        zxing/pdf417/PDFDecodedBitStreamParser.cpp
        zxing/pdf417/PDFDecoderResultExtra.h
        zxing/pdf417/PDFDetectionResult.h
        zxing/pdf417/PDFDetectionResult.cpp
        zxing/pdf417/PDFDetectionResultColumn.h
        zxing/pdf417/PDFDetectionResultColumn.cpp
        zxing/pdf417/PDFDetector.h
        zxing/pdf417/PDFDetector.cpp
        zxing/pdf417/PDFModulusGF.h
        zxing/pdf417/PDFModulusGF.cpp
        zxing/pdf417/PDFModulusPoly.h
        zxing/pdf417/PDFModulusPoly.cpp
        zxing/pdf417/PDFReader.h
        zxing/pdf417/PDFReader.cpp
        zxing/pdf417/PDFScanningDecoder.h
        zxing/pdf417/PDFScanningDecoder.cpp
    )
endif()

set (QRCODE_FILES
    zxing/qrcode/QRCodecMode.h
    zxing/qrcode/QRCodecMode.cpp
    zxing/qrcode/QRErrorCorrectionLevel.h
    zxing/qrcode/QRErrorCorrectionLevel.cpp
    zxing/qrcode/QRVersion.h
    zxing/qrcode/QRVersion.cpp
)
if (ENABLE_DECODERS)
    set (QRCODE_FILES ${QRCODE_FILES}
        zxing/qrcode/QRAlignmentPattern.h
        zxing/qrcode/QRAlignmentPattern.cpp
        zxing/qrcode/QRAlignmentPatternFinder.h
        zxing/qrcode/QRAlignmentPatternFinder.cpp
        zxing/qrcode/QRBitMatrixParser.h
        zxing/qrcode/QRBitMatrixParser.cpp
        zxing/qrcode/QRDataBlock.h
        zxing/qrcode/QRDataBlock.cpp
        zxing/qrcode/QRDataMask.h
        zxing/qrcode/QRDataMask.cpp
        zxing/qrcode/QRDecoder.h
        zxing/qrcode/QRDecoder.cpp
        zxing/qrcode/QRDecoderMetadata.h
        zxing/qrcode/QRDetector.h
        zxing/qrcode/QRDetector.cpp
        zxing/qrcode/QRECB.h
        zxing/qrcode/QRFinderPattern.h
        zxing/qrcode/QRFinderPattern.cpp
        zxing/qrcode/QRFinderPatternFinder.h
        zxing/qrcode/QRFinderPatternFinder.cpp
        zxing/qrcode/QRFinderPatternInfo.h
        zxing/qrcode/QRFormatInformation.h
        zxing/qrcode/QRFormatInformation.cpp
        zxing/qrcode/QRReader.h
        zxing/qrcode/QRReader.cpp
    )
endif()

set (TEXT_CODEC_FILES
    zxing/textcodec/Big5MapTable.h
    zxing/textcodec/Big5MapTable.cpp
    zxing/textcodec/KRHangulMapping.h
    zxing/textcodec/KRHangulMapping.cpp
)
if (ENABLE_DECODERS)
    set (TEXT_CODEC_FILES ${TEXT_CODEC_FILES}
        zxing/textcodec/Big5TextDecoder.h
        zxing/textcodec/Big5TextDecoder.cpp
        zxing/textcodec/GBTextDecoder.h
        zxing/textcodec/GBTextDecoder.cpp
        zxing/textcodec/JPTextDecoder.h
        zxing/textcodec/JPTextDecoder.cpp
        zxing/textcodec/KRTextDecoder.h
        zxing/textcodec/KRTextDecoder.cpp
    )
endif()

add_executable (zxing_barcode_reader.wasm
        scan_image.cpp
        ${COMMON_FILES}
        ${AZTEC_FILES}
        ${DATAMATRIX_FILES}
        ${MAXICODE_FILES}
        ${ONED_FILES}
        ${ONED_RSS_FILES}
        ${PDF417_FILES}
        ${QRCODE_FILES}
        ${TEXT_CODEC_FILES}
    )
    
target_include_directories (zxing_barcode_reader.wasm
    PRIVATE stb
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/zxing>"
)
