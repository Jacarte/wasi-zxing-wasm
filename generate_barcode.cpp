/*
* Copyright 2016 Nu-book Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "BarcodeFormat.h"
#include "BitMatrix.h"
#include "MultiFormatWriter.h"
#include "TextUtfEncoding.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace ZXing;

static void PrintUsage(const char* exePath)
{
	std::cout << "Usage: " << exePath << " [-size <width>x<height>] [-margin <margin>] [-encoding <encoding>] [-ecc <level>] <format> <text> <output>\n"
	          << "    -size      Size of generated image\n"
	          << "    -margin    Margin around barcode\n"
	          << "    -encoding  Encoding used to encode input text\n"
	          << "    -ecc       Error correction level, [0-8]\n"
	          << "\n"
			  << "Supported formats are:\n";
	
	std::cout << "Format can be lowercase letters, with or without '-'.\n";
}

static bool ParseSize(std::string str, int* width, int* height)
{
	std::transform(str.begin(), str.end(), str.begin(), [](char c) { return (char)std::tolower(c); });
	auto xPos = str.find('x');
	if (xPos != std::string::npos) {
		*width = std::stoi(str.substr(0, xPos));
		*height = std::stoi(str.substr(xPos + 1));
		return true;
	}
	return false;
}

static bool ParseOptions(int argc, char* argv[], int* width, int* height, int* margin, int* eccLevel, BarcodeFormat* format, std::string* text, std::string* filePath)
{
	int nonOptArgCount = 0;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-size") == 0) {
			if (++i == argc)
				return false;
			if (!ParseSize(argv[i], width, height)) {
				std::cerr << "Invalid size specification: " << argv[i] << std::endl;
				return false;
			}
		}
		else if (strcmp(argv[i], "-margin") == 0) {
			if (++i == argc)
				return false;
			*margin = std::stoi(argv[i]);
		}
		else if (strcmp(argv[i], "-ecc") == 0) {
			if (++i == argc)
				return false;
			*eccLevel = std::stoi(argv[i]);
		}
		else if (nonOptArgCount == 0) {
			*format = BarcodeFormatFromString(argv[i]);
			if (!format) {
				std::cerr << "Unrecognized format: " << argv[i] << std::endl;
				return false;
			}
			++nonOptArgCount;
		}
		else if (nonOptArgCount == 1) {
			*text = argv[i];
			++nonOptArgCount;
		}
		else if (nonOptArgCount == 2) {
			*filePath = argv[i];
			++nonOptArgCount;
		}
		else {
			return false;
		}
	}

	return nonOptArgCount == 3;
}

static std::string GetExtension(const std::string& path)
{
	auto fileNameStart = path.find_last_of("/\\");
	auto fileName = fileNameStart == std::string::npos ? path : path.substr(fileNameStart + 1);
	auto extStart = fileName.find_last_of('.');
	auto ext = extStart == std::string::npos ? "" : fileName.substr(extStart + 1);
	std::transform(ext.begin(), ext.end(), ext.begin(), [](char c) { return std::tolower(c); });
	return ext;
}

int main(int argc, char* argv[])
{
	int width = 100, height = 100;
	int margin = 10;
	int eccLevel = -1;
	std::string text, filePath;
	BarcodeFormat format;

	if (!ParseOptions(argc, argv, &width, &height, &margin, &eccLevel, &format, &text, &filePath)) {
		PrintUsage(argv[0]);
		return -1;
	}

    auto writer = MultiFormatWriter(format).setMargin(margin).setEccLevel(eccLevel);
    auto encoding = TextUtfEncoding::FromUtf8(text);
    auto bitmatrix = writer.encode(encoding, width, height);


	return 0;
}