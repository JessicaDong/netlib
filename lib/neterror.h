#include <stdarg.h>
#include"netlib.h"
#include"errorname.h"

static void
terminate(Boolean Exitcode){

    char *s; 

    s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
        abort();
    else if (Exitcode)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}


static void
outputError(Boolean useErr, int err, Boolean flushStdout,
        const char *format, va_list ap){

#define BUFFER_SIZE 500
    char buf[BUFFER_SIZE], userMsg[BUFFER_SIZE], errText[BUFFER_SIZE];

    vsnprintf(userMsg, BUFFER_SIZE, format, ap);

    if (useErr)
        snprintf(errText, BUFFER_SIZE, " [%s %s]",
                (err > 0 && err <= MAX_ENAME) ?
                ename[err] : "?UNKNOWN?", strerror(err));
    else
        snprintf(errText, BUFFER_SIZE, ":");

    snprintf(buf, BUFFER_SIZE, "ERROR%s %s\n", errText, userMsg);

    if (flushStdout)
        fflush(stdout);       /* Flush any pending stdout */
    fputs(buf, stderr);
    fflush(stderr);           /* In case stderr is not line-buffered */
}

void
errMsg(const char *format, ...){

    va_list argList;
    int savedErrno;

    savedErrno = errno;       /* In case we change it here */

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void
errExit(const char *format, ...){

    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}