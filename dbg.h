/* Zed's awesome debug macros from:
 * c.learncodethehardway.org/book/ex20.html
 */

#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

/* If NODEBUG is defined, either with "#define NODEBUG" or with
 * a "-DNODEBUG" flag passed to gcc/cc, then the debug() macro will
 * be a no-op (muting all debug output)
 *
 * Otherwise, debug prints a message to stderr with the current filename
 * and line number.
 */
#ifndef NODEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/* checks the global errno var and returns a string version for printing */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/* prints a message to stderr with an ERROR prefix, filename, line
 * number, and string error code
 */
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

/* prints a message to stderr with a WARN prefix, current filename,
 * current line number, and string error code
 */
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

/* Prints to stderr with an INFO prefix and the current filename and
 * line number, but does not check for and print and error code
 */
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/* Use like the built-in assert, but must provide an "error:" label in the
 * scope where you use it.  If condition A is false, will print the given
 * message M with log_err, reset errno, and jump to the defined error label.
 */
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

/* Use in places that should be unreachable; this function will always print
 * and error message and jump to the error label (there is no condition)
 */
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

/* Shortcut version of check() for doing check(ptr != NULL)
 * after attempted heap memory allocations.
 */
#define check_mem(A) check((A), "Out of memory.")

/* Version of check that logs using debug(), not log_err(), so it can
 * be silenced with the NODEBUG flag.  It will still reset errno and
 * jump to an error label regardless.
 */
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
