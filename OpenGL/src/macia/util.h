#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>

extern "C" {
#include <jpeglib.h>
}

#include "structure.h"

using namespace std;


const string kImagePath = "/home/legend/myfile/GLmacia/resources/img";
const string kShaderPath = "/home/legend/myfile/GLmacia/resources/shaders";

static bool ReadShaderFile(char* content, char* file_path) {
  FILE* in_file = fopen(file_path, "r");
  if (!in_file)
    return false;
  fseek(in_file, 0, SEEK_END);
  long file_length = ftell(in_file);
  rewind(in_file);
  if (file_length <= 0)
    return false;
  content = static_cast<char*>(malloc(file_length + 1));
  fread(content, file_length, 1, in_file);
  fclose(in_file);
  content[file_length] = '\0';
  return true;
}

static bool ReadShaderFile(string& content, string file_path) {
  content.clear();
  ifstream in_file(file_path.c_str(), ifstream::in);
  if (!in_file.is_open())
    return false;
  while (!in_file.eof()) {
    string temp_line;
    getline(in_file, temp_line);      
    content.append(temp_line);
  }
  in_file.close();
  return true;
}

static bool ReadJPEGFile(ImageData* image, string file_path) {
  struct jpeg_decompress_struct info;
  struct jpeg_error_mgr error;
  JSAMPARRAY buffer;

  FILE* in_file = fopen(file_path.c_str(), "rb");
  if (!in_file) {
    printf("Error opening jpeg file %s\n!", file_path.c_str());
    return false;
  }
  info.err = jpeg_std_error(&error);

  jpeg_create_decompress(&info);
  jpeg_stdio_src(&info, in_file);
  jpeg_read_header(&info, TRUE);
  jpeg_start_decompress(&info);

  int row_stride = info.output_width * info.output_components;
  buffer = (*info.mem->alloc_sarray)((j_common_ptr)&info, JPOOL_IMAGE, row_stride, 1);
  image->width = info.output_width;
  image->height = info.output_height;
  image->pixels = new unsigned char [row_stride * info.output_height];
  long counter = 0;
  while (info.output_scanline < info.output_height) {
    jpeg_read_scanlines(&info, buffer, 1);
    memcpy(image->pixels + counter, buffer[0], row_stride);
    counter += row_stride;
  }
  jpeg_finish_decompress(&info);
  jpeg_destroy_decompress(&info);
  fclose(in_file);
  return true;
}

#endif
