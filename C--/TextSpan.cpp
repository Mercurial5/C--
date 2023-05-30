#include "TextSpan.h"

TextSpan::TextSpan(int start, int length) {
	this->start = start;
	this->length = length;
	this->end = start + length;
}
