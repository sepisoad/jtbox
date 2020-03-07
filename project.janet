( declare-project
  :name "jtbox"
  :author "Sepehr Aryani <sepehr.aryani@gmail.com>")

(def os (os/which))

(def cflags
  (case os
    :macos '[]
    #default
    '["-std=gnu99" "-Wall" "-Wextra" "-O3" "-D_XOPEN_SOURCE"]))

# (def lflags
#   (case os
#     :windows '[]
#     :macos '["-lpthread" "-framework" "Cocoa" "-framework" "CoreVideo" "-framework" "IOKit" "-framework" "OpenGL"]
#     :linux '["-lpthread" "-lX11"]
#     #default
#     '["-lpthread"]))

(declare-native
  :name "termbox"

  :cflags cflags

  # :defines {"PLATFORM_DESKTOP" true}

  :source [# wrapper source
           "src/main.c"

           # raylib sources
           "termbox/src/termbox.c"
           "termbox/src/utf8.c"
           ]

  # :headers ["termbox/src/termbox.h"
  #           "termbox/src/bytebuffer.inl"
  #           "termbox/src/input.inl"
  #           "termbox/src/term.inl"]

  # :lflags lflags
  )

# `jpm run repl` to run a repl with access to jaylib
# (phony "repl" ["build"]
#        (os/execute ["janet" "-l" "build/jaylib"] :p))