//
// Created by vologhat on 10/19/24.
//

#ifndef PYGMALION_SYS_PATHS_H
#define PYGMALION_SYS_PATHS_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__arm__) || defined(__i386__)
#define LIB_DIR "lib"
#elif defined(__aarch64__) || defined(__x86_64__)
#define LIB_DIR "lib64"
#else
#error "Arch unknown, please port me"
#endif

#define SYSTEM_LIB_PATH         "/system/" LIB_DIR "/"
#define SYSTEM_VENDOR_LIB_PATH  "/system/vendor/" LIB_DIR "/"
#define VENDOR_LIB_PATH         "/vendor/" LIB_DIR "/"

#if defined(__cplusplus)
}
#endif

#endif //PYGMALION_SYS_PATHS_H