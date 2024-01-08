// Test harness for kirk engine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libkirk/kirk_engine.h"

unsigned char kirk7tests[0x80][0x10] = {
	{0x4C, 0x64, 0xBD, 0xF4, 0x98, 0x3A, 0xAE, 0xAB, 0x5E, 0x96, 0x7C, 0xE2, 0xE7, 0xBE, 0x10, 0x78},
	{0xCF, 0xED, 0x17, 0xE0, 0x89, 0x7C, 0x23, 0xF3, 0xFB, 0xDD, 0x13, 0x45, 0x12, 0xEC, 0x63, 0x61},
	{0x5F, 0x57, 0x6F, 0xB1, 0xF7, 0x5A, 0x8D, 0xFD, 0x65, 0xE2, 0xF1, 0xCA, 0xA9, 0xE3, 0xBE, 0x56},
	{0xE4, 0x8B, 0x57, 0x4C, 0x6E, 0xAF, 0x62, 0x51, 0x5C, 0x44, 0x52, 0x1D, 0xBA, 0x7D, 0xD4, 0x32},
	{0xC1, 0xBC, 0x73, 0x75, 0x8B, 0xEB, 0x7F, 0x27, 0x0A, 0xC5, 0x91, 0x61, 0x5F, 0xE0, 0xC9, 0x90},
	{0x2C, 0x54, 0x90, 0x63, 0x0A, 0x9E, 0x20, 0xF1, 0xD0, 0xA2, 0xFD, 0xC6, 0xE6, 0x4D, 0xAF, 0xF2},
	{0x3D, 0x15, 0x52, 0x25, 0x03, 0xE1, 0x20, 0x55, 0x47, 0x33, 0x5D, 0xE3, 0xF0, 0xE7, 0x94, 0x5E},
	{0xCE, 0xC2, 0xC1, 0xD9, 0x89, 0xF7, 0x97, 0xF2, 0xE4, 0xBC, 0xBF, 0x19, 0x70, 0x7E, 0xC4, 0x38},
	{0x85, 0x0D, 0x65, 0x85, 0x4F, 0xB6, 0xA9, 0xB5, 0x76, 0x2D, 0xA8, 0xB0, 0xAB, 0xF2, 0x3E, 0xD4},
	{0xCB, 0x3C, 0x6B, 0xA6, 0xCF, 0x5D, 0x26, 0xF7, 0x83, 0x3E, 0xF5, 0x54, 0x4B, 0x0A, 0x5D, 0xCF},
	{0xE9, 0xD1, 0xEE, 0x42, 0x8D, 0xDA, 0x45, 0xE7, 0x9B, 0xA2, 0x7C, 0xD4, 0xE1, 0x0D, 0xAB, 0xFA},
	{0x74, 0xB0, 0x85, 0xE2, 0x0F, 0xA2, 0x6F, 0x77, 0x6A, 0x62, 0xA9, 0xF6, 0x0D, 0x7A, 0x58, 0xFA},
	{0x56, 0x2D, 0xD2, 0xAD, 0x83, 0xFA, 0x7B, 0x61, 0x22, 0x63, 0xC6, 0x87, 0x8B, 0x49, 0x14, 0x97},
	{0x86, 0x0A, 0x8A, 0x65, 0xC0, 0xDF, 0x9C, 0x5A, 0xCF, 0x95, 0x13, 0xC7, 0xF9, 0x87, 0xE0, 0xB4},
	{0x39, 0x74, 0x44, 0xE0, 0x21, 0xB1, 0x79, 0x8A, 0x6D, 0x1E, 0x4E, 0x5B, 0x88, 0x47, 0x09, 0x43},
	{0x2C, 0x58, 0x69, 0x93, 0x9F, 0xEF, 0x36, 0xB8, 0xA9, 0x67, 0x06, 0xD5, 0x6F, 0x3A, 0xC6, 0xED},
	{0x96, 0xAD, 0xF5, 0x4E, 0x2B, 0x1B, 0x11, 0x43, 0x01, 0x69, 0xDA, 0xFA, 0x2B, 0x22, 0xEF, 0x8E},
	{0x90, 0xE6, 0xBB, 0x58, 0x5D, 0xBC, 0x22, 0x2B, 0x1E, 0x26, 0x86, 0xB5, 0x99, 0xDB, 0x6F, 0x91},
	{0x25, 0xF1, 0x3A, 0x74, 0x00, 0x24, 0x14, 0x2C, 0xDB, 0xE7, 0x1D, 0x18, 0x12, 0x96, 0x41, 0x5A},
	{0x51, 0xB2, 0x01, 0x86, 0x94, 0x21, 0xFA, 0xD3, 0x14, 0x6B, 0xFC, 0x89, 0x2F, 0xDC, 0x99, 0x44},
	{0x56, 0xB7, 0xD4, 0xDC, 0x83, 0x6E, 0x97, 0x49, 0xC4, 0x6D, 0xFA, 0x72, 0xA9, 0x74, 0x03, 0xC5},
	{0xBB, 0x94, 0x0C, 0x19, 0xF3, 0x1F, 0x66, 0x1F, 0x8A, 0x79, 0xC2, 0xCF, 0x8E, 0x0B, 0x01, 0x21},
	{0xCD, 0x80, 0x17, 0x39, 0xFA, 0x57, 0x3D, 0x73, 0x0E, 0xBB, 0x9C, 0xB7, 0xD3, 0x5F, 0x59, 0xF9},
	{0x3A, 0xA2, 0x57, 0x16, 0xCA, 0xA1, 0xC5, 0x2E, 0x06, 0xD2, 0x31, 0xF7, 0xC9, 0xE8, 0x51, 0x66},
	{0xA8, 0x12, 0x30, 0xB3, 0xBA, 0x02, 0x5F, 0x3D, 0x99, 0x33, 0x01, 0x4D, 0x6B, 0xD9, 0x2E, 0x3E},
	{0x79, 0x9A, 0x56, 0x66, 0x1F, 0xFA, 0x69, 0xAC, 0xA0, 0x58, 0x49, 0x51, 0xEF, 0x1D, 0xA1, 0xDD},
	{0x85, 0x40, 0x2B, 0x91, 0x3E, 0xEC, 0x68, 0x60, 0x87, 0x71, 0xBF, 0xEA, 0x74, 0xFB, 0x10, 0x3A},
	{0x2F, 0xA8, 0x12, 0xB3, 0x68, 0xB1, 0x44, 0xCF, 0x09, 0xC4, 0xDE, 0x4C, 0xF9, 0x00, 0x60, 0xE7},
	{0xC9, 0x2A, 0xD2, 0x53, 0x5D, 0x3C, 0xD6, 0xB2, 0x9E, 0x41, 0x21, 0xFF, 0x1D, 0xAE, 0x19, 0x16},
	{0x22, 0x02, 0x56, 0x57, 0xD0, 0x37, 0x5A, 0x7E, 0x75, 0xD4, 0x5E, 0x7D, 0xFA, 0x99, 0x6B, 0x51},
	{0x4F, 0x94, 0xD2, 0x3C, 0x13, 0x04, 0x67, 0x17, 0x24, 0xC6, 0x33, 0xBA, 0xDA, 0x1D, 0xBE, 0x3D},
	{0xA9, 0x7C, 0xD8, 0xAD, 0x00, 0xC9, 0x00, 0x3C, 0xCA, 0xDA, 0x02, 0x24, 0x28, 0x3E, 0xD8, 0xA0},
	{0xBD, 0x91, 0x2E, 0xD1, 0x3A, 0x8B, 0x66, 0x95, 0x51, 0x78, 0x7B, 0xFC, 0x76, 0x44, 0xB0, 0x9D},
	{0xDD, 0x48, 0xB4, 0xCD, 0x61, 0x6F, 0xA7, 0xF9, 0x19, 0x4B, 0xDC, 0xD7, 0x6E, 0x05, 0x3E, 0x56},
	{0x64, 0x41, 0x49, 0xED, 0x1F, 0x4B, 0xF6, 0x1C, 0xCB, 0xF3, 0x97, 0xB3, 0x7B, 0xEE, 0x8D, 0x7F},
	{0x15, 0x34, 0x82, 0xF0, 0x78, 0x4C, 0xED, 0x7F, 0x2D, 0xBB, 0x8A, 0xE9, 0xED, 0xFA, 0xBE, 0x9B},
	{0xE5, 0x48, 0xFD, 0xE9, 0x70, 0x47, 0x05, 0x27, 0x1C, 0x50, 0x25, 0x77, 0x76, 0xCA, 0x52, 0x52},
	{0x9A, 0x91, 0xEC, 0x08, 0x3E, 0x92, 0xB5, 0xC6, 0x8A, 0x30, 0xB8, 0x92, 0x6C, 0x44, 0x9B, 0x1E},
	{0x0E, 0x0D, 0xE0, 0x0E, 0x0F, 0x94, 0xDC, 0x0D, 0x83, 0x33, 0x27, 0x74, 0xA8, 0x27, 0x47, 0xE7},
	{0xC5, 0x57, 0xF8, 0xA0, 0xC6, 0x88, 0xCE, 0x9A, 0x59, 0x1B, 0x91, 0x4E, 0x07, 0x2E, 0xD6, 0xEA},
	{0x4D, 0x1C, 0x49, 0xF8, 0xFA, 0xC4, 0x04, 0x31, 0xC5, 0x26, 0x17, 0x27, 0x0A, 0x40, 0xE3, 0xEF},
	{0x4C, 0x5A, 0x7F, 0x60, 0x40, 0x61, 0xDD, 0xD3, 0xC2, 0x32, 0x86, 0x06, 0x37, 0xD8, 0xEE, 0xC7},
	{0x08, 0x58, 0x03, 0x35, 0x24, 0x0D, 0x55, 0x34, 0xD8, 0x62, 0xC2, 0x18, 0xAA, 0xDD, 0x76, 0xE9},
	{0x33, 0x9E, 0x5A, 0xDB, 0xB3, 0x43, 0x29, 0xA1, 0x2F, 0xD1, 0x78, 0x33, 0xDD, 0x8F, 0xD3, 0x83},
	{0x33, 0xB4, 0xBC, 0xD6, 0xF5, 0xD7, 0x52, 0x1A, 0xB0, 0xC4, 0x4C, 0x80, 0x79, 0x6E, 0x26, 0x93},
	{0x2D, 0xC4, 0x4E, 0x3E, 0xF4, 0xC4, 0xD9, 0x74, 0x71, 0x1F, 0x6D, 0x47, 0xC9, 0x8B, 0x28, 0x5F},
	{0xFE, 0x24, 0x95, 0x25, 0x3E, 0x16, 0x63, 0x83, 0x57, 0x6D, 0xB1, 0xE5, 0x5F, 0xEE, 0x70, 0x59},
	{0xF3, 0xD3, 0x7B, 0x50, 0x03, 0xBF, 0x66, 0xB3, 0x87, 0xD2, 0xD2, 0x98, 0x9F, 0x0C, 0x01, 0x27},
	{0xA8, 0xD1, 0x44, 0xF9, 0x38, 0x0F, 0xDD, 0x0D, 0x24, 0xF4, 0xCD, 0x62, 0x19, 0x95, 0x54, 0x6F},
	{0xD5, 0x17, 0xAD, 0x00, 0xEC, 0x29, 0x2E, 0x43, 0x9C, 0x4D, 0x96, 0xB3, 0x81, 0x3F, 0xD3, 0xDC},
	{0x23, 0xF5, 0xCB, 0xC6, 0x7B, 0x71, 0x53, 0x3F, 0x5C, 0xD3, 0x0F, 0x1F, 0x71, 0x83, 0x11, 0xB7},
	{0x67, 0x3E, 0x09, 0xC3, 0xFC, 0xC3, 0x69, 0x52, 0xAC, 0x1A, 0x9F, 0xF5, 0xCA, 0xDD, 0xFE, 0xFF},
	{0x4C, 0xF6, 0x07, 0xD1, 0xFA, 0x6E, 0xA3, 0x4F, 0x93, 0x39, 0x85, 0x93, 0x5A, 0xF6, 0x84, 0xCD},
	{0x17, 0x89, 0x41, 0x2F, 0xD4, 0xDC, 0x92, 0x65, 0x29, 0xC2, 0x4F, 0x68, 0x65, 0x60, 0xD7, 0x80},
	{0xF0, 0x3C, 0x4A, 0x41, 0xEB, 0xC1, 0xA4, 0x6F, 0x27, 0x52, 0x9D, 0xFD, 0x98, 0x36, 0xDE, 0x7B},
	{0xFA, 0xCC, 0xEB, 0x2C, 0x25, 0x65, 0xDD, 0x6E, 0x22, 0x4D, 0xD9, 0x08, 0x5A, 0x33, 0x04, 0x86},
	{0xBB, 0xCF, 0xA2, 0x1C, 0x1C, 0xA0, 0xA1, 0x38, 0xD2, 0xA2, 0x7F, 0xCF, 0x2E, 0x15, 0x45, 0xBE},
	{0x43, 0xD3, 0x48, 0x89, 0x9C, 0xD8, 0x39, 0x5C, 0x26, 0x80, 0x62, 0xE7, 0xDA, 0xDD, 0x8F, 0xE4},
	{0xD8, 0xE6, 0x35, 0xBD, 0x03, 0x21, 0x58, 0x27, 0x21, 0xA0, 0xD0, 0xDC, 0x49, 0x10, 0x01, 0x36},
	{0x67, 0xE5, 0x65, 0x30, 0xDA, 0x8D, 0x49, 0xB3, 0x4E, 0x42, 0x2E, 0xC6, 0xF0, 0x71, 0xF1, 0xAF},
	{0xA9, 0xCB, 0x6D, 0x33, 0xF3, 0x30, 0x91, 0xCF, 0x40, 0x42, 0xD0, 0x73, 0xCD, 0x58, 0x7D, 0x5D},
	{0x15, 0x58, 0xC7, 0x3F, 0xDF, 0xB8, 0xF2, 0x78, 0x4D, 0x79, 0x1A, 0xF9, 0x2D, 0x55, 0x6C, 0x2F},
	{0xF2, 0x01, 0x71, 0xB9, 0x29, 0xE0, 0x90, 0x84, 0xAC, 0x75, 0xB1, 0x95, 0xF4, 0x5A, 0xDD, 0x10},
	{0xFC, 0x1E, 0xDB, 0xE5, 0x34, 0xE6, 0x15, 0x62, 0x19, 0x7F, 0x92, 0x6C, 0x09, 0x52, 0xB1, 0xAE},
	{0x8D, 0x67, 0x88, 0xC6, 0x29, 0x3F, 0xB0, 0x7B, 0x23, 0x60, 0x32, 0xD2, 0x2C, 0x98, 0x32, 0x66},
	{0x97, 0x8B, 0xC1, 0xE2, 0x82, 0x4E, 0x86, 0x1A, 0xED, 0x0F, 0xBD, 0xD8, 0x85, 0xCF, 0x95, 0x20},
	{0xDB, 0x00, 0x10, 0xE5, 0xB7, 0xE9, 0x60, 0x6D, 0x3E, 0x72, 0xBA, 0x32, 0xC8, 0x43, 0xED, 0xB6},
	{0xF1, 0xDB, 0x06, 0x4C, 0x23, 0x88, 0xF5, 0xB7, 0xBC, 0x5F, 0x8A, 0x51, 0x6A, 0x8B, 0x85, 0x76},
	{0x6A, 0x6D, 0xFE, 0xBC, 0x7A, 0xD2, 0x6E, 0x30, 0xCF, 0xFC, 0x74, 0x01, 0x25, 0x86, 0x00, 0xF8},
	{0xA6, 0xA6, 0xE1, 0x57, 0xF2, 0xB4, 0x9A, 0xB2, 0x0A, 0x7B, 0x2E, 0x24, 0x5C, 0xC5, 0xAF, 0x00},
	{0xD8, 0x86, 0x95, 0x02, 0xB3, 0xE5, 0x06, 0x94, 0x52, 0x7B, 0xC4, 0x60, 0x27, 0x38, 0xDC, 0x69},
	{0x15, 0xE2, 0x85, 0x0C, 0x49, 0x65, 0xBF, 0x78, 0xF7, 0xA0, 0xDE, 0x8E, 0x07, 0x94, 0x17, 0x18},
	{0x32, 0x5B, 0x67, 0xD8, 0x74, 0xA0, 0x24, 0x21, 0x6D, 0xE2, 0x89, 0x69, 0x81, 0x9B, 0x30, 0x6D},
	{0x0F, 0x91, 0xF9, 0x51, 0xCA, 0x4A, 0xCF, 0x6E, 0xC2, 0x74, 0xF7, 0xA9, 0xEF, 0x3C, 0x9A, 0xD3},
	{0xFD, 0xB9, 0x85, 0x4F, 0x7C, 0xEA, 0x8B, 0xCB, 0x1C, 0x62, 0x65, 0x14, 0x87, 0x72, 0x74, 0x0F},
	{0x39, 0xBA, 0x18, 0xA7, 0xB8, 0xF8, 0xC5, 0xF9, 0x92, 0xB9, 0xF1, 0x64, 0x0A, 0xAB, 0x6B, 0x38},
	{0xF3, 0x2A, 0xDF, 0x3D, 0x97, 0x7D, 0x82, 0xEF, 0x1E, 0x27, 0xD4, 0xE6, 0xDA, 0xE1, 0xE5, 0x41},
	{0xFA, 0x3D, 0x7E, 0x21, 0xFE, 0xA9, 0xA0, 0x01, 0x20, 0xBF, 0x1A, 0xBE, 0x55, 0x21, 0xE4, 0x32},
	{0x08, 0x0B, 0xEC, 0x8B, 0x80, 0xEE, 0xF8, 0x1E, 0x20, 0x8E, 0xAB, 0x46, 0xD7, 0x66, 0x7A, 0xA6},
	{0xFA, 0x5F, 0xE5, 0xF2, 0xB2, 0x70, 0xCA, 0x4E, 0x81, 0xD3, 0x61, 0x89, 0x51, 0xD8, 0x05, 0xB0},
	{0xA8, 0x8E, 0xAD, 0xCC, 0x17, 0x49, 0xE8, 0x2E, 0x95, 0x04, 0x2F, 0x1F, 0x88, 0xA3, 0xF5, 0x71},
	{0xEC, 0xF9, 0xFC, 0x4D, 0xD8, 0x10, 0xD4, 0x07, 0x4A, 0x24, 0x31, 0x79, 0xAF, 0x78, 0xC8, 0xF9},
	{0xFF, 0xF8, 0xA1, 0x92, 0xEB, 0x72, 0xEE, 0x42, 0x5F, 0x30, 0x76, 0x4E, 0x50, 0xEB, 0x82, 0x5D},
	{0x9C, 0x3C, 0x4F, 0x4B, 0x30, 0xDC, 0x30, 0x25, 0xBE, 0xCE, 0xF1, 0xCC, 0x8E, 0x97, 0xBB, 0x75},
	{0x1C, 0x03, 0x4F, 0x75, 0xAE, 0x76, 0xC1, 0xC5, 0xE5, 0x63, 0x31, 0x72, 0xE5, 0xF0, 0xA2, 0x58},
	{0xC2, 0xF1, 0x20, 0x39, 0x6C, 0x6D, 0xA0, 0x12, 0x2C, 0x63, 0xFC, 0x17, 0x57, 0xA0, 0x71, 0x80},
	{0x3F, 0x16, 0x29, 0xB7, 0xAC, 0x3A, 0x97, 0x7B, 0x53, 0x98, 0xBD, 0x3B, 0xB2, 0x21, 0x5C, 0x8F},
	{0x07, 0x8F, 0xA2, 0xCB, 0x66, 0x9B, 0x4E, 0x16, 0x69, 0x02, 0x8B, 0xB1, 0x6B, 0x86, 0x4E, 0x9A},
	{0x5D, 0x63, 0xCB, 0x5D, 0xDB, 0xDC, 0xD2, 0xDC, 0xF6, 0x9C, 0xCC, 0x06, 0x43, 0xF0, 0x6A, 0xC3},
	{0x8A, 0x45, 0x36, 0xD8, 0x69, 0x59, 0xBC, 0xD4, 0xD3, 0x6A, 0xE3, 0x17, 0x32, 0x27, 0xE5, 0xC3},
	{0x04, 0xE5, 0xD1, 0x37, 0x26, 0x28, 0xF6, 0xA1, 0x27, 0x0C, 0xA6, 0x8E, 0xC5, 0x10, 0x86, 0x44},
	{0xC8, 0xE0, 0x4E, 0x7D, 0xBD, 0x8D, 0xF5, 0x35, 0x47, 0xD7, 0xA3, 0x3F, 0x1C, 0x91, 0x25, 0x53},
	{0xA7, 0x8C, 0xB7, 0xA3, 0xEF, 0x2E, 0x83, 0xC6, 0x8B, 0xF5, 0xF7, 0x5A, 0x87, 0x71, 0xEA, 0xDE},
	{0x8B, 0x2C, 0xB9, 0x14, 0xB7, 0xEC, 0x49, 0xD7, 0x94, 0x63, 0x8D, 0x4A, 0x0A, 0x8E, 0x09, 0x4A},
	{0x24, 0x62, 0xBC, 0x45, 0x43, 0x03, 0x91, 0x15, 0x0B, 0xF0, 0x65, 0xDC, 0xC7, 0x46, 0x96, 0x52},
	{0x00, 0x47, 0x05, 0x64, 0x7F, 0x4C, 0x42, 0xA9, 0x80, 0x42, 0x65, 0xC2, 0x58, 0x9E, 0xFD, 0x0D},
	{0xAC, 0xF3, 0x4B, 0xF8, 0xA0, 0x7D, 0xEA, 0xD9, 0x54, 0x44, 0x66, 0xE5, 0x04, 0xD5, 0xCD, 0xBF},
	{0xDE, 0x23, 0x4A, 0x27, 0x56, 0xA0, 0xB9, 0x79, 0x6E, 0x11, 0x4C, 0xC1, 0xF6, 0x44, 0x93, 0x27},
	{0x22, 0xA2, 0xF2, 0x80, 0x79, 0xDD, 0x7A, 0x95, 0xAD, 0xA7, 0xFE, 0x24, 0x03, 0xFF, 0x2E, 0x84},
	{0x6B, 0x9F, 0x15, 0xCC, 0x8C, 0x70, 0xDC, 0x35, 0x23, 0x3F, 0xD7, 0x6C, 0x10, 0x8C, 0x8E, 0x64},
	{0x13, 0xCA, 0xE5, 0xE5, 0x41, 0xD0, 0x08, 0xE4, 0xFD, 0x41, 0xB9, 0xCB, 0x8F, 0x5E, 0x32, 0x8F},
	{0xD3, 0x25, 0x32, 0x2D, 0x1E, 0xD6, 0xD0, 0x99, 0x23, 0xA5, 0x94, 0x98, 0x93, 0x43, 0x9D, 0x68},
	{0xE9, 0x4D, 0x73, 0x9D, 0x31, 0xF1, 0xF9, 0xB8, 0x9A, 0x50, 0x4C, 0x34, 0x3C, 0x4C, 0x95, 0x4C},
	{0xAE, 0xBB, 0xBA, 0x3D, 0x65, 0xB0, 0x74, 0x9A, 0x8A, 0x1B, 0x4C, 0xF4, 0x1B, 0x04, 0xD5, 0x5E},
	{0x8D, 0xAD, 0xEA, 0x39, 0x5C, 0x30, 0xBD, 0x70, 0x82, 0x6E, 0x1F, 0x9D, 0x12, 0x66, 0x37, 0xA1},
	{0x20, 0x73, 0x02, 0x9D, 0x54, 0x26, 0xD5, 0x19, 0xF2, 0x33, 0xAF, 0x75, 0x31, 0xDF, 0x2B, 0x47},
	{0x43, 0xD4, 0x38, 0xC8, 0xF3, 0x45, 0x43, 0x4F, 0x5C, 0xF7, 0xC5, 0xCF, 0x8E, 0xCD, 0xAC, 0x56},
	{0x7D, 0x27, 0xD5, 0x22, 0x85, 0x91, 0x98, 0xFD, 0x72, 0x2B, 0xDF, 0x45, 0x3E, 0xB8, 0x6A, 0x5D},
	{0x91, 0x91, 0x36, 0x18, 0x32, 0xD2, 0xC7, 0x3C, 0x0D, 0xD9, 0xD9, 0x10, 0xB7, 0xD3, 0x76, 0x0A},
	{0x87, 0x61, 0xB2, 0xCE, 0x41, 0x0E, 0x19, 0x4F, 0xF1, 0x64, 0x01, 0x1D, 0xAA, 0x6E, 0x5C, 0xFE},
	{0xB4, 0x31, 0x81, 0xFF, 0x7A, 0x3F, 0xE9, 0xD6, 0x1A, 0x05, 0x01, 0xA7, 0x29, 0xFF, 0x38, 0x47},
	{0x60, 0xB1, 0x29, 0x5D, 0x5B, 0x46, 0xE5, 0x28, 0x6E, 0x54, 0xC3, 0x46, 0xA3, 0xFE, 0xE1, 0x49},
	{0xE6, 0x48, 0x2D, 0xF1, 0x92, 0x39, 0x39, 0xB9, 0x3E, 0x55, 0xF2, 0xA5, 0xE0, 0x32, 0xAA, 0x6E},
	{0x0D, 0x9A, 0xD7, 0xDA, 0x54, 0x71, 0x7A, 0x53, 0xE0, 0xD7, 0xA3, 0xB1, 0xE6, 0xB8, 0x44, 0x98},
	{0x67, 0x22, 0xA5, 0x1F, 0x67, 0x6E, 0x36, 0xF9, 0x2D, 0x1F, 0x8D, 0xF4, 0xD7, 0x2A, 0x05, 0x2A},
	{0x85, 0xE5, 0x29, 0x1F, 0x7A, 0x74, 0x19, 0xE0, 0xB9, 0x41, 0x7D, 0x6F, 0xAC, 0xC8, 0xF4, 0xBB},
	{0xFA, 0x99, 0x6C, 0xA3, 0xDA, 0x3E, 0x49, 0xB7, 0xEE, 0x52, 0x6E, 0x5E, 0x78, 0x1B, 0x76, 0x0C},
	{0x9B, 0xFF, 0x19, 0x18, 0x0D, 0x9D, 0x54, 0xC4, 0x63, 0x9E, 0xD0, 0x5B, 0xF5, 0x0D, 0x13, 0x40},
	{0xC3, 0xF7, 0xFC, 0x1F, 0xA3, 0x93, 0x85, 0x36, 0xCE, 0x26, 0x8C, 0x9C, 0xD6, 0xEC, 0x3A, 0x0A},
	{0x0F, 0x92, 0xC6, 0xB3, 0xD0, 0x7A, 0x58, 0xA5, 0xB7, 0xB2, 0x96, 0x7B, 0x28, 0xF2, 0xE9, 0x7F},
	{0xF5, 0x9B, 0xEF, 0x7C, 0xF1, 0x99, 0x2F, 0x0E, 0x6C, 0x2C, 0xAA, 0xD1, 0x73, 0xFF, 0x1F, 0xA6},
	{0x8E, 0x5D, 0x53, 0x26, 0x37, 0x01, 0x50, 0x57, 0x02, 0x79, 0x94, 0x95, 0x99, 0x78, 0x37, 0x4A},
	{0xAA, 0xD9, 0xD6, 0x6A, 0xE5, 0xF4, 0x15, 0xF8, 0xE8, 0xA3, 0x51, 0x60, 0xD0, 0x56, 0x25, 0x18},
	{0xF4, 0xD2, 0x59, 0xC0, 0x8F, 0x69, 0xF8, 0x43, 0xE0, 0x7B, 0x15, 0x53, 0x84, 0xCB, 0x96, 0x78},
	{0x29, 0xFF, 0x56, 0xDE, 0x5F, 0xE0, 0x98, 0xD9, 0xFE, 0x6F, 0xF0, 0x64, 0xFE, 0x11, 0xC1, 0xAC},
	{0x9F, 0x0C, 0x7F, 0xDC, 0x2D, 0xDB, 0xCB, 0x33, 0xD9, 0x58, 0xE7, 0xEC, 0xC9, 0x37, 0xE0, 0xF6},
	{0xF6, 0x04, 0xC4, 0x4D, 0x65, 0xAA, 0x0D, 0x85, 0x7E, 0x5A, 0xAC, 0x70, 0x86, 0x89, 0x3F, 0x59},
	{0x82, 0x52, 0x0F, 0xFB, 0xD1, 0x31, 0xD6, 0xA4, 0x2D, 0x29, 0x52, 0xE1, 0xC9, 0x95, 0x21, 0xBE}
};


unsigned char sample_kirk1_ecdsa[320] =
{
    0x10, 0x6D, 0x65, 0x5D, 0xF7, 0xB4, 0xC0, 0x41, 0x5D, 0xAB, 0x17, 0x3C, 0xAE, 0x6D, 0xD8, 0xF2, 
    0x66, 0x4F, 0xE1, 0xF2, 0xE9, 0xD6, 0x63, 0x36, 0xF7, 0x33, 0x0B, 0xCA, 0xB9, 0x55, 0x6D, 0xB6, 
    0xEB, 0xE8, 0x05, 0xDC, 0xF5, 0x57, 0xE2, 0xF8, 0xC8, 0x1F, 0xD9, 0x5C, 0xB6, 0x0B, 0x60, 0x1B, 
    0xF0, 0x86, 0x2D, 0xDB, 0x1F, 0xCB, 0x4E, 0xAF, 0xCD, 0xE3, 0x88, 0xA6, 0x3C, 0x1D, 0x57, 0xDC, 
    0x5E, 0x94, 0xEE, 0xAC, 0x2E, 0x6C, 0x9F, 0x2E, 0x81, 0xC7, 0x1C, 0x58, 0x3A, 0xF1, 0x81, 0x74, 
    0xCB, 0xB5, 0xC6, 0x10, 0x4B, 0x09, 0xD1, 0x79, 0x08, 0xB8, 0xB7, 0x44, 0x92, 0x08, 0x5C, 0x23, 
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x26, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x7E, 0x50, 0x53, 0x50, 0x07, 0x10, 0x01, 0x00, 0x08, 0x01, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 
    0x65, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xEE, 0x92, 0x8E, 0xAE, 0x50, 0xCA, 0x4E, 0x01, 0x19, 0x9C, 0x1C, 0xA6, 0x90, 0xB8, 0x61, 0x70, 
    0x0A, 0x95, 0x54, 0x57, 0x8F, 0xC5, 0xEF, 0x2C, 0xA2, 0x49, 0xA6, 0xB5, 0x08, 0xDF, 0x8C, 0x78, 
    0x2E, 0x38, 0x94, 0x28, 0x9B, 0xE1, 0x1F, 0xC4, 0xCE, 0x61, 0xDB, 0x32, 0x0B, 0x5E, 0x05, 0xF0, 
} ;


void testkirk7() {
	unsigned char testdata[0x10+0x14];
	int i;
	//Use a 00 test vector
	for(i=0;i<0x80;i++) {
		memset(testdata,0,0x10+0x14);
		testdata[0] = 5;
		testdata[0xC] = i;
		testdata[0x10] = 0x10;
		sceUtilsBufferCopyWithRange(testdata,0x24,testdata,0x10,0x7);
		if(memcmp(testdata, kirk7tests[i], 0x10) == 0 ){
			printf("KIRK7 Key 0x%x test passed\n",i);
		} else {
			printf("WARNING! KIRK 7 Key 0x%x failed!\n",i);
		
		}
	}
		
}
int main(int argc, char  *argv[])
{
	int res;
	u8 rnd[0x14];
	u8 rndbig[0x80];
	u8 keypair[0x3C];
	u8 newpoint[0x28];
	u8 mult_test[0x3c];
	u8 testsig[0x1000];
	u8 correct_sha1[0x14] = { 0xDE, 0x8A, 0x84, 0x7B, 0xFF, 0x8C, 0x34, 0x3D, 0x69,0xB8,
				0x53,0xA2,0x15, 0xE6, 0xEE, 0x77, 0x5E,0xF2, 0xEF, 0x96 };
	u8 test17_fullsig[0x64];
	KIRK_CMD16_BUFFER ecdsa_sign;
	ECDSA_SIG signature;
	KIRK_CMD17_BUFFER ecdsa_test;
	// My private RIF
	
	// From NPEH90049 Demo NPUMDIMG Header SHA1 of 0xD8 bytes
	u8 test17_hash[0x14]= {
		0x2C, 0x39, 0xC1, 0x46, 0x22, 0xD5, 0x55, 0x02,
		0x3A, 0x03, 0xB1, 0x2D, 0x17, 0x00, 0x00, 0x36,
		0x8C, 0x28, 0xBD, 0x50
	};

	// From NPEH90049 Demo NPUMDIMG Header at offset 0xD8
	u8 test17_sig[0x28] = {
		0x4B, 0xBC, 0xBC, 0xB5, 0x01, 0x70, 0xCD, 0x23,
		0x20, 0x6F, 0x51, 0x9A, 0xBE, 0xD7, 0xD8, 0xCC,
		0x04, 0x56, 0x4C, 0x9E, 0x17, 0xE0, 0x1E, 0x2E,
		0x63, 0x12, 0x38, 0x60, 0x58, 0x0B, 0x21, 0x84,
		0x9F, 0x52, 0x13, 0xF1, 0x31, 0x2C, 0x6A, 0xBC
	};

	// Public NPUMDIMG Key from np9660.prx
	u8 rif_public[0x28] = {
		0x01, 0x21, 0xEA, 0x6E, 0xCD, 0xB2, 0x3A, 0x3E,
		0x23, 0x75, 0x67, 0x1C, 0x53, 0x62, 0xE8, 0xE2,
		0x8B, 0x1E, 0x78, 0x3B, 0x1A, 0x27, 0x32, 0x15,
		0x8B, 0x8C, 0xED, 0x98, 0x46, 0x6C, 0x18, 0xA3,
		0xAC, 0x3B, 0x11, 0x06, 0xAF, 0xB4, 0xEC, 0x3B

	};


	printf("Starting Test Harness...\n");

	printf("Generating a kirk 1 sig...\n");
	memset(testsig,0,0x1000);

	strcpy((char*)testsig,"This is a test.");
	
	
	// In the real world, you should use a secure way of generated a nice chunk of random data.
	// There are good OS-specific ways available on each platform normally. Use those!
	//
	// The two values for the fuse id can be grabbed from your personal device
	// by reading BC100090 for the first value and BC100094 for the second value.
	// Process them as u32 so the endian order stays correct.
	kirk_init2((u8*)"This is my test seed",20,0x12312355 , 0x4444 );
	//kirk_init();
	testkirk7();
	memset(rnd,0,0x14);
	memset(rndbig,0,0x80);
	sceUtilsBufferCopyWithRange(testsig,0x1000,testsig,0x1000,0);
	hex_dump("Signed", testsig,0x100);
	rndbig[0]= 0x20;
	hex_dump("KIRK 11 buff", rndbig,0x24);
	sceUtilsBufferCopyWithRange(rnd,0x14,rndbig,0x24,0xB);
	hex_dump("SHA1 Result", rnd,0x14);
	if(memcmp(rnd,correct_sha1,0x14) == 0 ) {
		printf("SHA1 of 0x20 00s is correct!\n");
	} else {
		printf("SHA1 failed!\n");
		return -1;
	}

	// Test Random Generator
	printf("\nGenerating 2 random numbers...\n");
	sceUtilsBufferCopyWithRange(rndbig,0x77,0,0,0xE);
	hex_dump("Big Random Number", rndbig, 0x77);
		
	sceUtilsBufferCopyWithRange(rnd,0x14,0,0,0xE);
	hex_dump("Random Number", rnd, 0x14);
	
	// Test Key Pair Generator
	printf("\nGenerating a new ECDSA keypair...\n");
	sceUtilsBufferCopyWithRange(keypair,0x3C,0,0,0xC);
	hex_dump("Private Key", keypair, 0x14);
	hex_dump("Public Key", keypair+0x14, 0x28);
	
	// Test Point Multiplication
	printf("\nMultiplying the Public Key by the Random Number...\n");
	memcpy(mult_test,rnd,0x14);
	memcpy(mult_test+0x14,keypair+0x14,0x28);
	sceUtilsBufferCopyWithRange(newpoint,0x28,mult_test,0x3C,0xD);
	hex_dump("New point", newpoint, 0x28);
	
	printf("Testing a known valid ECDSA signature...\n");
	memcpy(test17_fullsig, rif_public,0x28);
	memcpy(test17_fullsig+0x28, test17_hash,0x14);
	memcpy(test17_fullsig+0x3C, test17_sig,0x28);
	res=sceUtilsBufferCopyWithRange(0,0,test17_fullsig,0x64,0x11);
	printf("Signature check returned %d\n", res);
	if(res) {
		printf("Signature FAIL!\n");
	} else {
		printf("Signature VALID!\n");
	}
	printf("\nTesting ECDSA signing with ECDSA key pair...\n");
	encrypt_kirk16_private(ecdsa_sign.enc_private,keypair);
	hex_dump("Encrypted Private", ecdsa_sign.enc_private, 0x20);
	//Test with a message hash of all 00s
	memset(ecdsa_sign.message_hash,0,0x14);
	sceUtilsBufferCopyWithRange(signature.r,0x28,ecdsa_sign.enc_private,0x34,0x10);
	
	printf("\nChecking signature and Message hash...\n");
	hex_dump("Signature R", signature.r, 0x14);
	hex_dump("Signature S", signature.s, 0x14);
	hex_dump("Message hash", ecdsa_sign.message_hash,0x14);
	
	printf("\nUsing Public key...\n");
	hex_dump("Public.x", keypair+0x14,0x14);
	hex_dump("Public.y", keypair+0x28,0x14);
	// Build ecdsa verify message block
	memcpy(ecdsa_test.public_key.x,keypair+0x14,0x14);
	memcpy(ecdsa_test.public_key.y,keypair+0x28,0x14);
	memcpy(ecdsa_test.message_hash,ecdsa_sign.message_hash,0x14);
	memcpy(ecdsa_test.signature.r,signature.r,0x14);
	memcpy(ecdsa_test.signature.s,signature.s,0x14);
	
	res=sceUtilsBufferCopyWithRange(0,0,(u8*)ecdsa_test.public_key.x,0x64,0x11);
	printf("Signature check returned %d\n", res);
	if(res) {
		printf("Signature FAIL!\n");
	} else {
		printf("Signature VALID!\n");
	}	
	printf("\nTesting Kirk1 ECDSA Verification and Decryption...\n");
	res=sceUtilsBufferCopyWithRange(sample_kirk1_ecdsa,320,(u8*)sample_kirk1_ecdsa,320,0x1);
	printf("Signature check returned %d\n", res);
	if(res) {
		printf("Signature FAIL!\n");
	} else {
		printf("Signature VALID!\n");
	}
	printf("%s\n",sample_kirk1_ecdsa);
	return 0;
}
