/*
* Copyright 2016 Huy Cuong Nguyen
* Copyright 2016 ZXing authors
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

#include "ODCode39Writer.h"
#include "ODWriterHelper.h"
#include "ZXContainerAlgorithms.h"
#include "TextEncoder.h"
#include "CharacterSet.h"
#include "ZXStrConvWorkaround.h"

#include <array>

namespace ZXing {
namespace OneD {

static const char ALPHABET_STRING[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-. *$/+%";

/**
* These represent the encodings of characters, as patterns of wide and narrow bars.
* The 9 least-significant bits of each int correspond to the pattern of wide and narrow,
* with 1s representing "wide" and 0s representing narrow.
*/
static const int CHARACTER_ENCODINGS[] = {
	0x034, 0x121, 0x061, 0x160, 0x031, 0x130, 0x070, 0x025, 0x124, 0x064, // 0-9
	0x109, 0x049, 0x148, 0x019, 0x118, 0x058, 0x00D, 0x10C, 0x04C, 0x01C, // A-J
	0x103, 0x043, 0x142, 0x013, 0x112, 0x052, 0x007, 0x106, 0x046, 0x016, // K-T
	0x181, 0x0C1, 0x1C0, 0x091, 0x190, 0x0D0, 0x085, 0x184, 0x0C4, 0x094, // U-*
	0x0A8, 0x0A2, 0x08A, 0x02A // $-%
};

static_assert(Length(ALPHABET_STRING) - 1 == Length(CHARACTER_ENCODINGS), "table size mismatch");

static const int ASTERISK_ENCODING = CHARACTER_ENCODINGS[39];

static void ToIntArray(int a, std::array<int, 9>& toReturn) {
	for (int i = 0; i < 9; ++i) {
		toReturn[i] = (a & (1 << (8 - i))) == 0 ? 1 : 2;
	}
}

static std::string ToHexString(int c)
{
	const char* digits = "0123456789abcdef";
	std::string val(4, '0');
	val[1] = 'x';
	val[2] = digits[(c >> 4) & 0xf];
	val[3] = digits[c & 0xf];
	return val;
}

static std::string TryToConvertToExtendedMode(const std::wstring& contents) {
	size_t length = contents.length();
	std::string extendedContent;
	extendedContent.reserve(length * 2);

	for (size_t i = 0; i < length; i++) {
		int character = contents[i];
		switch (character) {
			case '\0':
				extendedContent.append("%U");
				break;
			case ' ':
			case '-':
			case '.':
				extendedContent.push_back((char)character);
				break;
			case '@':
				extendedContent.append("%V");
				break;
			case '`':
				extendedContent.append("%W");
				break;
			default:
				if (character > 0 && character < 27) {
					extendedContent.push_back('$');
					extendedContent.push_back((char)('A' + (character - 1)));
				}
				else if (character > 26 && character < ' ') {
					extendedContent.push_back('%');
					extendedContent.push_back((char)('A' + (character - 27)));
				}
				else if ((character > ' ' && character < '-') || character == '/' || character == ':') {
					extendedContent.push_back('/');
					extendedContent.push_back((char)('A' + (character - 33)));
				}
				else if (character > '/' && character < ':') {
					extendedContent.push_back((char)('0' + (character - 48)));
				}
				else if (character > ':' && character < '@') {
					extendedContent.push_back('%');
					extendedContent.push_back((char)('F' + (character - 59)));
				}
				else if (character > '@' && character < '[') {
					extendedContent.push_back((char)('A' + (character - 65)));
				}
				else if (character > 'Z' && character < '`') {
					extendedContent.push_back('%');
					extendedContent.push_back((char)('K' + (character - 91)));
				}
				else if (character > '`' && character < '{') {
					extendedContent.push_back('+');
					extendedContent.push_back((char)('A' + (character - 97)));
				}
				else if (character > 'z' && character < 128) {
					extendedContent.push_back('%');
					extendedContent.push_back((char)('P' + (character - 123)));
				}
				else {
					exit(5); // throw std::invalid_argument("Requested content contains a non-encodable character: '" + ToHexString(character) + "'");
				}
				break;
		}
	}

	return extendedContent;
}

BitMatrix
Code39Writer::encode(const std::wstring& contents, int width, int height) const
{
	size_t length = contents.length();
	if (length == 0) {
		exit(5); // throw std::invalid_argument("Found empty contents");
	}
	if (length > 80) {
		exit(5); // throw std::invalid_argument("Requested contents should be less than 80 digits long");
	}

	std::string extendedContent;
	for (size_t i = 0; i < length; i++) {
		int indexInString = IndexOf(ALPHABET_STRING, contents[i]);
		if (indexInString < 0) {
			extendedContent = TryToConvertToExtendedMode(contents);
			length = extendedContent.length();
			if (length > 80) {
				exit(5); // throw std::invalid_argument("Requested contents should be less than 80 digits long, but got " + std::to_string(length) + " (extended full ASCII mode)");
			}
			break;
		}
	}
	
	if (extendedContent.empty()) {
		extendedContent = TextEncoder::FromUnicode(contents, CharacterSet::ISO8859_1);
	}

	std::array<int, 9> widths = {};
	size_t codeWidth = 24 + 1 + (13 * length);

	std::vector<bool> result(codeWidth, false);
	ToIntArray(ASTERISK_ENCODING, widths);
	int pos = WriterHelper::AppendPattern(result, 0, widths, true);
	std::array<int, 1> narrowWhite = { 1 };
	pos += WriterHelper::AppendPattern(result, pos, narrowWhite, false);
	//append next character to byte matrix
	for (size_t i = 0; i < length; ++i) {
		int indexInString = IndexOf(ALPHABET_STRING, extendedContent[i]);
		ToIntArray(CHARACTER_ENCODINGS[indexInString], widths);
		pos += WriterHelper::AppendPattern(result, pos, widths, true);
		pos += WriterHelper::AppendPattern(result, pos, narrowWhite, false);
	}
	ToIntArray(ASTERISK_ENCODING, widths);
	WriterHelper::AppendPattern(result, pos, widths, true);
	return WriterHelper::RenderResult(result, width, height, _sidesMargin >= 0 ? _sidesMargin : 10);
}


} // OneD
} // ZXing
