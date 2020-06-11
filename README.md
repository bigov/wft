# C++ Wrapper fo FreeType (wft-lib)
A very simple C++ wrapper for the Freetype library

# Using
**First**: add two rows in the you CMakeLists.txt for link wrapper as library:

```bash
add_subdirectory( "../src" "wft" EXCLUDE_FROM_ALL )
...
target_link_libraries( application_name "${MY_APP_LIBRARIES}" wft)
```

**Second**: include header file and append three rows in the you code:

```cpp
#include "wft/src/wft.hpp"
...

wft::font Font {"font/LiberationSans-Regular.ttf"};
Font.set_size(0, 15);
auto Bitmap = Font.make_bitmap_text("Привет тебе, WORLD!");
```

**It's all!!**

For more information on using wrappers, see the example file "wft/sample/main.cpp".
