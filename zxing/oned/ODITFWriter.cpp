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
#include "ODITFWriter.h"
#include "ODWriterHelper.h"

#include <array>

namespace ZXing {
namespace OneD {

static const std::array<int, 4> START_PATTERN = { 1, 1, 1, 1 };
static const std::array<int, 3> END_PATTERN = { 3, 1, 1 };

static const int W = 3; // Pixel width of a wide line
static const int N = 1; // Pixed width of a narrow line

/**
* Patterns of Wide / Narrow lines to indicate each digit
*/
static const std::array<std::array<int, 5>, 10> PATTERNS = {
	N, N, W, W, N, // 0
	W, N, N, N, W, // 1
	N, W, N, N, W, // 2
	W, W, N, N, N, // 3
	N, N, W, N, W, // 4
	W, N, W, N, N, // 5
	N, W, W, N, N, // 6
	N, N, N, W, W, // 7
	W, N, N, W, N, // 8
	N, W, N, W, N,  // 9
};

BitMatrix
ITFWriter::encode(const std::wstring& contents, int width, int height) const
{
	size_t length = contents.length();
	if (length == 0) {
		exit(8); // throw std::invalid_argument("Found empty contents");
	}
	if (length % 2 != 0) {
		exit(8); // throw std::invalid_argument("The length of the input should be even");
	}
	if (length > 80) {
		exit(8); // throw std::invalid_argument("Requested contents should be less than 80 digits long");
	}

	std::vector<bool> result(9 + 9 * length, false);
	int pos = WriterHelper::AppendPattern(result, 0, START_PATTERN, true);
	for (size_t i = 0; i < length; i += 2) {
		int one = contents[i] - '0';
		int two = contents[i + 1] - '0';
		if (one < 0 || one > 9 || two < 0 || two > 9) {
			exit(8); // throw std::invalid_argument("Contents should contain only digits: 0-9");
		}
		std::array<int, 10> encoding = {};
		for (int j = 0; j < 5; j++) {
			encoding[2 * j] = PATTERNS[one][j];
			encoding[2 * j + 1] = PATTERNS[two][j];
		}
		pos += WriterHelper::AppendPattern(result, pos, encoding, true);
	}
	WriterHelper::AppendPattern(result, pos, END_PATTERN, true);
	return WriterHelper::RenderResult(result, width, height, _sidesMargin >= 0 ? _sidesMargin : 10);
}

} // OneD
} // ZXing
