#include "s21_string.h"
#include "s21_strerror.h"
#include <stdio.h>

#include <string.h>

void* s21_memchr(const void *str, int c, s21_size_t n) {
  void* result = s21_NULL;
  if (n != 0) {
    const char *p = str;
    do {
      if (*p++ == (char)c) {
        result = ((void *)(p - 1));
        break;
      }
    } while (--n != 0);
  }
  return result;
}

int s21_memcmp(const void* s1, const void* s2, s21_size_t n) {
  const unsigned char *p1 = s1, *p2 = s2;
  int result = 0;
  while (n--)
    if (*p1 != *p2) {
      result = *p1 - *p2;
    } else {
      p1++;
      p2++;
    }
  return result;
}


void* s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char* d = dest;
  const char* s = src;
  while (n-- > 0) {
    *d++ = *s++;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char* d = dest;
  char* s = (char*)src;
  if (d < s) {
    while (n--) {
      *d++ = *s++;
      }
    } else {
        char* ends = s + (n - 1);
        char* endd = d + (n - 1);
          while (n--) {
            *endd-- = *ends--;
          }
        }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *p = (char *)str;
  for (s21_size_t i = 0; i != n; ++i) {
    p[i] = c;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *tmp = dest;
  while (*dest) {
    dest++;
  }
  while ((*dest++ = *src++) != '\0') {}
  return tmp;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i;
  for (i = 0 ; i < n && src[i] != '\0' ; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + i] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int is_null = 0;
  for (; *str != (char)c; ++str) {
    if (*str == '\0') {
      is_null = 1;
      break;
      }
  }
  char *result = s21_NULL;
  if (is_null == 0) {
    result = (char *)str;
  }
  return result;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 && *str1 == *str2) {
    ++str1;
    ++str2;
  }
  return (*str1 - *str2);
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int resultcmp = 0;
    for (s21_size_t i = 0; i < n; i++) {
      if (str1[i] > str2[i] || str2[i] > str1[i]) {
        resultcmp = str1[i] - str2[i];
        break;
      } else if (str1[i] == '\0' || str2[i] == '\0') {
          break;
        }
    }
  return resultcmp;
}

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
    dest[i] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t stringlen = s21_strnlen(src, n);
        if (stringlen != n) {
                s21_memset(dest+stringlen, '\0', n - stringlen);
        }
    return s21_memcpy(dest, src, stringlen);
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int i = 0;
  while (str1[i] != '\0') {
    if (s21_strchr(str2, str1[i]) != s21_NULL) {
      break;
    }
    i++;
  }
  s21_size_t lenght = i * sizeof(char);
  return lenght;
}

char *s21_strerror(int errnum) {
#ifdef __APPLE__
  char errlist[107][50] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full",
  };
#endif  // __APPLE__

#ifdef __linux__
  char errlist[134][50] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"
  };
#endif  // __linux__

  static char message[128];
  if ((errnum < 0) || (errnum > ERROR_N)) {
    #ifdef __linux__
    s21_sprintf(message, "Unknown error %d", errnum);
    #elif __APPLE__
    s21_sprintf(message, "Unknown error: %d", errnum);
    #endif
  } else {
    s21_sprintf(message, "%s", errlist[errnum]);
  }
  return message;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t size = 0;
  while (str[size]) {
    size++;
  }
  return size;
}

// This function used only in strncpy
s21_size_t s21_strnlen(const char *src, s21_size_t n) {
    s21_size_t i = 0;
        for (i = 0; i < n; i++) {
           if (src[i] == '\0')
              break;
        }
    return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  for (; *str1 != '\0'; ++str1) {
    if (s21_strchr(str2, *str1) != s21_NULL) {
      result = (char *) str1;
      break;
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  const char *result = s21_NULL;
  if (str != s21_NULL) {
    do {
      if (*str == (char)c) {
        result = str;
      }
    } while (*str++);
  }
  return(char*)result;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *symstr1;
  const char *symstr2;
  int count = 0;

  for (symstr1=str1; *symstr1 != '\0'; symstr1++) {
    for (symstr2=str2; *symstr2 != '\0'; symstr2++) {
      if (*symstr1 == *symstr2) {
        count++;
        break;
      }
    }
    if (*symstr1 != *symstr2) {
      break;
    }
  }
  return(count);
}

char *s21_strstr(const char *str1, const char *str2) {
  const char *symstr2;
  const char *p;
  const char *flag = s21_NULL;
  if (*str2 !='\0') {
    for (; *str1 != '\0'; str1++) {
      if (*str1 == *str2) {
        for (p = str1, symstr2 = str2; *symstr2 != '\0'; symstr2++, p++) {
          if (*p != *symstr2) {
            break;
            }
          }
        if (*symstr2 == '\0') {
          flag = str1;
          break;
        }
      }
    }
  } else {flag = str1;}
  return (char*)flag;
}


char *s21_strtok(char *str, const char *delim) {
    static char *copy_base;
    char *str1;
    static char *last;
    char *ch;
    char *tonull;
    int is_null = 0;

    if (str) {
      copy_base = str;
      str1 = copy_base;
    }
    if (!str && *last == '\0') {
      is_null = 1;
    }
    if (!str) {
      str1 = last;
    }

    while (*str1 != 0) {
        ch = str1;
        if (!s21_strchr(delim, *ch)) {
          copy_base = str1;
          break;
        }
        str1++;
    }

    while (*str1 != 0) {
        tonull = str1;
        if (s21_strchr(delim, *tonull)) {
                break;
        }
        str1++;
    }
        if (*str1 == '\0') {
            tonull = str1;
        }

    while (*str1 != 0) {
        ch = str1;
        if (!s21_strchr(delim, *ch)) {
            last = str1;
            break;
        }
        str1++;
    }
    if (*str1 == '\0') {
        last = str1;
    }
    *tonull = '\0';

    char *result = s21_NULL;
    if (is_null == 0) {
      result = copy_base;
    }
    return result;
}


int s21_isDigit(int character) {
    if (character >= 48 && character <= 57)
        return (1);
    else
        return (0);
}

char *s21_strdup(const char *s1) {
    char *s2;
    s21_size_t len;
    s21_size_t i;

    len = s21_strlen(s1);
    if (!(s2 = (char *)calloc(len + 1, sizeof(char)))) return (S21_NULL);
    i = 0;
    while (s1[i]) {
        s2[i] = s1[i];
        i += 1;
    }
    s2[i] = '\0';
    return (s2);
}

int helper_isSpec(char c, struct s_format *formatParams) {
    int i = 0;
    if (c == 'd' || c == 'i' || c == 'c' || c == 'f' || c == 's' || c == 'u' ||
        c == '%') {
        i = 1;
    }
    formatParams->spec = (c == 'u' ? 1 : 0);
    return i;
}

// Инициализатор структуры
void helper_initStruct(struct s_format *formatParams) {
    formatParams->isInt = 0;
    formatParams->flagPlus = 0;
    formatParams->flagMinus = 0;
    formatParams->flagSpace = 0;
    formatParams->width = 0;
    formatParams->widthMustBeWrittenByZero = 0;
    formatParams->widthZeroDetected = 0;
    formatParams->precision = 0;
    formatParams->precisionWillBeSpecified = 0;
    formatParams->length_h = 0;
    formatParams->length_l = 0;
    formatParams->isAsteriskWidth = 0;
    formatParams->isAsteriskFloatWidthDescription = 0;
    formatParams->precisionIsNull = 0;
    formatParams->precisionSetByZero = 0;
    formatParams->isLongDouble = 0;
    formatParams->spec = 0;
}

// Записывает символ в буффер
void helper_writeChar(const char **format, char **str,
                      struct s_format *formatParams, char c) {
    if (formatParams->flagMinus) {
        **str = c;
        (*str)++;
    }
    for (int i = 0; i < formatParams->width - 1; i++) {
        **str = ' ';
        (*str)++;
    }
    if (!formatParams->flagMinus) {
        **str = c;
        (*str)++;
    }
    (*format)++;
}

// Записывает знак процента в буффер
void helper_writePercent(const char **format, char **str) {
    **str = '%';
    (*str)++;
    (*format)++;
}

// Заполняет строку размером n терминаторами.
void helper_bZero(void *s, s21_size_t n) {
    s21_size_t i;

    i = 0;
    while (i < n) {
        ((char *)s)[i] = 0;
        i++;
    }
}

// Выделяет память для чего-либо
void *helper_memalloc(s21_size_t size) {
    void *some;

    some = calloc(size, 1);
    if (!some) return (S21_NULL);
    helper_bZero(some, size);
    return (some);
}

// Конвертирует интеджер в строку
char *helper_itoa(long int n) {
    long int tmpn;
    int len;
    int neg;
    char *str;

    tmpn = n;
    len = 2;
    neg = tmpn < 0 ? 1 : 0;

    while (tmpn /= 10) len++;
    if (!(str = helper_memalloc(BUFFSIZE))) return (S21_NULL);
    len += neg;
    str[--len] = '\0';
    if (neg) n *= -1;
    while (len--) {
        str[len] = n % 10 + '0';
        n = n / 10;
    }
    if (neg) str[0] = '-';
    return (str);
}

char *helper_utoa(unsigned long long int n) {
    unsigned long long int tmpn;
    int len;
    char *str;

    tmpn = n;
    len = 2;

    while (tmpn /= 10) len++;
    if (!(str = helper_memalloc(BUFFSIZE))) return (S21_NULL);
    str[--len] = '\0';
    while (len--) {
        str[len] = n % 10 + '0';
        n = n / 10;
    }
    return (str);
}

char *helper_ldtoa(long long int n) {
    long long int tmpn;
    int len;
    int neg;
    char *str;

    tmpn = n;
    len = 2;
    neg = tmpn < 0 ? 1 : 0;
    int min = 0;

    while (tmpn /= 10) len++;
    if (!(str = helper_memalloc(BUFFSIZE))) return (S21_NULL);
    len += neg;
    str[--len] = '\0';
    if (neg) {
        if (n == LONG_MIN) {
            n += 1;
            n = n * (-1);
            min = 1;
        } else {
            n *= -1;
        }
    }
    while (len--) {
        str[len] = n % 10 + '0';
        n = n / 10;
    }
    char *tmpns = str;
    if (min) {
        while (*(tmpns++) != '\0') {
            tmpns--;
            tmpns--;
            *tmpns += 1;
        }
    }
    if (neg)
        str[0] = '-';
    return (str);
}

char *checkFloatMaxMinCases(long double f_case, char *str) {
    if (f_case == INFINITY) return (s21_strdup("inf"));
    if (f_case == -INFINITY) return (s21_strdup("-inf"));
    if (f_case == NAN) return (s21_strdup("nan"));
    if (f_case == DBL_MAX || f_case == FLT_MAX)
        helper_floatMaxConversion(str);
    else
        free(str);
    char *s;
    s = helper_strNew(2);
    return (s);
}

long double s21_round(int accuracy, long double number) {
    if (accuracy == 0) {
        accuracy = 6;
    }
    long double n = number;
    int min_check = 0;
    if (n < 0) {
        min_check = 1;
        n *= -1;
    }
    double c;
    double m = modf(n, &c) * pow(10.0, accuracy);
    double mod = fmod(m, pow(10.0, accuracy));
    if (mod == 50) {
        m = round(m + 1) / pow(10.0, accuracy);
    } else {
        m = round(m) / pow(10.0, accuracy);
    }
    n = c + m;
    if (min_check == 1) {
        n *= -1;
    }
    return n;
}


// Конвертирует флоат в строку
char *helper_ftoa(long double f, struct s_format formatParams) {
    int i;
    double fpNumber;
    int size;
    char *str = "";
    int isNegative;

    i = 0;
    size = 1;

    fpNumber = f;
    isNegative = fpNumber < 0 ? 1 : 0;

    fpNumber = s21_round(formatParams.precision, fpNumber);

    if (fpNumber == INFINITY || fpNumber == -INFINITY || fpNumber == DBL_MAX ||
        fpNumber == FLT_MAX || fpNumber == NAN) {
        checkFloatMaxMinCases(fpNumber, str);
    }
    if (fpNumber < 0) isNegative = 1;
    if (isNegative) fpNumber *= -1;
    char *lenNum = (helper_itoa(fpNumber));

    size += (s21_strlen(lenNum) + isNegative);
    free(lenNum);
    size += formatParams.precision <= 0 ? 6 : formatParams.precision;
    size = size < 0 ? 6 : size;
    str = helper_strNew(size + 4);

    if (isNegative == 1) str[i++] = '-';

    helper_convertInteger(&fpNumber, &str, &i,
                          (helper_findMultiplier(fpNumber, &size)));

    if ((formatParams.precision == 0 &&
         formatParams.precisionWillBeSpecified == 1) ||
        formatParams.precisionIsNull) {
        helper_cutStr(str, formatParams.precision, 1);
        return (str);
    }
    helper_convertDecimal(&str, &i, (float)fpNumber, size);
    helper_cutStr(str, formatParams.precision, 0);
    return (str);
}

// Конвертирует максимальный флоат
char *helper_floatMaxConversion(char *str) {
    int i;
    char float_max[50];

    i = 0;
    s21_strcpy(float_max, "340282346638528859811704183484516925440.000000\0");
    if (!(str = (char *)malloc(sizeof(float_max)))) return (S21_NULL);
    while (float_max[i] != '\0') {
        str[i] = float_max[i];
        i++;
    }
    return (str);
}
// Ищет множитель для работы с десятичной частью
long long int helper_findMultiplier(long double fpNumber, int *size) {
    long int multiplier;
    long int extra;

    extra = (long int)(fpNumber);
    multiplier = 1;
    while ((extra /= 10) != 0) {
        multiplier *= 10;
        size++;
    }
    return (multiplier);
}

// Конвертирует десятичную часть дабла
void helper_convertDecimal(char **str, int *i, float fpNumber, int accuracy) {
    int j;
    char *s;

    fpNumber *= 10;
    j = 0;
    s = *str;
    s[(*i)++] = '.';
    while (j++ < accuracy) {
        long int tmp = ((long int)fpNumber != 9) ? (long int)(fpNumber + 0.01)
                                        : (long int)fpNumber;
        s[(*i)++] = (char)(tmp + 48);
        fpNumber = (fpNumber - tmp) * 10;
    }
}

// Конвертирует целую часть дабла
void helper_convertInteger(double *fpNumber, char **str, int *i,
                           long int multiplier) {
    char *s;
    long int b;

    b = (long int)*fpNumber;
    s = *str;
    if (b < 0) {
        *fpNumber *= -1;
        b *= -1;
    }
    if (b == 0) {
        s[(*i)++] = '0';
        return;
    }
    *fpNumber -= (long double)b;
    while (multiplier >= 1) {
        s[(*i)++] = (char)((b / multiplier) + 48);
        b = b - (b / multiplier) * multiplier;
        multiplier /= 10;
    }
}

// Режет строку согласно необходимой точности
void helper_cutStr(char *str, int pres, int isSetByZero) {
    int i;
    int k;

    i = 0;
    if (isSetByZero) {
        k = 0;
    } else {
        k = pres <= 0 ? 6 : pres;
        while (str[i] != '.') str++;
    }

    while (k != 0 && (*str != '\0')) {
        str++;
        k--;
    }

    if (isSetByZero == 1) {
        s21_size_t j = s21_strlen(str);
        str[j] = '\0';
    } else {
        *(++str) = '\0';
    }
}

// Создает новую строку
char *helper_strNew(s21_size_t size) {
    char *str;
    if (size + 1 < size) return (S21_NULL);
    str = (char *)calloc(BUFFSIZE, sizeof(char));
    if (str == 0) return (S21_NULL);
    helper_bZero(str, size + 1);
    return (str);
}

// Возвращает длину предполагаемой строки исходя из количество цифр в числе
int helper_countNumerals(long double chislo) {
    char *str;
    int k;

    str = helper_itoa((long long int)chislo);
    k = s21_strlen(str);
    free(str);

    return (k);
}

// Конвертирует дабл
char *helper_dtoa(long double ldNumber, struct s_format formatParams) {
    int i;
    long double chislo;
    int size;
    char *str;
    int sign;

    i = 0;
    size = 1;

    chislo = ldNumber;

    sign = 0;
    if (chislo < 0) sign = 1;

    size += formatParams.precision <= 0 ? 6 : formatParams.precision;
    size += (sign);
    str = helper_strNew(helper_countNumerals(chislo) + 1);
    if (sign == 1) str[i++] = '-';
    helper_convertDblInteger(&chislo, &str, &i,
                             (helper_findMultiplier(chislo, &size)));
    if (formatParams.precision == 0 &&
        formatParams.precisionWillBeSpecified == 1) {
        helper_cutStr(str, formatParams.precision,
                      formatParams.precisionSetByZero);
        return (str);
    }
    helper_convertDblDecimal(&str, &i, chislo,
                             (helper_countNumerals(chislo) + size + 4 + sign));
    str = helper_round(str, formatParams.precision,
                       formatParams.precisionSetByZero);
    helper_cutStr(str, formatParams.precision, formatParams.precisionSetByZero);
    str[i - 1] = '\0';
    return (str);
}

// Конвертирует целую часть дабла
void helper_convertDblDecimal(char **str, int *i, long double chislo,
                              int accuracy) {
    int j;
    char *s;

    chislo *= 10;
    j = 0;
    s = *str;
    s[(*i)++] = '.';
    while (j++ < accuracy) {
        long long int tmp = ((long long int)chislo != 9) ? (long long int)(chislo + 0.01)
                                           : (long long int)chislo;
        s[(*i)++] = (char)(tmp + 48);
        chislo = (chislo - tmp) * 10;
    }
}

// Конвертирует десятичную часть дабла
void helper_convertDblInteger(long double *ldblNumber, char **str, int *i, long int multiplier) {
    char *s;
    long int b;

    b = (long int)*ldblNumber;
    s = *str;
    if (b < 0) {
        *ldblNumber *= -1;
        b *= -1;
    }
    if (b == 0) s[(*i)++] = '0';
    *ldblNumber -= (long double)b;
    while (multiplier >= 1) {
        s[(*i)++] = (char)((b / multiplier) + 48);
        b = b - (b / multiplier) * multiplier;
        multiplier /= 10;
    }
}

int helper_recursion(int *i, char *str) {
    if (*str == '.' && *(++str) == '0') {
        return 1;
    }
    if (*str == '9' && *(str--) != '.') {
        str++;
        *str = '0';
        str--;
        int rounded = helper_recursion(i, str);
        if (rounded) return (1);
    } else if (*str != '0' && *(str--) != '.') {
        *str += 1;
    } else if (*str != '0' && *(str--) == '.') {
        *str += 1;
        return 1;
    }
    return (0);
}

// Округлятор последней цифры
char *helper_round(char *str, int accuracy, int precisionSetByZero) {
    int i = 0;

    char *tmp = str;
    while (*str != '.') {
        str++;
    }
    str++;
    if (accuracy == 0 && precisionSetByZero) {
        accuracy = 0;
    } else if (accuracy == 0) {
        accuracy = 6;
    }
    i += accuracy + 1;
    for (int k = 0; k < i; k++) {
        str++;
    }

int k = 0;
if (*str >= 5 && *(str--) != '.') {
    int rounded = helper_recursion(&i, str);
    k = rounded;
}

char *tmpn = tmp;

if (k) {
    while (*(tmp++) != '.') {
        tmp--;
        tmp--;
        *tmp += 1;
    }
}
    return (tmpn);
}

void handlePrec(char *buff, struct s_format *formatParams) {
    char tmp[BUFFSIZE] = {'\0'};
    int isNeg = 0;
    int len = (int)s21_strlen(buff);

    if (buff[0] == '-') {
        tmp[0] = '-';
        len--;
        isNeg = 1;
    }

    if (formatParams->precision > len) {
        int i;
        for (i = isNeg; i < formatParams->precision - len + isNeg; i++)
            tmp[i] = '0';

        for (int j = isNeg; buff[j]; i++, j++) tmp[i] = buff[j];

        s21_strcpy(buff, tmp);
    }
    if (formatParams->precisionWillBeSpecified &&
        formatParams->precision == 0 && formatParams->isInt && buff[0] == '0')
        buff[0] = '\0';
}

void handleFlags(char *buff, struct s_format *formatParams) {
    char tmp[BUFFSIZE + 1] = {'\0'};
    if (formatParams->flagPlus && !formatParams->spec) {
        tmp[0] = buff[0] == '-' ? buff[0] : '+';
        s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
        s21_strcpy(buff, tmp);
    } else if (formatParams->flagSpace && buff[0] != '-' &&
               formatParams->spec != 1) {
        tmp[0] = ' ';
        s21_strcpy(tmp + 1, buff);
        s21_strcpy(buff, tmp);
    }
    if (formatParams->width > (int)s21_strlen(buff)) {
        int i = formatParams->width - s21_strlen(buff);
        if (!formatParams->flagMinus) {
            s21_memset(tmp, formatParams->widthMustBeWrittenByZero ? '0' : ' ',
                       i);
            if (buff[0] == '-' && formatParams->widthMustBeWrittenByZero) {
                buff++;
            }
            s21_strcpy(tmp + i, buff);
        } else {
            s21_strcpy(tmp, buff);
            s21_memset(tmp + s21_strlen(tmp), ' ', i);
        }
        s21_strcpy(buff, tmp);
    }
}

void writeInt(char *buff, struct s_format *formatParams, char *string) {
    s21_memcpy(buff, string, s21_strlen(string));
    handlePrec(buff, formatParams);
    handleFlags(buff, formatParams);
}

void handleString(struct s_format *formatParams, char *buff, char *str) {
    char tmp[BUFFSIZE] = {'\0'};
    s21_strcpy(tmp, str);
    if (formatParams->precisionWillBeSpecified)
        tmp[formatParams->precision] = '\0';

    int shift = formatParams->width - s21_strlen(tmp);
    s21_size_t len = s21_strlen(tmp);
    if (formatParams->precisionIsNull) s21_memset(tmp, ' ', len);
    if (formatParams->flagMinus && shift > 0) {
        s21_strcpy(buff, tmp);
        s21_memset(buff + len, ' ', shift);
    } else if (shift > 0) {
        s21_memset(buff, ' ', shift);
        s21_strcpy(buff + shift, tmp);
    } else {
        s21_strcpy(buff, tmp);
    }
}

void handleWideString(struct s_format *formatParams, char *buff, wchar_t *wstr) {
    char tmp[BUFFSIZE] = {'\0'};
    char str[BUFFSIZE] = {'\0'};

    wcstombs(str, wstr, BUFFSIZE);
    s21_strcpy(tmp, str);
    if (formatParams->precisionWillBeSpecified)
        tmp[formatParams->precision] = '\0';

    int shift = formatParams->width - s21_strlen(tmp);
    int len = s21_strlen(tmp);

    if (formatParams->flagMinus && shift > 0) {
        s21_strcpy(buff, tmp);
        s21_memset(buff + len, ' ', shift);
    } else if (shift > 0) {
        s21_memset(buff, ' ', shift);
        s21_strcpy(buff + shift, tmp);
    } else {
        s21_strcpy(buff, tmp);
    }
}

void writeFloat(char *buff, struct s_format *formatParams, char *string) {
    s21_memcpy(buff, string, s21_strlen(string));
    handleFlags(buff, formatParams);
}

int parser(const char **inputLine, struct s_format *inputLineParams) {
    int flags = 0;

    while (**inputLine) {
        if (**inputLine == '-' || **inputLine == '+' || **inputLine == ' ') {
            if (**inputLine == '-')
                inputLineParams->flagMinus = 1;
            else if (**inputLine == '+')
                inputLineParams->flagPlus = 1;
            else if (**inputLine == ' ')
                inputLineParams->flagSpace = 1;
            (*inputLine)++;
        } else if (s21_isDigit(**inputLine) == 1) {
            if (**inputLine == '0' && inputLineParams->widthZeroDetected == 0) {
                (*inputLine)--;
                if (s21_isDigit(**inputLine) == 0) {
                    inputLineParams->widthMustBeWrittenByZero = 1;
                    inputLineParams->widthZeroDetected = 1;
                }
                (*inputLine)++;
            }
            inputLineParams->width =
                **inputLine - '0' + inputLineParams->width * 10;
            (*inputLine)++;
        } else if (**inputLine == '*') {
            (*inputLine)--;
            if (**inputLine != '.') {
                inputLineParams->isAsteriskWidth = 1;
                (*inputLine)++;
            } else {
                (*inputLine)++;
            }
            (*inputLine)++;
        } else if (**inputLine == '.') {
            (*inputLine)++;
            if ((!s21_isDigit(**inputLine)) && **inputLine != '*')
                inputLineParams->precisionIsNull = 1;
            if (**inputLine == '*') {
                inputLineParams->isAsteriskFloatWidthDescription = 1;
                inputLineParams->precisionWillBeSpecified = 1;
            } else if (**inputLine == 'L' || **inputLine == 'f' ||
                       s21_isDigit(**inputLine) == 1) {
                inputLineParams->precisionWillBeSpecified = 1;
            } else if (**inputLine == '0') {
                inputLineParams->precisionSetByZero = 1;
            }
            while (s21_isDigit(**inputLine)) {
                inputLineParams->precision =
                    **inputLine - '0' + inputLineParams->precision * 10;
                (*inputLine)++;
            }
        } else if (**inputLine == 'h' || **inputLine == 'l' ||
                   **inputLine == 'L') {
            if (**inputLine == 'h')
                inputLineParams->length_h = 1;
            else if (**inputLine == 'l')
                inputLineParams->length_l = 1;
            else if (**inputLine == 'L')
                inputLineParams->isLongDouble = 1;
            (*inputLine)++;
        } else if (helper_isSpec(**inputLine, inputLineParams) == 1) {
            flags = 1;
            break;
        } else {
            flags = 0;
            break;
        }
    }
    return flags;
}

void helper_writeInBuffer(const char **format, char **str,
                          struct s_format *formatParams, va_list vlist,
                          char *buff) {
    if (**format == 'c') {
        if (formatParams->isAsteriskWidth) {
            formatParams->width = va_arg(vlist, int);
        }
        char c = va_arg(vlist, int);
        helper_writeChar(format, str, formatParams, c);
    } else if (**format == 'L') {
        formatParams->isLongDouble = 1;
    } else if (**format == '%') {
        if (formatParams->isAsteriskWidth) {
            formatParams->width = va_arg(vlist, int);
        }
        helper_writePercent(format, str);
    } else if (**format == 's') {
        if (formatParams->isAsteriskWidth) {
            formatParams->width = va_arg(vlist, int);
        }
        if (formatParams->isAsteriskFloatWidthDescription) {
            formatParams->precision = va_arg(vlist, int);
        }
        if (formatParams->length_l) {
            wchar_t *string = va_arg(vlist, wchar_t *);
            handleWideString(formatParams, buff, string);
            (*format)++;
        } else {
            char *string = va_arg(vlist, char *);
            if (!string) string = "(null)";
            handleString(formatParams, buff, string);
            (*format)++;
        }
    } else if (**format == 'd' || **format == 'i') {
        formatParams->isInt = 1;
        if (formatParams->isAsteriskWidth)
            formatParams->width = va_arg(vlist, int);
        if (formatParams->isAsteriskFloatWidthDescription)
            formatParams->precision = va_arg(vlist, int);
        if (formatParams->length_l) {
            long long int lint = va_arg(vlist, long long int);
            if (lint < 0) formatParams->flagPlus = 0;
            char *temps = helper_ldtoa(lint);
            writeInt(buff, formatParams, temps);
            free(temps);
            (*format)++;
        } else if (formatParams->length_h) {
            short int sint = va_arg(vlist, int);
            if (sint < 0) formatParams->flagPlus = 0;
            char *temp = helper_itoa(sint);
            writeInt(buff, formatParams, temp);
            free(temp);
            (*format)++;
        } else {
            int intParam = va_arg(vlist, int);
            if (intParam < 0) formatParams->flagPlus = 0;
            char *tempr = helper_itoa(intParam);
            writeInt(buff, formatParams, tempr);
            free(tempr);
            (*format)++;
        }
    } else if (**format == 'f') {
        if (formatParams->isAsteriskWidth)
            formatParams->width = va_arg(vlist, int);
        if (formatParams->isAsteriskFloatWidthDescription) {
            if (!formatParams->precisionIsNull)
                formatParams->precision = va_arg(vlist, int);
            else
                formatParams->precision = 0;
        }
        if (formatParams->isLongDouble) {
            long double floatParam = va_arg(vlist, long double);
            if (!floatParam) floatParam = 0;
            char *temporary = helper_dtoa(floatParam, *formatParams);
            writeFloat(buff, formatParams, temporary);
            free(temporary);
            (*format)++;
        } else {
            long double floatParam = va_arg(vlist, double);
            char *temporary = helper_ftoa(floatParam, *formatParams);
            writeFloat(buff, formatParams, temporary);
            free(temporary);
            (*format)++;
        }
    } else if (**format == 'u') {
        if (formatParams->isAsteriskWidth)
            formatParams->width = va_arg(vlist, int);
        if (formatParams->isAsteriskFloatWidthDescription) {
            if (!formatParams->precisionIsNull)
                formatParams->precision = va_arg(vlist, int);
            else
                formatParams->precision = 0;
        }
        long unsigned int uint = va_arg(vlist, long unsigned int);
        char *temp = helper_utoa(uint);
        writeInt(buff, formatParams, temp);
        free(temp);
        (*format)++;
    }
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list vlist;
    char *tmp = str;
    s21_size_t b = 0;
    va_start(vlist, format);

    while (*format) {
        if (*format != '%') {
            *str = *format;
            str++;
            format++;
        } else {
            struct s_format formatParams;
            helper_initStruct(&formatParams);
            format++;
            char buff[BUFFSIZE] = {'\0'};
            if (parser(&format, &formatParams) == 1) {
                helper_writeInBuffer(&format, &str, &formatParams, vlist, buff);
            }
            for (int i = 0; buff[i]; i++, str++) {
                *str = buff[i];
                b += 1;
            }
        }
    }
    *str = '\0';
    b = s21_strlen(tmp);
    va_end(vlist);

    return (b);
}

void *s21_to_upper(const char *str) {
  char *ret = (char*)calloc(s21_strlen(str)+1, sizeof(char));
        if (!ret) {
          exit(1);
        }
       for (s21_size_t i = 0; i < s21_strlen(str); i++) {
            if (str[i] > 96 && str[i] < 123) {
            ret[i] = str[i] - 32;
            } else {
              ret[i] = str[i];
              continue;
              }
       }
  return ret;
}

void *s21_to_lower(const char *str) {
  char *ret = (char*)calloc(s21_strlen(str)+1, sizeof(char));
        if (!ret) {
           exit(1);
        }
       for (s21_size_t i = 0; i < s21_strlen(str); i++) {
            if (str[i] > 64 && str[i] < 91) {
            ret[i] = str[i] + 32;
            } else {
              ret[i] = str[i];
              continue;
              }
       }
  return ret;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
    char *new_str = s21_NULL;
    int flag = 0;
    if (src && str && s21_strlen(src) >= start_index) {
        s21_size_t new_length = s21_strlen(src) + s21_strlen(str) + 1;
        if (src && str && s21_strlen(src) >= start_index) {
                new_str = malloc(new_length * sizeof(char) + 1);
        }
        if (new_str == s21_NULL) {
                flag++;
        }
        if (!flag) {
                for (s21_size_t i = 0; i < start_index; i++) {
                        new_str[i] = src[i];
                }
                size_t j = start_index;
                for (s21_size_t g = 0; g < s21_strlen(str); g++) {
                        new_str[j] = str[g];
                        j++;
                }
                s21_size_t k = s21_strlen(str) + start_index;
                for (s21_size_t i = start_index; i < s21_strlen(src); i++) {
                         new_str[k] = src[i];
                        k++;
                }
                new_str[new_length - 1] = '\0';
        }
     }
return  !flag ? (void *)new_str : s21_NULL;
}


void *s21_trim(const char *src, const char *trim_chars) {
    char *res = s21_NULL;

    if (src) {
        if (trim_chars && *trim_chars) {
            s21_size_t len = s21_strlen(src);
            s21_size_t chars_len = s21_strlen(trim_chars);

            s21_size_t m = 0;
                while (src && m != chars_len) {
                    if ((*src) == trim_chars[m]) {
                    src++;
                    len -= 1;
                    m = 0;
                    continue;
                    }
                    m++;
                    }
                if (len) {
                    s21_size_t e = 0;
                    s21_size_t t = len - 1;
                    while (src && e != chars_len) {
                        if (src[t] == trim_chars[e]) {
                            t--;
                            len--;
                            e = 0;
                            continue;
                            }
                            e++;
                        }
                }
            res = (char *)malloc(sizeof(char) * (len + 1));
            if (res) {
                for (s21_size_t i = 0; i < len + 1; i++) {
                    if (i < len) {
                        res[i] = src[i];
                    } else {
                        res[i] = '\0';
                    }
                }
            }
        } else {
            res = s21_trim(src, " \t\n");
        }
    }

    return res;
}
