/*
 * OpenGL sample application demonstrating the use of a wrapper
 *
 */
#include "../wft.hpp"

// The definition of this function is located in the file "win.cpp"
void opengl_window_show(const unsigned char* texture_data, int win_width, int win_height);

///
/// \brief main
/// \return
///
int main(int, char**)
{
  int window_width = 400;
  int window_height = 200;
  int bytes_per_pixel = 4;    // pixel colors: RGBA

  wft::font Font {"../sample/LiberationSans-Regular.ttf"};
  Font.set_size(0, 15);

  auto Bitmap = Font.make_bitmap_text("Привет тебе, WORLD!");
  if(window_width < Bitmap.width) window_width = Bitmap.width + 4;

  std::vector<unsigned char> texture(static_cast<unsigned>(window_width * window_height * bytes_per_pixel), 0xFF);

  // Calc in the center of the texture
  unsigned int dst_start = static_cast<unsigned>(bytes_per_pixel * (window_width/2 - Bitmap.width/2)
      + bytes_per_pixel * window_width * (window_height/2 - Bitmap.height));

  unsigned int src_start = 0;
  for(int i = 0; i < Bitmap.width * Bitmap.height; ++i)
  {
    int row_n = Bitmap.width;
    unsigned int dst = dst_start;
    unsigned int src = src_start;
    while(row_n > 0)
    {
      uint8_t c = Bitmap.Bits[src];
      texture[dst + 0] = 0x20; // Red
      texture[dst + 1] = 0x20; // Green
      texture[dst + 2] = 0x20; // Blue
      texture[dst + 3] = c;    // Alpha
      dst += 4;
      src += 1;
      row_n -= 1;
      i += 1;
    }
    src_start += static_cast<unsigned>(Bitmap.width);                   // next row source bitmap
    dst_start += static_cast<unsigned>(window_width * bytes_per_pixel); // next texture row
  }

  opengl_window_show(texture.data(), window_width, window_height);
  exit(EXIT_SUCCESS);
}

