# C++ Wrapper fo FreeType (wft-lib)

![sample](sample.png "Sample OpenGL window")

A very simple C++ wrapper for the Freetype library with support UFT8 strings.

# Using
**First**: add two rows in the you CMakeLists.txt for link wrapper as library:

```bash
add_subdirectory( "libs/wft" "wft" EXCLUDE_FROM_ALL )
...
target_link_libraries( application_name "${MY_APP_LIBRARIES}" wft)
```

**Second**: include header file and append three rows in the you code:

```cpp
#include "wft/wft.hpp"
...

wft::font Font {"font/LiberationSans-Regular.ttf"};
Font.set_size(0, 15);
auto Bitmap = Font.make_bitmap_text("Hello, World!");
```

**It's all!!**

Detailed information you can see in the example file "wft/sample/main.cpp".
