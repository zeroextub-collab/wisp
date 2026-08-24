#pragma section("__nv_managed_data__")
static char __nv_inited_managed_rt = 0; static void **__nv_fatbinhandle_for_managed_rt; static void __nv_save_fatbinhandle_for_managed_rt(void **in){__nv_fatbinhandle_for_managed_rt = in;} static char __nv_init_managed_rt_with_module(void **); static inline void __nv_init_managed_rt(void) { __nv_inited_managed_rt = (__nv_inited_managed_rt ? __nv_inited_managed_rt                 : __nv_init_managed_rt_with_module(__nv_fatbinhandle_for_managed_rt));}
#line 1 "CMakeCUDACompilerId.cu"
#define __nv_is_extended_device_lambda_closure_type(X) false
#define __nv_is_extended_host_device_lambda_closure_type(X) false
#define __nv_is_extended_device_lambda_with_preserved_return_type(X) false
#if defined(__nv_is_extended_device_lambda_closure_type) && defined(__nv_is_extended_host_device_lambda_closure_type)&& defined(__nv_is_extended_device_lambda_with_preserved_return_type)
#endif

#line 1
#line 67 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
#pragma warning(push)
#pragma warning(disable: 4820)
#line 708 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\sal.h"
#pragma region Input Buffer SAL 1 compatibility macros
#line 1472
#pragma endregion Input Buffer SAL 1 compatibility macros
#line 2361 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\sal.h"
extern "C" {
#line 2971 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\sal.h"
}
#line 22 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\concurrencysal.h"
extern "C" {
#line 391 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\concurrencysal.h"
}
#line 19 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
#pragma pack ( push, 8 )
#line 51 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 55
extern "C" {
#line 65 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
typedef unsigned __int64 uintptr_t; 
#line 76 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
typedef char *va_list; 
#line 153 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
void __cdecl __va_start(va_list *, ...); 
#line 165 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
}
#line 169 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
extern "C++" {
#line 171
template< class _Ty> 
#line 172
struct __vcrt_va_list_is_reference { 
#line 174
enum: bool { __the_value}; 
#line 175
}; 
#line 177
template< class _Ty> 
#line 178
struct __vcrt_va_list_is_reference< _Ty &>  { 
#line 180
enum: bool { __the_value = '\001'}; 
#line 181
}; 
#line 183
template< class _Ty> 
#line 184
struct __vcrt_va_list_is_reference< _Ty &&>  { 
#line 186
enum: bool { __the_value = '\001'}; 
#line 187
}; 
#line 189
template< class _Ty> 
#line 190
struct __vcrt_assert_va_start_is_not_reference { 
#line 192
static_assert((!__vcrt_va_list_is_reference< _Ty> ::__the_value), "va_start argument must not have reference type and must not be parenthesized");
#line 194
}; 
#line 195
}
#line 205 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vadefs.h"
#pragma warning(pop)
#pragma pack ( pop )
#line 60 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 96 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
__pragma( pack ( push, 8 )) extern "C" {
#line 188 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
typedef unsigned __int64 size_t; 
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#line 189
typedef __int64 ptrdiff_t; 
#line 190
typedef __int64 intptr_t; 
#line 198 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
typedef bool __vcrt_bool; 
#line 245 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
extern "C++" {
#line 247
template< class _CountofType, size_t _SizeOfArray> char (*__countof_helper(__unaligned _CountofType (& _Array)[_SizeOfArray]))[_SizeOfArray]; 
#line 251
}
#line 380 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
void __cdecl __security_init_cookie(); 
#line 389 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
void __cdecl __security_check_cookie(uintptr_t _StackCookie); 
#line 390
__declspec(noreturn) void __cdecl __report_gsfailure(uintptr_t _StackCookie); 
#line 394 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
extern uintptr_t __security_cookie; 
#line 402 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime.h"
}__pragma( pack ( pop )) 
#line 404
#pragma warning(pop)
#line 121 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 125
__pragma( pack ( push, 8 )) extern "C" {
#line 254 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
extern "C++" {
#line 256
template< bool _Enable, class _Ty> struct _CrtEnableIf; 
#line 259
template< class _Ty> 
#line 260
struct _CrtEnableIf< true, _Ty>  { 
#line 262
typedef _Ty _Type; 
#line 263
}; 
#line 264
}
#line 268 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
typedef bool __crt_bool; 
#line 371 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
void __cdecl _invalid_parameter_noinfo(); 
#line 372
__declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn(); 
#line 374
__declspec(noreturn) void __cdecl 
#line 375
_invoke_watson(const __wchar_t * _Expression, const __wchar_t * _FunctionName, const __wchar_t * _FileName, unsigned _LineNo, uintptr_t _Reserved); 
#line 604 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
typedef int errno_t; 
#line 605
typedef unsigned short wint_t; 
#line 606
typedef unsigned short wctype_t; 
#line 607
typedef long __time32_t; 
#line 608
typedef __int64 __time64_t; 
#line 615
typedef 
#line 610
struct __crt_locale_data_public { 
#line 612
const unsigned short *_locale_pctype; 
#line 613
int _locale_mb_cur_max; 
#line 614
unsigned _locale_lc_codepage; 
#line 615
} __crt_locale_data_public; 
#line 621
typedef 
#line 617
struct __crt_locale_pointers { 
#line 619
struct __crt_locale_data *locinfo; 
#line 620
struct __crt_multibyte_data *mbcinfo; 
#line 621
} __crt_locale_pointers; 
#line 623
typedef __crt_locale_pointers *_locale_t; 
#line 629
typedef 
#line 625
struct _Mbstatet { 
#line 627
unsigned long _Wchar; 
#line 628
unsigned short _Byte, _State; 
#line 629
} _Mbstatet; 
#line 631
typedef _Mbstatet mbstate_t; 
#line 684 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
typedef __time64_t time_t; 
#line 694 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
typedef size_t rsize_t; 
#line 2111 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt.h"
}__pragma( pack ( pop )) 
#line 2114
#pragma warning(pop)
#line 13 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wctype.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 17
__pragma( pack ( push, 8 )) extern "C" {
#line 35 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wctype.h"
const unsigned short *__cdecl __pctype_func(); 
#line 36
const wctype_t *__cdecl __pwctype_func(); 
#line 67 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wctype.h"
int __cdecl iswalnum(wint_t _C); 
#line 68
int __cdecl iswalpha(wint_t _C); 
#line 69
int __cdecl iswascii(wint_t _C); 
#line 70
int __cdecl iswblank(wint_t _C); 
#line 71
int __cdecl iswcntrl(wint_t _C); 
#line 74
int __cdecl iswdigit(wint_t _C); 
#line 76
int __cdecl iswgraph(wint_t _C); 
#line 77
int __cdecl iswlower(wint_t _C); 
#line 78
int __cdecl iswprint(wint_t _C); 
#line 79
int __cdecl iswpunct(wint_t _C); 
#line 80
int __cdecl iswspace(wint_t _C); 
#line 81
int __cdecl iswupper(wint_t _C); 
#line 82
int __cdecl iswxdigit(wint_t _C); 
#line 83
int __cdecl __iswcsymf(wint_t _C); 
#line 84
int __cdecl __iswcsym(wint_t _C); 
#line 86
int __cdecl _iswalnum_l(wint_t _C, _locale_t _Locale); 
#line 87
int __cdecl _iswalpha_l(wint_t _C, _locale_t _Locale); 
#line 88
int __cdecl _iswblank_l(wint_t _C, _locale_t _Locale); 
#line 89
int __cdecl _iswcntrl_l(wint_t _C, _locale_t _Locale); 
#line 90
int __cdecl _iswdigit_l(wint_t _C, _locale_t _Locale); 
#line 91
int __cdecl _iswgraph_l(wint_t _C, _locale_t _Locale); 
#line 92
int __cdecl _iswlower_l(wint_t _C, _locale_t _Locale); 
#line 93
int __cdecl _iswprint_l(wint_t _C, _locale_t _Locale); 
#line 94
int __cdecl _iswpunct_l(wint_t _C, _locale_t _Locale); 
#line 95
int __cdecl _iswspace_l(wint_t _C, _locale_t _Locale); 
#line 96
int __cdecl _iswupper_l(wint_t _C, _locale_t _Locale); 
#line 97
int __cdecl _iswxdigit_l(wint_t _C, _locale_t _Locale); 
#line 98
int __cdecl _iswcsymf_l(wint_t _C, _locale_t _Locale); 
#line 99
int __cdecl _iswcsym_l(wint_t _C, _locale_t _Locale); 
#line 102
wint_t __cdecl towupper(wint_t _C); 
#line 103
wint_t __cdecl towlower(wint_t _C); 
#line 104
int __cdecl iswctype(wint_t _C, wctype_t _Type); 
#line 106
wint_t __cdecl _towupper_l(wint_t _C, _locale_t _Locale); 
#line 107
wint_t __cdecl _towlower_l(wint_t _C, _locale_t _Locale); 
#line 108
int __cdecl _iswctype_l(wint_t _C, wctype_t _Type, _locale_t _Locale); 
#line 112
int __cdecl isleadbyte(int _C); 
#line 113
int __cdecl _isleadbyte_l(int _C, _locale_t _Locale); 
#line 115
__declspec(deprecated("This function or variable has been superceded by newer library or operating system functionality. Consider using iswctype instea" "d. See online help for details.")) int __cdecl is_wctype(wint_t _C, wctype_t _Type); 
#line 203 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wctype.h"
}__pragma( pack ( pop )) 
#line 205
#pragma warning(pop)
#line 15 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\ctype.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 19
__pragma( pack ( push, 8 )) extern "C" {
#line 29
int __cdecl _isctype(int _C, int _Type); 
#line 30
int __cdecl _isctype_l(int _C, int _Type, _locale_t _Locale); 
#line 31
int __cdecl isalpha(int _C); 
#line 32
int __cdecl _isalpha_l(int _C, _locale_t _Locale); 
#line 33
int __cdecl isupper(int _C); 
#line 34
int __cdecl _isupper_l(int _C, _locale_t _Locale); 
#line 35
int __cdecl islower(int _C); 
#line 36
int __cdecl _islower_l(int _C, _locale_t _Locale); 
#line 39
int __cdecl isdigit(int _C); 
#line 41
int __cdecl _isdigit_l(int _C, _locale_t _Locale); 
#line 42
int __cdecl isxdigit(int _C); 
#line 43
int __cdecl _isxdigit_l(int _C, _locale_t _Locale); 
#line 46
int __cdecl isspace(int _C); 
#line 48
int __cdecl _isspace_l(int _C, _locale_t _Locale); 
#line 49
int __cdecl ispunct(int _C); 
#line 50
int __cdecl _ispunct_l(int _C, _locale_t _Locale); 
#line 51
int __cdecl isblank(int _C); 
#line 52
int __cdecl _isblank_l(int _C, _locale_t _Locale); 
#line 53
int __cdecl isalnum(int _C); 
#line 54
int __cdecl _isalnum_l(int _C, _locale_t _Locale); 
#line 55
int __cdecl isprint(int _C); 
#line 56
int __cdecl _isprint_l(int _C, _locale_t _Locale); 
#line 57
int __cdecl isgraph(int _C); 
#line 58
int __cdecl _isgraph_l(int _C, _locale_t _Locale); 
#line 59
int __cdecl iscntrl(int _C); 
#line 60
int __cdecl _iscntrl_l(int _C, _locale_t _Locale); 
#line 63
int __cdecl toupper(int _C); 
#line 66
int __cdecl tolower(int _C); 
#line 68
int __cdecl _tolower(int _C); 
#line 69
int __cdecl _tolower_l(int _C, _locale_t _Locale); 
#line 70
int __cdecl _toupper(int _C); 
#line 71
int __cdecl _toupper_l(int _C, _locale_t _Locale); 
#line 73
int __cdecl __isascii(int _C); 
#line 74
int __cdecl __toascii(int _C); 
#line 75
int __cdecl __iscsymf(int _C); 
#line 76
int __cdecl __iscsym(int _C); 
#line 85
__inline int __cdecl __acrt_locale_get_ctype_array_value(const unsigned short *const 
#line 86
_Locale_pctype_array, const int 
#line 87
_Char_value, const int 
#line 88
_Mask) 
#line 90
{ 
#line 96
if ((_Char_value >= (-1)) && (_Char_value <= 255)) 
#line 97
{ 
#line 98
return (_Locale_pctype_array[_Char_value]) & _Mask; 
#line 99
}  
#line 101
return 0; 
#line 102
} 
#line 124 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\ctype.h"
int __cdecl ___mb_cur_max_func(); 
#line 126
int __cdecl ___mb_cur_max_l_func(_locale_t _Locale); 
#line 152 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\ctype.h"
__forceinline int __cdecl __ascii_tolower(const int _C) 
#line 153
{ 
#line 154
if ((_C >= ('A')) && (_C <= ('Z'))) 
#line 155
{ 
#line 156
return _C - (('A') - ('a')); 
#line 157
}  
#line 158
return _C; 
#line 159
} 
#line 161
__forceinline int __cdecl __ascii_toupper(const int _C) 
#line 162
{ 
#line 163
if ((_C >= ('a')) && (_C <= ('z'))) 
#line 164
{ 
#line 165
return _C - (('a') - ('A')); 
#line 166
}  
#line 167
return _C; 
#line 168
} 
#line 170
__forceinline int __cdecl __ascii_iswalpha(const int _C) 
#line 171
{ 
#line 172
return ((_C >= ('A')) && (_C <= ('Z'))) || ((_C >= ('a')) && (_C <= ('z'))); 
#line 173
} 
#line 175
__forceinline int __cdecl __ascii_iswdigit(const int _C) 
#line 176
{ 
#line 177
return (_C >= ('0')) && (_C <= ('9')); 
#line 178
} 
#line 180
__forceinline int __cdecl __ascii_towlower(const int _C) 
#line 181
{ 
#line 182
return __ascii_tolower(_C); 
#line 183
} 
#line 185
__forceinline int __cdecl __ascii_towupper(const int _C) 
#line 186
{ 
#line 187
return __ascii_toupper(_C); 
#line 188
} 
#line 208 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\ctype.h"
__inline __crt_locale_data_public *__cdecl __acrt_get_locale_data_prefix(const volatile void *const _LocalePointers) 
#line 209
{ 
#line 210
const _locale_t _TypedLocalePointers = (_locale_t)_LocalePointers; 
#line 211
return (__crt_locale_data_public *)(_TypedLocalePointers->locinfo); 
#line 212
} 
#line 218
__inline int __cdecl _chvalidchk_l(const int 
#line 219
_C, const int 
#line 220
_Mask, const _locale_t 
#line 221
_Locale) 
#line 223
{ 
#line 227
if (!_Locale) 
#line 228
{ 
#line 229
return __acrt_locale_get_ctype_array_value(__pctype_func(), _C, _Mask); 
#line 230
}  
#line 232
return __acrt_locale_get_ctype_array_value(__acrt_get_locale_data_prefix(_Locale)->_locale_pctype, _C, _Mask); 
#line 234 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\ctype.h"
} 
#line 239
__inline int __cdecl _ischartype_l(const int 
#line 240
_C, const int 
#line 241
_Mask, const _locale_t 
#line 242
_Locale) 
#line 244
{ 
#line 245
if (!_Locale) 
#line 246
{ 
#line 247
return _chvalidchk_l(_C, _Mask, 0); 
#line 248
}  
#line 250
if ((_C >= (-1)) && (_C <= 255)) 
#line 251
{ 
#line 252
return ((__acrt_get_locale_data_prefix(_Locale)->_locale_pctype)[_C]) & _Mask; 
#line 253
}  
#line 255
if ((__acrt_get_locale_data_prefix(_Locale)->_locale_mb_cur_max) > 1) 
#line 256
{ 
#line 257
return _isctype_l(_C, _Mask, _Locale); 
#line 258
}  
#line 260
return 0; 
#line 261
} 
#line 307 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\ctype.h"
}__pragma( pack ( pop )) 
#line 309
#pragma warning(pop)
#line 68 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_types.h"
#if 0
#line 68
enum cudaRoundMode { 
#line 70
cudaRoundNearest, 
#line 71
cudaRoundZero, 
#line 72
cudaRoundPosInf, 
#line 73
cudaRoundMinInf
#line 74
}; 
#endif
#line 178 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 178
struct char1 { 
#line 180
signed char x; 
#line 181
}; 
#endif
#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 183
struct uchar1 { 
#line 185
unsigned char x; 
#line 186
}; 
#endif
#line 189 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 189
struct __declspec(align(2)) char2 { 
#line 191
signed char x, y; 
#line 192
}; 
#endif
#line 194 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 194
struct __declspec(align(2)) uchar2 { 
#line 196
unsigned char x, y; 
#line 197
}; 
#endif
#line 199 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 199
struct char3 { 
#line 201
signed char x, y, z; 
#line 202
}; 
#endif
#line 204 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 204
struct uchar3 { 
#line 206
unsigned char x, y, z; 
#line 207
}; 
#endif
#line 209 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 209
struct __declspec(align(4)) char4 { 
#line 211
signed char x, y, z, w; 
#line 212
}; 
#endif
#line 214 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 214
struct __declspec(align(4)) uchar4 { 
#line 216
unsigned char x, y, z, w; 
#line 217
}; 
#endif
#line 219 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 219
struct short1 { 
#line 221
short x; 
#line 222
}; 
#endif
#line 224 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 224
struct ushort1 { 
#line 226
unsigned short x; 
#line 227
}; 
#endif
#line 229 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 229
struct __declspec(align(4)) short2 { 
#line 231
short x, y; 
#line 232
}; 
#endif
#line 234 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 234
struct __declspec(align(4)) ushort2 { 
#line 236
unsigned short x, y; 
#line 237
}; 
#endif
#line 239 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 239
struct short3 { 
#line 241
short x, y, z; 
#line 242
}; 
#endif
#line 244 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 244
struct ushort3 { 
#line 246
unsigned short x, y, z; 
#line 247
}; 
#endif
#line 249 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 249
struct __declspec(align(8)) short4 { short x; short y; short z; short w; }; 
#endif
#line 250 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 250
struct __declspec(align(8)) ushort4 { unsigned short x; unsigned short y; unsigned short z; unsigned short w; }; 
#endif
#line 252 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 252
struct int1 { 
#line 254
int x; 
#line 255
}; 
#endif
#line 257 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 257
struct uint1 { 
#line 259
unsigned x; 
#line 260
}; 
#endif
#line 262 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 262
struct __declspec(align(8)) int2 { int x; int y; }; 
#endif
#line 263 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 263
struct __declspec(align(8)) uint2 { unsigned x; unsigned y; }; 
#endif
#line 265 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 265
struct int3 { 
#line 267
int x, y, z; 
#line 268
}; 
#endif
#line 270 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 270
struct uint3 { 
#line 272
unsigned x, y, z; 
#line 273
}; 
#endif
#line 275 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 275
struct __declspec(align(16)) int4 { 
#line 277
int x, y, z, w; 
#line 278
}; 
#endif
#line 280 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 280
struct __declspec(align(16)) uint4 { 
#line 282
unsigned x, y, z, w; 
#line 283
}; 
#endif
#line 285 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 285
struct long1 { 
#line 287
long x; 
#line 288
}; 
#endif
#line 290 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 290
struct ulong1 { 
#line 292
unsigned long x; 
#line 293
}; 
#endif
#line 296 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 296
struct __declspec(align(8)) long2 { long x; long y; }; 
#endif
#line 297 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 297
struct __declspec(align(8)) ulong2 { unsigned long x; unsigned long y; }; 
#endif
#line 312 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 312
struct long3 { 
#line 314
long x, y, z; 
#line 315
}; 
#endif
#line 317 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 317
struct ulong3 { 
#line 319
unsigned long x, y, z; 
#line 320
}; 
#endif
#line 323 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 323
struct
#line 322
 __declspec(deprecated("use long4_16a or long4_32a"))
#line 323
 __declspec(align(16)) long4 { 
#line 325
long x, y, z, w; 
#line 326
}; 
#endif
#line 329 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 329
struct
#line 328
 __declspec(deprecated("use ulong4_16a or ulong4_32a"))
#line 329
 __declspec(align(16)) ulong4 { 
#line 331
unsigned long x, y, z, w; 
#line 332
}; 
#endif
#line 334 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 334
struct __declspec(align(16)) long4_16a { 
#line 336
long x, y, z, w; 
#line 337
}; 
#endif
#line 339 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 339
struct __declspec(align(16)) ulong4_16a { 
#line 341
unsigned long x, y, z, w; 
#line 342
}; 
#endif
#line 345 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#pragma warning(push)
#pragma warning(disable: 4324)
#line 348 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 348
struct __declspec(align(32)) long4_32a { 
#line 350
long x, y, z, w; 
#line 351
}; 
#endif
#line 353 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 353
struct __declspec(align(32)) ulong4_32a { 
#line 355
unsigned long x, y, z, w; 
#line 356
}; 
#endif
#line 358 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#pragma warning(pop)
#line 361 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 361
struct float1 { 
#line 363
float x; 
#line 364
}; 
#endif
#line 383 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 383
struct __declspec(align(8)) float2 { float x; float y; }; 
#endif
#line 388 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 388
struct float3 { 
#line 390
float x, y, z; 
#line 391
}; 
#endif
#line 393 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 393
struct __declspec(align(16)) float4 { 
#line 395
float x, y, z, w; 
#line 396
}; 
#endif
#line 398 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 398
struct longlong1 { 
#line 400
__int64 x; 
#line 401
}; 
#endif
#line 403 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 403
struct ulonglong1 { 
#line 405
unsigned __int64 x; 
#line 406
}; 
#endif
#line 408 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 408
struct __declspec(align(16)) longlong2 { 
#line 410
__int64 x, y; 
#line 411
}; 
#endif
#line 413 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 413
struct __declspec(align(16)) ulonglong2 { 
#line 415
unsigned __int64 x, y; 
#line 416
}; 
#endif
#line 418 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 418
struct longlong3 { 
#line 420
__int64 x, y, z; 
#line 421
}; 
#endif
#line 423 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 423
struct ulonglong3 { 
#line 425
unsigned __int64 x, y, z; 
#line 426
}; 
#endif
#line 429 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 429
struct
#line 428
 __declspec(deprecated("use longlong4_16a or longlong4_32a"))
#line 429
 __declspec(align(16)) longlong4 { 
#line 431
__int64 x, y, z, w; 
#line 432
}; 
#endif
#line 434 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 434
struct __declspec(align(16)) longlong4_16a { 
#line 436
__int64 x, y, z, w; 
#line 437
}; 
#endif
#line 439 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 439
struct __declspec(align(32)) longlong4_32a { 
#line 441
__int64 x, y, z, w; 
#line 442
}; 
#endif
#line 445 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 445
struct
#line 444
 __declspec(deprecated("use ulonglong4_16a or ulonglong4_32a"))
#line 445
 __declspec(align(16)) ulonglong4 { 
#line 447
unsigned __int64 x, y, z, w; 
#line 448
}; 
#endif
#line 450 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 450
struct __declspec(align(16)) ulonglong4_16a { 
#line 452
unsigned __int64 x, y, z, w; 
#line 453
}; 
#endif
#line 455 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 455
struct __declspec(align(32)) ulonglong4_32a { 
#line 457
unsigned __int64 x, y, z, w; 
#line 458
}; 
#endif
#line 461 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 461
struct double1 { 
#line 463
double x; 
#line 464
}; 
#endif
#line 466 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 466
struct __declspec(align(16)) double2 { 
#line 468
double x, y; 
#line 469
}; 
#endif
#line 471 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 471
struct double3 { 
#line 473
double x, y, z; 
#line 474
}; 
#endif
#line 477 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 477
struct
#line 476
 __declspec(deprecated("use double4_16a or double4_32a"))
#line 477
 __declspec(align(16)) double4 { 
#line 479
double x, y, z, w; 
#line 480
}; 
#endif
#line 482 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 482
struct __declspec(align(16)) double4_16a { 
#line 484
double x, y, z, w; 
#line 485
}; 
#endif
#line 487 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 487
struct __declspec(align(32)) double4_32a { 
#line 489
double x, y, z, w; 
#line 490
}; 
#endif
#line 504 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef char1 
#line 504
char1; 
#endif
#line 505 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uchar1 
#line 505
uchar1; 
#endif
#line 506 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef char2 
#line 506
char2; 
#endif
#line 507 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uchar2 
#line 507
uchar2; 
#endif
#line 508 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef char3 
#line 508
char3; 
#endif
#line 509 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uchar3 
#line 509
uchar3; 
#endif
#line 510 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef char4 
#line 510
char4; 
#endif
#line 511 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uchar4 
#line 511
uchar4; 
#endif
#line 512 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef short1 
#line 512
short1; 
#endif
#line 513 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ushort1 
#line 513
ushort1; 
#endif
#line 514 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef short2 
#line 514
short2; 
#endif
#line 515 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ushort2 
#line 515
ushort2; 
#endif
#line 516 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef short3 
#line 516
short3; 
#endif
#line 517 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ushort3 
#line 517
ushort3; 
#endif
#line 518 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef short4 
#line 518
short4; 
#endif
#line 519 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ushort4 
#line 519
ushort4; 
#endif
#line 520 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef int1 
#line 520
int1; 
#endif
#line 521 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uint1 
#line 521
uint1; 
#endif
#line 522 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef int2 
#line 522
int2; 
#endif
#line 523 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uint2 
#line 523
uint2; 
#endif
#line 524 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef int3 
#line 524
int3; 
#endif
#line 525 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uint3 
#line 525
uint3; 
#endif
#line 526 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef int4 
#line 526
int4; 
#endif
#line 527 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef uint4 
#line 527
uint4; 
#endif
#line 528 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef long1 
#line 528
long1; 
#endif
#line 529 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulong1 
#line 529
ulong1; 
#endif
#line 530 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef long2 
#line 530
long2; 
#endif
#line 531 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulong2 
#line 531
ulong2; 
#endif
#line 532 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef long3 
#line 532
long3; 
#endif
#line 533 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulong3 
#line 533
ulong3; 
#endif
#line 534 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#if 0
#line 535
__declspec(deprecated("use long4_16a or long4_32a")) typedef long4 long4; 
#endif
#line 536 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 536
__declspec(deprecated("use ulong4_16a or ulong4_32a")) typedef ulong4 ulong4; 
#endif
#line 537 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
__pragma( warning(pop)) 
#if 0
typedef long4_16a 
#line 538
long4_16a; 
#endif
#line 539 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulong4_16a 
#line 539
ulong4_16a; 
#endif
#line 540 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef long4_32a 
#line 540
long4_32a; 
#endif
#line 541 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulong4_32a 
#line 541
ulong4_32a; 
#endif
#line 542 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef float1 
#line 542
float1; 
#endif
#line 543 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef float2 
#line 543
float2; 
#endif
#line 544 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef float3 
#line 544
float3; 
#endif
#line 545 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef float4 
#line 545
float4; 
#endif
#line 546 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef longlong1 
#line 546
longlong1; 
#endif
#line 547 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulonglong1 
#line 547
ulonglong1; 
#endif
#line 548 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef longlong2 
#line 548
longlong2; 
#endif
#line 549 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulonglong2 
#line 549
ulonglong2; 
#endif
#line 550 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef longlong3 
#line 550
longlong3; 
#endif
#line 551 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulonglong3 
#line 551
ulonglong3; 
#endif
#line 552 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#if 0
#line 553
__declspec(deprecated("use longlong4_16a or longlong4_32a")) typedef longlong4 longlong4; 
#endif
#line 554 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 554
__declspec(deprecated("use ulonglong4_16a or ulonglong4_32a")) typedef ulonglong4 ulonglong4; 
#endif
#line 555 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
__pragma( warning(pop)) 
#if 0
typedef longlong4_16a 
#line 556
longlong4_16a; 
#endif
#line 557 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulonglong4_16a 
#line 557
ulonglong4_16a; 
#endif
#line 558 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef longlong4_32a 
#line 558
longlong4_32a; 
#endif
#line 559 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef ulonglong4_32a 
#line 559
ulonglong4_32a; 
#endif
#line 560 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef double1 
#line 560
double1; 
#endif
#line 561 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef double2 
#line 561
double2; 
#endif
#line 562 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef double3 
#line 562
double3; 
#endif
#line 563 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#if 0
#line 564
__declspec(deprecated("use double4_16a or double4_32a")) typedef double4 double4; 
#endif
#line 565 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
__pragma( warning(pop)) 
#if 0
typedef double4_16a 
#line 566
double4_16a; 
#endif
#line 567 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef double4_32a 
#line 567
double4_32a; 
#endif
#line 579 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
#line 579
struct dim3 { 
#line 581
unsigned x, y, z; 
#line 596 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
}; 
#endif
#line 598 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_types.h"
#if 0
typedef dim3 
#line 598
dim3; 
#endif
#line 13 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\limits.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 16
__pragma( pack ( push, 8 )) extern "C" {
#line 74 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\limits.h"
}__pragma( pack ( pop )) 
#line 76
#pragma warning(pop)
#line 14 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stddef.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 18
__pragma( pack ( push, 8 )) extern "C" {
#line 23
namespace std { 
#line 25
typedef decltype(nullptr) nullptr_t; 
#line 26
}
#line 28
using std::nullptr_t;
#line 35 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stddef.h"
int *__cdecl _errno(); 
#line 38
errno_t __cdecl _set_errno(int _Value); 
#line 39
errno_t __cdecl _get_errno(int * _Value); 
#line 55 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stddef.h"
extern unsigned long __cdecl __threadid(); 
#line 57
extern uintptr_t __cdecl __threadhandle(); 
#line 61
}__pragma( pack ( pop )) 
#line 63
#pragma warning(pop)
#line 192 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 192
enum cudaError { 
#line 199
cudaSuccess, 
#line 205
cudaErrorInvalidValue, 
#line 211
cudaErrorMemoryAllocation, 
#line 217
cudaErrorInitializationError, 
#line 224
cudaErrorCudartUnloading, 
#line 231
cudaErrorProfilerDisabled, 
#line 239
cudaErrorProfilerNotInitialized, 
#line 246
cudaErrorProfilerAlreadyStarted, 
#line 253
cudaErrorProfilerAlreadyStopped, 
#line 261
cudaErrorInvalidConfiguration, 
#line 268
cudaErrorVersionTranslation, 
#line 274
cudaErrorInvalidPitchValue = 12, 
#line 280
cudaErrorInvalidSymbol, 
#line 288
cudaErrorInvalidHostPointer = 16, 
#line 296
cudaErrorInvalidDevicePointer, 
#line 301
cudaErrorInvalidTexture, 
#line 307
cudaErrorInvalidTextureBinding, 
#line 314
cudaErrorInvalidChannelDescriptor, 
#line 320
cudaErrorInvalidMemcpyDirection, 
#line 330
cudaErrorAddressOfConstant, 
#line 339
cudaErrorTextureFetchFailed, 
#line 348
cudaErrorTextureNotBound, 
#line 357
cudaErrorSynchronizationError, 
#line 362
cudaErrorInvalidFilterSetting, 
#line 368
cudaErrorInvalidNormSetting, 
#line 376
cudaErrorMixedDeviceExecution, 
#line 384
cudaErrorNotYetImplemented = 31, 
#line 393
cudaErrorMemoryValueTooLarge, 
#line 399
cudaErrorStubLibrary = 34, 
#line 406
cudaErrorInsufficientDriver, 
#line 413
cudaErrorCallRequiresNewerDriver, 
#line 419
cudaErrorInvalidSurface, 
#line 425
cudaErrorDuplicateVariableName = 43, 
#line 431
cudaErrorDuplicateTextureName, 
#line 437
cudaErrorDuplicateSurfaceName, 
#line 447
cudaErrorDevicesUnavailable, 
#line 460
cudaErrorIncompatibleDriverContext = 49, 
#line 466
cudaErrorMissingConfiguration = 52, 
#line 475
cudaErrorPriorLaunchFailure, 
#line 481
cudaErrorLaunchMaxDepthExceeded = 65, 
#line 489
cudaErrorLaunchFileScopedTex, 
#line 497
cudaErrorLaunchFileScopedSurf, 
#line 513
cudaErrorSyncDepthExceeded, 
#line 525
cudaErrorLaunchPendingCountExceeded, 
#line 531
cudaErrorInvalidDeviceFunction = 98, 
#line 537
cudaErrorNoDevice = 100, 
#line 544
cudaErrorInvalidDevice, 
#line 549
cudaErrorDeviceNotLicensed, 
#line 558
cudaErrorSoftwareValidityNotEstablished, 
#line 563
cudaErrorStartupFailure = 127, 
#line 568
cudaErrorInvalidKernelImage = 200, 
#line 578
cudaErrorDeviceUninitialized, 
#line 583
cudaErrorMapBufferObjectFailed = 205, 
#line 588
cudaErrorUnmapBufferObjectFailed, 
#line 594
cudaErrorArrayIsMapped, 
#line 599
cudaErrorAlreadyMapped, 
#line 607
cudaErrorNoKernelImageForDevice, 
#line 612
cudaErrorAlreadyAcquired, 
#line 617
cudaErrorNotMapped, 
#line 623
cudaErrorNotMappedAsArray, 
#line 629
cudaErrorNotMappedAsPointer, 
#line 635
cudaErrorECCUncorrectable, 
#line 641
cudaErrorUnsupportedLimit, 
#line 647
cudaErrorDeviceAlreadyInUse, 
#line 653
cudaErrorPeerAccessUnsupported, 
#line 659
cudaErrorInvalidPtx, 
#line 664
cudaErrorInvalidGraphicsContext, 
#line 670
cudaErrorNvlinkUncorrectable, 
#line 677
cudaErrorJitCompilerNotFound, 
#line 684
cudaErrorUnsupportedPtxVersion, 
#line 691
cudaErrorJitCompilationDisabled, 
#line 696
cudaErrorUnsupportedExecAffinity, 
#line 702
cudaErrorUnsupportedDevSideSync, 
#line 713
cudaErrorContained, 
#line 718
cudaErrorInvalidSource = 300, 
#line 723
cudaErrorFileNotFound, 
#line 728
cudaErrorSharedObjectSymbolNotFound, 
#line 733
cudaErrorSharedObjectInitFailed, 
#line 738
cudaErrorOperatingSystem, 
#line 745
cudaErrorInvalidResourceHandle = 400, 
#line 751
cudaErrorIllegalState, 
#line 759
cudaErrorLossyQuery, 
#line 766
cudaErrorSymbolNotFound = 500, 
#line 774
cudaErrorNotReady = 600, 
#line 782
cudaErrorIllegalAddress = 700, 
#line 791
cudaErrorLaunchOutOfResources, 
#line 802
cudaErrorLaunchTimeout, 
#line 808
cudaErrorLaunchIncompatibleTexturing, 
#line 815
cudaErrorPeerAccessAlreadyEnabled, 
#line 822
cudaErrorPeerAccessNotEnabled, 
#line 835
cudaErrorSetOnActiveProcess = 708, 
#line 842
cudaErrorContextIsDestroyed, 
#line 849
cudaErrorAssert, 
#line 856
cudaErrorTooManyPeers, 
#line 862
cudaErrorHostMemoryAlreadyRegistered, 
#line 868
cudaErrorHostMemoryNotRegistered, 
#line 877
cudaErrorHardwareStackError, 
#line 885
cudaErrorIllegalInstruction, 
#line 894
cudaErrorMisalignedAddress, 
#line 905
cudaErrorInvalidAddressSpace, 
#line 913
cudaErrorInvalidPc, 
#line 924
cudaErrorLaunchFailure, 
#line 933
cudaErrorCooperativeLaunchTooLarge, 
#line 941
cudaErrorTensorMemoryLeak, 
#line 946
cudaErrorNotPermitted = 800, 
#line 952
cudaErrorNotSupported, 
#line 961
cudaErrorSystemNotReady, 
#line 968
cudaErrorSystemDriverMismatch, 
#line 977
cudaErrorCompatNotSupportedOnDevice, 
#line 982
cudaErrorMpsConnectionFailed, 
#line 987
cudaErrorMpsRpcFailure, 
#line 993
cudaErrorMpsServerNotReady, 
#line 998
cudaErrorMpsMaxClientsReached, 
#line 1003
cudaErrorMpsMaxConnectionsReached, 
#line 1008
cudaErrorMpsClientTerminated, 
#line 1013
cudaErrorCdpNotSupported, 
#line 1018
cudaErrorCdpVersionMismatch, 
#line 1023
cudaErrorStreamCaptureUnsupported = 900, 
#line 1029
cudaErrorStreamCaptureInvalidated, 
#line 1035
cudaErrorStreamCaptureMerge, 
#line 1040
cudaErrorStreamCaptureUnmatched, 
#line 1046
cudaErrorStreamCaptureUnjoined, 
#line 1053
cudaErrorStreamCaptureIsolation, 
#line 1059
cudaErrorStreamCaptureImplicit, 
#line 1065
cudaErrorCapturedEvent, 
#line 1072
cudaErrorStreamCaptureWrongThread, 
#line 1077
cudaErrorTimeout, 
#line 1083
cudaErrorGraphExecUpdateFailure, 
#line 1096
cudaErrorExternalDevice, 
#line 1102
cudaErrorInvalidClusterSize, 
#line 1108
cudaErrorFunctionNotLoaded, 
#line 1114
cudaErrorInvalidResourceType, 
#line 1120
cudaErrorInvalidResourceConfiguration, 
#line 1127
cudaErrorStreamDetached = 917, 
#line 1131
cudaErrorGraphRecaptureFailure, 
#line 1136
cudaErrorUnknown = 999, 
#line 1144
cudaErrorApiFailureBase = 10000
#line 1145
}; 
#endif
#line 1150 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1150
enum cudaChannelFormatKind { 
#line 1152
cudaChannelFormatKindSigned, 
#line 1153
cudaChannelFormatKindUnsigned, 
#line 1154
cudaChannelFormatKindFloat, 
#line 1155
cudaChannelFormatKindNone, 
#line 1156
cudaChannelFormatKindNV12, 
#line 1157
cudaChannelFormatKindUnsignedNormalized8X1, 
#line 1158
cudaChannelFormatKindUnsignedNormalized8X2, 
#line 1159
cudaChannelFormatKindUnsignedNormalized8X4, 
#line 1160
cudaChannelFormatKindUnsignedNormalized16X1, 
#line 1161
cudaChannelFormatKindUnsignedNormalized16X2, 
#line 1162
cudaChannelFormatKindUnsignedNormalized16X4, 
#line 1163
cudaChannelFormatKindSignedNormalized8X1, 
#line 1164
cudaChannelFormatKindSignedNormalized8X2, 
#line 1165
cudaChannelFormatKindSignedNormalized8X4, 
#line 1166
cudaChannelFormatKindSignedNormalized16X1, 
#line 1167
cudaChannelFormatKindSignedNormalized16X2, 
#line 1168
cudaChannelFormatKindSignedNormalized16X4, 
#line 1169
cudaChannelFormatKindUnsignedBlockCompressed1, 
#line 1170
cudaChannelFormatKindUnsignedBlockCompressed1SRGB, 
#line 1171
cudaChannelFormatKindUnsignedBlockCompressed2, 
#line 1172
cudaChannelFormatKindUnsignedBlockCompressed2SRGB, 
#line 1173
cudaChannelFormatKindUnsignedBlockCompressed3, 
#line 1174
cudaChannelFormatKindUnsignedBlockCompressed3SRGB, 
#line 1175
cudaChannelFormatKindUnsignedBlockCompressed4, 
#line 1176
cudaChannelFormatKindSignedBlockCompressed4, 
#line 1177
cudaChannelFormatKindUnsignedBlockCompressed5, 
#line 1178
cudaChannelFormatKindSignedBlockCompressed5, 
#line 1179
cudaChannelFormatKindUnsignedBlockCompressed6H, 
#line 1180
cudaChannelFormatKindSignedBlockCompressed6H, 
#line 1181
cudaChannelFormatKindUnsignedBlockCompressed7, 
#line 1182
cudaChannelFormatKindUnsignedBlockCompressed7SRGB, 
#line 1183
cudaChannelFormatKindUnsignedNormalized1010102, 
#line 1184
cudaChannelFormatKindUnsigned8Packed422, 
#line 1185
cudaChannelFormatKindUnsigned8Packed444, 
#line 1186
cudaChannelFormatKindUnsigned8SemiPlanar420, 
#line 1187
cudaChannelFormatKindUnsigned16SemiPlanar420, 
#line 1188
cudaChannelFormatKindUnsigned8SemiPlanar422, 
#line 1189
cudaChannelFormatKindUnsigned16SemiPlanar422, 
#line 1190
cudaChannelFormatKindUnsigned8SemiPlanar444, 
#line 1191
cudaChannelFormatKindUnsigned16SemiPlanar444, 
#line 1192
cudaChannelFormatKindUnsigned8Planar420, 
#line 1193
cudaChannelFormatKindUnsigned16Planar420, 
#line 1194
cudaChannelFormatKindUnsigned8Planar422, 
#line 1195
cudaChannelFormatKindUnsigned16Planar422, 
#line 1196
cudaChannelFormatKindUnsigned8Planar444, 
#line 1197
cudaChannelFormatKindUnsigned16Planar444
#line 1199
}; 
#endif
#line 1205 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUdevResourceDesc_st *
#line 1205
cudaDevResourceDesc_t; 
#endif
#line 1210 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct cudaExecutionContext_st *
#line 1210
cudaExecutionContext_t; 
#endif
#line 1215 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1215
struct cudaChannelFormatDesc { 
#line 1217
int x; 
#line 1218
int y; 
#line 1219
int z; 
#line 1220
int w; 
#line 1221
cudaChannelFormatKind f; 
#line 1222
}; 
#endif
#line 1227 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
typedef struct cudaArray *cudaArray_t; 
#line 1232
typedef const cudaArray *cudaArray_const_t; 
#line 1234
struct cudaArray; 
#line 1239
typedef struct cudaMipmappedArray *cudaMipmappedArray_t; 
#line 1244
typedef const cudaMipmappedArray *cudaMipmappedArray_const_t; 
#line 1246
struct cudaMipmappedArray; 
#line 1256
#if 0
#line 1256
struct cudaArraySparseProperties { 
#line 1257
struct { 
#line 1258
unsigned width; 
#line 1259
unsigned height; 
#line 1260
unsigned depth; 
#line 1261
} tileExtent; 
#line 1262
unsigned miptailFirstLevel; 
#line 1263
unsigned __int64 miptailSize; 
#line 1264
unsigned flags; 
#line 1265
unsigned reserved[4]; 
#line 1266
}; 
#endif
#line 1271 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1271
struct cudaArrayMemoryRequirements { 
#line 1272
size_t size; 
#line 1273
size_t alignment; 
#line 1274
unsigned reserved[4]; 
#line 1275
}; 
#endif
#line 1280 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1280
enum cudaMemoryType { 
#line 1282
cudaMemoryTypeUnregistered, 
#line 1283
cudaMemoryTypeHost, 
#line 1284
cudaMemoryTypeDevice, 
#line 1285
cudaMemoryTypeManaged
#line 1286
}; 
#endif
#line 1291 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1291
enum cudaMemcpyKind { 
#line 1293
cudaMemcpyHostToHost, 
#line 1294
cudaMemcpyHostToDevice, 
#line 1295
cudaMemcpyDeviceToHost, 
#line 1296
cudaMemcpyDeviceToDevice, 
#line 1297
cudaMemcpyDefault
#line 1298
}; 
#endif
#line 1305 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1305
struct cudaPitchedPtr { 
#line 1307
void *ptr; 
#line 1308
size_t pitch; 
#line 1309
size_t xsize; 
#line 1310
size_t ysize; 
#line 1311
}; 
#endif
#line 1318 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1318
struct cudaExtent { 
#line 1320
size_t width; 
#line 1321
size_t height; 
#line 1322
size_t depth; 
#line 1323
}; 
#endif
#line 1330 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1330
struct cudaPos { 
#line 1332
size_t x; 
#line 1333
size_t y; 
#line 1334
size_t z; 
#line 1335
}; 
#endif
#line 1340 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1340
struct cudaMemcpy3DParms { 
#line 1342
cudaArray_t srcArray; 
#line 1343
cudaPos srcPos; 
#line 1344
cudaPitchedPtr srcPtr; 
#line 1346
cudaArray_t dstArray; 
#line 1347
cudaPos dstPos; 
#line 1348
cudaPitchedPtr dstPtr; 
#line 1350
cudaExtent extent; 
#line 1351
cudaMemcpyKind kind; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 1352
}; 
#endif
#line 1357 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1357
struct cudaMemcpyNodeParams { 
#line 1358
int flags; 
#line 1359
int reserved; 
#line 1360
cudaExecutionContext_t ctx; 
#line 1361
cudaMemcpy3DParms copyParams; 
#line 1362
}; 
#endif
#line 1367 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1367
struct cudaMemcpy3DPeerParms { 
#line 1369
cudaArray_t srcArray; 
#line 1370
cudaPos srcPos; 
#line 1371
cudaPitchedPtr srcPtr; 
#line 1372
int srcDevice; 
#line 1374
cudaArray_t dstArray; 
#line 1375
cudaPos dstPos; 
#line 1376
cudaPitchedPtr dstPtr; 
#line 1377
int dstDevice; 
#line 1379
cudaExtent extent; 
#line 1380
}; 
#endif
#line 1385 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1385
struct cudaMemsetParams { 
#line 1386
void *dst; 
#line 1387
size_t pitch; 
#line 1388
unsigned value; 
#line 1389
unsigned elementSize; 
#line 1390
size_t width; 
#line 1391
size_t height; 
#line 1392
}; 
#endif
#line 1397 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1397
struct cudaMemsetParamsV2 { 
#line 1398
void *dst; 
#line 1399
size_t pitch; 
#line 1400
unsigned value; 
#line 1401
unsigned elementSize; 
#line 1402
size_t width; 
#line 1403
size_t height; 
#line 1404
cudaExecutionContext_t ctx; 
#line 1405
}; 
#endif
#line 1410 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1410
enum cudaAccessProperty { 
#line 1411
cudaAccessPropertyNormal, 
#line 1412
cudaAccessPropertyStreaming, 
#line 1413
cudaAccessPropertyPersisting
#line 1414
}; 
#endif
#line 1427 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1427
struct cudaAccessPolicyWindow { 
#line 1428
void *base_ptr; 
#line 1429
size_t num_bytes; 
#line 1430
float hitRatio; 
#line 1431
cudaAccessProperty hitProp; 
#line 1432
cudaAccessProperty missProp; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 1433
}; 
#endif
#line 1445 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
typedef void (__stdcall *cudaHostFn_t)(void * userData); 
#line 1450
#if 0
#line 1450
struct cudaHostNodeParams { 
#line 1451
cudaHostFn_t fn; 
#line 1452
void *userData; 
#line 1453
}; 
#endif
#line 1458 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1458
struct cudaHostNodeParamsV2 { 
#line 1459
cudaHostFn_t fn; 
#line 1460
void *userData; 
#line 1461
unsigned syncMode; 
#line 1462
}; 
#endif
#line 1467 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1467
enum cudaStreamCaptureStatus { 
#line 1468
cudaStreamCaptureStatusNone, 
#line 1469
cudaStreamCaptureStatusActive, 
#line 1470
cudaStreamCaptureStatusInvalidated
#line 1472
}; 
#endif
#line 1477 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1477
enum cudaGraphRecaptureStatus { 
#line 1478
cudaGraphRecaptureEligibleForUpdate, 
#line 1479
cudaGraphRecaptureIneligibleForUpdate, 
#line 1480
cudaGraphRecaptureError
#line 1481
}; 
#endif
#line 1487 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1487
enum cudaStreamCaptureMode { 
#line 1488
cudaStreamCaptureModeGlobal, 
#line 1489
cudaStreamCaptureModeThreadLocal, 
#line 1490
cudaStreamCaptureModeRelaxed
#line 1491
}; 
#endif
#line 1493 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1493
enum cudaSynchronizationPolicy { 
#line 1494
cudaSyncPolicyAuto = 1, 
#line 1495
cudaSyncPolicySpin, 
#line 1496
cudaSyncPolicyYield, 
#line 1497
cudaSyncPolicyBlockingSync
#line 1498
}; 
#endif
#line 1503 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1503
enum cudaClusterSchedulingPolicy { 
#line 1504
cudaClusterSchedulingPolicyDefault, 
#line 1505
cudaClusterSchedulingPolicySpread, 
#line 1506
cudaClusterSchedulingPolicyLoadBalancing
#line 1507
}; 
#endif
#line 1512 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1512
enum cudaStreamUpdateCaptureDependenciesFlags { 
#line 1513
cudaStreamAddCaptureDependencies, 
#line 1514
cudaStreamSetCaptureDependencies
#line 1515
}; 
#endif
#line 1520 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1520
enum cudaUserObjectFlags { 
#line 1521
cudaUserObjectNoDestructorSync = 1
#line 1522
}; 
#endif
#line 1527 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1527
enum cudaUserObjectRetainFlags { 
#line 1528
cudaGraphUserObjectMove = 1
#line 1529
}; 
#endif
#line 1534 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1534
enum cudaHostTaskSyncMode { 
#line 1535
cudaHostTaskBlocking, 
#line 1536
cudaHostTaskSpinWait
#line 1537
}; 
#endif
#line 1542 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
struct cudaGraphicsResource; 
#line 1547
#if 0
#line 1547
enum cudaGraphicsRegisterFlags { 
#line 1549
cudaGraphicsRegisterFlagsNone, 
#line 1550
cudaGraphicsRegisterFlagsReadOnly, 
#line 1551
cudaGraphicsRegisterFlagsWriteDiscard, 
#line 1552
cudaGraphicsRegisterFlagsSurfaceLoadStore = 4, 
#line 1553
cudaGraphicsRegisterFlagsTextureGather = 8
#line 1554
}; 
#endif
#line 1559 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1559
enum cudaGraphicsMapFlags { 
#line 1561
cudaGraphicsMapFlagsNone, 
#line 1562
cudaGraphicsMapFlagsReadOnly, 
#line 1563
cudaGraphicsMapFlagsWriteDiscard
#line 1564
}; 
#endif
#line 1569 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1569
enum cudaGraphicsCubeFace { 
#line 1571
cudaGraphicsCubeFacePositiveX, 
#line 1572
cudaGraphicsCubeFaceNegativeX, 
#line 1573
cudaGraphicsCubeFacePositiveY, 
#line 1574
cudaGraphicsCubeFaceNegativeY, 
#line 1575
cudaGraphicsCubeFacePositiveZ, 
#line 1576
cudaGraphicsCubeFaceNegativeZ
#line 1577
}; 
#endif
#line 1582 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1582
enum cudaResourceType { 
#line 1584
cudaResourceTypeArray, 
#line 1585
cudaResourceTypeMipmappedArray, 
#line 1586
cudaResourceTypeLinear, 
#line 1587
cudaResourceTypePitch2D
#line 1588
}; 
#endif
#line 1593 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1593
enum cudaResourceViewFormat { 
#line 1595
cudaResViewFormatNone, 
#line 1596
cudaResViewFormatUnsignedChar1, 
#line 1597
cudaResViewFormatUnsignedChar2, 
#line 1598
cudaResViewFormatUnsignedChar4, 
#line 1599
cudaResViewFormatSignedChar1, 
#line 1600
cudaResViewFormatSignedChar2, 
#line 1601
cudaResViewFormatSignedChar4, 
#line 1602
cudaResViewFormatUnsignedShort1, 
#line 1603
cudaResViewFormatUnsignedShort2, 
#line 1604
cudaResViewFormatUnsignedShort4, 
#line 1605
cudaResViewFormatSignedShort1, 
#line 1606
cudaResViewFormatSignedShort2, 
#line 1607
cudaResViewFormatSignedShort4, 
#line 1608
cudaResViewFormatUnsignedInt1, 
#line 1609
cudaResViewFormatUnsignedInt2, 
#line 1610
cudaResViewFormatUnsignedInt4, 
#line 1611
cudaResViewFormatSignedInt1, 
#line 1612
cudaResViewFormatSignedInt2, 
#line 1613
cudaResViewFormatSignedInt4, 
#line 1614
cudaResViewFormatHalf1, 
#line 1615
cudaResViewFormatHalf2, 
#line 1616
cudaResViewFormatHalf4, 
#line 1617
cudaResViewFormatFloat1, 
#line 1618
cudaResViewFormatFloat2, 
#line 1619
cudaResViewFormatFloat4, 
#line 1620
cudaResViewFormatUnsignedBlockCompressed1, 
#line 1621
cudaResViewFormatUnsignedBlockCompressed2, 
#line 1622
cudaResViewFormatUnsignedBlockCompressed3, 
#line 1623
cudaResViewFormatUnsignedBlockCompressed4, 
#line 1624
cudaResViewFormatSignedBlockCompressed4, 
#line 1625
cudaResViewFormatUnsignedBlockCompressed5, 
#line 1626
cudaResViewFormatSignedBlockCompressed5, 
#line 1627
cudaResViewFormatUnsignedBlockCompressed6H, 
#line 1628
cudaResViewFormatSignedBlockCompressed6H, 
#line 1629
cudaResViewFormatUnsignedBlockCompressed7
#line 1630
}; 
#endif
#line 1635 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1635
struct cudaResourceDesc { 
#line 1636
cudaResourceType resType; 
#line 1638
union { 
#line 1639
struct { 
#line 1640
cudaArray_t array; 
#line 1641
} array; 
#line 1642
struct { 
#line 1643
cudaMipmappedArray_t mipmap; 
#line 1644
} mipmap; 
#line 1645
struct { 
#line 1646
void *devPtr; 
#line 1647
cudaChannelFormatDesc desc; 
#line 1648
size_t sizeInBytes; 
#line 1649
} linear; 
#line 1650
struct { 
#line 1651
void *devPtr; 
#line 1652
cudaChannelFormatDesc desc; 
#line 1653
size_t width; 
#line 1654
size_t height; 
#line 1655
size_t pitchInBytes; 
#line 1656
} pitch2D; 
#line 1657
struct { 
#line 1658
int reserved[32]; 
#line 1659
} reserved; 
#line 1660
} res; 
#line 1662
unsigned flags; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 1663
}; 
#endif
#line 1668 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1668
struct cudaResourceViewDesc { 
#line 1670
cudaResourceViewFormat format; 
#line 1671
size_t width; 
#line 1672
size_t height; 
#line 1673
size_t depth; 
#line 1674
unsigned firstMipmapLevel; 
#line 1675
unsigned lastMipmapLevel; 
#line 1676
unsigned firstLayer; 
#line 1677
unsigned lastLayer; 
#line 1678
unsigned reserved[16]; 
#line 1679
}; 
#endif
#line 1689 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 1684
enum cudaSharedMemoryMode { 
#line 1685
cudaSharedMemoryModeDefault, 
#line 1687
cudaSharedMemoryModeRequirePortable, 
#line 1688
cudaSharedMemoryModeAllowNonPortable
#line 1689
} cudaSharedMemoryMode; 
#endif
#line 1694 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1694
struct cudaPointerAttributes { 
#line 1700
cudaMemoryType type; 
#line 1711
int device; 
#line 1717
void *devicePointer; 
#line 1726
void *hostPointer; 
#line 1731
long reserved[8]; 
#line 1732
}; 
#endif
#line 1737 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1737
struct cudaFuncAttributes { 
#line 1744
size_t sharedSizeBytes; 
#line 1750
size_t constSizeBytes; 
#line 1755
size_t localSizeBytes; 
#line 1762
int maxThreadsPerBlock; 
#line 1767
int numRegs; 
#line 1774
int ptxVersion; 
#line 1781
int binaryVersion; 
#line 1787
int cacheModeCA; 
#line 1794
int maxDynamicSharedSizeBytes; 
#line 1803
int preferredShmemCarveout; 
#line 1809
int clusterDimMustBeSet; 
#line 1820
int requiredClusterWidth; 
#line 1821
int requiredClusterHeight; 
#line 1822
int requiredClusterDepth; 
#line 1828
int clusterSchedulingPolicyPreference; 
#line 1850
int nonPortableClusterSizeAllowed; 
#line 1856
int deviceNodeUpdateStatus; 
#line 1858
int reserved1; 
#line 1863
int reserved[14]; 
#line 1864
}; 
#endif
#line 1869 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1869
enum cudaFuncAttribute { 
#line 1871
cudaFuncAttributeMaxDynamicSharedMemorySize = 8, 
#line 1872
cudaFuncAttributePreferredSharedMemoryCarveout, 
#line 1873
cudaFuncAttributeClusterDimMustBeSet, 
#line 1874
cudaFuncAttributeRequiredClusterWidth, 
#line 1875
cudaFuncAttributeRequiredClusterHeight, 
#line 1876
cudaFuncAttributeRequiredClusterDepth, 
#line 1877
cudaFuncAttributeNonPortableClusterSizeAllowed, 
#line 1878
cudaFuncAttributeClusterSchedulingPolicyPreference, 
#line 1879
cudaFuncAttributeMax
#line 1880
}; 
#endif
#line 1885 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1885
enum cudaFuncCache { 
#line 1887
cudaFuncCachePreferNone, 
#line 1888
cudaFuncCachePreferShared, 
#line 1889
cudaFuncCachePreferL1, 
#line 1890
cudaFuncCachePreferEqual
#line 1891
}; 
#endif
#line 1897 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1897
enum cudaSharedMemConfig { 
#line 1899
cudaSharedMemBankSizeDefault, 
#line 1900
cudaSharedMemBankSizeFourByte, 
#line 1901
cudaSharedMemBankSizeEightByte
#line 1902
}; 
#endif
#line 1907 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1907
enum cudaSharedCarveout { 
#line 1908
cudaSharedmemCarveoutDefault = (-1), 
#line 1909
cudaSharedmemCarveoutMaxShared = 100, 
#line 1910
cudaSharedmemCarveoutMaxL1 = 0
#line 1911
}; 
#endif
#line 1916 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1916
enum cudaComputeMode { 
#line 1918
cudaComputeModeDefault, 
#line 1919
cudaComputeModeExclusive, 
#line 1920
cudaComputeModeProhibited, 
#line 1921
cudaComputeModeExclusiveProcess
#line 1922
}; 
#endif
#line 1927 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1927
enum cudaLimit { 
#line 1929
cudaLimitStackSize, 
#line 1930
cudaLimitPrintfFifoSize, 
#line 1931
cudaLimitMallocHeapSize, 
#line 1932
cudaLimitDevRuntimeSyncDepth, 
#line 1933
cudaLimitDevRuntimePendingLaunchCount, 
#line 1934
cudaLimitMaxL2FetchGranularity, 
#line 1935
cudaLimitPersistingL2CacheSize
#line 1936
}; 
#endif
#line 1941 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1941
enum cudaMemoryAdvise { 
#line 1943
cudaMemAdviseSetReadMostly = 1, 
#line 1944
cudaMemAdviseUnsetReadMostly, 
#line 1945
cudaMemAdviseSetPreferredLocation, 
#line 1946
cudaMemAdviseUnsetPreferredLocation, 
#line 1947
cudaMemAdviseSetAccessedBy, 
#line 1948
cudaMemAdviseUnsetAccessedBy
#line 1949
}; 
#endif
#line 1954 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1954
enum cudaMemRangeAttribute { 
#line 1956
cudaMemRangeAttributeReadMostly = 1, 
#line 1957
cudaMemRangeAttributePreferredLocation, 
#line 1958
cudaMemRangeAttributeAccessedBy, 
#line 1959
cudaMemRangeAttributeLastPrefetchLocation, 
#line 1960
cudaMemRangeAttributePreferredLocationType, 
#line 1961
cudaMemRangeAttributePreferredLocationId, 
#line 1962
cudaMemRangeAttributeLastPrefetchLocationType, 
#line 1963
cudaMemRangeAttributeLastPrefetchLocationId
#line 1964
}; 
#endif
#line 1969 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1969
enum cudaFlushGPUDirectRDMAWritesOptions { 
#line 1970
cudaFlushGPUDirectRDMAWritesOptionHost = (1 << 0), 
#line 1971
cudaFlushGPUDirectRDMAWritesOptionMemOps
#line 1972
}; 
#endif
#line 1977 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1977
enum cudaGPUDirectRDMAWritesOrdering { 
#line 1978
cudaGPUDirectRDMAWritesOrderingNone, 
#line 1979
cudaGPUDirectRDMAWritesOrderingOwner = 100, 
#line 1980
cudaGPUDirectRDMAWritesOrderingAllDevices = 200
#line 1981
}; 
#endif
#line 1986 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1986
enum cudaFlushGPUDirectRDMAWritesScope { 
#line 1987
cudaFlushGPUDirectRDMAWritesToOwner = 100, 
#line 1988
cudaFlushGPUDirectRDMAWritesToAllDevices = 200
#line 1989
}; 
#endif
#line 1994 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 1994
enum cudaFlushGPUDirectRDMAWritesTarget { 
#line 1995
cudaFlushGPUDirectRDMAWritesTargetCurrentDevice
#line 1996
}; 
#endif
#line 2002 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2002
enum cudaDeviceAttr { 
#line 2004
cudaDevAttrMaxThreadsPerBlock = 1, 
#line 2005
cudaDevAttrMaxBlockDimX, 
#line 2006
cudaDevAttrMaxBlockDimY, 
#line 2007
cudaDevAttrMaxBlockDimZ, 
#line 2008
cudaDevAttrMaxGridDimX, 
#line 2009
cudaDevAttrMaxGridDimY, 
#line 2010
cudaDevAttrMaxGridDimZ, 
#line 2011
cudaDevAttrMaxSharedMemoryPerBlock, 
#line 2012
cudaDevAttrTotalConstantMemory, 
#line 2013
cudaDevAttrWarpSize, 
#line 2014
cudaDevAttrMaxPitch, 
#line 2015
cudaDevAttrMaxRegistersPerBlock, 
#line 2016
cudaDevAttrClockRate, 
#line 2017
cudaDevAttrTextureAlignment, 
#line 2018
cudaDevAttrGpuOverlap, 
#line 2019
cudaDevAttrMultiProcessorCount, 
#line 2020
cudaDevAttrKernelExecTimeout, 
#line 2021
cudaDevAttrIntegrated, 
#line 2022
cudaDevAttrCanMapHostMemory, 
#line 2023
cudaDevAttrComputeMode, 
#line 2024
cudaDevAttrMaxTexture1DWidth, 
#line 2025
cudaDevAttrMaxTexture2DWidth, 
#line 2026
cudaDevAttrMaxTexture2DHeight, 
#line 2027
cudaDevAttrMaxTexture3DWidth, 
#line 2028
cudaDevAttrMaxTexture3DHeight, 
#line 2029
cudaDevAttrMaxTexture3DDepth, 
#line 2030
cudaDevAttrMaxTexture2DLayeredWidth, 
#line 2031
cudaDevAttrMaxTexture2DLayeredHeight, 
#line 2032
cudaDevAttrMaxTexture2DLayeredLayers, 
#line 2033
cudaDevAttrSurfaceAlignment, 
#line 2034
cudaDevAttrConcurrentKernels, 
#line 2035
cudaDevAttrEccEnabled, 
#line 2036
cudaDevAttrPciBusId, 
#line 2037
cudaDevAttrPciDeviceId, 
#line 2038
cudaDevAttrTccDriver, 
#line 2039
cudaDevAttrMemoryClockRate, 
#line 2040
cudaDevAttrGlobalMemoryBusWidth, 
#line 2041
cudaDevAttrL2CacheSize, 
#line 2042
cudaDevAttrMaxThreadsPerMultiProcessor, 
#line 2043
cudaDevAttrAsyncEngineCount, 
#line 2044
cudaDevAttrUnifiedAddressing, 
#line 2045
cudaDevAttrMaxTexture1DLayeredWidth, 
#line 2046
cudaDevAttrMaxTexture1DLayeredLayers, 
#line 2047
cudaDevAttrMaxTexture2DGatherWidth = 45, 
#line 2048
cudaDevAttrMaxTexture2DGatherHeight, 
#line 2049
cudaDevAttrMaxTexture3DWidthAlt, 
#line 2050
cudaDevAttrMaxTexture3DHeightAlt, 
#line 2051
cudaDevAttrMaxTexture3DDepthAlt, 
#line 2052
cudaDevAttrPciDomainId, 
#line 2053
cudaDevAttrTexturePitchAlignment, 
#line 2054
cudaDevAttrMaxTextureCubemapWidth, 
#line 2055
cudaDevAttrMaxTextureCubemapLayeredWidth, 
#line 2056
cudaDevAttrMaxTextureCubemapLayeredLayers, 
#line 2057
cudaDevAttrMaxSurface1DWidth, 
#line 2058
cudaDevAttrMaxSurface2DWidth, 
#line 2059
cudaDevAttrMaxSurface2DHeight, 
#line 2060
cudaDevAttrMaxSurface3DWidth, 
#line 2061
cudaDevAttrMaxSurface3DHeight, 
#line 2062
cudaDevAttrMaxSurface3DDepth, 
#line 2063
cudaDevAttrMaxSurface1DLayeredWidth, 
#line 2064
cudaDevAttrMaxSurface1DLayeredLayers, 
#line 2065
cudaDevAttrMaxSurface2DLayeredWidth, 
#line 2066
cudaDevAttrMaxSurface2DLayeredHeight, 
#line 2067
cudaDevAttrMaxSurface2DLayeredLayers, 
#line 2068
cudaDevAttrMaxSurfaceCubemapWidth, 
#line 2069
cudaDevAttrMaxSurfaceCubemapLayeredWidth, 
#line 2070
cudaDevAttrMaxSurfaceCubemapLayeredLayers, 
#line 2071
cudaDevAttrMaxTexture1DLinearWidth, 
#line 2072
cudaDevAttrMaxTexture2DLinearWidth, 
#line 2073
cudaDevAttrMaxTexture2DLinearHeight, 
#line 2074
cudaDevAttrMaxTexture2DLinearPitch, 
#line 2075
cudaDevAttrMaxTexture2DMipmappedWidth, 
#line 2076
cudaDevAttrMaxTexture2DMipmappedHeight, 
#line 2077
cudaDevAttrComputeCapabilityMajor, 
#line 2078
cudaDevAttrComputeCapabilityMinor, 
#line 2079
cudaDevAttrMaxTexture1DMipmappedWidth, 
#line 2080
cudaDevAttrStreamPrioritiesSupported, 
#line 2081
cudaDevAttrGlobalL1CacheSupported, 
#line 2082
cudaDevAttrLocalL1CacheSupported, 
#line 2083
cudaDevAttrMaxSharedMemoryPerMultiprocessor, 
#line 2084
cudaDevAttrMaxRegistersPerMultiprocessor, 
#line 2085
cudaDevAttrManagedMemory, 
#line 2086
cudaDevAttrIsMultiGpuBoard, 
#line 2087
cudaDevAttrMultiGpuBoardGroupID, 
#line 2088
cudaDevAttrHostNativeAtomicSupported, 
#line 2089
cudaDevAttrSingleToDoublePrecisionPerfRatio, 
#line 2090
cudaDevAttrPageableMemoryAccess, 
#line 2091
cudaDevAttrConcurrentManagedAccess, 
#line 2092
cudaDevAttrComputePreemptionSupported, 
#line 2093
cudaDevAttrCanUseHostPointerForRegisteredMem, 
#line 2094
cudaDevAttrReserved92, 
#line 2095
cudaDevAttrReserved93, 
#line 2096
cudaDevAttrReserved94, 
#line 2097
cudaDevAttrCooperativeLaunch, 
#line 2098
cudaDevAttrReserved96, 
#line 2099
cudaDevAttrMaxSharedMemoryPerBlockOptin, 
#line 2100
cudaDevAttrCanFlushRemoteWrites, 
#line 2101
cudaDevAttrHostRegisterSupported, 
#line 2102
cudaDevAttrPageableMemoryAccessUsesHostPageTables, 
#line 2103
cudaDevAttrDirectManagedMemAccessFromHost, 
#line 2104
cudaDevAttrMaxBlocksPerMultiprocessor = 106, 
#line 2105
cudaDevAttrMaxPersistingL2CacheSize = 108, 
#line 2106
cudaDevAttrMaxAccessPolicyWindowSize, 
#line 2107
cudaDevAttrReservedSharedMemoryPerBlock = 111, 
#line 2108
cudaDevAttrSparseCudaArraySupported, 
#line 2109
cudaDevAttrHostRegisterReadOnlySupported, 
#line 2110
cudaDevAttrTimelineSemaphoreInteropSupported, 
#line 2111
cudaDevAttrMemoryPoolsSupported, 
#line 2112
cudaDevAttrGPUDirectRDMASupported, 
#line 2113
cudaDevAttrGPUDirectRDMAFlushWritesOptions, 
#line 2114
cudaDevAttrGPUDirectRDMAWritesOrdering, 
#line 2115
cudaDevAttrMemoryPoolSupportedHandleTypes, 
#line 2116
cudaDevAttrClusterLaunch, 
#line 2117
cudaDevAttrDeferredMappingCudaArraySupported, 
#line 2118
cudaDevAttrReserved122, 
#line 2119
cudaDevAttrReserved123, 
#line 2120
cudaDevAttrReserved124, 
#line 2121
cudaDevAttrIpcEventSupport, 
#line 2122
cudaDevAttrMemSyncDomainCount, 
#line 2123
cudaDevAttrReserved127, 
#line 2124
cudaDevAttrReserved128, 
#line 2125
cudaDevAttrReserved129, 
#line 2126
cudaDevAttrNumaConfig, 
#line 2127
cudaDevAttrNumaId, 
#line 2128
cudaDevAttrReserved132, 
#line 2129
cudaDevAttrMpsEnabled, 
#line 2130
cudaDevAttrHostNumaId, 
#line 2131
cudaDevAttrD3D12CigSupported, 
#line 2132
cudaDevAttrVulkanCigSupported = 138, 
#line 2133
cudaDevAttrGpuPciDeviceId, 
#line 2134
cudaDevAttrGpuPciSubsystemId, 
#line 2135
cudaDevAttrReserved141, 
#line 2136
cudaDevAttrHostNumaMemoryPoolsSupported, 
#line 2137
cudaDevAttrHostNumaMultinodeIpcSupported, 
#line 2138
cudaDevAttrHostMemoryPoolsSupported, 
#line 2139
cudaDevAttrReserved145, 
#line 2140
cudaDevAttrOnlyPartialHostNativeAtomicSupported = 147, 
#line 2141
cudaDevAttrAtomicReductionSupported, 
#line 2142
cudaDevAttrCigStreamsSupported = 151, 
#line 2144
cudaDevAttrMax
#line 2145
}; 
#endif
#line 2150 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2150
enum cudaMemPoolAttr { 
#line 2160
cudaMemPoolReuseFollowEventDependencies = 1, 
#line 2167
cudaMemPoolReuseAllowOpportunistic, 
#line 2175
cudaMemPoolReuseAllowInternalDependencies, 
#line 2186
cudaMemPoolAttrReleaseThreshold, 
#line 2192
cudaMemPoolAttrReservedMemCurrent, 
#line 2199
cudaMemPoolAttrReservedMemHigh, 
#line 2205
cudaMemPoolAttrUsedMemCurrent, 
#line 2212
cudaMemPoolAttrUsedMemHigh, 
#line 2217
cudaMemPoolAttrAllocationType, 
#line 2225
cudaMemPoolAttrExportHandleTypes, 
#line 2232
cudaMemPoolAttrLocationId, 
#line 2240
cudaMemPoolAttrLocationType, 
#line 2249
cudaMemPoolAttrMaxPoolSize, 
#line 2255
cudaMemPoolAttrHwDecompressEnabled
#line 2256
}; 
#endif
#line 2261 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2261
enum cudaMemLocationType { 
#line 2262
cudaMemLocationTypeInvalid, 
#line 2263
cudaMemLocationTypeNone = 0, 
#line 2264
cudaMemLocationTypeDevice, 
#line 2265
cudaMemLocationTypeHost, 
#line 2266
cudaMemLocationTypeHostNuma, 
#line 2267
cudaMemLocationTypeHostNumaCurrent, 
#line 2268
cudaMemLocationTypeInvisible
#line 2269
}; 
#endif
#line 2277 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2277
struct cudaMemLocation { 
#line 2278
cudaMemLocationType type; 
#line 2279
union { 
#line 2280
int id; 
#line 2281
}; 
#line 2282
}; 
#endif
#line 2287 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2287
enum cudaMemAccessFlags { 
#line 2288
cudaMemAccessFlagsProtNone, 
#line 2289
cudaMemAccessFlagsProtRead, 
#line 2290
cudaMemAccessFlagsProtReadWrite = 3
#line 2291
}; 
#endif
#line 2296 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2296
struct cudaMemAccessDesc { 
#line 2297
cudaMemLocation location; 
#line 2298
cudaMemAccessFlags flags; 
#line 2299
}; 
#endif
#line 2304 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2304
enum cudaMemAllocationType { 
#line 2305
cudaMemAllocationTypeInvalid, 
#line 2309
cudaMemAllocationTypePinned, 
#line 2312
cudaMemAllocationTypeManaged, 
#line 2313
cudaMemAllocationTypeMax = 2147483647
#line 2314
}; 
#endif
#line 2319 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2319
enum cudaMemAllocationHandleType { 
#line 2320
cudaMemHandleTypeNone, 
#line 2321
cudaMemHandleTypePosixFileDescriptor, 
#line 2322
cudaMemHandleTypeWin32, 
#line 2323
cudaMemHandleTypeWin32Kmt = 4, 
#line 2324
cudaMemHandleTypeFabric = 8
#line 2325
}; 
#endif
#line 2336 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2336
struct cudaMemPoolProps { 
#line 2337
cudaMemAllocationType allocType; 
#line 2338
cudaMemAllocationHandleType handleTypes; 
#line 2339
cudaMemLocation location; 
#line 2346
void *win32SecurityAttributes; 
#line 2347
size_t maxSize; 
#line 2348
unsigned short usage; 
#line 2349
unsigned char reserved[54]; 
#line 2350
}; 
#endif
#line 2355 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2355
struct cudaMemPoolPtrExportData { 
#line 2356
unsigned char reserved[64]; 
#line 2357
}; 
#endif
#line 2362 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2362
struct cudaMemAllocNodeParams { 
#line 2367
cudaMemPoolProps poolProps; 
#line 2368
const cudaMemAccessDesc *accessDescs; 
#line 2369
size_t accessDescCount; 
#line 2370
size_t bytesize; 
#line 2371
void *dptr; 
#line 2372
}; 
#endif
#line 2377 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2377
struct cudaMemAllocNodeParamsV2 { 
#line 2382
cudaMemPoolProps poolProps; 
#line 2383
const cudaMemAccessDesc *accessDescs; 
#line 2384
size_t accessDescCount; 
#line 2385
size_t bytesize; 
#line 2386
void *dptr; 
#line 2387
}; 
#endif
#line 2392 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2392
struct cudaMemFreeNodeParams { 
#line 2393
void *dptr; 
#line 2394
}; 
#endif
#line 2399 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2399
enum cudaGraphMemAttributeType { 
#line 2404
cudaGraphMemAttrUsedMemCurrent, 
#line 2411
cudaGraphMemAttrUsedMemHigh, 
#line 2418
cudaGraphMemAttrReservedMemCurrent, 
#line 2425
cudaGraphMemAttrReservedMemHigh
#line 2426
}; 
#endif
#line 2431 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2431
enum cudaMemcpyFlags { 
#line 2432
cudaMemcpyFlagDefault, 
#line 2437
cudaMemcpyFlagPreferOverlapWithCompute
#line 2438
}; 
#endif
#line 2440 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2440
enum cudaMemcpySrcAccessOrder { 
#line 2444
cudaMemcpySrcAccessOrderInvalid, 
#line 2449
cudaMemcpySrcAccessOrderStream, 
#line 2460
cudaMemcpySrcAccessOrderDuringApiCall, 
#line 2469
cudaMemcpySrcAccessOrderAny, 
#line 2471
cudaMemcpySrcAccessOrderMax = 2147483647
#line 2472
}; 
#endif
#line 2477 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2477
struct cudaMemcpyAttributes { 
#line 2478
cudaMemcpySrcAccessOrder srcAccessOrder; 
#line 2479
cudaMemLocation srcLocHint; 
#line 2480
cudaMemLocation dstLocHint; 
#line 2481
unsigned flags; 
#line 2482
}; 
#endif
#line 2487 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2487
enum cudaMemcpy3DOperandType { 
#line 2488
cudaMemcpyOperandTypePointer = 1, 
#line 2489
cudaMemcpyOperandTypeArray, 
#line 2490
cudaMemcpyOperandTypeMax = 2147483647
#line 2491
}; 
#endif
#line 2496 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2496
struct cudaOffset3D { 
#line 2497
size_t x; 
#line 2498
size_t y; 
#line 2499
size_t z; 
#line 2500
}; 
#endif
#line 2505 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2505
struct cudaMemcpy3DOperand { 
#line 2506
cudaMemcpy3DOperandType type; 
#line 2507
union { 
#line 2511
struct { 
#line 2512
void *ptr; 
#line 2513
size_t rowLength; 
#line 2514
size_t layerHeight; 
#line 2515
cudaMemLocation locHint; 
#line 2516
} ptr; 
#line 2521
struct { 
#line 2522
cudaArray_t array; 
#line 2523
cudaOffset3D offset; 
#line 2524
} array; 
#line 2525
} op; 
#line 2526
}; 
#endif
#line 2528 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2528
struct cudaMemcpy3DBatchOp { 
#line 2529
cudaMemcpy3DOperand src; 
#line 2530
cudaMemcpy3DOperand dst; 
#line 2531
cudaExtent extent; 
#line 2532
cudaMemcpySrcAccessOrder srcAccessOrder; 
#line 2533
unsigned flags; 
#line 2534
}; 
#endif
#line 2540 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2540
enum cudaDeviceP2PAttr { 
#line 2541
cudaDevP2PAttrPerformanceRank = 1, 
#line 2542
cudaDevP2PAttrAccessSupported, 
#line 2543
cudaDevP2PAttrNativeAtomicSupported, 
#line 2544
cudaDevP2PAttrCudaArrayAccessSupported, 
#line 2546
cudaDevP2PAttrOnlyPartialNativeAtomicSupported
#line 2548
}; 
#endif
#line 2553 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2553
enum cudaAtomicOperation { 
#line 2554
cudaAtomicOperationIntegerAdd, 
#line 2555
cudaAtomicOperationIntegerMin, 
#line 2556
cudaAtomicOperationIntegerMax, 
#line 2557
cudaAtomicOperationIntegerIncrement, 
#line 2558
cudaAtomicOperationIntegerDecrement, 
#line 2559
cudaAtomicOperationAnd, 
#line 2560
cudaAtomicOperationOr, 
#line 2561
cudaAtomicOperationXOR, 
#line 2562
cudaAtomicOperationExchange, 
#line 2563
cudaAtomicOperationCAS, 
#line 2564
cudaAtomicOperationFloatAdd, 
#line 2565
cudaAtomicOperationFloatMin, 
#line 2566
cudaAtomicOperationFloatMax
#line 2567
}; 
#endif
#line 2572 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2572
enum cudaAtomicOperationCapability { 
#line 2573
cudaAtomicCapabilitySigned = (1U << 0), 
#line 2574
cudaAtomicCapabilityUnsigned, 
#line 2575
cudaAtomicCapabilityReduction = (1U << 2), 
#line 2576
cudaAtomicCapabilityScalar32 = (1U << 3), 
#line 2577
cudaAtomicCapabilityScalar64 = (1U << 4), 
#line 2578
cudaAtomicCapabilityScalar128 = (1U << 5), 
#line 2579
cudaAtomicCapabilityVector32x4 = (1U << 6)
#line 2580
}; 
#endif
#line 2589 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2589
struct CUuuid_st { 
#line 2590
char bytes[16]; 
#line 2591
}; 
#endif
#line 2592 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef CUuuid_st 
#line 2592
CUuuid; 
#endif
#line 2594 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef CUuuid_st 
#line 2594
cudaUUID_t; 
#endif
#line 2599 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2599
struct cudaDeviceProp { 
#line 2601
char name[256]; 
#line 2602
cudaUUID_t uuid; 
#line 2603
char luid[8]; 
#line 2604
unsigned luidDeviceNodeMask; 
#line 2605
size_t totalGlobalMem; 
#line 2606
size_t sharedMemPerBlock; 
#line 2607
int regsPerBlock; 
#line 2608
int warpSize; 
#line 2609
size_t memPitch; 
#line 2610
int maxThreadsPerBlock; 
#line 2611
int maxThreadsDim[3]; 
#line 2612
int maxGridSize[3]; 
#line 2613
size_t totalConstMem; 
#line 2614
int major; 
#line 2615
int minor; 
#line 2616
size_t textureAlignment; 
#line 2617
size_t texturePitchAlignment; 
#line 2618
int multiProcessorCount; 
#line 2619
int integrated; 
#line 2620
int canMapHostMemory; 
#line 2621
int maxTexture1D; 
#line 2622
int maxTexture1DMipmap; 
#line 2623
int maxTexture2D[2]; 
#line 2624
int maxTexture2DMipmap[2]; 
#line 2625
int maxTexture2DLinear[3]; 
#line 2626
int maxTexture2DGather[2]; 
#line 2627
int maxTexture3D[3]; 
#line 2628
int maxTexture3DAlt[3]; 
#line 2629
int maxTextureCubemap; 
#line 2630
int maxTexture1DLayered[2]; 
#line 2631
int maxTexture2DLayered[3]; 
#line 2632
int maxTextureCubemapLayered[2]; 
#line 2633
int maxSurface1D; 
#line 2634
int maxSurface2D[2]; 
#line 2635
int maxSurface3D[3]; 
#line 2636
int maxSurface1DLayered[2]; 
#line 2637
int maxSurface2DLayered[3]; 
#line 2638
int maxSurfaceCubemap; 
#line 2639
int maxSurfaceCubemapLayered[2]; 
#line 2640
size_t surfaceAlignment; 
#line 2641
int concurrentKernels; 
#line 2642
int ECCEnabled; 
#line 2643
int pciBusID; 
#line 2644
int pciDeviceID; 
#line 2645
int pciDomainID; 
#line 2646
int tccDriver; 
#line 2647
int asyncEngineCount; 
#line 2648
int unifiedAddressing; 
#line 2649
int memoryBusWidth; 
#line 2650
int l2CacheSize; 
#line 2651
int persistingL2CacheMaxSize; 
#line 2652
int maxThreadsPerMultiProcessor; 
#line 2653
int streamPrioritiesSupported; 
#line 2654
int globalL1CacheSupported; 
#line 2655
int localL1CacheSupported; 
#line 2656
size_t sharedMemPerMultiprocessor; 
#line 2657
int regsPerMultiprocessor; 
#line 2658
int managedMemory; 
#line 2659
int isMultiGpuBoard; 
#line 2660
int multiGpuBoardGroupID; 
#line 2661
int hostNativeAtomicSupported; 
#line 2662
int pageableMemoryAccess; 
#line 2663
int concurrentManagedAccess; 
#line 2664
int computePreemptionSupported; 
#line 2665
int canUseHostPointerForRegisteredMem; 
#line 2666
int cooperativeLaunch; 
#line 2667
size_t sharedMemPerBlockOptin; 
#line 2668
int pageableMemoryAccessUsesHostPageTables; 
#line 2669
int directManagedMemAccessFromHost; 
#line 2670
int maxBlocksPerMultiProcessor; 
#line 2671
int accessPolicyMaxWindowSize; 
#line 2672
size_t reservedSharedMemPerBlock; 
#line 2673
int hostRegisterSupported; 
#line 2674
int sparseCudaArraySupported; 
#line 2675
int hostRegisterReadOnlySupported; 
#line 2676
int timelineSemaphoreInteropSupported; 
#line 2677
int memoryPoolsSupported; 
#line 2678
int gpuDirectRDMASupported; 
#line 2679
unsigned gpuDirectRDMAFlushWritesOptions; 
#line 2680
int gpuDirectRDMAWritesOrdering; 
#line 2681
unsigned memoryPoolSupportedHandleTypes; 
#line 2682
int deferredMappingCudaArraySupported; 
#line 2683
int ipcEventSupported; 
#line 2684
int clusterLaunch; 
#line 2685
int unifiedFunctionPointers; 
#line 2686
int deviceNumaConfig; 
#line 2687
int deviceNumaId; 
#line 2688
int mpsEnabled; 
#line 2689
int hostNumaId; 
#line 2690
unsigned gpuPciDeviceID; 
#line 2691
unsigned gpuPciSubsystemID; 
#line 2692
int hostNumaMultinodeIpcSupported; 
#line 2693
int reserved[56]; 
#line 2694
}; 
#endif
#line 2707 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 2704
struct cudaIpcEventHandle_st { 
#line 2706
char reserved[64]; 
#line 2707
} cudaIpcEventHandle_t; 
#endif
#line 2715 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 2712
struct cudaIpcMemHandle_st { 
#line 2714
char reserved[64]; 
#line 2715
} cudaIpcMemHandle_t; 
#endif
#line 2723 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 2720
struct cudaMemFabricHandle_st { 
#line 2722
char reserved[64]; 
#line 2723
} cudaMemFabricHandle_t; 
#endif
#line 2728 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2728
enum cudaExternalMemoryHandleType { 
#line 2732
cudaExternalMemoryHandleTypeOpaqueFd = 1, 
#line 2736
cudaExternalMemoryHandleTypeOpaqueWin32, 
#line 2740
cudaExternalMemoryHandleTypeOpaqueWin32Kmt, 
#line 2744
cudaExternalMemoryHandleTypeD3D12Heap, 
#line 2748
cudaExternalMemoryHandleTypeD3D12Resource, 
#line 2752
cudaExternalMemoryHandleTypeD3D11Resource, 
#line 2756
cudaExternalMemoryHandleTypeD3D11ResourceKmt, 
#line 2760
cudaExternalMemoryHandleTypeNvSciBuf
#line 2761
}; 
#endif
#line 2803 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2803
struct cudaExternalMemoryHandleDesc { 
#line 2807
cudaExternalMemoryHandleType type; 
#line 2808
union { 
#line 2814
int fd; 
#line 2830
struct { 
#line 2834
void *handle; 
#line 2839
const void *name; 
#line 2840
} win32; 
#line 2845
const void *nvSciBufObject; 
#line 2846
} handle; 
#line 2850
unsigned __int64 size; 
#line 2854
unsigned flags; 
#line 2858
unsigned reserved[16]; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 2859
}; 
#endif
#line 2864 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2864
struct cudaExternalMemoryBufferDesc { 
#line 2868
unsigned __int64 offset; 
#line 2872
unsigned __int64 size; 
#line 2876
unsigned flags; 
#line 2880
unsigned reserved[16]; 
#line 2881
}; 
#endif
#line 2886 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2886
struct cudaExternalMemoryMipmappedArrayDesc { 
#line 2891
unsigned __int64 offset; 
#line 2895
cudaChannelFormatDesc formatDesc; 
#line 2899
cudaExtent extent; 
#line 2904
unsigned flags; 
#line 2908
unsigned numLevels; 
#line 2912
unsigned reserved[16]; 
#line 2913
}; 
#endif
#line 2918 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2918
enum cudaExternalSemaphoreHandleType { 
#line 2922
cudaExternalSemaphoreHandleTypeOpaqueFd = 1, 
#line 2926
cudaExternalSemaphoreHandleTypeOpaqueWin32, 
#line 2930
cudaExternalSemaphoreHandleTypeOpaqueWin32Kmt, 
#line 2934
cudaExternalSemaphoreHandleTypeD3D12Fence, 
#line 2938
cudaExternalSemaphoreHandleTypeD3D11Fence, 
#line 2942
cudaExternalSemaphoreHandleTypeNvSciSync, 
#line 2946
cudaExternalSemaphoreHandleTypeKeyedMutex, 
#line 2950
cudaExternalSemaphoreHandleTypeKeyedMutexKmt, 
#line 2954
cudaExternalSemaphoreHandleTypeTimelineSemaphoreFd, 
#line 2958
cudaExternalSemaphoreHandleTypeTimelineSemaphoreWin32
#line 2959
}; 
#endif
#line 2964 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 2964
struct cudaExternalSemaphoreHandleDesc { 
#line 2968
cudaExternalSemaphoreHandleType type; 
#line 2969
union { 
#line 2976
int fd; 
#line 2992
struct { 
#line 2996
void *handle; 
#line 3001
const void *name; 
#line 3002
} win32; 
#line 3006
const void *nvSciSyncObj; 
#line 3007
} handle; 
#line 3011
unsigned flags; 
#line 3015
unsigned reserved[16]; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 3016
}; 
#endif
#line 3022 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3022
struct cudaExternalSemaphoreSignalParams { 
#line 3023
struct { 
#line 3027
struct { 
#line 3031
unsigned __int64 value; 
#line 3032
} fence; 
#line 3033
union { 
#line 3038
void *fence; 
#line 3039
unsigned __int64 reserved; 
#line 3040
} nvSciSync; 
#line 3044
struct { 
#line 3048
unsigned __int64 key; 
#line 3049
} keyedMutex; 
#line 3050
unsigned reserved[12]; 
#line 3051
} params; 
#line 3062
unsigned flags; 
#line 3063
unsigned reserved[16]; 
#line 3064
}; 
#endif
#line 3069 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3069
struct cudaExternalSemaphoreWaitParams { 
#line 3070
struct { 
#line 3074
struct { 
#line 3078
unsigned __int64 value; 
#line 3079
} fence; 
#line 3080
union { 
#line 3085
void *fence; 
#line 3086
unsigned __int64 reserved; 
#line 3087
} nvSciSync; 
#line 3091
struct { 
#line 3095
unsigned __int64 key; 
#line 3099
unsigned timeoutMs; 
#line 3100
} keyedMutex; 
#line 3101
unsigned reserved[10]; 
#line 3102
} params; 
#line 3113
unsigned flags; 
#line 3114
unsigned reserved[16]; 
#line 3115
}; 
#endif
#line 3122 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3122
enum cudaDevSmResourceGroup_flags { 
#line 3123
cudaDevSmResourceGroupDefault, 
#line 3124
cudaDevSmResourceGroupBackfill
#line 3125
}; 
#endif
#line 3127 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3127
enum cudaDevSmResourceSplitByCount_flags { 
#line 3128
cudaDevSmResourceSplitIgnoreSmCoscheduling = 1, 
#line 3129
cudaDevSmResourceSplitMaxPotentialClusterSize
#line 3130
}; 
#endif
#line 3135 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3135
enum cudaDevResourceType { 
#line 3136
cudaDevResourceTypeInvalid, 
#line 3137
cudaDevResourceTypeSm, 
#line 3138
cudaDevResourceTypeWorkqueueConfig = 1000, 
#line 3139
cudaDevResourceTypeWorkqueue = 10000
#line 3140
}; 
#endif
#line 3146 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3146
struct cudaDevSmResource { 
#line 3147
unsigned smCount; 
#line 3148
unsigned minSmPartitionSize; 
#line 3149
unsigned smCoscheduledAlignment; 
#line 3152
unsigned flags; 
#line 3153
}; 
#endif
#line 3158 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3158
enum cudaDevWorkqueueConfigScope { 
#line 3159
cudaDevWorkqueueConfigScopeDeviceCtx, 
#line 3160
cudaDevWorkqueueConfigScopeGreenCtxBalanced
#line 3161
}; 
#endif
#line 3166 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3166
struct cudaDevWorkqueueConfigResource { 
#line 3167
int device; 
#line 3168
unsigned wqConcurrencyLimit; 
#line 3169
cudaDevWorkqueueConfigScope sharingScope; 
#line 3170
}; 
#endif
#line 3175 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3175
struct cudaDevWorkqueueResource { 
#line 3176
unsigned char reserved[40]; 
#line 3177
}; 
#endif
#line 3188 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3182
struct cudaDevSmResourceGroupParams_st { 
#line 3183
unsigned smCount; 
#line 3184
unsigned coscheduledSmCount; 
#line 3185
unsigned preferredCoscheduledSmCount; 
#line 3186
unsigned flags; 
#line 3187
unsigned reserved[12]; 
#line 3188
} cudaDevSmResourceGroupParams; 
#endif
#line 3218 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3208
struct cudaDevResource_st { 
#line 3209
cudaDevResourceType type; 
#line 3210
unsigned char _internal_padding[92]; 
#line 3211
union { 
#line 3212
cudaDevSmResource sm; 
#line 3213
cudaDevWorkqueueConfigResource wqConfig; 
#line 3214
cudaDevWorkqueueResource wq; 
#line 3215
unsigned char _oversize[40]; 
#line 3216
}; 
#line 3217
cudaDevResource_st *nextResource; 
#line 3218
} cudaDevResource; 
#endif
#line 3231 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef cudaError 
#line 3231
cudaError_t; 
#endif
#line 3236 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUstream_st *
#line 3236
cudaStream_t; 
#endif
#line 3241 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUevent_st *
#line 3241
cudaEvent_t; 
#endif
#line 3246 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef cudaGraphicsResource *
#line 3246
cudaGraphicsResource_t; 
#endif
#line 3251 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUexternalMemory_st *
#line 3251
cudaExternalMemory_t; 
#endif
#line 3256 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUexternalSemaphore_st *
#line 3256
cudaExternalSemaphore_t; 
#endif
#line 3261 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUgraph_st *
#line 3261
cudaGraph_t; 
#endif
#line 3266 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUgraphNode_st *
#line 3266
cudaGraphNode_t; 
#endif
#line 3271 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUuserObject_st *
#line 3271
cudaUserObject_t; 
#endif
#line 3276 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef unsigned __int64 
#line 3276
cudaGraphConditionalHandle; 
#endif
#line 3281 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUfunc_st *
#line 3281
cudaFunction_t; 
#endif
#line 3286 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUkern_st *
#line 3286
cudaKernel_t; 
#endif
#line 3291 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3291
enum cudaJitOption { 
#line 3298
cudaJitMaxRegisters, 
#line 3312
cudaJitThreadsPerBlock, 
#line 3320
cudaJitWallTime, 
#line 3329
cudaJitInfoLogBuffer, 
#line 3338
cudaJitInfoLogBufferSizeBytes, 
#line 3347
cudaJitErrorLogBuffer, 
#line 3356
cudaJitErrorLogBufferSizeBytes, 
#line 3364
cudaJitOptimizationLevel, 
#line 3372
cudaJitFallbackStrategy = 10, 
#line 3380
cudaJitGenerateDebugInfo, 
#line 3387
cudaJitLogVerbose, 
#line 3394
cudaJitGenerateLineInfo, 
#line 3402
cudaJitCacheMode, 
#line 3409
cudaJitPositionIndependentCode = 30, 
#line 3422
cudaJitMinCtaPerSm, 
#line 3435
cudaJitMaxThreadsPerBlock, 
#line 3445
cudaJitOverrideDirectiveValues
#line 3446
}; 
#endif
#line 3452 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3452
enum cudaLibraryOption { 
#line 3454
cudaLibraryHostUniversalFunctionAndDataTable, 
#line 3465
cudaLibraryBinaryIsPreserved
#line 3466
}; 
#endif
#line 3468 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3468
struct cudalibraryHostUniversalFunctionAndDataTable { 
#line 3470
void *functionTable; 
#line 3471
size_t functionWindowSize; 
#line 3472
void *dataTable; 
#line 3473
size_t dataWindowSize; 
#line 3474
}; 
#endif
#line 3479 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3479
enum cudaJit_CacheMode { 
#line 3481
cudaJitCacheOptionNone, 
#line 3482
cudaJitCacheOptionCG, 
#line 3483
cudaJitCacheOptionCA
#line 3484
}; 
#endif
#line 3489 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3489
enum cudaJit_Fallback { 
#line 3491
cudaPreferPtx, 
#line 3493
cudaPreferBinary
#line 3494
}; 
#endif
#line 3499 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUlib_st *
#line 3499
cudaLibrary_t; 
#endif
#line 3504 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUmemPoolHandle_st *
#line 3504
cudaMemPool_t; 
#endif
#line 3509 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3509
enum cudaCGScope { 
#line 3510
cudaCGScopeInvalid, 
#line 3511
cudaCGScopeGrid, 
#line 3512
cudaCGScopeReserved
#line 3513
}; 
#endif
#line 3518 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3518
struct cudaKernelNodeParams { 
#line 3519
void *func; 
#line 3520
dim3 gridDim; 
#line 3521
dim3 blockDim; 
#line 3522
unsigned sharedMemBytes; 
#line 3523
void **kernelParams; 
#line 3524
void **extra; 
#line 3525
}; 
#endif
#line 3530 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3530
enum cudaKernelFunctionType { 
#line 3531
cudaKernelFunctionTypeUnspecified, 
#line 3532
cudaKernelFunctionTypeDeviceEntry, 
#line 3533
cudaKernelFunctionTypeKernel, 
#line 3534
cudaKernelFunctionTypeFunction
#line 3535
}; 
#endif
#line 3540 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3540
struct cudaKernelNodeParamsV2 { 
#line 3541
union { 
#line 3542
void *func; 
#line 3543
cudaKernel_t kern; 
#line 3544
cudaFunction_t cuFunc; 
#line 3545
}; 
#line 3552 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
uint3 gridDim; 
#line 3553
uint3 blockDim; 
#line 3555 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
unsigned sharedMemBytes; 
#line 3556
void **kernelParams; 
#line 3557
void **extra; 
#line 3558
cudaExecutionContext_t ctx; 
#line 3559
cudaKernelFunctionType functionType; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 3560
}; 
#endif
#line 3565 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3565
struct cudaExternalSemaphoreSignalNodeParams { 
#line 3566
cudaExternalSemaphore_t *extSemArray; 
#line 3567
const cudaExternalSemaphoreSignalParams *paramsArray; 
#line 3568
unsigned numExtSems; 
#line 3569
}; 
#endif
#line 3574 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3574
struct cudaExternalSemaphoreSignalNodeParamsV2 { 
#line 3575
cudaExternalSemaphore_t *extSemArray; 
#line 3576
const cudaExternalSemaphoreSignalParams *paramsArray; 
#line 3577
unsigned numExtSems; 
#line 3578
}; 
#endif
#line 3583 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3583
struct cudaExternalSemaphoreWaitNodeParams { 
#line 3584
cudaExternalSemaphore_t *extSemArray; 
#line 3585
const cudaExternalSemaphoreWaitParams *paramsArray; 
#line 3586
unsigned numExtSems; 
#line 3587
}; 
#endif
#line 3592 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3592
struct cudaExternalSemaphoreWaitNodeParamsV2 { 
#line 3593
cudaExternalSemaphore_t *extSemArray; 
#line 3594
const cudaExternalSemaphoreWaitParams *paramsArray; 
#line 3595
unsigned numExtSems; 
#line 3596
}; 
#endif
#line 3598 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3598
enum cudaGraphConditionalHandleFlags { 
#line 3599
cudaGraphCondAssignDefault = 1
#line 3600
}; 
#endif
#line 3605 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3605
enum cudaGraphConditionalNodeType { 
#line 3606
cudaGraphCondTypeIf, 
#line 3607
cudaGraphCondTypeWhile, 
#line 3608
cudaGraphCondTypeSwitch
#line 3609
}; 
#endif
#line 3614 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3614
struct cudaConditionalNodeParams { 
#line 3615
cudaGraphConditionalHandle handle; 
#line 3618
cudaGraphConditionalNodeType type; 
#line 3619
unsigned size; 
#line 3621
cudaGraph_t *phGraph_out; 
#line 3640
cudaExecutionContext_t ctx; 
#line 3641
}; 
#endif
#line 3646 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3646
enum cudaGraphNodeType { 
#line 3647
cudaGraphNodeTypeKernel, 
#line 3648
cudaGraphNodeTypeMemcpy, 
#line 3649
cudaGraphNodeTypeMemset, 
#line 3650
cudaGraphNodeTypeHost, 
#line 3651
cudaGraphNodeTypeGraph, 
#line 3652
cudaGraphNodeTypeEmpty, 
#line 3653
cudaGraphNodeTypeWaitEvent, 
#line 3654
cudaGraphNodeTypeEventRecord, 
#line 3655
cudaGraphNodeTypeExtSemaphoreSignal, 
#line 3656
cudaGraphNodeTypeExtSemaphoreWait, 
#line 3657
cudaGraphNodeTypeMemAlloc, 
#line 3658
cudaGraphNodeTypeMemFree, 
#line 3659
cudaGraphNodeTypeConditional = 13, 
#line 3676
cudaGraphNodeTypeReserved16 = 16, 
#line 3677
cudaGraphNodeTypeCount
#line 3678
}; 
#endif
#line 3683 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3683
enum cudaGraphChildGraphNodeOwnership { 
#line 3684
cudaGraphChildGraphOwnershipClone, 
#line 3687
cudaGraphChildGraphOwnershipMove, 
#line 3696
cudaGraphChildGraphOwnershipInvalid = (-1)
#line 3698
}; 
#endif
#line 3703 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3703
struct cudaChildGraphNodeParams { 
#line 3704
cudaGraph_t graph; 
#line 3710
cudaGraphChildGraphNodeOwnership ownership; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 3711
}; 
#endif
#line 3716 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3716
struct cudaEventRecordNodeParams { 
#line 3717
cudaEvent_t event; 
#line 3718
}; 
#endif
#line 3723 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3723
struct cudaEventWaitNodeParams { 
#line 3724
cudaEvent_t event; 
#line 3725
}; 
#endif
#line 3730 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3730
struct cudaGraphNodeParams { 
#line 3731
cudaGraphNodeType type; 
#line 3732
int reserved0[3]; 
#line 3734
union { 
#line 3735
__int64 reserved1[29]; 
#line 3736
cudaKernelNodeParamsV2 kernel; 
#line 3737
cudaMemcpyNodeParams memcpy; 
#line 3738
cudaMemsetParamsV2 memset; 
#line 3739
cudaHostNodeParamsV2 host; 
#line 3740
cudaChildGraphNodeParams graph; 
#line 3741
cudaEventWaitNodeParams eventWait; 
#line 3742
cudaEventRecordNodeParams eventRecord; 
#line 3743
cudaExternalSemaphoreSignalNodeParamsV2 extSemSignal; 
#line 3744
cudaExternalSemaphoreWaitNodeParamsV2 extSemWait; 
#line 3745
cudaMemAllocNodeParamsV2 alloc; 
#line 3746
cudaMemFreeNodeParams free; 
#line 3747
cudaConditionalNodeParams conditional; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 3748
}; 
#line 3750
__int64 reserved2; 
#line 3751
}; 
#endif
#line 3763 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3756
enum cudaGraphDependencyType_enum { 
#line 3757
cudaGraphDependencyTypeDefault, 
#line 3758
cudaGraphDependencyTypeProgrammatic
#line 3763
} cudaGraphDependencyType; 
#endif
#line 3793 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3770
struct cudaGraphEdgeData_st { 
#line 3771
unsigned char from_port; 
#line 3781
unsigned char to_port; 
#line 3788
unsigned char type; 
#line 3791
unsigned char reserved[5]; 
#line 3793
} cudaGraphEdgeData; 
#endif
#line 3814 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
typedef struct CUgraphExec_st *cudaGraphExec_t; 
#line 3819
#if 0
#line 3819
enum cudaGraphExecUpdateResult { 
#line 3820
cudaGraphExecUpdateSuccess, 
#line 3821
cudaGraphExecUpdateError, 
#line 3822
cudaGraphExecUpdateErrorTopologyChanged, 
#line 3823
cudaGraphExecUpdateErrorNodeTypeChanged, 
#line 3824
cudaGraphExecUpdateErrorFunctionChanged, 
#line 3825
cudaGraphExecUpdateErrorParametersChanged, 
#line 3826
cudaGraphExecUpdateErrorNotSupported, 
#line 3827
cudaGraphExecUpdateErrorUnsupportedFunctionChange, 
#line 3828
cudaGraphExecUpdateErrorAttributesChanged
#line 3829
}; 
#endif
#line 3841 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3834
enum cudaGraphInstantiateResult { 
#line 3835
cudaGraphInstantiateSuccess, 
#line 3836
cudaGraphInstantiateError, 
#line 3837
cudaGraphInstantiateInvalidStructure, 
#line 3838
cudaGraphInstantiateNodeOperationNotSupported, 
#line 3839
cudaGraphInstantiateMultipleDevicesNotSupported, 
#line 3840
cudaGraphInstantiateConditionalHandleUnused
#line 3841
} cudaGraphInstantiateResult; 
#endif
#line 3852 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3846
struct cudaGraphInstantiateParams_st { 
#line 3848
unsigned __int64 flags; 
#line 3849
cudaStream_t uploadStream; 
#line 3850
cudaGraphNode_t errNode_out; 
#line 3851
cudaGraphInstantiateResult result_out; 
#line 3852
} cudaGraphInstantiateParams; 
#endif
#line 3874 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3857
struct cudaGraphExecUpdateResultInfo_st { 
#line 3861
cudaGraphExecUpdateResult result; 
#line 3868
cudaGraphNode_t errorNode; 
#line 3873
cudaGraphNode_t errorFromNode; 
#line 3874
} cudaGraphExecUpdateResultInfo; 
#endif
#line 3879 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
typedef struct CUgraphDeviceUpdatableNode_st *cudaGraphDeviceNode_t; 
#line 3884
#if 0
#line 3884
enum cudaGraphKernelNodeField { 
#line 3886
cudaGraphKernelNodeFieldInvalid, 
#line 3887
cudaGraphKernelNodeFieldGridDim, 
#line 3888
cudaGraphKernelNodeFieldParam, 
#line 3889
cudaGraphKernelNodeFieldEnabled
#line 3890
}; 
#endif
#line 3895 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3895
struct cudaGraphKernelNodeUpdate { 
#line 3896
cudaGraphDeviceNode_t node; 
#line 3897
cudaGraphKernelNodeField field; 
#line 3898
union { 
#line 3903 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
uint3 gridDim; 
#line 3905 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
struct { 
#line 3906
const void *pValue; 
#line 3907
size_t offset; 
#line 3908
size_t size; 
#line 3909
} param; 
#line 3910
unsigned isEnabled; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 3911
} updateData; 
#line 3912
}; 
#endif
#line 3918 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3918
enum cudaGetDriverEntryPointFlags { 
#line 3919
cudaEnableDefault, 
#line 3920
cudaEnableLegacyStream, 
#line 3921
cudaEnablePerThreadDefaultStream
#line 3922
}; 
#endif
#line 3927 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3927
enum cudaDriverEntryPointQueryResult { 
#line 3928
cudaDriverEntryPointSuccess, 
#line 3929
cudaDriverEntryPointSymbolNotFound, 
#line 3930
cudaDriverEntryPointVersionNotSufficent
#line 3931
}; 
#endif
#line 3936 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3936
enum cudaGraphDebugDotFlags { 
#line 3937
cudaGraphDebugDotFlagsVerbose = (1 << 0), 
#line 3938
cudaGraphDebugDotFlagsKernelNodeParams = (1 << 2), 
#line 3939
cudaGraphDebugDotFlagsMemcpyNodeParams = (1 << 3), 
#line 3940
cudaGraphDebugDotFlagsMemsetNodeParams = (1 << 4), 
#line 3941
cudaGraphDebugDotFlagsHostNodeParams = (1 << 5), 
#line 3942
cudaGraphDebugDotFlagsEventNodeParams = (1 << 6), 
#line 3943
cudaGraphDebugDotFlagsExtSemasSignalNodeParams = (1 << 7), 
#line 3944
cudaGraphDebugDotFlagsExtSemasWaitNodeParams = (1 << 8), 
#line 3945
cudaGraphDebugDotFlagsKernelNodeAttributes = (1 << 9), 
#line 3946
cudaGraphDebugDotFlagsHandles = (1 << 10), 
#line 3947
cudaGraphDebugDotFlagsConditionalNodeParams = (1 << 15)
#line 3948
}; 
#endif
#line 3953 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 3953
enum cudaGraphInstantiateFlags { 
#line 3954
cudaGraphInstantiateFlagAutoFreeOnLaunch = 1, 
#line 3955
cudaGraphInstantiateFlagUpload, 
#line 3958
cudaGraphInstantiateFlagDeviceLaunch = 4, 
#line 3961
cudaGraphInstantiateFlagUseNodePriority = 8
#line 3963
}; 
#endif
#line 3984 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3981
enum cudaLaunchMemSyncDomain { 
#line 3982
cudaLaunchMemSyncDomainDefault, 
#line 3983
cudaLaunchMemSyncDomainRemote
#line 3984
} cudaLaunchMemSyncDomain; 
#endif
#line 4000 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 3997
struct cudaLaunchMemSyncDomainMap_st { 
#line 3998
unsigned char default_; 
#line 3999
unsigned char remote; 
#line 4000
} cudaLaunchMemSyncDomainMap; 
#endif
#line 4010 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 4005
enum cudaLaunchAttributePortableClusterMode { 
#line 4006
cudaLaunchPortableClusterModeDefault, 
#line 4008
cudaLaunchPortableClusterModeRequirePortable, 
#line 4009
cudaLaunchPortableClusterModeAllowNonPortable
#line 4010
} cudaLaunchAttributePortableClusterMode; 
#endif
#line 4179 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 4015
enum cudaLaunchAttributeID { 
#line 4016
cudaLaunchAttributeIgnore, 
#line 4017
cudaLaunchAttributeAccessPolicyWindow, 
#line 4019
cudaLaunchAttributeCooperative, 
#line 4021
cudaLaunchAttributeSynchronizationPolicy, 
#line 4022
cudaLaunchAttributeClusterDimension, 
#line 4024
cudaLaunchAttributeClusterSchedulingPolicyPreference, 
#line 4026
cudaLaunchAttributeProgrammaticStreamSerialization, 
#line 4037
cudaLaunchAttributeProgrammaticEvent, 
#line 4063
cudaLaunchAttributePriority, 
#line 4065
cudaLaunchAttributeMemSyncDomainMap, 
#line 4067
cudaLaunchAttributeMemSyncDomain, 
#line 4069
cudaLaunchAttributePreferredClusterDimension, 
#line 4105
cudaLaunchAttributeLaunchCompletionEvent, 
#line 4127
cudaLaunchAttributeDeviceUpdatableKernelNode, 
#line 4155
cudaLaunchAttributePreferredSharedMemoryCarveout, 
#line 4162
cudaLaunchAttributeNvlinkUtilCentricScheduling = 16, 
#line 4175
cudaLaunchAttributePortableClusterSizeMode, 
#line 4178
cudaLaunchAttributeSharedMemoryMode
#line 4179
} cudaLaunchAttributeID; 
#endif
#line 4279 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 4184
union cudaLaunchAttributeValue { 
#line 4185
char pad[64]; 
#line 4186
cudaAccessPolicyWindow accessPolicyWindow; 
#line 4187
int cooperative; 
#line 4189
cudaSynchronizationPolicy syncPolicy; 
#line 4203
struct { 
#line 4204
unsigned x; 
#line 4205
unsigned y; 
#line 4206
unsigned z; 
#line 4207
} clusterDim; 
#line 4208
cudaClusterSchedulingPolicy clusterSchedulingPolicyPreference; 
#line 4211
int programmaticStreamSerializationAllowed; 
#line 4222
struct { 
#line 4223
cudaEvent_t event; 
#line 4224
int flags; 
#line 4225
int triggerAtBlockStart; 
#line 4226
} programmaticEvent; 
#line 4227
int priority; 
#line 4228
cudaLaunchMemSyncDomainMap memSyncDomainMap; 
#line 4231
cudaLaunchMemSyncDomain memSyncDomain; 
#line 4246
struct { 
#line 4247
unsigned x; 
#line 4248
unsigned y; 
#line 4249
unsigned z; 
#line 4250
} preferredClusterDim; 
#line 4259
struct { 
#line 4260
cudaEvent_t event; 
#line 4261
int flags; 
#line 4262
} launchCompletionEvent; 
#line 4270
struct { 
#line 4271
int deviceUpdatable; 
#line 4272
cudaGraphDeviceNode_t devNode; 
#line 4273
} deviceUpdatableKernelNode; 
#line 4274
unsigned sharedMemCarveout; 
#line 4275
unsigned nvlinkUtilCentricScheduling; 
#line 4276
cudaLaunchAttributePortableClusterMode portableClusterSizeMode; 
#line 4277
cudaSharedMemoryMode sharedMemoryMode; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 4279
} cudaLaunchAttributeValue; 
#endif
#line 4288 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 4284
struct cudaLaunchAttribute_st { 
#line 4285
cudaLaunchAttributeID id; 
#line 4286
char pad[(8) - sizeof(cudaLaunchAttributeID)]; 
#line 4287
cudaLaunchAttributeValue val; 
#line 4288
} cudaLaunchAttribute; 
#endif
#line 4300 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 4293
struct cudaLaunchConfig_st { 
#line 4294
dim3 gridDim; 
#line 4295
dim3 blockDim; 
#line 4296
size_t dynamicSmemBytes; 
#line 4297
cudaStream_t stream; 
#line 4298
cudaLaunchAttribute *attrs; 
#line 4299
unsigned numAttrs; __pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)__pad__(volatile char:8;)
#line 4300
} cudaLaunchConfig_t; 
#endif
#line 4329 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 4329
enum cudaDeviceNumaConfig { 
#line 4330
cudaDeviceNumaConfigNone, 
#line 4331
cudaDeviceNumaConfigNumaNode
#line 4332
}; 
#endif
#line 4337 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
typedef struct cudaAsyncCallbackEntry *cudaAsyncCallbackHandle_t; 
#line 4339
struct cudaAsyncCallbackEntry; 
#line 4346
#if 0
typedef 
#line 4344
enum cudaAsyncNotificationType_enum { 
#line 4345
cudaAsyncNotificationTypeOverBudget = 1
#line 4346
} cudaAsyncNotificationType; 
#endif
#line 4359 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef 
#line 4351
struct cudaAsyncNotificationInfo { 
#line 4353
cudaAsyncNotificationType type; 
#line 4354
union { 
#line 4355
struct { 
#line 4356
unsigned __int64 bytesOverBudget; 
#line 4357
} overBudget; 
#line 4358
} info; 
#line 4359
} cudaAsyncNotificationInfo_t; 
#endif
#line 4361 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
typedef void (*cudaAsyncCallback)(cudaAsyncNotificationInfo_t *, void *, cudaAsyncCallbackHandle_t); 
#line 4366
#if 0
typedef 
#line 4363
enum CUDAlogLevel_enum { 
#line 4364
cudaLogLevelError, 
#line 4365
cudaLogLevelWarning
#line 4366
} cudaLogLevel; 
#endif
#line 4368 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef struct CUlogsCallbackEntry_st *
#line 4368
cudaLogsCallbackHandle; 
#endif
#line 4369 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
typedef unsigned 
#line 4369
cudaLogIterator; 
#endif
#line 4372 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 4372
enum cudaFabricOpStatusSource { 
#line 4373
cudaFabricOpStatusSourceMbarrierV1, 
#line 4375
cudaFabricOpStatusSourceMax = 2147483647
#line 4376
}; 
#endif
#line 4379 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_types.h"
#if 0
#line 4379
enum cudaFabricOpStatusInfo { 
#line 4380
cudaFabricOpStatusInfoSuccess, 
#line 4381
cudaFabricOpStatusInfoLast = cudaFabricOpStatusInfoSuccess, 
#line 4383
cudaFabricOpStatusInfoMax = 2147483647
#line 4384
}; 
#endif
#line 86 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_types.h"
#if 0
#line 86
enum cudaSurfaceBoundaryMode { 
#line 88
cudaBoundaryModeZero, 
#line 89
cudaBoundaryModeClamp, 
#line 90
cudaBoundaryModeTrap
#line 91
}; 
#endif
#line 96 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_types.h"
#if 0
#line 96
enum cudaSurfaceFormatMode { 
#line 98
cudaFormatModeForced, 
#line 99
cudaFormatModeAuto
#line 100
}; 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_types.h"
#if 0
typedef unsigned __int64 
#line 105
cudaSurfaceObject_t; 
#endif
#line 86 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_types.h"
#if 0
#line 86
enum cudaTextureAddressMode { 
#line 88
cudaAddressModeWrap, 
#line 89
cudaAddressModeClamp, 
#line 90
cudaAddressModeMirror, 
#line 91
cudaAddressModeBorder
#line 92
}; 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_types.h"
#if 0
#line 97
enum cudaTextureFilterMode { 
#line 99
cudaFilterModePoint, 
#line 100
cudaFilterModeLinear
#line 101
}; 
#endif
#line 106 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_types.h"
#if 0
#line 106
enum cudaTextureReadMode { 
#line 108
cudaReadModeElementType, 
#line 109
cudaReadModeNormalizedFloat
#line 110
}; 
#endif
#line 115 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_types.h"
#if 0
#line 115
struct cudaTextureDesc { 
#line 120
cudaTextureAddressMode addressMode[3]; 
#line 124
cudaTextureFilterMode filterMode; 
#line 128
cudaTextureReadMode readMode; 
#line 132
int sRGB; 
#line 136
float borderColor[4]; 
#line 140
int normalizedCoords; 
#line 144
unsigned maxAnisotropy; 
#line 148
cudaTextureFilterMode mipmapFilterMode; 
#line 152
float mipmapLevelBias; 
#line 156
float minMipmapLevelClamp; 
#line 160
float maxMipmapLevelClamp; 
#line 164
int disableTrilinearOptimization; 
#line 168
int seamlessCubemap; 
#line 169
}; 
#endif
#line 174 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_types.h"
#if 0
typedef unsigned __int64 
#line 174
cudaTextureObject_t; 
#endif
#line 94 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\library_types.h"
typedef 
#line 57
enum cudaDataType_t { 
#line 59
CUDA_R_16F = 2, 
#line 60
CUDA_C_16F = 6, 
#line 61
CUDA_R_16BF = 14, 
#line 62
CUDA_C_16BF, 
#line 63
CUDA_R_32F = 0, 
#line 64
CUDA_C_32F = 4, 
#line 65
CUDA_R_64F = 1, 
#line 66
CUDA_C_64F = 5, 
#line 67
CUDA_R_4I = 16, 
#line 68
CUDA_C_4I, 
#line 69
CUDA_R_4U, 
#line 70
CUDA_C_4U, 
#line 71
CUDA_R_8I = 3, 
#line 72
CUDA_C_8I = 7, 
#line 73
CUDA_R_8U, 
#line 74
CUDA_C_8U, 
#line 75
CUDA_R_16I = 20, 
#line 76
CUDA_C_16I, 
#line 77
CUDA_R_16U, 
#line 78
CUDA_C_16U, 
#line 79
CUDA_R_32I = 10, 
#line 80
CUDA_C_32I, 
#line 81
CUDA_R_32U, 
#line 82
CUDA_C_32U, 
#line 83
CUDA_R_64I = 24, 
#line 84
CUDA_C_64I, 
#line 85
CUDA_R_64U, 
#line 86
CUDA_C_64U, 
#line 87
CUDA_R_8F_E4M3, 
#line 88
CUDA_R_8F_UE4M3 = CUDA_R_8F_E4M3, 
#line 89
CUDA_R_8F_E5M2, 
#line 90
CUDA_R_8F_UE8M0, 
#line 91
CUDA_R_6F_E2M3, 
#line 92
CUDA_R_6F_E3M2, 
#line 93
CUDA_R_4F_E2M1
#line 94
} cudaDataType; 
#line 115
typedef 
#line 98
enum cudaEmulationStrategy_t { 
#line 104
CUDA_EMULATION_STRATEGY_DEFAULT, 
#line 109
CUDA_EMULATION_STRATEGY_PERFORMANT, 
#line 114
CUDA_EMULATION_STRATEGY_EAGER
#line 115
} cudaEmulationStrategy; 
#line 131
typedef 
#line 120
enum cudaEmulationMantissaControl_t { 
#line 126
CUDA_EMULATION_MANTISSA_CONTROL_DYNAMIC, 
#line 130
CUDA_EMULATION_MANTISSA_CONTROL_FIXED
#line 131
} cudaEmulationMantissaControl; 
#line 156
typedef 
#line 136
enum cudaEmulationSpecialValuesSupport_t { 
#line 141
CUDA_EMULATION_SPECIAL_VALUES_SUPPORT_DEFAULT = 65535, 
#line 146
CUDA_EMULATION_SPECIAL_VALUES_SUPPORT_NONE = 0, 
#line 151
CUDA_EMULATION_SPECIAL_VALUES_SUPPORT_INFINITY, 
#line 155
CUDA_EMULATION_SPECIAL_VALUES_SUPPORT_NAN
#line 156
} cudaEmulationSpecialValuesSupport; 
#line 163
typedef 
#line 158
enum libraryPropertyType_t { 
#line 160
MAJOR_VERSION, 
#line 161
MINOR_VERSION, 
#line 162
PATCH_LEVEL
#line 163
} libraryPropertyType; 
#line 13 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_malloc.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 17
__pragma( pack ( push, 8 )) extern "C" {
#line 58 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_malloc.h"
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 59
_calloc_base(size_t _Count, size_t _Size); 
#line 65
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 66
calloc(size_t _Count, size_t _Size); 
#line 72
int __cdecl _callnewh(size_t _Size); 
#line 77
__declspec(allocator) void *__cdecl 
#line 78
_expand(void * _Block, size_t _Size); 
#line 84
void __cdecl _free_base(void * _Block); 
#line 89
void __cdecl free(void * _Block); 
#line 94
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 95
_malloc_base(size_t _Size); 
#line 100
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 101
malloc(size_t _Size); 
#line 107
size_t __cdecl _msize_base(void * _Block) noexcept; 
#line 113
size_t __cdecl _msize(void * _Block); 
#line 118
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 119
_realloc_base(void * _Block, size_t _Size); 
#line 125
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 126
realloc(void * _Block, size_t _Size); 
#line 132
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 133
_recalloc_base(void * _Block, size_t _Count, size_t _Size); 
#line 140
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 141
_recalloc(void * _Block, size_t _Count, size_t _Size); 
#line 148
void __cdecl _aligned_free(void * _Block); 
#line 153
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 154
_aligned_malloc(size_t _Size, size_t _Alignment); 
#line 160
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 161
_aligned_offset_malloc(size_t _Size, size_t _Alignment, size_t _Offset); 
#line 169
size_t __cdecl _aligned_msize(void * _Block, size_t _Alignment, size_t _Offset); 
#line 176
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 177
_aligned_offset_realloc(void * _Block, size_t _Size, size_t _Alignment, size_t _Offset); 
#line 185
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 186
_aligned_offset_recalloc(void * _Block, size_t _Count, size_t _Size, size_t _Alignment, size_t _Offset); 
#line 195
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 196
_aligned_realloc(void * _Block, size_t _Size, size_t _Alignment); 
#line 203
__declspec(allocator) __declspec(restrict) void *__cdecl 
#line 204
_aligned_recalloc(void * _Block, size_t _Count, size_t _Size, size_t _Alignment); 
#line 232 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_malloc.h"
}__pragma( pack ( pop )) 
#line 234
#pragma warning(pop)
#line 16 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_search.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 20
__pragma( pack ( push, 8 )) extern "C" {
#line 23
typedef int (__cdecl *_CoreCrtSecureSearchSortCompareFunction)(void *, const void *, const void *); 
#line 24
typedef int (__cdecl *_CoreCrtNonSecureSearchSortCompareFunction)(const void *, const void *); 
#line 30
void *__cdecl bsearch_s(const void * _Key, const void * _Base, rsize_t _NumOfElements, rsize_t _SizeOfElements, _CoreCrtSecureSearchSortCompareFunction _CompareFunction, void * _Context); 
#line 39
void __cdecl qsort_s(void * _Base, rsize_t _NumOfElements, rsize_t _SizeOfElements, _CoreCrtSecureSearchSortCompareFunction _CompareFunction, void * _Context); 
#line 52 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_search.h"
void *__cdecl bsearch(const void * _Key, const void * _Base, size_t _NumOfElements, size_t _SizeOfElements, _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction); 
#line 60
void __cdecl qsort(void * _Base, size_t _NumOfElements, size_t _SizeOfElements, _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction); 
#line 68
void *__cdecl _lfind_s(const void * _Key, const void * _Base, unsigned * _NumOfElements, size_t _SizeOfElements, _CoreCrtSecureSearchSortCompareFunction _CompareFunction, void * _Context); 
#line 78
void *__cdecl _lfind(const void * _Key, const void * _Base, unsigned * _NumOfElements, unsigned _SizeOfElements, _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction); 
#line 87
void *__cdecl _lsearch_s(const void * _Key, void * _Base, unsigned * _NumOfElements, size_t _SizeOfElements, _CoreCrtSecureSearchSortCompareFunction _CompareFunction, void * _Context); 
#line 97
void *__cdecl _lsearch(const void * _Key, void * _Base, unsigned * _NumOfElements, unsigned _SizeOfElements, _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction); 
#line 195 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_search.h"
void *__cdecl lfind(const void * _Key, const void * _Base, unsigned * _NumOfElements, unsigned _SizeOfElements, _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction); 
#line 204
void *__cdecl lsearch(const void * _Key, void * _Base, unsigned * _NumOfElements, unsigned _SizeOfElements, _CoreCrtNonSecureSearchSortCompareFunction _CompareFunction); 
#line 216 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_search.h"
}__pragma( pack ( pop )) 
#line 218
#pragma warning(pop)
#line 13 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 17
__pragma( pack ( push, 8 )) extern "C" {
#line 54
errno_t __cdecl _itow_s(int _Value, __wchar_t * _Buffer, size_t _BufferCount, int _Radix); 
#line 61
extern "C++" {template < size_t _Size > inline errno_t __cdecl _itow_s ( int _Value, wchar_t ( & _Buffer ) [ _Size ], int _Radix ) throw ( ) { return _itow_s ( _Value, _Buffer, _Size, _Radix ); }}
#line 68 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
__wchar_t *__cdecl _itow(int _Value, __wchar_t * _Buffer, int _Radix); 
#line 77 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
errno_t __cdecl _ltow_s(long _Value, __wchar_t * _Buffer, size_t _BufferCount, int _Radix); 
#line 84
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ltow_s ( long _Value, wchar_t ( & _Buffer ) [ _Size ], int _Radix ) throw ( ) { return _ltow_s ( _Value, _Buffer, _Size, _Radix ); }}
#line 91 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
__wchar_t *__cdecl _ltow(long _Value, __wchar_t * _Buffer, int _Radix); 
#line 99 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
errno_t __cdecl _ultow_s(unsigned long _Value, __wchar_t * _Buffer, size_t _BufferCount, int _Radix); 
#line 106
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ultow_s ( unsigned long _Value, wchar_t ( & _Buffer ) [ _Size ], int _Radix ) throw ( ) { return _ultow_s ( _Value, _Buffer, _Size, _Radix ); }}
#line 113 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
__wchar_t *__cdecl _ultow(unsigned long _Value, __wchar_t * _Buffer, int _Radix); 
#line 121 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
double __cdecl wcstod(const __wchar_t * _String, __wchar_t ** _EndPtr); 
#line 127
double __cdecl _wcstod_l(const __wchar_t * _String, __wchar_t ** _EndPtr, _locale_t _Locale); 
#line 134
long __cdecl wcstol(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix); 
#line 141
long __cdecl _wcstol_l(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 149
__int64 __cdecl wcstoll(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix); 
#line 156
__int64 __cdecl _wcstoll_l(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 164
unsigned long __cdecl wcstoul(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix); 
#line 171
unsigned long __cdecl _wcstoul_l(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 179
unsigned __int64 __cdecl wcstoull(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix); 
#line 186
unsigned __int64 __cdecl _wcstoull_l(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 194
long double __cdecl wcstold(const __wchar_t * _String, __wchar_t ** _EndPtr); 
#line 200
long double __cdecl _wcstold_l(const __wchar_t * _String, __wchar_t ** _EndPtr, _locale_t _Locale); 
#line 207
float __cdecl wcstof(const __wchar_t * _String, __wchar_t ** _EndPtr); 
#line 213
float __cdecl _wcstof_l(const __wchar_t * _String, __wchar_t ** _EndPtr, _locale_t _Locale); 
#line 220
double __cdecl _wtof(const __wchar_t * _String); 
#line 225
double __cdecl _wtof_l(const __wchar_t * _String, _locale_t _Locale); 
#line 231
int __cdecl _wtoi(const __wchar_t * _String); 
#line 236
int __cdecl _wtoi_l(const __wchar_t * _String, _locale_t _Locale); 
#line 242
long __cdecl _wtol(const __wchar_t * _String); 
#line 247
long __cdecl _wtol_l(const __wchar_t * _String, _locale_t _Locale); 
#line 253
__int64 __cdecl _wtoll(const __wchar_t * _String); 
#line 258
__int64 __cdecl _wtoll_l(const __wchar_t * _String, _locale_t _Locale); 
#line 264
errno_t __cdecl _i64tow_s(__int64 _Value, __wchar_t * _Buffer, size_t _BufferCount, int _Radix); 
#line 272
__wchar_t *__cdecl _i64tow(__int64 _Value, __wchar_t * _Buffer, int _Radix); 
#line 279
errno_t __cdecl _ui64tow_s(unsigned __int64 _Value, __wchar_t * _Buffer, size_t _BufferCount, int _Radix); 
#line 287
__wchar_t *__cdecl _ui64tow(unsigned __int64 _Value, __wchar_t * _Buffer, int _Radix); 
#line 294
__int64 __cdecl _wtoi64(const __wchar_t * _String); 
#line 299
__int64 __cdecl _wtoi64_l(const __wchar_t * _String, _locale_t _Locale); 
#line 305
__int64 __cdecl _wcstoi64(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix); 
#line 312
__int64 __cdecl _wcstoi64_l(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 320
unsigned __int64 __cdecl _wcstoui64(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix); 
#line 327
unsigned __int64 __cdecl _wcstoui64_l(const __wchar_t * _String, __wchar_t ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 339
__declspec(allocator) __wchar_t *__cdecl _wfullpath(__wchar_t * _Buffer, const __wchar_t * _Path, size_t _BufferCount); 
#line 348
errno_t __cdecl _wmakepath_s(__wchar_t * _Buffer, size_t _BufferCount, const __wchar_t * _Drive, const __wchar_t * _Dir, const __wchar_t * _Filename, const __wchar_t * _Ext); 
#line 357
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wmakepath_s ( wchar_t ( & _Buffer ) [ _Size ], wchar_t const * _Drive, wchar_t const * _Dir, wchar_t const * _Filename, wchar_t const * _Ext ) throw ( ) { return _wmakepath_s ( _Buffer, _Size, _Drive, _Dir, _Filename, _Ext ); }}
#line 366 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
void __cdecl _wmakepath(__wchar_t * _Buffer, const __wchar_t * _Drive, const __wchar_t * _Dir, const __wchar_t * _Filename, const __wchar_t * _Ext); 
#line 375 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
void __cdecl _wperror(const __wchar_t * _ErrorMessage); 
#line 380
void __cdecl _wsplitpath(const __wchar_t * _FullPath, __wchar_t * _Drive, __wchar_t * _Dir, __wchar_t * _Filename, __wchar_t * _Ext); 
#line 388
errno_t __cdecl _wsplitpath_s(const __wchar_t * _FullPath, __wchar_t * _Drive, size_t _DriveCount, __wchar_t * _Dir, size_t _DirCount, __wchar_t * _Filename, size_t _FilenameCount, __wchar_t * _Ext, size_t _ExtCount); 
#line 400
extern "C++" {template < size_t _DriveSize, size_t _DirSize, size_t _NameSize, size_t _ExtSize > inline errno_t __cdecl _wsplitpath_s ( wchar_t const * _Path, wchar_t ( & _Drive ) [ _DriveSize ], wchar_t ( & _Dir ) [ _DirSize ], wchar_t ( & _Name ) [ _NameSize ], wchar_t ( & _Ext ) [ _ExtSize ] ) throw ( ) { return _wsplitpath_s ( _Path, _Drive, _DriveSize, _Dir, _DirSize, _Name, _NameSize, _Ext, _ExtSize ); }}
#line 409 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
errno_t __cdecl _wdupenv_s(__wchar_t ** _Buffer, size_t * _BufferCount, const __wchar_t * _VarName); 
#line 418
__wchar_t *__cdecl _wgetenv(const __wchar_t * _VarName); 
#line 424
errno_t __cdecl _wgetenv_s(size_t * _RequiredCount, __wchar_t * _Buffer, size_t _BufferCount, const __wchar_t * _VarName); 
#line 431
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wgetenv_s ( size_t * _RequiredCount, wchar_t ( & _Buffer ) [ _Size ], wchar_t const * _VarName ) throw ( ) { return _wgetenv_s ( _RequiredCount, _Buffer, _Size, _VarName ); }}
#line 440 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
int __cdecl _wputenv(const __wchar_t * _EnvString); 
#line 445
errno_t __cdecl _wputenv_s(const __wchar_t * _Name, const __wchar_t * _Value); 
#line 450
errno_t __cdecl _wsearchenv_s(const __wchar_t * _Filename, const __wchar_t * _VarName, __wchar_t * _Buffer, size_t _BufferCount); 
#line 457
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wsearchenv_s ( wchar_t const * _Filename, wchar_t const * _VarName, wchar_t ( & _ResultPath ) [ _Size ] ) throw ( ) { return _wsearchenv_s ( _Filename, _VarName, _ResultPath, _Size ); }}
#line 464 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
void __cdecl _wsearchenv(const __wchar_t * _Filename, const __wchar_t * _VarName, __wchar_t * _ResultPath); 
#line 471 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
int __cdecl _wsystem(const __wchar_t * _Command); 
#line 479 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstdlib.h"
}__pragma( pack ( pop )) 
#line 481
#pragma warning(pop)
#line 18 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 22
__pragma( pack ( push, 8 )) extern "C" {
#line 38 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
void __cdecl _swab(char * _Buf1, char * _Buf2, int _SizeInBytes); 
#line 56
__declspec(noreturn) void __cdecl exit(int _Code); 
#line 57
__declspec(noreturn) void __cdecl _exit(int _Code); 
#line 58
__declspec(noreturn) void __cdecl _Exit(int _Code); 
#line 59
__declspec(noreturn) void __cdecl quick_exit(int _Code); 
#line 60
__declspec(noreturn) void __cdecl abort(); 
#line 67 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
unsigned __cdecl _set_abort_behavior(unsigned _Flags, unsigned _Mask); 
#line 77
typedef int (__cdecl *_onexit_t)(void); 
#line 144 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
int __cdecl atexit(void (__cdecl *)(void)); 
#line 145
_onexit_t __cdecl _onexit(_onexit_t _Func); 
#line 148 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
int __cdecl at_quick_exit(void (__cdecl *)(void)); 
#line 159
typedef void (__cdecl *_purecall_handler)(void); 
#line 162
typedef void (__cdecl *_invalid_parameter_handler)(const __wchar_t *, const __wchar_t *, const __wchar_t *, unsigned, uintptr_t); 
#line 171
_purecall_handler __cdecl _set_purecall_handler(_purecall_handler _Handler); 
#line 175
_purecall_handler __cdecl _get_purecall_handler(); 
#line 178
_invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_invalid_parameter_handler _Handler); 
#line 182
_invalid_parameter_handler __cdecl _get_invalid_parameter_handler(); 
#line 184
_invalid_parameter_handler __cdecl _set_thread_local_invalid_parameter_handler(_invalid_parameter_handler _Handler); 
#line 188
_invalid_parameter_handler __cdecl _get_thread_local_invalid_parameter_handler(); 
#line 212 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
int __cdecl _set_error_mode(int _Mode); 
#line 217
int *__cdecl _errno(); 
#line 220
errno_t __cdecl _set_errno(int _Value); 
#line 221
errno_t __cdecl _get_errno(int * _Value); 
#line 223
unsigned long *__cdecl __doserrno(); 
#line 226
errno_t __cdecl _set_doserrno(unsigned long _Value); 
#line 227
errno_t __cdecl _get_doserrno(unsigned long * _Value); 
#line 230
char **__cdecl __sys_errlist(); 
#line 233
int *__cdecl __sys_nerr(); 
#line 236
void __cdecl perror(const char * _ErrMsg); 
#line 242 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char **__cdecl __p__pgmptr(); 
#line 243
__wchar_t **__cdecl __p__wpgmptr(); 
#line 244
int *__cdecl __p__fmode(); 
#line 259 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _get_pgmptr(char ** _Value); 
#line 262
errno_t __cdecl _get_wpgmptr(__wchar_t ** _Value); 
#line 264
errno_t __cdecl _set_fmode(int _Mode); 
#line 266
errno_t __cdecl _get_fmode(int * _PMode); 
#line 279
typedef 
#line 275
struct _div_t { 
#line 277
int quot; 
#line 278
int rem; 
#line 279
} div_t; 
#line 285
typedef 
#line 281
struct _ldiv_t { 
#line 283
long quot; 
#line 284
long rem; 
#line 285
} ldiv_t; 
#line 291
typedef 
#line 287
struct _lldiv_t { 
#line 289
__int64 quot; 
#line 290
__int64 rem; 
#line 291
} lldiv_t; 
#line 293
int __cdecl abs(int _Number); 
#line 294
long __cdecl labs(long _Number); 
#line 295
__int64 __cdecl llabs(__int64 _Number); 
#line 296
__int64 __cdecl _abs64(__int64 _Number); 
#line 298
unsigned short __cdecl _byteswap_ushort(unsigned short _Number); 
#line 299
unsigned long __cdecl _byteswap_ulong(unsigned long _Number); 
#line 300
unsigned __int64 __cdecl _byteswap_uint64(unsigned __int64 _Number); 
#line 302
div_t __cdecl div(int _Numerator, int _Denominator); 
#line 303
ldiv_t __cdecl ldiv(long _Numerator, long _Denominator); 
#line 304
lldiv_t __cdecl lldiv(__int64 _Numerator, __int64 _Denominator); 
#line 308
#pragma warning(push)
#pragma warning(disable: 6540)
#line 311
unsigned __cdecl _rotl(unsigned _Value, int _Shift); 
#line 317
unsigned long __cdecl _lrotl(unsigned long _Value, int _Shift); 
#line 322
unsigned __int64 __cdecl _rotl64(unsigned __int64 _Value, int _Shift); 
#line 327
unsigned __cdecl _rotr(unsigned _Value, int _Shift); 
#line 333
unsigned long __cdecl _lrotr(unsigned long _Value, int _Shift); 
#line 338
unsigned __int64 __cdecl _rotr64(unsigned __int64 _Value, int _Shift); 
#line 343
#pragma warning(pop)
#line 350
void __cdecl srand(unsigned _Seed); 
#line 352
int __cdecl rand(); 
#line 361 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
extern "C++" {
#line 363
inline long abs(const long _X) throw() 
#line 364
{ 
#line 365
return labs(_X); 
#line 366
} 
#line 368
inline __int64 abs(const __int64 _X) throw() 
#line 369
{ 
#line 370
return llabs(_X); 
#line 371
} 
#line 373
inline ldiv_t div(const long _A1, const long _A2) throw() 
#line 374
{ 
#line 375
return ldiv(_A1, _A2); 
#line 376
} 
#line 378
inline lldiv_t div(const __int64 _A1, const __int64 _A2) throw() 
#line 379
{ 
#line 380
return lldiv(_A1, _A2); 
#line 381
} 
#line 382
}
#line 394 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
#pragma pack ( push, 4 )
#line 398
typedef 
#line 396
struct { 
#line 397
unsigned char ld[10]; 
#line 398
} _LDOUBLE; 
#pragma pack ( pop )
#line 418 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
typedef 
#line 416
struct { 
#line 417
double x; 
#line 418
} _CRT_DOUBLE; 
#line 423
typedef 
#line 421
struct { 
#line 422
float f; 
#line 423
} _CRT_FLOAT; 
#line 432
typedef 
#line 430
struct { 
#line 431
long double x; 
#line 432
} _LONGDOUBLE; 
#line 436
#pragma pack ( push, 4 )
#line 440
typedef 
#line 438
struct { 
#line 439
unsigned char ld12[12]; 
#line 440
} _LDBL12; 
#pragma pack ( pop )
#line 450
double __cdecl atof(const char * _String); 
#line 451
int __cdecl atoi(const char * _String); 
#line 452
long __cdecl atol(const char * _String); 
#line 453
__int64 __cdecl atoll(const char * _String); 
#line 454
__int64 __cdecl _atoi64(const char * _String); 
#line 456
double __cdecl _atof_l(const char * _String, _locale_t _Locale); 
#line 457
int __cdecl _atoi_l(const char * _String, _locale_t _Locale); 
#line 458
long __cdecl _atol_l(const char * _String, _locale_t _Locale); 
#line 459
__int64 __cdecl _atoll_l(const char * _String, _locale_t _Locale); 
#line 460
__int64 __cdecl _atoi64_l(const char * _String, _locale_t _Locale); 
#line 462
int __cdecl _atoflt(_CRT_FLOAT * _Result, const char * _String); 
#line 463
int __cdecl _atodbl(_CRT_DOUBLE * _Result, char * _String); 
#line 464
int __cdecl _atoldbl(_LDOUBLE * _Result, char * _String); 
#line 467
int __cdecl _atoflt_l(_CRT_FLOAT * _Result, const char * _String, _locale_t _Locale); 
#line 474
int __cdecl _atodbl_l(_CRT_DOUBLE * _Result, char * _String, _locale_t _Locale); 
#line 482
int __cdecl _atoldbl_l(_LDOUBLE * _Result, char * _String, _locale_t _Locale); 
#line 489
float __cdecl strtof(const char * _String, char ** _EndPtr); 
#line 495
float __cdecl _strtof_l(const char * _String, char ** _EndPtr, _locale_t _Locale); 
#line 502
double __cdecl strtod(const char * _String, char ** _EndPtr); 
#line 508
double __cdecl _strtod_l(const char * _String, char ** _EndPtr, _locale_t _Locale); 
#line 515
long double __cdecl strtold(const char * _String, char ** _EndPtr); 
#line 521
long double __cdecl _strtold_l(const char * _String, char ** _EndPtr, _locale_t _Locale); 
#line 528
long __cdecl strtol(const char * _String, char ** _EndPtr, int _Radix); 
#line 535
long __cdecl _strtol_l(const char * _String, char ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 543
__int64 __cdecl strtoll(const char * _String, char ** _EndPtr, int _Radix); 
#line 550
__int64 __cdecl _strtoll_l(const char * _String, char ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 558
unsigned long __cdecl strtoul(const char * _String, char ** _EndPtr, int _Radix); 
#line 565
unsigned long __cdecl _strtoul_l(const char * _String, char ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 573
unsigned __int64 __cdecl strtoull(const char * _String, char ** _EndPtr, int _Radix); 
#line 580
unsigned __int64 __cdecl _strtoull_l(const char * _String, char ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 588
__int64 __cdecl _strtoi64(const char * _String, char ** _EndPtr, int _Radix); 
#line 595
__int64 __cdecl _strtoi64_l(const char * _String, char ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 603
unsigned __int64 __cdecl _strtoui64(const char * _String, char ** _EndPtr, int _Radix); 
#line 610
unsigned __int64 __cdecl _strtoui64_l(const char * _String, char ** _EndPtr, int _Radix, _locale_t _Locale); 
#line 626
errno_t __cdecl _itoa_s(int _Value, char * _Buffer, size_t _BufferCount, int _Radix); 
#line 633
extern "C++" {template < size_t _Size > inline errno_t __cdecl _itoa_s ( int _Value, char ( & _Buffer ) [ _Size ], int _Radix ) throw ( ) { return _itoa_s ( _Value, _Buffer, _Size, _Radix ); }}
#line 641 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl _itoa(int _Value, char * _Buffer, int _Radix); 
#line 650 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _ltoa_s(long _Value, char * _Buffer, size_t _BufferCount, int _Radix); 
#line 657
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ltoa_s ( long _Value, char ( & _Buffer ) [ _Size ], int _Radix ) throw ( ) { return _ltoa_s ( _Value, _Buffer, _Size, _Radix ); }}
#line 664 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl _ltoa(long _Value, char * _Buffer, int _Radix); 
#line 673 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _ultoa_s(unsigned long _Value, char * _Buffer, size_t _BufferCount, int _Radix); 
#line 680
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ultoa_s ( unsigned long _Value, char ( & _Buffer ) [ _Size ], int _Radix ) throw ( ) { return _ultoa_s ( _Value, _Buffer, _Size, _Radix ); }}
#line 687 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl _ultoa(unsigned long _Value, char * _Buffer, int _Radix); 
#line 696 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _i64toa_s(__int64 _Value, char * _Buffer, size_t _BufferCount, int _Radix); 
#line 705
char *__cdecl _i64toa(__int64 _Value, char * _Buffer, int _Radix); 
#line 713
errno_t __cdecl _ui64toa_s(unsigned __int64 _Value, char * _Buffer, size_t _BufferCount, int _Radix); 
#line 721
char *__cdecl _ui64toa(unsigned __int64 _Value, char * _Buffer, int _Radix); 
#line 741
errno_t __cdecl _ecvt_s(char * _Buffer, size_t _BufferCount, double _Value, int _DigitCount, int * _PtDec, int * _PtSign); 
#line 750
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ecvt_s ( char ( & _Buffer ) [ _Size ], double _Value, int _DigitCount, int * _PtDec, int * _PtSign ) throw ( ) { return _ecvt_s ( _Buffer, _Size, _Value, _DigitCount, _PtDec, _PtSign ); }}
#line 760 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl _ecvt(double _Value, int _DigitCount, int * _PtDec, int * _PtSign); 
#line 769
errno_t __cdecl _fcvt_s(char * _Buffer, size_t _BufferCount, double _Value, int _FractionalDigitCount, int * _PtDec, int * _PtSign); 
#line 778
extern "C++" {template < size_t _Size > inline errno_t __cdecl _fcvt_s ( char ( & _Buffer ) [ _Size ], double _Value, int _FractionalDigitCount, int * _PtDec, int * _PtSign ) throw ( ) { return _fcvt_s ( _Buffer, _Size, _Value, _FractionalDigitCount, _PtDec, _PtSign ); }}
#line 790 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl _fcvt(double _Value, int _FractionalDigitCount, int * _PtDec, int * _PtSign); 
#line 798
errno_t __cdecl _gcvt_s(char * _Buffer, size_t _BufferCount, double _Value, int _DigitCount); 
#line 805
extern "C++" {template < size_t _Size > inline errno_t __cdecl _gcvt_s ( char ( & _Buffer ) [ _Size ], double _Value, int _DigitCount ) throw ( ) { return _gcvt_s ( _Buffer, _Size, _Value, _DigitCount ); }}
#line 814 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl _gcvt(double _Value, int _DigitCount, char * _Buffer); 
#line 852
int __cdecl mblen(const char * _Ch, size_t _MaxCount); 
#line 858
int __cdecl _mblen_l(const char * _Ch, size_t _MaxCount, _locale_t _Locale); 
#line 866
size_t __cdecl _mbstrlen(const char * _String); 
#line 872
size_t __cdecl _mbstrlen_l(const char * _String, _locale_t _Locale); 
#line 879
size_t __cdecl _mbstrnlen(const char * _String, size_t _MaxCount); 
#line 886
size_t __cdecl _mbstrnlen_l(const char * _String, size_t _MaxCount, _locale_t _Locale); 
#line 893
int __cdecl mbtowc(__wchar_t * _DstCh, const char * _SrcCh, size_t _SrcSizeInBytes); 
#line 900
int __cdecl _mbtowc_l(__wchar_t * _DstCh, const char * _SrcCh, size_t _SrcSizeInBytes, _locale_t _Locale); 
#line 908
errno_t __cdecl mbstowcs_s(size_t * _PtNumOfCharConverted, __wchar_t * _DstBuf, size_t _SizeInWords, const char * _SrcBuf, size_t _MaxCount); 
#line 916
extern "C++" {template < size_t _Size > inline errno_t __cdecl mbstowcs_s ( size_t * _PtNumOfCharConverted, wchar_t ( & _Dest ) [ _Size ], char const * _Source, size_t _MaxCount ) throw ( ) { return mbstowcs_s ( _PtNumOfCharConverted, _Dest, _Size, _Source, _MaxCount ); }}
#line 924 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
size_t __cdecl mbstowcs(__wchar_t * _Dest, const char * _Source, size_t _MaxCount); 
#line 932 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _mbstowcs_s_l(size_t * _PtNumOfCharConverted, __wchar_t * _DstBuf, size_t _SizeInWords, const char * _SrcBuf, size_t _MaxCount, _locale_t _Locale); 
#line 941
extern "C++" {template < size_t _Size > inline errno_t __cdecl _mbstowcs_s_l ( size_t * _PtNumOfCharConverted, wchar_t ( & _Dest ) [ _Size ], char const * _Source, size_t _MaxCount, _locale_t _Locale ) throw ( ) { return _mbstowcs_s_l ( _PtNumOfCharConverted, _Dest, _Size, _Source, _MaxCount, _Locale ); }}
#line 950 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
size_t __cdecl _mbstowcs_l(__wchar_t * _Dest, const char * _Source, size_t _MaxCount, _locale_t _Locale); 
#line 963 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
int __cdecl wctomb(char * _MbCh, __wchar_t _WCh); 
#line 969
int __cdecl _wctomb_l(char * _MbCh, __wchar_t _WCh, _locale_t _Locale); 
#line 978
errno_t __cdecl wctomb_s(int * _SizeConverted, char * _MbCh, rsize_t _SizeInBytes, __wchar_t _WCh); 
#line 988 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _wctomb_s_l(int * _SizeConverted, char * _MbCh, size_t _SizeInBytes, __wchar_t _WCh, _locale_t _Locale); 
#line 996
errno_t __cdecl wcstombs_s(size_t * _PtNumOfCharConverted, char * _Dst, size_t _DstSizeInBytes, const __wchar_t * _Src, size_t _MaxCountInBytes); 
#line 1004
extern "C++" {template < size_t _Size > inline errno_t __cdecl wcstombs_s ( size_t * _PtNumOfCharConverted, char ( & _Dest ) [ _Size ], wchar_t const * _Source, size_t _MaxCount ) throw ( ) { return wcstombs_s ( _PtNumOfCharConverted, _Dest, _Size, _Source, _MaxCount ); }}
#line 1012 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
size_t __cdecl wcstombs(char * _Dest, const __wchar_t * _Source, size_t _MaxCount); 
#line 1020 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _wcstombs_s_l(size_t * _PtNumOfCharConverted, char * _Dst, size_t _DstSizeInBytes, const __wchar_t * _Src, size_t _MaxCountInBytes, _locale_t _Locale); 
#line 1029
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcstombs_s_l ( size_t * _PtNumOfCharConverted, char ( & _Dest ) [ _Size ], wchar_t const * _Source, size_t _MaxCount, _locale_t _Locale ) throw ( ) { return _wcstombs_s_l ( _PtNumOfCharConverted, _Dest, _Size, _Source, _MaxCount, _Locale ); }}
#line 1038 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
size_t __cdecl _wcstombs_l(char * _Dest, const __wchar_t * _Source, size_t _MaxCount, _locale_t _Locale); 
#line 1068 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
__declspec(allocator) char *__cdecl _fullpath(char * _Buffer, const char * _Path, size_t _BufferCount); 
#line 1077
errno_t __cdecl _makepath_s(char * _Buffer, size_t _BufferCount, const char * _Drive, const char * _Dir, const char * _Filename, const char * _Ext); 
#line 1086
extern "C++" {template < size_t _Size > inline errno_t __cdecl _makepath_s ( char ( & _Buffer ) [ _Size ], char const * _Drive, char const * _Dir, char const * _Filename, char const * _Ext ) throw ( ) { return _makepath_s ( _Buffer, _Size, _Drive, _Dir, _Filename, _Ext ); }}
#line 1095 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
void __cdecl _makepath(char * _Buffer, const char * _Drive, const char * _Dir, const char * _Filename, const char * _Ext); 
#line 1105 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
void __cdecl _splitpath(const char * _FullPath, char * _Drive, char * _Dir, char * _Filename, char * _Ext); 
#line 1114
errno_t __cdecl _splitpath_s(const char * _FullPath, char * _Drive, size_t _DriveCount, char * _Dir, size_t _DirCount, char * _Filename, size_t _FilenameCount, char * _Ext, size_t _ExtCount); 
#line 1126
extern "C++" {template < size_t _DriveSize, size_t _DirSize, size_t _NameSize, size_t _ExtSize > inline errno_t __cdecl _splitpath_s ( char const * _Dest, char ( & _Drive ) [ _DriveSize ], char ( & _Dir ) [ _DirSize ], char ( & _Name ) [ _NameSize ], char ( & _Ext ) [ _ExtSize ] ) throw ( ) { return _splitpath_s ( _Dest, _Drive, _DriveSize, _Dir, _DirSize, _Name, _NameSize, _Ext, _ExtSize ); }}
#line 1132
errno_t __cdecl getenv_s(size_t * _RequiredCount, char * _Buffer, rsize_t _BufferCount, const char * _VarName); 
#line 1144 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
int *__cdecl __p___argc(); 
#line 1145
char ***__cdecl __p___argv(); 
#line 1146
__wchar_t ***__cdecl __p___wargv(); 
#line 1158 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char ***__cdecl __p__environ(); 
#line 1159
__wchar_t ***__cdecl __p__wenviron(); 
#line 1184 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
char *__cdecl getenv(const char * _VarName); 
#line 1188
extern "C++" {template < size_t _Size > inline errno_t __cdecl getenv_s ( size_t * _RequiredCount, char ( & _Buffer ) [ _Size ], char const * _VarName ) throw ( ) { return getenv_s ( _RequiredCount, _Buffer, _Size, _VarName ); }}
#line 1201 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
errno_t __cdecl _dupenv_s(char ** _Buffer, size_t * _BufferCount, const char * _VarName); 
#line 1211 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
int __cdecl system(const char * _Command); 
#line 1217
#pragma warning(push)
#pragma warning(disable: 6540)
#line 1221
int __cdecl _putenv(const char * _EnvString); 
#line 1226
errno_t __cdecl _putenv_s(const char * _Name, const char * _Value); 
#line 1231
#pragma warning(pop)
#line 1233
errno_t __cdecl _searchenv_s(const char * _Filename, const char * _VarName, char * _Buffer, size_t _BufferCount); 
#line 1240
extern "C++" {template < size_t _Size > inline errno_t __cdecl _searchenv_s ( char const * _Filename, char const * _VarName, char ( & _Buffer ) [ _Size ] ) throw ( ) { return _searchenv_s ( _Filename, _VarName, _Buffer, _Size ); }}
#line 1247 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
void __cdecl _searchenv(const char * _Filename, const char * _VarName, char * _Buffer); 
#line 1255 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
__declspec(deprecated("This function or variable has been superceded by newer library or operating system functionality. Consider using SetErrorMode in" "stead. See online help for details.")) void __cdecl 
#line 1256
_seterrormode(int _Mode); 
#line 1260
__declspec(deprecated("This function or variable has been superceded by newer library or operating system functionality. Consider using Beep instead. S" "ee online help for details.")) void __cdecl 
#line 1261
_beep(unsigned _Frequency, unsigned _Duration); 
#line 1266
__declspec(deprecated("This function or variable has been superceded by newer library or operating system functionality. Consider using Sleep instead. " "See online help for details.")) void __cdecl 
#line 1267
_sleep(unsigned long _Duration); 
#line 1289 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
#pragma warning(push)
#pragma warning(disable: 4141)
#line 1293
char *__cdecl ecvt(double _Value, int _DigitCount, int * _PtDec, int * _PtSign); 
#line 1301
char *__cdecl fcvt(double _Value, int _FractionalDigitCount, int * _PtDec, int * _PtSign); 
#line 1309
char *__cdecl gcvt(double _Value, int _DigitCount, char * _DstBuf); 
#line 1316
char *__cdecl itoa(int _Value, char * _Buffer, int _Radix); 
#line 1323
char *__cdecl ltoa(long _Value, char * _Buffer, int _Radix); 
#line 1331
void __cdecl swab(char * _Buf1, char * _Buf2, int _SizeInBytes); 
#line 1338
char *__cdecl ultoa(unsigned long _Value, char * _Buffer, int _Radix); 
#line 1347
int __cdecl putenv(const char * _EnvString); 
#line 1351
#pragma warning(pop)
#line 1353
_onexit_t __cdecl onexit(_onexit_t _Func); 
#line 1359 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\stdlib.h"
}__pragma( pack ( pop )) 
#line 1361
#pragma warning(pop)
#line 184 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
extern "C" {
#line 191
extern cudaError_t __stdcall __cudaDeviceSynchronizeDeprecationAvoidance(); 
#line 244
extern cudaError_t __stdcall __cudaCDP2DeviceGetAttribute(int * value, cudaDeviceAttr attr, int device); 
#line 245
extern cudaError_t __stdcall __cudaCDP2DeviceGetLimit(size_t * pValue, cudaLimit limit); 
#line 246
extern cudaError_t __stdcall __cudaCDP2DeviceGetCacheConfig(cudaFuncCache * pCacheConfig); 
#line 247
extern cudaError_t __stdcall __cudaCDP2DeviceGetSharedMemConfig(cudaSharedMemConfig * pConfig); 
#line 248
extern cudaError_t __stdcall __cudaCDP2GetLastError(); 
#line 249
extern cudaError_t __stdcall __cudaCDP2PeekAtLastError(); 
#line 250
extern const char *__stdcall __cudaCDP2GetErrorString(cudaError_t error); 
#line 251
extern const char *__stdcall __cudaCDP2GetErrorName(cudaError_t error); 
#line 252
extern cudaError_t __stdcall __cudaCDP2GetDeviceCount(int * count); 
#line 253
extern cudaError_t __stdcall __cudaCDP2GetDevice(int * device); 
#line 254
extern cudaError_t __stdcall __cudaCDP2StreamCreateWithFlags(cudaStream_t * pStream, unsigned flags); 
#line 255
extern cudaError_t __stdcall __cudaCDP2StreamDestroy(cudaStream_t stream); 
#line 256
extern cudaError_t __stdcall __cudaCDP2StreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned flags); 
#line 257
extern cudaError_t __stdcall __cudaCDP2StreamWaitEvent_ptsz(cudaStream_t stream, cudaEvent_t event, unsigned flags); 
#line 258
extern cudaError_t __stdcall __cudaCDP2EventCreateWithFlags(cudaEvent_t * event, unsigned flags); 
#line 259
extern cudaError_t __stdcall __cudaCDP2EventRecord(cudaEvent_t event, cudaStream_t stream); 
#line 260
extern cudaError_t __stdcall __cudaCDP2EventRecord_ptsz(cudaEvent_t event, cudaStream_t stream); 
#line 261
extern cudaError_t __stdcall __cudaCDP2EventRecordWithFlags(cudaEvent_t event, cudaStream_t stream, unsigned flags); 
#line 262
extern cudaError_t __stdcall __cudaCDP2EventRecordWithFlags_ptsz(cudaEvent_t event, cudaStream_t stream, unsigned flags); 
#line 263
extern cudaError_t __stdcall __cudaCDP2EventDestroy(cudaEvent_t event); 
#line 264
extern cudaError_t __stdcall __cudaCDP2FuncGetAttributes(cudaFuncAttributes * attr, const void * func); 
#line 265
extern cudaError_t __stdcall __cudaCDP2Free(void * devPtr); 
#line 266
extern cudaError_t __stdcall __cudaCDP2Malloc(void ** devPtr, size_t size); 
#line 267
extern cudaError_t __stdcall __cudaCDP2MemcpyAsync(void * dst, const void * src, size_t count, cudaMemcpyKind kind, cudaStream_t stream); 
#line 268
extern cudaError_t __stdcall __cudaCDP2MemcpyAsync_ptsz(void * dst, const void * src, size_t count, cudaMemcpyKind kind, cudaStream_t stream); 
#line 269
extern cudaError_t __stdcall __cudaCDP2Memcpy2DAsync(void * dst, size_t dpitch, const void * src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream); 
#line 270
extern cudaError_t __stdcall __cudaCDP2Memcpy2DAsync_ptsz(void * dst, size_t dpitch, const void * src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream); 
#line 271
extern cudaError_t __stdcall __cudaCDP2Memcpy3DAsync(const cudaMemcpy3DParms * p, cudaStream_t stream); 
#line 272
extern cudaError_t __stdcall __cudaCDP2Memcpy3DAsync_ptsz(const cudaMemcpy3DParms * p, cudaStream_t stream); 
#line 273
extern cudaError_t __stdcall __cudaCDP2MemsetAsync(void * devPtr, int value, size_t count, cudaStream_t stream); 
#line 274
extern cudaError_t __stdcall __cudaCDP2MemsetAsync_ptsz(void * devPtr, int value, size_t count, cudaStream_t stream); 
#line 275
extern cudaError_t __stdcall __cudaCDP2Memset2DAsync(void * devPtr, size_t pitch, int value, size_t width, size_t height, cudaStream_t stream); 
#line 276
extern cudaError_t __stdcall __cudaCDP2Memset2DAsync_ptsz(void * devPtr, size_t pitch, int value, size_t width, size_t height, cudaStream_t stream); 
#line 277
extern cudaError_t __stdcall __cudaCDP2Memset3DAsync(cudaPitchedPtr pitchedDevPtr, int value, cudaExtent extent, cudaStream_t stream); 
#line 278
extern cudaError_t __stdcall __cudaCDP2Memset3DAsync_ptsz(cudaPitchedPtr pitchedDevPtr, int value, cudaExtent extent, cudaStream_t stream); 
#line 279
extern cudaError_t __stdcall __cudaCDP2RuntimeGetVersion(int * runtimeVersion); 
#line 280
extern void *__stdcall __cudaCDP2GetParameterBuffer(size_t alignment, size_t size); 
#line 281
extern void *__stdcall __cudaCDP2GetParameterBufferV2(void * func, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize); 
#line 282
extern cudaError_t __stdcall __cudaCDP2LaunchDevice_ptsz(void * func, void * parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize, cudaStream_t stream); 
#line 283
extern cudaError_t __stdcall __cudaCDP2LaunchDeviceV2_ptsz(void * parameterBuffer, cudaStream_t stream); 
#line 284
extern cudaError_t __stdcall __cudaCDP2LaunchDevice(void * func, void * parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize, cudaStream_t stream); 
#line 285
extern cudaError_t __stdcall __cudaCDP2LaunchDeviceV2(void * parameterBuffer, cudaStream_t stream); 
#line 286
extern cudaError_t __stdcall __cudaCDP2OccupancyMaxActiveBlocksPerMultiprocessor(int * numBlocks, const void * func, int blockSize, size_t dynamicSmemSize); 
#line 287
extern cudaError_t __stdcall __cudaCDP2OccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int * numBlocks, const void * func, int blockSize, size_t dynamicSmemSize, unsigned flags); 
#line 290
extern cudaError_t __stdcall cudaGraphLaunch(cudaGraphExec_t graphExec, cudaStream_t stream); 
#line 311 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static inline cudaGraphExec_t __stdcall cudaGetCurrentGraphExec() {int volatile ___ = 1;::exit(___);}
#if 0
#line 312
{ 
#line 313
unsigned __int64 current_graph_exec; 
#line 314
__asm mov.u64 %0, %%current_graph_exec;
return (cudaGraphExec_t)current_graph_exec; 
#line 316
} 
#endif
#line 346 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
extern cudaError_t __stdcall cudaGraphKernelNodeSetParam(cudaGraphDeviceNode_t node, size_t offset, const void * value, size_t size); 
#line 374
extern cudaError_t __stdcall cudaGraphKernelNodeSetEnabled(cudaGraphDeviceNode_t node, bool enable); 
#line 401
extern cudaError_t __stdcall cudaGraphKernelNodeSetGridDim(cudaGraphDeviceNode_t node, dim3 gridDim); 
#line 430
extern cudaError_t __stdcall cudaGraphKernelNodeUpdatesApply(const cudaGraphKernelNodeUpdate * updates, size_t updateCount); 
#line 448
static inline void __stdcall cudaTriggerProgrammaticLaunchCompletion() {int volatile ___ = 1;::exit(___);}
#if 0
#line 449
{ 
#line 450
__asm griddepcontrol.launch_dependents;
} 
#endif
#line 464 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static inline void __stdcall cudaGridDependencySynchronize() {int volatile ___ = 1;::exit(___);}
#if 0
#line 465
{ 
#line 466
__asm griddepcontrol.wait;
} 
#endif
#line 480 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
extern void __stdcall cudaGraphSetConditional(cudaGraphConditionalHandle handle, unsigned value); 
#line 483
extern unsigned __int64 __stdcall cudaCGGetIntrinsicHandle(cudaCGScope scope); 
#line 484
extern cudaError_t __stdcall cudaCGSynchronize(unsigned __int64 handle, unsigned flags); 
#line 485
extern cudaError_t __stdcall cudaCGSynchronizeGrid(unsigned __int64 handle, unsigned flags); 
#line 486
extern cudaError_t __stdcall cudaCGGetSize(unsigned * numThreads, unsigned * numGrids, unsigned __int64 handle); 
#line 487
extern cudaError_t __stdcall cudaCGGetRank(unsigned * threadRank, unsigned * gridRank, unsigned __int64 handle); 
#line 715
static __inline void *__stdcall cudaGetParameterBuffer(size_t alignment, size_t size) {int volatile ___ = 1;(void)alignment;(void)size;::exit(___);}
#if 0
#line 716
{ 
#line 717
return __cudaCDP2GetParameterBuffer(alignment, size); 
#line 718
} 
#endif
#line 725 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static __inline void *__stdcall cudaGetParameterBufferV2(void *func, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize) {int volatile ___ = 1;(void)func;(void)gridDimension;(void)blockDimension;(void)sharedMemSize;::exit(___);}
#if 0
#line 726
{ 
#line 727
return __cudaCDP2GetParameterBufferV2(func, gridDimension, blockDimension, sharedMemSize); 
#line 728
} 
#endif
#line 735 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static __inline cudaError_t __stdcall cudaLaunchDevice_ptsz(void *func, void *parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize, cudaStream_t stream) {int volatile ___ = 1;(void)func;(void)parameterBuffer;(void)gridDimension;(void)blockDimension;(void)sharedMemSize;(void)stream;::exit(___);}
#if 0
#line 736
{ 
#line 737
return __cudaCDP2LaunchDevice_ptsz(func, parameterBuffer, gridDimension, blockDimension, sharedMemSize, stream); 
#line 738
} 
#endif
#line 740 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static __inline cudaError_t __stdcall cudaLaunchDeviceV2_ptsz(void *parameterBuffer, cudaStream_t stream) {int volatile ___ = 1;(void)parameterBuffer;(void)stream;::exit(___);}
#if 0
#line 741
{ 
#line 742
return __cudaCDP2LaunchDeviceV2_ptsz(parameterBuffer, stream); 
#line 743
} 
#endif
#line 801 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static __inline cudaError_t __stdcall cudaLaunchDevice(void *func, void *parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize, cudaStream_t stream) {int volatile ___ = 1;(void)func;(void)parameterBuffer;(void)gridDimension;(void)blockDimension;(void)sharedMemSize;(void)stream;::exit(___);}
#if 0
#line 802
{ 
#line 803
return __cudaCDP2LaunchDevice(func, parameterBuffer, gridDimension, blockDimension, sharedMemSize, stream); 
#line 804
} 
#endif
#line 806 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
static __inline cudaError_t __stdcall cudaLaunchDeviceV2(void *parameterBuffer, cudaStream_t stream) {int volatile ___ = 1;(void)parameterBuffer;(void)stream;::exit(___);}
#if 0
#line 807
{ 
#line 808
return __cudaCDP2LaunchDeviceV2(parameterBuffer, stream); 
#line 809
} 
#endif
#line 863 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
}
#line 869
template< class T> static __inline cudaError_t cudaMalloc(T ** devPtr, size_t size); 
#line 870
template< class T> static __inline cudaError_t cudaFuncGetAttributes(cudaFuncAttributes * attr, T * entry); 
#line 871
template< class T> static __inline cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessor(int * numBlocks, T func, int blockSize, size_t dynamicSmemSize); 
#line 872
template< class T> static __inline cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int * numBlocks, T func, int blockSize, size_t dynamicSmemSize, unsigned flags); 
#line 902
template< class T> static __inline ::cudaError_t __stdcall 
#line 903
cudaGraphKernelNodeSetParam(::cudaGraphDeviceNode_t node, ::size_t offset, const T &value) {int volatile ___ = 1;(void)node;(void)offset;(void)value;::exit(___);}
#if 0
#line 904
{ 
#line 905
return cudaGraphKernelNodeSetParam(node, offset, &value, sizeof(T)); 
#line 906
} 
#endif
#line 935 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_device_runtime_api.h"
extern "C" cudaError_t __stdcall cudaFabricOpErrorStatusCount(void * status, cudaFabricOpStatusSource statusSource, unsigned * count); 
#line 960
extern "C" cudaError_t __stdcall cudaFabricOpErrorStatusGet(void * status, cudaFabricOpStatusSource statusSource, unsigned statusIndex, cudaFabricOpStatusInfo * statusInfo); 
#line 291 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern "C" {
#line 338 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaDeviceReset(); 
#line 361
extern cudaError_t __stdcall cudaDeviceSynchronize(); 
#line 447
extern cudaError_t __stdcall cudaDeviceSetLimit(cudaLimit limit, size_t value); 
#line 483
extern cudaError_t __stdcall cudaDeviceGetLimit(size_t * pValue, cudaLimit limit); 
#line 506
extern cudaError_t __stdcall cudaDeviceGetTexture1DLinearMaxWidth(size_t * maxWidthInElements, const cudaChannelFormatDesc * fmtDesc, int device); 
#line 540 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaDeviceGetCacheConfig(cudaFuncCache * pCacheConfig); 
#line 577
extern cudaError_t __stdcall cudaDeviceGetStreamPriorityRange(int * leastPriority, int * greatestPriority); 
#line 621
extern cudaError_t __stdcall cudaDeviceSetCacheConfig(cudaFuncCache cacheConfig); 
#line 648
extern cudaError_t __stdcall cudaDeviceGetByPCIBusId(int * device, const char * pciBusId); 
#line 678
extern cudaError_t __stdcall cudaDeviceGetPCIBusId(char * pciBusId, int len, int device); 
#line 729
extern cudaError_t __stdcall cudaIpcGetEventHandle(cudaIpcEventHandle_t * handle, cudaEvent_t event); 
#line 773
extern cudaError_t __stdcall cudaIpcOpenEventHandle(cudaEvent_t * event, cudaIpcEventHandle_t handle); 
#line 818
extern cudaError_t __stdcall cudaIpcGetMemHandle(cudaIpcMemHandle_t * handle, void * devPtr); 
#line 885
extern cudaError_t __stdcall cudaIpcOpenMemHandle(void ** devPtr, cudaIpcMemHandle_t handle, unsigned flags); 
#line 924
extern cudaError_t __stdcall cudaIpcCloseMemHandle(void * devPtr); 
#line 956
extern cudaError_t __stdcall cudaDeviceFlushGPUDirectRDMAWrites(cudaFlushGPUDirectRDMAWritesTarget target, cudaFlushGPUDirectRDMAWritesScope scope); 
#line 994 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaDeviceRegisterAsyncNotification(int device, cudaAsyncCallback callbackFunc, void * userData, cudaAsyncCallbackHandle_t * callback); 
#line 1017
extern cudaError_t __stdcall cudaDeviceUnregisterAsyncNotification(int device, cudaAsyncCallbackHandle_t callback); 
#line 1064
__declspec(deprecated) extern cudaError_t __stdcall cudaDeviceGetSharedMemConfig(cudaSharedMemConfig * pConfig); 
#line 1110
__declspec(deprecated) extern cudaError_t __stdcall cudaDeviceSetSharedMemConfig(cudaSharedMemConfig config); 
#line 1175
extern cudaError_t __stdcall cudaGetLastError(); 
#line 1226
extern cudaError_t __stdcall cudaPeekAtLastError(); 
#line 1242
extern const char *__stdcall cudaGetErrorName(cudaError_t error); 
#line 1258
extern const char *__stdcall cudaGetErrorString(cudaError_t error); 
#line 1287
extern cudaError_t __stdcall cudaGetDeviceCount(int * count); 
#line 1309
extern cudaError_t __stdcall cudaGetDeviceProperties(cudaDeviceProp * prop, int device); 
#line 1334
extern cudaError_t __stdcall cudaDeviceGetAttribute(int * value, cudaDeviceAttr attr, int device); 
#line 1367
extern cudaError_t __stdcall cudaDeviceGetHostAtomicCapabilities(unsigned * capabilities, const cudaAtomicOperation * operations, unsigned count, int device); 
#line 1385
extern cudaError_t __stdcall cudaDeviceGetDefaultMemPool(cudaMemPool_t * memPool, int device); 
#line 1409
extern cudaError_t __stdcall cudaDeviceSetMemPool(int device, cudaMemPool_t memPool); 
#line 1429
extern cudaError_t __stdcall cudaDeviceGetMemPool(cudaMemPool_t * memPool, int device); 
#line 1491
extern cudaError_t __stdcall cudaDeviceGetNvSciSyncAttributes(void * nvSciSyncAttrList, int device, int flags); 
#line 1535
extern cudaError_t __stdcall cudaDeviceGetP2PAttribute(int * value, cudaDeviceP2PAttr attr, int srcDevice, int dstDevice); 
#line 1571
extern cudaError_t __stdcall cudaDeviceGetP2PAtomicCapabilities(unsigned * capabilities, const cudaAtomicOperation * operations, unsigned count, int srcDevice, int dstDevice); 
#line 1594
extern cudaError_t __stdcall cudaChooseDevice(int * device, const cudaDeviceProp * prop); 
#line 1623
extern cudaError_t __stdcall cudaInitDevice(int device, unsigned deviceFlags, unsigned flags); 
#line 1669
extern cudaError_t __stdcall cudaSetDevice(int device); 
#line 1691
extern cudaError_t __stdcall cudaGetDevice(int * device); 
#line 1722
extern cudaError_t __stdcall cudaSetValidDevices(int * device_arr, int len); 
#line 1792
extern cudaError_t __stdcall cudaSetDeviceFlags(unsigned flags); 
#line 1837
extern cudaError_t __stdcall cudaGetDeviceFlags(unsigned * flags); 
#line 1883
extern cudaError_t __stdcall cudaStreamCreate(cudaStream_t * pStream); 
#line 1921
extern cudaError_t __stdcall cudaStreamCreateWithFlags(cudaStream_t * pStream, unsigned flags); 
#line 1974
extern cudaError_t __stdcall cudaStreamCreateWithPriority(cudaStream_t * pStream, unsigned flags, int priority); 
#line 2003
extern cudaError_t __stdcall cudaStreamGetPriority(cudaStream_t hStream, int * priority); 
#line 2029
extern cudaError_t __stdcall cudaStreamGetFlags(cudaStream_t hStream, unsigned * flags); 
#line 2066
extern cudaError_t __stdcall cudaStreamGetId(cudaStream_t hStream, unsigned __int64 * streamId); 
#line 2092
extern cudaError_t __stdcall cudaStreamGetDevice(cudaStream_t hStream, int * device); 
#line 2107
extern cudaError_t __stdcall cudaCtxResetPersistingL2Cache(); 
#line 2127
extern cudaError_t __stdcall cudaStreamCopyAttributes(cudaStream_t dst, cudaStream_t src); 
#line 2148
extern cudaError_t __stdcall cudaStreamGetAttribute(cudaStream_t hStream, cudaLaunchAttributeID attr, cudaLaunchAttributeValue * value_out); 
#line 2172
extern cudaError_t __stdcall cudaStreamSetAttribute(cudaStream_t hStream, cudaLaunchAttributeID attr, const cudaLaunchAttributeValue * value); 
#line 2207
extern cudaError_t __stdcall cudaStreamDestroy(cudaStream_t stream); 
#line 2238
extern cudaError_t __stdcall cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned flags = 0); 
#line 2246
typedef void (__stdcall *cudaStreamCallback_t)(cudaStream_t stream, cudaError_t status, void * userData); 
#line 2313
extern cudaError_t __stdcall cudaStreamAddCallback(cudaStream_t stream, cudaStreamCallback_t callback, void * userData, unsigned flags); 
#line 2337
extern cudaError_t __stdcall cudaStreamSynchronize(cudaStream_t stream); 
#line 2362
extern cudaError_t __stdcall cudaStreamQuery(cudaStream_t stream); 
#line 2446
extern cudaError_t __stdcall cudaStreamAttachMemAsync(cudaStream_t stream, void * devPtr, size_t length = 0, unsigned flags = 4); 
#line 2485 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaStreamBeginCapture(cudaStream_t stream, cudaStreamCaptureMode mode); 
#line 2498
typedef cudaError_t (__stdcall *cudaGraphRecaptureCallback_t)(void * data, cudaGraphNode_t node, const cudaGraphNodeParams * originalParams, const cudaGraphNodeParams * recaptureParams, cudaGraphRecaptureStatus status); 
#line 2507
struct cudaGraphRecaptureCallbackData { 
#line 2512
cudaGraphRecaptureCallback_t callbackFunc; 
#line 2516
void *userData; 
#line 2517
}; 
#line 2557
extern cudaError_t __stdcall cudaStreamBeginRecaptureToGraph(cudaStream_t stream, cudaStreamCaptureMode mode, cudaGraph_t graph, cudaGraphRecaptureCallbackData * callbackData = 0); 
#line 2601
extern cudaError_t __stdcall cudaStreamBeginCaptureToGraph(cudaStream_t stream, cudaGraph_t graph, const cudaGraphNode_t * dependencies, const cudaGraphEdgeData * dependencyData, size_t numDependencies, cudaStreamCaptureMode mode); 
#line 2652
extern cudaError_t __stdcall cudaThreadExchangeStreamCaptureMode(cudaStreamCaptureMode * mode); 
#line 2681
extern cudaError_t __stdcall cudaStreamEndCapture(cudaStream_t stream, cudaGraph_t * pGraph); 
#line 2719
extern cudaError_t __stdcall cudaStreamIsCapturing(cudaStream_t stream, cudaStreamCaptureStatus * pCaptureStatus); 
#line 2779
extern cudaError_t __stdcall cudaStreamGetCaptureInfo(cudaStream_t stream, cudaStreamCaptureStatus * captureStatus_out, unsigned __int64 * id_out = 0, cudaGraph_t * graph_out = 0, const cudaGraphNode_t ** dependencies_out = 0, const cudaGraphEdgeData ** edgeData_out = 0, size_t * numDependencies_out = 0); 
#line 2818
extern cudaError_t __stdcall cudaStreamUpdateCaptureDependencies(cudaStream_t stream, cudaGraphNode_t * dependencies, const cudaGraphEdgeData * dependencyData, size_t numDependencies, unsigned flags = 0); 
#line 2855
extern cudaError_t __stdcall cudaEventCreate(cudaEvent_t * event); 
#line 2892
extern cudaError_t __stdcall cudaEventCreateWithFlags(cudaEvent_t * event, unsigned flags); 
#line 2933
extern cudaError_t __stdcall cudaEventRecord(cudaEvent_t event, cudaStream_t stream = 0); 
#line 2981
extern cudaError_t __stdcall cudaEventRecordWithFlags(cudaEvent_t event, cudaStream_t stream = 0, unsigned flags = 0); 
#line 3014 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaEventQuery(cudaEvent_t event); 
#line 3045
extern cudaError_t __stdcall cudaEventSynchronize(cudaEvent_t event); 
#line 3075
extern cudaError_t __stdcall cudaEventDestroy(cudaEvent_t event); 
#line 3123
extern cudaError_t __stdcall cudaEventElapsedTime(float * ms, cudaEvent_t start, cudaEvent_t end); 
#line 3304
extern cudaError_t __stdcall cudaImportExternalMemory(cudaExternalMemory_t * extMem_out, const cudaExternalMemoryHandleDesc * memHandleDesc); 
#line 3359
extern cudaError_t __stdcall cudaExternalMemoryGetMappedBuffer(void ** devPtr, cudaExternalMemory_t extMem, const cudaExternalMemoryBufferDesc * bufferDesc); 
#line 3419
extern cudaError_t __stdcall cudaExternalMemoryGetMappedMipmappedArray(cudaMipmappedArray_t * mipmap, cudaExternalMemory_t extMem, const cudaExternalMemoryMipmappedArrayDesc * mipmapDesc); 
#line 3443
extern cudaError_t __stdcall cudaDestroyExternalMemory(cudaExternalMemory_t extMem); 
#line 3597
extern cudaError_t __stdcall cudaImportExternalSemaphore(cudaExternalSemaphore_t * extSem_out, const cudaExternalSemaphoreHandleDesc * semHandleDesc); 
#line 3693
extern cudaError_t __stdcall cudaSignalExternalSemaphoresAsync(const cudaExternalSemaphore_t * extSemArray, const cudaExternalSemaphoreSignalParams * paramsArray, unsigned numExtSems, cudaStream_t stream = 0); 
#line 3769
extern cudaError_t __stdcall cudaWaitExternalSemaphoresAsync(const cudaExternalSemaphore_t * extSemArray, const cudaExternalSemaphoreWaitParams * paramsArray, unsigned numExtSems, cudaStream_t stream = 0); 
#line 3792
extern cudaError_t __stdcall cudaDestroyExternalSemaphore(cudaExternalSemaphore_t extSem); 
#line 3860
extern cudaError_t __stdcall cudaLaunchKernel(const void * func, dim3 gridDim, dim3 blockDim, void ** args, size_t sharedMem, cudaStream_t stream); 
#line 3923
extern cudaError_t __stdcall cudaLaunchKernelExC(const cudaLaunchConfig_t * config, const void * func, void ** args); 
#line 3980
extern cudaError_t __stdcall cudaLaunchCooperativeKernel(const void * func, dim3 gridDim, dim3 blockDim, void ** args, size_t sharedMem, cudaStream_t stream); 
#line 4030
extern cudaError_t __stdcall cudaFuncSetCacheConfig(const void * func, cudaFuncCache cacheConfig); 
#line 4065
extern cudaError_t __stdcall cudaFuncGetAttributes(cudaFuncAttributes * attr, const void * func); 
#line 4124
extern cudaError_t __stdcall cudaFuncSetAttribute(const void * func, cudaFuncAttribute attr, int value); 
#line 4150
extern cudaError_t __stdcall cudaFuncGetName(const char ** name, const void * func); 
#line 4173
extern cudaError_t __stdcall cudaFuncGetParamInfo(const void * func, size_t paramIndex, size_t * paramOffset, size_t * paramSize); 
#line 4189
extern cudaError_t __stdcall cudaFuncGetParamCount(const void * func, size_t * paramCount); 
#line 4255
extern cudaError_t __stdcall cudaLaunchHostFunc(cudaStream_t stream, cudaHostFn_t fn, void * userData); 
#line 4322
extern cudaError_t __stdcall cudaLaunchHostFunc_v2(cudaStream_t stream, cudaHostFn_t fn, void * userData, unsigned syncMode); 
#line 4396
__declspec(deprecated) extern cudaError_t __stdcall cudaFuncSetSharedMemConfig(const void * func, cudaSharedMemConfig config); 
#line 4453
extern cudaError_t __stdcall cudaOccupancyMaxActiveBlocksPerMultiprocessor(int * numBlocks, const void * func, int blockSize, size_t dynamicSMemSize); 
#line 4483
extern cudaError_t __stdcall cudaOccupancyAvailableDynamicSMemPerBlock(size_t * dynamicSmemSize, const void * func, int numBlocks, int blockSize); 
#line 4529
extern cudaError_t __stdcall cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int * numBlocks, const void * func, int blockSize, size_t dynamicSMemSize, unsigned flags); 
#line 4565
extern cudaError_t __stdcall cudaOccupancyMaxPotentialClusterSize(int * clusterSize, const void * func, const cudaLaunchConfig_t * launchConfig); 
#line 4605
extern cudaError_t __stdcall cudaOccupancyMaxActiveClusters(int * numClusters, const void * func, const cudaLaunchConfig_t * launchConfig); 
#line 4725
extern cudaError_t __stdcall cudaMallocManaged(void ** devPtr, size_t size, unsigned flags = 1); 
#line 4759 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaMalloc(void ** devPtr, size_t size); 
#line 4797
extern cudaError_t __stdcall cudaMallocHost(void ** ptr, size_t size); 
#line 4840
extern cudaError_t __stdcall cudaMallocPitch(void ** devPtr, size_t * pitch, size_t width, size_t height); 
#line 4892
extern cudaError_t __stdcall cudaMallocArray(cudaArray_t * array, const cudaChannelFormatDesc * desc, size_t width, size_t height = 0, unsigned flags = 0); 
#line 4931
extern cudaError_t __stdcall cudaFree(void * devPtr); 
#line 4954
extern cudaError_t __stdcall cudaFreeHost(void * ptr); 
#line 4977
extern cudaError_t __stdcall cudaFreeArray(cudaArray_t array); 
#line 5000
extern cudaError_t __stdcall cudaFreeMipmappedArray(cudaMipmappedArray_t mipmappedArray); 
#line 5067
extern cudaError_t __stdcall cudaHostAlloc(void ** pHost, size_t size, unsigned flags); 
#line 5165
extern cudaError_t __stdcall cudaHostRegister(void * ptr, size_t size, unsigned flags); 
#line 5188
extern cudaError_t __stdcall cudaHostUnregister(void * ptr); 
#line 5233
extern cudaError_t __stdcall cudaHostGetDevicePointer(void ** pDevice, void * pHost, unsigned flags); 
#line 5255
extern cudaError_t __stdcall cudaHostGetFlags(unsigned * pFlags, void * pHost); 
#line 5294
extern cudaError_t __stdcall cudaMalloc3D(cudaPitchedPtr * pitchedDevPtr, cudaExtent extent); 
#line 5395
extern cudaError_t __stdcall cudaMalloc3DArray(cudaArray_t * array, const cudaChannelFormatDesc * desc, cudaExtent extent, unsigned flags = 0); 
#line 5497
extern cudaError_t __stdcall cudaMallocMipmappedArray(cudaMipmappedArray_t * mipmappedArray, const cudaChannelFormatDesc * desc, cudaExtent extent, unsigned numLevels, unsigned flags = 0); 
#line 5530
extern cudaError_t __stdcall cudaGetMipmappedArrayLevel(cudaArray_t * levelArray, cudaMipmappedArray_const_t mipmappedArray, unsigned level); 
#line 5635
extern cudaError_t __stdcall cudaMemcpy3D(const cudaMemcpy3DParms * p); 
#line 5667
extern cudaError_t __stdcall cudaMemcpy3DPeer(const cudaMemcpy3DPeerParms * p); 
#line 5785
extern cudaError_t __stdcall cudaMemcpy3DAsync(const cudaMemcpy3DParms * p, cudaStream_t stream = 0); 
#line 5812
extern cudaError_t __stdcall cudaMemcpy3DPeerAsync(const cudaMemcpy3DPeerParms * p, cudaStream_t stream = 0); 
#line 5846
extern cudaError_t __stdcall cudaMemGetInfo(size_t * free, size_t * total); 
#line 5872
extern cudaError_t __stdcall cudaArrayGetInfo(cudaChannelFormatDesc * desc, cudaExtent * extent, unsigned * flags, cudaArray_t array); 
#line 5901
extern cudaError_t __stdcall cudaArrayGetPlane(cudaArray_t * pPlaneArray, cudaArray_t hArray, unsigned planeIdx); 
#line 5924
extern cudaError_t __stdcall cudaArrayGetMemoryRequirements(cudaArrayMemoryRequirements * memoryRequirements, cudaArray_t array, int device); 
#line 5948
extern cudaError_t __stdcall cudaMipmappedArrayGetMemoryRequirements(cudaArrayMemoryRequirements * memoryRequirements, cudaMipmappedArray_t mipmap, int device); 
#line 5976
extern cudaError_t __stdcall cudaArrayGetSparseProperties(cudaArraySparseProperties * sparseProperties, cudaArray_t array); 
#line 6006 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaMipmappedArrayGetSparseProperties(cudaArraySparseProperties * sparseProperties, cudaMipmappedArray_t mipmap); 
#line 6051 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaMemcpy(void * dst, const void * src, size_t count, cudaMemcpyKind kind); 
#line 6086
extern cudaError_t __stdcall cudaMemcpyPeer(void * dst, int dstDevice, const void * src, int srcDevice, size_t count); 
#line 6135
extern cudaError_t __stdcall cudaMemcpy2D(void * dst, size_t dpitch, const void * src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind); 
#line 6185
extern cudaError_t __stdcall cudaMemcpy2DToArray(cudaArray_t dst, size_t wOffset, size_t hOffset, const void * src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind); 
#line 6235
extern cudaError_t __stdcall cudaMemcpy2DFromArray(void * dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, cudaMemcpyKind kind); 
#line 6282
extern cudaError_t __stdcall cudaMemcpy2DArrayToArray(cudaArray_t dst, size_t wOffsetDst, size_t hOffsetDst, cudaArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height, cudaMemcpyKind kind = cudaMemcpyDeviceToDevice); 
#line 6325
extern cudaError_t __stdcall cudaMemcpyToSymbol(const void * symbol, const void * src, size_t count, size_t offset = 0, cudaMemcpyKind kind = cudaMemcpyHostToDevice); 
#line 6369
extern cudaError_t __stdcall cudaMemcpyFromSymbol(void * dst, const void * symbol, size_t count, size_t offset = 0, cudaMemcpyKind kind = cudaMemcpyDeviceToHost); 
#line 6426
extern cudaError_t __stdcall cudaMemcpyAsync(void * dst, const void * src, size_t count, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 6461
extern cudaError_t __stdcall cudaMemcpyPeerAsync(void * dst, int dstDevice, const void * src, int srcDevice, size_t count, cudaStream_t stream = 0); 
#line 6529
extern cudaError_t __stdcall cudaMemcpyBatchAsync(void *const * dsts, const void *const * srcs, const size_t * sizes, size_t count, cudaMemcpyAttributes * attrs, size_t * attrsIdxs, size_t numAttrs, cudaStream_t stream); 
#line 6593
extern cudaError_t __stdcall cudaMemcpy3DBatchAsync(size_t numOps, cudaMemcpy3DBatchOp * opList, unsigned __int64 flags, cudaStream_t stream); 
#line 6620
extern cudaError_t __stdcall cudaMemcpyWithAttributesAsync(void * dst, const void * src, size_t size, cudaMemcpyAttributes * attr, cudaStream_t stream); 
#line 6643
extern cudaError_t __stdcall cudaMemcpy3DWithAttributesAsync(cudaMemcpy3DBatchOp * op, unsigned __int64 flags, cudaStream_t stream); 
#line 6706
extern cudaError_t __stdcall cudaMemcpy2DAsync(void * dst, size_t dpitch, const void * src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 6764
extern cudaError_t __stdcall cudaMemcpy2DToArrayAsync(cudaArray_t dst, size_t wOffset, size_t hOffset, const void * src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 6821
extern cudaError_t __stdcall cudaMemcpy2DFromArrayAsync(void * dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 6872
extern cudaError_t __stdcall cudaMemcpyToSymbolAsync(const void * symbol, const void * src, size_t count, size_t offset, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 6923
extern cudaError_t __stdcall cudaMemcpyFromSymbolAsync(void * dst, const void * symbol, size_t count, size_t offset, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 6952
extern cudaError_t __stdcall cudaMemset(void * devPtr, int value, size_t count); 
#line 6986
extern cudaError_t __stdcall cudaMemset2D(void * devPtr, size_t pitch, int value, size_t width, size_t height); 
#line 7032
extern cudaError_t __stdcall cudaMemset3D(cudaPitchedPtr pitchedDevPtr, int value, cudaExtent extent); 
#line 7068
extern cudaError_t __stdcall cudaMemsetAsync(void * devPtr, int value, size_t count, cudaStream_t stream = 0); 
#line 7109
extern cudaError_t __stdcall cudaMemset2DAsync(void * devPtr, size_t pitch, int value, size_t width, size_t height, cudaStream_t stream = 0); 
#line 7162
extern cudaError_t __stdcall cudaMemset3DAsync(cudaPitchedPtr pitchedDevPtr, int value, cudaExtent extent, cudaStream_t stream = 0); 
#line 7190
extern cudaError_t __stdcall cudaGetSymbolAddress(void ** devPtr, const void * symbol); 
#line 7217
extern cudaError_t __stdcall cudaGetSymbolSize(size_t * size, const void * symbol); 
#line 7299
extern cudaError_t __stdcall cudaMemPrefetchAsync(const void * devPtr, size_t count, cudaMemLocation location, unsigned flags, cudaStream_t stream = 0); 
#line 7340
extern cudaError_t __stdcall cudaMemPrefetchBatchAsync(void ** dptrs, size_t * sizes, size_t count, cudaMemLocation * prefetchLocs, size_t * prefetchLocIdxs, size_t numPrefetchLocs, unsigned __int64 flags, cudaStream_t stream); 
#line 7373
extern cudaError_t __stdcall cudaMemDiscardBatchAsync(void ** dptrs, size_t * sizes, size_t count, unsigned __int64 flags, cudaStream_t stream); 
#line 7421
extern cudaError_t __stdcall cudaMemDiscardAndPrefetchBatchAsync(void ** dptrs, size_t * sizes, size_t count, cudaMemLocation * prefetchLocs, size_t * prefetchLocIdxs, size_t numPrefetchLocs, unsigned __int64 flags, cudaStream_t stream); 
#line 7547
extern cudaError_t __stdcall cudaMemAdvise(const void * devPtr, size_t count, cudaMemoryAdvise advice, cudaMemLocation location); 
#line 7629
extern cudaError_t __stdcall cudaMemRangeGetAttribute(void * data, size_t dataSize, cudaMemRangeAttribute attribute, const void * devPtr, size_t count); 
#line 7672
extern cudaError_t __stdcall cudaMemRangeGetAttributes(void ** data, size_t * dataSizes, cudaMemRangeAttribute * attributes, size_t numAttributes, const void * devPtr, size_t count); 
#line 7732
__declspec(deprecated) extern cudaError_t __stdcall cudaMemcpyToArray(cudaArray_t dst, size_t wOffset, size_t hOffset, const void * src, size_t count, cudaMemcpyKind kind); 
#line 7774
__declspec(deprecated) extern cudaError_t __stdcall cudaMemcpyFromArray(void * dst, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t count, cudaMemcpyKind kind); 
#line 7817
__declspec(deprecated) extern cudaError_t __stdcall cudaMemcpyArrayToArray(cudaArray_t dst, size_t wOffsetDst, size_t hOffsetDst, cudaArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc, size_t count, cudaMemcpyKind kind = cudaMemcpyDeviceToDevice); 
#line 7868
__declspec(deprecated) extern cudaError_t __stdcall cudaMemcpyToArrayAsync(cudaArray_t dst, size_t wOffset, size_t hOffset, const void * src, size_t count, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 7918
__declspec(deprecated) extern cudaError_t __stdcall cudaMemcpyFromArrayAsync(void * dst, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t count, cudaMemcpyKind kind, cudaStream_t stream = 0); 
#line 7987
extern cudaError_t __stdcall cudaMallocAsync(void ** devPtr, size_t size, cudaStream_t hStream); 
#line 8013
extern cudaError_t __stdcall cudaFreeAsync(void * devPtr, cudaStream_t hStream); 
#line 8038
extern cudaError_t __stdcall cudaMemPoolTrimTo(cudaMemPool_t memPool, size_t minBytesToKeep); 
#line 8082
extern cudaError_t __stdcall cudaMemPoolSetAttribute(cudaMemPool_t memPool, cudaMemPoolAttr attr, void * value); 
#line 8153
extern cudaError_t __stdcall cudaMemPoolGetAttribute(cudaMemPool_t memPool, cudaMemPoolAttr attr, void * value); 
#line 8168
extern cudaError_t __stdcall cudaMemPoolSetAccess(cudaMemPool_t memPool, const cudaMemAccessDesc * descList, size_t count); 
#line 8181
extern cudaError_t __stdcall cudaMemPoolGetAccess(cudaMemAccessFlags * flags, cudaMemPool_t memPool, cudaMemLocation * location); 
#line 8240
extern cudaError_t __stdcall cudaMemPoolCreate(cudaMemPool_t * memPool, const cudaMemPoolProps * poolProps); 
#line 8262
extern cudaError_t __stdcall cudaMemPoolDestroy(cudaMemPool_t memPool); 
#line 8282
extern cudaError_t __stdcall cudaMemGetDefaultMemPool(cudaMemPool_t * memPool, cudaMemLocation * location, cudaMemAllocationType type); 
#line 8307
extern cudaError_t __stdcall cudaMemGetMemPool(cudaMemPool_t * memPool, cudaMemLocation * location, cudaMemAllocationType type); 
#line 8337
extern cudaError_t __stdcall cudaMemSetMemPool(cudaMemLocation * location, cudaMemAllocationType type, cudaMemPool_t memPool); 
#line 8373
extern cudaError_t __stdcall cudaMallocFromPoolAsync(void ** ptr, size_t size, cudaMemPool_t memPool, cudaStream_t stream); 
#line 8398
extern cudaError_t __stdcall cudaMemPoolExportToShareableHandle(void * shareableHandle, cudaMemPool_t memPool, cudaMemAllocationHandleType handleType, unsigned flags); 
#line 8425
extern cudaError_t __stdcall cudaMemPoolImportFromShareableHandle(cudaMemPool_t * memPool, void * shareableHandle, cudaMemAllocationHandleType handleType, unsigned flags); 
#line 8448
extern cudaError_t __stdcall cudaMemPoolExportPointer(cudaMemPoolPtrExportData * exportData, void * ptr); 
#line 8477
extern cudaError_t __stdcall cudaMemPoolImportPointer(void ** ptr, cudaMemPool_t memPool, cudaMemPoolPtrExportData * exportData); 
#line 8630
extern cudaError_t __stdcall cudaPointerGetAttributes(cudaPointerAttributes * attributes, const void * ptr); 
#line 8671
extern cudaError_t __stdcall cudaDeviceCanAccessPeer(int * canAccessPeer, int device, int peerDevice); 
#line 8713
extern cudaError_t __stdcall cudaDeviceEnablePeerAccess(int peerDevice, unsigned flags); 
#line 8735
extern cudaError_t __stdcall cudaDeviceDisablePeerAccess(int peerDevice); 
#line 8799
extern cudaError_t __stdcall cudaGraphicsUnregisterResource(cudaGraphicsResource_t resource); 
#line 8834
extern cudaError_t __stdcall cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t resource, unsigned flags); 
#line 8873
extern cudaError_t __stdcall cudaGraphicsMapResources(int count, cudaGraphicsResource_t * resources, cudaStream_t stream = 0); 
#line 8908
extern cudaError_t __stdcall cudaGraphicsUnmapResources(int count, cudaGraphicsResource_t * resources, cudaStream_t stream = 0); 
#line 8940
extern cudaError_t __stdcall cudaGraphicsResourceGetMappedPointer(void ** devPtr, size_t * size, cudaGraphicsResource_t resource); 
#line 8978
extern cudaError_t __stdcall cudaGraphicsSubResourceGetMappedArray(cudaArray_t * array, cudaGraphicsResource_t resource, unsigned arrayIndex, unsigned mipLevel); 
#line 9007
extern cudaError_t __stdcall cudaGraphicsResourceGetMappedMipmappedArray(cudaMipmappedArray_t * mipmappedArray, cudaGraphicsResource_t resource); 
#line 9042
extern cudaError_t __stdcall cudaGetChannelDesc(cudaChannelFormatDesc * desc, cudaArray_const_t array); 
#line 9072
extern cudaChannelFormatDesc __stdcall cudaCreateChannelDesc(int x, int y, int z, int w, cudaChannelFormatKind f); 
#line 9297
extern cudaError_t __stdcall cudaCreateTextureObject(cudaTextureObject_t * pTexObject, const cudaResourceDesc * pResDesc, const cudaTextureDesc * pTexDesc, const cudaResourceViewDesc * pResViewDesc); 
#line 9317
extern cudaError_t __stdcall cudaDestroyTextureObject(cudaTextureObject_t texObject); 
#line 9337
extern cudaError_t __stdcall cudaGetTextureObjectResourceDesc(cudaResourceDesc * pResDesc, cudaTextureObject_t texObject); 
#line 9357
extern cudaError_t __stdcall cudaGetTextureObjectTextureDesc(cudaTextureDesc * pTexDesc, cudaTextureObject_t texObject); 
#line 9378
extern cudaError_t __stdcall cudaGetTextureObjectResourceViewDesc(cudaResourceViewDesc * pResViewDesc, cudaTextureObject_t texObject); 
#line 9423
extern cudaError_t __stdcall cudaCreateSurfaceObject(cudaSurfaceObject_t * pSurfObject, const cudaResourceDesc * pResDesc); 
#line 9443
extern cudaError_t __stdcall cudaDestroySurfaceObject(cudaSurfaceObject_t surfObject); 
#line 9462
extern cudaError_t __stdcall cudaGetSurfaceObjectResourceDesc(cudaResourceDesc * pResDesc, cudaSurfaceObject_t surfObject); 
#line 9496
extern cudaError_t __stdcall cudaDriverGetVersion(int * driverVersion); 
#line 9525
extern cudaError_t __stdcall cudaRuntimeGetVersion(int * runtimeVersion); 
#line 9549
typedef void (__stdcall *cudaLogsCallback_t)(void * data, cudaLogLevel logLevel, char * message, size_t length); 
#line 9562
extern cudaError_t __stdcall cudaLogsRegisterCallback(cudaLogsCallback_t callbackFunc, void * userData, cudaLogsCallbackHandle * callback_out); 
#line 9573
extern cudaError_t __stdcall cudaLogsUnregisterCallback(cudaLogsCallbackHandle callback); 
#line 9585
extern cudaError_t __stdcall cudaLogsCurrent(cudaLogIterator * iterator_out, unsigned flags); 
#line 9609
extern cudaError_t __stdcall cudaLogsDumpToFile(cudaLogIterator * iterator, const char * pathToFile, unsigned flags); 
#line 9645
extern cudaError_t __stdcall cudaLogsDumpToMemory(cudaLogIterator * iterator, char * buffer, size_t * size, unsigned flags); 
#line 9692
extern cudaError_t __stdcall cudaGraphCreate(cudaGraph_t * pGraph, unsigned flags = 0); 
#line 9791
extern cudaError_t __stdcall cudaGraphAddKernelNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const cudaKernelNodeParams * pNodeParams); 
#line 9825
extern cudaError_t __stdcall cudaGraphKernelNodeGetParams(cudaGraphNode_t node, cudaKernelNodeParams * pNodeParams); 
#line 9852
extern cudaError_t __stdcall cudaGraphKernelNodeSetParams(cudaGraphNode_t node, const cudaKernelNodeParams * pNodeParams); 
#line 9872
extern cudaError_t __stdcall cudaGraphKernelNodeCopyAttributes(cudaGraphNode_t hDst, cudaGraphNode_t hSrc); 
#line 9895
extern cudaError_t __stdcall cudaGraphKernelNodeGetAttribute(cudaGraphNode_t hNode, cudaLaunchAttributeID attr, cudaLaunchAttributeValue * value_out); 
#line 9919
extern cudaError_t __stdcall cudaGraphKernelNodeSetAttribute(cudaGraphNode_t hNode, cudaLaunchAttributeID attr, const cudaLaunchAttributeValue * value); 
#line 9970
extern cudaError_t __stdcall cudaGraphAddMemcpyNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const cudaMemcpy3DParms * pCopyParams); 
#line 10029
extern cudaError_t __stdcall cudaGraphAddMemcpyNodeToSymbol(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const void * symbol, const void * src, size_t count, size_t offset, cudaMemcpyKind kind); 
#line 10098 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddMemcpyNodeFromSymbol(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, void * dst, const void * symbol, size_t count, size_t offset, cudaMemcpyKind kind); 
#line 10166 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddMemcpyNode1D(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, void * dst, const void * src, size_t count, cudaMemcpyKind kind); 
#line 10199 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphMemcpyNodeGetParams(cudaGraphNode_t node, cudaMemcpy3DParms * pNodeParams); 
#line 10226
extern cudaError_t __stdcall cudaGraphMemcpyNodeSetParams(cudaGraphNode_t node, const cudaMemcpy3DParms * pNodeParams); 
#line 10265
extern cudaError_t __stdcall cudaGraphMemcpyNodeSetParamsToSymbol(cudaGraphNode_t node, const void * symbol, const void * src, size_t count, size_t offset, cudaMemcpyKind kind); 
#line 10311 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphMemcpyNodeSetParamsFromSymbol(cudaGraphNode_t node, void * dst, const void * symbol, size_t count, size_t offset, cudaMemcpyKind kind); 
#line 10357 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphMemcpyNodeSetParams1D(cudaGraphNode_t node, void * dst, const void * src, size_t count, cudaMemcpyKind kind); 
#line 10405 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddMemsetNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const cudaMemsetParams * pMemsetParams); 
#line 10429
extern cudaError_t __stdcall cudaGraphMemsetNodeGetParams(cudaGraphNode_t node, cudaMemsetParams * pNodeParams); 
#line 10453
extern cudaError_t __stdcall cudaGraphMemsetNodeSetParams(cudaGraphNode_t node, const cudaMemsetParams * pNodeParams); 
#line 10495
extern cudaError_t __stdcall cudaGraphAddHostNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const cudaHostNodeParams * pNodeParams); 
#line 10519
extern cudaError_t __stdcall cudaGraphHostNodeGetParams(cudaGraphNode_t node, cudaHostNodeParams * pNodeParams); 
#line 10543
extern cudaError_t __stdcall cudaGraphHostNodeSetParams(cudaGraphNode_t node, const cudaHostNodeParams * pNodeParams); 
#line 10585
extern cudaError_t __stdcall cudaGraphAddChildGraphNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, cudaGraph_t childGraph); 
#line 10612
extern cudaError_t __stdcall cudaGraphChildGraphNodeGetGraph(cudaGraphNode_t node, cudaGraph_t * pGraph); 
#line 10650
extern cudaError_t __stdcall cudaGraphAddEmptyNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies); 
#line 10694
extern cudaError_t __stdcall cudaGraphAddEventRecordNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, cudaEvent_t event); 
#line 10721 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphEventRecordNodeGetEvent(cudaGraphNode_t node, cudaEvent_t * event_out); 
#line 10749 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphEventRecordNodeSetEvent(cudaGraphNode_t node, cudaEvent_t event); 
#line 10796 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddEventWaitNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, cudaEvent_t event); 
#line 10823 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphEventWaitNodeGetEvent(cudaGraphNode_t node, cudaEvent_t * event_out); 
#line 10851 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphEventWaitNodeSetEvent(cudaGraphNode_t node, cudaEvent_t event); 
#line 10901 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddExternalSemaphoresSignalNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const cudaExternalSemaphoreSignalNodeParams * nodeParams); 
#line 10935 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExternalSemaphoresSignalNodeGetParams(cudaGraphNode_t hNode, cudaExternalSemaphoreSignalNodeParams * params_out); 
#line 10963 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExternalSemaphoresSignalNodeSetParams(cudaGraphNode_t hNode, const cudaExternalSemaphoreSignalNodeParams * nodeParams); 
#line 11013 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddExternalSemaphoresWaitNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, const cudaExternalSemaphoreWaitNodeParams * nodeParams); 
#line 11047 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExternalSemaphoresWaitNodeGetParams(cudaGraphNode_t hNode, cudaExternalSemaphoreWaitNodeParams * params_out); 
#line 11075 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExternalSemaphoresWaitNodeSetParams(cudaGraphNode_t hNode, const cudaExternalSemaphoreWaitNodeParams * nodeParams); 
#line 11153 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddMemAllocNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, cudaMemAllocNodeParams * nodeParams); 
#line 11181 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphMemAllocNodeGetParams(cudaGraphNode_t node, cudaMemAllocNodeParams * params_out); 
#line 11242 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphAddMemFreeNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, size_t numDependencies, void * dptr); 
#line 11267 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphMemFreeNodeGetParams(cudaGraphNode_t node, void * dptr_out); 
#line 11295 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaDeviceGraphMemTrim(int device); 
#line 11332 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaDeviceGetGraphMemAttribute(int device, cudaGraphMemAttributeType attr, void * value); 
#line 11366 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaDeviceSetGraphMemAttribute(int device, cudaGraphMemAttributeType attr, void * value); 
#line 11397 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphClone(cudaGraph_t * pGraphClone, cudaGraph_t originalGraph); 
#line 11425
extern cudaError_t __stdcall cudaGraphNodeFindInClone(cudaGraphNode_t * pNode, cudaGraphNode_t originalNode, cudaGraph_t clonedGraph); 
#line 11456
extern cudaError_t __stdcall cudaGraphNodeGetType(cudaGraphNode_t node, cudaGraphNodeType * pType); 
#line 11478
extern cudaError_t __stdcall cudaGraphNodeGetContainingGraph(cudaGraphNode_t hNode, cudaGraph_t * phGraph); 
#line 11501
extern cudaError_t __stdcall cudaGraphNodeGetLocalId(cudaGraphNode_t hNode, unsigned * nodeId); 
#line 11521
extern cudaError_t __stdcall cudaGraphNodeGetToolsId(cudaGraphNode_t hNode, unsigned __int64 * toolsNodeId); 
#line 11543
extern cudaError_t __stdcall cudaGraphGetId(cudaGraph_t hGraph, unsigned * graphID); 
#line 11565
extern cudaError_t __stdcall cudaGraphExecGetId(cudaGraphExec_t hGraphExec, unsigned * graphID); 
#line 11596
extern cudaError_t __stdcall cudaGraphGetNodes(cudaGraph_t graph, cudaGraphNode_t * nodes, size_t * numNodes); 
#line 11627
extern cudaError_t __stdcall cudaGraphGetRootNodes(cudaGraph_t graph, cudaGraphNode_t * pRootNodes, size_t * pNumRootNodes); 
#line 11668
extern cudaError_t __stdcall cudaGraphGetEdges(cudaGraph_t graph, cudaGraphNode_t * from, cudaGraphNode_t * to, cudaGraphEdgeData * edgeData, size_t * numEdges); 
#line 11706
extern cudaError_t __stdcall cudaGraphNodeGetDependencies(cudaGraphNode_t node, cudaGraphNode_t * pDependencies, cudaGraphEdgeData * edgeData, size_t * pNumDependencies); 
#line 11745
extern cudaError_t __stdcall cudaGraphNodeGetDependentNodes(cudaGraphNode_t node, cudaGraphNode_t * pDependentNodes, cudaGraphEdgeData * edgeData, size_t * pNumDependentNodes); 
#line 11778
extern cudaError_t __stdcall cudaGraphAddDependencies(cudaGraph_t graph, const cudaGraphNode_t * from, const cudaGraphNode_t * to, const cudaGraphEdgeData * edgeData, size_t numDependencies); 
#line 11814
extern cudaError_t __stdcall cudaGraphRemoveDependencies(cudaGraph_t graph, const cudaGraphNode_t * from, const cudaGraphNode_t * to, const cudaGraphEdgeData * edgeData, size_t numDependencies); 
#line 11844
extern cudaError_t __stdcall cudaGraphDestroyNode(cudaGraphNode_t node); 
#line 11915
extern cudaError_t __stdcall cudaGraphInstantiate(cudaGraphExec_t * pGraphExec, cudaGraph_t graph, unsigned __int64 flags = 0); 
#line 11988
extern cudaError_t __stdcall cudaGraphInstantiateWithFlags(cudaGraphExec_t * pGraphExec, cudaGraph_t graph, unsigned __int64 flags = 0); 
#line 12095 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphInstantiateWithParams(cudaGraphExec_t * pGraphExec, cudaGraph_t graph, cudaGraphInstantiateParams * instantiateParams); 
#line 12120
extern cudaError_t __stdcall cudaGraphExecGetFlags(cudaGraphExec_t graphExec, unsigned __int64 * flags); 
#line 12180
extern cudaError_t __stdcall cudaGraphExecKernelNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaKernelNodeParams * pNodeParams); 
#line 12231
extern cudaError_t __stdcall cudaGraphExecMemcpyNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaMemcpy3DParms * pNodeParams); 
#line 12286
extern cudaError_t __stdcall cudaGraphExecMemcpyNodeSetParamsToSymbol(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const void * symbol, const void * src, size_t count, size_t offset, cudaMemcpyKind kind); 
#line 12349 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecMemcpyNodeSetParamsFromSymbol(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, void * dst, const void * symbol, size_t count, size_t offset, cudaMemcpyKind kind); 
#line 12410 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecMemcpyNodeSetParams1D(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, void * dst, const void * src, size_t count, cudaMemcpyKind kind); 
#line 12469 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecMemsetNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaMemsetParams * pNodeParams); 
#line 12509
extern cudaError_t __stdcall cudaGraphExecHostNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaHostNodeParams * pNodeParams); 
#line 12556
extern cudaError_t __stdcall cudaGraphExecChildGraphNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, cudaGraph_t childGraph); 
#line 12601 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecEventRecordNodeSetEvent(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, cudaEvent_t event); 
#line 12646 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecEventWaitNodeSetEvent(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, cudaEvent_t event); 
#line 12694 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecExternalSemaphoresSignalNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, const cudaExternalSemaphoreSignalNodeParams * nodeParams); 
#line 12742 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecExternalSemaphoresWaitNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, const cudaExternalSemaphoreWaitNodeParams * nodeParams); 
#line 12782 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphNodeSetEnabled(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, unsigned isEnabled); 
#line 12816 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphNodeGetEnabled(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, unsigned * isEnabled); 
#line 12910 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphExecUpdate(cudaGraphExec_t hGraphExec, cudaGraph_t hGraph, cudaGraphExecUpdateResultInfo * resultInfo); 
#line 12935
extern cudaError_t __stdcall cudaGraphUpload(cudaGraphExec_t graphExec, cudaStream_t stream); 
#line 12966 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGraphLaunch(cudaGraphExec_t graphExec, cudaStream_t stream); 
#line 12989
extern cudaError_t __stdcall cudaGraphExecDestroy(cudaGraphExec_t graphExec); 
#line 13010
extern cudaError_t __stdcall cudaGraphDestroy(cudaGraph_t graph); 
#line 13029
extern cudaError_t __stdcall cudaGraphDebugDotPrint(cudaGraph_t graph, const char * path, unsigned flags); 
#line 13065
extern cudaError_t __stdcall cudaUserObjectCreate(cudaUserObject_t * object_out, void * ptr, cudaHostFn_t destroy, unsigned initialRefcount, unsigned flags); 
#line 13089
extern cudaError_t __stdcall cudaUserObjectRetain(cudaUserObject_t object, unsigned count = 1); 
#line 13117
extern cudaError_t __stdcall cudaUserObjectRelease(cudaUserObject_t object, unsigned count = 1); 
#line 13145
extern cudaError_t __stdcall cudaGraphRetainUserObject(cudaGraph_t graph, cudaUserObject_t object, unsigned count = 1, unsigned flags = 0); 
#line 13170
extern cudaError_t __stdcall cudaGraphReleaseUserObject(cudaGraph_t graph, cudaUserObject_t object, unsigned count = 1); 
#line 13215
extern cudaError_t __stdcall cudaGraphAddNode(cudaGraphNode_t * pGraphNode, cudaGraph_t graph, const cudaGraphNode_t * pDependencies, const cudaGraphEdgeData * dependencyData, size_t numDependencies, cudaGraphNodeParams * nodeParams); 
#line 13245
extern cudaError_t __stdcall cudaGraphNodeSetParams(cudaGraphNode_t node, cudaGraphNodeParams * nodeParams); 
#line 13281
extern cudaError_t __stdcall cudaGraphNodeGetParams(cudaGraphNode_t node, cudaGraphNodeParams * nodeParams); 
#line 13330
extern cudaError_t __stdcall cudaGraphExecNodeSetParams(cudaGraphExec_t graphExec, cudaGraphNode_t node, cudaGraphNodeParams * nodeParams); 
#line 13357
extern cudaError_t __stdcall cudaGraphConditionalHandleCreate(cudaGraphConditionalHandle * pHandle_out, cudaGraph_t graph, unsigned defaultLaunchValue = 0, unsigned flags = 0); 
#line 13385
extern cudaError_t __stdcall cudaGraphConditionalHandleCreate_v2(cudaGraphConditionalHandle * pHandle_out, cudaGraph_t graph, cudaExecutionContext_t ctx = 0, unsigned defaultLaunchValue = 0, unsigned flags = 0); 
#line 13471
__declspec(deprecated) extern cudaError_t __stdcall cudaGetDriverEntryPoint(const char * symbol, void ** funcPtr, unsigned __int64 flags, cudaDriverEntryPointQueryResult * driverStatus = 0); 
#line 13548 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaGetDriverEntryPointByVersion(const char * symbol, void ** funcPtr, unsigned cudaVersion, unsigned __int64 flags, cudaDriverEntryPointQueryResult * driverStatus = 0); 
#line 13624 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
extern cudaError_t __stdcall cudaLibraryLoadData(cudaLibrary_t * library, const void * code, cudaJitOption * jitOptions, void ** jitOptionsValues, unsigned numJitOptions, cudaLibraryOption * libraryOptions, void ** libraryOptionValues, unsigned numLibraryOptions); 
#line 13685
extern cudaError_t __stdcall cudaLibraryLoadFromFile(cudaLibrary_t * library, const char * fileName, cudaJitOption * jitOptions, void ** jitOptionsValues, unsigned numJitOptions, cudaLibraryOption * libraryOptions, void ** libraryOptionValues, unsigned numLibraryOptions); 
#line 13706
extern cudaError_t __stdcall cudaLibraryUnload(cudaLibrary_t library); 
#line 13731
extern cudaError_t __stdcall cudaLibraryGetKernel(cudaKernel_t * pKernel, cudaLibrary_t library, const char * name); 
#line 13765
extern cudaError_t __stdcall cudaLibraryGetGlobal(void ** dptr, size_t * bytes, cudaLibrary_t library, const char * name); 
#line 13798
extern cudaError_t __stdcall cudaLibraryGetManaged(void ** dptr, size_t * bytes, cudaLibrary_t library, const char * name); 
#line 13825
extern cudaError_t __stdcall cudaLibraryGetUnifiedFunction(void ** fptr, cudaLibrary_t library, const char * symbol); 
#line 13847
extern cudaError_t __stdcall cudaLibraryGetKernelCount(unsigned * count, cudaLibrary_t lib); 
#line 13869
extern cudaError_t __stdcall cudaLibraryEnumerateKernels(cudaKernel_t * kernels, unsigned numKernels, cudaLibrary_t lib); 
#line 13938
extern cudaError_t __stdcall cudaKernelSetAttributeForDevice(cudaKernel_t kernel, cudaFuncAttribute attr, int value, int device); 
#line 14092
extern cudaError_t __stdcall cudaDeviceGetDevResource(int device, cudaDevResource * resource, cudaDevResourceType type); 
#line 14170
extern cudaError_t __stdcall cudaDevSmResourceSplitByCount(cudaDevResource * result, unsigned * nbGroups, const cudaDevResource * input, cudaDevResource * remaining, unsigned flags, unsigned minCount); 
#line 14278
extern cudaError_t __stdcall cudaDevSmResourceSplit(cudaDevResource * result, unsigned nbGroups, const cudaDevResource * input, cudaDevResource * remainder, unsigned flags, cudaDevSmResourceGroupParams * groupParams); 
#line 14323
extern cudaError_t __stdcall cudaDevResourceGenerateDesc(cudaDevResourceDesc_t * phDesc, cudaDevResource * resources, unsigned nbResources); 
#line 14369
extern cudaError_t __stdcall cudaGreenCtxCreate(cudaExecutionContext_t * phCtx, cudaDevResourceDesc_t desc, int device, unsigned flags); 
#line 14406
extern cudaError_t __stdcall cudaExecutionCtxDestroy(cudaExecutionContext_t ctx); 
#line 14436
extern cudaError_t __stdcall cudaExecutionCtxGetDevResource(cudaExecutionContext_t ctx, cudaDevResource * resource, cudaDevResourceType type); 
#line 14461
extern cudaError_t __stdcall cudaExecutionCtxGetDevice(int * device, cudaExecutionContext_t ctx); 
#line 14488
extern cudaError_t __stdcall cudaExecutionCtxGetId(cudaExecutionContext_t ctx, unsigned __int64 * ctxId); 
#line 14547
extern cudaError_t __stdcall cudaExecutionCtxStreamCreate(cudaStream_t * phStream, cudaExecutionContext_t ctx, unsigned flags, int priority); 
#line 14575
extern cudaError_t __stdcall cudaExecutionCtxSynchronize(cudaExecutionContext_t ctx); 
#line 14610
extern cudaError_t __stdcall cudaStreamGetDevResource(cudaStream_t hStream, cudaDevResource * resource, cudaDevResourceType type); 
#line 14648
extern cudaError_t __stdcall cudaExecutionCtxRecordEvent(cudaExecutionContext_t ctx, cudaEvent_t event); 
#line 14686
extern cudaError_t __stdcall cudaExecutionCtxWaitEvent(cudaExecutionContext_t ctx, cudaEvent_t event); 
#line 14709
extern cudaError_t __stdcall cudaDeviceGetExecutionCtx(cudaExecutionContext_t * ctx, int device); 
#line 14714
extern cudaError_t __stdcall cudaGetExportTable(const void ** ppExportTable, const cudaUUID_t * pExportTableId); 
#line 14909
extern cudaError_t __stdcall cudaGetFuncBySymbol(cudaFunction_t * functionPtr, const void * symbolPtr); 
#line 14933
extern cudaError_t __stdcall cudaGetKernel(cudaKernel_t * kernelPtr, const void * entryFuncAddr); 
#line 15112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\cuda_runtime_api.h"
}
#line 134 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\channel_descriptor.h"
template< class T> __inline ::cudaChannelFormatDesc cudaCreateChannelDesc() 
#line 135
{ 
#line 136
return cudaCreateChannelDesc(0, 0, 0, 0, cudaChannelFormatKindNone); 
#line 137
} 
#line 139
static __inline cudaChannelFormatDesc cudaCreateChannelDescHalf() 
#line 140
{ 
#line 141
int e = (((int)sizeof(unsigned short)) * 8); 
#line 143
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat); 
#line 144
} 
#line 146
static __inline cudaChannelFormatDesc cudaCreateChannelDescHalf1() 
#line 147
{ 
#line 148
int e = (((int)sizeof(unsigned short)) * 8); 
#line 150
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat); 
#line 151
} 
#line 153
static __inline cudaChannelFormatDesc cudaCreateChannelDescHalf2() 
#line 154
{ 
#line 155
int e = (((int)sizeof(unsigned short)) * 8); 
#line 157
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindFloat); 
#line 158
} 
#line 160
static __inline cudaChannelFormatDesc cudaCreateChannelDescHalf4() 
#line 161
{ 
#line 162
int e = (((int)sizeof(unsigned short)) * 8); 
#line 164
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindFloat); 
#line 165
} 
#line 167
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< char> () 
#line 168
{ 
#line 169
int e = (((int)sizeof(char)) * 8); 
#line 174 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\channel_descriptor.h"
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 176 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\channel_descriptor.h"
} 
#line 178
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< signed char> () 
#line 179
{ 
#line 180
int e = (((int)sizeof(signed char)) * 8); 
#line 182
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 183
} 
#line 185
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned char> () 
#line 186
{ 
#line 187
int e = (((int)sizeof(unsigned char)) * 8); 
#line 189
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 190
} 
#line 192
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< char1> () 
#line 193
{ 
#line 194
int e = (((int)sizeof(signed char)) * 8); 
#line 196
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 197
} 
#line 199
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< uchar1> () 
#line 200
{ 
#line 201
int e = (((int)sizeof(unsigned char)) * 8); 
#line 203
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 204
} 
#line 206
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< char2> () 
#line 207
{ 
#line 208
int e = (((int)sizeof(signed char)) * 8); 
#line 210
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned); 
#line 211
} 
#line 213
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< uchar2> () 
#line 214
{ 
#line 215
int e = (((int)sizeof(unsigned char)) * 8); 
#line 217
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned); 
#line 218
} 
#line 220
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< char4> () 
#line 221
{ 
#line 222
int e = (((int)sizeof(signed char)) * 8); 
#line 224
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned); 
#line 225
} 
#line 227
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< uchar4> () 
#line 228
{ 
#line 229
int e = (((int)sizeof(unsigned char)) * 8); 
#line 231
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned); 
#line 232
} 
#line 234
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< short> () 
#line 235
{ 
#line 236
int e = (((int)sizeof(short)) * 8); 
#line 238
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 239
} 
#line 241
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned short> () 
#line 242
{ 
#line 243
int e = (((int)sizeof(unsigned short)) * 8); 
#line 245
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 246
} 
#line 248
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< short1> () 
#line 249
{ 
#line 250
int e = (((int)sizeof(short)) * 8); 
#line 252
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 253
} 
#line 255
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< ushort1> () 
#line 256
{ 
#line 257
int e = (((int)sizeof(unsigned short)) * 8); 
#line 259
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 260
} 
#line 262
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< short2> () 
#line 263
{ 
#line 264
int e = (((int)sizeof(short)) * 8); 
#line 266
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned); 
#line 267
} 
#line 269
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< ushort2> () 
#line 270
{ 
#line 271
int e = (((int)sizeof(unsigned short)) * 8); 
#line 273
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned); 
#line 274
} 
#line 276
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< short4> () 
#line 277
{ 
#line 278
int e = (((int)sizeof(short)) * 8); 
#line 280
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned); 
#line 281
} 
#line 283
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< ushort4> () 
#line 284
{ 
#line 285
int e = (((int)sizeof(unsigned short)) * 8); 
#line 287
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned); 
#line 288
} 
#line 290
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< int> () 
#line 291
{ 
#line 292
int e = (((int)sizeof(int)) * 8); 
#line 294
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 295
} 
#line 297
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned> () 
#line 298
{ 
#line 299
int e = (((int)sizeof(unsigned)) * 8); 
#line 301
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 302
} 
#line 304
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< int1> () 
#line 305
{ 
#line 306
int e = (((int)sizeof(int)) * 8); 
#line 308
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 309
} 
#line 311
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< uint1> () 
#line 312
{ 
#line 313
int e = (((int)sizeof(unsigned)) * 8); 
#line 315
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 316
} 
#line 318
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< int2> () 
#line 319
{ 
#line 320
int e = (((int)sizeof(int)) * 8); 
#line 322
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned); 
#line 323
} 
#line 325
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< uint2> () 
#line 326
{ 
#line 327
int e = (((int)sizeof(unsigned)) * 8); 
#line 329
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned); 
#line 330
} 
#line 332
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< int4> () 
#line 333
{ 
#line 334
int e = (((int)sizeof(int)) * 8); 
#line 336
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned); 
#line 337
} 
#line 339
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< uint4> () 
#line 340
{ 
#line 341
int e = (((int)sizeof(unsigned)) * 8); 
#line 343
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned); 
#line 344
} 
#line 348
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< long> () 
#line 349
{ 
#line 350
int e = (((int)sizeof(long)) * 8); 
#line 352
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 353
} 
#line 355
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< unsigned long> () 
#line 356
{ 
#line 357
int e = (((int)sizeof(unsigned long)) * 8); 
#line 359
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 360
} 
#line 362
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< long1> () 
#line 363
{ 
#line 364
int e = (((int)sizeof(long)) * 8); 
#line 366
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindSigned); 
#line 367
} 
#line 369
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< ulong1> () 
#line 370
{ 
#line 371
int e = (((int)sizeof(unsigned long)) * 8); 
#line 373
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindUnsigned); 
#line 374
} 
#line 376
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< long2> () 
#line 377
{ 
#line 378
int e = (((int)sizeof(long)) * 8); 
#line 380
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindSigned); 
#line 381
} 
#line 383
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< ulong2> () 
#line 384
{ 
#line 385
int e = (((int)sizeof(unsigned long)) * 8); 
#line 387
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindUnsigned); 
#line 388
} 
#line 390
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 391
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< long4> () 
#line 392
{ 
#line 393
int e = (((int)sizeof(long)) * 8); 
#line 395
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindSigned); 
#line 396
} 
#line 398
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< ulong4> () 
#line 399
{ 
#line 400
int e = (((int)sizeof(unsigned long)) * 8); 
#line 402
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindUnsigned); 
#line 403
} 
#line 404
__pragma( warning(pop)) 
#line 408 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\channel_descriptor.h"
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< float> () 
#line 409
{ 
#line 410
int e = (((int)sizeof(float)) * 8); 
#line 412
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat); 
#line 413
} 
#line 415
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< float1> () 
#line 416
{ 
#line 417
int e = (((int)sizeof(float)) * 8); 
#line 419
return cudaCreateChannelDesc(e, 0, 0, 0, cudaChannelFormatKindFloat); 
#line 420
} 
#line 422
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< float2> () 
#line 423
{ 
#line 424
int e = (((int)sizeof(float)) * 8); 
#line 426
return cudaCreateChannelDesc(e, e, 0, 0, cudaChannelFormatKindFloat); 
#line 427
} 
#line 429
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< float4> () 
#line 430
{ 
#line 431
int e = (((int)sizeof(float)) * 8); 
#line 433
return cudaCreateChannelDesc(e, e, e, e, cudaChannelFormatKindFloat); 
#line 434
} 
#line 436
static __inline cudaChannelFormatDesc cudaCreateChannelDescNV12() 
#line 437
{ 
#line 438
int e = (((int)sizeof(char)) * 8); 
#line 440
return cudaCreateChannelDesc(e, e, e, 0, cudaChannelFormatKindNV12); 
#line 441
} 
#line 443
template< cudaChannelFormatKind > __inline ::cudaChannelFormatDesc cudaCreateChannelDesc() 
#line 444
{ 
#line 445
return cudaCreateChannelDesc(0, 0, 0, 0, cudaChannelFormatKindNone); 
#line 446
} 
#line 449
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedNormalized8X1> () 
#line 450
{ 
#line 451
return cudaCreateChannelDesc(8, 0, 0, 0, cudaChannelFormatKindSignedNormalized8X1); 
#line 452
} 
#line 454
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedNormalized8X2> () 
#line 455
{ 
#line 456
return cudaCreateChannelDesc(8, 8, 0, 0, cudaChannelFormatKindSignedNormalized8X2); 
#line 457
} 
#line 459
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedNormalized8X4> () 
#line 460
{ 
#line 461
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindSignedNormalized8X4); 
#line 462
} 
#line 465
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized8X1> () 
#line 466
{ 
#line 467
return cudaCreateChannelDesc(8, 0, 0, 0, cudaChannelFormatKindUnsignedNormalized8X1); 
#line 468
} 
#line 470
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized8X2> () 
#line 471
{ 
#line 472
return cudaCreateChannelDesc(8, 8, 0, 0, cudaChannelFormatKindUnsignedNormalized8X2); 
#line 473
} 
#line 475
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized8X4> () 
#line 476
{ 
#line 477
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedNormalized8X4); 
#line 478
} 
#line 481
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedNormalized16X1> () 
#line 482
{ 
#line 483
return cudaCreateChannelDesc(16, 0, 0, 0, cudaChannelFormatKindSignedNormalized16X1); 
#line 484
} 
#line 486
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedNormalized16X2> () 
#line 487
{ 
#line 488
return cudaCreateChannelDesc(16, 16, 0, 0, cudaChannelFormatKindSignedNormalized16X2); 
#line 489
} 
#line 491
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedNormalized16X4> () 
#line 492
{ 
#line 493
return cudaCreateChannelDesc(16, 16, 16, 16, cudaChannelFormatKindSignedNormalized16X4); 
#line 494
} 
#line 497
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized16X1> () 
#line 498
{ 
#line 499
return cudaCreateChannelDesc(16, 0, 0, 0, cudaChannelFormatKindUnsignedNormalized16X1); 
#line 500
} 
#line 502
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized16X2> () 
#line 503
{ 
#line 504
return cudaCreateChannelDesc(16, 16, 0, 0, cudaChannelFormatKindUnsignedNormalized16X2); 
#line 505
} 
#line 507
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized16X4> () 
#line 508
{ 
#line 509
return cudaCreateChannelDesc(16, 16, 16, 16, cudaChannelFormatKindUnsignedNormalized16X4); 
#line 510
} 
#line 513
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindNV12> () 
#line 514
{ 
#line 515
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindNV12); 
#line 516
} 
#line 519
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedNormalized1010102> () 
#line 520
{ 
#line 521
return cudaCreateChannelDesc(10, 10, 10, 2, cudaChannelFormatKindUnsignedNormalized1010102); 
#line 522
} 
#line 525
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed1> () 
#line 526
{ 
#line 527
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed1); 
#line 528
} 
#line 531
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed1SRGB> () 
#line 532
{ 
#line 533
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed1SRGB); 
#line 534
} 
#line 537
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed2> () 
#line 538
{ 
#line 539
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed2); 
#line 540
} 
#line 543
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed2SRGB> () 
#line 544
{ 
#line 545
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed2SRGB); 
#line 546
} 
#line 549
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed3> () 
#line 550
{ 
#line 551
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed3); 
#line 552
} 
#line 555
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed3SRGB> () 
#line 556
{ 
#line 557
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed3SRGB); 
#line 558
} 
#line 561
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed4> () 
#line 562
{ 
#line 563
return cudaCreateChannelDesc(8, 0, 0, 0, cudaChannelFormatKindUnsignedBlockCompressed4); 
#line 564
} 
#line 567
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedBlockCompressed4> () 
#line 568
{ 
#line 569
return cudaCreateChannelDesc(8, 0, 0, 0, cudaChannelFormatKindSignedBlockCompressed4); 
#line 570
} 
#line 573
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed5> () 
#line 574
{ 
#line 575
return cudaCreateChannelDesc(8, 8, 0, 0, cudaChannelFormatKindUnsignedBlockCompressed5); 
#line 576
} 
#line 579
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedBlockCompressed5> () 
#line 580
{ 
#line 581
return cudaCreateChannelDesc(8, 8, 0, 0, cudaChannelFormatKindSignedBlockCompressed5); 
#line 582
} 
#line 585
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed6H> () 
#line 586
{ 
#line 587
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsignedBlockCompressed6H); 
#line 588
} 
#line 591
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindSignedBlockCompressed6H> () 
#line 592
{ 
#line 593
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindSignedBlockCompressed6H); 
#line 594
} 
#line 597
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed7> () 
#line 598
{ 
#line 599
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed7); 
#line 600
} 
#line 603
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsignedBlockCompressed7SRGB> () 
#line 604
{ 
#line 605
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsignedBlockCompressed7SRGB); 
#line 606
} 
#line 609
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8Packed422> () 
#line 610
{ 
#line 611
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsigned8Packed422); 
#line 612
} 
#line 615
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8Packed444> () 
#line 616
{ 
#line 617
return cudaCreateChannelDesc(8, 8, 8, 8, cudaChannelFormatKindUnsigned8Packed444); 
#line 618
} 
#line 621
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8SemiPlanar420> () 
#line 622
{ 
#line 623
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindUnsigned8SemiPlanar420); 
#line 624
} 
#line 627
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned16SemiPlanar420> () 
#line 628
{ 
#line 629
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsigned16SemiPlanar420); 
#line 630
} 
#line 633
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8SemiPlanar422> () 
#line 634
{ 
#line 635
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindUnsigned8SemiPlanar422); 
#line 636
} 
#line 639
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned16SemiPlanar422> () 
#line 640
{ 
#line 641
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsigned16SemiPlanar422); 
#line 642
} 
#line 645
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8SemiPlanar444> () 
#line 646
{ 
#line 647
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindUnsigned8SemiPlanar444); 
#line 648
} 
#line 651
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned16SemiPlanar444> () 
#line 652
{ 
#line 653
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsigned16SemiPlanar444); 
#line 654
} 
#line 657
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8Planar420> () 
#line 658
{ 
#line 659
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindUnsigned8Planar420); 
#line 660
} 
#line 663
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned16Planar420> () 
#line 664
{ 
#line 665
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsigned16Planar420); 
#line 666
} 
#line 669
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8Planar422> () 
#line 670
{ 
#line 671
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindUnsigned8Planar422); 
#line 672
} 
#line 675
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned16Planar422> () 
#line 676
{ 
#line 677
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsigned16Planar422); 
#line 678
} 
#line 681
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned8Planar444> () 
#line 682
{ 
#line 683
return cudaCreateChannelDesc(8, 8, 8, 0, cudaChannelFormatKindUnsigned8Planar444); 
#line 684
} 
#line 687
template<> __inline cudaChannelFormatDesc cudaCreateChannelDesc< cudaChannelFormatKindUnsigned16Planar444> () 
#line 688
{ 
#line 689
return cudaCreateChannelDesc(16, 16, 16, 0, cudaChannelFormatKindUnsigned16Planar444); 
#line 690
} 
#line 79 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\driver_functions.h"
static __inline cudaPitchedPtr make_cudaPitchedPtr(void *d, size_t p, size_t xsz, size_t ysz) 
#line 80
{ 
#line 81
cudaPitchedPtr s; 
#line 83
(s.ptr) = d; 
#line 84
(s.pitch) = p; 
#line 85
(s.xsize) = xsz; 
#line 86
(s.ysize) = ysz; 
#line 88
return s; 
#line 89
} 
#line 106
static __inline cudaPos make_cudaPos(size_t x, size_t y, size_t z) 
#line 107
{ 
#line 108
cudaPos p; 
#line 110
(p.x) = x; 
#line 111
(p.y) = y; 
#line 112
(p.z) = z; 
#line 114
return p; 
#line 115
} 
#line 132
static __inline cudaExtent make_cudaExtent(size_t w, size_t h, size_t d) 
#line 133
{ 
#line 134
cudaExtent e; 
#line 136
(e.width) = w; 
#line 137
(e.height) = h; 
#line 138
(e.depth) = d; 
#line 140
return e; 
#line 141
} 
#line 77 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_functions.h"
static __inline char1 make_char1(signed char x); 
#line 79
static __inline uchar1 make_uchar1(unsigned char x); 
#line 81
static __inline char2 make_char2(signed char x, signed char y); 
#line 83
static __inline uchar2 make_uchar2(unsigned char x, unsigned char y); 
#line 85
static __inline char3 make_char3(signed char x, signed char y, signed char z); 
#line 87
static __inline uchar3 make_uchar3(unsigned char x, unsigned char y, unsigned char z); 
#line 89
static __inline char4 make_char4(signed char x, signed char y, signed char z, signed char w); 
#line 91
static __inline uchar4 make_uchar4(unsigned char x, unsigned char y, unsigned char z, unsigned char w); 
#line 93
static __inline short1 make_short1(short x); 
#line 95
static __inline ushort1 make_ushort1(unsigned short x); 
#line 97
static __inline short2 make_short2(short x, short y); 
#line 99
static __inline ushort2 make_ushort2(unsigned short x, unsigned short y); 
#line 101
static __inline short3 make_short3(short x, short y, short z); 
#line 103
static __inline ushort3 make_ushort3(unsigned short x, unsigned short y, unsigned short z); 
#line 105
static __inline short4 make_short4(short x, short y, short z, short w); 
#line 107
static __inline ushort4 make_ushort4(unsigned short x, unsigned short y, unsigned short z, unsigned short w); 
#line 109
static __inline int1 make_int1(int x); 
#line 111
static __inline uint1 make_uint1(unsigned x); 
#line 113
static __inline int2 make_int2(int x, int y); 
#line 115
static __inline uint2 make_uint2(unsigned x, unsigned y); 
#line 117
static __inline int3 make_int3(int x, int y, int z); 
#line 119
static __inline uint3 make_uint3(unsigned x, unsigned y, unsigned z); 
#line 121
static __inline int4 make_int4(int x, int y, int z, int w); 
#line 123
static __inline uint4 make_uint4(unsigned x, unsigned y, unsigned z, unsigned w); 
#line 125
static __inline long1 make_long1(long x); 
#line 127
static __inline ulong1 make_ulong1(unsigned long x); 
#line 129
static __inline long2 make_long2(long x, long y); 
#line 131
static __inline ulong2 make_ulong2(unsigned long x, unsigned long y); 
#line 133
static __inline long3 make_long3(long x, long y, long z); 
#line 135
static __inline ulong3 make_ulong3(unsigned long x, unsigned long y, unsigned long z); 
#line 137
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 138
static __inline long4 make_long4(long x, long y, long z, long w); 
#line 140
static __inline ulong4 make_ulong4(unsigned long x, unsigned long y, unsigned long z, unsigned long w); 
#line 141
__pragma( warning(pop)) 
#line 143
static __inline long4_16a make_long4_16a(long x, long y, long z, long w); 
#line 145
static __inline long4_32a make_long4_32a(long x, long y, long z, long w); 
#line 147
static __inline ulong4_16a make_ulong4_16a(unsigned long x, unsigned long y, unsigned long z, unsigned long w); 
#line 149
static __inline ulong4_32a make_ulong4_32a(unsigned long x, unsigned long y, unsigned long z, unsigned long w); 
#line 151
static __inline float1 make_float1(float x); 
#line 153
static __inline float2 make_float2(float x, float y); 
#line 155
static __inline float3 make_float3(float x, float y, float z); 
#line 157
static __inline float4 make_float4(float x, float y, float z, float w); 
#line 159
static __inline longlong1 make_longlong1(__int64 x); 
#line 161
static __inline ulonglong1 make_ulonglong1(unsigned __int64 x); 
#line 163
static __inline longlong2 make_longlong2(__int64 x, __int64 y); 
#line 165
static __inline ulonglong2 make_ulonglong2(unsigned __int64 x, unsigned __int64 y); 
#line 167
static __inline longlong3 make_longlong3(__int64 x, __int64 y, __int64 z); 
#line 169
static __inline ulonglong3 make_ulonglong3(unsigned __int64 x, unsigned __int64 y, unsigned __int64 z); 
#line 171
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 172
static __inline longlong4 make_longlong4(__int64 x, __int64 y, __int64 z, __int64 w); 
#line 174
static __inline ulonglong4 make_ulonglong4(unsigned __int64 x, unsigned __int64 y, unsigned __int64 z, unsigned __int64 w); 
#line 175
__pragma( warning(pop)) 
#line 177
static __inline double1 make_double1(double x); 
#line 179
static __inline double2 make_double2(double x, double y); 
#line 181
static __inline double3 make_double3(double x, double y, double z); 
#line 183
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 184
static __inline double4 make_double4(double x, double y, double z, double w); 
#line 185
__pragma( warning(pop)) 
#line 187
static __inline double4_16a make_double4_16a(double x, double y, double z, double w); 
#line 189
static __inline double4_32a make_double4_32a(double x, double y, double z, double w); 
#line 73 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\vector_functions.hpp"
static __inline char1 make_char1(signed char x) 
#line 74
{ 
#line 75
char1 t; (t.x) = x; return t; 
#line 76
} 
#line 78
static __inline uchar1 make_uchar1(unsigned char x) 
#line 79
{ 
#line 80
uchar1 t; (t.x) = x; return t; 
#line 81
} 
#line 83
static __inline char2 make_char2(signed char x, signed char y) 
#line 84
{ 
#line 85
char2 t; (t.x) = x; (t.y) = y; return t; 
#line 86
} 
#line 88
static __inline uchar2 make_uchar2(unsigned char x, unsigned char y) 
#line 89
{ 
#line 90
uchar2 t; (t.x) = x; (t.y) = y; return t; 
#line 91
} 
#line 93
static __inline char3 make_char3(signed char x, signed char y, signed char z) 
#line 94
{ 
#line 95
char3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 96
} 
#line 98
static __inline uchar3 make_uchar3(unsigned char x, unsigned char y, unsigned char z) 
#line 99
{ 
#line 100
uchar3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 101
} 
#line 103
static __inline char4 make_char4(signed char x, signed char y, signed char z, signed char w) 
#line 104
{ 
#line 105
char4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 106
} 
#line 108
static __inline uchar4 make_uchar4(unsigned char x, unsigned char y, unsigned char z, unsigned char w) 
#line 109
{ 
#line 110
uchar4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 111
} 
#line 113
static __inline short1 make_short1(short x) 
#line 114
{ 
#line 115
short1 t; (t.x) = x; return t; 
#line 116
} 
#line 118
static __inline ushort1 make_ushort1(unsigned short x) 
#line 119
{ 
#line 120
ushort1 t; (t.x) = x; return t; 
#line 121
} 
#line 123
static __inline short2 make_short2(short x, short y) 
#line 124
{ 
#line 125
short2 t; (t.x) = x; (t.y) = y; return t; 
#line 126
} 
#line 128
static __inline ushort2 make_ushort2(unsigned short x, unsigned short y) 
#line 129
{ 
#line 130
ushort2 t; (t.x) = x; (t.y) = y; return t; 
#line 131
} 
#line 133
static __inline short3 make_short3(short x, short y, short z) 
#line 134
{ 
#line 135
short3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 136
} 
#line 138
static __inline ushort3 make_ushort3(unsigned short x, unsigned short y, unsigned short z) 
#line 139
{ 
#line 140
ushort3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 141
} 
#line 143
static __inline short4 make_short4(short x, short y, short z, short w) 
#line 144
{ 
#line 145
short4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 146
} 
#line 148
static __inline ushort4 make_ushort4(unsigned short x, unsigned short y, unsigned short z, unsigned short w) 
#line 149
{ 
#line 150
ushort4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 151
} 
#line 153
static __inline int1 make_int1(int x) 
#line 154
{ 
#line 155
int1 t; (t.x) = x; return t; 
#line 156
} 
#line 158
static __inline uint1 make_uint1(unsigned x) 
#line 159
{ 
#line 160
uint1 t; (t.x) = x; return t; 
#line 161
} 
#line 163
static __inline int2 make_int2(int x, int y) 
#line 164
{ 
#line 165
int2 t; (t.x) = x; (t.y) = y; return t; 
#line 166
} 
#line 168
static __inline uint2 make_uint2(unsigned x, unsigned y) 
#line 169
{ 
#line 170
uint2 t; (t.x) = x; (t.y) = y; return t; 
#line 171
} 
#line 173
static __inline int3 make_int3(int x, int y, int z) 
#line 174
{ 
#line 175
int3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 176
} 
#line 178
static __inline uint3 make_uint3(unsigned x, unsigned y, unsigned z) 
#line 179
{ 
#line 180
uint3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 181
} 
#line 183
static __inline int4 make_int4(int x, int y, int z, int w) 
#line 184
{ 
#line 185
int4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 186
} 
#line 188
static __inline uint4 make_uint4(unsigned x, unsigned y, unsigned z, unsigned w) 
#line 189
{ 
#line 190
uint4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 191
} 
#line 193
static __inline long1 make_long1(long x) 
#line 194
{ 
#line 195
long1 t; (t.x) = x; return t; 
#line 196
} 
#line 198
static __inline ulong1 make_ulong1(unsigned long x) 
#line 199
{ 
#line 200
ulong1 t; (t.x) = x; return t; 
#line 201
} 
#line 203
static __inline long2 make_long2(long x, long y) 
#line 204
{ 
#line 205
long2 t; (t.x) = x; (t.y) = y; return t; 
#line 206
} 
#line 208
static __inline ulong2 make_ulong2(unsigned long x, unsigned long y) 
#line 209
{ 
#line 210
ulong2 t; (t.x) = x; (t.y) = y; return t; 
#line 211
} 
#line 213
static __inline long3 make_long3(long x, long y, long z) 
#line 214
{ 
#line 215
long3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 216
} 
#line 218
static __inline ulong3 make_ulong3(unsigned long x, unsigned long y, unsigned long z) 
#line 219
{ 
#line 220
ulong3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 221
} 
#line 223
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 224
static __inline long4 make_long4(long x, long y, long z, long w) 
#line 225
{ 
#line 226
long4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 227
} 
#line 229
static __inline ulong4 make_ulong4(unsigned long x, unsigned long y, unsigned long z, unsigned long w) 
#line 230
{ 
#line 231
ulong4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 232
} 
#line 233
__pragma( warning(pop)) 
#line 235
static __inline long4_16a make_long4_16a(long x, long y, long z, long w) 
#line 236
{ 
#line 237
long4_16a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 238
} 
#line 240
static __inline long4_32a make_long4_32a(long x, long y, long z, long w) 
#line 241
{ 
#line 242
long4_32a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 243
} 
#line 245
static __inline ulong4_16a make_ulong4_16a(unsigned long x, unsigned long y, unsigned long z, unsigned long w) 
#line 246
{ 
#line 247
ulong4_16a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 248
} 
#line 250
static __inline ulong4_32a make_ulong4_32a(unsigned long x, unsigned long y, unsigned long z, unsigned long w) 
#line 251
{ 
#line 252
ulong4_32a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 253
} 
#line 255
static __inline float1 make_float1(float x) 
#line 256
{ 
#line 257
float1 t; (t.x) = x; return t; 
#line 258
} 
#line 260
static __inline float2 make_float2(float x, float y) 
#line 261
{ 
#line 262
float2 t; (t.x) = x; (t.y) = y; return t; 
#line 263
} 
#line 265
static __inline float3 make_float3(float x, float y, float z) 
#line 266
{ 
#line 267
float3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 268
} 
#line 270
static __inline float4 make_float4(float x, float y, float z, float w) 
#line 271
{ 
#line 272
float4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 273
} 
#line 275
static __inline longlong1 make_longlong1(__int64 x) 
#line 276
{ 
#line 277
longlong1 t; (t.x) = x; return t; 
#line 278
} 
#line 280
static __inline ulonglong1 make_ulonglong1(unsigned __int64 x) 
#line 281
{ 
#line 282
ulonglong1 t; (t.x) = x; return t; 
#line 283
} 
#line 285
static __inline longlong2 make_longlong2(__int64 x, __int64 y) 
#line 286
{ 
#line 287
longlong2 t; (t.x) = x; (t.y) = y; return t; 
#line 288
} 
#line 290
static __inline ulonglong2 make_ulonglong2(unsigned __int64 x, unsigned __int64 y) 
#line 291
{ 
#line 292
ulonglong2 t; (t.x) = x; (t.y) = y; return t; 
#line 293
} 
#line 295
static __inline longlong3 make_longlong3(__int64 x, __int64 y, __int64 z) 
#line 296
{ 
#line 297
longlong3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 298
} 
#line 300
static __inline ulonglong3 make_ulonglong3(unsigned __int64 x, unsigned __int64 y, unsigned __int64 z) 
#line 301
{ 
#line 302
ulonglong3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 303
} 
#line 305
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 306
static __inline longlong4 make_longlong4(__int64 x, __int64 y, __int64 z, __int64 w) 
#line 307
{ 
#line 308
longlong4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 309
} 
#line 311
static __inline ulonglong4 make_ulonglong4(unsigned __int64 x, unsigned __int64 y, unsigned __int64 z, unsigned __int64 w) 
#line 312
{ 
#line 313
ulonglong4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 314
} 
#line 315
__pragma( warning(pop)) 
#line 317
static __inline longlong4_16a make_longlong4_16a(__int64 x, __int64 y, __int64 z, __int64 w) 
#line 318
{ 
#line 319
longlong4_16a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 320
} 
#line 322
static __inline longlong4_32a make_longlong4_32a(__int64 x, __int64 y, __int64 z, __int64 w) 
#line 323
{ 
#line 324
longlong4_32a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 325
} 
#line 327
static __inline ulonglong4_16a make_ulonglong4_16a(unsigned __int64 x, unsigned __int64 y, unsigned __int64 z, unsigned __int64 w) 
#line 328
{ 
#line 329
ulonglong4_16a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 330
} 
#line 332
static __inline ulonglong4_32a make_ulonglong4_32a(unsigned __int64 x, unsigned __int64 y, unsigned __int64 z, unsigned __int64 w) 
#line 333
{ 
#line 334
ulonglong4_32a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 335
} 
#line 336
static __inline double1 make_double1(double x) 
#line 337
{ 
#line 338
double1 t; (t.x) = x; return t; 
#line 339
} 
#line 341
static __inline double2 make_double2(double x, double y) 
#line 342
{ 
#line 343
double2 t; (t.x) = x; (t.y) = y; return t; 
#line 344
} 
#line 346
static __inline double3 make_double3(double x, double y, double z) 
#line 347
{ 
#line 348
double3 t; (t.x) = x; (t.y) = y; (t.z) = z; return t; 
#line 349
} 
#line 351
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 352
static __inline double4 make_double4(double x, double y, double z, double w) 
#line 353
{ 
#line 354
double4 t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 355
} 
#line 356
__pragma( warning(pop)) 
#line 358
static __inline double4_16a make_double4_16a(double x, double y, double z, double w) 
#line 359
{ 
#line 360
double4_16a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 361
} 
#line 363
static __inline double4_32a make_double4_32a(double x, double y, double z, double w) 
#line 364
{ 
#line 365
double4_32a t; (t.x) = x; (t.y) = y; (t.z) = z; (t.w) = w; return t; 
#line 366
} 
#line 14 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\errno.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 18
__pragma( pack ( push, 8 )) extern "C" {
#line 23
int *__cdecl _errno(); 
#line 26
errno_t __cdecl _set_errno(int _Value); 
#line 27
errno_t __cdecl _get_errno(int * _Value); 
#line 29
unsigned long *__cdecl __doserrno(); 
#line 32
errno_t __cdecl _set_doserrno(unsigned long _Value); 
#line 33
errno_t __cdecl _get_doserrno(unsigned long * _Value); 
#line 134 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\errno.h"
}__pragma( pack ( pop )) 
#line 136
#pragma warning(pop)
#line 12 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_string.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 17
__pragma( pack ( push, 8 )) extern "C" {
#line 21
[[nodiscard]] const void *__cdecl 
#line 22
memchr(const void * _Buf, int _Val, size_t _MaxCount); 
#line 28
[[nodiscard]] int __cdecl 
#line 29
memcmp(const void * _Buf1, const void * _Buf2, size_t _Size); 
#line 43 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_string.h"
void *__cdecl memcpy(void * _Dst, const void * _Src, size_t _Size); 
#line 50
void *__cdecl memmove(void * _Dst, const void * _Src, size_t _Size); 
#line 63 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_string.h"
void *__cdecl memset(void * _Dst, int _Val, size_t _Size); 
#line 69
[[nodiscard]] const char *__cdecl 
#line 70
strchr(const char * _Str, int _Val); 
#line 75
[[nodiscard]] const char *__cdecl 
#line 76
strrchr(const char * _Str, int _Ch); 
#line 81
[[nodiscard]] const char *__cdecl 
#line 82
strstr(const char * _Str, const char * _SubStr); 
#line 87
[[nodiscard]] const __wchar_t *__cdecl 
#line 89
wcschr(const __wchar_t * _Str, __wchar_t _Ch); 
#line 94
[[nodiscard]] const __wchar_t *__cdecl 
#line 95
wcsrchr(const __wchar_t * _Str, __wchar_t _Ch); 
#line 100
[[nodiscard]] const __wchar_t *__cdecl 
#line 102
wcsstr(const __wchar_t * _Str, const __wchar_t * _SubStr); 
#line 109
}__pragma( pack ( pop )) 
#line 113 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_string.h"
#pragma warning(pop)
#line 14 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memcpy_s.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 18
__pragma( pack ( push, 8 )) extern "C" {
#line 40 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memcpy_s.h"
static __inline errno_t __cdecl memcpy_s(void *const 
#line 41
_Destination, const rsize_t 
#line 42
_DestinationSize, const void *const 
#line 43
_Source, const rsize_t 
#line 44
_SourceSize) 
#line 46
{ 
#line 47
if (_SourceSize == (0)) 
#line 48
{ 
#line 49
return 0; 
#line 50
}  
#line 52
{ int _Expr_val = !(!(_Destination != (0))); if (!_Expr_val) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; }  } ; 
#line 53
if ((_Source == (0)) || (_DestinationSize < _SourceSize)) 
#line 54
{ 
#line 55
memset(_Destination, 0, _DestinationSize); 
#line 57
{ int _Expr_val = !(!(_Source != (0))); if (!_Expr_val) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; }  } ; 
#line 58
{ int _Expr_val = !(!(_DestinationSize >= _SourceSize)); if (!_Expr_val) { (*_errno()) = 34; _invalid_parameter_noinfo(); return 34; }  } ; 
#line 61
return 22; 
#line 62
}  
#line 63
memcpy(_Destination, _Source, _SourceSize); 
#line 64
return 0; 
#line 65
} 
#line 69
static __inline errno_t __cdecl memmove_s(void *const 
#line 70
_Destination, const rsize_t 
#line 71
_DestinationSize, const void *const 
#line 72
_Source, const rsize_t 
#line 73
_SourceSize) 
#line 75
{ 
#line 76
if (_SourceSize == (0)) 
#line 77
{ 
#line 78
return 0; 
#line 79
}  
#line 81
{ int _Expr_val = !(!(_Destination != (0))); if (!_Expr_val) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; }  } ; 
#line 82
{ int _Expr_val = !(!(_Source != (0))); if (!_Expr_val) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; }  } ; 
#line 83
{ int _Expr_val = !(!(_DestinationSize >= _SourceSize)); if (!_Expr_val) { (*_errno()) = 34; _invalid_parameter_noinfo(); return 34; }  } ; 
#line 85
memmove(_Destination, _Source, _SourceSize); 
#line 86
return 0; 
#line 87
} 
#line 95 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memcpy_s.h"
}
#line 94
#pragma warning(pop)
__pragma( pack ( pop )) 
#line 17 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memory.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 23
__pragma( pack ( push, 8 )) extern "C" {
#line 28
int __cdecl _memicmp(const void * _Buf1, const void * _Buf2, size_t _Size); 
#line 35
int __cdecl _memicmp_l(const void * _Buf1, const void * _Buf2, size_t _Size, _locale_t _Locale); 
#line 83 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memory.h"
void *__cdecl memccpy(void * _Dst, const void * _Src, int _Val, size_t _Size); 
#line 91
int __cdecl memicmp(const void * _Buf1, const void * _Buf2, size_t _Size); 
#line 104 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memory.h"
extern "C++" inline void *__cdecl memchr(void *
#line 105
_Pv, int 
#line 106
_C, size_t 
#line 107
_N) 
#line 109
{ 
#line 110
const void *const _Pvc = _Pv; 
#line 111
return const_cast< void *>(memchr(_Pvc, _C, _N)); 
#line 112
} 
#line 118 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memory.h"
}__pragma( pack ( pop )) 
#line 122 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_memory.h"
#pragma warning(pop)
#line 14 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 20
__pragma( pack ( push, 8 )) extern "C" {
#line 32
errno_t __cdecl wcscat_s(__wchar_t * _Destination, rsize_t _SizeInWords, const __wchar_t * _Source); 
#line 39
errno_t __cdecl wcscpy_s(__wchar_t * _Destination, rsize_t _SizeInWords, const __wchar_t * _Source); 
#line 46
errno_t __cdecl wcsncat_s(__wchar_t * _Destination, rsize_t _SizeInWords, const __wchar_t * _Source, rsize_t _MaxCount); 
#line 54
errno_t __cdecl wcsncpy_s(__wchar_t * _Destination, rsize_t _SizeInWords, const __wchar_t * _Source, rsize_t _MaxCount); 
#line 62
__wchar_t *__cdecl wcstok_s(__wchar_t * _String, const __wchar_t * _Delimiter, __wchar_t ** _Context); 
#line 83 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__declspec(allocator) __wchar_t *__cdecl _wcsdup(const __wchar_t * _String); 
#line 93 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
extern "C++" {template < size_t _Size > inline errno_t __cdecl wcscat_s ( wchar_t ( & _Destination ) [ _Size ], wchar_t const * _Source ) throw ( ) { return wcscat_s ( _Destination, _Size, _Source ); }}
#line 100 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl wcscat(__wchar_t * _Destination, const __wchar_t * _Source); 
#line 108 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
int __cdecl wcscmp(const __wchar_t * _String1, const __wchar_t * _String2); 
#line 113
extern "C++" {template < size_t _Size > inline errno_t __cdecl wcscpy_s ( wchar_t ( & _Destination ) [ _Size ], wchar_t const * _Source ) throw ( ) { return wcscpy_s ( _Destination, _Size, _Source ); }}
#line 119 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl wcscpy(__wchar_t * _Destination, const __wchar_t * _Source); 
#line 126 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
size_t __cdecl wcscspn(const __wchar_t * _String, const __wchar_t * _Control); 
#line 132
size_t __cdecl wcslen(const __wchar_t * _String); 
#line 145 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
size_t __cdecl wcsnlen(const __wchar_t * _Source, size_t _MaxCount); 
#line 161 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__inline size_t __cdecl wcsnlen_s(const __wchar_t *
#line 162
_Source, size_t 
#line 163
_MaxCount) 
#line 165
{ 
#line 166
return (_Source == (0)) ? 0 : wcsnlen(_Source, _MaxCount); 
#line 167
} 
#line 171 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
extern "C++" {template < size_t _Size > inline errno_t __cdecl wcsncat_s ( wchar_t ( & _Destination ) [ _Size ], wchar_t const * _Source, size_t _Count ) throw ( ) { return wcsncat_s ( _Destination, _Size, _Source, _Count ); }}
#line 178 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl wcsncat(__wchar_t * _Destination, const __wchar_t * _Source, size_t _Count); 
#line 187 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
int __cdecl wcsncmp(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount); 
#line 193
extern "C++" {template < size_t _Size > inline errno_t __cdecl wcsncpy_s ( wchar_t ( & _Destination ) [ _Size ], wchar_t const * _Source, size_t _Count ) throw ( ) { return wcsncpy_s ( _Destination, _Size, _Source, _Count ); }}
#line 200 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl wcsncpy(__wchar_t * _Destination, const __wchar_t * _Source, size_t _Count); 
#line 209 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
const __wchar_t *__cdecl wcspbrk(const __wchar_t * _String, const __wchar_t * _Control); 
#line 215
size_t __cdecl wcsspn(const __wchar_t * _String, const __wchar_t * _Control); 
#line 221
__wchar_t *__cdecl wcstok(__wchar_t * _String, const __wchar_t * _Delimiter, __wchar_t ** _Context); 
#line 240 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
static __inline __wchar_t *__cdecl _wcstok(__wchar_t *const 
#line 241
_String, const __wchar_t *const 
#line 242
_Delimiter) 
#line 244
{ 
#line 245
return wcstok(_String, _Delimiter, 0); 
#line 246
} 
#line 254 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
extern "C++" 
#line 253
__declspec(deprecated("wcstok has been changed to conform with the ISO C standard, adding an extra context parameter. To use the legacy Microsoft wcsto" "k, define _CRT_NON_CONFORMING_WCSTOK.")) inline __wchar_t *__cdecl 
#line 254
wcstok(__wchar_t *
#line 255
_String, const __wchar_t *
#line 256
_Delimiter) throw() 
#line 258
{ 
#line 259
return wcstok(_String, _Delimiter, 0); 
#line 260
} 
#line 269 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcserror(int _ErrorNumber); 
#line 274
errno_t __cdecl _wcserror_s(__wchar_t * _Buffer, size_t _SizeInWords, int _ErrorNumber); 
#line 280
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcserror_s ( wchar_t ( & _Buffer ) [ _Size ], int _Error ) throw ( ) { return _wcserror_s ( _Buffer, _Size, _Error ); }}
#line 289 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl __wcserror(const __wchar_t * _String); 
#line 293
errno_t __cdecl __wcserror_s(__wchar_t * _Buffer, size_t _SizeInWords, const __wchar_t * _ErrorMessage); 
#line 299
extern "C++" {template < size_t _Size > inline errno_t __cdecl __wcserror_s ( wchar_t ( & _Buffer ) [ _Size ], wchar_t const * _ErrorMessage ) throw ( ) { return __wcserror_s ( _Buffer, _Size, _ErrorMessage ); }}
#line 305 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
int __cdecl _wcsicmp(const __wchar_t * _String1, const __wchar_t * _String2); 
#line 310
int __cdecl _wcsicmp_l(const __wchar_t * _String1, const __wchar_t * _String2, _locale_t _Locale); 
#line 316
int __cdecl _wcsnicmp(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount); 
#line 322
int __cdecl _wcsnicmp_l(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount, _locale_t _Locale); 
#line 329
errno_t __cdecl _wcsnset_s(__wchar_t * _Destination, size_t _SizeInWords, __wchar_t _Value, size_t _MaxCount); 
#line 336
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcsnset_s ( wchar_t ( & _Destination ) [ _Size ], wchar_t _Value, size_t _MaxCount ) throw ( ) { return _wcsnset_s ( _Destination, _Size, _Value, _MaxCount ); }}
#line 343 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcsnset(__wchar_t * _String, __wchar_t _Value, size_t _MaxCount); 
#line 351 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcsrev(__wchar_t * _String); 
#line 355
errno_t __cdecl _wcsset_s(__wchar_t * _Destination, size_t _SizeInWords, __wchar_t _Value); 
#line 361
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcsset_s ( wchar_t ( & _String ) [ _Size ], wchar_t _Value ) throw ( ) { return _wcsset_s ( _String, _Size, _Value ); }}
#line 367 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcsset(__wchar_t * _String, __wchar_t _Value); 
#line 374 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
errno_t __cdecl _wcslwr_s(__wchar_t * _String, size_t _SizeInWords); 
#line 379
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcslwr_s ( wchar_t ( & _String ) [ _Size ] ) throw ( ) { return _wcslwr_s ( _String, _Size ); }}
#line 384 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcslwr(__wchar_t * _String); 
#line 390 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
errno_t __cdecl _wcslwr_s_l(__wchar_t * _String, size_t _SizeInWords, _locale_t _Locale); 
#line 396
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcslwr_s_l ( wchar_t ( & _String ) [ _Size ], _locale_t _Locale ) throw ( ) { return _wcslwr_s_l ( _String, _Size, _Locale ); }}
#line 402 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcslwr_l(__wchar_t * _String, _locale_t _Locale); 
#line 410 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
errno_t __cdecl _wcsupr_s(__wchar_t * _String, size_t _Size); 
#line 415
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcsupr_s ( wchar_t ( & _String ) [ _Size ] ) throw ( ) { return _wcsupr_s ( _String, _Size ); }}
#line 420 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcsupr(__wchar_t * _String); 
#line 426 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
errno_t __cdecl _wcsupr_s_l(__wchar_t * _String, size_t _Size, _locale_t _Locale); 
#line 432
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wcsupr_s_l ( wchar_t ( & _String ) [ _Size ], _locale_t _Locale ) throw ( ) { return _wcsupr_s_l ( _String, _Size, _Locale ); }}
#line 438 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl _wcsupr_l(__wchar_t * _String, _locale_t _Locale); 
#line 447 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
size_t __cdecl wcsxfrm(__wchar_t * _Destination, const __wchar_t * _Source, size_t _MaxCount); 
#line 455
size_t __cdecl _wcsxfrm_l(__wchar_t * _Destination, const __wchar_t * _Source, size_t _MaxCount, _locale_t _Locale); 
#line 463
int __cdecl wcscoll(const __wchar_t * _String1, const __wchar_t * _String2); 
#line 469
int __cdecl _wcscoll_l(const __wchar_t * _String1, const __wchar_t * _String2, _locale_t _Locale); 
#line 476
int __cdecl _wcsicoll(const __wchar_t * _String1, const __wchar_t * _String2); 
#line 482
int __cdecl _wcsicoll_l(const __wchar_t * _String1, const __wchar_t * _String2, _locale_t _Locale); 
#line 489
int __cdecl _wcsncoll(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount); 
#line 496
int __cdecl _wcsncoll_l(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount, _locale_t _Locale); 
#line 504
int __cdecl _wcsnicoll(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount); 
#line 511
int __cdecl _wcsnicoll_l(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount, _locale_t _Locale); 
#line 526
extern "C++" {
#line 530
inline __wchar_t *__cdecl wcschr(__wchar_t *_String, __wchar_t _C) 
#line 531
{ 
#line 532
return const_cast< __wchar_t *>(wcschr(static_cast< const __wchar_t *>(_String), _C)); 
#line 533
} 
#line 536
inline __wchar_t *__cdecl wcspbrk(__wchar_t *_String, const __wchar_t *_Control) 
#line 537
{ 
#line 538
return const_cast< __wchar_t *>(wcspbrk(static_cast< const __wchar_t *>(_String), _Control)); 
#line 539
} 
#line 542
inline __wchar_t *__cdecl wcsrchr(__wchar_t *_String, __wchar_t _C) 
#line 543
{ 
#line 544
return const_cast< __wchar_t *>(wcsrchr(static_cast< const __wchar_t *>(_String), _C)); 
#line 545
} 
#line 549
inline __wchar_t *__cdecl wcsstr(__wchar_t *_String, const __wchar_t *_SubStr) 
#line 550
{ 
#line 551
return const_cast< __wchar_t *>(wcsstr(static_cast< const __wchar_t *>(_String), _SubStr)); 
#line 552
} 
#line 554
}
#line 571 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
__wchar_t *__cdecl wcsdup(const __wchar_t * _String); 
#line 583 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
int __cdecl wcsicmp(const __wchar_t * _String1, const __wchar_t * _String2); 
#line 589
int __cdecl wcsnicmp(const __wchar_t * _String1, const __wchar_t * _String2, size_t _MaxCount); 
#line 597
__wchar_t *__cdecl wcsnset(__wchar_t * _String, __wchar_t _Value, size_t _MaxCount); 
#line 605
__wchar_t *__cdecl wcsrev(__wchar_t * _String); 
#line 611
__wchar_t *__cdecl wcsset(__wchar_t * _String, __wchar_t _Value); 
#line 618
__wchar_t *__cdecl wcslwr(__wchar_t * _String); 
#line 624
__wchar_t *__cdecl wcsupr(__wchar_t * _String); 
#line 629
int __cdecl wcsicoll(const __wchar_t * _String1, const __wchar_t * _String2); 
#line 638 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
}__pragma( pack ( pop )) 
#line 642 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wstring.h"
#pragma warning(pop)
#line 19 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 23
__pragma( pack ( push, 8 )) extern "C" {
#line 32
errno_t __cdecl strcpy_s(char * _Destination, rsize_t _SizeInBytes, const char * _Source); 
#line 39
errno_t __cdecl strcat_s(char * _Destination, rsize_t _SizeInBytes, const char * _Source); 
#line 46
errno_t __cdecl strerror_s(char * _Buffer, size_t _SizeInBytes, int _ErrorNumber); 
#line 52
errno_t __cdecl strncat_s(char * _Destination, rsize_t _SizeInBytes, const char * _Source, rsize_t _MaxCount); 
#line 60
errno_t __cdecl strncpy_s(char * _Destination, rsize_t _SizeInBytes, const char * _Source, rsize_t _MaxCount); 
#line 68
char *__cdecl strtok_s(char * _String, const char * _Delimiter, char ** _Context); 
#line 76 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
void *__cdecl _memccpy(void * _Dst, const void * _Src, int _Val, size_t _MaxCount); 
#line 83
extern "C++" {template < size_t _Size > inline errno_t __cdecl strcat_s ( char ( & _Destination ) [ _Size ], char const * _Source ) throw ( ) { return strcat_s ( _Destination, _Size, _Source ); }}
#line 91 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl strcat(char * _Destination, const char * _Source); 
#line 100 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
int __cdecl strcmp(const char * _Str1, const char * _Str2); 
#line 106
int __cdecl _strcmpi(const char * _String1, const char * _String2); 
#line 112
int __cdecl strcoll(const char * _String1, const char * _String2); 
#line 118
int __cdecl _strcoll_l(const char * _String1, const char * _String2, _locale_t _Locale); 
#line 124
extern "C++" {template < size_t _Size > inline errno_t __cdecl strcpy_s ( char ( & _Destination ) [ _Size ], char const * _Source ) throw ( ) { return strcpy_s ( _Destination, _Size, _Source ); }}
#line 130 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl strcpy(char * _Destination, const char * _Source); 
#line 137 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
size_t __cdecl strcspn(const char * _Str, const char * _Control); 
#line 148 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
__declspec(allocator) char *__cdecl _strdup(const char * _Source); 
#line 159 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strerror(const char * _ErrorMessage); 
#line 164
errno_t __cdecl _strerror_s(char * _Buffer, size_t _SizeInBytes, const char * _ErrorMessage); 
#line 170
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strerror_s ( char ( & _Buffer ) [ _Size ], char const * _ErrorMessage ) throw ( ) { return _strerror_s ( _Buffer, _Size, _ErrorMessage ); }}
#line 178 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl strerror(int _ErrorMessage); 
#line 182
extern "C++" {template < size_t _Size > inline errno_t __cdecl strerror_s ( char ( & _Buffer ) [ _Size ], int _ErrorMessage ) throw ( ) { return strerror_s ( _Buffer, _Size, _ErrorMessage ); }}
#line 189 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
int __cdecl _stricmp(const char * _String1, const char * _String2); 
#line 195
int __cdecl _stricoll(const char * _String1, const char * _String2); 
#line 201
int __cdecl _stricoll_l(const char * _String1, const char * _String2, _locale_t _Locale); 
#line 208
int __cdecl _stricmp_l(const char * _String1, const char * _String2, _locale_t _Locale); 
#line 215
size_t __cdecl strlen(const char * _Str); 
#line 220
errno_t __cdecl _strlwr_s(char * _String, size_t _Size); 
#line 225
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strlwr_s ( char ( & _String ) [ _Size ] ) throw ( ) { return _strlwr_s ( _String, _Size ); }}
#line 230 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strlwr(char * _String); 
#line 236 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
errno_t __cdecl _strlwr_s_l(char * _String, size_t _Size, _locale_t _Locale); 
#line 242
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strlwr_s_l ( char ( & _String ) [ _Size ], _locale_t _Locale ) throw ( ) { return _strlwr_s_l ( _String, _Size, _Locale ); }}
#line 248 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strlwr_l(char * _String, _locale_t _Locale); 
#line 255 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
extern "C++" {template < size_t _Size > inline errno_t __cdecl strncat_s ( char ( & _Destination ) [ _Size ], char const * _Source, size_t _Count ) throw ( ) { return strncat_s ( _Destination, _Size, _Source, _Count ); }}
#line 262 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl strncat(char * _Destination, const char * _Source, size_t _Count); 
#line 271 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
int __cdecl strncmp(const char * _Str1, const char * _Str2, size_t _MaxCount); 
#line 278
int __cdecl _strnicmp(const char * _String1, const char * _String2, size_t _MaxCount); 
#line 285
int __cdecl _strnicmp_l(const char * _String1, const char * _String2, size_t _MaxCount, _locale_t _Locale); 
#line 293
int __cdecl _strnicoll(const char * _String1, const char * _String2, size_t _MaxCount); 
#line 300
int __cdecl _strnicoll_l(const char * _String1, const char * _String2, size_t _MaxCount, _locale_t _Locale); 
#line 308
int __cdecl _strncoll(const char * _String1, const char * _String2, size_t _MaxCount); 
#line 315
int __cdecl _strncoll_l(const char * _String1, const char * _String2, size_t _MaxCount, _locale_t _Locale); 
#line 322
size_t __cdecl __strncnt(const char * _String, size_t _Count); 
#line 327
extern "C++" {template < size_t _Size > inline errno_t __cdecl strncpy_s ( char ( & _Destination ) [ _Size ], char const * _Source, size_t _Count ) throw ( ) { return strncpy_s ( _Destination, _Size, _Source, _Count ); }}
#line 334 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl strncpy(char * _Destination, const char * _Source, size_t _Count); 
#line 351 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
size_t __cdecl strnlen(const char * _String, size_t _MaxCount); 
#line 367 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
__inline size_t __cdecl strnlen_s(const char *
#line 368
_String, size_t 
#line 369
_MaxCount) 
#line 371
{ 
#line 372
return (_String == (0)) ? 0 : strnlen(_String, _MaxCount); 
#line 373
} 
#line 378 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
errno_t __cdecl _strnset_s(char * _String, size_t _SizeInBytes, int _Value, size_t _MaxCount); 
#line 385
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strnset_s ( char ( & _Destination ) [ _Size ], int _Value, size_t _Count ) throw ( ) { return _strnset_s ( _Destination, _Size, _Value, _Count ); }}
#line 392 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strnset(char * _Destination, int _Value, size_t _Count); 
#line 401 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
const char *__cdecl strpbrk(const char * _Str, const char * _Control); 
#line 406
char *__cdecl _strrev(char * _Str); 
#line 411
errno_t __cdecl _strset_s(char * _Destination, size_t _DestinationSize, int _Value); 
#line 417
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strset_s ( char ( & _Destination ) [ _Size ], int _Value ) throw ( ) { return _strset_s ( _Destination, _Size, _Value ); }}
#line 423 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strset(char * _Destination, int _Value); 
#line 430 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
size_t __cdecl strspn(const char * _Str, const char * _Control); 
#line 436
char *__cdecl strtok(char * _String, const char * _Delimiter); 
#line 442
errno_t __cdecl _strupr_s(char * _String, size_t _Size); 
#line 447
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strupr_s ( char ( & _String ) [ _Size ] ) throw ( ) { return _strupr_s ( _String, _Size ); }}
#line 452 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strupr(char * _String); 
#line 458 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
errno_t __cdecl _strupr_s_l(char * _String, size_t _Size, _locale_t _Locale); 
#line 464
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strupr_s_l ( char ( & _String ) [ _Size ], _locale_t _Locale ) throw ( ) { return _strupr_s_l ( _String, _Size, _Locale ); }}
#line 470 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl _strupr_l(char * _String, _locale_t _Locale); 
#line 479 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
size_t __cdecl strxfrm(char * _Destination, const char * _Source, size_t _MaxCount); 
#line 487
size_t __cdecl _strxfrm_l(char * _Destination, const char * _Source, size_t _MaxCount, _locale_t _Locale); 
#line 497
extern "C++" {
#line 500
inline char *__cdecl strchr(char *const _String, const int _Ch) 
#line 501
{ 
#line 502
return const_cast< char *>(strchr(static_cast< const char *>(_String), _Ch)); 
#line 503
} 
#line 506
inline char *__cdecl strpbrk(char *const _String, const char *const _Control) 
#line 507
{ 
#line 508
return const_cast< char *>(strpbrk(static_cast< const char *>(_String), _Control)); 
#line 509
} 
#line 512
inline char *__cdecl strrchr(char *const _String, const int _Ch) 
#line 513
{ 
#line 514
return const_cast< char *>(strrchr(static_cast< const char *>(_String), _Ch)); 
#line 515
} 
#line 518
inline char *__cdecl strstr(char *const _String, const char *const _SubString) 
#line 519
{ 
#line 520
return const_cast< char *>(strstr(static_cast< const char *>(_String), _SubString)); 
#line 521
} 
#line 522
}
#line 532 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
char *__cdecl strdup(const char * _String); 
#line 539
int __cdecl strcmpi(const char * _String1, const char * _String2); 
#line 545
int __cdecl stricmp(const char * _String1, const char * _String2); 
#line 551
char *__cdecl strlwr(char * _String); 
#line 556
int __cdecl strnicmp(const char * _String1, const char * _String2, size_t _MaxCount); 
#line 563
char *__cdecl strnset(char * _String, int _Value, size_t _MaxCount); 
#line 570
char *__cdecl strrev(char * _String); 
#line 575
char *__cdecl strset(char * _String, int _Value); 
#line 580
char *__cdecl strupr(char * _String); 
#line 588 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\string.h"
}__pragma( pack ( pop )) 
#line 590
#pragma warning(pop)
#line 13 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 17
__pragma( pack ( push, 8 )) extern "C" {
#line 26
struct tm { 
#line 28
int tm_sec; 
#line 29
int tm_min; 
#line 30
int tm_hour; 
#line 31
int tm_mday; 
#line 32
int tm_mon; 
#line 33
int tm_year; 
#line 34
int tm_wday; 
#line 35
int tm_yday; 
#line 36
int tm_isdst; 
#line 37
}; 
#line 48
__wchar_t *__cdecl _wasctime(const tm * _Tm); 
#line 54
errno_t __cdecl _wasctime_s(__wchar_t * _Buffer, size_t _SizeInWords, const tm * _Tm); 
#line 60
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wasctime_s ( wchar_t ( & _Buffer ) [ _Size ], struct tm const * _Time ) throw ( ) { return _wasctime_s ( _Buffer, _Size, _Time ); }}
#line 69 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
size_t __cdecl wcsftime(__wchar_t * _Buffer, size_t _SizeInWords, const __wchar_t * _Format, const tm * _Tm); 
#line 78
size_t __cdecl _wcsftime_l(__wchar_t * _Buffer, size_t _SizeInWords, const __wchar_t * _Format, const tm * _Tm, _locale_t _Locale); 
#line 88
__wchar_t *__cdecl _wctime32(const __time32_t * _Time); 
#line 93
errno_t __cdecl _wctime32_s(__wchar_t * _Buffer, size_t _SizeInWords, const __time32_t * _Time); 
#line 99
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wctime32_s ( wchar_t ( & _Buffer ) [ _Size ], __time32_t const * _Time ) throw ( ) { return _wctime32_s ( _Buffer, _Size, _Time ); }}
#line 108 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
__wchar_t *__cdecl _wctime64(const __time64_t * _Time); 
#line 113
errno_t __cdecl _wctime64_s(__wchar_t * _Buffer, size_t _SizeInWords, const __time64_t * _Time); 
#line 118
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wctime64_s ( wchar_t ( & _Buffer ) [ _Size ], __time64_t const * _Time ) throw ( ) { return _wctime64_s ( _Buffer, _Size, _Time ); }}
#line 125 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
errno_t __cdecl _wstrdate_s(__wchar_t * _Buffer, size_t _SizeInWords); 
#line 130
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wstrdate_s ( wchar_t ( & _Buffer ) [ _Size ] ) throw ( ) { return _wstrdate_s ( _Buffer, _Size ); }}
#line 135 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
__wchar_t *__cdecl _wstrdate(__wchar_t * _Buffer); 
#line 141 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
errno_t __cdecl _wstrtime_s(__wchar_t * _Buffer, size_t _SizeInWords); 
#line 146
extern "C++" {template < size_t _Size > inline errno_t __cdecl _wstrtime_s ( wchar_t ( & _Buffer ) [ _Size ] ) throw ( ) { return _wstrtime_s ( _Buffer, _Size ); }}
#line 151 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
__wchar_t *__cdecl _wstrtime(__wchar_t * _Buffer); 
#line 186 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
__inline __wchar_t *__cdecl _wctime(const time_t *const 
#line 187
_Time) 
#line 188
{ 
#line 189
return _wctime64(_Time); 
#line 190
} 
#line 193
__inline errno_t __cdecl _wctime_s(__wchar_t *const 
#line 194
_Buffer, const size_t 
#line 195
_SizeInWords, const time_t *const 
#line 196
_Time) 
#line 198
{ 
#line 199
return _wctime64_s(_Buffer, _SizeInWords, _Time); 
#line 200
} 
#line 205 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_wtime.h"
}__pragma( pack ( pop )) 
#line 207
#pragma warning(pop)
#line 15 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 19
__pragma( pack ( push, 8 )) extern "C" {
#line 30 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
typedef long clock_t; 
#line 32
struct _timespec32 { 
#line 34
__time32_t tv_sec; 
#line 35
long tv_nsec; 
#line 36
}; 
#line 38
struct _timespec64 { 
#line 40
__time64_t tv_sec; 
#line 41
long tv_nsec; 
#line 42
}; 
#line 45
struct timespec { 
#line 47
time_t tv_sec; 
#line 48
long tv_nsec; 
#line 49
}; 
#line 68 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
int *__cdecl __daylight(); 
#line 74
long *__cdecl __dstbias(); 
#line 80
long *__cdecl __timezone(); 
#line 86
char **__cdecl __tzname(); 
#line 91
errno_t __cdecl _get_daylight(int * _Daylight); 
#line 96
errno_t __cdecl _get_dstbias(long * _DaylightSavingsBias); 
#line 101
errno_t __cdecl _get_timezone(long * _TimeZone); 
#line 106
errno_t __cdecl _get_tzname(size_t * _ReturnValue, char * _Buffer, size_t _SizeInBytes, int _Index); 
#line 123
char *__cdecl asctime(const tm * _Tm); 
#line 130
errno_t __cdecl asctime_s(char * _Buffer, size_t _SizeInBytes, const tm * _Tm); 
#line 137 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
extern "C++" {template < size_t _Size > inline errno_t __cdecl asctime_s ( char ( & _Buffer ) [ _Size ], struct tm const * _Time ) throw ( ) { return asctime_s ( _Buffer, _Size, _Time ); }}
#line 144 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
clock_t __cdecl clock(); 
#line 149
char *__cdecl _ctime32(const __time32_t * _Time); 
#line 154
errno_t __cdecl _ctime32_s(char * _Buffer, size_t _SizeInBytes, const __time32_t * _Time); 
#line 160
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ctime32_s ( char ( & _Buffer ) [ _Size ], __time32_t const * _Time ) throw ( ) { return _ctime32_s ( _Buffer, _Size, _Time ); }}
#line 169 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
char *__cdecl _ctime64(const __time64_t * _Time); 
#line 174
errno_t __cdecl _ctime64_s(char * _Buffer, size_t _SizeInBytes, const __time64_t * _Time); 
#line 180
extern "C++" {template < size_t _Size > inline errno_t __cdecl _ctime64_s ( char ( & _Buffer ) [ _Size ], __time64_t const * _Time ) throw ( ) { return _ctime64_s ( _Buffer, _Size, _Time ); }}
#line 187 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
double __cdecl _difftime32(__time32_t _Time1, __time32_t _Time2); 
#line 193
double __cdecl _difftime64(__time64_t _Time1, __time64_t _Time2); 
#line 200
tm *__cdecl _gmtime32(const __time32_t * _Time); 
#line 205
errno_t __cdecl _gmtime32_s(tm * _Tm, const __time32_t * _Time); 
#line 212
tm *__cdecl _gmtime64(const __time64_t * _Time); 
#line 217
errno_t __cdecl _gmtime64_s(tm * _Tm, const __time64_t * _Time); 
#line 224
tm *__cdecl _localtime32(const __time32_t * _Time); 
#line 229
errno_t __cdecl _localtime32_s(tm * _Tm, const __time32_t * _Time); 
#line 236
tm *__cdecl _localtime64(const __time64_t * _Time); 
#line 241
errno_t __cdecl _localtime64_s(tm * _Tm, const __time64_t * _Time); 
#line 247
__time32_t __cdecl _mkgmtime32(tm * _Tm); 
#line 252
__time64_t __cdecl _mkgmtime64(tm * _Tm); 
#line 257
__time32_t __cdecl _mktime32(tm * _Tm); 
#line 262
__time64_t __cdecl _mktime64(tm * _Tm); 
#line 268
size_t __cdecl strftime(char * _Buffer, size_t _SizeInBytes, const char * _Format, const tm * _Tm); 
#line 277
size_t __cdecl _strftime_l(char * _Buffer, size_t _MaxSize, const char * _Format, const tm * _Tm, _locale_t _Locale); 
#line 286
errno_t __cdecl _strdate_s(char * _Buffer, size_t _SizeInBytes); 
#line 291
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strdate_s ( char ( & _Buffer ) [ _Size ] ) throw ( ) { return _strdate_s ( _Buffer, _Size ); }}
#line 296 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
char *__cdecl _strdate(char * _Buffer); 
#line 302 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
errno_t __cdecl _strtime_s(char * _Buffer, size_t _SizeInBytes); 
#line 307
extern "C++" {template < size_t _Size > inline errno_t __cdecl _strtime_s ( char ( & _Buffer ) [ _Size ] ) throw ( ) { return _strtime_s ( _Buffer, _Size ); }}
#line 312 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
char *__cdecl _strtime(char * _Buffer); 
#line 317 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
__time32_t __cdecl _time32(__time32_t * _Time); 
#line 321
__time64_t __cdecl _time64(__time64_t * _Time); 
#line 327
int __cdecl _timespec32_get(_timespec32 * _Ts, int _Base); 
#line 334
int __cdecl _timespec64_get(_timespec64 * _Ts, int _Base); 
#line 348
void __cdecl _tzset(); 
#line 351
__declspec(deprecated("This function or variable has been superceded by newer library or operating system functionality. Consider using GetLocalTime in" "stead. See online help for details.")) unsigned __cdecl 
#line 352
_getsystime(tm * _Tm); 
#line 356
__declspec(deprecated("This function or variable has been superceded by newer library or operating system functionality. Consider using SetLocalTime in" "stead. See online help for details.")) unsigned __cdecl 
#line 357
_setsystime(tm * _Tm, unsigned _Milliseconds); 
#line 501 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
__inline char *__cdecl ctime(const time_t *const 
#line 502
_Time) 
#line 504
{ 
#line 505
return _ctime64(_Time); 
#line 506
} 
#line 509
__inline double __cdecl difftime(const time_t 
#line 510
_Time1, const time_t 
#line 511
_Time2) 
#line 513
{ 
#line 514
return _difftime64(_Time1, _Time2); 
#line 515
} 
#line 518
__inline tm *__cdecl gmtime(const time_t *const 
#line 519
_Time) 
#line 520
{ 
#line 521
return _gmtime64(_Time); 
#line 522
} 
#line 525
__inline tm *__cdecl localtime(const time_t *const 
#line 526
_Time) 
#line 528
{ 
#line 529
return _localtime64(_Time); 
#line 530
} 
#line 533
__inline time_t __cdecl _mkgmtime(tm *const 
#line 534
_Tm) 
#line 536
{ 
#line 537
return _mkgmtime64(_Tm); 
#line 538
} 
#line 541
__inline time_t __cdecl mktime(tm *const 
#line 542
_Tm) 
#line 544
{ 
#line 545
return _mktime64(_Tm); 
#line 546
} 
#line 548
__inline time_t __cdecl time(time_t *const 
#line 549
_Time) 
#line 551
{ 
#line 552
return _time64(_Time); 
#line 553
} 
#line 556
__inline int __cdecl timespec_get(timespec *const 
#line 557
_Ts, const int 
#line 558
_Base) 
#line 560
{ 
#line 561
return _timespec64_get((_timespec64 *)_Ts, _Base); 
#line 562
} 
#line 566
__inline errno_t __cdecl ctime_s(char *const 
#line 567
_Buffer, const size_t 
#line 568
_SizeInBytes, const time_t *const 
#line 569
_Time) 
#line 571
{ 
#line 572
return _ctime64_s(_Buffer, _SizeInBytes, _Time); 
#line 573
} 
#line 603 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
__inline errno_t __cdecl gmtime_s(tm *const 
#line 604
_Tm, const time_t *const 
#line 605
_Time) 
#line 607
{ 
#line 608
return _gmtime64_s(_Tm, _Time); 
#line 609
} 
#line 612
__inline errno_t __cdecl localtime_s(tm *const 
#line 613
_Tm, const time_t *const 
#line 614
_Time) 
#line 616
{ 
#line 617
return _localtime64_s(_Tm, _Time); 
#line 618
} 
#line 638 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
void __cdecl tzset(); 
#line 645 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\time.h"
}__pragma( pack ( pop )) 
#line 647
#pragma warning(pop)
#line 88 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/common_functions.h"
extern "C" {
#line 91 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/common_functions.h"
extern clock_t __cdecl clock(); 
#line 96 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/common_functions.h"
extern void *__cdecl memset(void *, int, size_t); 
#line 97
extern void *__cdecl memcpy(void *, const void *, size_t); 
#line 99
}
#line 167 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern "C" {
#line 274 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __cdecl abs(int a); 
#line 285
extern long __cdecl labs(long a); 
#line 296
extern __int64 llabs(__int64 a); 
#line 324 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl fabs(double x); 
#line 347 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern __inline float fabsf(float x); 
#line 358 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline int min(const int a, const int b); 
#line 365
extern inline unsigned umin(const unsigned a, const unsigned b); 
#line 372
extern inline __int64 llmin(const __int64 a, const __int64 b); 
#line 379
extern inline unsigned __int64 ullmin(const unsigned __int64 a, const unsigned __int64 b); 
#line 402 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl fminf(float x, float y); 
#line 422 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl fmin(double x, double y); 
#line 433 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline int max(const int a, const int b); 
#line 441
extern inline unsigned umax(const unsigned a, const unsigned b); 
#line 448
extern inline __int64 llmax(const __int64 a, const __int64 b); 
#line 455
extern inline unsigned __int64 ullmax(const unsigned __int64 a, const unsigned __int64 b); 
#line 478 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl fmaxf(float x, float y); 
#line 498 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl fmax(double, double); 
#line 518 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl sin(double x); 
#line 536
extern double __cdecl cos(double x); 
#line 552 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern void sincos(double x, double * sptr, double * cptr); 
#line 565
extern void sincosf(float x, float * sptr, float * cptr); 
#line 588 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl tan(double x); 
#line 612
extern double __cdecl sqrt(double x); 
#line 639 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double rsqrt(double x); 
#line 663
extern float rsqrtf(float x); 
#line 692 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl log2(double x); 
#line 721 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl exp2(double x); 
#line 750 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl exp2f(float x); 
#line 779 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double exp10(double x); 
#line 806
extern float exp10f(float x); 
#line 842 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl expm1(double x); 
#line 875 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl expm1f(float x); 
#line 902 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl log2f(float x); 
#line 925 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl log10(double x); 
#line 951
extern double __cdecl log(double x); 
#line 980 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl log1p(double x); 
#line 1010 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl log1pf(float x); 
#line 1034 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl floor(double x); 
#line 1063
extern double __cdecl exp(double x); 
#line 1082
extern double __cdecl cosh(double x); 
#line 1102
extern double __cdecl sinh(double x); 
#line 1122
extern double __cdecl tanh(double x); 
#line 1148 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl acosh(double x); 
#line 1175 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl acoshf(float x); 
#line 1199 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl asinh(double x); 
#line 1223 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl asinhf(float x); 
#line 1248 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl atanh(double x); 
#line 1273 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl atanhf(float x); 
#line 1289 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl ldexp(double x, int exp); 
#line 1304
extern __inline float ldexpf(float x, int exp); 
#line 1327 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl logb(double x); 
#line 1351 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl logbf(float x); 
#line 1375 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __cdecl ilogb(double x); 
#line 1399 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __cdecl ilogbf(float x); 
#line 1427 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl scalbn(double x, int n); 
#line 1455 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl scalbnf(float x, int n); 
#line 1483 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl scalbln(double x, long n); 
#line 1511 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl scalblnf(float x, long n); 
#line 1541 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl frexp(double x, int * nptr); 
#line 1570
extern __inline float frexpf(float x, int * nptr); 
#line 1595 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl round(double x); 
#line 1621 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl roundf(float x); 
#line 1639 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern long __cdecl lround(double x); 
#line 1657 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern long __cdecl lroundf(float x); 
#line 1675 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern __int64 __cdecl llround(double x); 
#line 1693 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern __int64 __cdecl llroundf(float x); 
#line 1763 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl rintf(float x); 
#line 1780 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern long __cdecl lrint(double x); 
#line 1797 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern long __cdecl lrintf(float x); 
#line 1814 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern __int64 __cdecl llrint(double x); 
#line 1831 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern __int64 __cdecl llrintf(float x); 
#line 1855 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl nearbyint(double x); 
#line 1879 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl nearbyintf(float x); 
#line 1901 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl ceil(double x); 
#line 1926 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl trunc(double x); 
#line 1952 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl truncf(float x); 
#line 1974 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl fdim(double x, double y); 
#line 1995 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl fdimf(float x, float y); 
#line 2076 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl atan2(double y, double x); 
#line 2102
extern double __cdecl atan(double x); 
#line 2119
extern double __cdecl acos(double x); 
#line 2141
extern double __cdecl asin(double x); 
#line 2169 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl hypot(double x, double y); 
#line 2227 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline float __cdecl hypotf(float x, float y); 
#line 2503 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl cbrt(double x); 
#line 2530 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl cbrtf(float x); 
#line 2554 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double rcbrt(double x); 
#line 2575
extern float rcbrtf(float x); 
#line 2604 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double sinpi(double x); 
#line 2627
extern float sinpif(float x); 
#line 2649
extern double cospi(double x); 
#line 2671
extern float cospif(float x); 
#line 2686
extern void sincospi(double x, double * sptr, double * cptr); 
#line 2699
extern void sincospif(float x, float * sptr, float * cptr); 
#line 2785 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl pow(double x, double y); 
#line 2809
extern double __cdecl modf(double x, double * iptr); 
#line 2836
extern double __cdecl fmod(double x, double y); 
#line 2868 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl remainder(double x, double y); 
#line 2901 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl remainderf(float x, float y); 
#line 2939 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl remquo(double x, double y, int * quo); 
#line 2977 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl remquof(float x, float y, int * quo); 
#line 2996 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl j0(double x); 
#line 3018 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float j0f(float x); 
#line 3045 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl j1(double x); 
#line 3072 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float j1f(float x); 
#line 3095 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl jn(int n, double x); 
#line 3118 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float jnf(int n, float x); 
#line 3145 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl y0(double x); 
#line 3172 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float y0f(float x); 
#line 3199 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl y1(double x); 
#line 3226 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float y1f(float x); 
#line 3254 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl yn(int n, double x); 
#line 3282 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float ynf(int n, float x); 
#line 3380 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl erf(double x); 
#line 3405 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl erff(float x); 
#line 3433 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double erfinv(double x); 
#line 3456
extern float erfinvf(float x); 
#line 3482 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl erfc(double x); 
#line 3505 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl erfcf(float x); 
#line 3537 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl lgamma(double x); 
#line 3563 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double erfcinv(double x); 
#line 3584
extern float erfcinvf(float x); 
#line 3606
extern double normcdfinv(double x); 
#line 3628
extern float normcdfinvf(float x); 
#line 3647
extern double normcdf(double x); 
#line 3666
extern float normcdff(float x); 
#line 3686
extern double erfcx(double x); 
#line 3706
extern float erfcxf(float x); 
#line 3741 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl lgammaf(float x); 
#line 3770 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl tgamma(double x); 
#line 3799 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl tgammaf(float x); 
#line 3813 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl copysign(double x, double y); 
#line 3827 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl copysignf(float x, float y); 
#line 3846 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl nextafter(double x, double y); 
#line 3865 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl nextafterf(float x, float y); 
#line 3881 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl nan(const char * tagp); 
#line 3897 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl nanf(const char * tagp); 
#line 3902 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __isinff(float); 
#line 3903
extern int __isnanf(float); 
#line 3913 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __finite(double); 
#line 3914
extern int __finitef(float); 
#line 3915
extern int __signbit(double); 
#line 3916
extern int __isnan(double); 
#line 3917
extern int __isinf(double); 
#line 3920 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __signbitf(float); 
#line 3973 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern double __cdecl fma(double x, double y, double z); 
#line 4023 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl fmaf(float x, float y, float z); 
#line 4032 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __signbitl(long double); 
#line 4038 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern int __finitel(long double); 
#line 4039
extern int __isinfl(long double); 
#line 4040
extern int __isnanl(long double); 
#line 4044 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern float __cdecl acosf(float); 
#line 4045
extern float __cdecl asinf(float); 
#line 4046
extern float __cdecl atanf(float); 
#line 4047
extern float __cdecl atan2f(float, float); 
#line 4048
extern float __cdecl cosf(float); 
#line 4049
extern float __cdecl sinf(float); 
#line 4050
extern float __cdecl tanf(float); 
#line 4051
extern float __cdecl coshf(float); 
#line 4052
extern float __cdecl sinhf(float); 
#line 4053
extern float __cdecl tanhf(float); 
#line 4054
extern float __cdecl expf(float); 
#line 4055
extern float __cdecl logf(float); 
#line 4056
extern float __cdecl log10f(float); 
#line 4057
extern float __cdecl modff(float, float *); 
#line 4058
extern float __cdecl powf(float, float); 
#line 4059
extern float __cdecl sqrtf(float); 
#line 4060
extern float __cdecl ceilf(float); 
#line 4061
extern float __cdecl floorf(float); 
#line 4062
extern float __cdecl fmodf(float, float); 
#line 4624 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
}
#line 14 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 18
__pragma( pack ( push, 8 )) extern "C" {
#line 23
struct _exception { 
#line 25
int type; 
#line 26
char *name; 
#line 27
double arg1; 
#line 28
double arg2; 
#line 29
double retval; 
#line 30
}; 
#line 37
struct _complex { 
#line 39
double x, y; 
#line 40
}; 
#line 59 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
typedef float float_t; 
#line 60
typedef double double_t; 
#line 78 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
extern const double _HUGE; 
#line 189 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
void __cdecl _fperrraise(int _Except); 
#line 191
short __cdecl _dclass(double _X); 
#line 192
short __cdecl _ldclass(long double _X); 
#line 193
short __cdecl _fdclass(float _X); 
#line 195
int __cdecl _dsign(double _X); 
#line 196
int __cdecl _ldsign(long double _X); 
#line 197
int __cdecl _fdsign(float _X); 
#line 199
int __cdecl _dpcomp(double _X, double _Y); 
#line 200
int __cdecl _ldpcomp(long double _X, long double _Y); 
#line 201
int __cdecl _fdpcomp(float _X, float _Y); 
#line 203
short __cdecl _dtest(double * _Px); 
#line 204
short __cdecl _ldtest(long double * _Px); 
#line 205
short __cdecl _fdtest(float * _Px); 
#line 207
short __cdecl _d_int(double * _Px, short _Xexp); 
#line 208
short __cdecl _ld_int(long double * _Px, short _Xexp); 
#line 209
short __cdecl _fd_int(float * _Px, short _Xexp); 
#line 211
short __cdecl _dscale(double * _Px, long _Lexp); 
#line 212
short __cdecl _ldscale(long double * _Px, long _Lexp); 
#line 213
short __cdecl _fdscale(float * _Px, long _Lexp); 
#line 215
short __cdecl _dunscale(short * _Pex, double * _Px); 
#line 216
short __cdecl _ldunscale(short * _Pex, long double * _Px); 
#line 217
short __cdecl _fdunscale(short * _Pex, float * _Px); 
#line 219
short __cdecl _dexp(double * _Px, double _Y, long _Eoff); 
#line 220
short __cdecl _ldexp(long double * _Px, long double _Y, long _Eoff); 
#line 221
short __cdecl _fdexp(float * _Px, float _Y, long _Eoff); 
#line 223
short __cdecl _dnorm(unsigned short * _Ps); 
#line 224
short __cdecl _fdnorm(unsigned short * _Ps); 
#line 226
double __cdecl _dpoly(double _X, const double * _Tab, int _N); 
#line 227
long double __cdecl _ldpoly(long double _X, const long double * _Tab, int _N); 
#line 228
float __cdecl _fdpoly(float _X, const float * _Tab, int _N); 
#line 230
double __cdecl _dlog(double _X, int _Baseflag); 
#line 231
long double __cdecl _ldlog(long double _X, int _Baseflag); 
#line 232
float __cdecl _fdlog(float _X, int _Baseflag); 
#line 234
double __cdecl _dsin(double _X, unsigned _Qoff); 
#line 235
long double __cdecl _ldsin(long double _X, unsigned _Qoff); 
#line 236
float __cdecl _fdsin(float _X, unsigned _Qoff); 
#line 243
typedef 
#line 240
union { 
#line 241
unsigned short _Sh[4]; 
#line 242
double _Val; 
#line 243
} _double_val; 
#line 250
typedef 
#line 247
union { 
#line 248
unsigned short _Sh[2]; 
#line 249
float _Val; 
#line 250
} _float_val; 
#line 257
typedef 
#line 254
union { 
#line 255
unsigned short _Sh[4]; 
#line 256
long double _Val; 
#line 257
} _ldouble_val; 
#line 265
typedef 
#line 260
union { 
#line 261
unsigned short _Word[4]; 
#line 262
float _Float; 
#line 263
double _Double; 
#line 264
long double _Long_double; 
#line 265
} _float_const; 
#line 267
extern const _float_const _Denorm_C, _Inf_C, _Nan_C, _Snan_C, _Hugeval_C; 
#line 268
extern const _float_const _FDenorm_C, _FInf_C, _FNan_C, _FSnan_C; 
#line 269
extern const _float_const _LDenorm_C, _LInf_C, _LNan_C, _LSnan_C; 
#line 271
extern const _float_const _Eps_C, _Rteps_C; 
#line 272
extern const _float_const _FEps_C, _FRteps_C; 
#line 273
extern const _float_const _LEps_C, _LRteps_C; 
#line 275
extern const double _Zero_C, _Xbig_C; 
#line 276
extern const float _FZero_C, _FXbig_C; 
#line 277
extern const long double _LZero_C, _LXbig_C; 
#line 310
extern "C++" {
#line 312
inline int fpclassify(float _X) throw() 
#line 313
{ 
#line 317 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
return _fdtest(&_X); 
#line 319 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
} 
#line 321
inline int fpclassify(double _X) throw() 
#line 322
{ 
#line 326 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
return _dtest(&_X); 
#line 328 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
} 
#line 330
inline int fpclassify(long double _X) throw() 
#line 331
{ 
#line 335 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
return _ldtest(&_X); 
#line 337 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
} 
#line 339
inline bool signbit(float _X) throw() 
#line 340
{ 
#line 341
return _fdsign(_X) != 0; 
#line 342
} 
#line 344
inline bool signbit(double _X) throw() 
#line 345
{ 
#line 346
return _dsign(_X) != 0; 
#line 347
} 
#line 349
inline bool signbit(long double _X) throw() 
#line 350
{ 
#line 351
return _ldsign(_X) != 0; 
#line 352
} 
#line 354
inline int _fpcomp(float _X, float _Y) throw() 
#line 355
{ 
#line 356
return _fdpcomp(_X, _Y); 
#line 357
} 
#line 359
inline int _fpcomp(double _X, double _Y) throw() 
#line 360
{ 
#line 361
return _dpcomp(_X, _Y); 
#line 362
} 
#line 364
inline int _fpcomp(long double _X, long double _Y) throw() 
#line 365
{ 
#line 366
return _ldpcomp(_X, _Y); 
#line 367
} 
#line 369
template< class _Trc, class _Tre> struct _Combined_type { 
#line 371
typedef float _Type; 
#line 372
}; 
#line 374
template<> struct _Combined_type< float, double>  { 
#line 376
typedef double _Type; 
#line 377
}; 
#line 379
template<> struct _Combined_type< float, long double>  { 
#line 381
typedef long double _Type; 
#line 382
}; 
#line 384
template< class _Ty, class _T2> struct _Real_widened { 
#line 386
typedef long double _Type; 
#line 387
}; 
#line 389
template<> struct _Real_widened< float, float>  { 
#line 391
typedef float _Type; 
#line 392
}; 
#line 394
template<> struct _Real_widened< float, double>  { 
#line 396
typedef double _Type; 
#line 397
}; 
#line 399
template<> struct _Real_widened< double, float>  { 
#line 401
typedef double _Type; 
#line 402
}; 
#line 404
template<> struct _Real_widened< double, double>  { 
#line 406
typedef double _Type; 
#line 407
}; 
#line 409
template< class _Ty> struct _Real_type { 
#line 411
typedef double _Type; 
#line 412
}; 
#line 414
template<> struct _Real_type< float>  { 
#line 416
typedef float _Type; 
#line 417
}; 
#line 419
template<> struct _Real_type< long double>  { 
#line 421
typedef long double _Type; 
#line 422
}; 
#line 424
template < class _T1, class _T2 >
      inline int _fpcomp ( _T1 _X, _T2 _Y ) throw ( )
    {
        typedef typename _Combined_type < float,
            typename _Real_widened <
            typename _Real_type < _T1 > :: _Type,
            typename _Real_type < _T2 > :: _Type > :: _Type > :: _Type _Tw;
        return _fpcomp ( ( _Tw ) _X, ( _Tw ) _Y );
    }
#line 434
template < class _Ty >
      inline bool isfinite ( _Ty _X ) throw ( )
    {
        return fpclassify ( _X ) <= 0;
    }
#line 440
template < class _Ty >
      inline bool isinf ( _Ty _X ) throw ( )
    {
        return fpclassify ( _X ) == 1;
    }
#line 446
template < class _Ty >
      inline bool isnan ( _Ty _X ) throw ( )
    {
        return fpclassify ( _X ) == 2;
    }
#line 452
template < class _Ty >
      inline bool isnormal ( _Ty _X ) throw ( )
    {
        return fpclassify ( _X ) == ( - 1 );
    }
#line 458
template < class _Ty1, class _Ty2 >
      inline bool isgreater ( _Ty1 _X, _Ty2 _Y ) throw ( )
    {
        return ( _fpcomp ( _X, _Y ) & 4 ) != 0;
    }
#line 464
template < class _Ty1, class _Ty2 >
      inline bool isgreaterequal ( _Ty1 _X, _Ty2 _Y ) throw ( )
    {
        return ( _fpcomp ( _X, _Y ) & ( 2 | 4 ) ) != 0;
    }
#line 470
template < class _Ty1, class _Ty2 >
      inline bool isless ( _Ty1 _X, _Ty2 _Y ) throw ( )
    {
        return ( _fpcomp ( _X, _Y ) & 1 ) != 0;
    }
#line 476
template < class _Ty1, class _Ty2 >
      inline bool islessequal ( _Ty1 _X, _Ty2 _Y ) throw ( )
    {
        return ( _fpcomp ( _X, _Y ) & ( 1 | 2 ) ) != 0;
    }
#line 482
template < class _Ty1, class _Ty2 >
      inline bool islessgreater ( _Ty1 _X, _Ty2 _Y ) throw ( )
    {
        return ( _fpcomp ( _X, _Y ) & ( 1 | 4 ) ) != 0;
    }
#line 488
template < class _Ty1, class _Ty2 >
      inline bool isunordered ( _Ty1 _X, _Ty2 _Y ) throw ( )
    {
        return _fpcomp ( _X, _Y ) == 0;
    }
#line 493
}
#line 500 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
int __cdecl abs(int _X); 
#line 501
long __cdecl labs(long _X); 
#line 502
__int64 __cdecl llabs(__int64 _X); 
#line 504
double __cdecl acos(double _X); 
#line 505
double __cdecl asin(double _X); 
#line 506
double __cdecl atan(double _X); 
#line 507
double __cdecl atan2(double _Y, double _X); 
#line 509
double __cdecl cos(double _X); 
#line 510
double __cdecl cosh(double _X); 
#line 511
double __cdecl exp(double _X); 
#line 512
double __cdecl fabs(double _X); 
#line 513
double __cdecl fmod(double _X, double _Y); 
#line 514
double __cdecl log(double _X); 
#line 515
double __cdecl log10(double _X); 
#line 516
double __cdecl pow(double _X, double _Y); 
#line 517
double __cdecl sin(double _X); 
#line 518
double __cdecl sinh(double _X); 
#line 519
double __cdecl sqrt(double _X); 
#line 520
double __cdecl tan(double _X); 
#line 521
double __cdecl tanh(double _X); 
#line 523
double __cdecl acosh(double _X); 
#line 524
double __cdecl asinh(double _X); 
#line 525
double __cdecl atanh(double _X); 
#line 526
double __cdecl atof(const char * _String); 
#line 527
double __cdecl _atof_l(const char * _String, _locale_t _Locale); 
#line 528
double __cdecl _cabs(_complex _Complex_value); 
#line 529
double __cdecl cbrt(double _X); 
#line 530
double __cdecl ceil(double _X); 
#line 531
double __cdecl _chgsign(double _X); 
#line 532
double __cdecl copysign(double _Number, double _Sign); 
#line 533
double __cdecl _copysign(double _Number, double _Sign); 
#line 534
double __cdecl erf(double _X); 
#line 535
double __cdecl erfc(double _X); 
#line 536
double __cdecl exp2(double _X); 
#line 537
double __cdecl expm1(double _X); 
#line 538
double __cdecl fdim(double _X, double _Y); 
#line 539
double __cdecl floor(double _X); 
#line 540
double __cdecl fma(double _X, double _Y, double _Z); 
#line 541
double __cdecl fmax(double _X, double _Y); 
#line 542
double __cdecl fmin(double _X, double _Y); 
#line 543
double __cdecl frexp(double _X, int * _Y); 
#line 544
double __cdecl hypot(double _X, double _Y); 
#line 545
double __cdecl _hypot(double _X, double _Y); 
#line 546
int __cdecl ilogb(double _X); 
#line 547
double __cdecl ldexp(double _X, int _Y); 
#line 548
double __cdecl lgamma(double _X); 
#line 549
__int64 __cdecl llrint(double _X); 
#line 550
__int64 __cdecl llround(double _X); 
#line 551
double __cdecl log1p(double _X); 
#line 552
double __cdecl log2(double _X); 
#line 553
double __cdecl logb(double _X); 
#line 554
long __cdecl lrint(double _X); 
#line 555
long __cdecl lround(double _X); 
#line 557
int __cdecl _matherr(_exception * _Except); 
#line 559
double __cdecl modf(double _X, double * _Y); 
#line 560
double __cdecl nan(const char * _X); 
#line 561
double __cdecl nearbyint(double _X); 
#line 562
double __cdecl nextafter(double _X, double _Y); 
#line 563
double __cdecl nexttoward(double _X, long double _Y); 
#line 564
double __cdecl remainder(double _X, double _Y); 
#line 565
double __cdecl remquo(double _X, double _Y, int * _Z); 
#line 566
double __cdecl rint(double _X); 
#line 567
double __cdecl round(double _X); 
#line 568
double __cdecl scalbln(double _X, long _Y); 
#line 569
double __cdecl scalbn(double _X, int _Y); 
#line 570
double __cdecl tgamma(double _X); 
#line 571
double __cdecl trunc(double _X); 
#line 572
double __cdecl _j0(double _X); 
#line 573
double __cdecl _j1(double _X); 
#line 574
double __cdecl _jn(int _X, double _Y); 
#line 575
double __cdecl _y0(double _X); 
#line 576
double __cdecl _y1(double _X); 
#line 577
double __cdecl _yn(int _X, double _Y); 
#line 579
float __cdecl acoshf(float _X); 
#line 580
float __cdecl asinhf(float _X); 
#line 581
float __cdecl atanhf(float _X); 
#line 582
float __cdecl cbrtf(float _X); 
#line 583
float __cdecl _chgsignf(float _X); 
#line 584
float __cdecl copysignf(float _Number, float _Sign); 
#line 585
float __cdecl _copysignf(float _Number, float _Sign); 
#line 586
float __cdecl erff(float _X); 
#line 587
float __cdecl erfcf(float _X); 
#line 588
float __cdecl expm1f(float _X); 
#line 589
float __cdecl exp2f(float _X); 
#line 590
float __cdecl fdimf(float _X, float _Y); 
#line 591
float __cdecl fmaf(float _X, float _Y, float _Z); 
#line 592
float __cdecl fmaxf(float _X, float _Y); 
#line 593
float __cdecl fminf(float _X, float _Y); 
#line 594
float __cdecl _hypotf(float _X, float _Y); 
#line 595
int __cdecl ilogbf(float _X); 
#line 596
float __cdecl lgammaf(float _X); 
#line 597
__int64 __cdecl llrintf(float _X); 
#line 598
__int64 __cdecl llroundf(float _X); 
#line 599
float __cdecl log1pf(float _X); 
#line 600
float __cdecl log2f(float _X); 
#line 601
float __cdecl logbf(float _X); 
#line 602
long __cdecl lrintf(float _X); 
#line 603
long __cdecl lroundf(float _X); 
#line 604
float __cdecl nanf(const char * _X); 
#line 605
float __cdecl nearbyintf(float _X); 
#line 606
float __cdecl nextafterf(float _X, float _Y); 
#line 607
float __cdecl nexttowardf(float _X, long double _Y); 
#line 608
float __cdecl remainderf(float _X, float _Y); 
#line 609
float __cdecl remquof(float _X, float _Y, int * _Z); 
#line 610
float __cdecl rintf(float _X); 
#line 611
float __cdecl roundf(float _X); 
#line 612
float __cdecl scalblnf(float _X, long _Y); 
#line 613
float __cdecl scalbnf(float _X, int _Y); 
#line 614
float __cdecl tgammaf(float _X); 
#line 615
float __cdecl truncf(float _X); 
#line 625 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
float __cdecl _logbf(float _X); 
#line 626
float __cdecl _nextafterf(float _X, float _Y); 
#line 627
int __cdecl _finitef(float _X); 
#line 628
int __cdecl _isnanf(float _X); 
#line 629
int __cdecl _fpclassf(float _X); 
#line 631
int __cdecl _set_FMA3_enable(int _Flag); 
#line 632
int __cdecl _get_FMA3_enable(); 
#line 645 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
float __cdecl acosf(float _X); 
#line 646
float __cdecl asinf(float _X); 
#line 647
float __cdecl atan2f(float _Y, float _X); 
#line 648
float __cdecl atanf(float _X); 
#line 649
float __cdecl ceilf(float _X); 
#line 650
float __cdecl cosf(float _X); 
#line 651
float __cdecl coshf(float _X); 
#line 652
float __cdecl expf(float _X); 
#line 709 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
__inline float __cdecl fabsf(float _X) 
#line 710
{ 
#line 711
return (float)fabs(_X); 
#line 712
} 
#line 718 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
float __cdecl floorf(float _X); 
#line 719
float __cdecl fmodf(float _X, float _Y); 
#line 735 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
__inline float __cdecl frexpf(float _X, int *_Y) 
#line 736
{ 
#line 737
return (float)frexp(_X, _Y); 
#line 738
} 
#line 740
__inline float __cdecl hypotf(float _X, float _Y) 
#line 741
{ 
#line 742
return _hypotf(_X, _Y); 
#line 743
} 
#line 745
__inline float __cdecl ldexpf(float _X, int _Y) 
#line 746
{ 
#line 747
return (float)ldexp(_X, _Y); 
#line 748
} 
#line 752
float __cdecl log10f(float _X); 
#line 753
float __cdecl logf(float _X); 
#line 754
float __cdecl modff(float _X, float * _Y); 
#line 755
float __cdecl powf(float _X, float _Y); 
#line 756
float __cdecl sinf(float _X); 
#line 757
float __cdecl sinhf(float _X); 
#line 758
float __cdecl sqrtf(float _X); 
#line 759
float __cdecl tanf(float _X); 
#line 760
float __cdecl tanhf(float _X); 
#line 814 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
long double __cdecl acoshl(long double _X); 
#line 816
__inline long double __cdecl acosl(long double _X) 
#line 817
{ 
#line 818
return acos((double)_X); 
#line 819
} 
#line 821
long double __cdecl asinhl(long double _X); 
#line 823
__inline long double __cdecl asinl(long double _X) 
#line 824
{ 
#line 825
return asin((double)_X); 
#line 826
} 
#line 828
__inline long double __cdecl atan2l(long double _Y, long double _X) 
#line 829
{ 
#line 830
return atan2((double)_Y, (double)_X); 
#line 831
} 
#line 833
long double __cdecl atanhl(long double _X); 
#line 835
__inline long double __cdecl atanl(long double _X) 
#line 836
{ 
#line 837
return atan((double)_X); 
#line 838
} 
#line 840
long double __cdecl cbrtl(long double _X); 
#line 842
__inline long double __cdecl ceill(long double _X) 
#line 843
{ 
#line 844
return ceil((double)_X); 
#line 845
} 
#line 847
__inline long double __cdecl _chgsignl(long double _X) 
#line 848
{ 
#line 849
return _chgsign((double)_X); 
#line 850
} 
#line 852
long double __cdecl copysignl(long double _Number, long double _Sign); 
#line 854
__inline long double __cdecl _copysignl(long double _Number, long double _Sign) 
#line 855
{ 
#line 856
return _copysign((double)_Number, (double)_Sign); 
#line 857
} 
#line 859
__inline long double __cdecl coshl(long double _X) 
#line 860
{ 
#line 861
return cosh((double)_X); 
#line 862
} 
#line 864
__inline long double __cdecl cosl(long double _X) 
#line 865
{ 
#line 866
return cos((double)_X); 
#line 867
} 
#line 869
long double __cdecl erfl(long double _X); 
#line 870
long double __cdecl erfcl(long double _X); 
#line 872
__inline long double __cdecl expl(long double _X) 
#line 873
{ 
#line 874
return exp((double)_X); 
#line 875
} 
#line 877
long double __cdecl exp2l(long double _X); 
#line 878
long double __cdecl expm1l(long double _X); 
#line 880
__inline long double __cdecl fabsl(long double _X) 
#line 881
{ 
#line 882
return fabs((double)_X); 
#line 883
} 
#line 885
long double __cdecl fdiml(long double _X, long double _Y); 
#line 887
__inline long double __cdecl floorl(long double _X) 
#line 888
{ 
#line 889
return floor((double)_X); 
#line 890
} 
#line 892
long double __cdecl fmal(long double _X, long double _Y, long double _Z); 
#line 893
long double __cdecl fmaxl(long double _X, long double _Y); 
#line 894
long double __cdecl fminl(long double _X, long double _Y); 
#line 896
__inline long double __cdecl fmodl(long double _X, long double _Y) 
#line 897
{ 
#line 898
return fmod((double)_X, (double)_Y); 
#line 899
} 
#line 901
__inline long double __cdecl frexpl(long double _X, int *_Y) 
#line 902
{ 
#line 903
return frexp((double)_X, _Y); 
#line 904
} 
#line 906
int __cdecl ilogbl(long double _X); 
#line 908
__inline long double __cdecl _hypotl(long double _X, long double _Y) 
#line 909
{ 
#line 910
return _hypot((double)_X, (double)_Y); 
#line 911
} 
#line 913
__inline long double __cdecl hypotl(long double _X, long double _Y) 
#line 914
{ 
#line 915
return _hypot((double)_X, (double)_Y); 
#line 916
} 
#line 918
__inline long double __cdecl ldexpl(long double _X, int _Y) 
#line 919
{ 
#line 920
return ldexp((double)_X, _Y); 
#line 921
} 
#line 923
long double __cdecl lgammal(long double _X); 
#line 924
__int64 __cdecl llrintl(long double _X); 
#line 925
__int64 __cdecl llroundl(long double _X); 
#line 927
__inline long double __cdecl logl(long double _X) 
#line 928
{ 
#line 929
return log((double)_X); 
#line 930
} 
#line 932
__inline long double __cdecl log10l(long double _X) 
#line 933
{ 
#line 934
return log10((double)_X); 
#line 935
} 
#line 937
long double __cdecl log1pl(long double _X); 
#line 938
long double __cdecl log2l(long double _X); 
#line 939
long double __cdecl logbl(long double _X); 
#line 940
long __cdecl lrintl(long double _X); 
#line 941
long __cdecl lroundl(long double _X); 
#line 943
__inline long double __cdecl modfl(long double _X, long double *_Y) 
#line 944
{ 
#line 945
double _F, _I; 
#line 946
_F = modf((double)_X, &_I); 
#line 947
(*_Y) = _I; 
#line 948
return _F; 
#line 949
} 
#line 951
long double __cdecl nanl(const char * _X); 
#line 952
long double __cdecl nearbyintl(long double _X); 
#line 953
long double __cdecl nextafterl(long double _X, long double _Y); 
#line 954
long double __cdecl nexttowardl(long double _X, long double _Y); 
#line 956
__inline long double __cdecl powl(long double _X, long double _Y) 
#line 957
{ 
#line 958
return pow((double)_X, (double)_Y); 
#line 959
} 
#line 961
long double __cdecl remainderl(long double _X, long double _Y); 
#line 962
long double __cdecl remquol(long double _X, long double _Y, int * _Z); 
#line 963
long double __cdecl rintl(long double _X); 
#line 964
long double __cdecl roundl(long double _X); 
#line 965
long double __cdecl scalblnl(long double _X, long _Y); 
#line 966
long double __cdecl scalbnl(long double _X, int _Y); 
#line 968
__inline long double __cdecl sinhl(long double _X) 
#line 969
{ 
#line 970
return sinh((double)_X); 
#line 971
} 
#line 973
__inline long double __cdecl sinl(long double _X) 
#line 974
{ 
#line 975
return sin((double)_X); 
#line 976
} 
#line 978
__inline long double __cdecl sqrtl(long double _X) 
#line 979
{ 
#line 980
return sqrt((double)_X); 
#line 981
} 
#line 983
__inline long double __cdecl tanhl(long double _X) 
#line 984
{ 
#line 985
return tanh((double)_X); 
#line 986
} 
#line 988
__inline long double __cdecl tanl(long double _X) 
#line 989
{ 
#line 990
return tan((double)_X); 
#line 991
} 
#line 993
long double __cdecl tgammal(long double _X); 
#line 994
long double __cdecl truncl(long double _X); 
#line 1015 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
extern double HUGE; 
#line 1020 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
double __cdecl j0(double _X); 
#line 1021
double __cdecl j1(double _X); 
#line 1022
double __cdecl jn(int _X, double _Y); 
#line 1023
double __cdecl y0(double _X); 
#line 1024
double __cdecl y1(double _X); 
#line 1025
double __cdecl yn(int _X, double _Y); 
#line 1030 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\corecrt_math.h"
}__pragma( pack ( pop )) 
#line 1032
#pragma warning(pop)
#line 17 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\__msvc_doom_core.hpp"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 42 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\__msvc_doom_core.hpp"
extern "C" __declspec(noreturn) void __fastfail(unsigned); 
#line 51 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\__msvc_doom_core.hpp"
#pragma warning(pop)
#pragma pack ( pop )
#line 12 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#pragma warning(disable: 4985)
#line 17
extern "C++" {
#line 19
#pragma pack ( push, 8 )
#line 33
namespace std { 
#line 35
struct nothrow_t { 
#line 36
explicit nothrow_t() = default;
#line 37
}; 
#line 39
extern const nothrow_t nothrow; 
#line 40
}
#line 43 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new.h"
[[nodiscard]] __declspec(allocator) void *__cdecl 
#line 44
operator new(size_t _Size); 
#line 48
[[nodiscard]] __declspec(allocator) void *__cdecl 
#line 49
operator new(size_t _Size, const ::std::nothrow_t &) noexcept; 
#line 54
[[nodiscard]] __declspec(allocator) void *__cdecl 
#line 55
operator new[](size_t _Size); 
#line 59
[[nodiscard]] __declspec(allocator) void *__cdecl 
#line 60
operator new[](size_t _Size, const ::std::nothrow_t &) noexcept; 
#line 65
void __cdecl operator delete(void * _Block) noexcept; 
#line 69
void __cdecl operator delete(void * _Block, const ::std::nothrow_t &) noexcept; 
#line 74
void __cdecl operator delete[](void * _Block) noexcept; 
#line 78
void __cdecl operator delete[](void * _Block, const ::std::nothrow_t &) noexcept; 
#line 83
void __cdecl operator delete(void * _Block, size_t _Size) noexcept; 
#line 88
void __cdecl operator delete[](void * _Block, size_t _Size) noexcept; 
#line 156
#pragma warning(push)
#pragma warning(disable: 4577)
#pragma warning(disable: 4514)
#line 161
[[nodiscard]] [[msvc::constexpr]] inline void *__cdecl 
#line 162
operator new(size_t _Size, void *
#line 163
_Where) noexcept 
#line 164
{ 
#line 165
(void)_Size; 
#line 166
return _Where; 
#line 167
} 
#line 169
inline void __cdecl operator delete(void *, void *) noexcept 
#line 170
{ 
#line 172
} 
#line 177 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new.h"
[[nodiscard]] [[msvc::constexpr]] inline void *__cdecl 
#line 178
operator new[](size_t _Size, void *
#line 179
_Where) noexcept 
#line 180
{ 
#line 181
(void)_Size; 
#line 182
return _Where; 
#line 183
} 
#line 185
inline void __cdecl operator delete[](void *, void *) noexcept 
#line 186
{ 
#line 187
} 
#line 195 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new.h"
}
#line 189
#pragma warning(pop)
#line 193
#pragma pack ( pop )
#line 198 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new.h"
#pragma warning(pop)
#line 12 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new_debug.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 16
extern "C++" {
#line 18
#pragma pack ( push, 8 )
#line 25
[[nodiscard]] 
#line 26
__declspec(allocator) void *__cdecl operator new(size_t _Size, int _BlockUse, const char * _FileName, int _LineNumber); 
#line 33
[[nodiscard]] 
#line 34
__declspec(allocator) void *__cdecl operator new[](size_t _Size, int _BlockUse, const char * _FileName, int _LineNumber); 
#line 41
void __cdecl operator delete(void * _Block, int _BlockUse, const char * _FileName, int _LineNumber) noexcept; 
#line 48
void __cdecl operator delete[](void * _Block, int _BlockUse, const char * _FileName, int _LineNumber) noexcept; 
#line 61 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new_debug.h"
}
#line 59
#pragma pack ( pop )
#line 64 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\vcruntime_new_debug.h"
#pragma warning(pop)
#line 15 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\crtdbg.h"
#pragma warning(push)
#pragma warning(disable: 4324 4514 4574 4710 4793 4820 4995 4996 28719 28726 28727 )
#line 19
__pragma( pack ( push, 8 )) extern "C" {
#line 23
typedef void *_HFILE; 
#line 49
typedef int (__cdecl *_CRT_REPORT_HOOK)(int, char *, int *); 
#line 50
typedef int (__cdecl *_CRT_REPORT_HOOKW)(int, __wchar_t *, int *); 
#line 56
typedef int (__cdecl *_CRT_ALLOC_HOOK)(int, void *, size_t, int, long, const unsigned char *, int); 
#line 112
typedef void (__cdecl *_CRT_DUMP_CLIENT)(void *, size_t); 
#line 118
struct _CrtMemBlockHeader; 
#line 127
typedef 
#line 120
struct _CrtMemState { 
#line 122
_CrtMemBlockHeader *pBlockHeader; 
#line 123
size_t lCounts[5]; 
#line 124
size_t lSizes[5]; 
#line 125
size_t lHighWaterCount; 
#line 126
size_t lTotalCount; 
#line 127
} _CrtMemState; 
#line 813 "C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.26100.0\\ucrt\\crtdbg.h"
}__pragma( pack ( pop )) 
#line 815
#pragma warning(pop)
#line 25 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 143 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
#pragma detect_mismatch("_MSC_VER", "1900")
#line 147 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
#pragma detect_mismatch("_ITERATOR_DEBUG_LEVEL", "0")
#line 152 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
#pragma detect_mismatch("RuntimeLibrary", "MT_StaticRelease")
#line 46 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\use_ansi.h"
#pragma comment(lib, "libcpmt")
#line 360 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
namespace std { 
#line 361
enum _Uninitialized { 
#line 362
_Noinit
#line 363
}; 
#line 365
class _Lockit { 
#line 380
public: __thiscall _Lockit() noexcept; 
#line 381
explicit __thiscall _Lockit(int) noexcept; 
#line 382
__thiscall ~_Lockit() noexcept; 
#line 385 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
static void __cdecl _Lockit_ctor(int) noexcept; 
#line 386
static void __cdecl _Lockit_dtor(int) noexcept; 
#line 389
private: static void __cdecl _Lockit_ctor(_Lockit *) noexcept; 
#line 390
static void __cdecl _Lockit_ctor(_Lockit *, int) noexcept; 
#line 391
static void __cdecl _Lockit_dtor(_Lockit *) noexcept; 
#line 394
public: _Lockit(const _Lockit &) = delete;
#line 395
_Lockit &operator=(const _Lockit &) = delete;
#line 398
private: int _Locktype; 
#line 399
}; 
#line 505 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\yvals.h"
}
#line 509
#pragma warning(pop)
#pragma pack ( pop )
#line 14 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cstdlib"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 23
[[nodiscard]] inline double abs(double _Xx) noexcept { 
#line 24
return ::fabs(_Xx); 
#line 25
} 
#line 27
[[nodiscard]] inline float abs(float _Xx) noexcept { 
#line 28
return ::fabsf(_Xx); 
#line 29
} 
#line 31
[[nodiscard]] inline long double abs(long double _Xx) noexcept { 
#line 32
return ::fabsl(_Xx); 
#line 33
} 
#line 36
namespace std { 
#line 37
using ::size_t;
#line 38
using ::div_t;
#line 39
using ::ldiv_t;
#line 40
using ::abort;
#line 41
using ::abs;
#line 42
using ::atexit;
#line 43
using ::atof;
#line 44
using ::atoi;
#line 45
using ::atol;
#line 46
using ::bsearch;
#line 47
using ::calloc;
#line 48
using ::div;
#line 49
using ::exit;
#line 50
using ::free;
#line 51
using ::labs;
#line 52
using ::ldiv;
#line 53
using ::malloc;
#line 54
using ::mblen;
#line 55
using ::mbstowcs;
#line 56
using ::mbtowc;
#line 57
using ::qsort;
#line 58
using ::rand;
#line 59
using ::realloc;
#line 60
using ::srand;
#line 61
using ::strtod;
#line 62
using ::strtol;
#line 63
using ::strtoul;
#line 64
using ::wcstombs;
#line 65
using ::wctomb;
#line 67
using ::lldiv_t;
#line 69
using ::getenv;
#line 70
using ::system;
#line 72
using ::atoll;
#line 73
using ::llabs;
#line 74
using ::lldiv;
#line 75
using ::strtof;
#line 76
using ::strtold;
#line 77
using ::strtoll;
#line 78
using ::strtoull;
#line 80
using ::_Exit;
#line 81
using ::at_quick_exit;
#line 82
using ::quick_exit;
#line 83
}
#line 87
#pragma warning(pop)
#pragma pack ( pop )
#line 11 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\xtr1common"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 26
namespace std { 
#line 27
template < class _Ty, _Ty _Val >
struct [ [ msvc :: no_specializations ( "Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" ) ] ] integral_constant {
    static constexpr _Ty value = _Val;

    using value_type = _Ty;
    using type = integral_constant;

    constexpr operator value_type ( ) const noexcept {
        return value;
    }

    [ [ nodiscard ] ] constexpr value_type operator ( ) ( ) const noexcept {
        return value;
    }
};
#line 43
template< bool _Val> using bool_constant = integral_constant< bool, _Val> ; 
#line 46
using true_type = bool_constant< true> ; 
#line 47
using false_type = bool_constant< false> ; 
#line 49
template< bool _Test, class _Ty = void> 
#line 50
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] enable_if { }; 
#line 52
template< class _Ty> 
#line 53
struct enable_if< true, _Ty>  { 
#line 54
using type = _Ty; 
#line 55
}; 
#line 57
template< bool _Test, class _Ty = void> using enable_if_t = typename enable_if< _Test, _Ty> ::type; 
#line 60
template< bool _Test, class _Ty1, class _Ty2> 
#line 61
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] conditional { 
#line 62
using type = _Ty1; 
#line 63
}; 
#line 65
template< class _Ty1, class _Ty2> 
#line 66
struct conditional< false, _Ty1, _Ty2>  { 
#line 67
using type = _Ty2; 
#line 68
}; 
#line 70
template< bool _Test, class _Ty1, class _Ty2> using conditional_t = typename conditional< _Test, _Ty1, _Ty2> ::type; 
#line 80
template< class , class > 
#line 81
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_same_v = false; 
#line 82
template< class _Ty> constexpr bool 
#line 83
is_same_v< _Ty, _Ty>  = true; 
#line 85
template< class _Ty1, class _Ty2> 
#line 86
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_same : public bool_constant< is_same_v< _Ty1, _Ty2> >  { }; 
#line 89 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\xtr1common"
template< class _Ty> 
#line 90
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_const { 
#line 91
using type = _Ty; 
#line 92
}; 
#line 94
template< class _Ty> 
#line 95
struct remove_const< const _Ty>  { 
#line 96
using type = _Ty; 
#line 97
}; 
#line 99
template< class _Ty> using remove_const_t = typename remove_const< _Ty> ::type; 
#line 102
template< class _Ty> 
#line 103
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_volatile { 
#line 104
using type = _Ty; 
#line 105
}; 
#line 107
template< class _Ty> 
#line 108
struct remove_volatile< volatile _Ty>  { 
#line 109
using type = _Ty; 
#line 110
}; 
#line 112
template< class _Ty> using remove_volatile_t = typename remove_volatile< _Ty> ::type; 
#line 115
template< class _Ty> 
#line 116
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_cv { 
#line 117
using type = _Ty; 
#line 119
template< template< class >  class _Fn> using _Apply = _Fn< _Ty> ; 
#line 121
}; 
#line 123
template< class _Ty> 
#line 124
struct remove_cv< const _Ty>  { 
#line 125
using type = _Ty; 
#line 127
template< template< class >  class _Fn> using _Apply = const _Fn< _Ty> ; 
#line 129
}; 
#line 131
template< class _Ty> 
#line 132
struct remove_cv< volatile _Ty>  { 
#line 133
using type = _Ty; 
#line 135
template< template< class >  class _Fn> using _Apply = volatile _Fn< _Ty> ; 
#line 137
}; 
#line 139
template< class _Ty> 
#line 140
struct remove_cv< const volatile _Ty>  { 
#line 141
using type = _Ty; 
#line 143
template< template< class >  class _Fn> using _Apply = const volatile _Fn< _Ty> ; 
#line 145
}; 
#line 147
template< class _Ty> using remove_cv_t = typename remove_cv< _Ty> ::type; 
#line 150
template< bool _First_value, class _First, class ..._Rest> 
#line 151
struct _Disjunction { 
#line 152
using type = _First; 
#line 153
}; 
#line 155
template< class _False, class _Next, class ..._Rest> 
#line 156
struct _Disjunction< false, _False, _Next, _Rest...>  { 
#line 157
using type = typename std::_Disjunction< static_cast< bool>(_Next::value), _Next, _Rest...> ::type; 
#line 158
}; 
#line 160
template< class ..._Traits> 
#line 161
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] disjunction : public false_type { }; 
#line 163
template< class _First, class ..._Rest> 
#line 164
struct disjunction< _First, _Rest...>  : public _Disjunction< static_cast< bool>(_First::value), _First, _Rest...> ::type { 
#line 166
}; 
#line 168
template< class ..._Traits> 
#line 169
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool disjunction_v = (disjunction< _Traits...> ::value); 
#line 171
template< class _Ty, class ..._Types> constexpr bool 
#line 172
_Is_any_of_v = disjunction_v< is_same< _Ty, _Types> ...> ; 
#line 179 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\xtr1common"
[[nodiscard]] constexpr bool _Is_constant_evaluated() noexcept { 
#line 180
return __builtin_is_constant_evaluated(); 
#line 181
} 
#line 189 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\xtr1common"
template< class _Ty> 
#line 190
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_integral_v = _Is_any_of_v< remove_cv_t< _Ty> , bool, char, signed char, unsigned char, __wchar_t, char16_t, char32_t, short, unsigned short, int, unsigned, long, unsigned long, __int64, unsigned __int64> ; 
#line 197
template< class _Ty> 
#line 198
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_integral : public bool_constant< is_integral_v< _Ty> >  { }; 
#line 200
template< class _Ty> constexpr bool 
#line 201
_Is_nonbool_integral = is_integral_v< _Ty>  && (!is_same_v< remove_cv_t< _Ty> , bool> ); 
#line 203
template< class _Ty> 
#line 204
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_floating_point_v = _Is_any_of_v< remove_cv_t< _Ty> , float, double, long double> ; 
#line 207
template< class _Ty> 
#line 208
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_floating_point : public bool_constant< is_floating_point_v< _Ty> >  { }; 
#line 210
template< class _Ty> 
#line 211
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_arithmetic_v = is_integral_v< _Ty>  || is_floating_point_v< _Ty> ; 
#line 214
template< class _Ty> 
#line 215
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_arithmetic : public bool_constant< is_arithmetic_v< _Ty> >  { }; 
#line 217
template< class _Ty> 
#line 218
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_reference { 
#line 219
using type = _Ty; 
#line 220
using _Const_thru_ref_type = const _Ty; 
#line 221
}; 
#line 223
template< class _Ty> 
#line 224
struct remove_reference< _Ty &>  { 
#line 225
using type = _Ty; 
#line 226
using _Const_thru_ref_type = const _Ty &; 
#line 227
}; 
#line 229
template< class _Ty> 
#line 230
struct remove_reference< _Ty &&>  { 
#line 231
using type = _Ty; 
#line 232
using _Const_thru_ref_type = const _Ty &&; 
#line 233
}; 
#line 235
template< class _Ty> using remove_reference_t = typename remove_reference< _Ty> ::type; 
#line 238
template< class _Ty> using _Const_thru_ref = typename remove_reference< _Ty> ::_Const_thru_ref_type; 
#line 241
template< class _Ty> using _Remove_cvref_t
#line 242
 [[msvc::known_semantics]] = remove_cv_t< remove_reference_t< _Ty> > ; 
#line 254 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\xtr1common"
}
#line 263
#pragma warning(pop)
#pragma pack ( pop )
#line 20 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\intrin0.inl.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 25
#pragma warning(disable: 28251)
#line 28
extern "C" {
#line 115 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\intrin0.inl.h"
unsigned char _BitScanForward(unsigned long * _Index, unsigned long _Mask); 
#line 116
unsigned char _BitScanForward64(unsigned long * _Index, unsigned __int64 _Mask); 
#line 118
unsigned char _BitScanReverse(unsigned long * _Index, unsigned long _Mask); 
#line 119
unsigned char _BitScanReverse64(unsigned long * _Index, unsigned __int64 _Mask); 
#line 121
unsigned char _bittest(const long *, long); 
#line 126
long _InterlockedAnd(volatile long * _Value, long _Mask); 
#line 127
short _InterlockedAnd16(volatile short * _Value, short _Mask); 
#line 131
__int64 _InterlockedAnd64(volatile __int64 * _Value, __int64 _Mask); 
#line 132
__int64 _interlockedand64(volatile __int64 * _Value, __int64 _Mask); 
#line 136
char _InterlockedAnd8(volatile char * _Value, char _Mask); 
#line 143
long _InterlockedCompareExchange(volatile long * _Destination, long _Exchange, long _Comparand); 
#line 145
short _InterlockedCompareExchange16(volatile short * _Destination, short _Exchange, short _Comparand); 
#line 149
__int64 _InterlockedCompareExchange64(volatile __int64 * _Destination, __int64 _Exchange, __int64 _Comparand); 
#line 153
char _InterlockedCompareExchange8(volatile char * _Destination, char _Exchange, char _Comparand); 
#line 160
unsigned char _InterlockedCompareExchange128(volatile __int64 * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult); 
#line 164
long _InterlockedDecrement(volatile long * _Addend); 
#line 166
short _InterlockedDecrement16(volatile short * _Addend); 
#line 167
__int64 _InterlockedDecrement64(volatile __int64 * _Addend); 
#line 168
__int64 _interlockeddecrement64(volatile __int64 * _Addend); 
#line 169
long _InterlockedExchange(volatile long * _Target, long _Value); 
#line 171
short _InterlockedExchange16(volatile short * _Target, short _Value); 
#line 175
__int64 _InterlockedExchange64(volatile __int64 * _Target, __int64 _Value); 
#line 176
__int64 _interlockedexchange64(volatile __int64 * _Target, __int64 _Value); 
#line 180
char _InterlockedExchange8(volatile char * _Target, char _Value); 
#line 184
long _InterlockedExchangeAdd(volatile long * _Addend, long _Value); 
#line 185
short _InterlockedExchangeAdd16(volatile short * _Addend, short _Value); 
#line 189
__int64 _InterlockedExchangeAdd64(volatile __int64 * _Addend, __int64 _Value); 
#line 190
__int64 _interlockedexchangeadd64(volatile __int64 * _Addend, __int64 _Value); 
#line 194
char _InterlockedExchangeAdd8(volatile char * _Addend, char _Value); 
#line 204
long _InterlockedIncrement(volatile long * _Addend); 
#line 206
short _InterlockedIncrement16(volatile short * _Addend); 
#line 207
__int64 _InterlockedIncrement64(volatile __int64 * _Addend); 
#line 208
__int64 _interlockedincrement64(volatile __int64 * _Addend); 
#line 210
long _InterlockedOr(volatile long * _Value, long _Mask); 
#line 211
short _InterlockedOr16(volatile short * _Value, short _Mask); 
#line 215
__int64 _InterlockedOr64(volatile __int64 * _Value, __int64 _Mask); 
#line 216
__int64 _interlockedor64(volatile __int64 * _Value, __int64 _Mask); 
#line 220
char _InterlockedOr8(volatile char * _Value, char _Mask); 
#line 227
long _InterlockedXor(volatile long * _Value, long _Mask); 
#line 228
short _InterlockedXor16(volatile short * _Value, short _Mask); 
#line 232
__int64 _InterlockedXor64(volatile __int64 * _Value, __int64 _Mask); 
#line 233
__int64 _interlockedxor64(volatile __int64 * _Value, __int64 _Mask); 
#line 237
char _InterlockedXor8(volatile char * _Value, char _Mask); 
#line 244
void _ReadWriteBarrier(); 
#line 245
short __iso_volatile_load16(const volatile short *); 
#line 246
int __iso_volatile_load32(const volatile int *); 
#line 247
__int64 __iso_volatile_load64(const volatile __int64 *); 
#line 248
char __iso_volatile_load8(const volatile char *); 
#line 249
void __iso_volatile_store16(volatile short *, short); 
#line 250
void __iso_volatile_store32(volatile int *, int); 
#line 251
void __iso_volatile_store64(volatile __int64 *, __int64); 
#line 252
void __iso_volatile_store8(volatile char *, char); 
#line 254
void _mm_pause(); 
#line 255
unsigned __lzcnt(unsigned); 
#line 256
unsigned short __lzcnt16(unsigned short); 
#line 257
unsigned __int64 __lzcnt64(unsigned __int64); 
#line 258
unsigned __popcnt(unsigned); 
#line 259
unsigned short __popcnt16(unsigned short); 
#line 260
unsigned __int64 __popcnt64(unsigned __int64); 
#line 261
unsigned __cdecl _rotl(unsigned _Value, int _Shift); 
#line 262
unsigned short __cdecl _rotl16(unsigned short _Value, unsigned char _Shift); 
#line 263
unsigned __int64 __cdecl _rotl64(unsigned __int64 _Value, int _Shift); 
#line 264
unsigned char __cdecl _rotl8(unsigned char _Value, unsigned char _Shift); 
#line 265
unsigned __cdecl _rotr(unsigned _Value, int _Shift); 
#line 266
unsigned short __cdecl _rotr16(unsigned short _Value, unsigned char _Shift); 
#line 267
unsigned __int64 __cdecl _rotr64(unsigned __int64 _Value, int _Shift); 
#line 268
unsigned char __cdecl _rotr8(unsigned char _Value, unsigned char _Shift); 
#line 269
unsigned __int64 __shiftleft128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _Shift); 
#line 270
unsigned __int64 __shiftright128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _Shift); 
#line 272
unsigned _tzcnt_u32(unsigned); 
#line 273
unsigned __int64 _tzcnt_u64(unsigned __int64); 
#line 275 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\intrin0.inl.h"
unsigned __int64 _umul128(unsigned __int64 _Multiplier, unsigned __int64 _Multiplicand, unsigned __int64 * _HighProduct); 
#line 276
unsigned __int64 __umulh(unsigned __int64, unsigned __int64); 
#line 278
unsigned __int64 __cdecl _udiv128(unsigned __int64 _HighDividend, unsigned __int64 _LowDividend, unsigned __int64 _Divisor, unsigned __int64 * _Remainder); 
#line 279
unsigned char __cdecl _addcarry_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *); 
#line 280
unsigned char __cdecl _subborrow_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *); 
#line 281
double __ceil(double); 
#line 282
float __ceilf(float); 
#line 283
double __floor(double); 
#line 284
float __floorf(float); 
#line 285
double __round(double); 
#line 286
float __roundf(float); 
#line 287
double __trunc(double); 
#line 288
float __truncf(float); 
#line 289
double __copysign(double, double); 
#line 290
float __copysignf(float, float); 
#line 291
unsigned __signbitvalue(double); 
#line 292
unsigned __signbitvaluef(float); 
#line 310 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\intrin0.inl.h"
void *__cdecl __builtin_assume_aligned(const void *, size_t, ...) noexcept; 
#line 321 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\intrin0.inl.h"
}
#line 323 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\intrin0.inl.h"
#pragma warning(pop)
#line 28 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 36
[[nodiscard]] inline float acos(float _Xx) noexcept { 
#line 37
return ::acosf(_Xx); 
#line 38
} 
#line 40
[[nodiscard]] inline float acosh(float _Xx) noexcept { 
#line 41
return ::acoshf(_Xx); 
#line 42
} 
#line 44
[[nodiscard]] inline float asin(float _Xx) noexcept { 
#line 45
return ::asinf(_Xx); 
#line 46
} 
#line 48
[[nodiscard]] inline float asinh(float _Xx) noexcept { 
#line 49
return ::asinhf(_Xx); 
#line 50
} 
#line 52
[[nodiscard]] inline float atan(float _Xx) noexcept { 
#line 53
return ::atanf(_Xx); 
#line 54
} 
#line 56
[[nodiscard]] inline float atanh(float _Xx) noexcept { 
#line 57
return ::atanhf(_Xx); 
#line 58
} 
#line 60
[[nodiscard]] inline float atan2(float _Yx, float _Xx) noexcept { 
#line 61
return ::atan2f(_Yx, _Xx); 
#line 62
} 
#line 64
[[nodiscard]] inline float cbrt(float _Xx) noexcept { 
#line 65
return ::cbrtf(_Xx); 
#line 66
} 
#line 68
[[nodiscard]] inline float ceil(float _Xx) noexcept { 
#line 70
return __ceilf(_Xx); 
#line 76 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 78
[[nodiscard]] inline float copysign(float _Number, float _Sign) noexcept { 
#line 80
return __copysignf(_Number, _Sign); 
#line 86 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 88
[[nodiscard]] inline float cos(float _Xx) noexcept { 
#line 89
return ::cosf(_Xx); 
#line 90
} 
#line 92
[[nodiscard]] inline float cosh(float _Xx) noexcept { 
#line 93
return ::coshf(_Xx); 
#line 94
} 
#line 96
[[nodiscard]] inline float erf(float _Xx) noexcept { 
#line 97
return ::erff(_Xx); 
#line 98
} 
#line 100
[[nodiscard]] inline float erfc(float _Xx) noexcept { 
#line 101
return ::erfcf(_Xx); 
#line 102
} 
#line 104
[[nodiscard]] inline float exp(float _Xx) noexcept { 
#line 105
return ::expf(_Xx); 
#line 106
} 
#line 108
[[nodiscard]] inline float exp2(float _Xx) noexcept { 
#line 109
return ::exp2f(_Xx); 
#line 110
} 
#line 112
[[nodiscard]] inline float expm1(float _Xx) noexcept { 
#line 113
return ::expm1f(_Xx); 
#line 114
} 
#line 116
[[nodiscard]] inline float fabs(float _Xx) noexcept { 
#line 117
return ::fabsf(_Xx); 
#line 118
} 
#line 120
[[nodiscard]] inline float fdim(float _Xx, float _Yx) noexcept { 
#line 121
return ::fdimf(_Xx, _Yx); 
#line 122
} 
#line 124
[[nodiscard]] inline float floor(float _Xx) noexcept { 
#line 126
return __floorf(_Xx); 
#line 132 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 134
[[nodiscard]] inline float fma(float _Xx, float _Yx, float _Zx) noexcept { 
#line 135
return ::fmaf(_Xx, _Yx, _Zx); 
#line 136
} 
#line 138
[[nodiscard]] inline float fmax(float _Xx, float _Yx) noexcept { 
#line 139
return ::fmaxf(_Xx, _Yx); 
#line 140
} 
#line 142
[[nodiscard]] inline float fmin(float _Xx, float _Yx) noexcept { 
#line 143
return ::fminf(_Xx, _Yx); 
#line 144
} 
#line 146
[[nodiscard]] inline float fmod(float _Xx, float _Yx) noexcept { 
#line 147
return ::fmodf(_Xx, _Yx); 
#line 148
} 
#line 150
inline float frexp(float _Xx, int *_Yx) noexcept { 
#line 151
return ::frexpf(_Xx, _Yx); 
#line 152
} 
#line 154
[[nodiscard]] inline float hypot(float _Xx, float _Yx) noexcept { 
#line 155
return ::hypotf(_Xx, _Yx); 
#line 156
} 
#line 158
[[nodiscard]] inline int ilogb(float _Xx) noexcept { 
#line 159
return ::ilogbf(_Xx); 
#line 160
} 
#line 162
[[nodiscard]] inline float ldexp(float _Xx, int _Yx) noexcept { 
#line 163
return ::ldexpf(_Xx, _Yx); 
#line 164
} 
#line 166
[[nodiscard]] inline float lgamma(float _Xx) noexcept { 
#line 167
return ::lgammaf(_Xx); 
#line 168
} 
#line 170
[[nodiscard]] inline __int64 llrint(float _Xx) noexcept { 
#line 171
return ::llrintf(_Xx); 
#line 172
} 
#line 174
[[nodiscard]] inline __int64 llround(float _Xx) noexcept { 
#line 175
return ::llroundf(_Xx); 
#line 176
} 
#line 178
[[nodiscard]] inline float log(float _Xx) noexcept { 
#line 179
return ::logf(_Xx); 
#line 180
} 
#line 182
[[nodiscard]] inline float log10(float _Xx) noexcept { 
#line 183
return ::log10f(_Xx); 
#line 184
} 
#line 186
[[nodiscard]] inline float log1p(float _Xx) noexcept { 
#line 187
return ::log1pf(_Xx); 
#line 188
} 
#line 190
[[nodiscard]] inline float log2(float _Xx) noexcept { 
#line 191
return ::log2f(_Xx); 
#line 192
} 
#line 194
[[nodiscard]] inline float logb(float _Xx) noexcept { 
#line 195
return ::logbf(_Xx); 
#line 196
} 
#line 198
[[nodiscard]] inline long lrint(float _Xx) noexcept { 
#line 199
return ::lrintf(_Xx); 
#line 200
} 
#line 202
[[nodiscard]] inline long lround(float _Xx) noexcept { 
#line 203
return ::lroundf(_Xx); 
#line 204
} 
#line 206
inline float modf(float _Xx, float *_Yx) noexcept { 
#line 207
return ::modff(_Xx, _Yx); 
#line 208
} 
#line 210
[[nodiscard]] inline float nearbyint(float _Xx) noexcept { 
#line 211
return ::nearbyintf(_Xx); 
#line 212
} 
#line 214
[[nodiscard]] inline float nextafter(float _Xx, float _Yx) noexcept { 
#line 215
return ::nextafterf(_Xx, _Yx); 
#line 216
} 
#line 218
[[nodiscard]] inline float nexttoward(float _Xx, long double _Yx) noexcept { 
#line 219
return ::nexttowardf(_Xx, _Yx); 
#line 220
} 
#line 222
[[nodiscard]] inline float pow(float _Xx, float _Yx) noexcept { 
#line 223
return ::powf(_Xx, _Yx); 
#line 224
} 
#line 226
[[nodiscard]] inline float remainder(float _Xx, float _Yx) noexcept { 
#line 227
return ::remainderf(_Xx, _Yx); 
#line 228
} 
#line 230
inline float remquo(float _Xx, float _Yx, int *_Zx) noexcept { 
#line 231
return ::remquof(_Xx, _Yx, _Zx); 
#line 232
} 
#line 234
[[nodiscard]] inline float rint(float _Xx) noexcept { 
#line 235
return ::rintf(_Xx); 
#line 236
} 
#line 238
[[nodiscard]] inline float round(float _Xx) noexcept { 
#line 240
return __roundf(_Xx); 
#line 246 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 248
[[nodiscard]] inline float scalbln(float _Xx, long _Yx) noexcept { 
#line 249
return ::scalblnf(_Xx, _Yx); 
#line 250
} 
#line 252
[[nodiscard]] inline float scalbn(float _Xx, int _Yx) noexcept { 
#line 253
return ::scalbnf(_Xx, _Yx); 
#line 254
} 
#line 256
[[nodiscard]] inline float sin(float _Xx) noexcept { 
#line 257
return ::sinf(_Xx); 
#line 258
} 
#line 260
[[nodiscard]] inline float sinh(float _Xx) noexcept { 
#line 261
return ::sinhf(_Xx); 
#line 262
} 
#line 264
[[nodiscard]] inline float sqrt(float _Xx) noexcept { 
#line 265
return ::sqrtf(_Xx); 
#line 266
} 
#line 268
[[nodiscard]] inline float tan(float _Xx) noexcept { 
#line 269
return ::tanf(_Xx); 
#line 270
} 
#line 272
[[nodiscard]] inline float tanh(float _Xx) noexcept { 
#line 273
return ::tanhf(_Xx); 
#line 274
} 
#line 276
[[nodiscard]] inline float tgamma(float _Xx) noexcept { 
#line 277
return ::tgammaf(_Xx); 
#line 278
} 
#line 280
[[nodiscard]] inline float trunc(float _Xx) noexcept { 
#line 282
return __truncf(_Xx); 
#line 288 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 290
[[nodiscard]] inline long double acos(long double _Xx) noexcept { 
#line 291
return ::acosl(_Xx); 
#line 292
} 
#line 294
[[nodiscard]] inline long double acosh(long double _Xx) noexcept { 
#line 295
return ::acoshl(_Xx); 
#line 296
} 
#line 298
[[nodiscard]] inline long double asin(long double _Xx) noexcept { 
#line 299
return ::asinl(_Xx); 
#line 300
} 
#line 302
[[nodiscard]] inline long double asinh(long double _Xx) noexcept { 
#line 303
return ::asinhl(_Xx); 
#line 304
} 
#line 306
[[nodiscard]] inline long double atan(long double _Xx) noexcept { 
#line 307
return ::atanl(_Xx); 
#line 308
} 
#line 310
[[nodiscard]] inline long double atanh(long double _Xx) noexcept { 
#line 311
return ::atanhl(_Xx); 
#line 312
} 
#line 314
[[nodiscard]] inline long double atan2(long double _Yx, long double _Xx) noexcept 
#line 315
{ 
#line 316
return ::atan2l(_Yx, _Xx); 
#line 317
} 
#line 319
[[nodiscard]] inline long double cbrt(long double _Xx) noexcept { 
#line 320
return ::cbrtl(_Xx); 
#line 321
} 
#line 323
[[nodiscard]] inline long double ceil(long double _Xx) noexcept { 
#line 325
return __ceil(static_cast< double>(_Xx)); 
#line 331 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 333
[[nodiscard]] inline long double copysign(long double _Number, long double _Sign) noexcept 
#line 334
{ 
#line 336
return __copysign(static_cast< double>(_Number), static_cast< double>(_Sign)); 
#line 342 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 344
[[nodiscard]] inline long double cos(long double _Xx) noexcept { 
#line 345
return ::cosl(_Xx); 
#line 346
} 
#line 348
[[nodiscard]] inline long double cosh(long double _Xx) noexcept { 
#line 349
return ::coshl(_Xx); 
#line 350
} 
#line 352
[[nodiscard]] inline long double erf(long double _Xx) noexcept { 
#line 353
return ::erfl(_Xx); 
#line 354
} 
#line 356
[[nodiscard]] inline long double erfc(long double _Xx) noexcept { 
#line 357
return ::erfcl(_Xx); 
#line 358
} 
#line 360
[[nodiscard]] inline long double exp(long double _Xx) noexcept { 
#line 361
return ::expl(_Xx); 
#line 362
} 
#line 364
[[nodiscard]] inline long double exp2(long double _Xx) noexcept { 
#line 365
return ::exp2l(_Xx); 
#line 366
} 
#line 368
[[nodiscard]] inline long double expm1(long double _Xx) noexcept { 
#line 369
return ::expm1l(_Xx); 
#line 370
} 
#line 372
[[nodiscard]] inline long double fabs(long double _Xx) noexcept { 
#line 373
return ::fabsl(_Xx); 
#line 374
} 
#line 376
[[nodiscard]] inline long double fdim(long double _Xx, long double _Yx) noexcept 
#line 377
{ 
#line 378
return ::fdiml(_Xx, _Yx); 
#line 379
} 
#line 381
[[nodiscard]] inline long double floor(long double _Xx) noexcept { 
#line 383
return __floor(static_cast< double>(_Xx)); 
#line 389 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 391
[[nodiscard]] inline long double fma(long double 
#line 392
_Xx, long double _Yx, long double _Zx) noexcept { 
#line 393
return ::fmal(_Xx, _Yx, _Zx); 
#line 394
} 
#line 396
[[nodiscard]] inline long double fmax(long double _Xx, long double _Yx) noexcept 
#line 397
{ 
#line 398
return ::fmaxl(_Xx, _Yx); 
#line 399
} 
#line 401
[[nodiscard]] inline long double fmin(long double _Xx, long double _Yx) noexcept 
#line 402
{ 
#line 403
return ::fminl(_Xx, _Yx); 
#line 404
} 
#line 406
[[nodiscard]] inline long double fmod(long double _Xx, long double _Yx) noexcept 
#line 407
{ 
#line 408
return ::fmodl(_Xx, _Yx); 
#line 409
} 
#line 411
inline long double frexp(long double _Xx, int *_Yx) noexcept { 
#line 412
return ::frexpl(_Xx, _Yx); 
#line 413
} 
#line 415
[[nodiscard]] inline long double hypot(long double _Xx, long double _Yx) noexcept 
#line 416
{ 
#line 417
return ::hypotl(_Xx, _Yx); 
#line 418
} 
#line 420
[[nodiscard]] inline int ilogb(long double _Xx) noexcept { 
#line 421
return ::ilogbl(_Xx); 
#line 422
} 
#line 424
[[nodiscard]] inline long double ldexp(long double _Xx, int _Yx) noexcept { 
#line 425
return ::ldexpl(_Xx, _Yx); 
#line 426
} 
#line 428
[[nodiscard]] inline long double lgamma(long double _Xx) noexcept { 
#line 429
return ::lgammal(_Xx); 
#line 430
} 
#line 432
[[nodiscard]] inline __int64 llrint(long double _Xx) noexcept { 
#line 433
return ::llrintl(_Xx); 
#line 434
} 
#line 436
[[nodiscard]] inline __int64 llround(long double _Xx) noexcept { 
#line 437
return ::llroundl(_Xx); 
#line 438
} 
#line 440
[[nodiscard]] inline long double log(long double _Xx) noexcept { 
#line 441
return ::logl(_Xx); 
#line 442
} 
#line 444
[[nodiscard]] inline long double log10(long double _Xx) noexcept { 
#line 445
return ::log10l(_Xx); 
#line 446
} 
#line 448
[[nodiscard]] inline long double log1p(long double _Xx) noexcept { 
#line 449
return ::log1pl(_Xx); 
#line 450
} 
#line 452
[[nodiscard]] inline long double log2(long double _Xx) noexcept { 
#line 453
return ::log2l(_Xx); 
#line 454
} 
#line 456
[[nodiscard]] inline long double logb(long double _Xx) noexcept { 
#line 457
return ::logbl(_Xx); 
#line 458
} 
#line 460
[[nodiscard]] inline long lrint(long double _Xx) noexcept { 
#line 461
return ::lrintl(_Xx); 
#line 462
} 
#line 464
[[nodiscard]] inline long lround(long double _Xx) noexcept { 
#line 465
return ::lroundl(_Xx); 
#line 466
} 
#line 468
inline long double modf(long double _Xx, long double *_Yx) noexcept { 
#line 469
return ::modfl(_Xx, _Yx); 
#line 470
} 
#line 472
[[nodiscard]] inline long double nearbyint(long double _Xx) noexcept { 
#line 473
return ::nearbyintl(_Xx); 
#line 474
} 
#line 476
[[nodiscard]] inline long double nextafter(long double _Xx, long double _Yx) noexcept 
#line 477
{ 
#line 478
return ::nextafterl(_Xx, _Yx); 
#line 479
} 
#line 481
[[nodiscard]] inline long double nexttoward(long double _Xx, long double _Yx) noexcept 
#line 482
{ 
#line 483
return ::nexttowardl(_Xx, _Yx); 
#line 484
} 
#line 486
[[nodiscard]] inline long double pow(long double _Xx, long double _Yx) noexcept 
#line 487
{ 
#line 488
return ::powl(_Xx, _Yx); 
#line 489
} 
#line 491
[[nodiscard]] inline long double remainder(long double _Xx, long double _Yx) noexcept 
#line 492
{ 
#line 493
return ::remainderl(_Xx, _Yx); 
#line 494
} 
#line 496
inline long double remquo(long double _Xx, long double _Yx, int *_Zx) noexcept { 
#line 497
return ::remquol(_Xx, _Yx, _Zx); 
#line 498
} 
#line 500
[[nodiscard]] inline long double rint(long double _Xx) noexcept { 
#line 501
return ::rintl(_Xx); 
#line 502
} 
#line 504
[[nodiscard]] inline long double round(long double _Xx) noexcept { 
#line 506
return __round(static_cast< double>(_Xx)); 
#line 512 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 514
[[nodiscard]] inline long double scalbln(long double _Xx, long _Yx) noexcept { 
#line 515
return ::scalblnl(_Xx, _Yx); 
#line 516
} 
#line 518
[[nodiscard]] inline long double scalbn(long double _Xx, int _Yx) noexcept { 
#line 519
return ::scalbnl(_Xx, _Yx); 
#line 520
} 
#line 522
[[nodiscard]] inline long double sin(long double _Xx) noexcept { 
#line 523
return ::sinl(_Xx); 
#line 524
} 
#line 526
[[nodiscard]] inline long double sinh(long double _Xx) noexcept { 
#line 527
return ::sinhl(_Xx); 
#line 528
} 
#line 530
[[nodiscard]] inline long double sqrt(long double _Xx) noexcept { 
#line 531
return ::sqrtl(_Xx); 
#line 532
} 
#line 534
[[nodiscard]] inline long double tan(long double _Xx) noexcept { 
#line 535
return ::tanl(_Xx); 
#line 536
} 
#line 538
[[nodiscard]] inline long double tanh(long double _Xx) noexcept { 
#line 539
return ::tanhl(_Xx); 
#line 540
} 
#line 542
[[nodiscard]] inline long double tgamma(long double _Xx) noexcept { 
#line 543
return ::tgammal(_Xx); 
#line 544
} 
#line 546
[[nodiscard]] inline long double trunc(long double _Xx) noexcept { 
#line 548
return __trunc(static_cast< double>(_Xx)); 
#line 554 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
} 
#line 557
namespace std { 
#line 558
template< class _Ty1, class _Ty2> using _Common_float_type_t = conditional_t< is_same_v< _Ty1, long double>  || is_same_v< _Ty2, long double> , long double, conditional_t< is_same_v< _Ty1, float>  && is_same_v< _Ty2, float> , float, double> > ; 
#line 562
}
#line 565
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 >
double frexp ( _Ty _Value, int * const _Exp ) noexcept {
    return :: frexp ( static_cast < double > ( _Value ), _Exp );
}
#line 570
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 >
[ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > pow ( _Ty1 _Left, _Ty2 _Right ) noexcept {
    if constexpr ( :: std :: _Is_nonbool_integral < _Ty2 > ) {
        if ( _Right == 2 ) {
            return static_cast < double > ( _Left ) * static_cast < double > ( _Left );
        }
    }

    return :: pow ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) );
}
#line 581
template < class _Ty1, class _Ty2, class _Ty3,
    :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 > && :: std :: is_arithmetic_v < _Ty3 >, int > = 0 >
[ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, :: std :: _Common_float_type_t < _Ty2, _Ty3 > > fma (
    _Ty1 _Left, _Ty2 _Middle, _Ty3 _Right ) noexcept {
    using _Common = :: std :: _Common_float_type_t < _Ty1, :: std :: _Common_float_type_t < _Ty2, _Ty3 >>;
    if constexpr ( :: std :: is_same_v < _Common, float > ) {
        return :: fmaf ( static_cast < _Common > ( _Left ), static_cast < _Common > ( _Middle ), static_cast < _Common > ( _Right ) );
    } else if constexpr ( :: std :: is_same_v < _Common, double > ) {
        return :: fma ( static_cast < _Common > ( _Left ), static_cast < _Common > ( _Middle ), static_cast < _Common > ( _Right ) );
    } else {
        return :: fmal ( static_cast < _Common > ( _Left ), static_cast < _Common > ( _Middle ), static_cast < _Common > ( _Right ) );
    }
}
#line 595
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 >
:: std :: _Common_float_type_t < _Ty1, _Ty2 > remquo ( _Ty1 _Left, _Ty2 _Right, int * _Pquo ) noexcept {
    using _Common = :: std :: _Common_float_type_t < _Ty1, _Ty2 >;
    if constexpr ( :: std :: is_same_v < _Common, float > ) {
        return :: remquof ( static_cast < _Common > ( _Left ), static_cast < _Common > ( _Right ), _Pquo );
    } else if constexpr ( :: std :: is_same_v < _Common, double > ) {
        return :: remquo ( static_cast < _Common > ( _Left ), static_cast < _Common > ( _Right ), _Pquo );
    } else {
        return :: remquol ( static_cast < _Common > ( _Left ), static_cast < _Common > ( _Right ), _Pquo );
    }
}
#line 717
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 >
[ [ nodiscard ] ] inline int fpclassify ( const _Ty _Ix ) noexcept {
    return _Ix == 0 ? 0 : ( - 1 );
}
#line 723
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 >
[ [ nodiscard ] ] inline bool signbit ( const _Ty _Ix ) noexcept {
    if constexpr ( static_cast < _Ty > ( - 1 ) < _Ty { } ) {
        return _Ix < 0;
    } else {
        return false;
    }
}
#line 738
[[nodiscard]] inline bool isnormal(const signed char _Ix) noexcept { return _Ix != 0; } 
#line 739
[[nodiscard]] inline bool isnormal(const unsigned char _Ix) noexcept { return _Ix != 0; } 
#line 740
[[nodiscard]] inline bool isnormal(const short _Ix) noexcept { return _Ix != 0; } 
#line 741
[[nodiscard]] inline bool isnormal(const unsigned short _Ix) noexcept { return _Ix != 0; } 
#line 742
[[nodiscard]] inline bool isnormal(const int _Ix) noexcept { return _Ix != 0; } 
#line 743
[[nodiscard]] inline bool isnormal(const unsigned _Ix) noexcept { return _Ix != (0); } 
#line 744
[[nodiscard]] inline bool isnormal(const long _Ix) noexcept { return _Ix != (0); } 
#line 745
[[nodiscard]] inline bool isnormal(const unsigned long _Ix) noexcept { return _Ix != (0); } 
#line 746
[[nodiscard]] inline bool isnormal(const __int64 _Ix) noexcept { return _Ix != (0); } 
#line 747
[[nodiscard]] inline bool isnormal(const unsigned __int64 _Ix) noexcept { return _Ix != (0); } 
#line 748
[[nodiscard]] inline bool isnormal(const bool _Ix) noexcept { return _Ix != 0; } 
#line 749
[[nodiscard]] inline bool isnormal(const char _Ix) noexcept { return _Ix != 0; } 
#line 753
[[nodiscard]] inline bool isnormal(const char16_t _Ix) noexcept { return _Ix != 0; } 
#line 754
[[nodiscard]] inline bool isnormal(const char32_t _Ix) noexcept { return _Ix != (0); } 
#line 756
[[nodiscard]] inline bool isnormal(const __wchar_t _Ix) noexcept { return _Ix != 0; } 
#line 843 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double acos ( _Ty _Left ) noexcept { return :: acos ( static_cast < double > ( _Left ) ); }
#line 844
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double asin ( _Ty _Left ) noexcept { return :: asin ( static_cast < double > ( _Left ) ); }
#line 845
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double atan ( _Ty _Left ) noexcept { return :: atan ( static_cast < double > ( _Left ) ); }
#line 846
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > atan2 ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: atan2 ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 847
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double cos ( _Ty _Left ) noexcept { return :: cos ( static_cast < double > ( _Left ) ); }
#line 848
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double sin ( _Ty _Left ) noexcept { return :: sin ( static_cast < double > ( _Left ) ); }
#line 849
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double tan ( _Ty _Left ) noexcept { return :: tan ( static_cast < double > ( _Left ) ); }
#line 850
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double acosh ( _Ty _Left ) noexcept { return :: acosh ( static_cast < double > ( _Left ) ); }
#line 851
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double asinh ( _Ty _Left ) noexcept { return :: asinh ( static_cast < double > ( _Left ) ); }
#line 852
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double atanh ( _Ty _Left ) noexcept { return :: atanh ( static_cast < double > ( _Left ) ); }
#line 853
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double cosh ( _Ty _Left ) noexcept { return :: cosh ( static_cast < double > ( _Left ) ); }
#line 854
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double sinh ( _Ty _Left ) noexcept { return :: sinh ( static_cast < double > ( _Left ) ); }
#line 855
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double tanh ( _Ty _Left ) noexcept { return :: tanh ( static_cast < double > ( _Left ) ); }
#line 856
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double exp ( _Ty _Left ) noexcept { return :: exp ( static_cast < double > ( _Left ) ); }
#line 857
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double exp2 ( _Ty _Left ) noexcept { return :: exp2 ( static_cast < double > ( _Left ) ); }
#line 858
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double expm1 ( _Ty _Left ) noexcept { return :: expm1 ( static_cast < double > ( _Left ) ); }
#line 860
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] int ilogb ( _Ty _Left ) noexcept { return :: ilogb ( static_cast < double > ( _Left ) ); }
#line 861
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double ldexp ( _Ty _Left, int _Arg2 ) noexcept { return :: ldexp ( static_cast < double > ( _Left ), _Arg2 ); }
#line 862
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double log ( _Ty _Left ) noexcept { return :: log ( static_cast < double > ( _Left ) ); }
#line 863
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double log10 ( _Ty _Left ) noexcept { return :: log10 ( static_cast < double > ( _Left ) ); }
#line 864
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double log1p ( _Ty _Left ) noexcept { return :: log1p ( static_cast < double > ( _Left ) ); }
#line 865
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double log2 ( _Ty _Left ) noexcept { return :: log2 ( static_cast < double > ( _Left ) ); }
#line 866
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double logb ( _Ty _Left ) noexcept { return :: logb ( static_cast < double > ( _Left ) ); }
#line 868
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double scalbn ( _Ty _Left, int _Arg2 ) noexcept { return :: scalbn ( static_cast < double > ( _Left ), _Arg2 ); }
#line 869
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double scalbln ( _Ty _Left, long _Arg2 ) noexcept { return :: scalbln ( static_cast < double > ( _Left ), _Arg2 ); }
#line 870
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double cbrt ( _Ty _Left ) noexcept { return :: cbrt ( static_cast < double > ( _Left ) ); }
#line 872
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double fabs ( _Ty _Left ) noexcept { return :: fabs ( static_cast < double > ( _Left ) ); }
#line 873
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > hypot ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: hypot ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 876
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double sqrt ( _Ty _Left ) noexcept { return :: sqrt ( static_cast < double > ( _Left ) ); }
#line 877
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double erf ( _Ty _Left ) noexcept { return :: erf ( static_cast < double > ( _Left ) ); }
#line 878
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double erfc ( _Ty _Left ) noexcept { return :: erfc ( static_cast < double > ( _Left ) ); }
#line 879
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double lgamma ( _Ty _Left ) noexcept { return :: lgamma ( static_cast < double > ( _Left ) ); }
#line 880
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double tgamma ( _Ty _Left ) noexcept { return :: tgamma ( static_cast < double > ( _Left ) ); }
#line 881
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double ceil ( _Ty _Left ) noexcept { return __ceil ( static_cast < double > ( _Left ) ); }
#line 882
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double floor ( _Ty _Left ) noexcept { return __floor ( static_cast < double > ( _Left ) ); }
#line 883
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double nearbyint ( _Ty _Left ) noexcept { return :: nearbyint ( static_cast < double > ( _Left ) ); }
#line 884
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double rint ( _Ty _Left ) noexcept { return :: rint ( static_cast < double > ( _Left ) ); }
#line 885
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] long lrint ( _Ty _Left ) noexcept { return :: lrint ( static_cast < double > ( _Left ) ); }
#line 886
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] long long llrint ( _Ty _Left ) noexcept { return :: llrint ( static_cast < double > ( _Left ) ); }
#line 887
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double round ( _Ty _Left ) noexcept { return __round ( static_cast < double > ( _Left ) ); }
#line 888
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] long lround ( _Ty _Left ) noexcept { return :: lround ( static_cast < double > ( _Left ) ); }
#line 889
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] long long llround ( _Ty _Left ) noexcept { return :: llround ( static_cast < double > ( _Left ) ); }
#line 890
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double trunc ( _Ty _Left ) noexcept { return __trunc ( static_cast < double > ( _Left ) ); }
#line 891
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > fmod ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: fmod ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 892
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > remainder ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: remainder ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 894
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > copysign ( _Ty1 _Left, _Ty2 _Right ) noexcept { return __copysign ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 896
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > nextafter ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: nextafter ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 897
template < class _Ty, :: std :: enable_if_t < :: std :: is_integral_v < _Ty >, int > = 0 > [ [ nodiscard ] ] double nexttoward ( _Ty _Left, long double _Arg2 ) noexcept { return :: nexttoward ( static_cast < double > ( _Left ), _Arg2 ); }
#line 898
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > fdim ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: fdim ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 899
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > fmax ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: fmax ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 900
template < class _Ty1, class _Ty2, :: std :: enable_if_t < :: std :: is_arithmetic_v < _Ty1 > && :: std :: is_arithmetic_v < _Ty2 >, int > = 0 > [ [ nodiscard ] ] :: std :: _Common_float_type_t < _Ty1, _Ty2 > fmin ( _Ty1 _Left, _Ty2 _Right ) noexcept { return :: fmin ( static_cast < double > ( _Left ), static_cast < double > ( _Right ) ); }
#line 904
[[nodiscard]] inline bool isfinite(signed char) noexcept { return true; } [[nodiscard]] inline bool isfinite(unsigned char) noexcept { return true; } [[nodiscard]] inline bool isfinite(short) noexcept { return true; } [[nodiscard]] inline bool isfinite(unsigned short) noexcept { return true; } [[nodiscard]] inline bool isfinite(int) noexcept { return true; } [[nodiscard]] inline bool isfinite(unsigned) noexcept { return true; } [[nodiscard]] inline bool isfinite(long) noexcept { return true; } [[nodiscard]] inline bool isfinite(unsigned long) noexcept { return true; } [[nodiscard]] inline bool isfinite(__int64) noexcept { return true; } [[nodiscard]] inline bool isfinite(unsigned __int64) noexcept { return true; } [[nodiscard]] inline bool isfinite(bool) noexcept { return true; } [[nodiscard]] inline bool isfinite(char) noexcept { return true; } [[nodiscard]] inline bool isfinite(char16_t) noexcept { return true; } [[nodiscard]] inline bool isfinite(char32_t) noexcept { return true; } [[nodiscard]] inline bool isfinite(__wchar_t) noexcept { return true; } 
#line 905
[[nodiscard]] inline bool isinf(signed char) noexcept { return false; } [[nodiscard]] inline bool isinf(unsigned char) noexcept { return false; } [[nodiscard]] inline bool isinf(short) noexcept { return false; } [[nodiscard]] inline bool isinf(unsigned short) noexcept { return false; } [[nodiscard]] inline bool isinf(int) noexcept { return false; } [[nodiscard]] inline bool isinf(unsigned) noexcept { return false; } [[nodiscard]] inline bool isinf(long) noexcept { return false; } [[nodiscard]] inline bool isinf(unsigned long) noexcept { return false; } [[nodiscard]] inline bool isinf(__int64) noexcept { return false; } [[nodiscard]] inline bool isinf(unsigned __int64) noexcept { return false; } [[nodiscard]] inline bool isinf(bool) noexcept { return false; } [[nodiscard]] inline bool isinf(char) noexcept { return false; } [[nodiscard]] inline bool isinf(char16_t) noexcept { return false; } [[nodiscard]] inline bool isinf(char32_t) noexcept { return false; } [[nodiscard]] inline bool isinf(__wchar_t) noexcept { return false; } 
#line 906
[[nodiscard]] inline bool isnan(signed char) noexcept { return false; } [[nodiscard]] inline bool isnan(unsigned char) noexcept { return false; } [[nodiscard]] inline bool isnan(short) noexcept { return false; } [[nodiscard]] inline bool isnan(unsigned short) noexcept { return false; } [[nodiscard]] inline bool isnan(int) noexcept { return false; } [[nodiscard]] inline bool isnan(unsigned) noexcept { return false; } [[nodiscard]] inline bool isnan(long) noexcept { return false; } [[nodiscard]] inline bool isnan(unsigned long) noexcept { return false; } [[nodiscard]] inline bool isnan(__int64) noexcept { return false; } [[nodiscard]] inline bool isnan(unsigned __int64) noexcept { return false; } [[nodiscard]] inline bool isnan(bool) noexcept { return false; } [[nodiscard]] inline bool isnan(char) noexcept { return false; } [[nodiscard]] inline bool isnan(char16_t) noexcept { return false; } [[nodiscard]] inline bool isnan(char32_t) noexcept { return false; } [[nodiscard]] inline bool isnan(__wchar_t) noexcept { return false; } 
#line 925
namespace std { 
#line 926
using ::abs;
#line 927
using ::acos;
#line 928
using ::asin;
#line 929
using ::atan;
#line 930
using ::atan2;
#line 931
using ::ceil;
#line 932
using ::cos;
#line 933
using ::cosh;
#line 934
using ::exp;
#line 935
using ::fabs;
#line 936
using ::floor;
#line 937
using ::fmod;
#line 938
using ::frexp;
#line 939
using ::ldexp;
#line 940
using ::log;
#line 941
using ::log10;
#line 942
using ::modf;
#line 943
using ::pow;
#line 944
using ::sin;
#line 945
using ::sinh;
#line 946
using ::sqrt;
#line 947
using ::tan;
#line 948
using ::tanh;
#line 950
using ::acosf;
#line 951
using ::asinf;
#line 952
using ::atanf;
#line 953
using ::atan2f;
#line 954
using ::ceilf;
#line 955
using ::cosf;
#line 956
using ::coshf;
#line 957
using ::expf;
#line 958
using ::fabsf;
#line 959
using ::floorf;
#line 960
using ::fmodf;
#line 961
using ::frexpf;
#line 962
using ::ldexpf;
#line 963
using ::logf;
#line 964
using ::log10f;
#line 965
using ::modff;
#line 966
using ::powf;
#line 967
using ::sinf;
#line 968
using ::sinhf;
#line 969
using ::sqrtf;
#line 970
using ::tanf;
#line 971
using ::tanhf;
#line 973
using ::acosl;
#line 974
using ::asinl;
#line 975
using ::atanl;
#line 976
using ::atan2l;
#line 977
using ::ceill;
#line 978
using ::cosl;
#line 979
using ::coshl;
#line 980
using ::expl;
#line 981
using ::fabsl;
#line 982
using ::floorl;
#line 983
using ::fmodl;
#line 984
using ::frexpl;
#line 985
using ::ldexpl;
#line 986
using ::logl;
#line 987
using ::log10l;
#line 988
using ::modfl;
#line 989
using ::powl;
#line 990
using ::sinl;
#line 991
using ::sinhl;
#line 992
using ::sqrtl;
#line 993
using ::tanl;
#line 994
using ::tanhl;
#line 996
using ::float_t;
#line 997
using ::double_t;
#line 999
using ::acosh;
#line 1000
using ::asinh;
#line 1001
using ::atanh;
#line 1002
using ::cbrt;
#line 1003
using ::erf;
#line 1004
using ::erfc;
#line 1005
using ::expm1;
#line 1006
using ::exp2;
#line 1008
inline namespace _Binary_hypot { 
#line 1009
using ::hypot;
#line 1010
}
#line 1012
using ::ilogb;
#line 1013
using ::lgamma;
#line 1014
using ::log1p;
#line 1015
using ::log2;
#line 1016
using ::logb;
#line 1017
using ::llrint;
#line 1018
using ::lrint;
#line 1019
using ::nearbyint;
#line 1020
using ::rint;
#line 1021
using ::llround;
#line 1022
using ::lround;
#line 1023
using ::fdim;
#line 1024
using ::fma;
#line 1025
using ::fmax;
#line 1026
using ::fmin;
#line 1027
using ::round;
#line 1028
using ::trunc;
#line 1029
using ::remainder;
#line 1030
using ::remquo;
#line 1031
using ::copysign;
#line 1032
using ::nan;
#line 1033
using ::nextafter;
#line 1034
using ::scalbn;
#line 1035
using ::scalbln;
#line 1036
using ::nexttoward;
#line 1037
using ::tgamma;
#line 1039
using ::acoshf;
#line 1040
using ::asinhf;
#line 1041
using ::atanhf;
#line 1042
using ::cbrtf;
#line 1043
using ::erff;
#line 1044
using ::erfcf;
#line 1045
using ::expm1f;
#line 1046
using ::exp2f;
#line 1047
using ::hypotf;
#line 1048
using ::ilogbf;
#line 1049
using ::lgammaf;
#line 1050
using ::log1pf;
#line 1051
using ::log2f;
#line 1052
using ::logbf;
#line 1053
using ::llrintf;
#line 1054
using ::lrintf;
#line 1055
using ::nearbyintf;
#line 1056
using ::rintf;
#line 1057
using ::llroundf;
#line 1058
using ::lroundf;
#line 1059
using ::fdimf;
#line 1060
using ::fmaf;
#line 1061
using ::fmaxf;
#line 1062
using ::fminf;
#line 1063
using ::roundf;
#line 1064
using ::truncf;
#line 1065
using ::remainderf;
#line 1066
using ::remquof;
#line 1067
using ::copysignf;
#line 1068
using ::nanf;
#line 1069
using ::nextafterf;
#line 1070
using ::scalbnf;
#line 1071
using ::scalblnf;
#line 1072
using ::nexttowardf;
#line 1073
using ::tgammaf;
#line 1075
using ::acoshl;
#line 1076
using ::asinhl;
#line 1077
using ::atanhl;
#line 1078
using ::cbrtl;
#line 1079
using ::erfl;
#line 1080
using ::erfcl;
#line 1081
using ::expm1l;
#line 1082
using ::exp2l;
#line 1083
using ::hypotl;
#line 1084
using ::ilogbl;
#line 1085
using ::lgammal;
#line 1086
using ::log1pl;
#line 1087
using ::log2l;
#line 1088
using ::logbl;
#line 1089
using ::llrintl;
#line 1090
using ::lrintl;
#line 1091
using ::nearbyintl;
#line 1092
using ::rintl;
#line 1093
using ::llroundl;
#line 1094
using ::lroundl;
#line 1095
using ::fdiml;
#line 1096
using ::fmal;
#line 1097
using ::fmaxl;
#line 1098
using ::fminl;
#line 1099
using ::roundl;
#line 1100
using ::truncl;
#line 1101
using ::remainderl;
#line 1102
using ::remquol;
#line 1103
using ::copysignl;
#line 1104
using ::nanl;
#line 1105
using ::nextafterl;
#line 1106
using ::scalbnl;
#line 1107
using ::scalblnl;
#line 1108
using ::nexttowardl;
#line 1109
using ::tgammal;
#line 1111
using ::fpclassify;
#line 1112
using ::signbit;
#line 1113
using ::isfinite;
#line 1114
using ::isinf;
#line 1115
using ::isnan;
#line 1116
using ::isnormal;
#line 1117
using ::isgreater;
#line 1118
using ::isgreaterequal;
#line 1119
using ::isless;
#line 1120
using ::islessequal;
#line 1121
using ::islessgreater;
#line 1122
using ::isunordered;
#line 1123
}
#line 1705 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cmath"
#pragma warning(pop)
#pragma pack ( pop )
#line 4925 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern "C" double __cdecl _hypot(double x, double y); 
#line 4926
extern "C" float __cdecl _hypotf(float x, float y); 
#line 4936 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline bool signbit(long double) throw(); 
#line 4937
extern "C" int _ldsign(long double); 
#line 4980 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline bool signbit(double) throw(); 
#line 4981
extern "C" int _dsign(double); 
#line 5025 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline bool signbit(float) throw(); 
#line 5026
extern "C" int _fdsign(float); 
#line 5034 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isinf(long double a); 
#line 5069 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isinf(double a); 
#line 5107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isinf(float a); 
#line 5114 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isnan(long double a); 
#line 5147 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isnan(double a); 
#line 5183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isnan(float a); 
#line 5190 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isfinite(long double a); 
#line 5227 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isfinite(double a); 
#line 5263 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static __inline bool isfinite(float a); 
#line 5281 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
template< class T> extern T _Pow_int(T, int) throw(); 
#line 5282
extern inline __int64 abs(__int64) throw(); 
#line 5384 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline long __cdecl abs(long) throw(); 
#line 5388 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline float __cdecl abs(float) throw(); 
#line 5389
extern inline double __cdecl abs(double) throw(); 
#line 5392 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline float __cdecl fabs(float) throw(); 
#line 5393
extern inline float __cdecl ceil(float) throw(); 
#line 5394
extern inline float __cdecl floor(float) throw(); 
#line 5395
extern inline float __cdecl sqrt(float) throw(); 
#line 5396
extern inline float __cdecl pow(float, float) throw(); 
#line 5447 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
template< class _Ty1, class _Ty2, ::std::enable_if_t< std::is_arithmetic_v< _Ty1>  && std::is_arithmetic_v< _Ty2> , int>  > [[nodiscard]] ::std::_Common_float_type_t< _Ty1, _Ty2>  __cdecl pow(_Ty1 _Left, _Ty2 _Right) noexcept; 
#line 5454 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline float __cdecl log(float) throw(); 
#line 5455
extern inline float __cdecl log10(float) throw(); 
#line 5456
extern inline float __cdecl fmod(float, float) throw(); 
#line 5457
extern inline float __cdecl modf(float, float *) throw(); 
#line 5458
extern inline float __cdecl exp(float) throw(); 
#line 5459
extern inline float __cdecl frexp(float, int *) throw(); 
#line 5460
extern inline float __cdecl ldexp(float, int) throw(); 
#line 5461
extern inline float __cdecl asin(float) throw(); 
#line 5462
extern inline float __cdecl sin(float) throw(); 
#line 5463
extern inline float __cdecl sinh(float) throw(); 
#line 5464
extern inline float __cdecl acos(float) throw(); 
#line 5465
extern inline float __cdecl cos(float) throw(); 
#line 5466
extern inline float __cdecl cosh(float) throw(); 
#line 5467
extern inline float __cdecl atan(float) throw(); 
#line 5468
extern inline float __cdecl atan2(float, float) throw(); 
#line 5469
extern inline float __cdecl tan(float) throw(); 
#line 5470
extern inline float __cdecl tanh(float) throw(); 
#line 5696 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
extern inline float __cdecl logb(float) throw(); 
#line 5697
extern inline int __cdecl ilogb(float) throw(); 
#line 5698
extern float __cdecl scalbn(float, float) throw(); 
#line 5699
extern inline float __cdecl scalbln(float, long) throw(); 
#line 5700
extern inline float __cdecl exp2(float) throw(); 
#line 5701
extern inline float __cdecl expm1(float) throw(); 
#line 5702
extern inline float __cdecl log2(float) throw(); 
#line 5703
extern inline float __cdecl log1p(float) throw(); 
#line 5704
extern inline float __cdecl acosh(float) throw(); 
#line 5705
extern inline float __cdecl asinh(float) throw(); 
#line 5706
extern inline float __cdecl atanh(float) throw(); 
#line 5707
extern inline float __cdecl hypot(float, float) throw(); 
#line 5708
extern inline float __cdecl cbrt(float) throw(); 
#line 5709
extern inline float __cdecl erf(float) throw(); 
#line 5710
extern inline float __cdecl erfc(float) throw(); 
#line 5711
extern inline float __cdecl lgamma(float) throw(); 
#line 5712
extern inline float __cdecl tgamma(float) throw(); 
#line 5713
extern inline float __cdecl copysign(float, float) throw(); 
#line 5714
extern inline float __cdecl nextafter(float, float) throw(); 
#line 5715
extern inline float __cdecl remainder(float, float) throw(); 
#line 5716
extern inline float __cdecl remquo(float, float, int *) throw(); 
#line 5717
extern inline float __cdecl round(float) throw(); 
#line 5718
extern inline long __cdecl lround(float) throw(); 
#line 5719
extern inline __int64 __cdecl llround(float) throw(); 
#line 5720
extern inline float __cdecl trunc(float) throw(); 
#line 5721
extern inline float __cdecl rint(float) throw(); 
#line 5722
extern inline long __cdecl lrint(float) throw(); 
#line 5723
extern inline __int64 __cdecl llrint(float) throw(); 
#line 5724
extern inline float __cdecl nearbyint(float) throw(); 
#line 5725
extern inline float __cdecl fdim(float, float) throw(); 
#line 5726
extern inline float __cdecl fma(float, float, float) throw(); 
#line 5727
extern inline float __cdecl fmax(float, float) throw(); 
#line 5728
extern inline float __cdecl fmin(float, float) throw(); 
#line 5731 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
static inline float exp10(const float a); 
#line 5733
static inline float rsqrt(const float a); 
#line 5735
static inline float rcbrt(const float a); 
#line 5737
static inline float sinpi(const float a); 
#line 5739
static inline float cospi(const float a); 
#line 5741
static inline void sincospi(const float a, float *const sptr, float *const cptr); 
#line 5743
static inline void sincos(const float a, float *const sptr, float *const cptr); 
#line 5745
static inline float j0(const float a); 
#line 5747
static inline float j1(const float a); 
#line 5749
static inline float jn(const int n, const float a); 
#line 5751
static inline float y0(const float a); 
#line 5753
static inline float y1(const float a); 
#line 5755
static inline float yn(const int n, const float a); 
#line 5757
static inline float cyl_bessel_i0(const float a); 
#line 5759
static inline float cyl_bessel_i1(const float a); 
#line 5761
static inline float erfinv(const float a); 
#line 5763
static inline float erfcinv(const float a); 
#line 5765
static inline float normcdfinv(const float a); 
#line 5767
static inline float normcdf(const float a); 
#line 5769
static inline float erfcx(const float a); 
#line 5771
static inline double copysign(const double a, const float b); 
#line 5773
static inline double copysign(const float a, const double b); 
#line 5781
static inline unsigned min(const unsigned a, const unsigned b); 
#line 5789
static inline unsigned min(const int a, const unsigned b); 
#line 5797
static inline unsigned min(const unsigned a, const int b); 
#line 5805
static inline long min(const long a, const long b); 
#line 5813
static inline unsigned long min(const unsigned long a, const unsigned long b); 
#line 5821
static inline unsigned long min(const long a, const unsigned long b); 
#line 5829
static inline unsigned long min(const unsigned long a, const long b); 
#line 5837
static inline __int64 min(const __int64 a, const __int64 b); 
#line 5845
static inline unsigned __int64 min(const unsigned __int64 a, const unsigned __int64 b); 
#line 5853
static inline unsigned __int64 min(const __int64 a, const unsigned __int64 b); 
#line 5861
static inline unsigned __int64 min(const unsigned __int64 a, const __int64 b); 
#line 5872
static inline float min(const float a, const float b); 
#line 5883
static inline double min(const double a, const double b); 
#line 5893
static inline double min(const float a, const double b); 
#line 5903
static inline double min(const double a, const float b); 
#line 5911
static inline unsigned max(const unsigned a, const unsigned b); 
#line 5919
static inline unsigned max(const int a, const unsigned b); 
#line 5927
static inline unsigned max(const unsigned a, const int b); 
#line 5935
static inline long max(const long a, const long b); 
#line 5943
static inline unsigned long max(const unsigned long a, const unsigned long b); 
#line 5951
static inline unsigned long max(const long a, const unsigned long b); 
#line 5959
static inline unsigned long max(const unsigned long a, const long b); 
#line 5967
static inline __int64 max(const __int64 a, const __int64 b); 
#line 5975
static inline unsigned __int64 max(const unsigned __int64 a, const unsigned __int64 b); 
#line 5983
static inline unsigned __int64 max(const __int64 a, const unsigned __int64 b); 
#line 5991
static inline unsigned __int64 max(const unsigned __int64 a, const __int64 b); 
#line 6002
static inline float max(const float a, const float b); 
#line 6013
static inline double max(const double a, const double b); 
#line 6023
static inline double max(const float a, const double b); 
#line 6033
static inline double max(const double a, const float b); 
#line 6045
extern "C" {
#line 6046
inline void *__nv_aligned_device_malloc(size_t size, size_t align) {int volatile ___ = 1;(void)size;(void)align;::exit(___);}
#if 0
#line 6047
{ 
#line 6048
void *__nv_aligned_device_malloc_impl(size_t, size_t); 
#line 6049
return __nv_aligned_device_malloc_impl(size, align); 
#line 6050
} 
#endif
#line 6051 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.h"
}
#line 459 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isinf(const long double a) 
#line 460
{ 
#line 464 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isinf< long double> (a); 
#line 466 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 475 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isinf(const double a) 
#line 476
{ 
#line 480 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isinf< double> (a); 
#line 482 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 491 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isinf(const float a) 
#line 492
{ 
#line 496 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isinf< float> (a); 
#line 498 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 507 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isnan(const long double a) 
#line 508
{ 
#line 512 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isnan< long double> (a); 
#line 514 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 523 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isnan(const double a) 
#line 524
{ 
#line 528 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isnan< double> (a); 
#line 530 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 539 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isnan(const float a) 
#line 540
{ 
#line 544 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isnan< float> (a); 
#line 546 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 555 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isfinite(const long double a) 
#line 556
{ 
#line 560 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isfinite< long double> (a); 
#line 562 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 571 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isfinite(const double a) 
#line 572
{ 
#line 576 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isfinite< double> (a); 
#line 578 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 587 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static __inline bool isfinite(const float a) 
#line 588
{ 
#line 592 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
return isfinite< float> (a); 
#line 594 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
} 
#line 784 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static inline float exp10(const float a) 
#line 785
{ 
#line 786
return exp10f(a); 
#line 787
} 
#line 789
static inline float rsqrt(const float a) 
#line 790
{ 
#line 791
return rsqrtf(a); 
#line 792
} 
#line 794
static inline float rcbrt(const float a) 
#line 795
{ 
#line 796
return rcbrtf(a); 
#line 797
} 
#line 799
static inline float sinpi(const float a) 
#line 800
{ 
#line 801
return sinpif(a); 
#line 802
} 
#line 804
static inline float cospi(const float a) 
#line 805
{ 
#line 806
return cospif(a); 
#line 807
} 
#line 809
static inline void sincospi(const float a, float *const sptr, float *const cptr) 
#line 810
{ 
#line 811
sincospif(a, sptr, cptr); 
#line 812
} 
#line 814
static inline void sincos(const float a, float *const sptr, float *const cptr) 
#line 815
{ 
#line 816
sincosf(a, sptr, cptr); 
#line 817
} 
#line 819
static inline float j0(const float a) 
#line 820
{ 
#line 821
return j0f(a); 
#line 822
} 
#line 824
static inline float j1(const float a) 
#line 825
{ 
#line 826
return j1f(a); 
#line 827
} 
#line 829
static inline float jn(const int n, const float a) 
#line 830
{ 
#line 831
return jnf(n, a); 
#line 832
} 
#line 834
static inline float y0(const float a) 
#line 835
{ 
#line 836
return y0f(a); 
#line 837
} 
#line 839
static inline float y1(const float a) 
#line 840
{ 
#line 841
return y1f(a); 
#line 842
} 
#line 844
static inline float yn(const int n, const float a) 
#line 845
{ 
#line 846
return ynf(n, a); 
#line 847
} 
#line 849
static inline float cyl_bessel_i0(const float a) {int volatile ___ = 1;(void)a;::exit(___);}
#if 0
#line 850
{ 
#line 851
return cyl_bessel_i0f(a); 
#line 852
} 
#endif
#line 854 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static inline float cyl_bessel_i1(const float a) {int volatile ___ = 1;(void)a;::exit(___);}
#if 0
#line 855
{ 
#line 856
return cyl_bessel_i1f(a); 
#line 857
} 
#endif
#line 859 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static inline float erfinv(const float a) 
#line 860
{ 
#line 861
return erfinvf(a); 
#line 862
} 
#line 864
static inline float erfcinv(const float a) 
#line 865
{ 
#line 866
return erfcinvf(a); 
#line 867
} 
#line 869
static inline float normcdfinv(const float a) 
#line 870
{ 
#line 871
return normcdfinvf(a); 
#line 872
} 
#line 874
static inline float normcdf(const float a) 
#line 875
{ 
#line 876
return normcdff(a); 
#line 877
} 
#line 879
static inline float erfcx(const float a) 
#line 880
{ 
#line 881
return erfcxf(a); 
#line 882
} 
#line 884
static inline double copysign(const double a, const float b) 
#line 885
{ 
#line 886
return copysign(a, static_cast< double>(b)); 
#line 887
} 
#line 889
static inline double copysign(const float a, const double b) 
#line 890
{ 
#line 891
return copysign(static_cast< double>(a), b); 
#line 892
} 
#line 894
static inline unsigned min(const unsigned a, const unsigned b) 
#line 895
{ 
#line 896
return umin(a, b); 
#line 897
} 
#line 899
static inline unsigned min(const int a, const unsigned b) 
#line 900
{ 
#line 901
return umin(static_cast< unsigned>(a), b); 
#line 902
} 
#line 904
static inline unsigned min(const unsigned a, const int b) 
#line 905
{ 
#line 906
return umin(a, static_cast< unsigned>(b)); 
#line 907
} 
#line 909
static inline long min(const long a, const long b) 
#line 910
{ 
#line 911
long retval; 
#line 914
#pragma warning (push)
#pragma warning (disable: 4127)
#line 918 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(long) == sizeof(int)) { 
#line 920
#pragma warning (pop)
#line 922 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< long>(::min(static_cast< int>(a), static_cast< int>(b)))); 
#line 923
} else { 
#line 924
retval = (static_cast< long>(llmin(static_cast< __int64>(a), static_cast< __int64>(b)))); 
#line 925
}  
#line 926
return retval; 
#line 927
} 
#line 929
static inline unsigned long min(const unsigned long a, const unsigned long b) 
#line 930
{ 
#line 931
unsigned long retval; 
#line 933
#pragma warning (push)
#pragma warning (disable: 4127)
#line 936 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(unsigned long) == sizeof(unsigned)) { 
#line 938
#pragma warning (pop)
#line 940 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< unsigned long>(umin(static_cast< unsigned>(a), static_cast< unsigned>(b)))); 
#line 941
} else { 
#line 942
retval = (static_cast< unsigned long>(ullmin(static_cast< unsigned __int64>(a), static_cast< unsigned __int64>(b)))); 
#line 943
}  
#line 944
return retval; 
#line 945
} 
#line 947
static inline unsigned long min(const long a, const unsigned long b) 
#line 948
{ 
#line 949
unsigned long retval; 
#line 951
#pragma warning (push)
#pragma warning (disable: 4127)
#line 954 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(unsigned long) == sizeof(unsigned)) { 
#line 956
#pragma warning (pop)
#line 958 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< unsigned long>(umin(static_cast< unsigned>(a), static_cast< unsigned>(b)))); 
#line 959
} else { 
#line 960
retval = (static_cast< unsigned long>(ullmin(static_cast< unsigned __int64>(a), static_cast< unsigned __int64>(b)))); 
#line 961
}  
#line 962
return retval; 
#line 963
} 
#line 965
static inline unsigned long min(const unsigned long a, const long b) 
#line 966
{ 
#line 967
unsigned long retval; 
#line 969
#pragma warning (push)
#pragma warning (disable: 4127)
#line 972 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(unsigned long) == sizeof(unsigned)) { 
#line 974
#pragma warning (pop)
#line 976 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< unsigned long>(umin(static_cast< unsigned>(a), static_cast< unsigned>(b)))); 
#line 977
} else { 
#line 978
retval = (static_cast< unsigned long>(ullmin(static_cast< unsigned __int64>(a), static_cast< unsigned __int64>(b)))); 
#line 979
}  
#line 980
return retval; 
#line 981
} 
#line 983
static inline __int64 min(const __int64 a, const __int64 b) 
#line 984
{ 
#line 985
return llmin(a, b); 
#line 986
} 
#line 988
static inline unsigned __int64 min(const unsigned __int64 a, const unsigned __int64 b) 
#line 989
{ 
#line 990
return ullmin(a, b); 
#line 991
} 
#line 993
static inline unsigned __int64 min(const __int64 a, const unsigned __int64 b) 
#line 994
{ 
#line 995
return ullmin(static_cast< unsigned __int64>(a), b); 
#line 996
} 
#line 998
static inline unsigned __int64 min(const unsigned __int64 a, const __int64 b) 
#line 999
{ 
#line 1000
return ullmin(a, static_cast< unsigned __int64>(b)); 
#line 1001
} 
#line 1003
static inline float min(const float a, const float b) 
#line 1004
{ 
#line 1005
return fminf(a, b); 
#line 1006
} 
#line 1008
static inline double min(const double a, const double b) 
#line 1009
{ 
#line 1010
return fmin(a, b); 
#line 1011
} 
#line 1013
static inline double min(const float a, const double b) 
#line 1014
{ 
#line 1015
return fmin(static_cast< double>(a), b); 
#line 1016
} 
#line 1018
static inline double min(const double a, const float b) 
#line 1019
{ 
#line 1020
return fmin(a, static_cast< double>(b)); 
#line 1021
} 
#line 1023
static inline unsigned max(const unsigned a, const unsigned b) 
#line 1024
{ 
#line 1025
return umax(a, b); 
#line 1026
} 
#line 1028
static inline unsigned max(const int a, const unsigned b) 
#line 1029
{ 
#line 1030
return umax(static_cast< unsigned>(a), b); 
#line 1031
} 
#line 1033
static inline unsigned max(const unsigned a, const int b) 
#line 1034
{ 
#line 1035
return umax(a, static_cast< unsigned>(b)); 
#line 1036
} 
#line 1038
static inline long max(const long a, const long b) 
#line 1039
{ 
#line 1040
long retval; 
#line 1043
#pragma warning (push)
#pragma warning (disable: 4127)
#line 1046 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(long) == sizeof(int)) { 
#line 1048
#pragma warning (pop)
#line 1050 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< long>(::max(static_cast< int>(a), static_cast< int>(b)))); 
#line 1051
} else { 
#line 1052
retval = (static_cast< long>(llmax(static_cast< __int64>(a), static_cast< __int64>(b)))); 
#line 1053
}  
#line 1054
return retval; 
#line 1055
} 
#line 1057
static inline unsigned long max(const unsigned long a, const unsigned long b) 
#line 1058
{ 
#line 1059
unsigned long retval; 
#line 1061
#pragma warning (push)
#pragma warning (disable: 4127)
#line 1064 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(unsigned long) == sizeof(unsigned)) { 
#line 1066
#pragma warning (pop)
#line 1068 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< unsigned long>(umax(static_cast< unsigned>(a), static_cast< unsigned>(b)))); 
#line 1069
} else { 
#line 1070
retval = (static_cast< unsigned long>(ullmax(static_cast< unsigned __int64>(a), static_cast< unsigned __int64>(b)))); 
#line 1071
}  
#line 1072
return retval; 
#line 1073
} 
#line 1075
static inline unsigned long max(const long a, const unsigned long b) 
#line 1076
{ 
#line 1077
unsigned long retval; 
#line 1079
#pragma warning (push)
#pragma warning (disable: 4127)
#line 1082 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(unsigned long) == sizeof(unsigned)) { 
#line 1084
#pragma warning (pop)
#line 1086 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< unsigned long>(umax(static_cast< unsigned>(a), static_cast< unsigned>(b)))); 
#line 1087
} else { 
#line 1088
retval = (static_cast< unsigned long>(ullmax(static_cast< unsigned __int64>(a), static_cast< unsigned __int64>(b)))); 
#line 1089
}  
#line 1090
return retval; 
#line 1091
} 
#line 1093
static inline unsigned long max(const unsigned long a, const long b) 
#line 1094
{ 
#line 1095
unsigned long retval; 
#line 1097
#pragma warning (push)
#pragma warning (disable: 4127)
#line 1100 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
if (sizeof(unsigned long) == sizeof(unsigned)) { 
#line 1102
#pragma warning (pop)
#line 1104 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
retval = (static_cast< unsigned long>(umax(static_cast< unsigned>(a), static_cast< unsigned>(b)))); 
#line 1105
} else { 
#line 1106
retval = (static_cast< unsigned long>(ullmax(static_cast< unsigned __int64>(a), static_cast< unsigned __int64>(b)))); 
#line 1107
}  
#line 1108
return retval; 
#line 1109
} 
#line 1111
static inline __int64 max(const __int64 a, const __int64 b) 
#line 1112
{ 
#line 1113
return llmax(a, b); 
#line 1114
} 
#line 1116
static inline unsigned __int64 max(const unsigned __int64 a, const unsigned __int64 b) 
#line 1117
{ 
#line 1118
return ullmax(a, b); 
#line 1119
} 
#line 1121
static inline unsigned __int64 max(const __int64 a, const unsigned __int64 b) 
#line 1122
{ 
#line 1123
return ullmax(static_cast< unsigned __int64>(a), b); 
#line 1124
} 
#line 1126
static inline unsigned __int64 max(const unsigned __int64 a, const __int64 b) 
#line 1127
{ 
#line 1128
return ullmax(a, static_cast< unsigned __int64>(b)); 
#line 1129
} 
#line 1131
static inline float max(const float a, const float b) 
#line 1132
{ 
#line 1133
return fmaxf(a, b); 
#line 1134
} 
#line 1136
static inline double max(const double a, const double b) 
#line 1137
{ 
#line 1138
return fmax(a, b); 
#line 1139
} 
#line 1141
static inline double max(const float a, const double b) 
#line 1142
{ 
#line 1143
return fmax(static_cast< double>(a), b); 
#line 1144
} 
#line 1146
static inline double max(const double a, const float b) 
#line 1147
{ 
#line 1148
return fmax(a, static_cast< double>(b)); 
#line 1149
} 
#line 1155
#pragma warning (push)
#pragma warning (disable : 4211)
#line 1161 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\math_functions.hpp"
static inline int min(const int a, const int b) 
#line 1162
{ 
#line 1163
if (a < b) { return a; }  
#line 1164
return b; 
#line 1165
} 
#line 1167
static inline unsigned umin(const unsigned a, const unsigned b) 
#line 1168
{ 
#line 1169
if (a < b) { return a; }  
#line 1170
return b; 
#line 1171
} 
#line 1173
static inline __int64 llmin(const __int64 a, const __int64 b) 
#line 1174
{ 
#line 1175
if (a < b) { return a; }  
#line 1176
return b; 
#line 1177
} 
#line 1179
static inline unsigned __int64 ullmin(const unsigned __int64 a, const unsigned __int64 
#line 1180
b) 
#line 1181
{ 
#line 1182
if (a < b) { return a; }  
#line 1183
return b; 
#line 1184
} 
#line 1186
static inline int max(const int a, const int b) 
#line 1187
{ 
#line 1188
if (a > b) { return a; }  
#line 1189
return b; 
#line 1190
} 
#line 1192
static inline unsigned umax(const unsigned a, const unsigned b) 
#line 1193
{ 
#line 1194
if (a > b) { return a; }  
#line 1195
return b; 
#line 1196
} 
#line 1198
static inline __int64 llmax(const __int64 a, const __int64 b) 
#line 1199
{ 
#line 1200
if (a > b) { return a; }  
#line 1201
return b; 
#line 1202
} 
#line 1204
static inline unsigned __int64 ullmax(const unsigned __int64 a, const unsigned __int64 
#line 1205
b) 
#line 1206
{ 
#line 1207
if (a > b) { return a; }  
#line 1208
return b; 
#line 1209
} 
#line 1212
#pragma warning (pop)
#line 95 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/device_functions.h"
extern "C" {
#line 2505 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/device_functions.h"
static __inline int __vimax_s32_relu(const int a, const int b); 
#line 2517
static __inline unsigned __vimax_s16x2_relu(const unsigned a, const unsigned b); 
#line 2526
static __inline int __vimin_s32_relu(const int a, const int b); 
#line 2538
static __inline unsigned __vimin_s16x2_relu(const unsigned a, const unsigned b); 
#line 2547
static __inline int __vimax3_s32(const int a, const int b, const int c); 
#line 2559
static __inline unsigned __vimax3_s16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2568
static __inline unsigned __vimax3_u32(const unsigned a, const unsigned b, const unsigned c); 
#line 2580
static __inline unsigned __vimax3_u16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2589
static __inline int __vimin3_s32(const int a, const int b, const int c); 
#line 2601
static __inline unsigned __vimin3_s16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2610
static __inline unsigned __vimin3_u32(const unsigned a, const unsigned b, const unsigned c); 
#line 2622
static __inline unsigned __vimin3_u16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2631
static __inline int __vimax3_s32_relu(const int a, const int b, const int c); 
#line 2643
static __inline unsigned __vimax3_s16x2_relu(const unsigned a, const unsigned b, const unsigned c); 
#line 2652
static __inline int __vimin3_s32_relu(const int a, const int b, const int c); 
#line 2664
static __inline unsigned __vimin3_s16x2_relu(const unsigned a, const unsigned b, const unsigned c); 
#line 2673
static __inline int __viaddmax_s32(const int a, const int b, const int c); 
#line 2685
static __inline unsigned __viaddmax_s16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2694
static __inline unsigned __viaddmax_u32(const unsigned a, const unsigned b, const unsigned c); 
#line 2706
static __inline unsigned __viaddmax_u16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2715
static __inline int __viaddmin_s32(const int a, const int b, const int c); 
#line 2727
static __inline unsigned __viaddmin_s16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2736
static __inline unsigned __viaddmin_u32(const unsigned a, const unsigned b, const unsigned c); 
#line 2748
static __inline unsigned __viaddmin_u16x2(const unsigned a, const unsigned b, const unsigned c); 
#line 2758
static __inline int __viaddmax_s32_relu(const int a, const int b, const int c); 
#line 2770
static __inline unsigned __viaddmax_s16x2_relu(const unsigned a, const unsigned b, const unsigned c); 
#line 2780
static __inline int __viaddmin_s32_relu(const int a, const int b, const int c); 
#line 2792
static __inline unsigned __viaddmin_s16x2_relu(const unsigned a, const unsigned b, const unsigned c); 
#line 2801
static __inline int __vibmax_s32(const int a, const int b, bool *const pred); 
#line 2810
static __inline unsigned __vibmax_u32(const unsigned a, const unsigned b, bool *const pred); 
#line 2819
static __inline int __vibmin_s32(const int a, const int b, bool *const pred); 
#line 2828
static __inline unsigned __vibmin_u32(const unsigned a, const unsigned b, bool *const pred); 
#line 2842
static __inline unsigned __vibmax_s16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo); 
#line 2856
static __inline unsigned __vibmax_u16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo); 
#line 2870
static __inline unsigned __vibmin_s16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo); 
#line 2884
static __inline unsigned __vibmin_u16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo); 
#line 2891
}
#line 117 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
static short __internal_cast_u2s(unsigned short x) 
#line 118
{ 
#line 119
short res; 
#line 121
(void)memcpy(&res, &x, sizeof x); 
#line 125 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 126
} 
#line 129 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
static __inline int __vimax_s32_relu(const int a, const int b) { 
#line 136
int ans = max(a, b); 
#line 138
return (ans > 0) ? ans : 0; 
#line 140 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 142
static __inline unsigned __vimax_s16x2_relu(const unsigned a, const unsigned b) { 
#line 143
unsigned res; 
#line 151 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 152
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 154
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 155
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 158
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 159
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 161
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 162
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 165
int ansI_lo = max(aS_lo, bS_lo); 
#line 166
int ansI_hi = max(aS_hi, bS_hi); 
#line 169
if (ansI_lo < 0) { ansI_lo = 0; }  
#line 170
if (ansI_hi < 0) { ansI_hi = 0; }  
#line 173
unsigned ansU_lo = (unsigned)ansI_lo; 
#line 174
unsigned ansU_hi = (unsigned)ansI_hi; 
#line 177
res = (ansU_lo | (ansU_hi << 16)); 
#line 180 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 181
} 
#line 183
static __inline int __vimin_s32_relu(const int a, const int b) { 
#line 190
int ans = min(a, b); 
#line 192
return (ans > 0) ? ans : 0; 
#line 194 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 196
static __inline unsigned __vimin_s16x2_relu(const unsigned a, const unsigned b) { 
#line 197
unsigned res; 
#line 205 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 206
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 208
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 209
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 212
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 213
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 215
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 216
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 219
int ansI_lo = min(aS_lo, bS_lo); 
#line 220
int ansI_hi = min(aS_hi, bS_hi); 
#line 223
if (ansI_lo < 0) { ansI_lo = 0; }  
#line 224
if (ansI_hi < 0) { ansI_hi = 0; }  
#line 227
unsigned ansU_lo = (unsigned)ansI_lo; 
#line 228
unsigned ansU_hi = (unsigned)ansI_hi; 
#line 231
res = (ansU_lo | (ansU_hi << 16)); 
#line 234 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 235
} 
#line 237
static __inline int __vimax3_s32(const int a, const int b, const int c) { 
#line 247 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return max(max(a, b), c); 
#line 249 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 251
static __inline unsigned __vimax3_s16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 252
unsigned res; 
#line 263 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 264
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 266
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 267
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 269
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 270
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 273
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 274
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 276
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 277
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 279
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 280
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 283
unsigned ansU_lo = (unsigned)max(max(aS_lo, bS_lo), cS_lo); 
#line 284
unsigned ansU_hi = (unsigned)max(max(aS_hi, bS_hi), cS_hi); 
#line 287
res = ((ansU_lo & 65535U) | (ansU_hi << 16)); 
#line 289 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 290
} 
#line 292
static __inline unsigned __vimax3_u32(const unsigned a, const unsigned b, const unsigned c) { 
#line 302 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return max(max(a, b), c); 
#line 304 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 306
static __inline unsigned __vimax3_u16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 307
unsigned res; 
#line 318 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 319
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 321
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 322
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 324
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 325
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 328
unsigned short ansU_lo = (unsigned short)max(max(aU_lo, bU_lo), cU_lo); 
#line 329
unsigned short ansU_hi = (unsigned short)max(max(aU_hi, bU_hi), cU_hi); 
#line 332
res = (((unsigned)ansU_lo) | (((unsigned)ansU_hi) << 16)); 
#line 335 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 336
} 
#line 338
static __inline int __vimin3_s32(const int a, const int b, const int c) { 
#line 348 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return min(min(a, b), c); 
#line 350 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 352
static __inline unsigned __vimin3_s16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 353
unsigned res; 
#line 364 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 365
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 367
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 368
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 370
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 371
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 374
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 375
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 377
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 378
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 380
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 381
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 384
unsigned ansU_lo = (unsigned)min(min(aS_lo, bS_lo), cS_lo); 
#line 385
unsigned ansU_hi = (unsigned)min(min(aS_hi, bS_hi), cS_hi); 
#line 388
res = ((ansU_lo & 65535U) | (ansU_hi << 16)); 
#line 391 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 392
} 
#line 394
static __inline unsigned __vimin3_u32(const unsigned a, const unsigned b, const unsigned c) { 
#line 404 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return min(min(a, b), c); 
#line 406 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 408
static __inline unsigned __vimin3_u16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 409
unsigned res; 
#line 420 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 421
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 423
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 424
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 426
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 427
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 430
unsigned short ansU_lo = (unsigned short)min(min(aU_lo, bU_lo), cU_lo); 
#line 431
unsigned short ansU_hi = (unsigned short)min(min(aU_hi, bU_hi), cU_hi); 
#line 434
res = (((unsigned)ansU_lo) | (((unsigned)ansU_hi) << 16)); 
#line 437 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 438
} 
#line 440
static __inline int __vimax3_s32_relu(const int a, const int b, const int c) { 
#line 450 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
int ans = max(max(a, b), c); 
#line 452
return (ans > 0) ? ans : 0; 
#line 454 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 456
static __inline unsigned __vimax3_s16x2_relu(const unsigned a, const unsigned b, const unsigned c) { 
#line 457
unsigned res; 
#line 468 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 469
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 471
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 472
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 474
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 475
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 478
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 479
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 481
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 482
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 484
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 485
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 488
unsigned ansU_lo = (unsigned)max(0, max(max(aS_lo, bS_lo), cS_lo)); 
#line 489
unsigned ansU_hi = (unsigned)max(0, max(max(aS_hi, bS_hi), cS_hi)); 
#line 492
res = (ansU_lo | (ansU_hi << 16)); 
#line 495 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 496
} 
#line 498
static __inline int __vimin3_s32_relu(const int a, const int b, const int c) { 
#line 508 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
int ans = min(min(a, b), c); 
#line 510
return (ans > 0) ? ans : 0; 
#line 512 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 514
static __inline unsigned __vimin3_s16x2_relu(const unsigned a, const unsigned b, const unsigned c) { 
#line 515
unsigned res; 
#line 526 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 527
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 529
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 530
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 532
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 533
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 536
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 537
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 539
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 540
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 542
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 543
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 546
unsigned ansU_lo = (unsigned)max(0, min(min(aS_lo, bS_lo), cS_lo)); 
#line 547
unsigned ansU_hi = (unsigned)max(0, min(min(aS_hi, bS_hi), cS_hi)); 
#line 550
res = (ansU_lo | (ansU_hi << 16)); 
#line 554 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 555
} 
#line 557
static __inline int __viaddmax_s32(const int a, const int b, const int c) { 
#line 567 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return max(a + b, c); 
#line 569 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 571
static __inline unsigned __viaddmax_s16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 572
unsigned res; 
#line 583 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 584
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 586
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 587
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 589
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 590
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 592
aU_lo += bU_lo; 
#line 593
aU_hi += bU_hi; 
#line 596
short sS_lo = __internal_cast_u2s(aU_lo); 
#line 597
short sS_hi = __internal_cast_u2s(aU_hi); 
#line 599
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 600
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 603
unsigned ansU_lo = (unsigned)max(sS_lo, cS_lo); 
#line 604
unsigned ansU_hi = (unsigned)max(sS_hi, cS_hi); 
#line 607
res = ((ansU_lo & 65535U) | (ansU_hi << 16)); 
#line 610 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 611
} 
#line 613
static __inline unsigned __viaddmax_u32(const unsigned a, const unsigned b, const unsigned c) { 
#line 623 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return max(a + b, c); 
#line 625 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 627
static __inline unsigned __viaddmax_u16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 628
unsigned res; 
#line 639 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 640
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 642
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 643
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 645
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 646
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 649
unsigned short ansU_lo = (unsigned short)max((unsigned short)(aU_lo + bU_lo), cU_lo); 
#line 650
unsigned short ansU_hi = (unsigned short)max((unsigned short)(aU_hi + bU_hi), cU_hi); 
#line 653
res = (((unsigned)ansU_lo) | (((unsigned)ansU_hi) << 16)); 
#line 656 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 657
} 
#line 659
static __inline int __viaddmin_s32(const int a, const int b, const int c) { 
#line 669 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return min(a + b, c); 
#line 671 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 673
static __inline unsigned __viaddmin_s16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 674
unsigned res; 
#line 685 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 686
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 688
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 689
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 691
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 692
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 694
aU_lo += bU_lo; 
#line 695
aU_hi += bU_hi; 
#line 698
short sS_lo = __internal_cast_u2s(aU_lo); 
#line 699
short sS_hi = __internal_cast_u2s(aU_hi); 
#line 701
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 702
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 705
unsigned ansU_lo = (unsigned)min(sS_lo, cS_lo); 
#line 706
unsigned ansU_hi = (unsigned)min(sS_hi, cS_hi); 
#line 709
res = ((ansU_lo & 65535U) | (ansU_hi << 16)); 
#line 712 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 713
} 
#line 715
static __inline unsigned __viaddmin_u32(const unsigned a, const unsigned b, const unsigned c) { 
#line 725 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return min(a + b, c); 
#line 727 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 729
static __inline unsigned __viaddmin_u16x2(const unsigned a, const unsigned b, const unsigned c) { 
#line 730
unsigned res; 
#line 741 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 742
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 744
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 745
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 747
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 748
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 751
unsigned short ansU_lo = (unsigned short)min((unsigned short)(aU_lo + bU_lo), cU_lo); 
#line 752
unsigned short ansU_hi = (unsigned short)min((unsigned short)(aU_hi + bU_hi), cU_hi); 
#line 755
res = (((unsigned)ansU_lo) | (((unsigned)ansU_hi) << 16)); 
#line 758 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 759
} 
#line 761
static __inline int __viaddmax_s32_relu(const int a, const int b, const int c) { 
#line 771 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
int ans = max(a + b, c); 
#line 773
return (ans > 0) ? ans : 0; 
#line 775 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 777
static __inline unsigned __viaddmax_s16x2_relu(const unsigned a, const unsigned b, const unsigned c) { 
#line 778
unsigned res; 
#line 789 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 790
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 792
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 793
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 795
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 796
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 798
aU_lo += bU_lo; 
#line 799
aU_hi += bU_hi; 
#line 802
short sS_lo = __internal_cast_u2s(aU_lo); 
#line 803
short sS_hi = __internal_cast_u2s(aU_hi); 
#line 805
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 806
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 809
unsigned ansU_lo = (unsigned)max(0, max(sS_lo, cS_lo)); 
#line 810
unsigned ansU_hi = (unsigned)max(0, max(sS_hi, cS_hi)); 
#line 813
res = (ansU_lo | (ansU_hi << 16)); 
#line 816 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 817
} 
#line 819
static __inline int __viaddmin_s32_relu(const int a, const int b, const int c) { 
#line 829 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
int ans = min(a + b, c); 
#line 831
return (ans > 0) ? ans : 0; 
#line 833 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 835
static __inline unsigned __viaddmin_s16x2_relu(const unsigned a, const unsigned b, const unsigned c) { 
#line 836
unsigned res; 
#line 847 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 848
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 850
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 851
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 853
unsigned short cU_lo = (unsigned short)(c & 65535U); 
#line 854
unsigned short cU_hi = (unsigned short)(c >> 16); 
#line 856
aU_lo += bU_lo; 
#line 857
aU_hi += bU_hi; 
#line 860
short sS_lo = __internal_cast_u2s(aU_lo); 
#line 861
short sS_hi = __internal_cast_u2s(aU_hi); 
#line 863
short cS_lo = __internal_cast_u2s(cU_lo); 
#line 864
short cS_hi = __internal_cast_u2s(cU_hi); 
#line 867
unsigned ansU_lo = (unsigned)max(0, min(sS_lo, cS_lo)); 
#line 868
unsigned ansU_hi = (unsigned)max(0, min(sS_hi, cS_hi)); 
#line 871
res = (ansU_lo | (ansU_hi << 16)); 
#line 874 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
return res; 
#line 875
} 
#line 879
static __inline int __vibmax_s32(const int a, const int b, bool *const pred) { 
#line 893
int ans = max(a, b); 
#line 895
(*pred) = (a >= b); 
#line 896
return ans; 
#line 898 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 900
static __inline unsigned __vibmax_u32(const unsigned a, const unsigned b, bool *const pred) { 
#line 914
unsigned ans = max(a, b); 
#line 916
(*pred) = (a >= b); 
#line 917
return ans; 
#line 919 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 922
static __inline int __vibmin_s32(const int a, const int b, bool *const pred) { 
#line 936
int ans = min(a, b); 
#line 938
(*pred) = (a <= b); 
#line 939
return ans; 
#line 941 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 944
static __inline unsigned __vibmin_u32(const unsigned a, const unsigned b, bool *const pred) { 
#line 958
unsigned ans = min(a, b); 
#line 960
(*pred) = (a <= b); 
#line 961
return ans; 
#line 963 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 965
static __inline unsigned __vibmax_s16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo) { 
#line 987
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 988
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 990
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 991
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 994
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 995
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 997
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 998
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 1001
unsigned ansU_lo = (unsigned)max(aS_lo, bS_lo); 
#line 1002
unsigned ansU_hi = (unsigned)max(aS_hi, bS_hi); 
#line 1004
(*pred_hi) = (aS_hi >= bS_hi); 
#line 1005
(*pred_lo) = (aS_lo >= bS_lo); 
#line 1008
unsigned ans = (ansU_lo & 65535U) | (ansU_hi << 16); 
#line 1010
return ans; 
#line 1012 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 1014
static __inline unsigned __vibmax_u16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo) { 
#line 1036
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 1037
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 1039
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 1040
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 1043
unsigned short ansU_lo = (unsigned short)max(aU_lo, bU_lo); 
#line 1044
unsigned short ansU_hi = (unsigned short)max(aU_hi, bU_hi); 
#line 1046
(*pred_hi) = (aU_hi >= bU_hi); 
#line 1047
(*pred_lo) = (aU_lo >= bU_lo); 
#line 1050
unsigned ans = ((unsigned)ansU_lo) | (((unsigned)ansU_hi) << 16); 
#line 1052
return ans; 
#line 1054 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 1056
static __inline unsigned __vibmin_s16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo) { 
#line 1078
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 1079
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 1081
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 1082
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 1085
short aS_lo = __internal_cast_u2s(aU_lo); 
#line 1086
short aS_hi = __internal_cast_u2s(aU_hi); 
#line 1088
short bS_lo = __internal_cast_u2s(bU_lo); 
#line 1089
short bS_hi = __internal_cast_u2s(bU_hi); 
#line 1092
unsigned ansU_lo = (unsigned)min(aS_lo, bS_lo); 
#line 1093
unsigned ansU_hi = (unsigned)min(aS_hi, bS_hi); 
#line 1095
(*pred_hi) = (aS_hi <= bS_hi); 
#line 1096
(*pred_lo) = (aS_lo <= bS_lo); 
#line 1099
unsigned ans = (ansU_lo & 65535U) | (ansU_hi << 16); 
#line 1101
return ans; 
#line 1103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 1105
static __inline unsigned __vibmin_u16x2(const unsigned a, const unsigned b, bool *const pred_hi, bool *const pred_lo) { 
#line 1127
unsigned short aU_lo = (unsigned short)(a & 65535U); 
#line 1128
unsigned short aU_hi = (unsigned short)(a >> 16); 
#line 1130
unsigned short bU_lo = (unsigned short)(b & 65535U); 
#line 1131
unsigned short bU_hi = (unsigned short)(b >> 16); 
#line 1134
unsigned short ansU_lo = (unsigned short)min(aU_lo, bU_lo); 
#line 1135
unsigned short ansU_hi = (unsigned short)min(aU_hi, bU_hi); 
#line 1137
(*pred_hi) = (aU_hi <= bU_hi); 
#line 1138
(*pred_lo) = (aU_lo <= bU_lo); 
#line 1141
unsigned ans = ((unsigned)ansU_lo) | (((unsigned)ansU_hi) << 16); 
#line 1143
return ans; 
#line 1145 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_functions.hpp"
} 
#line 89 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicAdd(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 89
{ } 
#endif
#line 91 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicAdd(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 91
{ } 
#endif
#line 93 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicSub(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 93
{ } 
#endif
#line 95 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicSub(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 95
{ } 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicExch(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 97
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicExch(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline float atomicExch(float *address, float val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 101
{ } 
#endif
#line 103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicMin(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 103
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicMin(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicMax(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 107
{ } 
#endif
#line 109 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicMax(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 109
{ } 
#endif
#line 111 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicInc(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 111
{ } 
#endif
#line 113 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicDec(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 113
{ } 
#endif
#line 115 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicAnd(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 115
{ } 
#endif
#line 117 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicAnd(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 117
{ } 
#endif
#line 119 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicOr(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 119
{ } 
#endif
#line 121 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicOr(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 121
{ } 
#endif
#line 123 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicXor(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 123
{ } 
#endif
#line 125 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicXor(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 125
{ } 
#endif
#line 127 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline int atomicCAS(int *address, int compare, int val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 127
{ } 
#endif
#line 129 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned atomicCAS(unsigned *address, unsigned compare, unsigned val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 129
{ } 
#endif
#line 156 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
extern "C" {
#line 160
}
#line 169
static __inline unsigned __int64 atomicAdd(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 169
{ } 
#endif
#line 171 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned __int64 atomicExch(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 171
{ } 
#endif
#line 173 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
static __inline unsigned __int64 atomicCAS(unsigned __int64 *address, unsigned __int64 compare, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 173
{ } 
#endif
#line 175 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
__declspec(deprecated("__any() is deprecated in favor of __any_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to suppr" "ess this warning).")) static __inline bool any(bool cond) {int volatile ___ = 1;(void)cond;::exit(___);}
#if 0
#line 175
{ } 
#endif
#line 177 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_atomic_functions.h"
__declspec(deprecated("__all() is deprecated in favor of __all_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to suppr" "ess this warning).")) static __inline bool all(bool cond) {int volatile ___ = 1;(void)cond;::exit(___);}
#if 0
#line 177
{ } 
#endif
#line 90 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.h"
extern "C" {
#line 1142
}
#line 1150
static __inline double fma(double a, double b, double c, cudaRoundMode mode); 
#line 1154
static __inline double dmul(double a, double b, cudaRoundMode mode = cudaRoundNearest); 
#line 1156
static __inline double dadd(double a, double b, cudaRoundMode mode = cudaRoundNearest); 
#line 1158
static __inline double dsub(double a, double b, cudaRoundMode mode = cudaRoundNearest); 
#line 1160
static __inline int double2int(double a, cudaRoundMode mode = cudaRoundZero); 
#line 1162
static __inline unsigned double2uint(double a, cudaRoundMode mode = cudaRoundZero); 
#line 1164
static __inline __int64 double2ll(double a, cudaRoundMode mode = cudaRoundZero); 
#line 1166
static __inline unsigned __int64 double2ull(double a, cudaRoundMode mode = cudaRoundZero); 
#line 1168
static __inline double ll2double(__int64 a, cudaRoundMode mode = cudaRoundNearest); 
#line 1170
static __inline double ull2double(unsigned __int64 a, cudaRoundMode mode = cudaRoundNearest); 
#line 1172
static __inline double int2double(int a, cudaRoundMode mode = cudaRoundNearest); 
#line 1174
static __inline double uint2double(unsigned a, cudaRoundMode mode = cudaRoundNearest); 
#line 1176
static __inline double float2double(float a, cudaRoundMode mode = cudaRoundNearest); 
#line 93 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double fma(double a, double b, double c, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)b;(void)c;(void)mode;::exit(___);}
#if 0
#line 94
{ 
#line 95
return (mode == (cudaRoundZero)) ? __fma_rz(a, b, c) : ((mode == (cudaRoundPosInf)) ? __fma_ru(a, b, c) : ((mode == (cudaRoundMinInf)) ? __fma_rd(a, b, c) : __fma_rn(a, b, c))); 
#line 99
} 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double dmul(double a, double b, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)b;(void)mode;::exit(___);}
#if 0
#line 102
{ 
#line 103
return (mode == (cudaRoundZero)) ? __dmul_rz(a, b) : ((mode == (cudaRoundPosInf)) ? __dmul_ru(a, b) : ((mode == (cudaRoundMinInf)) ? __dmul_rd(a, b) : __dmul_rn(a, b))); 
#line 107
} 
#endif
#line 109 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double dadd(double a, double b, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)b;(void)mode;::exit(___);}
#if 0
#line 110
{ 
#line 111
return (mode == (cudaRoundZero)) ? __dadd_rz(a, b) : ((mode == (cudaRoundPosInf)) ? __dadd_ru(a, b) : ((mode == (cudaRoundMinInf)) ? __dadd_rd(a, b) : __dadd_rn(a, b))); 
#line 115
} 
#endif
#line 117 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double dsub(double a, double b, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)b;(void)mode;::exit(___);}
#if 0
#line 118
{ 
#line 119
return (mode == (cudaRoundZero)) ? __dsub_rz(a, b) : ((mode == (cudaRoundPosInf)) ? __dsub_ru(a, b) : ((mode == (cudaRoundMinInf)) ? __dsub_rd(a, b) : __dsub_rn(a, b))); 
#line 123
} 
#endif
#line 125 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline int double2int(double a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 126
{ 
#line 127
return (mode == (cudaRoundNearest)) ? __double2int_rn(a) : ((mode == (cudaRoundPosInf)) ? __double2int_ru(a) : ((mode == (cudaRoundMinInf)) ? __double2int_rd(a) : __double2int_rz(a))); 
#line 131
} 
#endif
#line 133 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline unsigned double2uint(double a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 134
{ 
#line 135
return (mode == (cudaRoundNearest)) ? __double2uint_rn(a) : ((mode == (cudaRoundPosInf)) ? __double2uint_ru(a) : ((mode == (cudaRoundMinInf)) ? __double2uint_rd(a) : __double2uint_rz(a))); 
#line 139
} 
#endif
#line 141 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline __int64 double2ll(double a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 142
{ 
#line 143
return (mode == (cudaRoundNearest)) ? __double2ll_rn(a) : ((mode == (cudaRoundPosInf)) ? __double2ll_ru(a) : ((mode == (cudaRoundMinInf)) ? __double2ll_rd(a) : __double2ll_rz(a))); 
#line 147
} 
#endif
#line 149 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline unsigned __int64 double2ull(double a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 150
{ 
#line 151
return (mode == (cudaRoundNearest)) ? __double2ull_rn(a) : ((mode == (cudaRoundPosInf)) ? __double2ull_ru(a) : ((mode == (cudaRoundMinInf)) ? __double2ull_rd(a) : __double2ull_rz(a))); 
#line 155
} 
#endif
#line 157 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double ll2double(__int64 a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 158
{ 
#line 159
return (mode == (cudaRoundZero)) ? __ll2double_rz(a) : ((mode == (cudaRoundPosInf)) ? __ll2double_ru(a) : ((mode == (cudaRoundMinInf)) ? __ll2double_rd(a) : __ll2double_rn(a))); 
#line 163
} 
#endif
#line 165 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double ull2double(unsigned __int64 a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 166
{ 
#line 167
return (mode == (cudaRoundZero)) ? __ull2double_rz(a) : ((mode == (cudaRoundPosInf)) ? __ull2double_ru(a) : ((mode == (cudaRoundMinInf)) ? __ull2double_rd(a) : __ull2double_rn(a))); 
#line 171
} 
#endif
#line 173 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double int2double(int a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 174
{ 
#line 175
return (double)a; 
#line 176
} 
#endif
#line 178 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double uint2double(unsigned a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 179
{ 
#line 180
return (double)a; 
#line 181
} 
#endif
#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\device_double_functions.hpp"
static __inline double float2double(float a, cudaRoundMode mode) {int volatile ___ = 1;(void)a;(void)mode;::exit(___);}
#if 0
#line 184
{ 
#line 185
return (double)a; 
#line 186
} 
#endif
#line 88 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_atomic_functions.h"
static __inline float atomicAdd(float *address, float val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 88
{ } 
#endif
#line 89 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline __int64 atomicMin(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 89
{ } 
#endif
#line 91 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline __int64 atomicMax(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 91
{ } 
#endif
#line 93 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline __int64 atomicAnd(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 93
{ } 
#endif
#line 95 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline __int64 atomicOr(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 95
{ } 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline __int64 atomicXor(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 97
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline unsigned __int64 atomicMin(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline unsigned __int64 atomicMax(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 101
{ } 
#endif
#line 103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline unsigned __int64 atomicAnd(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 103
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline unsigned __int64 atomicOr(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_atomic_functions.h"
static __inline unsigned __int64 atomicXor(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 107
{ } 
#endif
#line 93 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline double atomicAdd(double *address, double val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 93
{ } 
#endif
#line 96 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicAdd_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 96
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicAdd_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 102 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicAdd_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 102
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicAdd_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 108 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicAdd_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 108
{ } 
#endif
#line 111 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicAdd_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 111
{ } 
#endif
#line 114 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline float atomicAdd_block(float *address, float val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 114
{ } 
#endif
#line 117 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline float atomicAdd_system(float *address, float val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 117
{ } 
#endif
#line 120 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline double atomicAdd_block(double *address, double val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 120
{ } 
#endif
#line 123 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline double atomicAdd_system(double *address, double val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 123
{ } 
#endif
#line 126 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicSub_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 126
{ } 
#endif
#line 129 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicSub_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 129
{ } 
#endif
#line 132 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicSub_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 132
{ } 
#endif
#line 135 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicSub_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 135
{ } 
#endif
#line 138 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicExch_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 138
{ } 
#endif
#line 141 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicExch_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 141
{ } 
#endif
#line 144 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicExch_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 144
{ } 
#endif
#line 147 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicExch_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 147
{ } 
#endif
#line 150 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicExch_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 150
{ } 
#endif
#line 153 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicExch_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 153
{ } 
#endif
#line 156 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline float atomicExch_block(float *address, float val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 156
{ } 
#endif
#line 159 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline float atomicExch_system(float *address, float val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 159
{ } 
#endif
#line 162 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicMin_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 162
{ } 
#endif
#line 165 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicMin_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 165
{ } 
#endif
#line 168 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicMin_block(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 168
{ } 
#endif
#line 171 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicMin_system(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 171
{ } 
#endif
#line 174 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicMin_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 174
{ } 
#endif
#line 177 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicMin_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 177
{ } 
#endif
#line 180 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicMin_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 180
{ } 
#endif
#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicMin_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 183
{ } 
#endif
#line 186 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicMax_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 186
{ } 
#endif
#line 189 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicMax_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 189
{ } 
#endif
#line 192 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicMax_block(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 192
{ } 
#endif
#line 195 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicMax_system(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 195
{ } 
#endif
#line 198 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicMax_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 198
{ } 
#endif
#line 201 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicMax_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 201
{ } 
#endif
#line 204 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicMax_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 204
{ } 
#endif
#line 207 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicMax_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 207
{ } 
#endif
#line 210 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicInc_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 210
{ } 
#endif
#line 213 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicInc_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 213
{ } 
#endif
#line 216 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicDec_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 216
{ } 
#endif
#line 219 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicDec_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 219
{ } 
#endif
#line 222 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicCAS_block(int *address, int compare, int val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 222
{ } 
#endif
#line 225 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicCAS_system(int *address, int compare, int val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 225
{ } 
#endif
#line 228 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicCAS_block(unsigned *address, unsigned compare, unsigned 
#line 229
val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 229
{ } 
#endif
#line 232 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicCAS_system(unsigned *address, unsigned compare, unsigned 
#line 233
val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 233
{ } 
#endif
#line 236 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicCAS_block(unsigned __int64 *address, unsigned __int64 
#line 237
compare, unsigned __int64 
#line 238
val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 238
{ } 
#endif
#line 241 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicCAS_system(unsigned __int64 *address, unsigned __int64 
#line 242
compare, unsigned __int64 
#line 243
val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 243
{ } 
#endif
#line 246 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicAnd_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 246
{ } 
#endif
#line 249 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicAnd_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 249
{ } 
#endif
#line 252 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicAnd_block(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 252
{ } 
#endif
#line 255 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicAnd_system(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 255
{ } 
#endif
#line 258 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicAnd_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 258
{ } 
#endif
#line 261 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicAnd_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 261
{ } 
#endif
#line 264 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicAnd_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 264
{ } 
#endif
#line 267 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicAnd_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 267
{ } 
#endif
#line 270 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicOr_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 270
{ } 
#endif
#line 273 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicOr_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 273
{ } 
#endif
#line 276 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicOr_block(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 276
{ } 
#endif
#line 279 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicOr_system(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 279
{ } 
#endif
#line 282 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicOr_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 282
{ } 
#endif
#line 285 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicOr_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 285
{ } 
#endif
#line 288 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicOr_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 288
{ } 
#endif
#line 291 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicOr_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 291
{ } 
#endif
#line 294 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicXor_block(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 294
{ } 
#endif
#line 297 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline int atomicXor_system(int *address, int val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 297
{ } 
#endif
#line 300 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicXor_block(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 300
{ } 
#endif
#line 303 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline __int64 atomicXor_system(__int64 *address, __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 303
{ } 
#endif
#line 306 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicXor_block(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 306
{ } 
#endif
#line 309 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned atomicXor_system(unsigned *address, unsigned val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 309
{ } 
#endif
#line 312 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicXor_block(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 312
{ } 
#endif
#line 315 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_60_atomic_functions.h"
static __inline unsigned __int64 atomicXor_system(unsigned __int64 *address, unsigned __int64 val) {int volatile ___ = 1;(void)address;(void)val;::exit(___);}
#if 0
#line 315
{ } 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
extern "C" {
#line 1038
}
#line 1045
__declspec(deprecated("__ballot() is deprecated in favor of __ballot_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to" " suppress this warning).")) static __inline unsigned ballot(bool pred) {int volatile ___ = 1;(void)pred;::exit(___);}
#if 0
#line 1045
{ } 
#endif
#line 1047 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline int syncthreads_count(bool pred) {int volatile ___ = 1;(void)pred;::exit(___);}
#if 0
#line 1047
{ } 
#endif
#line 1049 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline bool syncthreads_and(bool pred) {int volatile ___ = 1;(void)pred;::exit(___);}
#if 0
#line 1049
{ } 
#endif
#line 1051 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline bool syncthreads_or(bool pred) {int volatile ___ = 1;(void)pred;::exit(___);}
#if 0
#line 1051
{ } 
#endif
#line 1056 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline unsigned __isGlobal(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1056
{ } 
#endif
#line 1057 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline unsigned __isShared(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1057
{ } 
#endif
#line 1058 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline unsigned __isConstant(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1058
{ } 
#endif
#line 1059 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline unsigned __isLocal(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1059
{ } 
#endif
#line 1061 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline unsigned __isGridConstant(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1061
{ } 
#endif
#line 1063 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline size_t __cvta_generic_to_global(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1063
{ } 
#endif
#line 1064 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline size_t __cvta_generic_to_shared(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1064
{ } 
#endif
#line 1065 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline size_t __cvta_generic_to_constant(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1065
{ } 
#endif
#line 1066 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline size_t __cvta_generic_to_local(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1066
{ } 
#endif
#line 1068 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline size_t __cvta_generic_to_grid_constant(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 1068
{ } 
#endif
#line 1071 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline void *__cvta_global_to_generic(size_t rawbits) {int volatile ___ = 1;(void)rawbits;::exit(___);}
#if 0
#line 1071
{ } 
#endif
#line 1072 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline void *__cvta_shared_to_generic(size_t rawbits) {int volatile ___ = 1;(void)rawbits;::exit(___);}
#if 0
#line 1072
{ } 
#endif
#line 1073 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline void *__cvta_constant_to_generic(size_t rawbits) {int volatile ___ = 1;(void)rawbits;::exit(___);}
#if 0
#line 1073
{ } 
#endif
#line 1074 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline void *__cvta_local_to_generic(size_t rawbits) {int volatile ___ = 1;(void)rawbits;::exit(___);}
#if 0
#line 1074
{ } 
#endif
#line 1076 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline void *__cvta_grid_constant_to_generic(size_t rawbits) {int volatile ___ = 1;(void)rawbits;::exit(___);}
#if 0
#line 1076
{ } 
#endif
#line 1090 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
static __inline unsigned short __nv_bswap16(unsigned short x) { 
#line 1094 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
return _byteswap_ushort(x); 
#line 1098 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
} 
#line 1109
static __inline unsigned __nv_bswap32(unsigned x) { 
#line 1113 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
unsigned long ret = _byteswap_ulong(static_cast< unsigned long>(x)); 
#line 1114
return static_cast< unsigned>(ret); 
#line 1118 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
} 
#line 1129
static __inline unsigned __int64 __nv_bswap64(unsigned __int64 x) { 
#line 1133 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
unsigned __int64 ret = _byteswap_uint64(x); 
#line 1134
return ret; 
#line 1138 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_20_intrinsics.h"
} 
#line 123 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __fns(unsigned mask, unsigned base, int offset) {int volatile ___ = 1;(void)mask;(void)base;(void)offset;::exit(___);}
#if 0
#line 123
{ } 
#endif
#line 124 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline void __barrier_sync(unsigned id) {int volatile ___ = 1;(void)id;::exit(___);}
#if 0
#line 124
{ } 
#endif
#line 125 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline void __barrier_sync_count(unsigned id, unsigned cnt) {int volatile ___ = 1;(void)id;(void)cnt;::exit(___);}
#if 0
#line 125
{ } 
#endif
#line 126 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline void __syncwarp(unsigned mask = 4294967295U) {int volatile ___ = 1;(void)mask;::exit(___);}
#if 0
#line 126
{ } 
#endif
#line 127 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __all_sync(unsigned mask, int pred) {int volatile ___ = 1;(void)mask;(void)pred;::exit(___);}
#if 0
#line 127
{ } 
#endif
#line 128 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __any_sync(unsigned mask, int pred) {int volatile ___ = 1;(void)mask;(void)pred;::exit(___);}
#if 0
#line 128
{ } 
#endif
#line 129 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __uni_sync(unsigned mask, int pred) {int volatile ___ = 1;(void)mask;(void)pred;::exit(___);}
#if 0
#line 129
{ } 
#endif
#line 130 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __ballot_sync(unsigned mask, int pred) {int volatile ___ = 1;(void)mask;(void)pred;::exit(___);}
#if 0
#line 130
{ } 
#endif
#line 131 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __activemask() {int volatile ___ = 1;::exit(___);}
#if 0
#line 131
{ } 
#endif
#line 140 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline int __shfl(int var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 140
{ } 
#endif
#line 141 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline unsigned __shfl(unsigned var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 141
{ } 
#endif
#line 142 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline int __shfl_up(int var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 142
{ } 
#endif
#line 143 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline unsigned __shfl_up(unsigned var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 143
{ } 
#endif
#line 144 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline int __shfl_down(int var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 144
{ } 
#endif
#line 145 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline unsigned __shfl_down(unsigned var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 145
{ } 
#endif
#line 146 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline int __shfl_xor(int var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 146
{ } 
#endif
#line 147 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline unsigned __shfl_xor(unsigned var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 147
{ } 
#endif
#line 148 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline float __shfl(float var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 148
{ } 
#endif
#line 149 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline float __shfl_up(float var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 149
{ } 
#endif
#line 150 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline float __shfl_down(float var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 150
{ } 
#endif
#line 151 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline float __shfl_xor(float var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 151
{ } 
#endif
#line 154 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __shfl_sync(unsigned mask, int var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 154
{ } 
#endif
#line 155 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __shfl_sync(unsigned mask, unsigned var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 155
{ } 
#endif
#line 156 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __shfl_up_sync(unsigned mask, int var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 156
{ } 
#endif
#line 157 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __shfl_up_sync(unsigned mask, unsigned var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 157
{ } 
#endif
#line 158 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __shfl_down_sync(unsigned mask, int var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 158
{ } 
#endif
#line 159 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __shfl_down_sync(unsigned mask, unsigned var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 159
{ } 
#endif
#line 160 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline int __shfl_xor_sync(unsigned mask, int var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 160
{ } 
#endif
#line 161 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __shfl_xor_sync(unsigned mask, unsigned var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 161
{ } 
#endif
#line 162 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline float __shfl_sync(unsigned mask, float var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 162
{ } 
#endif
#line 163 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline float __shfl_up_sync(unsigned mask, float var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 163
{ } 
#endif
#line 164 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline float __shfl_down_sync(unsigned mask, float var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 164
{ } 
#endif
#line 165 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline float __shfl_xor_sync(unsigned mask, float var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 165
{ } 
#endif
#line 169 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline unsigned __int64 __shfl(unsigned __int64 var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 169
{ } 
#endif
#line 170 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline __int64 __shfl(__int64 var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 170
{ } 
#endif
#line 171 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline __int64 __shfl_up(__int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 171
{ } 
#endif
#line 172 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline unsigned __int64 __shfl_up(unsigned __int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 172
{ } 
#endif
#line 173 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline __int64 __shfl_down(__int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 173
{ } 
#endif
#line 174 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline unsigned __int64 __shfl_down(unsigned __int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 174
{ } 
#endif
#line 175 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline __int64 __shfl_xor(__int64 var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 175
{ } 
#endif
#line 176 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline unsigned __int64 __shfl_xor(unsigned __int64 var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 176
{ } 
#endif
#line 177 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline double __shfl(double var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 177
{ } 
#endif
#line 178 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline double __shfl_up(double var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 178
{ } 
#endif
#line 179 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline double __shfl_down(double var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 179
{ } 
#endif
#line 180 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline double __shfl_xor(double var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 180
{ } 
#endif
#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline __int64 __shfl_sync(unsigned mask, __int64 var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 183
{ } 
#endif
#line 184 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __int64 __shfl_sync(unsigned mask, unsigned __int64 var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 184
{ } 
#endif
#line 185 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline __int64 __shfl_up_sync(unsigned mask, __int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 185
{ } 
#endif
#line 186 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __int64 __shfl_up_sync(unsigned mask, unsigned __int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 186
{ } 
#endif
#line 187 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline __int64 __shfl_down_sync(unsigned mask, __int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 187
{ } 
#endif
#line 188 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __int64 __shfl_down_sync(unsigned mask, unsigned __int64 var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 188
{ } 
#endif
#line 189 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline __int64 __shfl_xor_sync(unsigned mask, __int64 var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 189
{ } 
#endif
#line 190 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned __int64 __shfl_xor_sync(unsigned mask, unsigned __int64 var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 190
{ } 
#endif
#line 191 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline double __shfl_sync(unsigned mask, double var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 191
{ } 
#endif
#line 192 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline double __shfl_up_sync(unsigned mask, double var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 192
{ } 
#endif
#line 193 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline double __shfl_down_sync(unsigned mask, double var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 193
{ } 
#endif
#line 194 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline double __shfl_xor_sync(unsigned mask, double var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 194
{ } 
#endif
#line 198 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline long __shfl(long var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 198
{ } 
#endif
#line 199 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl() is deprecated in favor of __shfl_sync() and may be removed in a future release (Use -Wno-deprecated-declarations to sup" "press this warning).")) static __inline unsigned long __shfl(unsigned long var, int srcLane, int width = 32) {int volatile ___ = 1;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 199
{ } 
#endif
#line 200 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline long __shfl_up(long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 200
{ } 
#endif
#line 201 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_up() is deprecated in favor of __shfl_up_sync() and may be removed in a future release (Use -Wno-deprecated-declarations " "to suppress this warning).")) static __inline unsigned long __shfl_up(unsigned long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 201
{ } 
#endif
#line 202 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline long __shfl_down(long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 202
{ } 
#endif
#line 203 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_down() is deprecated in favor of __shfl_down_sync() and may be removed in a future release (Use -Wno-deprecated-declarati" "ons to suppress this warning).")) static __inline unsigned long __shfl_down(unsigned long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 203
{ } 
#endif
#line 204 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline long __shfl_xor(long var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 204
{ } 
#endif
#line 205 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
__declspec(deprecated("__shfl_xor() is deprecated in favor of __shfl_xor_sync() and may be removed in a future release (Use -Wno-deprecated-declaration" "s to suppress this warning).")) static __inline unsigned long __shfl_xor(unsigned long var, int laneMask, int width = 32) {int volatile ___ = 1;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 205
{ } 
#endif
#line 208 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline long __shfl_sync(unsigned mask, long var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 208
{ } 
#endif
#line 209 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned long __shfl_sync(unsigned mask, unsigned long var, int srcLane, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)srcLane;(void)width;::exit(___);}
#if 0
#line 209
{ } 
#endif
#line 210 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline long __shfl_up_sync(unsigned mask, long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 210
{ } 
#endif
#line 211 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned long __shfl_up_sync(unsigned mask, unsigned long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 211
{ } 
#endif
#line 212 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline long __shfl_down_sync(unsigned mask, long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 212
{ } 
#endif
#line 213 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned long __shfl_down_sync(unsigned mask, unsigned long var, unsigned delta, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)delta;(void)width;::exit(___);}
#if 0
#line 213
{ } 
#endif
#line 214 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline long __shfl_xor_sync(unsigned mask, long var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 214
{ } 
#endif
#line 215 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_30_intrinsics.h"
static __inline unsigned long __shfl_xor_sync(unsigned mask, unsigned long var, int laneMask, int width = 32) {int volatile ___ = 1;(void)mask;(void)var;(void)laneMask;(void)width;::exit(___);}
#if 0
#line 215
{ } 
#endif
#line 91 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline long __ldg(const long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 91
{ } 
#endif
#line 92 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned long __ldg(const unsigned long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 92
{ } 
#endif
#line 94 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char __ldg(const char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 94
{ } 
#endif
#line 95 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline signed char __ldg(const signed char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 95
{ } 
#endif
#line 96 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short __ldg(const short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 96
{ } 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int __ldg(const int *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 97
{ } 
#endif
#line 98 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline __int64 __ldg(const __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 98
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char2 __ldg(const char2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 100 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char4 __ldg(const char4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 100
{ } 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short2 __ldg(const short2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 101
{ } 
#endif
#line 102 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short4 __ldg(const short4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 102
{ } 
#endif
#line 103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int2 __ldg(const int2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 103
{ } 
#endif
#line 104 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int4 __ldg(const int4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 104
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline longlong2 __ldg(const longlong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned char __ldg(const unsigned char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 107
{ } 
#endif
#line 108 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned short __ldg(const unsigned short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 108
{ } 
#endif
#line 109 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __ldg(const unsigned *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 109
{ } 
#endif
#line 110 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __int64 __ldg(const unsigned __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 110
{ } 
#endif
#line 111 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar2 __ldg(const uchar2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 111
{ } 
#endif
#line 112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar4 __ldg(const uchar4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 112
{ } 
#endif
#line 113 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort2 __ldg(const ushort2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 113
{ } 
#endif
#line 114 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort4 __ldg(const ushort4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 114
{ } 
#endif
#line 115 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint2 __ldg(const uint2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 115
{ } 
#endif
#line 116 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint4 __ldg(const uint4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 116
{ } 
#endif
#line 117 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ulonglong2 __ldg(const ulonglong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 117
{ } 
#endif
#line 119 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float __ldg(const float *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 119
{ } 
#endif
#line 120 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double __ldg(const double *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 120
{ } 
#endif
#line 121 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float2 __ldg(const float2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 121
{ } 
#endif
#line 122 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float4 __ldg(const float4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 122
{ } 
#endif
#line 123 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double2 __ldg(const double2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 123
{ } 
#endif
#line 128 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline long __ldcg(const long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 128
{ } 
#endif
#line 129 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned long __ldcg(const unsigned long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 129
{ } 
#endif
#line 131 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char __ldcg(const char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 131
{ } 
#endif
#line 132 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline signed char __ldcg(const signed char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 132
{ } 
#endif
#line 133 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short __ldcg(const short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 133
{ } 
#endif
#line 134 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int __ldcg(const int *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 134
{ } 
#endif
#line 135 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline __int64 __ldcg(const __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 135
{ } 
#endif
#line 136 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char2 __ldcg(const char2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 136
{ } 
#endif
#line 137 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char4 __ldcg(const char4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 137
{ } 
#endif
#line 138 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short2 __ldcg(const short2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 138
{ } 
#endif
#line 139 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short4 __ldcg(const short4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 139
{ } 
#endif
#line 140 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int2 __ldcg(const int2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 140
{ } 
#endif
#line 141 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int4 __ldcg(const int4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 141
{ } 
#endif
#line 142 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline longlong2 __ldcg(const longlong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 142
{ } 
#endif
#line 144 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned char __ldcg(const unsigned char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 144
{ } 
#endif
#line 145 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned short __ldcg(const unsigned short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 145
{ } 
#endif
#line 146 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __ldcg(const unsigned *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 146
{ } 
#endif
#line 147 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __int64 __ldcg(const unsigned __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 147
{ } 
#endif
#line 148 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar2 __ldcg(const uchar2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 148
{ } 
#endif
#line 149 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar4 __ldcg(const uchar4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 149
{ } 
#endif
#line 150 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort2 __ldcg(const ushort2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 150
{ } 
#endif
#line 151 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort4 __ldcg(const ushort4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 151
{ } 
#endif
#line 152 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint2 __ldcg(const uint2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 152
{ } 
#endif
#line 153 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint4 __ldcg(const uint4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 153
{ } 
#endif
#line 154 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ulonglong2 __ldcg(const ulonglong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 154
{ } 
#endif
#line 156 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float __ldcg(const float *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 156
{ } 
#endif
#line 157 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double __ldcg(const double *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 157
{ } 
#endif
#line 158 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float2 __ldcg(const float2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 158
{ } 
#endif
#line 159 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float4 __ldcg(const float4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 159
{ } 
#endif
#line 160 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double2 __ldcg(const double2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 160
{ } 
#endif
#line 164 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline long __ldca(const long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 164
{ } 
#endif
#line 165 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned long __ldca(const unsigned long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 165
{ } 
#endif
#line 167 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char __ldca(const char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 167
{ } 
#endif
#line 168 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline signed char __ldca(const signed char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 168
{ } 
#endif
#line 169 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short __ldca(const short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 169
{ } 
#endif
#line 170 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int __ldca(const int *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 170
{ } 
#endif
#line 171 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline __int64 __ldca(const __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 171
{ } 
#endif
#line 172 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char2 __ldca(const char2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 172
{ } 
#endif
#line 173 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char4 __ldca(const char4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 173
{ } 
#endif
#line 174 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short2 __ldca(const short2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 174
{ } 
#endif
#line 175 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short4 __ldca(const short4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 175
{ } 
#endif
#line 176 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int2 __ldca(const int2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 176
{ } 
#endif
#line 177 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int4 __ldca(const int4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 177
{ } 
#endif
#line 178 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline longlong2 __ldca(const longlong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 178
{ } 
#endif
#line 180 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned char __ldca(const unsigned char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 180
{ } 
#endif
#line 181 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned short __ldca(const unsigned short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 181
{ } 
#endif
#line 182 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __ldca(const unsigned *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 182
{ } 
#endif
#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __int64 __ldca(const unsigned __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 183
{ } 
#endif
#line 184 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar2 __ldca(const uchar2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 184
{ } 
#endif
#line 185 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar4 __ldca(const uchar4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 185
{ } 
#endif
#line 186 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort2 __ldca(const ushort2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 186
{ } 
#endif
#line 187 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort4 __ldca(const ushort4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 187
{ } 
#endif
#line 188 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint2 __ldca(const uint2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 188
{ } 
#endif
#line 189 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint4 __ldca(const uint4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 189
{ } 
#endif
#line 190 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ulonglong2 __ldca(const ulonglong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 190
{ } 
#endif
#line 192 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float __ldca(const float *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 192
{ } 
#endif
#line 193 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double __ldca(const double *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 193
{ } 
#endif
#line 194 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float2 __ldca(const float2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 194
{ } 
#endif
#line 195 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float4 __ldca(const float4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 195
{ } 
#endif
#line 196 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double2 __ldca(const double2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 196
{ } 
#endif
#line 200 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline long __ldcs(const long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 200
{ } 
#endif
#line 201 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned long __ldcs(const unsigned long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 201
{ } 
#endif
#line 203 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char __ldcs(const char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 203
{ } 
#endif
#line 204 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline signed char __ldcs(const signed char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 204
{ } 
#endif
#line 205 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short __ldcs(const short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 205
{ } 
#endif
#line 206 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int __ldcs(const int *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 206
{ } 
#endif
#line 207 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline __int64 __ldcs(const __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 207
{ } 
#endif
#line 208 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char2 __ldcs(const char2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 208
{ } 
#endif
#line 209 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char4 __ldcs(const char4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 209
{ } 
#endif
#line 210 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short2 __ldcs(const short2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 210
{ } 
#endif
#line 211 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short4 __ldcs(const short4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 211
{ } 
#endif
#line 212 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int2 __ldcs(const int2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 212
{ } 
#endif
#line 213 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int4 __ldcs(const int4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 213
{ } 
#endif
#line 214 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline longlong2 __ldcs(const longlong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 214
{ } 
#endif
#line 216 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned char __ldcs(const unsigned char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 216
{ } 
#endif
#line 217 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned short __ldcs(const unsigned short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 217
{ } 
#endif
#line 218 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __ldcs(const unsigned *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 218
{ } 
#endif
#line 219 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __int64 __ldcs(const unsigned __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 219
{ } 
#endif
#line 220 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar2 __ldcs(const uchar2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 220
{ } 
#endif
#line 221 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar4 __ldcs(const uchar4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 221
{ } 
#endif
#line 222 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort2 __ldcs(const ushort2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 222
{ } 
#endif
#line 223 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort4 __ldcs(const ushort4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 223
{ } 
#endif
#line 224 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint2 __ldcs(const uint2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 224
{ } 
#endif
#line 225 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint4 __ldcs(const uint4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 225
{ } 
#endif
#line 226 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ulonglong2 __ldcs(const ulonglong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 226
{ } 
#endif
#line 228 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float __ldcs(const float *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 228
{ } 
#endif
#line 229 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double __ldcs(const double *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 229
{ } 
#endif
#line 230 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float2 __ldcs(const float2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 230
{ } 
#endif
#line 231 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float4 __ldcs(const float4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 231
{ } 
#endif
#line 232 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double2 __ldcs(const double2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 232
{ } 
#endif
#line 236 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline long __ldlu(const long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 236
{ } 
#endif
#line 237 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned long __ldlu(const unsigned long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 237
{ } 
#endif
#line 239 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char __ldlu(const char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 239
{ } 
#endif
#line 240 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline signed char __ldlu(const signed char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 240
{ } 
#endif
#line 241 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short __ldlu(const short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 241
{ } 
#endif
#line 242 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int __ldlu(const int *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 242
{ } 
#endif
#line 243 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline __int64 __ldlu(const __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 243
{ } 
#endif
#line 244 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char2 __ldlu(const char2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 244
{ } 
#endif
#line 245 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char4 __ldlu(const char4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 245
{ } 
#endif
#line 246 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short2 __ldlu(const short2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 246
{ } 
#endif
#line 247 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short4 __ldlu(const short4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 247
{ } 
#endif
#line 248 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int2 __ldlu(const int2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 248
{ } 
#endif
#line 249 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int4 __ldlu(const int4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 249
{ } 
#endif
#line 250 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline longlong2 __ldlu(const longlong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 250
{ } 
#endif
#line 252 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned char __ldlu(const unsigned char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 252
{ } 
#endif
#line 253 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned short __ldlu(const unsigned short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 253
{ } 
#endif
#line 254 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __ldlu(const unsigned *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 254
{ } 
#endif
#line 255 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __int64 __ldlu(const unsigned __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 255
{ } 
#endif
#line 256 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar2 __ldlu(const uchar2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 256
{ } 
#endif
#line 257 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar4 __ldlu(const uchar4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 257
{ } 
#endif
#line 258 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort2 __ldlu(const ushort2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 258
{ } 
#endif
#line 259 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort4 __ldlu(const ushort4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 259
{ } 
#endif
#line 260 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint2 __ldlu(const uint2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 260
{ } 
#endif
#line 261 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint4 __ldlu(const uint4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 261
{ } 
#endif
#line 262 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ulonglong2 __ldlu(const ulonglong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 262
{ } 
#endif
#line 264 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float __ldlu(const float *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 264
{ } 
#endif
#line 265 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double __ldlu(const double *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 265
{ } 
#endif
#line 266 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float2 __ldlu(const float2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 266
{ } 
#endif
#line 267 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float4 __ldlu(const float4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 267
{ } 
#endif
#line 268 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double2 __ldlu(const double2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 268
{ } 
#endif
#line 272 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline long __ldcv(const long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 272
{ } 
#endif
#line 273 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned long __ldcv(const unsigned long *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 273
{ } 
#endif
#line 275 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char __ldcv(const char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 275
{ } 
#endif
#line 276 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline signed char __ldcv(const signed char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 276
{ } 
#endif
#line 277 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short __ldcv(const short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 277
{ } 
#endif
#line 278 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int __ldcv(const int *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 278
{ } 
#endif
#line 279 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline __int64 __ldcv(const __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 279
{ } 
#endif
#line 280 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char2 __ldcv(const char2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 280
{ } 
#endif
#line 281 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline char4 __ldcv(const char4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 281
{ } 
#endif
#line 282 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short2 __ldcv(const short2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 282
{ } 
#endif
#line 283 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline short4 __ldcv(const short4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 283
{ } 
#endif
#line 284 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int2 __ldcv(const int2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 284
{ } 
#endif
#line 285 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline int4 __ldcv(const int4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 285
{ } 
#endif
#line 286 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline longlong2 __ldcv(const longlong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 286
{ } 
#endif
#line 288 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned char __ldcv(const unsigned char *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 288
{ } 
#endif
#line 289 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned short __ldcv(const unsigned short *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 289
{ } 
#endif
#line 290 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __ldcv(const unsigned *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 290
{ } 
#endif
#line 291 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __int64 __ldcv(const unsigned __int64 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 291
{ } 
#endif
#line 292 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar2 __ldcv(const uchar2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 292
{ } 
#endif
#line 293 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uchar4 __ldcv(const uchar4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 293
{ } 
#endif
#line 294 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort2 __ldcv(const ushort2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 294
{ } 
#endif
#line 295 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ushort4 __ldcv(const ushort4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 295
{ } 
#endif
#line 296 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint2 __ldcv(const uint2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 296
{ } 
#endif
#line 297 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline uint4 __ldcv(const uint4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 297
{ } 
#endif
#line 298 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline ulonglong2 __ldcv(const ulonglong2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 298
{ } 
#endif
#line 300 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float __ldcv(const float *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 300
{ } 
#endif
#line 301 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double __ldcv(const double *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 301
{ } 
#endif
#line 302 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float2 __ldcv(const float2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 302
{ } 
#endif
#line 303 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline float4 __ldcv(const float4 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 303
{ } 
#endif
#line 304 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline double2 __ldcv(const double2 *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 304
{ } 
#endif
#line 308 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(long *ptr, long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 308
{ } 
#endif
#line 309 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(unsigned long *ptr, unsigned long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 309
{ } 
#endif
#line 311 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(char *ptr, char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 311
{ } 
#endif
#line 312 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(signed char *ptr, signed char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 312
{ } 
#endif
#line 313 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(short *ptr, short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 313
{ } 
#endif
#line 314 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(int *ptr, int value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 314
{ } 
#endif
#line 315 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(__int64 *ptr, __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 315
{ } 
#endif
#line 316 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(char2 *ptr, char2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 316
{ } 
#endif
#line 317 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(char4 *ptr, char4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 317
{ } 
#endif
#line 318 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(short2 *ptr, short2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 318
{ } 
#endif
#line 319 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(short4 *ptr, short4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 319
{ } 
#endif
#line 320 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(int2 *ptr, int2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 320
{ } 
#endif
#line 321 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(int4 *ptr, int4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 321
{ } 
#endif
#line 322 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(longlong2 *ptr, longlong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 322
{ } 
#endif
#line 324 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(unsigned char *ptr, unsigned char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 324
{ } 
#endif
#line 325 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(unsigned short *ptr, unsigned short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 325
{ } 
#endif
#line 326 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(unsigned *ptr, unsigned value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 326
{ } 
#endif
#line 327 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(unsigned __int64 *ptr, unsigned __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 327
{ } 
#endif
#line 328 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(uchar2 *ptr, uchar2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 328
{ } 
#endif
#line 329 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(uchar4 *ptr, uchar4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 329
{ } 
#endif
#line 330 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(ushort2 *ptr, ushort2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 330
{ } 
#endif
#line 331 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(ushort4 *ptr, ushort4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 331
{ } 
#endif
#line 332 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(uint2 *ptr, uint2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 332
{ } 
#endif
#line 333 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(uint4 *ptr, uint4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 333
{ } 
#endif
#line 334 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(ulonglong2 *ptr, ulonglong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 334
{ } 
#endif
#line 336 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(float *ptr, float value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 336
{ } 
#endif
#line 337 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(double *ptr, double value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 337
{ } 
#endif
#line 338 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(float2 *ptr, float2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 338
{ } 
#endif
#line 339 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(float4 *ptr, float4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 339
{ } 
#endif
#line 340 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwb(double2 *ptr, double2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 340
{ } 
#endif
#line 344 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(long *ptr, long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 344
{ } 
#endif
#line 345 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(unsigned long *ptr, unsigned long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 345
{ } 
#endif
#line 347 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(char *ptr, char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 347
{ } 
#endif
#line 348 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(signed char *ptr, signed char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 348
{ } 
#endif
#line 349 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(short *ptr, short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 349
{ } 
#endif
#line 350 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(int *ptr, int value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 350
{ } 
#endif
#line 351 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(__int64 *ptr, __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 351
{ } 
#endif
#line 352 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(char2 *ptr, char2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 352
{ } 
#endif
#line 353 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(char4 *ptr, char4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 353
{ } 
#endif
#line 354 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(short2 *ptr, short2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 354
{ } 
#endif
#line 355 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(short4 *ptr, short4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 355
{ } 
#endif
#line 356 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(int2 *ptr, int2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 356
{ } 
#endif
#line 357 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(int4 *ptr, int4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 357
{ } 
#endif
#line 358 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(longlong2 *ptr, longlong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 358
{ } 
#endif
#line 360 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(unsigned char *ptr, unsigned char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 360
{ } 
#endif
#line 361 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(unsigned short *ptr, unsigned short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 361
{ } 
#endif
#line 362 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(unsigned *ptr, unsigned value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 362
{ } 
#endif
#line 363 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(unsigned __int64 *ptr, unsigned __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 363
{ } 
#endif
#line 364 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(uchar2 *ptr, uchar2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 364
{ } 
#endif
#line 365 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(uchar4 *ptr, uchar4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 365
{ } 
#endif
#line 366 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(ushort2 *ptr, ushort2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 366
{ } 
#endif
#line 367 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(ushort4 *ptr, ushort4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 367
{ } 
#endif
#line 368 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(uint2 *ptr, uint2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 368
{ } 
#endif
#line 369 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(uint4 *ptr, uint4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 369
{ } 
#endif
#line 370 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(ulonglong2 *ptr, ulonglong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 370
{ } 
#endif
#line 372 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(float *ptr, float value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 372
{ } 
#endif
#line 373 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(double *ptr, double value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 373
{ } 
#endif
#line 374 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(float2 *ptr, float2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 374
{ } 
#endif
#line 375 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(float4 *ptr, float4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 375
{ } 
#endif
#line 376 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcg(double2 *ptr, double2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 376
{ } 
#endif
#line 380 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(long *ptr, long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 380
{ } 
#endif
#line 381 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(unsigned long *ptr, unsigned long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 381
{ } 
#endif
#line 383 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(char *ptr, char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 383
{ } 
#endif
#line 384 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(signed char *ptr, signed char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 384
{ } 
#endif
#line 385 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(short *ptr, short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 385
{ } 
#endif
#line 386 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(int *ptr, int value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 386
{ } 
#endif
#line 387 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(__int64 *ptr, __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 387
{ } 
#endif
#line 388 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(char2 *ptr, char2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 388
{ } 
#endif
#line 389 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(char4 *ptr, char4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 389
{ } 
#endif
#line 390 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(short2 *ptr, short2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 390
{ } 
#endif
#line 391 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(short4 *ptr, short4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 391
{ } 
#endif
#line 392 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(int2 *ptr, int2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 392
{ } 
#endif
#line 393 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(int4 *ptr, int4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 393
{ } 
#endif
#line 394 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(longlong2 *ptr, longlong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 394
{ } 
#endif
#line 396 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(unsigned char *ptr, unsigned char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 396
{ } 
#endif
#line 397 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(unsigned short *ptr, unsigned short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 397
{ } 
#endif
#line 398 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(unsigned *ptr, unsigned value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 398
{ } 
#endif
#line 399 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(unsigned __int64 *ptr, unsigned __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 399
{ } 
#endif
#line 400 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(uchar2 *ptr, uchar2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 400
{ } 
#endif
#line 401 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(uchar4 *ptr, uchar4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 401
{ } 
#endif
#line 402 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(ushort2 *ptr, ushort2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 402
{ } 
#endif
#line 403 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(ushort4 *ptr, ushort4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 403
{ } 
#endif
#line 404 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(uint2 *ptr, uint2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 404
{ } 
#endif
#line 405 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(uint4 *ptr, uint4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 405
{ } 
#endif
#line 406 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(ulonglong2 *ptr, ulonglong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 406
{ } 
#endif
#line 408 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(float *ptr, float value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 408
{ } 
#endif
#line 409 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(double *ptr, double value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 409
{ } 
#endif
#line 410 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(float2 *ptr, float2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 410
{ } 
#endif
#line 411 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(float4 *ptr, float4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 411
{ } 
#endif
#line 412 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stcs(double2 *ptr, double2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 412
{ } 
#endif
#line 416 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(long *ptr, long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 416
{ } 
#endif
#line 417 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(unsigned long *ptr, unsigned long value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 417
{ } 
#endif
#line 419 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(char *ptr, char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 419
{ } 
#endif
#line 420 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(signed char *ptr, signed char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 420
{ } 
#endif
#line 421 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(short *ptr, short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 421
{ } 
#endif
#line 422 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(int *ptr, int value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 422
{ } 
#endif
#line 423 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(__int64 *ptr, __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 423
{ } 
#endif
#line 424 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(char2 *ptr, char2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 424
{ } 
#endif
#line 425 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(char4 *ptr, char4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 425
{ } 
#endif
#line 426 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(short2 *ptr, short2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 426
{ } 
#endif
#line 427 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(short4 *ptr, short4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 427
{ } 
#endif
#line 428 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(int2 *ptr, int2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 428
{ } 
#endif
#line 429 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(int4 *ptr, int4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 429
{ } 
#endif
#line 430 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(longlong2 *ptr, longlong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 430
{ } 
#endif
#line 432 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(unsigned char *ptr, unsigned char value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 432
{ } 
#endif
#line 433 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(unsigned short *ptr, unsigned short value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 433
{ } 
#endif
#line 434 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(unsigned *ptr, unsigned value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 434
{ } 
#endif
#line 435 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(unsigned __int64 *ptr, unsigned __int64 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 435
{ } 
#endif
#line 436 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(uchar2 *ptr, uchar2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 436
{ } 
#endif
#line 437 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(uchar4 *ptr, uchar4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 437
{ } 
#endif
#line 438 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(ushort2 *ptr, ushort2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 438
{ } 
#endif
#line 439 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(ushort4 *ptr, ushort4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 439
{ } 
#endif
#line 440 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(uint2 *ptr, uint2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 440
{ } 
#endif
#line 441 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(uint4 *ptr, uint4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 441
{ } 
#endif
#line 442 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(ulonglong2 *ptr, ulonglong2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 442
{ } 
#endif
#line 444 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(float *ptr, float value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 444
{ } 
#endif
#line 445 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(double *ptr, double value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 445
{ } 
#endif
#line 446 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(float2 *ptr, float2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 446
{ } 
#endif
#line 447 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(float4 *ptr, float4 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 447
{ } 
#endif
#line 448 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline void __stwt(double2 *ptr, double2 value) {int volatile ___ = 1;(void)ptr;(void)value;::exit(___);}
#if 0
#line 448
{ } 
#endif
#line 465 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __funnelshift_l(unsigned lo, unsigned hi, unsigned shift) {int volatile ___ = 1;(void)lo;(void)hi;(void)shift;::exit(___);}
#if 0
#line 465
{ } 
#endif
#line 477 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __funnelshift_lc(unsigned lo, unsigned hi, unsigned shift) {int volatile ___ = 1;(void)lo;(void)hi;(void)shift;::exit(___);}
#if 0
#line 477
{ } 
#endif
#line 490 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __funnelshift_r(unsigned lo, unsigned hi, unsigned shift) {int volatile ___ = 1;(void)lo;(void)hi;(void)shift;::exit(___);}
#if 0
#line 490
{ } 
#endif
#line 502 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_32_intrinsics.h"
static __inline unsigned __funnelshift_rc(unsigned lo, unsigned hi, unsigned shift) {int volatile ___ = 1;(void)lo;(void)hi;(void)shift;::exit(___);}
#if 0
#line 502
{ } 
#endif
#line 102 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline int __dp2a_lo(int srcA, int srcB, int c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 102
{ } 
#endif
#line 113 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline unsigned __dp2a_lo(unsigned srcA, unsigned srcB, unsigned c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 113
{ } 
#endif
#line 125 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline int __dp2a_lo(short2 srcA, char4 srcB, int c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 125
{ } 
#endif
#line 136 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline unsigned __dp2a_lo(ushort2 srcA, uchar4 srcB, unsigned c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 136
{ } 
#endif
#line 148 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline int __dp2a_hi(int srcA, int srcB, int c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 148
{ } 
#endif
#line 159 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline unsigned __dp2a_hi(unsigned srcA, unsigned srcB, unsigned c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 159
{ } 
#endif
#line 171 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline int __dp2a_hi(short2 srcA, char4 srcB, int c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 171
{ } 
#endif
#line 182 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline unsigned __dp2a_hi(ushort2 srcA, uchar4 srcB, unsigned c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 182
{ } 
#endif
#line 197 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline int __dp4a(int srcA, int srcB, int c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 197
{ } 
#endif
#line 206 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline unsigned __dp4a(unsigned srcA, unsigned srcB, unsigned c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 206
{ } 
#endif
#line 216 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline int __dp4a(char4 srcA, char4 srcB, int c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 216
{ } 
#endif
#line 225 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\sm_61_intrinsics.h"
static __inline unsigned __dp4a(uchar4 srcA, uchar4 srcB, unsigned c) {int volatile ___ = 1;(void)srcA;(void)srcB;(void)c;::exit(___);}
#if 0
#line 225
{ } 
#endif
#line 98 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 98
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, int value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 100 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, unsigned long value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 100
{ } 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, long value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 101
{ } 
#endif
#line 102 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, unsigned __int64 value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 102
{ } 
#endif
#line 103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, __int64 value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 103
{ } 
#endif
#line 104 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, float value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 104
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_any_sync(unsigned mask, double value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, unsigned value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 107
{ } 
#endif
#line 108 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, int value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 108
{ } 
#endif
#line 109 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, unsigned long value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 109
{ } 
#endif
#line 110 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, long value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 110
{ } 
#endif
#line 111 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, unsigned __int64 value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 111
{ } 
#endif
#line 112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, __int64 value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 112
{ } 
#endif
#line 113 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, float value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 113
{ } 
#endif
#line 114 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned __match_all_sync(unsigned mask, double value, int *pred) {int volatile ___ = 1;(void)mask;(void)value;(void)pred;::exit(___);}
#if 0
#line 114
{ } 
#endif
#line 116 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline void __nanosleep(unsigned ns) {int volatile ___ = 1;(void)ns;::exit(___);}
#if 0
#line 116
{ } 
#endif
#line 118 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_70_rt.h"
static __inline unsigned short atomicCAS(unsigned short *address, unsigned short compare, unsigned short val) {int volatile ___ = 1;(void)address;(void)compare;(void)val;::exit(___);}
#if 0
#line 118
{ } 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline unsigned __reduce_add_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 97
{ } 
#endif
#line 98 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline unsigned __reduce_min_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 98
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline unsigned __reduce_max_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline int __reduce_add_sync(unsigned mask, int value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 101
{ } 
#endif
#line 102 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline int __reduce_min_sync(unsigned mask, int value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 102
{ } 
#endif
#line 103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline int __reduce_max_sync(unsigned mask, int value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 103
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline unsigned __reduce_and_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 106 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline unsigned __reduce_or_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 106
{ } 
#endif
#line 107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
static __inline unsigned __reduce_xor_sync(unsigned mask, unsigned value) {int volatile ___ = 1;(void)mask;(void)value;::exit(___);}
#if 0
#line 107
{ } 
#endif
#line 112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
extern "C" {
#line 113
inline void *__nv_associate_access_property(const void *ptr, unsigned __int64 
#line 114
property) {int volatile ___ = 1;(void)ptr;(void)property;::exit(___);}
#if 0
#line 114
{ 
#line 115
extern void *__nv_associate_access_property_impl(const void *, unsigned __int64); 
#line 117
return __nv_associate_access_property_impl(ptr, property); 
#line 118
} 
#endif
#line 120 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
inline void __nv_memcpy_async_shared_global_4(void *dst, const void *
#line 121
src, unsigned 
#line 122
src_size) {int volatile ___ = 1;(void)dst;(void)src;(void)src_size;::exit(___);}
#if 0
#line 122
{ 
#line 123
extern void __nv_memcpy_async_shared_global_4_impl(void *, const void *, unsigned); 
#line 126
__nv_memcpy_async_shared_global_4_impl(dst, src, src_size); 
#line 127
} 
#endif
#line 129 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
inline void __nv_memcpy_async_shared_global_8(void *dst, const void *
#line 130
src, unsigned 
#line 131
src_size) {int volatile ___ = 1;(void)dst;(void)src;(void)src_size;::exit(___);}
#if 0
#line 131
{ 
#line 132
extern void __nv_memcpy_async_shared_global_8_impl(void *, const void *, unsigned); 
#line 135
__nv_memcpy_async_shared_global_8_impl(dst, src, src_size); 
#line 136
} 
#endif
#line 138 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
inline void __nv_memcpy_async_shared_global_16(void *dst, const void *
#line 139
src, unsigned 
#line 140
src_size) {int volatile ___ = 1;(void)dst;(void)src;(void)src_size;::exit(___);}
#if 0
#line 140
{ 
#line 141
extern void __nv_memcpy_async_shared_global_16_impl(void *, const void *, unsigned); 
#line 144
__nv_memcpy_async_shared_global_16_impl(dst, src, src_size); 
#line 145
} 
#endif
#line 147 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_80_rt.h"
}
#line 92 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline unsigned __isCtaShared(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 92
{ } 
#endif
#line 93 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline unsigned __isClusterShared(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 93
{ } 
#endif
#line 94 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline void *__cluster_map_shared_rank(const void *ptr, unsigned target_block_rank) {int volatile ___ = 1;(void)ptr;(void)target_block_rank;::exit(___);}
#if 0
#line 94
{ } 
#endif
#line 95 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline unsigned __cluster_query_shared_rank(const void *ptr) {int volatile ___ = 1;(void)ptr;::exit(___);}
#if 0
#line 95
{ } 
#endif
#line 96 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline uint2 __cluster_map_shared_multicast(const void *ptr, unsigned cluster_cta_mask) {int volatile ___ = 1;(void)ptr;(void)cluster_cta_mask;::exit(___);}
#if 0
#line 96
{ } 
#endif
#line 97 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline unsigned __clusterDimIsSpecified() {int volatile ___ = 1;::exit(___);}
#if 0
#line 97
{ } 
#endif
#line 98 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline dim3 __clusterDim() {int volatile ___ = 1;::exit(___);}
#if 0
#line 98
{ } 
#endif
#line 99 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline dim3 __clusterRelativeBlockIdx() {int volatile ___ = 1;::exit(___);}
#if 0
#line 99
{ } 
#endif
#line 100 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline dim3 __clusterGridDimInClusters() {int volatile ___ = 1;::exit(___);}
#if 0
#line 100
{ } 
#endif
#line 101 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline dim3 __clusterIdx() {int volatile ___ = 1;::exit(___);}
#if 0
#line 101
{ } 
#endif
#line 102 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline unsigned __clusterRelativeBlockRank() {int volatile ___ = 1;::exit(___);}
#if 0
#line 102
{ } 
#endif
#line 103 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline unsigned __clusterSizeInBlocks() {int volatile ___ = 1;::exit(___);}
#if 0
#line 103
{ } 
#endif
#line 104 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline void __cluster_barrier_arrive() {int volatile ___ = 1;::exit(___);}
#if 0
#line 104
{ } 
#endif
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline void __cluster_barrier_arrive_relaxed() {int volatile ___ = 1;::exit(___);}
#if 0
#line 105
{ } 
#endif
#line 106 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline void __cluster_barrier_wait() {int volatile ___ = 1;::exit(___);}
#if 0
#line 106
{ } 
#endif
#line 107 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline void __threadfence_cluster() {int volatile ___ = 1;::exit(___);}
#if 0
#line 107
{ } 
#endif
#line 109 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline float2 atomicAdd(float2 *__address, float2 val) {int volatile ___ = 1;(void)__address;(void)val;::exit(___);}
#if 0
#line 109
{ } 
#endif
#line 110 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline float2 atomicAdd_block(float2 *__address, float2 val) {int volatile ___ = 1;(void)__address;(void)val;::exit(___);}
#if 0
#line 110
{ } 
#endif
#line 111 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline float2 atomicAdd_system(float2 *__address, float2 val) {int volatile ___ = 1;(void)__address;(void)val;::exit(___);}
#if 0
#line 111
{ } 
#endif
#line 112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline float4 atomicAdd(float4 *__address, float4 val) {int volatile ___ = 1;(void)__address;(void)val;::exit(___);}
#if 0
#line 112
{ } 
#endif
#line 113 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline float4 atomicAdd_block(float4 *__address, float4 val) {int volatile ___ = 1;(void)__address;(void)val;::exit(___);}
#if 0
#line 113
{ } 
#endif
#line 114 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static __inline float4 atomicAdd_system(float4 *__address, float4 val) {int volatile ___ = 1;(void)__address;(void)val;::exit(___);}
#if 0
#line 114
{ } 
#endif
#line 125 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
extern "C" {
#line 132
}
#line 139
template< bool __b, class _T> 
#line 140
struct __nv_atomic_enable_if { }; 
#line 142
template< class _T> 
#line 143
struct __nv_atomic_enable_if< true, _T>  { typedef _T __type; }; 
#line 153 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> 
#line 154
struct __nv_atomic_triv_cp_helper { 
#line 164 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
static const bool __val = __is_trivially_copyable(_T); 
#line 166 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; 
#line 201 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> static __inline typename __nv_atomic_enable_if< ((sizeof(_T) == (16)) && (__alignof(_T) >= (16))) && __nv_atomic_triv_cp_helper< _T> ::__val, _T> ::__type 
#line 203
atomicCAS(_T *__address, _T __compare, _T __val) {int volatile ___ = 1;(void)__address;(void)__compare;(void)__val;::exit(___);}
#if 0
#line 203
{ 
#line 204
union _U { _T __ret; __inline _U() {int *volatile ___ = 0;::free(___);}
#if 0
#line 204
{ } 
#endif
#line 204 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; _U __u; 
#line 205
__u128AtomicCAS((void *)__address, (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__compare)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__val)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__u.__ret))))); 
#line 209
return __u.__ret; 
#line 210
} 
#endif
#line 212 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> static __inline typename __nv_atomic_enable_if< ((sizeof(_T) == (16)) && (__alignof(_T) >= (16))) && __nv_atomic_triv_cp_helper< _T> ::__val, _T> ::__type 
#line 214
atomicCAS_block(_T *__address, _T __compare, _T __val) {int volatile ___ = 1;(void)__address;(void)__compare;(void)__val;::exit(___);}
#if 0
#line 214
{ 
#line 215
union _U { _T __ret; __inline _U() {int *volatile ___ = 0;::free(___);}
#if 0
#line 215
{ } 
#endif
#line 215 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; _U __u; 
#line 216
__u128AtomicCAS_block((void *)__address, (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__compare)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__val)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__u.__ret))))); 
#line 220
return __u.__ret; 
#line 221
} 
#endif
#line 223 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> static __inline typename __nv_atomic_enable_if< ((sizeof(_T) == (16)) && (__alignof(_T) >= (16))) && __nv_atomic_triv_cp_helper< _T> ::__val, _T> ::__type 
#line 225
atomicCAS_system(_T *__address, _T __compare, _T __val) {int volatile ___ = 1;(void)__address;(void)__compare;(void)__val;::exit(___);}
#if 0
#line 225
{ 
#line 226
union _U { _T __ret; __inline _U() {int *volatile ___ = 0;::free(___);}
#if 0
#line 226
{ } 
#endif
#line 226 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; _U __u; 
#line 227
__u128AtomicCAS_system((void *)__address, (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__compare)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__val)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__u.__ret))))); 
#line 231
return __u.__ret; 
#line 232
} 
#endif
#line 234 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> static __inline typename __nv_atomic_enable_if< ((sizeof(_T) == (16)) && (__alignof(_T) >= (16))) && __nv_atomic_triv_cp_helper< _T> ::__val, _T> ::__type 
#line 236
atomicExch(_T *__address, _T __val) {int volatile ___ = 1;(void)__address;(void)__val;::exit(___);}
#if 0
#line 236
{ 
#line 237
union _U { _T __ret; __inline _U() {int *volatile ___ = 0;::free(___);}
#if 0
#line 237
{ } 
#endif
#line 237 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; _U __u; 
#line 238
__u128AtomicExch((void *)__address, (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__val)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__u.__ret))))); 
#line 241
return __u.__ret; 
#line 242
} 
#endif
#line 244 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> static __inline typename __nv_atomic_enable_if< ((sizeof(_T) == (16)) && (__alignof(_T) >= (16))) && __nv_atomic_triv_cp_helper< _T> ::__val, _T> ::__type 
#line 246
atomicExch_block(_T *__address, _T __val) {int volatile ___ = 1;(void)__address;(void)__val;::exit(___);}
#if 0
#line 246
{ 
#line 247
union _U { _T __ret; __inline _U() {int *volatile ___ = 0;::free(___);}
#if 0
#line 247
{ } 
#endif
#line 247 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; _U __u; 
#line 248
__u128AtomicExch_block((void *)__address, (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__val)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__u.__ret))))); 
#line 251
return __u.__ret; 
#line 252
} 
#endif
#line 254 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
template< class _T> static __inline typename __nv_atomic_enable_if< ((sizeof(_T) == (16)) && (__alignof(_T) >= (16))) && __nv_atomic_triv_cp_helper< _T> ::__val, _T> ::__type 
#line 256
atomicExch_system(_T *__address, _T __val) {int volatile ___ = 1;(void)__address;(void)__val;::exit(___);}
#if 0
#line 256
{ 
#line 257
union _U { _T __ret; __inline _U() {int *volatile ___ = 0;::free(___);}
#if 0
#line 257
{ } 
#endif
#line 257 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_90_rt.h"
}; _U __u; 
#line 258
__u128AtomicExch_system((void *)__address, (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__val)))), (void *)(&(const_cast< char &>(reinterpret_cast< const volatile char &>(__u.__ret))))); 
#line 261
return __u.__ret; 
#line 262
} 
#endif
#line 100 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __ffma2_rn(float2 x, float2 y, float2 z) {int volatile ___ = 1;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 100
{ } 
#endif
#line 112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __ffma2_rz(float2 x, float2 y, float2 z) {int volatile ___ = 1;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 112
{ } 
#endif
#line 124 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __ffma2_rd(float2 x, float2 y, float2 z) {int volatile ___ = 1;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 124
{ } 
#endif
#line 136 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __ffma2_ru(float2 x, float2 y, float2 z) {int volatile ___ = 1;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 136
{ } 
#endif
#line 149 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fadd2_rn(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 149
{ } 
#endif
#line 161 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fadd2_rz(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 161
{ } 
#endif
#line 173 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fadd2_rd(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 173
{ } 
#endif
#line 185 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fadd2_ru(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 185
{ } 
#endif
#line 198 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fmul2_rn(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 198
{ } 
#endif
#line 210 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fmul2_rz(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 210
{ } 
#endif
#line 222 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fmul2_rd(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 222
{ } 
#endif
#line 234 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt\\sm_100_rt.h"
static __inline float2 __fmul2_ru(float2 x, float2 y) {int volatile ___ = 1;(void)x;(void)y;::exit(___);}
#if 0
#line 234
{ } 
#endif
#line 65 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> struct __nv_itex_trait { }; 
#line 66
template<> struct __nv_itex_trait< char>  { typedef void type; }; 
#line 67
template<> struct __nv_itex_trait< signed char>  { typedef void type; }; 
#line 68
template<> struct __nv_itex_trait< char1>  { typedef void type; }; 
#line 69
template<> struct __nv_itex_trait< char2>  { typedef void type; }; 
#line 70
template<> struct __nv_itex_trait< char4>  { typedef void type; }; 
#line 71
template<> struct __nv_itex_trait< unsigned char>  { typedef void type; }; 
#line 72
template<> struct __nv_itex_trait< uchar1>  { typedef void type; }; 
#line 73
template<> struct __nv_itex_trait< uchar2>  { typedef void type; }; 
#line 74
template<> struct __nv_itex_trait< uchar4>  { typedef void type; }; 
#line 75
template<> struct __nv_itex_trait< short>  { typedef void type; }; 
#line 76
template<> struct __nv_itex_trait< short1>  { typedef void type; }; 
#line 77
template<> struct __nv_itex_trait< short2>  { typedef void type; }; 
#line 78
template<> struct __nv_itex_trait< short4>  { typedef void type; }; 
#line 79
template<> struct __nv_itex_trait< unsigned short>  { typedef void type; }; 
#line 80
template<> struct __nv_itex_trait< ushort1>  { typedef void type; }; 
#line 81
template<> struct __nv_itex_trait< ushort2>  { typedef void type; }; 
#line 82
template<> struct __nv_itex_trait< ushort4>  { typedef void type; }; 
#line 83
template<> struct __nv_itex_trait< int>  { typedef void type; }; 
#line 84
template<> struct __nv_itex_trait< int1>  { typedef void type; }; 
#line 85
template<> struct __nv_itex_trait< int2>  { typedef void type; }; 
#line 86
template<> struct __nv_itex_trait< int4>  { typedef void type; }; 
#line 87
template<> struct __nv_itex_trait< unsigned>  { typedef void type; }; 
#line 88
template<> struct __nv_itex_trait< uint1>  { typedef void type; }; 
#line 89
template<> struct __nv_itex_trait< uint2>  { typedef void type; }; 
#line 90
template<> struct __nv_itex_trait< uint4>  { typedef void type; }; 
#line 92
template<> struct __nv_itex_trait< long>  { typedef void type; }; 
#line 93
template<> struct __nv_itex_trait< long1>  { typedef void type; }; 
#line 94
template<> struct __nv_itex_trait< long2>  { typedef void type; }; 
#line 95
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 96
template<> struct __nv_itex_trait< long4>  { typedef void type; }; 
#line 97
__pragma( warning(pop)) 
#line 98
template<> struct __nv_itex_trait< unsigned long>  { typedef void type; }; 
#line 99
template<> struct __nv_itex_trait< ulong1>  { typedef void type; }; 
#line 100
template<> struct __nv_itex_trait< ulong2>  { typedef void type; }; 
#line 101
__pragma( warning(push)) __pragma( warning(disable:4996)) 
#line 102
template<> struct __nv_itex_trait< ulong4>  { typedef void type; }; 
#line 103
__pragma( warning(pop)) 
#line 105 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template<> struct __nv_itex_trait< float>  { typedef void type; }; 
#line 106
template<> struct __nv_itex_trait< float1>  { typedef void type; }; 
#line 107
template<> struct __nv_itex_trait< float2>  { typedef void type; }; 
#line 108
template<> struct __nv_itex_trait< float4>  { typedef void type; }; 
__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 112
template< class T> static typename __nv_itex_trait< T> ::type 
#line 113
tex1Dfetch(T *ptr, ::cudaTextureObject_t obj, int x) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;::exit(___);}
#if 0
#line 114
{ 
#line 115
__nv_tex_surf_handler("__itex1Dfetch", ptr, obj, x); 
#line 116
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 118 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 119
tex1Dfetch(::cudaTextureObject_t texObject, int x) {int volatile ___ = 1;(void)texObject;(void)x;::exit(___);}
#if 0
#line 120
{ 
#line 121
T ret; 
#line 122
tex1Dfetch(&ret, texObject, x); 
#line 123
return ret; 
#line 124
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 126 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 127
tex1D(T *ptr, ::cudaTextureObject_t obj, float x) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;::exit(___);}
#if 0
#line 128
{ 
#line 129
__nv_tex_surf_handler("__itex1D", ptr, obj, x); 
#line 130
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 133 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 134
tex1D(::cudaTextureObject_t texObject, float x) {int volatile ___ = 1;(void)texObject;(void)x;::exit(___);}
#if 0
#line 135
{ 
#line 136
T ret; 
#line 137
tex1D(&ret, texObject, x); 
#line 138
return ret; 
#line 139
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 142 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 143
tex2D(T *ptr, ::cudaTextureObject_t obj, float x, float y) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;::exit(___);}
#if 0
#line 144
{ 
#line 145
__nv_tex_surf_handler("__itex2D", ptr, obj, x, y); 
#line 146
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 148 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 149
tex2D(::cudaTextureObject_t texObject, float x, float y) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;::exit(___);}
#if 0
#line 150
{ 
#line 151
T ret; 
#line 152
tex2D(&ret, texObject, x, y); 
#line 153
return ret; 
#line 154
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 157 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 158
tex2D(T *ptr, ::cudaTextureObject_t obj, float x, float y, bool *
#line 159
isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)isResident;::exit(___);}
#if 0
#line 160
{ 
#line 161
unsigned char res; 
#line 162
__nv_tex_surf_handler("__itex2D_sparse", ptr, obj, x, y, &res); 
#line 163
(*isResident) = (res != 0); 
#line 164
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 166 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 167
tex2D(::cudaTextureObject_t texObject, float x, float y, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)isResident;::exit(___);}
#if 0
#line 168
{ 
#line 169
T ret; 
#line 170
tex2D(&ret, texObject, x, y, isResident); 
#line 171
return ret; 
#line 172
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 177 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 178
tex3D(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 179
{ 
#line 180
__nv_tex_surf_handler("__itex3D", ptr, obj, x, y, z); 
#line 181
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 184
tex3D(::cudaTextureObject_t texObject, float x, float y, float z) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 185
{ 
#line 186
T ret; 
#line 187
tex3D(&ret, texObject, x, y, z); 
#line 188
return ret; 
#line 189
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 192 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 193
tex3D(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, bool *
#line 194
isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)isResident;::exit(___);}
#if 0
#line 195
{ 
#line 196
unsigned char res; 
#line 197
__nv_tex_surf_handler("__itex3D_sparse", ptr, obj, x, y, z, &res); 
#line 198
(*isResident) = (res != 0); 
#line 199
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 201 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 202
tex3D(::cudaTextureObject_t texObject, float x, float y, float z, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)isResident;::exit(___);}
#if 0
#line 203
{ 
#line 204
T ret; 
#line 205
tex3D(&ret, texObject, x, y, z, isResident); 
#line 206
return ret; 
#line 207
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 211 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 212
tex1DLayered(T *ptr, ::cudaTextureObject_t obj, float x, int layer) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)layer;::exit(___);}
#if 0
#line 213
{ 
#line 214
__nv_tex_surf_handler("__itex1DLayered", ptr, obj, x, layer); 
#line 215
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 217 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 218
tex1DLayered(::cudaTextureObject_t texObject, float x, int layer) {int volatile ___ = 1;(void)texObject;(void)x;(void)layer;::exit(___);}
#if 0
#line 219
{ 
#line 220
T ret; 
#line 221
tex1DLayered(&ret, texObject, x, layer); 
#line 222
return ret; 
#line 223
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 225 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 226
tex2DLayered(T *ptr, ::cudaTextureObject_t obj, float x, float y, int layer) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;::exit(___);}
#if 0
#line 227
{ 
#line 228
__nv_tex_surf_handler("__itex2DLayered", ptr, obj, x, y, layer); 
#line 229
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 231 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 232
tex2DLayered(::cudaTextureObject_t texObject, float x, float y, int layer) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)layer;::exit(___);}
#if 0
#line 233
{ 
#line 234
T ret; 
#line 235
tex2DLayered(&ret, texObject, x, y, layer); 
#line 236
return ret; 
#line 237
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 240 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 241
tex2DLayered(T *ptr, ::cudaTextureObject_t obj, float x, float y, int layer, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;(void)isResident;::exit(___);}
#if 0
#line 242
{ 
#line 243
unsigned char res; 
#line 244
__nv_tex_surf_handler("__itex2DLayered_sparse", ptr, obj, x, y, layer, &res); 
#line 245
(*isResident) = (res != 0); 
#line 246
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 248 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 249
tex2DLayered(::cudaTextureObject_t texObject, float x, float y, int layer, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)layer;(void)isResident;::exit(___);}
#if 0
#line 250
{ 
#line 251
T ret; 
#line 252
tex2DLayered(&ret, texObject, x, y, layer, isResident); 
#line 253
return ret; 
#line 254
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 258 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 259
texCubemap(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 260
{ 
#line 261
__nv_tex_surf_handler("__itexCubemap", ptr, obj, x, y, z); 
#line 262
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 265 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 266
texCubemap(::cudaTextureObject_t texObject, float x, float y, float z) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;::exit(___);}
#if 0
#line 267
{ 
#line 268
T ret; 
#line 269
texCubemap(&ret, texObject, x, y, z); 
#line 270
return ret; 
#line 271
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 274 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 275
texCubemapLayered(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, int layer) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)layer;::exit(___);}
#if 0
#line 276
{ 
#line 277
__nv_tex_surf_handler("__itexCubemapLayered", ptr, obj, x, y, z, layer); 
#line 278
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 280 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 281
texCubemapLayered(::cudaTextureObject_t texObject, float x, float y, float z, int layer) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)layer;::exit(___);}
#if 0
#line 282
{ 
#line 283
T ret; 
#line 284
texCubemapLayered(&ret, texObject, x, y, z, layer); 
#line 285
return ret; 
#line 286
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 288 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 289
tex2Dgather(T *ptr, ::cudaTextureObject_t obj, float x, float y, int comp = 0) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)comp;::exit(___);}
#if 0
#line 290
{ 
#line 291
__nv_tex_surf_handler("__itex2Dgather", ptr, obj, x, y, comp); 
#line 292
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 294 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 295
tex2Dgather(::cudaTextureObject_t to, float x, float y, int comp = 0) {int volatile ___ = 1;(void)to;(void)x;(void)y;(void)comp;::exit(___);}
#if 0
#line 296
{ 
#line 297
T ret; 
#line 298
tex2Dgather(&ret, to, x, y, comp); 
#line 299
return ret; 
#line 300
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 303 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 304
tex2Dgather(T *ptr, ::cudaTextureObject_t obj, float x, float y, bool *isResident, int comp = 0) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)isResident;(void)comp;::exit(___);}
#if 0
#line 305
{ 
#line 306
unsigned char res; 
#line 307
__nv_tex_surf_handler("__itex2Dgather_sparse", ptr, obj, x, y, comp, &res); 
#line 308
(*isResident) = (res != 0); 
#line 309
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 311 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 312
tex2Dgather(::cudaTextureObject_t to, float x, float y, bool *isResident, int comp = 0) {int volatile ___ = 1;(void)to;(void)x;(void)y;(void)isResident;(void)comp;::exit(___);}
#if 0
#line 313
{ 
#line 314
T ret; 
#line 315
tex2Dgather(&ret, to, x, y, isResident, comp); 
#line 316
return ret; 
#line 317
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 321 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 322
tex1DLod(T *ptr, ::cudaTextureObject_t obj, float x, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)level;::exit(___);}
#if 0
#line 323
{ 
#line 324
__nv_tex_surf_handler("__itex1DLod", ptr, obj, x, level); 
#line 325
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 327 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 328
tex1DLod(::cudaTextureObject_t texObject, float x, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)level;::exit(___);}
#if 0
#line 329
{ 
#line 330
T ret; 
#line 331
tex1DLod(&ret, texObject, x, level); 
#line 332
return ret; 
#line 333
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 336 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 337
tex2DLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)level;::exit(___);}
#if 0
#line 338
{ 
#line 339
__nv_tex_surf_handler("__itex2DLod", ptr, obj, x, y, level); 
#line 340
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 342 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 343
tex2DLod(::cudaTextureObject_t texObject, float x, float y, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)level;::exit(___);}
#if 0
#line 344
{ 
#line 345
T ret; 
#line 346
tex2DLod(&ret, texObject, x, y, level); 
#line 347
return ret; 
#line 348
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 352 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 353
tex2DLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, float level, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)level;(void)isResident;::exit(___);}
#if 0
#line 354
{ 
#line 355
unsigned char res; 
#line 356
__nv_tex_surf_handler("__itex2DLod_sparse", ptr, obj, x, y, level, &res); 
#line 357
(*isResident) = (res != 0); 
#line 358
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 360 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 361
tex2DLod(::cudaTextureObject_t texObject, float x, float y, float level, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)level;(void)isResident;::exit(___);}
#if 0
#line 362
{ 
#line 363
T ret; 
#line 364
tex2DLod(&ret, texObject, x, y, level, isResident); 
#line 365
return ret; 
#line 366
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 371 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 372
tex3DLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)level;::exit(___);}
#if 0
#line 373
{ 
#line 374
__nv_tex_surf_handler("__itex3DLod", ptr, obj, x, y, z, level); 
#line 375
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 377 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 378
tex3DLod(::cudaTextureObject_t texObject, float x, float y, float z, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)level;::exit(___);}
#if 0
#line 379
{ 
#line 380
T ret; 
#line 381
tex3DLod(&ret, texObject, x, y, z, level); 
#line 382
return ret; 
#line 383
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 386 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 387
tex3DLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, float level, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)level;(void)isResident;::exit(___);}
#if 0
#line 388
{ 
#line 389
unsigned char res; 
#line 390
__nv_tex_surf_handler("__itex3DLod_sparse", ptr, obj, x, y, z, level, &res); 
#line 391
(*isResident) = (res != 0); 
#line 392
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 394 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 395
tex3DLod(::cudaTextureObject_t texObject, float x, float y, float z, float level, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)level;(void)isResident;::exit(___);}
#if 0
#line 396
{ 
#line 397
T ret; 
#line 398
tex3DLod(&ret, texObject, x, y, z, level, isResident); 
#line 399
return ret; 
#line 400
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 405 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 406
tex1DLayeredLod(T *ptr, ::cudaTextureObject_t obj, float x, int layer, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)layer;(void)level;::exit(___);}
#if 0
#line 407
{ 
#line 408
__nv_tex_surf_handler("__itex1DLayeredLod", ptr, obj, x, layer, level); 
#line 409
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 411 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 412
tex1DLayeredLod(::cudaTextureObject_t texObject, float x, int layer, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)layer;(void)level;::exit(___);}
#if 0
#line 413
{ 
#line 414
T ret; 
#line 415
tex1DLayeredLod(&ret, texObject, x, layer, level); 
#line 416
return ret; 
#line 417
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 420 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 421
tex2DLayeredLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, int layer, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;(void)level;::exit(___);}
#if 0
#line 422
{ 
#line 423
__nv_tex_surf_handler("__itex2DLayeredLod", ptr, obj, x, y, layer, level); 
#line 424
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 426 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 427
tex2DLayeredLod(::cudaTextureObject_t texObject, float x, float y, int layer, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)layer;(void)level;::exit(___);}
#if 0
#line 428
{ 
#line 429
T ret; 
#line 430
tex2DLayeredLod(&ret, texObject, x, y, layer, level); 
#line 431
return ret; 
#line 432
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 435 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 436
tex2DLayeredLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, int layer, float level, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;(void)level;(void)isResident;::exit(___);}
#if 0
#line 437
{ 
#line 438
unsigned char res; 
#line 439
__nv_tex_surf_handler("__itex2DLayeredLod_sparse", ptr, obj, x, y, layer, level, &res); 
#line 440
(*isResident) = (res != 0); 
#line 441
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 443 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 444
tex2DLayeredLod(::cudaTextureObject_t texObject, float x, float y, int layer, float level, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)layer;(void)level;(void)isResident;::exit(___);}
#if 0
#line 445
{ 
#line 446
T ret; 
#line 447
tex2DLayeredLod(&ret, texObject, x, y, layer, level, isResident); 
#line 448
return ret; 
#line 449
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 452 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 453
texCubemapLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)level;::exit(___);}
#if 0
#line 454
{ 
#line 455
__nv_tex_surf_handler("__itexCubemapLod", ptr, obj, x, y, z, level); 
#line 456
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 458 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 459
texCubemapLod(::cudaTextureObject_t texObject, float x, float y, float z, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)level;::exit(___);}
#if 0
#line 460
{ 
#line 461
T ret; 
#line 462
texCubemapLod(&ret, texObject, x, y, z, level); 
#line 463
return ret; 
#line 464
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 467 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 468
texCubemapGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, ::float4 dPdx, ::float4 dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 469
{ 
#line 470
__nv_tex_surf_handler("__itexCubemapGrad_v2", ptr, obj, x, y, z, &dPdx, &dPdy); 
#line 471
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 473 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 474
texCubemapGrad(::cudaTextureObject_t texObject, float x, float y, float z, ::float4 dPdx, ::float4 dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 475
{ 
#line 476
T ret; 
#line 477
texCubemapGrad(&ret, texObject, x, y, z, dPdx, dPdy); 
#line 478
return ret; 
#line 479
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 481 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 482
texCubemapLayeredLod(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, int layer, float level) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)layer;(void)level;::exit(___);}
#if 0
#line 483
{ 
#line 484
__nv_tex_surf_handler("__itexCubemapLayeredLod", ptr, obj, x, y, z, layer, level); 
#line 485
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 487 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 488
texCubemapLayeredLod(::cudaTextureObject_t texObject, float x, float y, float z, int layer, float level) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)layer;(void)level;::exit(___);}
#if 0
#line 489
{ 
#line 490
T ret; 
#line 491
texCubemapLayeredLod(&ret, texObject, x, y, z, layer, level); 
#line 492
return ret; 
#line 493
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 495 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 496
tex1DGrad(T *ptr, ::cudaTextureObject_t obj, float x, float dPdx, float dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 497
{ 
#line 498
__nv_tex_surf_handler("__itex1DGrad", ptr, obj, x, dPdx, dPdy); 
#line 499
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 501 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 502
tex1DGrad(::cudaTextureObject_t texObject, float x, float dPdx, float dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 503
{ 
#line 504
T ret; 
#line 505
tex1DGrad(&ret, texObject, x, dPdx, dPdy); 
#line 506
return ret; 
#line 507
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 510 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 511
tex2DGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, ::float2 dPdx, ::float2 dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 512
{ 
#line 513
__nv_tex_surf_handler("__itex2DGrad_v2", ptr, obj, x, y, &dPdx, &dPdy); 
#line 514
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 516 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 517
tex2DGrad(::cudaTextureObject_t texObject, float x, float y, ::float2 dPdx, ::float2 dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 518
{ 
#line 519
T ret; 
#line 520
tex2DGrad(&ret, texObject, x, y, dPdx, dPdy); 
#line 521
return ret; 
#line 522
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 525 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 526
tex2DGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, ::float2 dPdx, ::float2 dPdy, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)dPdx;(void)dPdy;(void)isResident;::exit(___);}
#if 0
#line 527
{ 
#line 528
unsigned char res; 
#line 529
__nv_tex_surf_handler("__itex2DGrad_sparse", ptr, obj, x, y, &dPdx, &dPdy, &res); 
#line 530
(*isResident) = (res != 0); 
#line 531
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 533 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 534
tex2DGrad(::cudaTextureObject_t texObject, float x, float y, ::float2 dPdx, ::float2 dPdy, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)dPdx;(void)dPdy;(void)isResident;::exit(___);}
#if 0
#line 535
{ 
#line 536
T ret; 
#line 537
tex2DGrad(&ret, texObject, x, y, dPdx, dPdy, isResident); 
#line 538
return ret; 
#line 539
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 543 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 544
tex3DGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, ::float4 dPdx, ::float4 dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 545
{ 
#line 546
__nv_tex_surf_handler("__itex3DGrad_v2", ptr, obj, x, y, z, &dPdx, &dPdy); 
#line 547
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 549 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 550
tex3DGrad(::cudaTextureObject_t texObject, float x, float y, float z, ::float4 dPdx, ::float4 dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 551
{ 
#line 552
T ret; 
#line 553
tex3DGrad(&ret, texObject, x, y, z, dPdx, dPdy); 
#line 554
return ret; 
#line 555
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 558 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 559
tex3DGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, ::float4 dPdx, ::float4 dPdy, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)dPdx;(void)dPdy;(void)isResident;::exit(___);}
#if 0
#line 560
{ 
#line 561
unsigned char res; 
#line 562
__nv_tex_surf_handler("__itex3DGrad_sparse", ptr, obj, x, y, z, &dPdx, &dPdy, &res); 
#line 563
(*isResident) = (res != 0); 
#line 564
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 566 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 567
tex3DGrad(::cudaTextureObject_t texObject, float x, float y, float z, ::float4 dPdx, ::float4 dPdy, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)dPdx;(void)dPdy;(void)isResident;::exit(___);}
#if 0
#line 568
{ 
#line 569
T ret; 
#line 570
tex3DGrad(&ret, texObject, x, y, z, dPdx, dPdy, isResident); 
#line 571
return ret; 
#line 572
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 577 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 578
tex1DLayeredGrad(T *ptr, ::cudaTextureObject_t obj, float x, int layer, float dPdx, float dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)layer;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 579
{ 
#line 580
__nv_tex_surf_handler("__itex1DLayeredGrad", ptr, obj, x, layer, dPdx, dPdy); 
#line 581
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 583 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 584
tex1DLayeredGrad(::cudaTextureObject_t texObject, float x, int layer, float dPdx, float dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)layer;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 585
{ 
#line 586
T ret; 
#line 587
tex1DLayeredGrad(&ret, texObject, x, layer, dPdx, dPdy); 
#line 588
return ret; 
#line 589
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 592 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 593
tex2DLayeredGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, int layer, ::float2 dPdx, ::float2 dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 594
{ 
#line 595
__nv_tex_surf_handler("__itex2DLayeredGrad_v2", ptr, obj, x, y, layer, &dPdx, &dPdy); 
#line 596
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 598 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 599
tex2DLayeredGrad(::cudaTextureObject_t texObject, float x, float y, int layer, ::float2 dPdx, ::float2 dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)layer;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 600
{ 
#line 601
T ret; 
#line 602
tex2DLayeredGrad(&ret, texObject, x, y, layer, dPdx, dPdy); 
#line 603
return ret; 
#line 604
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 607 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 608
tex2DLayeredGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, int layer, ::float2 dPdx, ::float2 dPdy, bool *isResident) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;(void)dPdx;(void)dPdy;(void)isResident;::exit(___);}
#if 0
#line 609
{ 
#line 610
unsigned char res; 
#line 611
__nv_tex_surf_handler("__itex2DLayeredGrad_sparse", ptr, obj, x, y, layer, &dPdx, &dPdy, &res); 
#line 612
(*isResident) = (res != 0); 
#line 613
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 615 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 616
tex2DLayeredGrad(::cudaTextureObject_t texObject, float x, float y, int layer, ::float2 dPdx, ::float2 dPdy, bool *isResident) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)layer;(void)dPdx;(void)dPdy;(void)isResident;::exit(___);}
#if 0
#line 617
{ 
#line 618
T ret; 
#line 619
tex2DLayeredGrad(&ret, texObject, x, y, layer, dPdx, dPdy, isResident); 
#line 620
return ret; 
#line 621
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 625 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static typename __nv_itex_trait< T> ::type 
#line 626
texCubemapLayeredGrad(T *ptr, ::cudaTextureObject_t obj, float x, float y, float z, int layer, ::float4 dPdx, ::float4 dPdy) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)layer;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 627
{ 
#line 628
__nv_tex_surf_handler("__itexCubemapLayeredGrad_v2", ptr, obj, x, y, z, layer, &dPdx, &dPdy); 
#line 629
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 631 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\texture_indirect_functions.h"
template< class T> static T 
#line 632
texCubemapLayeredGrad(::cudaTextureObject_t texObject, float x, float y, float z, int layer, ::float4 dPdx, ::float4 dPdy) {int volatile ___ = 1;(void)texObject;(void)x;(void)y;(void)z;(void)layer;(void)dPdx;(void)dPdy;::exit(___);}
#if 0
#line 633
{ 
#line 634
T ret; 
#line 635
texCubemapLayeredGrad(&ret, texObject, x, y, z, layer, dPdx, dPdy); 
#line 636
return ret; 
#line 637
} 
#endif

__pragma(warning(pop))

#line 58 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> struct __nv_isurf_trait { }; 
#line 59
template<> struct __nv_isurf_trait< char>  { typedef void type; }; 
#line 60
template<> struct __nv_isurf_trait< signed char>  { typedef void type; }; 
#line 61
template<> struct __nv_isurf_trait< char1>  { typedef void type; }; 
#line 62
template<> struct __nv_isurf_trait< unsigned char>  { typedef void type; }; 
#line 63
template<> struct __nv_isurf_trait< uchar1>  { typedef void type; }; 
#line 64
template<> struct __nv_isurf_trait< short>  { typedef void type; }; 
#line 65
template<> struct __nv_isurf_trait< short1>  { typedef void type; }; 
#line 66
template<> struct __nv_isurf_trait< unsigned short>  { typedef void type; }; 
#line 67
template<> struct __nv_isurf_trait< ushort1>  { typedef void type; }; 
#line 68
template<> struct __nv_isurf_trait< int>  { typedef void type; }; 
#line 69
template<> struct __nv_isurf_trait< int1>  { typedef void type; }; 
#line 70
template<> struct __nv_isurf_trait< unsigned>  { typedef void type; }; 
#line 71
template<> struct __nv_isurf_trait< uint1>  { typedef void type; }; 
#line 72
template<> struct __nv_isurf_trait< __int64>  { typedef void type; }; 
#line 73
template<> struct __nv_isurf_trait< longlong1>  { typedef void type; }; 
#line 74
template<> struct __nv_isurf_trait< unsigned __int64>  { typedef void type; }; 
#line 75
template<> struct __nv_isurf_trait< ulonglong1>  { typedef void type; }; 
#line 76
template<> struct __nv_isurf_trait< float>  { typedef void type; }; 
#line 77
template<> struct __nv_isurf_trait< float1>  { typedef void type; }; 
#line 79
template<> struct __nv_isurf_trait< char2>  { typedef void type; }; 
#line 80
template<> struct __nv_isurf_trait< uchar2>  { typedef void type; }; 
#line 81
template<> struct __nv_isurf_trait< short2>  { typedef void type; }; 
#line 82
template<> struct __nv_isurf_trait< ushort2>  { typedef void type; }; 
#line 83
template<> struct __nv_isurf_trait< int2>  { typedef void type; }; 
#line 84
template<> struct __nv_isurf_trait< uint2>  { typedef void type; }; 
#line 85
template<> struct __nv_isurf_trait< longlong2>  { typedef void type; }; 
#line 86
template<> struct __nv_isurf_trait< ulonglong2>  { typedef void type; }; 
#line 87
template<> struct __nv_isurf_trait< float2>  { typedef void type; }; 
#line 89
template<> struct __nv_isurf_trait< char4>  { typedef void type; }; 
#line 90
template<> struct __nv_isurf_trait< uchar4>  { typedef void type; }; 
#line 91
template<> struct __nv_isurf_trait< short4>  { typedef void type; }; 
#line 92
template<> struct __nv_isurf_trait< ushort4>  { typedef void type; }; 
#line 93
template<> struct __nv_isurf_trait< int4>  { typedef void type; }; 
#line 94
template<> struct __nv_isurf_trait< uint4>  { typedef void type; }; 
#line 95
template<> struct __nv_isurf_trait< float4>  { typedef void type; }; 
__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 98
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 99
surf1Dread(T *ptr, ::cudaSurfaceObject_t obj, int x, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)mode;::exit(___);}
#if 0
#line 100
{ 
#line 101
__nv_tex_surf_handler("__isurf1Dread", ptr, obj, x, mode); 
#line 102
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 104 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 105
surf1Dread(::cudaSurfaceObject_t surfObject, int x, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)boundaryMode;::exit(___);}
#if 0
#line 106
{ 
#line 107
T ret; 
#line 108
surf1Dread(&ret, surfObject, x, boundaryMode); 
#line 109
return ret; 
#line 110
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 112 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 113
surf2Dread(T *ptr, ::cudaSurfaceObject_t obj, int x, int y, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)mode;::exit(___);}
#if 0
#line 114
{ 
#line 115
__nv_tex_surf_handler("__isurf2Dread", ptr, obj, x, y, mode); 
#line 116
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 118 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 119
surf2Dread(::cudaSurfaceObject_t surfObject, int x, int y, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)y;(void)boundaryMode;::exit(___);}
#if 0
#line 120
{ 
#line 121
T ret; 
#line 122
surf2Dread(&ret, surfObject, x, y, boundaryMode); 
#line 123
return ret; 
#line 124
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 127 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 128
surf3Dread(T *ptr, ::cudaSurfaceObject_t obj, int x, int y, int z, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)z;(void)mode;::exit(___);}
#if 0
#line 129
{ 
#line 130
__nv_tex_surf_handler("__isurf3Dread", ptr, obj, x, y, z, mode); 
#line 131
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 133 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 134
surf3Dread(::cudaSurfaceObject_t surfObject, int x, int y, int z, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)y;(void)z;(void)boundaryMode;::exit(___);}
#if 0
#line 135
{ 
#line 136
T ret; 
#line 137
surf3Dread(&ret, surfObject, x, y, z, boundaryMode); 
#line 138
return ret; 
#line 139
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 141 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 142
surf1DLayeredread(T *ptr, ::cudaSurfaceObject_t obj, int x, int layer, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)layer;(void)mode;::exit(___);}
#if 0
#line 143
{ 
#line 144
__nv_tex_surf_handler("__isurf1DLayeredread", ptr, obj, x, layer, mode); 
#line 145
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 147 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 148
surf1DLayeredread(::cudaSurfaceObject_t surfObject, int x, int layer, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)layer;(void)boundaryMode;::exit(___);}
#if 0
#line 149
{ 
#line 150
T ret; 
#line 151
surf1DLayeredread(&ret, surfObject, x, layer, boundaryMode); 
#line 152
return ret; 
#line 153
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 155 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 156
surf2DLayeredread(T *ptr, ::cudaSurfaceObject_t obj, int x, int y, int layer, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layer;(void)mode;::exit(___);}
#if 0
#line 157
{ 
#line 158
__nv_tex_surf_handler("__isurf2DLayeredread", ptr, obj, x, y, layer, mode); 
#line 159
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 161 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 162
surf2DLayeredread(::cudaSurfaceObject_t surfObject, int x, int y, int layer, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)y;(void)layer;(void)boundaryMode;::exit(___);}
#if 0
#line 163
{ 
#line 164
T ret; 
#line 165
surf2DLayeredread(&ret, surfObject, x, y, layer, boundaryMode); 
#line 166
return ret; 
#line 167
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 169 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 170
surfCubemapread(T *ptr, ::cudaSurfaceObject_t obj, int x, int y, int face, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)face;(void)mode;::exit(___);}
#if 0
#line 171
{ 
#line 172
__nv_tex_surf_handler("__isurfCubemapread", ptr, obj, x, y, face, mode); 
#line 173
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 175 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 176
surfCubemapread(::cudaSurfaceObject_t surfObject, int x, int y, int face, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)y;(void)face;(void)boundaryMode;::exit(___);}
#if 0
#line 177
{ 
#line 178
T ret; 
#line 179
surfCubemapread(&ret, surfObject, x, y, face, boundaryMode); 
#line 180
return ret; 
#line 181
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 183 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 184
surfCubemapLayeredread(T *ptr, ::cudaSurfaceObject_t obj, int x, int y, int layerface, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)ptr;(void)obj;(void)x;(void)y;(void)layerface;(void)mode;::exit(___);}
#if 0
#line 185
{ 
#line 186
__nv_tex_surf_handler("__isurfCubemapLayeredread", ptr, obj, x, y, layerface, mode); 
#line 187
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 189 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static T 
#line 190
surfCubemapLayeredread(::cudaSurfaceObject_t surfObject, int x, int y, int layerface, ::cudaSurfaceBoundaryMode boundaryMode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)surfObject;(void)x;(void)y;(void)layerface;(void)boundaryMode;::exit(___);}
#if 0
#line 191
{ 
#line 192
T ret; 
#line 193
surfCubemapLayeredread(&ret, surfObject, x, y, layerface, boundaryMode); 
#line 194
return ret; 
#line 195
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 197 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 198
surf1Dwrite(T val, ::cudaSurfaceObject_t obj, int x, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)mode;::exit(___);}
#if 0
#line 199
{ 
#line 200
__nv_tex_surf_handler("__isurf1Dwrite_v2", &val, obj, x, mode); 
#line 201
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 203 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 204
surf2Dwrite(T val, ::cudaSurfaceObject_t obj, int x, int y, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)y;(void)mode;::exit(___);}
#if 0
#line 205
{ 
#line 206
__nv_tex_surf_handler("__isurf2Dwrite_v2", &val, obj, x, y, mode); 
#line 207
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 209 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 210
surf3Dwrite(T val, ::cudaSurfaceObject_t obj, int x, int y, int z, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)y;(void)z;(void)mode;::exit(___);}
#if 0
#line 211
{ 
#line 212
__nv_tex_surf_handler("__isurf3Dwrite_v2", &val, obj, x, y, z, mode); 
#line 213
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 215 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 216
surf1DLayeredwrite(T val, ::cudaSurfaceObject_t obj, int x, int layer, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)layer;(void)mode;::exit(___);}
#if 0
#line 217
{ 
#line 218
__nv_tex_surf_handler("__isurf1DLayeredwrite_v2", &val, obj, x, layer, mode); 
#line 219
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 221 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 222
surf2DLayeredwrite(T val, ::cudaSurfaceObject_t obj, int x, int y, int layer, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)y;(void)layer;(void)mode;::exit(___);}
#if 0
#line 223
{ 
#line 224
__nv_tex_surf_handler("__isurf2DLayeredwrite_v2", &val, obj, x, y, layer, mode); 
#line 225
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 227 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 228
surfCubemapwrite(T val, ::cudaSurfaceObject_t obj, int x, int y, int face, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)y;(void)face;(void)mode;::exit(___);}
#if 0
#line 229
{ 
#line 230
__nv_tex_surf_handler("__isurfCubemapwrite_v2", &val, obj, x, y, face, mode); 
#line 231
} 
#endif

__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable : 4505)) /* "unreferenced local function has been removed" */

#line 233 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\surface_indirect_functions.h"
template< class T> static typename __nv_isurf_trait< T> ::type 
#line 234
surfCubemapLayeredwrite(T val, ::cudaSurfaceObject_t obj, int x, int y, int layerface, ::cudaSurfaceBoundaryMode mode = cudaBoundaryModeTrap) {int volatile ___ = 1;(void)val;(void)obj;(void)x;(void)y;(void)layerface;(void)mode;::exit(___);}
#if 0
#line 235
{ 
#line 236
__nv_tex_surf_handler("__isurfCubemapLayeredwrite_v2", &val, obj, x, y, layerface, mode); 
#line 237
} 
#endif

__pragma(warning(pop))

#line 2932 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/device_functions.h"
extern "C" unsigned __stdcall __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim = 1, size_t sharedMem = 0, CUstream_st * stream = 0); 
#line 2938
extern "C" cudaError_t __stdcall __cudaGetKernel(cudaKernel_t *, const void *); 
#line 2940
extern "C" cudaError_t __stdcall __cudaLaunchKernel(cudaKernel_t kernel, dim3 gridDim, dim3 blockDim, void ** args, size_t sharedMem, cudaStream_t stream); 
#line 2949
extern "C" cudaError_t __stdcall __cudaLaunchKernel_ptsz(cudaKernel_t kernel, dim3 gridDim, dim3 blockDim, void ** args, size_t sharedMem, cudaStream_t stream); 
#line 2959
static inline cudaError_t __cudaLaunchKernel_helper(cudaKernel_t 
#line 2960
kernel, dim3 
#line 2961
gridDim, dim3 
#line 2962
blockDim, void **
#line 2963
args, size_t 
#line 2964
sharedMem, cudaStream_t 
#line 2965
stream) 
#line 2966
{ 
#line 2971 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/device_functions.h"
return __cudaLaunchKernel(kernel, gridDim, blockDim, args, sharedMem, stream); 
#line 2974 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/device_functions.h"
} 
#line 2977 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\crt/device_functions.h"
enum { 
#line 2978
__NV_ATOMIC_RELAXED, 
#line 2979
__NV_ATOMIC_CONSUME, 
#line 2980
__NV_ATOMIC_ACQUIRE, 
#line 2981
__NV_ATOMIC_RELEASE, 
#line 2982
__NV_ATOMIC_ACQ_REL, 
#line 2983
__NV_ATOMIC_SEQ_CST
#line 2984
}; 
#line 2986
enum { 
#line 2987
__NV_THREAD_SCOPE_THREAD, 
#line 2988
__NV_THREAD_SCOPE_BLOCK, 
#line 2989
__NV_THREAD_SCOPE_CLUSTER, 
#line 2990
__NV_THREAD_SCOPE_DEVICE, 
#line 2991
__NV_THREAD_SCOPE_SYSTEM
#line 2992
}; 
#line 68 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_launch_parameters.h"
extern "C" {
#line 71 "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v13.3\\include\\device_launch_parameters.h"
extern const uint3 __device_builtin_variable_threadIdx; 
#line 72
extern const uint3 __device_builtin_variable_blockIdx; 
#line 73
extern const dim3 __device_builtin_variable_blockDim; 
#line 74
extern const dim3 __device_builtin_variable_gridDim; 
#line 75
extern const int __device_builtin_variable_warpSize; 
#line 80
}
#line 14 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cstddef"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 27
namespace std { 
#line 28
using ::ptrdiff_t;
#line 30
using max_align_t = double; 
#line 31
using nullptr_t = decltype(nullptr); 
#line 99
}
#line 102
using std::max_align_t;
#line 111
#pragma warning(pop)
#pragma pack ( pop )
#line 12 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\initializer_list"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 25
namespace std { 
#line 26
template < class _Elem >
class [ [ msvc :: no_specializations ( "Specializing this standard library template is forbidden by N5014 [initializer.list.syn]/2" ) ] ] initializer_list {
public :
    using value_type = _Elem;
    using reference = const _Elem &;
    using const_reference = const _Elem &;
    using size_type = size_t;

    using iterator = const _Elem *;
    using const_iterator = const _Elem *;

    constexpr initializer_list ( ) noexcept : _First ( nullptr ), _Last ( nullptr ) { }

    constexpr initializer_list ( const _Elem * _First_arg, const _Elem * _Last_arg ) noexcept
        : _First ( _First_arg ), _Last ( _Last_arg ) { }

    [ [ nodiscard ] ] constexpr const _Elem * begin ( ) const noexcept {
        return _First;
    }

    [ [ nodiscard ] ] constexpr const _Elem * end ( ) const noexcept {
        return _Last;
    }

    [ [ nodiscard ] ] constexpr size_t size ( ) const noexcept {
        return static_cast < size_t > ( _Last - _First );
    }

    [ [ nodiscard ] ] constexpr bool empty ( ) const noexcept {
        return _First == _Last;
    }

    [ [ nodiscard ] ] constexpr const _Elem * data ( ) const noexcept {
        return _First;
    }

private :
    const _Elem * _First;
    const _Elem * _Last;
};
#line 67
}
#line 75
#pragma warning(pop)
#pragma pack ( pop )
#line 15 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\stdint.h"
#pragma warning(push)
#pragma warning(disable: 4514 4820 )
#line 18
typedef signed char int8_t; 
#line 19
typedef short int16_t; 
#line 20
typedef int int32_t; 
#line 21
typedef __int64 int64_t; 
#line 22
typedef unsigned char uint8_t; 
#line 23
typedef unsigned short uint16_t; 
#line 24
typedef unsigned uint32_t; 
#line 25
typedef unsigned __int64 uint64_t; 
#line 27
typedef signed char int_least8_t; 
#line 28
typedef short int_least16_t; 
#line 29
typedef int int_least32_t; 
#line 30
typedef __int64 int_least64_t; 
#line 31
typedef unsigned char uint_least8_t; 
#line 32
typedef unsigned short uint_least16_t; 
#line 33
typedef unsigned uint_least32_t; 
#line 34
typedef unsigned __int64 uint_least64_t; 
#line 36
typedef signed char int_fast8_t; 
#line 37
typedef int int_fast16_t; 
#line 38
typedef int int_fast32_t; 
#line 39
typedef __int64 int_fast64_t; 
#line 40
typedef unsigned char uint_fast8_t; 
#line 41
typedef unsigned uint_fast16_t; 
#line 42
typedef unsigned uint_fast32_t; 
#line 43
typedef unsigned __int64 uint_fast64_t; 
#line 45
typedef __int64 intmax_t; 
#line 46
typedef unsigned __int64 uintmax_t; 
#line 136 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\stdint.h"
#pragma warning(pop)
#line 13 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\cstdint"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 20
namespace std { 
#line 21
using ::int8_t;
#line 22
using ::int16_t;
#line 23
using ::int32_t;
#line 24
using ::int64_t;
#line 25
using ::uint8_t;
#line 26
using ::uint16_t;
#line 27
using ::uint32_t;
#line 28
using ::uint64_t;
#line 30
using ::int_least8_t;
#line 31
using ::int_least16_t;
#line 32
using ::int_least32_t;
#line 33
using ::int_least64_t;
#line 34
using ::uint_least8_t;
#line 35
using ::uint_least16_t;
#line 36
using ::uint_least32_t;
#line 37
using ::uint_least64_t;
#line 39
using ::int_fast8_t;
#line 40
using ::int_fast16_t;
#line 41
using ::int_fast32_t;
#line 42
using ::int_fast64_t;
#line 43
using ::uint_fast8_t;
#line 44
using ::uint_fast16_t;
#line 45
using ::uint_fast32_t;
#line 46
using ::uint_fast64_t;
#line 48
using ::intmax_t;
#line 49
using ::intptr_t;
#line 50
using ::uintmax_t;
#line 51
using ::uintptr_t;
#line 52
}
#line 56
#pragma warning(pop)
#pragma pack ( pop )
#line 14 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 31
namespace std { 
#line 32
template< bool _First_value, class _First, class ..._Rest> 
#line 33
struct _Conjunction { 
#line 34
using type = _First; 
#line 35
}; 
#line 37
template< class _True, class _Next, class ..._Rest> 
#line 38
struct _Conjunction< true, _True, _Next, _Rest...>  { 
#line 39
using type = typename std::_Conjunction< static_cast< bool>(_Next::value), _Next, _Rest...> ::type; 
#line 40
}; 
#line 42
template< class ..._Traits> 
#line 43
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] conjunction : public true_type { }; 
#line 45
template< class _First, class ..._Rest> 
#line 46
struct conjunction< _First, _Rest...>  : public _Conjunction< static_cast< bool>(_First::value), _First, _Rest...> ::type { 
#line 48
}; 
#line 50
template< class ..._Traits> 
#line 51
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool conjunction_v = (conjunction< _Traits...> ::value); 
#line 53
template< class _Trait> 
#line 54
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] negation : public bool_constant< !(static_cast< bool>(_Trait::value))>  { 
#line 56
}; 
#line 58
template< class _Trait> 
#line 59
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool negation_v = (negation< _Trait> ::value); 
#line 61
template< class _Ty> 
#line 62
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_void_v = is_same_v< remove_cv_t< _Ty> , void> ; 
#line 64
template< class _Ty> 
#line 65
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_void : public bool_constant< is_void_v< _Ty> >  { }; 
#line 67
template< class ..._Types> using void_t = void; 
#line 70
template< class _Ty> 
#line 71
struct _Identity { 
#line 72
using type = _Ty; 
#line 73
}; 
#line 74
template< class _Ty> using _Identity_t
#line 75
 [[msvc::known_semantics]] = typename _Identity< _Ty> ::type; 
#line 78
template< class _Ty> 
#line 79
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] add_const { 
#line 80
using type = const _Ty; 
#line 81
}; 
#line 83
template< class _Ty> using add_const_t = typename add_const< _Ty> ::type; 
#line 86
template< class _Ty> 
#line 87
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] add_volatile { 
#line 88
using type = volatile _Ty; 
#line 89
}; 
#line 91
template< class _Ty> using add_volatile_t = typename add_volatile< _Ty> ::type; 
#line 94
template< class _Ty> 
#line 95
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] add_cv { 
#line 96
using type = const volatile _Ty; 
#line 97
}; 
#line 99
template< class _Ty> using add_cv_t = typename add_cv< _Ty> ::type; 
#line 102
template< class _Ty, class  = void> 
#line 103
struct _Add_reference { 
#line 104
using _Lvalue = _Ty; 
#line 105
using _Rvalue = _Ty; 
#line 106
}; 
#line 108
template< class _Ty> 
#line 109
struct _Add_reference< _Ty, void_t< _Ty &> >  { 
#line 110
using _Lvalue = _Ty &; 
#line 111
using _Rvalue = _Ty &&; 
#line 112
}; 
#line 114
template< class _Ty> 
#line 115
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] add_lvalue_reference { 
#line 116
using type = typename _Add_reference< _Ty> ::_Lvalue; 
#line 117
}; 
#line 119
template< class _Ty> using add_lvalue_reference_t = typename _Add_reference< _Ty> ::_Lvalue; 
#line 122
template< class _Ty> 
#line 123
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] add_rvalue_reference { 
#line 124
using type = typename _Add_reference< _Ty> ::_Rvalue; 
#line 125
}; 
#line 127
template< class _Ty> using add_rvalue_reference_t = typename _Add_reference< _Ty> ::_Rvalue; 
#line 130
template < class _Ty >
add_rvalue_reference_t < _Ty > declval ( ) noexcept {
    static_assert ( false, "Calling declval is ill-formed, see N4950 [declval]/2." );
}
#line 135
template< class _Ty> 
#line 136
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_extent { 
#line 137
using type = _Ty; 
#line 138
}; 
#line 140
template< class _Ty, size_t _Ix> 
#line 141
struct remove_extent< _Ty [_Ix]>  { 
#line 142
using type = _Ty; 
#line 143
}; 
#line 145
template< class _Ty> 
#line 146
struct remove_extent< _Ty []>  { 
#line 147
using type = _Ty; 
#line 148
}; 
#line 150
template< class _Ty> using remove_extent_t = typename remove_extent< _Ty> ::type; 
#line 153
template< class _Ty> 
#line 154
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_all_extents { 
#line 155
using type = _Ty; 
#line 156
}; 
#line 158
template< class _Ty, size_t _Ix> 
#line 159
struct remove_all_extents< _Ty [_Ix]>  { 
#line 160
using type = typename std::remove_all_extents< _Ty> ::type; 
#line 161
}; 
#line 163
template< class _Ty> 
#line 164
struct remove_all_extents< _Ty []>  { 
#line 165
using type = typename std::remove_all_extents< _Ty> ::type; 
#line 166
}; 
#line 168
template< class _Ty> using remove_all_extents_t = typename remove_all_extents< _Ty> ::type; 
#line 171
template< class _Ty> 
#line 172
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] remove_pointer { 
#line 173
using type = _Ty; 
#line 174
}; 
#line 176
template< class _Ty> 
#line 177
struct remove_pointer< _Ty *>  { 
#line 178
using type = _Ty; 
#line 179
}; 
#line 181
template< class _Ty> 
#line 182
struct remove_pointer< _Ty *const>  { 
#line 183
using type = _Ty; 
#line 184
}; 
#line 186
template< class _Ty> 
#line 187
struct remove_pointer< _Ty *volatile>  { 
#line 188
using type = _Ty; 
#line 189
}; 
#line 191
template< class _Ty> 
#line 192
struct remove_pointer< _Ty *const volatile>  { 
#line 193
using type = _Ty; 
#line 194
}; 
#line 196
template< class _Ty> using remove_pointer_t = typename remove_pointer< _Ty> ::type; 
#line 199
template< class _Ty, class  = void> 
#line 200
struct _Add_pointer { 
#line 201
using type = _Ty; 
#line 202
}; 
#line 204
template< class _Ty> 
#line 205
struct _Add_pointer< _Ty, void_t< remove_reference_t< _Ty>  *> >  { 
#line 206
using type = remove_reference_t< _Ty>  *; 
#line 207
}; 
#line 209
template< class _Ty> 
#line 210
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] add_pointer { 
#line 211
using type = typename _Add_pointer< _Ty> ::type; 
#line 212
}; 
#line 214
template< class _Ty> using add_pointer_t = typename _Add_pointer< _Ty> ::type; 
#line 217
template< class > 
#line 218
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_array_v = false; 
#line 220
template< class _Ty, size_t _Nx> constexpr bool 
#line 221
is_array_v< _Ty [_Nx]>  = true; 
#line 223
template< class _Ty> constexpr bool 
#line 224
is_array_v< _Ty []>  = true; 
#line 226
template< class _Ty> 
#line 227
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_array : public bool_constant< is_array_v< _Ty> >  { }; 
#line 249 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class > 
#line 250
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_lvalue_reference_v = false; 
#line 253
template< class _Ty> constexpr bool 
#line 254
is_lvalue_reference_v< _Ty &>  = true; 
#line 256
template< class _Ty> 
#line 257
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_lvalue_reference : public bool_constant< is_lvalue_reference_v< _Ty> >  { }; 
#line 259
template< class > 
#line 260
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_rvalue_reference_v = false; 
#line 263
template< class _Ty> constexpr bool 
#line 264
is_rvalue_reference_v< _Ty &&>  = true; 
#line 266
template< class _Ty> 
#line 267
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_rvalue_reference : public bool_constant< is_rvalue_reference_v< _Ty> >  { }; 
#line 269
template< class > 
#line 270
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_reference_v = false; 
#line 273
template< class _Ty> constexpr bool 
#line 274
is_reference_v< _Ty &>  = true; 
#line 276
template< class _Ty> constexpr bool 
#line 277
is_reference_v< _Ty &&>  = true; 
#line 279
template< class _Ty> 
#line 280
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_reference : public bool_constant< is_reference_v< _Ty> >  { }; 
#line 282
template< class > 
#line 283
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_pointer_v = false; 
#line 285
template< class _Ty> constexpr bool 
#line 286
is_pointer_v< _Ty *>  = true; 
#line 288
template< class _Ty> constexpr bool 
#line 289
is_pointer_v< _Ty *const>  = true; 
#line 291
template< class _Ty> constexpr bool 
#line 292
is_pointer_v< _Ty *volatile>  = true; 
#line 294
template< class _Ty> constexpr bool 
#line 295
is_pointer_v< _Ty *const volatile>  = true; 
#line 297
template< class _Ty> 
#line 298
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_pointer : public bool_constant< is_pointer_v< _Ty> >  { }; 
#line 300
template< class _Ty> 
#line 301
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_null_pointer_v = is_same_v< remove_cv_t< _Ty> , nullptr_t> ; 
#line 304
template< class _Ty> 
#line 305
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_null_pointer : public bool_constant< is_null_pointer_v< _Ty> >  { }; 
#line 307
template< class _Ty> 
#line 308
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_union : public bool_constant< __is_union(_Ty)>  { 
#line 309
}; 
#line 311
template< class _Ty> 
#line 312
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_union_v = __is_union(_Ty); 
#line 314
template< class _Ty> 
#line 315
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_class : public bool_constant< __is_class(_Ty)>  { 
#line 316
}; 
#line 318
template< class _Ty> 
#line 319
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_class_v = __is_class(_Ty); 
#line 321
template< class _Ty> 
#line 322
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_fundamental_v = (is_arithmetic_v< _Ty>  || is_void_v< _Ty> ) || is_null_pointer_v< _Ty> ; 
#line 325
template< class _Ty> 
#line 326
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_fundamental : public bool_constant< is_fundamental_v< _Ty> >  { 
#line 328
}; 
#line 330
template< class _From, class _To> 
#line 331
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_convertible : public bool_constant< __is_convertible_to(_From, _To)>  { 
#line 333
}; 
#line 335
template< class _From, class _To> 
#line 336
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_convertible_v = __is_convertible_to(_From, _To); 
#line 338
template< class _Ty> 
#line 339
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_enum : public bool_constant< __is_enum(_Ty)>  { 
#line 340
}; 
#line 342
template< class _Ty> 
#line 343
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_enum_v = __is_enum(_Ty); 
#line 362 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 363
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_compound : public bool_constant< !is_fundamental_v< _Ty> >  { 
#line 365
}; 
#line 367
template< class _Ty> 
#line 368
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_compound_v = (!is_fundamental_v< _Ty> ); 
#line 493 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class ..._Types> 
#line 494
struct _Arg_types { }; 
#line 496
template< class _Ty1> 
#line 497
struct _Arg_types< _Ty1>  { 
#line 498
using argument_type = _Ty1; 
#line 499
}; 
#line 501
template< class _Ty1, class _Ty2> 
#line 502
struct _Arg_types< _Ty1, _Ty2>  { 
#line 503
using first_argument_type = _Ty1; 
#line 504
using second_argument_type = _Ty2; 
#line 505
}; 
#line 507
template< class _Ty> 
#line 508
struct _Is_memfunptr { 
#line 509
using _Bool_type = false_type; 
#line 510
}; 
#line 522
template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...)>  : public _Arg_types< _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...)>  : public _Arg_types< _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) const>  : public _Arg_types< const _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) const>  : public _Arg_types< const _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) volatile>  : public _Arg_types< volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) volatile>  : public _Arg_types< volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) const volatile>  : public _Arg_types< const volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) const volatile>  : public _Arg_types< const volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) &>  : public _Arg_types< _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) &>  : public _Arg_types< _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) const &>  : public _Arg_types< const _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) const &>  : public _Arg_types< const _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) volatile &>  : public _Arg_types< volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) volatile &>  : public _Arg_types< volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) const volatile &>  : public _Arg_types< const volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) const volatile &>  : public _Arg_types< const volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< true, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) &&>  : public _Arg_types< _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) &&>  : public _Arg_types< _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) const &&>  : public _Arg_types< const _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) const &&>  : public _Arg_types< const _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) volatile &&>  : public _Arg_types< volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) volatile &&>  : public _Arg_types< volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__cdecl _Arg0::*)(_Types ...) const volatile &&>  : public _Arg_types< const volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (__vectorcall _Arg0::*)(_Types ...) const volatile &&>  : public _Arg_types< const volatile _Arg0 *, _Types...>  { using _Bool_type = std::true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false, _Ret (_Types ...)> ; }; 
#line 535
template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...)>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) const>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) volatile>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) const volatile>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) &>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) const &>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) volatile &>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) const volatile &>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) &&>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) const &&>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) volatile &&>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; template< class _Ret, class _Arg0, class ..._Types> struct _Is_memfunptr< _Ret (_Arg0::*)(_Types ..., ...) const volatile &&>  { using _Bool_type = true_type; using result_type = _Ret; using _Class_type = _Arg0; using _Guide_type = enable_if< false> ; }; 
#line 558 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 559
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_member_function_pointer_v = (_Is_memfunptr< remove_cv_t< _Ty> > ::_Bool_type::value); 
#line 563 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 564
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_member_function_pointer : public bool_constant< is_member_function_pointer_v< _Ty> >  { 
#line 565
}; 
#line 567
template< class > 
#line 568
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_const_v = false; 
#line 571
template< class _Ty> constexpr bool 
#line 572
is_const_v< const _Ty>  = true; 
#line 574
template< class _Ty> 
#line 575
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_const : public bool_constant< is_const_v< _Ty> >  { }; 
#line 577
template< class > 
#line 578
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_volatile_v = false; 
#line 581
template< class _Ty> constexpr bool 
#line 582
is_volatile_v< volatile _Ty>  = true; 
#line 584
template< class _Ty> 
#line 585
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_volatile : public bool_constant< is_volatile_v< _Ty> >  { }; 
#line 587
template< class _Ty> 
#line 588
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool 
#line 589
is_function_v = ((!is_const_v< const _Ty> ) && (!is_reference_v< _Ty> )); 
#line 592
template< class _Ty> 
#line 593
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_function : public bool_constant< is_function_v< _Ty> >  { }; 
#line 595
template< class _Ty> 
#line 596
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool 
#line 597
is_object_v = is_const_v< const _Ty>  && (!is_void_v< _Ty> ); 
#line 600
template< class _Ty> 
#line 601
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_object : public bool_constant< is_object_v< _Ty> >  { }; 
#line 603
template< class > 
#line 604
struct _Is_member_object_pointer { 
#line 605
static constexpr bool value = false; 
#line 606
}; 
#line 608
template< class _Ty1, class _Ty2> 
#line 609
struct _Is_member_object_pointer< _Ty1 _Ty2::*>  { 
#line 610
static constexpr bool value = (!is_function_v< _Ty1> ); 
#line 611
using _Class_type = _Ty2; 
#line 612
}; 
#line 618
template< class _Ty> 
#line 619
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_member_object_pointer_v = (_Is_member_object_pointer< remove_cv_t< _Ty> > ::value); 
#line 623 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 624
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_member_object_pointer : public bool_constant< is_member_object_pointer_v< _Ty> >  { }; 
#line 630
template< class _Ty> 
#line 631
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_member_pointer_v = is_member_object_pointer_v< _Ty>  || is_member_function_pointer_v< _Ty> ; 
#line 635 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 636
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_member_pointer : public bool_constant< is_member_pointer_v< _Ty> >  { 
#line 638
}; 
#line 640
template< class _Ty> 
#line 641
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_scalar_v = (((is_arithmetic_v< _Ty>  || is_enum_v< _Ty> ) || is_pointer_v< _Ty> ) || is_member_pointer_v< _Ty> ) || is_null_pointer_v< _Ty> ; 
#line 644
template< class _Ty> 
#line 645
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_scalar : public bool_constant< is_scalar_v< _Ty> >  { }; 
#line 647
template< class _Ty> 
#line 648
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_pod : public bool_constant< __is_pod(_Ty)>  { 
#line 650
}; 
#line 652
template< class _Ty> 
#line 653
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_pod_v = __is_pod(_Ty); 
#line 655
template< class _Ty> 
#line 656
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_empty : public bool_constant< __is_empty(_Ty)>  { 
#line 657
}; 
#line 659
template< class _Ty> 
#line 660
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_empty_v = __is_empty(_Ty); 
#line 662
template< class _Ty> 
#line 663
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_polymorphic : public bool_constant< __is_polymorphic(_Ty)>  { 
#line 665
}; 
#line 667
template< class _Ty> 
#line 668
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_polymorphic_v = __is_polymorphic(_Ty); 
#line 670
template< class _Ty> 
#line 671
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_abstract : public bool_constant< __is_abstract(_Ty)>  { 
#line 673
}; 
#line 675
template< class _Ty> 
#line 676
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_abstract_v = __is_abstract(_Ty); 
#line 678
template< class _Ty> 
#line 679
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_final : public bool_constant< __is_final(_Ty)>  { 
#line 680
}; 
#line 682
template< class _Ty> 
#line 683
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_final_v = __is_final(_Ty); 
#line 685
template< class _Ty> 
#line 686
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_standard_layout : public bool_constant< __is_standard_layout(_Ty)>  { 
#line 688
}; 
#line 690
template< class _Ty> 
#line 691
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_standard_layout_v = __is_standard_layout(_Ty); 
#line 694
template< class _Ty> 
#line 695
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_literal_type : public bool_constant< __is_literal_type(_Ty)>  { 
#line 698
}; 
#line 700
template< class _Ty> 
#line 701
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_literal_type_v = __is_literal_type(_Ty); 
#line 705 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 706
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivial : public bool_constant< __is_trivial(_Ty)>  { 
#line 707
}; 
#line 709
template< class _Ty> 
#line 710
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivial_v = __is_trivial(_Ty); 
#line 712
template< class _Ty> 
#line 713
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_copyable : public bool_constant< __is_trivially_copyable(_Ty)>  { 
#line 715
}; 
#line 717
template< class _Ty> 
#line 718
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_copyable_v = __is_trivially_copyable(_Ty); 
#line 730 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 731
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] has_virtual_destructor : public bool_constant< __has_virtual_destructor(_Ty)>  { 
#line 733
}; 
#line 735
template< class _Ty> 
#line 736
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool has_virtual_destructor_v = __has_virtual_destructor(_Ty); 
#line 813 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty, class ..._Args> 
#line 814
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_constructible : public bool_constant< __is_constructible(_Ty, _Args...)>  { 
#line 816
}; 
#line 818
template< class _Ty, class ..._Args> 
#line 819
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_constructible_v = __is_constructible(_Ty, _Args...); 
#line 821
template< class _Ty> 
#line 822
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_copy_constructible : public bool_constant< __is_constructible(_Ty, add_lvalue_reference_t< const _Ty> )>  { 
#line 825
}; 
#line 827
template< class _Ty> 
#line 828
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_copy_constructible_v = __is_constructible(_Ty, add_lvalue_reference_t< const _Ty> ); 
#line 831
template< class _Ty> 
#line 832
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_default_constructible : public bool_constant< __is_constructible(_Ty)>  { 
#line 834
}; 
#line 836
template< class _Ty> 
#line 837
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_default_constructible_v = __is_constructible(_Ty); 
#line 839
template< class _Ty, class  = void> 
#line 840
struct _Is_implicitly_default_constructible : public false_type { 
#line 842
}; 
#line 844
template< class _Ty> void _Implicitly_default_construct(const _Ty &); 
#line 847
template< class _Ty> 
#line 848
struct _Is_implicitly_default_constructible< _Ty, void_t< decltype(_Implicitly_default_construct< _Ty> ({}))> >  : public true_type { 
#line 849
}; 
#line 851
template< class _Ty> 
#line 852
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_move_constructible : public bool_constant< __is_constructible(_Ty, _Ty)>  { 
#line 854
}; 
#line 856
template< class _Ty> 
#line 857
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_move_constructible_v = __is_constructible(_Ty, _Ty); 
#line 859
template< class _To, class _From> 
#line 860
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_assignable : public bool_constant< __is_assignable(_To, _From)>  { 
#line 862
}; 
#line 864
template< class _To, class _From> 
#line 865
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_assignable_v = __is_assignable(_To, _From); 
#line 868
template< class _To, class _From> 
#line 869
struct _Is_assignable_no_precondition_check : public bool_constant< __is_assignable_no_precondition_check(_To, _From)>  { }; 
#line 875 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 876
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_copy_assignable : public bool_constant< __is_assignable(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> )>  { 
#line 879
}; 
#line 881
template< class _Ty> 
#line 882
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_copy_assignable_v = __is_assignable(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> ); 
#line 886
template< class _Ty> 
#line 887
struct _Is_copy_assignable_no_precondition_check : public bool_constant< __is_assignable_no_precondition_check(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> )>  { 
#line 889
}; 
#line 891
template< class _Ty> constexpr bool 
#line 892
_Is_copy_assignable_unchecked_v = __is_assignable_no_precondition_check(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> ); 
#line 902 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 903
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_move_assignable : public bool_constant< __is_assignable(add_lvalue_reference_t< _Ty> , _Ty)>  { 
#line 906
}; 
#line 908
template< class _Ty> 
#line 909
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_move_assignable_v = __is_assignable(add_lvalue_reference_t< _Ty> , _Ty); 
#line 913
template< class _Ty> 
#line 914
struct _Is_move_assignable_no_precondition_check : public bool_constant< __is_assignable_no_precondition_check(add_lvalue_reference_t< _Ty> , _Ty)>  { 
#line 915
}; 
#line 917
template< class _Ty> constexpr bool 
#line 918
_Is_move_assignable_unchecked_v = __is_assignable_no_precondition_check(add_lvalue_reference_t< _Ty> , _Ty); 
#line 928 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 929
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_destructible : public bool_constant< __is_destructible(_Ty)>  { 
#line 931
}; 
#line 933
template< class _Ty> 
#line 934
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_destructible_v = __is_destructible(_Ty); 
#line 936
template< class _Ty, class ..._Args> 
#line 937
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_constructible : public bool_constant< __is_trivially_constructible(_Ty, _Args...)>  { 
#line 940
}; 
#line 942
template< class _Ty, class ..._Args> 
#line 943
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_constructible_v = __is_trivially_constructible(_Ty, _Args...); 
#line 946
template< class _Ty> 
#line 947
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_copy_constructible : public bool_constant< __is_trivially_constructible(_Ty, add_lvalue_reference_t< const _Ty> )>  { 
#line 950
}; 
#line 952
template< class _Ty> 
#line 953
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_copy_constructible_v = __is_trivially_constructible(_Ty, add_lvalue_reference_t< const _Ty> ); 
#line 956
template< class _Ty> 
#line 957
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_default_constructible : public bool_constant< __is_trivially_constructible(_Ty)>  { 
#line 960
}; 
#line 962
template< class _Ty> 
#line 963
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_default_constructible_v = __is_trivially_constructible(_Ty); 
#line 966
template< class _Ty> 
#line 967
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_move_constructible : public bool_constant< __is_trivially_constructible(_Ty, _Ty)>  { 
#line 970
}; 
#line 972
template< class _Ty> 
#line 973
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_move_constructible_v = __is_trivially_constructible(_Ty, _Ty); 
#line 976
template< class _To, class _From> 
#line 977
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_assignable : public bool_constant< __is_trivially_assignable(_To, _From)>  { 
#line 980
}; 
#line 982
template< class _To, class _From> 
#line 983
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_assignable_v = __is_trivially_assignable(_To, _From); 
#line 985
template< class _Ty> 
#line 986
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_copy_assignable : public bool_constant< __is_trivially_assignable(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> )>  { 
#line 989
}; 
#line 991
template< class _Ty> 
#line 992
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_copy_assignable_v = __is_trivially_assignable(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> ); 
#line 995
template< class _Ty> 
#line 996
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_move_assignable : public bool_constant< __is_trivially_assignable(add_lvalue_reference_t< _Ty> , _Ty)>  { 
#line 999
}; 
#line 1001
template< class _Ty> 
#line 1002
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_move_assignable_v = __is_trivially_assignable(add_lvalue_reference_t< _Ty> , _Ty); 
#line 1005
template< class _Ty> 
#line 1006
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_trivially_destructible : public bool_constant< __is_trivially_destructible(_Ty)>  { 
#line 1008
}; 
#line 1010
template< class _Ty> 
#line 1011
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_trivially_destructible_v = __is_trivially_destructible(_Ty); 
#line 1013
template< class _Ty, class ..._Args> 
#line 1014
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_constructible : public bool_constant< __is_nothrow_constructible(_Ty, _Args...)>  { 
#line 1017
}; 
#line 1019
template< class _Ty, class ..._Args> 
#line 1020
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_constructible_v = __is_nothrow_constructible(_Ty, _Args...); 
#line 1023
template< class _Ty> 
#line 1024
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_copy_constructible : public bool_constant< __is_nothrow_constructible(_Ty, add_lvalue_reference_t< const _Ty> )>  { 
#line 1028
}; 
#line 1030
template< class _Ty> 
#line 1031
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_copy_constructible_v = __is_nothrow_constructible(_Ty, add_lvalue_reference_t< const _Ty> ); 
#line 1034
template< class _Ty> 
#line 1035
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_default_constructible : public bool_constant< __is_nothrow_constructible(_Ty)>  { 
#line 1038
}; 
#line 1040
template< class _Ty> 
#line 1041
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_default_constructible_v = __is_nothrow_constructible(_Ty); 
#line 1043
template< class _Ty> 
#line 1044
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_move_constructible : public bool_constant< __is_nothrow_constructible(_Ty, _Ty)>  { 
#line 1047
}; 
#line 1049
template< class _Ty> 
#line 1050
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_move_constructible_v = __is_nothrow_constructible(_Ty, _Ty); 
#line 1053
template< class _To, class _From> 
#line 1054
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_assignable : public bool_constant< __is_nothrow_assignable(_To, _From)>  { 
#line 1056
}; 
#line 1058
template< class _To, class _From> 
#line 1059
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_assignable_v = __is_nothrow_assignable(_To, _From); 
#line 1061
template< class _Ty> 
#line 1062
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_copy_assignable : public bool_constant< __is_nothrow_assignable(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> )>  { 
#line 1065
}; 
#line 1067
template< class _Ty> 
#line 1068
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_copy_assignable_v = __is_nothrow_assignable(add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< const _Ty> ); 
#line 1071
template< class _Ty> 
#line 1072
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_move_assignable : public bool_constant< __is_nothrow_assignable(add_lvalue_reference_t< _Ty> , _Ty)>  { 
#line 1075
}; 
#line 1077
template< class _Ty> 
#line 1078
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_move_assignable_v = __is_nothrow_assignable(add_lvalue_reference_t< _Ty> , _Ty); 
#line 1081
template< class _Ty> 
#line 1082
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_nothrow_destructible : public bool_constant< __is_nothrow_destructible(_Ty)>  { 
#line 1085
}; 
#line 1087
template< class _Ty> 
#line 1088
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_nothrow_destructible_v = __is_nothrow_destructible(_Ty); 
#line 1090
template< class _Ty, bool  = is_integral_v< _Ty> > 
#line 1091
struct _Sign_base { 
#line 1092
using _Uty = remove_cv_t< _Ty> ; 
#line 1094
static constexpr bool _Signed = ((static_cast< _Uty>(-1)) < (static_cast< _Uty>(0))); 
#line 1095
static constexpr bool _Unsigned = (!_Signed); 
#line 1096
}; 
#line 1098
template< class _Ty> 
#line 1099
struct _Sign_base< _Ty, false>  { 
#line 1101
static constexpr bool _Signed = is_floating_point_v< _Ty> ; 
#line 1102
static constexpr bool _Unsigned = false; 
#line 1103
}; 
#line 1105
template< class _Ty> 
#line 1106
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_signed : public bool_constant< _Sign_base< _Ty> ::_Signed>  { 
#line 1108
}; 
#line 1110
template< class _Ty> 
#line 1111
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_signed_v = (_Sign_base< _Ty> ::_Signed); 
#line 1113
template< class _Ty> 
#line 1114
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_unsigned : public bool_constant< _Sign_base< _Ty> ::_Unsigned>  { 
#line 1116
}; 
#line 1118
template< class _Ty> 
#line 1119
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_unsigned_v = (_Sign_base< _Ty> ::_Unsigned); 
#line 1121
template< bool > 
#line 1122
struct _Select { 
#line 1123
template< class _Ty1, class > using _Apply = _Ty1; 
#line 1125
}; 
#line 1128
template<> struct _Select< false>  { 
#line 1129
template< class , class _Ty2> using _Apply = _Ty2; 
#line 1131
}; 
#line 1133
template< size_t > struct _Make_signed2; 
#line 1137
template<> struct _Make_signed2< 1>  { 
#line 1138
template< class > using _Apply = signed char; 
#line 1140
}; 
#line 1143
template<> struct _Make_signed2< 2>  { 
#line 1144
template< class > using _Apply = short; 
#line 1146
}; 
#line 1149
template<> struct _Make_signed2< 4>  { 
#line 1150
template< class _Ty> using _Apply = typename _Select< is_same_v< _Ty, long>  || is_same_v< _Ty, unsigned long> > ::template _Apply< long, int> ; 
#line 1153
}; 
#line 1156
template<> struct _Make_signed2< 8>  { 
#line 1157
template< class > using _Apply = __int64; 
#line 1159
}; 
#line 1161
template< class _Ty> using _Make_signed1 = typename _Make_signed2< sizeof(_Ty)> ::template _Apply< _Ty> ; 
#line 1165
template< class _Ty> 
#line 1166
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] make_signed { 
#line 1167
static_assert((_Is_nonbool_integral< _Ty>  || is_enum_v< _Ty> ), "make_signed<T> requires that T shall be a (possibly cv-qualified) integral type or enumeration but not a bool type.");
#line 1171
using type = typename remove_cv< _Ty> ::template _Apply< _Make_signed1> ; 
#line 1172
}; 
#line 1174
template< class _Ty> using make_signed_t = typename make_signed< _Ty> ::type; 
#line 1177
template< size_t > struct _Make_unsigned2; 
#line 1181
template<> struct _Make_unsigned2< 1>  { 
#line 1182
template< class > using _Apply = unsigned char; 
#line 1184
}; 
#line 1187
template<> struct _Make_unsigned2< 2>  { 
#line 1188
template< class > using _Apply = unsigned short; 
#line 1190
}; 
#line 1193
template<> struct _Make_unsigned2< 4>  { 
#line 1194
template< class _Ty> using _Apply = typename _Select< is_same_v< _Ty, long>  || is_same_v< _Ty, unsigned long> > ::template _Apply< unsigned long, unsigned> ; 
#line 1198
}; 
#line 1201
template<> struct _Make_unsigned2< 8>  { 
#line 1202
template< class > using _Apply = unsigned __int64; 
#line 1204
}; 
#line 1206
template< class _Ty> using _Make_unsigned1 = typename _Make_unsigned2< sizeof(_Ty)> ::template _Apply< _Ty> ; 
#line 1210
template< class _Ty> 
#line 1211
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] make_unsigned { 
#line 1212
static_assert((_Is_nonbool_integral< _Ty>  || is_enum_v< _Ty> ), "make_unsigned<T> requires that T shall be a (possibly cv-qualified) integral type or enumeration but not a bool type.");
#line 1216
using type = typename remove_cv< _Ty> ::template _Apply< _Make_unsigned1> ; 
#line 1217
}; 
#line 1219
template< class _Ty> using make_unsigned_t = typename make_unsigned< _Ty> ::type; 
#line 1222
template < class _Rep >
constexpr make_unsigned_t < _Rep > _Unsigned_value ( _Rep _Val ) {
    return static_cast < make_unsigned_t < _Rep >> ( _Val );
}
#line 1227
template< class _Ty> 
#line 1228
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] alignment_of : public integral_constant< ::size_t, __alignof(_Ty)>  { 
#line 1229
}; 
#line 1231
template< class _Ty> 
#line 1232
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr size_t alignment_of_v = __alignof(_Ty); 
#line 1234
template< class _Ty, size_t _Len> 
#line 1235
union _Align_type { 
#line 1236
_Ty _Val; 
#line 1237
char _Pad[_Len]; 
#line 1238
}; 
#line 1240
template< size_t _Len, size_t _Align, class _Ty, bool _Ok> struct _Aligned; 
#line 1243
template< size_t _Len, size_t _Align, class _Ty> 
#line 1244
struct _Aligned< _Len, _Align, _Ty, true>  { 
#line 1245
using type = _Align_type< _Ty, _Len> ; 
#line 1246
}; 
#line 1248
template< size_t _Len, size_t _Align> 
#line 1249
struct _Aligned< _Len, _Align, double, false>  { 
#line 1256
static_assert(false, "You\'ve instantiated std::aligned_storage<Len, Align> with an extended alignment (in other words, Align > alignof(max_align_t))." " Before VS 2017 15.8, the member \"type\" would non-conformingly have an alignment of only alignof(max_align_t). VS 2017 15.8 wa" "s fixed to handle this correctly, but the fix inherently changes layout and breaks binary compatibility (*only* for uses of alig" "ned_storage with extended alignments). To suppress this error, please define either (1) _ENABLE_EXTENDED_ALIGNED_STORAGE to conf" "irm that you want a type with an extended alignment, or (2) _DISABLE_EXTENDED_ALIGNED_STORAGE to get the old non-conforming beha" "vior.");
#line 1266 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
using type = _Align_type< max_align_t, _Len> ; 
#line 1268 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
}; 
#line 1270
template< size_t _Len, size_t _Align> 
#line 1271
struct _Aligned< _Len, _Align, int, false>  { 
#line 1272
using _Next = double; 
#line 1273
static constexpr bool _Fits = (_Align <= __alignof(_Next)); 
#line 1274
using type = typename std::_Aligned< _Len, _Align, double, _Fits> ::type; 
#line 1275
}; 
#line 1277
template< size_t _Len, size_t _Align> 
#line 1278
struct _Aligned< _Len, _Align, short, false>  { 
#line 1279
using _Next = int; 
#line 1280
static constexpr bool _Fits = (_Align <= __alignof(_Next)); 
#line 1281
using type = typename std::_Aligned< _Len, _Align, int, _Fits> ::type; 
#line 1282
}; 
#line 1284
template< size_t _Len, size_t _Align> 
#line 1285
struct _Aligned< _Len, _Align, char, false>  { 
#line 1286
using _Next = short; 
#line 1287
static constexpr bool _Fits = (_Align <= __alignof(_Next)); 
#line 1288
using type = typename std::_Aligned< _Len, _Align, short, _Fits> ::type; 
#line 1289
}; 
#line 1292
template< size_t _Len, size_t _Align = 8Ui64> 
#line 1293
struct _Aligned_storage { 
#line 1294
using _Next = char; 
#line 1295
static constexpr bool _Fits = (_Align <= __alignof(_Next)); 
#line 1296
using type = typename _Aligned< _Len, _Align, _Next, _Fits> ::type; 
#line 1297
}; 
#line 1299
template< size_t _Len, size_t _Align = 8Ui64> using _Aligned_storage_t = typename _Aligned_storage< _Len, _Align> ::type; 
#line 1302
template< size_t _Len, size_t _Align = 8Ui64> 
#line 1303
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] aligned_storage { 
#line 1305
using type = _Aligned_storage_t< _Len, _Align> ; 
#line 1306
}; 
#line 1308
template< size_t _Len, size_t _Align = 8Ui64> using aligned_storage_t = _Aligned_storage_t< _Len, _Align> ; 
#line 1311
template< size_t ..._Vals> struct _Maximum; 
#line 1315
template<> struct _Maximum< >  : public integral_constant< size_t, 0>  { }; 
#line 1317
template< size_t _Val> 
#line 1318
struct _Maximum< _Val>  : public integral_constant< ::size_t, _Val>  { }; 
#line 1320
template< size_t _First, size_t _Second, size_t ..._Rest> 
#line 1321
struct _Maximum< _First, _Second, _Rest...>  : public std::_Maximum< (((_First) < _Second) ? _Second : _First), _Rest...> ::type { 
#line 1323
}; 
#line 1325
template< size_t _Len, class ..._Types> 
#line 1326
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] aligned_union { 
#line 1328
static constexpr size_t _Max_len = (_Maximum< _Len, sizeof(_Types)...> ::value); 
#line 1329
static constexpr size_t alignment_value = (_Maximum< __alignof(_Types)...> ::value); 
#line 1331
using type = _Aligned_storage_t< _Max_len, alignment_value> ; 
#line 1332
}; 
#line 1334
__pragma( warning(push)) __pragma( warning(disable : 4996)) 
#line 1335
template< size_t _Len, class ..._Types> using aligned_union_t = typename aligned_union< _Len, _Types...> ::type; 
#line 1337
__pragma( warning(pop)) 
#line 1339
template< class _Ty, bool  = is_enum_v< _Ty> > 
#line 1340
struct _Underlying_type { 
#line 1341
using type = __underlying_type(_Ty); 
#line 1342
}; 
#line 1344
template< class _Ty> 
#line 1345
struct _Underlying_type< _Ty, false>  { }; 
#line 1347
template< class _Ty> 
#line 1348
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] underlying_type : public _Underlying_type< _Ty>  { 
#line 1349
}; 
#line 1351
template< class _Ty> using underlying_type_t = typename _Underlying_type< _Ty> ::type; 
#line 1354
template< class _Ty> 
#line 1355
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr size_t rank_v = (0); 
#line 1357
template< class _Ty, size_t _Nx> constexpr size_t 
#line 1358
rank_v< _Ty [_Nx]>  = rank_v< _Ty>  + 1; 
#line 1360
template< class _Ty> constexpr size_t 
#line 1361
rank_v< _Ty []>  = rank_v< _Ty>  + 1; 
#line 1363
template< class _Ty> 
#line 1364
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] rank : public integral_constant< ::size_t, rank_v< _Ty> >  { }; 
#line 1366
template< class _Ty, unsigned _Ix = 0U> 
#line 1367
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr size_t extent_v = (0); 
#line 1369
template< class _Ty, size_t _Nx> constexpr size_t 
#line 1370
extent_v< _Ty [_Nx], 0>  = _Nx; 
#line 1372
template< class _Ty, unsigned _Ix, size_t _Nx> constexpr size_t 
#line 1373
extent_v< _Ty [_Nx], _Ix>  = extent_v< _Ty, _Ix - (1)> ; 
#line 1375
template< class _Ty, unsigned _Ix> constexpr size_t 
#line 1376
extent_v< _Ty [], _Ix>  = extent_v< _Ty, _Ix - (1)> ; 
#line 1378
template< class _Ty, unsigned _Ix = 0U> 
#line 1379
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] extent : public integral_constant< ::size_t, extent_v< _Ty, _Ix> >  { }; 
#line 1381
template< class _Base, class _Derived> 
#line 1382
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] is_base_of : public bool_constant< __is_base_of(_Base, _Derived)>  { 
#line 1384
}; 
#line 1386
template< class _Base, class _Derived> 
#line 1387
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] constexpr bool is_base_of_v = __is_base_of(_Base, _Derived); 
#line 1389
template< class _Ty> 
#line 1390
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] decay { 
#line 1391
using _Ty1 = remove_reference_t< _Ty> ; 
#line 1392
using _Ty2 = typename _Select< is_function_v< _Ty1> > ::template _Apply< add_pointer< _Ty1> , remove_cv< _Ty1> > ; 
#line 1393
using type = typename _Select< is_array_v< _Ty1> > ::template _Apply< add_pointer< remove_extent_t< _Ty1> > , _Ty2> ::type; 
#line 1394
}; 
#line 1396
template< class _Ty> using decay_t = typename decay< _Ty> ::type; 
#line 1399
template< class _Ty1, class _Ty2> using _Conditional_type = decltype(false ? std::declval< _Ty1> () : std::declval< _Ty2> ()); 
#line 1417 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty1, class _Ty2, class  = void> 
#line 1418
struct _Decayed_cond_oper { }; 
#line 1421 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty1, class _Ty2> 
#line 1422
struct _Decayed_cond_oper< _Ty1, _Ty2, void_t< _Conditional_type< _Ty1, _Ty2> > >  { 
#line 1423
using type = decay_t< _Conditional_type< _Ty1, _Ty2> > ; 
#line 1424
}; 
#line 1426
template< class ..._Ty> struct common_type; 
#line 1429
template< class ..._Ty> using common_type_t = typename common_type< _Ty...> ::type; 
#line 1433
template<> struct common_type< >  { }; 
#line 1435
template< class _Ty1> 
#line 1436
struct common_type< _Ty1>  : public std::common_type< _Ty1, _Ty1>  { }; 
#line 1438
template< class _Ty1, class _Ty2, class _Decayed1 = decay_t< _Ty1> , class _Decayed2 = decay_t< _Ty2> > 
#line 1439
struct _Common_type2 : public common_type< _Decayed1, _Decayed2>  { }; 
#line 1441
template< class _Ty1, class _Ty2> 
#line 1442
struct _Common_type2< _Ty1, _Ty2, _Ty1, _Ty2>  : public _Decayed_cond_oper< _Ty1, _Ty2>  { }; 
#line 1444
template< class _Ty1, class _Ty2> 
#line 1445
struct common_type< _Ty1, _Ty2>  : public _Common_type2< _Ty1, _Ty2>  { }; 
#line 1447
template< class _Void, class _Ty1, class _Ty2, class ..._Rest> 
#line 1448
struct _Common_type3 { }; 
#line 1450
template< class _Ty1, class _Ty2, class ..._Rest> 
#line 1451
struct _Common_type3< void_t< common_type_t< _Ty1, _Ty2> > , _Ty1, _Ty2, _Rest...>  : public common_type< common_type_t< _Ty1, _Ty2> , _Rest...>  { 
#line 1452
}; 
#line 1454
template< class _Ty1, class _Ty2, class ..._Rest> 
#line 1455
struct common_type< _Ty1, _Ty2, _Rest...>  : public _Common_type3< void, _Ty1, _Ty2, _Rest...>  { }; 
#line 1457
template< class _Ty> _Ty _Returns_exactly() noexcept; 
#line 1623 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Type, template< class ...>  class _Template> constexpr bool 
#line 1624
_Is_specialization_v = false; 
#line 1625
template< template< class ...>  class _Template, class ..._Types> constexpr bool 
#line 1626
_Is_specialization_v< _Template< _Types...> , _Template>  = true; 
#line 1628
template< class _Type, template< class ...>  class _Template> 
#line 1629
struct _Is_specialization : public bool_constant< _Is_specialization_v< _Type, _Template> >  { }; 
#line 1631
template< class _Ty> 
#line 1632
[[nodiscard]] [[msvc::intrinsic]] constexpr _Ty &&forward(remove_reference_t< _Ty>  &_Arg) noexcept { 
#line 1633
return static_cast< _Ty &&>(_Arg); 
#line 1634
} 
#line 1636
template< class _Ty> 
#line 1637
[[nodiscard]] [[msvc::intrinsic]] constexpr _Ty &&forward(remove_reference_t< _Ty>  &&_Arg) noexcept { 
#line 1638
static_assert((!is_lvalue_reference_v< _Ty> ), "bad forward call");
#line 1639
return static_cast< _Ty &&>(_Arg); 
#line 1640
} 
#line 1642
template< class _Ty> 
#line 1643
[[nodiscard]] [[msvc::intrinsic]] constexpr remove_reference_t< _Ty>  &&move(_Ty &&_Arg) noexcept { 
#line 1644
return static_cast< remove_reference_t< _Ty>  &&>(_Arg); 
#line 1645
} 
#line 1647
template < class _Ty >
[ [ nodiscard ] ] [ [ msvc :: intrinsic ] ] constexpr
    conditional_t < ! is_nothrow_move_constructible_v < _Ty > && is_copy_constructible_v < _Ty >, const _Ty &, _Ty && >
    move_if_noexcept ( _Ty & _Arg ) noexcept {
    return :: std :: move ( _Arg );
}
#line 1654
template < class _Ty >
[ [ nodiscard ] ] constexpr _Ty * addressof ( _Ty & _Val ) noexcept {
    return __builtin_addressof ( _Val );
}
#line 1659
template < class _Ty >
const _Ty * addressof ( const _Ty && ) = delete;
#line 1662
#pragma warning(push)
#pragma warning(disable : 5215)
#pragma warning(disable : 5216)
#line 1671
template< class _Ty> 
#line 1672
[[nodiscard]] _Ty 
#line 1671
_Fake_copy_init(_Ty) noexcept; 
#line 1682
#pragma warning(pop)
#line 1684
template < class _Ty >
class reference_wrapper;
#line 1691
enum class _Invoker_strategy { 
#line 1692
_Functor, 
#line 1693
_Pmf_object, 
#line 1694
_Pmf_refwrap, 
#line 1695
_Pmf_pointer, 
#line 1696
_Pmd_object, 
#line 1697
_Pmd_refwrap, 
#line 1698
_Pmd_pointer
#line 1699
}; 
#line 1701
struct _Invoker_functor { 
#line 1702
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Functor; 
#line 1704
template < class _Callable, class ... _Types >
    static constexpr auto _Call ( _Callable && _Obj, _Types && ... _Args )
        noexcept ( noexcept ( static_cast < _Callable && > ( _Obj ) ( static_cast < _Types && > ( _Args ) ... ) ) )
        -> decltype ( static_cast < _Callable && > ( _Obj ) ( static_cast < _Types && > ( _Args ) ... ) ) {
        return static_cast < _Callable && > ( _Obj ) ( static_cast < _Types && > ( _Args ) ... );
    }
#line 1710
}; 
#line 1712
struct _Invoker_pmf_object { 
#line 1713
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Pmf_object; 
#line 1715
template < class _Decayed, class _Ty1, class ... _Types2 >
    static constexpr auto _Call ( _Decayed _Pmf, _Ty1 && _Arg1, _Types2 && ... _Args2 )
        noexcept ( noexcept ( ( static_cast < _Ty1 && > ( _Arg1 ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... ) ) )
        -> decltype ( ( static_cast < _Ty1 && > ( _Arg1 ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... ) ) {
        return ( static_cast < _Ty1 && > ( _Arg1 ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... );
    }
#line 1721
}; 
#line 1723
struct _Invoker_pmf_refwrap { 
#line 1724
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Pmf_refwrap; 
#line 1726
template < class _Decayed, class _Refwrap, class ... _Types2 >
    static constexpr auto _Call ( _Decayed _Pmf, _Refwrap _Rw, _Types2 && ... _Args2 )
        noexcept ( noexcept ( ( _Rw . get ( ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... ) ) )
        -> decltype ( ( _Rw . get ( ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... ) ) {
        return ( _Rw . get ( ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... );
    }
#line 1732
}; 
#line 1734
struct _Invoker_pmf_pointer { 
#line 1735
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Pmf_pointer; 
#line 1737
template < class _Decayed, class _Ty1, class ... _Types2 >
    static constexpr auto _Call ( _Decayed _Pmf, _Ty1 && _Arg1, _Types2 && ... _Args2 )
        noexcept ( noexcept ( ( ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... ) ) )
        -> decltype ( ( ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... ) ) {
        return ( ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Pmf ) ( static_cast < _Types2 && > ( _Args2 ) ... );
    }
#line 1743
}; 
#line 1745
struct _Invoker_pmd_object { 
#line 1746
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Pmd_object; 
#line 1748
template < class _Decayed, class _Ty1 >
    static constexpr auto _Call ( _Decayed _Pmd, _Ty1 && _Arg1 ) noexcept -> decltype ( static_cast < _Ty1 && > ( _Arg1 ) .* _Pmd ) {
        return static_cast < _Ty1 && > ( _Arg1 ) .* _Pmd;
    }
#line 1752
}; 
#line 1754
struct _Invoker_pmd_refwrap { 
#line 1755
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Pmd_refwrap; 
#line 1757
template < class _Decayed, class _Refwrap >
    static constexpr auto _Call ( _Decayed _Pmd, _Refwrap _Rw ) noexcept -> decltype ( _Rw . get ( ) .* _Pmd ) {
        return _Rw . get ( ) .* _Pmd;
    }
#line 1761
}; 
#line 1763
struct _Invoker_pmd_pointer { 
#line 1764
static constexpr _Invoker_strategy _Strategy = _Invoker_strategy::_Pmd_pointer; 
#line 1766
template < class _Decayed, class _Ty1 >
    static constexpr auto _Call ( _Decayed _Pmd, _Ty1 && _Arg1 ) noexcept ( noexcept ( ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Pmd ) )
        -> decltype ( ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Pmd ) {
        return ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Pmd;
    }
#line 1771
}; 
#line 1773
template< class _Callable, class _Ty1, class _Removed_cvref = _Remove_cvref_t< _Callable> , bool 
#line 1774
_Is_pmf = is_member_function_pointer_v< _Removed_cvref> , bool 
#line 1775
_Is_pmd = is_member_object_pointer_v< _Removed_cvref> > struct _Invoker1; 
#line 1778
template< class _Callable, class _Ty1, class _Removed_cvref> 
#line 1779
struct _Invoker1< _Callable, _Ty1, _Removed_cvref, true, false>  : public conditional_t< is_same_v< typename _Is_memfunptr< _Removed_cvref> ::_Class_type, _Remove_cvref_t< _Ty1> >  || is_base_of_v< typename _Is_memfunptr< _Removed_cvref> ::_Class_type, _Remove_cvref_t< _Ty1> > , _Invoker_pmf_object, conditional_t< _Is_specialization_v< _Remove_cvref_t< _Ty1> , reference_wrapper> , _Invoker_pmf_refwrap, _Invoker_pmf_pointer> >  { 
#line 1784
}; 
#line 1786
template< class _Callable, class _Ty1, class _Removed_cvref> 
#line 1787
struct _Invoker1< _Callable, _Ty1, _Removed_cvref, false, true>  : public conditional_t< is_same_v< typename _Is_member_object_pointer< _Removed_cvref> ::_Class_type, _Remove_cvref_t< _Ty1> >  || is_base_of_v< typename _Is_member_object_pointer< _Removed_cvref> ::_Class_type, _Remove_cvref_t< _Ty1> > , _Invoker_pmd_object, conditional_t< _Is_specialization_v< _Remove_cvref_t< _Ty1> , reference_wrapper> , _Invoker_pmd_refwrap, _Invoker_pmd_pointer> >  { 
#line 1793
}; 
#line 1795
template< class _Callable, class _Ty1, class _Removed_cvref> 
#line 1796
struct _Invoker1< _Callable, _Ty1, _Removed_cvref, false, false>  : public _Invoker_functor { }; 
#line 1798
template < class _Callable >
constexpr auto invoke ( _Callable && _Obj ) noexcept ( noexcept ( static_cast < _Callable && > ( _Obj ) ( ) ) )
    -> decltype ( static_cast < _Callable && > ( _Obj ) ( ) ) {
    return static_cast < _Callable && > ( _Obj ) ( );
}
#line 1804
template < class _Callable, class _Ty1, class ... _Types2 >
constexpr auto invoke ( _Callable && _Obj, _Ty1 && _Arg1, _Types2 && ... _Args2 )
    noexcept ( noexcept ( _Invoker1 < _Callable, _Ty1 > :: _Call (
        static_cast < _Callable && > ( _Obj ), static_cast < _Ty1 && > ( _Arg1 ), static_cast < _Types2 && > ( _Args2 ) ... ) ) )
    -> decltype ( _Invoker1 < _Callable, _Ty1 > :: _Call (
        static_cast < _Callable && > ( _Obj ), static_cast < _Ty1 && > ( _Arg1 ), static_cast < _Types2 && > ( _Args2 ) ... ) ) {
    if constexpr ( _Invoker1 < _Callable, _Ty1 > :: _Strategy == _Invoker_strategy :: _Functor ) {
        return static_cast < _Callable && > ( _Obj ) ( static_cast < _Ty1 && > ( _Arg1 ), static_cast < _Types2 && > ( _Args2 ) ... );
    } else if constexpr ( _Invoker1 < _Callable, _Ty1 > :: _Strategy == _Invoker_strategy :: _Pmf_object ) {
        return ( static_cast < _Ty1 && > ( _Arg1 ) .* _Obj ) ( static_cast < _Types2 && > ( _Args2 ) ... );
    } else if constexpr ( _Invoker1 < _Callable, _Ty1 > :: _Strategy == _Invoker_strategy :: _Pmf_refwrap ) {
        return ( _Arg1 . get ( ) .* _Obj ) ( static_cast < _Types2 && > ( _Args2 ) ... );
    } else if constexpr ( _Invoker1 < _Callable, _Ty1 > :: _Strategy == _Invoker_strategy :: _Pmf_pointer ) {
        return ( ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Obj ) ( static_cast < _Types2 && > ( _Args2 ) ... );
    } else if constexpr ( _Invoker1 < _Callable, _Ty1 > :: _Strategy == _Invoker_strategy :: _Pmd_object ) {
        return static_cast < _Ty1 && > ( _Arg1 ) .* _Obj;
    } else if constexpr ( _Invoker1 < _Callable, _Ty1 > :: _Strategy == _Invoker_strategy :: _Pmd_refwrap ) {



        auto & _Ref = _Arg1 . get ( );
        return _Ref .* _Obj;

    } else {
        ;
        return ( * static_cast < _Ty1 && > ( _Arg1 ) ) .* _Obj;
    }
}
#line 1833 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
#pragma warning(push)
#pragma warning(disable : 4242)
#pragma warning(disable : 4244)
#pragma warning(disable : 4365)
#line 1838
template< class _From, class _To, bool  = is_convertible_v< _From, _To> , bool  = is_void_v< _To> > constexpr bool 
#line 1839
_Is_nothrow_convertible_v = noexcept(std::_Fake_copy_init< _To> (std::declval< _From> ())); 
#line 1841
#pragma warning(pop)
#line 1843
template< class _From, class _To, bool _IsVoid> constexpr bool 
#line 1844
_Is_nothrow_convertible_v< _From, _To, false, _IsVoid>  = false; 
#line 1846
template< class _From, class _To> constexpr bool 
#line 1847
_Is_nothrow_convertible_v< _From, _To, true, true>  = true; 
#line 1849
template< class _From, class _To> 
#line 1850
struct _Is_nothrow_convertible : public bool_constant< _Is_nothrow_convertible_v< _From, _To> >  { 
#line 1852
}; 
#line 1863 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _From, class _To, class  = void> 
#line 1864
struct _Invoke_convertible : public false_type { }; 
#line 1875 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _To, class _From> using _Not_reference_converts_from_temporary = true_type; 
#line 1879 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _From, class _To> 
#line 1880
struct _Invoke_convertible< _From, _To, void_t< decltype(std::_Fake_copy_init< _To> (std::_Returns_exactly< _From> ()))> >  : public _Not_reference_converts_from_temporary< _To, _From>  { 
#line 1881
}; 
#line 1883
template< class _From, class _To> 
#line 1884
struct _Invoke_nothrow_convertible : public bool_constant< noexcept(std::_Fake_copy_init< _To> (std::_Returns_exactly< _From> ()))>  { 
#line 1885
}; 
#line 1887
template< class _Result, bool _Nothrow> 
#line 1888
struct _Invoke_traits_common { 
#line 1889
using type = _Result; 
#line 1890
using _Is_invocable = true_type; 
#line 1891
using _Is_nothrow_invocable = bool_constant< _Nothrow> ; 
#line 1892
template< class _Rx> using _Is_invocable_r = bool_constant< disjunction_v< is_void< _Rx> , _Invoke_convertible< type, _Rx> > > ; 
#line 1894
template< class _Rx> using _Is_nothrow_invocable_r = bool_constant< conjunction_v< _Is_nothrow_invocable, disjunction< is_void< _Rx> , conjunction< _Invoke_convertible< type, _Rx> , _Invoke_nothrow_convertible< type, _Rx> > > > > ; 
#line 1898
}; 
#line 1900
template< class _Void, class _Callable> 
#line 1901
struct _Invoke_traits_zero { 
#line 1903
using _Is_invocable = false_type; 
#line 1904
using _Is_nothrow_invocable = false_type; 
#line 1905
template< class _Rx> using _Is_invocable_r = false_type; 
#line 1907
template< class _Rx> using _Is_nothrow_invocable_r = false_type; 
#line 1909
}; 
#line 1911
template< class _Callable> using _Decltype_invoke_zero = decltype(std::declval< _Callable> ()()); 
#line 1914
template< class _Callable> 
#line 1915
struct _Invoke_traits_zero< void_t< _Decltype_invoke_zero< _Callable> > , _Callable>  : public _Invoke_traits_common< _Decltype_invoke_zero< _Callable> , noexcept(std::declval< _Callable> ()())>  { 
#line 1916
}; 
#line 1918
template< class _Void, class ..._Types> 
#line 1919
struct _Invoke_traits_nonzero { 
#line 1921
using _Is_invocable = false_type; 
#line 1922
using _Is_nothrow_invocable = false_type; 
#line 1923
template< class _Rx> using _Is_invocable_r = false_type; 
#line 1925
template< class _Rx> using _Is_nothrow_invocable_r = false_type; 
#line 1927
}; 
#line 1929
template< class _Callable, class _Ty1, class ..._Types2> using _Decltype_invoke_nonzero = decltype(_Invoker1< _Callable, _Ty1> ::_Call(std::declval< _Callable> (), std::declval< _Ty1> (), std::declval< _Types2> ()...)); 
#line 1933
template< class _Callable, class _Ty1, class ..._Types2> 
#line 1934
struct _Invoke_traits_nonzero< void_t< _Decltype_invoke_nonzero< _Callable, _Ty1, _Types2...> > , _Callable, _Ty1, _Types2...>  : public _Invoke_traits_common< _Decltype_invoke_nonzero< _Callable, _Ty1, _Types2...> , noexcept(_Invoker1< _Callable, _Ty1> ::_Call(std::declval< _Callable> (), std::declval< _Ty1> (), std::declval< _Types2> ()...))>  { 
#line 1937
}; 
#line 1939
template< class _Callable, class ..._Args> using _Select_invoke_traits = conditional_t< sizeof...(_Args) == (0), _Invoke_traits_zero< void, _Callable> , _Invoke_traits_nonzero< void, _Callable, _Args...> > ; 
#line 1944
template< class _Fty> 
#line 1945
struct [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [meta.rqmts]/4" )]] result_of { 
#line 1946
static_assert(false, "result_of<CallableType> is invalid; use result_of<CallableType(zero or more argument types)> instead.");
#line 1948
}; 
#line 1956
template< class _Callable, class ..._Args> struct result_of< _Callable __cdecl (_Args ...)>  : public _Select_invoke_traits< _Callable, _Args...>  { }; template< class _Callable, class ..._Args> struct result_of< _Callable __vectorcall (_Args ...)>  : public _Select_invoke_traits< _Callable, _Args...>  { }; 
#line 1959
__pragma( warning(push)) __pragma( warning(disable : 4996)) 
#line 1960
template< class _Ty> using result_of_t = typename result_of< _Ty> ::type; 
#line 1962
__pragma( warning(pop)) 
#line 1965 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Callable, class ..._Args> using _Invoke_result_t = typename _Select_invoke_traits< _Callable, _Args...> ::type; 
#line 1968
template< class _Rx, class _Callable, class ..._Args> using _Is_invocable_r_ = typename _Select_invoke_traits< _Callable, _Args...> ::template _Is_invocable_r< _Rx> ; 
#line 1971
template< class _Rx, class _Callable, class ..._Args> 
#line 1972
struct _Is_invocable_r : public _Is_invocable_r_< _Rx, _Callable, _Args...>  { 
#line 1974
}; 
#line 2063 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> 
#line 2064
struct _Function_args { }; 
#line 2072
template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...)>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...)>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) const>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) const>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) volatile>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) volatile>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) const volatile>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) const volatile>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) const &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) const &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) volatile &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) volatile &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) const volatile &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) const volatile &>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) const &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) const &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) volatile &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) volatile &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __cdecl (_Types ...) const volatile &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret __vectorcall (_Types ...) const volatile &&>  : public _Arg_types< _Types...>  { using result_type = _Ret; }; 
#line 2081
template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...)>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) const>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) volatile>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) const volatile>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) &>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) const &>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) volatile &>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) const volatile &>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) &&>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) const &&>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) volatile &&>  { using result_type = _Ret; }; template< class _Ret, class ..._Types> struct _Function_args< _Ret (_Types ..., ...) const volatile &&>  { using result_type = _Ret; }; 
#line 2084
template< class _Ty, class  = void> 
#line 2085
struct _Weak_result_type { }; 
#line 2087
__pragma( warning(push)) __pragma( warning(disable : 4996)) 
#line 2088
template< class _Ty> 
#line 2089
struct _Weak_result_type< _Ty, void_t< typename _Ty::result_type> >  { 
#line 2090
using result_type = typename _Ty::result_type; 
#line 2091
}; 
#line 2092
__pragma( warning(pop)) 
#line 2094
template< class _Ty, class  = void> 
#line 2095
struct _Weak_argument_type : public _Weak_result_type< _Ty>  { }; 
#line 2097
__pragma( warning(push)) __pragma( warning(disable : 4996)) 
#line 2098
template< class _Ty> 
#line 2099
struct _Weak_argument_type< _Ty, void_t< typename _Ty::argument_type> >  : public _Weak_result_type< _Ty>  { 
#line 2101
using argument_type = typename _Ty::argument_type; 
#line 2102
}; 
#line 2103
__pragma( warning(pop)) 
#line 2105
template< class _Ty, class  = void> 
#line 2106
struct _Weak_binary_args : public _Weak_argument_type< _Ty>  { }; 
#line 2108
__pragma( warning(push)) __pragma( warning(disable : 4996)) 
#line 2109
template< class _Ty> 
#line 2110
struct _Weak_binary_args< _Ty, void_t< typename _Ty::first_argument_type, typename _Ty::second_argument_type> >  : public _Weak_argument_type< _Ty>  { 
#line 2113
using first_argument_type = typename _Ty::first_argument_type; 
#line 2114
using second_argument_type = typename _Ty::second_argument_type; 
#line 2115
}; 
#line 2116
__pragma( warning(pop)) 
#line 2118
template< class _Ty> using _Weak_types = conditional_t< is_function_v< remove_pointer_t< _Ty> > , _Function_args< remove_pointer_t< _Ty> > , conditional_t< is_member_function_pointer_v< _Ty> , _Is_memfunptr< remove_cv_t< _Ty> > , _Weak_binary_args< _Ty> > > ; 
#line 2122
template< class _Ty> void _Refwrap_ctor_fun(_Identity_t< _Ty &> ) noexcept; 
#line 2124
template < class _Ty >
void _Refwrap_ctor_fun ( _Identity_t < _Ty && > ) = delete;
#line 2127
template< class _Ty, class _Uty, class  = void> 
#line 2128
struct _Refwrap_has_ctor_from : public false_type { }; 
#line 2130
template< class _Ty, class _Uty> 
#line 2131
struct _Refwrap_has_ctor_from< _Ty, _Uty, void_t< decltype(std::_Refwrap_ctor_fun< _Ty> (std::declval< _Uty> ()))> >  : public true_type { 
#line 2132
}; 
#line 2134
template < class _Ty >
class reference_wrapper

    : public _Weak_types < _Ty >

{
public :
    static_assert ( is_object_v < _Ty > || is_function_v < _Ty >,
        "reference_wrapper<T> requires T to be an object type or a function type." );

    using type = _Ty;

    template < class _Uty, enable_if_t < conjunction_v < negation < is_same < _Remove_cvref_t < _Uty >, reference_wrapper >>,
                                          _Refwrap_has_ctor_from < _Ty, _Uty >>,
                              int > = 0 >
    inline reference_wrapper ( _Uty && _Val ) noexcept (
        noexcept ( :: std :: _Refwrap_ctor_fun < _Ty > ( :: std :: declval < _Uty > ( ) ) ) ) {
        _Ty & _Ref = static_cast < _Uty && > ( _Val );
        _Ptr = :: std :: addressof ( _Ref );
    }

    inline operator _Ty & ( ) const noexcept {
        return * _Ptr;
    }

    [ [ nodiscard ] ] inline _Ty & get ( ) const noexcept {
        return * _Ptr;
    }

private :
    _Ty * _Ptr { };

public :
    template < class ... _Types >
    inline auto operator ( ) ( _Types && ... _Args ) const
        noexcept ( noexcept ( :: std :: invoke ( * _Ptr, static_cast < _Types && > ( _Args ) ... ) ) )
        -> decltype ( :: std :: invoke ( * _Ptr, static_cast < _Types && > ( _Args ) ... ) ) {
        return :: std :: invoke ( * _Ptr, static_cast < _Types && > ( _Args ) ... );
    }
};
#line 2180 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template < class _Ty >
[ [ nodiscard ] ] inline reference_wrapper < _Ty > ref ( _Ty & _Val ) noexcept {
    return reference_wrapper < _Ty > ( _Val );
}
#line 2185
template < class _Ty >
void ref ( const _Ty && ) = delete;
#line 2188
template < class _Ty >
[ [ nodiscard ] ] inline reference_wrapper < _Ty > ref ( reference_wrapper < _Ty > _Val ) noexcept {
    return _Val;
}
#line 2193
template < class _Ty >
[ [ nodiscard ] ] inline reference_wrapper < const _Ty > cref ( const _Ty & _Val ) noexcept {
    return reference_wrapper < const _Ty > ( _Val );
}
#line 2198
template < class _Ty >
void cref ( const _Ty && ) = delete;
#line 2201
template < class _Ty >
[ [ nodiscard ] ] inline reference_wrapper < const _Ty > cref ( reference_wrapper < _Ty > _Val ) noexcept {
    return _Val;
}
#line 2226 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class _Ty> struct _Is_swappable; 
#line 2229
template< class _Ty> struct _Is_nothrow_swappable; 
#line 2235 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template < class _Ty, int _Enabled = 0 >

inline void swap ( _Ty &, _Ty & ) noexcept ( is_nothrow_move_constructible_v < _Ty > && is_nothrow_move_assignable_v < _Ty > );
#line 2239 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template < class _Ty, size_t _Size, enable_if_t < _Is_swappable < _Ty > :: value, int > = 0 >
inline void swap ( _Ty ( & ) [ _Size ], _Ty ( & ) [ _Size ] ) noexcept ( _Is_nothrow_swappable < _Ty > :: value );
#line 2242
template< class _Ty1, class _Ty2, class  = void> 
#line 2243
struct _Swappable_with_helper : public false_type { }; 
#line 2245
template< class _Ty1, class _Ty2> 
#line 2246
struct _Swappable_with_helper< _Ty1, _Ty2, void_t< decltype(swap(std::declval< _Ty1> (), std::declval< _Ty2> ()))> >  : public true_type { 
#line 2247
}; 
#line 2249
template< class _Ty1, class _Ty2> 
#line 2250
struct _Is_swappable_with : public bool_constant< conjunction_v< _Swappable_with_helper< _Ty1, _Ty2> , _Swappable_with_helper< _Ty2, _Ty1> > >  { 
#line 2253
}; 
#line 2255
template< class _Ty> 
#line 2256
struct _Is_swappable : public _Is_swappable_with< add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< _Ty> > ::type { 
#line 2258
}; 
#line 2260
template< class _Ty1, class _Ty2> 
#line 2261
struct _Swap_cannot_throw : public bool_constant< noexcept(swap(std::declval< _Ty1> (), std::declval< _Ty2> ())) && noexcept(swap(std::declval< _Ty2> (), std::declval< _Ty1> ()))>  { 
#line 2265
}; 
#line 2267
template< class _Ty1, class _Ty2> 
#line 2268
struct _Is_nothrow_swappable_with : public bool_constant< conjunction_v< _Is_swappable_with< _Ty1, _Ty2> , _Swap_cannot_throw< _Ty1, _Ty2> > >  { 
#line 2272
}; 
#line 2274
template< class _Ty> 
#line 2275
struct _Is_nothrow_swappable : public _Is_nothrow_swappable_with< add_lvalue_reference_t< _Ty> , add_lvalue_reference_t< _Ty> > ::type { 
#line 2278
}; 
#line 2318 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
namespace _Has_ADL_swap_detail { 
#line 2322 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
void swap(); 
#line 2325 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template< class , class  = void> 
#line 2326
struct _Has_ADL_swap : public false_type { }; 
#line 2327
template< class _Ty> 
#line 2328
struct _Has_ADL_swap< _Ty, void_t< decltype(swap(std::declval< _Ty &> (), std::declval< _Ty &> ()))> >  : public true_type { }; 
#line 2329
}
#line 2330
using _Has_ADL_swap_detail::_Has_ADL_swap;
#line 2332
template< class _Ty> constexpr bool 
#line 2333
_Is_trivially_swappable_v = conjunction_v< is_trivially_destructible< _Ty> , is_trivially_move_constructible< _Ty> , is_trivially_move_assignable< _Ty> , negation< _Has_ADL_swap_detail::_Has_ADL_swap< _Ty> > > ; 
#line 2341
template< class _Ty> 
#line 2342
struct _Is_trivially_swappable : public bool_constant< _Is_trivially_swappable_v< _Ty> >  { 
#line 2344
}; 
#line 2403 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
template < class _Bitmask >
[ [ nodiscard ] ] constexpr bool _Bitmask_includes_any ( _Bitmask _Left, _Bitmask _Elements ) noexcept {
    return ( _Left & _Elements ) != _Bitmask { };
}
#line 2408
template < class _Bitmask >
[ [ nodiscard ] ] constexpr bool _Bitmask_includes_all ( _Bitmask _Left, _Bitmask _Elements ) noexcept {
    return ( _Left & _Elements ) == _Elements;
}
#line 2416
constexpr size_t _FNV_offset_basis = 14695981039346656037Ui64; 
#line 2417
constexpr size_t _FNV_prime = 1099511628211Ui64; 
#line 2423 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\type_traits"
[[nodiscard]] inline size_t _Fnv1a_append_bytes(size_t _Val, const unsigned char *const _First, const size_t 
#line 2424
_Count) noexcept { 
#line 2425
for (size_t _Idx = (0); _Idx < _Count; ++_Idx) { 
#line 2426
_Val ^= (static_cast< size_t>(_First[_Idx])); 
#line 2427
_Val *= _FNV_prime; 
#line 2428
}  
#line 2430
return _Val; 
#line 2431
} 
#line 2433
template < class _Ty >
[ [ nodiscard ] ] size_t _Fnv1a_append_range ( const size_t _Val, const _Ty * const _First,
    const _Ty * const _Last ) noexcept {
    static_assert ( is_trivially_copyable_v < _Ty >, "Only trivially copyable types can be directly hashed." );
    const auto _Firstb = reinterpret_cast < const unsigned char * > ( _First );
    const auto _Lastb = reinterpret_cast < const unsigned char * > ( _Last );
    return _Fnv1a_append_bytes ( _Val, _Firstb, static_cast < size_t > ( _Lastb - _Firstb ) );
}
#line 2442
template < class _Kty >
[ [ nodiscard ] ] size_t _Fnv1a_append_value (
    const size_t _Val, const _Kty & _Keyval ) noexcept {
    static_assert ( is_trivially_copyable_v < _Kty >, "Only trivially copyable types can be directly hashed." );
    return _Fnv1a_append_bytes ( _Val, & reinterpret_cast < const unsigned char & > ( _Keyval ), sizeof ( _Kty ) );
}
#line 2449
template < class _Kty >
[ [ nodiscard ] ] size_t _Hash_representation ( const _Kty & _Keyval ) noexcept {
    return _Fnv1a_append_value ( _FNV_offset_basis, _Keyval );
}
#line 2454
template < class _Kty >
[ [ nodiscard ] ] size_t _Hash_array_representation (
    const _Kty * const _First, const size_t _Count ) noexcept {
    static_assert ( is_trivially_copyable_v < _Kty >, "Only trivially copyable types can be directly hashed." );
    return _Fnv1a_append_bytes (
        _FNV_offset_basis, reinterpret_cast < const unsigned char * > ( _First ), _Count * sizeof ( _Kty ) );
}
#line 2462
template < class _Kty >
struct hash;
#line 2465
template < class _Kty, bool _Enabled >
struct _Conditionally_enabled_hash {
    using argument_type = _Kty;
    using result_type = size_t;

    [ [ nodiscard ] ] static size_t operator ( ) ( const _Kty & _Keyval )
        noexcept ( noexcept ( hash < _Kty > :: _Do_hash ( _Keyval ) ) ) {
        return hash < _Kty > :: _Do_hash ( _Keyval );
    }
};
#line 2476
template< class _Kty> 
#line 2477
struct _Conditionally_enabled_hash< _Kty, false>  { 
#line 2478
_Conditionally_enabled_hash() = delete;
#line 2479
_Conditionally_enabled_hash(const _Conditionally_enabled_hash &) = delete;
#line 2480
_Conditionally_enabled_hash(_Conditionally_enabled_hash &&) = delete;
#line 2481
_Conditionally_enabled_hash &operator=(const _Conditionally_enabled_hash &) = delete;
#line 2482
_Conditionally_enabled_hash &operator=(_Conditionally_enabled_hash &&) = delete;
#line 2483
}; 
#line 2485
template < class _Kty >
struct hash : _Conditionally_enabled_hash < _Kty, ! is_const_v < _Kty > && ! is_volatile_v < _Kty >
                                                    && ( is_enum_v < _Kty > || is_integral_v < _Kty > || is_pointer_v < _Kty > ) > {

    static size_t _Do_hash ( const _Kty & _Keyval ) noexcept {
        return _Hash_representation ( _Keyval );
    }
};
#line 2495
template<> struct hash< float>  { 
#line 2496
using argument_type = float; 
#line 2497
using result_type = size_t; 
#line 2498
[[nodiscard]] static size_t operator()(const float _Keyval) noexcept { 
#line 2499
return _Hash_representation((_Keyval == (0.0F)) ? (0.0F) : _Keyval); 
#line 2500
} 
#line 2501
}; 
#line 2504
template<> struct hash< double>  { 
#line 2505
using argument_type = double; 
#line 2506
using result_type = size_t; 
#line 2507
[[nodiscard]] static size_t operator()(const double _Keyval) noexcept { 
#line 2508
return _Hash_representation((_Keyval == (0.0)) ? (0.0) : _Keyval); 
#line 2509
} 
#line 2510
}; 
#line 2513
template<> struct hash< long double>  { 
#line 2514
using argument_type = long double; 
#line 2515
using result_type = size_t; 
#line 2516
[[nodiscard]] static size_t operator()(const long double _Keyval) noexcept { 
#line 2517
return _Hash_representation((_Keyval == (0.0L)) ? (0.0L) : _Keyval); 
#line 2518
} 
#line 2519
}; 
#line 2522
template<> struct hash< nullptr_t>  { 
#line 2523
using argument_type = nullptr_t; 
#line 2524
using result_type = size_t; 
#line 2525
[[nodiscard]] static size_t operator()(nullptr_t) noexcept { 
#line 2526
void *_Null{((void *)0i64)}; 
#line 2527
return _Hash_representation(_Null); 
#line 2528
} 
#line 2529
}; 
#line 2531
template< class _Kty, class  = void> 
#line 2532
struct _Is_nothrow_hashable : public false_type { }; 
#line 2534
template< class _Kty> 
#line 2535
struct _Is_nothrow_hashable< _Kty, void_t< decltype(hash< _Kty> {}(std::declval< const _Kty &> ()))> >  : public bool_constant< noexcept(hash< _Kty> {}(std::declval< const _Kty &> ()))>  { 
#line 2536
}; 
#line 2538
template < class _Ty = void >
struct less {
    using first_argument_type = _Ty;
    using second_argument_type = _Ty;
    using result_type = bool;

    [ [ nodiscard ] ] constexpr bool operator ( ) ( const _Ty & _Left, const _Ty & _Right ) const
        noexcept ( noexcept ( :: std :: _Fake_copy_init < bool > ( _Left < _Right ) ) ) {
        return _Left < _Right;
    }
};
#line 2551
template<> struct less< void>  { 
#line 2552
template < class _Ty1, class _Ty2 >
    [ [ nodiscard ] ] constexpr auto operator ( ) ( _Ty1 && _Left, _Ty2 && _Right ) const
        noexcept ( noexcept ( static_cast < _Ty1 && > ( _Left ) < static_cast < _Ty2 && > ( _Right ) ) )
        -> decltype ( static_cast < _Ty1 && > ( _Left ) < static_cast < _Ty2 && > ( _Right ) ) {
        return static_cast < _Ty1 && > ( _Left ) < static_cast < _Ty2 && > ( _Right );
    }
#line 2559
using is_transparent = int; 
#line 2560
}; 
#line 2564
template< class _FloatingType> struct _Floating_type_traits; 
#line 2568
template<> struct _Floating_type_traits< float>  { 
#line 2569
static constexpr int32_t _Mantissa_bits = 24; 
#line 2570
static constexpr int32_t _Exponent_bits = 8; 
#line 2571
static constexpr int32_t _Maximum_binary_exponent = 127; 
#line 2572
static constexpr int32_t _Minimum_binary_exponent = (-126); 
#line 2573
static constexpr int32_t _Exponent_bias = 127; 
#line 2574
static constexpr int32_t _Sign_shift = 31; 
#line 2575
static constexpr int32_t _Exponent_shift = 23; 
#line 2577
using _Uint_type = uint32_t; 
#line 2579
static constexpr uint32_t _Exponent_mask = 255U; 
#line 2580
static constexpr uint32_t _Normal_mantissa_mask = 16777215U; 
#line 2581
static constexpr uint32_t _Denormal_mantissa_mask = 8388607U; 
#line 2582
static constexpr uint32_t _Special_nan_mantissa_mask = 4194304U; 
#line 2583
static constexpr uint32_t _Shifted_sign_mask = 2147483648U; 
#line 2584
static constexpr uint32_t _Shifted_exponent_mask = 2139095040U; 
#line 2586
static constexpr float _Minimum_value = (1.175494351e-38F); 
#line 2587
static constexpr float _Maximum_value = (3.402823466e+38F); 
#line 2588
}; 
#line 2591
template<> struct _Floating_type_traits< double>  { 
#line 2592
static constexpr int32_t _Mantissa_bits = 53; 
#line 2593
static constexpr int32_t _Exponent_bits = 11; 
#line 2594
static constexpr int32_t _Maximum_binary_exponent = 1023; 
#line 2595
static constexpr int32_t _Minimum_binary_exponent = (-1022); 
#line 2596
static constexpr int32_t _Exponent_bias = 1023; 
#line 2597
static constexpr int32_t _Sign_shift = 63; 
#line 2598
static constexpr int32_t _Exponent_shift = 52; 
#line 2600
using _Uint_type = uint64_t; 
#line 2602
static constexpr uint64_t _Exponent_mask = (2047U); 
#line 2603
static constexpr uint64_t _Normal_mantissa_mask = 9007199254740991Ui64; 
#line 2604
static constexpr uint64_t _Denormal_mantissa_mask = 4503599627370495Ui64; 
#line 2605
static constexpr uint64_t _Special_nan_mantissa_mask = 2251799813685248Ui64; 
#line 2606
static constexpr uint64_t _Shifted_sign_mask = 0x8000000000000000Ui64; 
#line 2607
static constexpr uint64_t _Shifted_exponent_mask = 9218868437227405312Ui64; 
#line 2609
static constexpr double _Minimum_value = (2.225073858507201383e-308); 
#line 2610
static constexpr double _Maximum_value = (1.797693134862315708e+308); 
#line 2611
}; 
#line 2614
template<> struct _Floating_type_traits< long double>  : public std::_Floating_type_traits< double>  { }; 
#line 2618
template < class _To, class _From,
    enable_if_t < conjunction_v < bool_constant < sizeof ( _To ) == sizeof ( _From ) >, is_trivially_copyable < _To >,
                    is_trivially_copyable < _From > >,
        int > = 0 >
[ [ nodiscard ] ] constexpr _To _Bit_cast ( const _From & _Val ) noexcept {
    return __builtin_bit_cast ( _To, _Val );
}
#line 2626
template < class _Ty, enable_if_t < is_floating_point_v < _Ty >, int > = 0 >
[ [ nodiscard ] ] constexpr auto _Float_abs_bits ( const _Ty & _Xx ) noexcept {
    using _Traits = _Floating_type_traits < _Ty >;
    using _Uint_type = typename _Traits :: _Uint_type;
    const auto _Bits = _Bit_cast < _Uint_type > ( _Xx );
    return _Bits & ~ _Traits :: _Shifted_sign_mask;
}
#line 2634
template < class _Ty, enable_if_t < is_floating_point_v < _Ty >, int > = 0 >
[ [ nodiscard ] ] constexpr _Ty _Float_abs ( const _Ty _Xx ) noexcept {
    return _Bit_cast < _Ty > ( _Float_abs_bits ( _Xx ) );
}
#line 2639
template < class _Ty, enable_if_t < is_floating_point_v < _Ty >, int > = 0 >
[ [ nodiscard ] ] constexpr bool _Is_nan ( const _Ty _Xx ) noexcept {
    using _Traits = _Floating_type_traits < _Ty >;
    return _Float_abs_bits ( _Xx ) > _Traits :: _Shifted_exponent_mask;
}
#line 2645
template < class _Ty, enable_if_t < is_floating_point_v < _Ty >, int > = 0 >
[ [ nodiscard ] ] constexpr bool _Is_finite ( const _Ty _Xx ) noexcept {
    using _Traits = _Floating_type_traits < _Ty >;
    return _Float_abs_bits ( _Xx ) < _Traits :: _Shifted_exponent_mask;
}
#line 2651
template< bool _IsConst, class _Ty> using _Maybe_const = conditional_t< _IsConst, const _Ty, _Ty> ; 
#line 2654
template < class _Ty, size_t _Size >
void _Swap_trivial_arrays ( _Ty ( & _Left ) [ _Size ], _Ty ( & _Right ) [ _Size ] ) noexcept {






    auto _Left_ptr = reinterpret_cast < unsigned char * > ( & _Left );
    auto _Right_ptr = reinterpret_cast < unsigned char * > ( & _Right );

    constexpr size_t _Part_size_bytes = 64;
    constexpr size_t _Size_bytes = _Size * sizeof ( _Ty );
    constexpr size_t _Size_tail = _Size_bytes % _Part_size_bytes;
    constexpr size_t _Size_parts = _Size_bytes - _Size_tail;

    if constexpr ( _Size_parts != 0 ) {
        const auto _Stop = _Left_ptr + _Size_parts;
        do {
            struct _Buffer_type {
                unsigned char _Data [ _Part_size_bytes ];
            };

            ;

            const _Buffer_type _Buffer = * reinterpret_cast < const _Buffer_type * > ( _Left_ptr );
            * reinterpret_cast < _Buffer_type * > ( _Left_ptr ) = * reinterpret_cast < const _Buffer_type * > ( _Right_ptr );
            * reinterpret_cast < _Buffer_type * > ( _Right_ptr ) = _Buffer;
            _Left_ptr += _Part_size_bytes;
            _Right_ptr += _Part_size_bytes;
        } while ( _Left_ptr != _Stop );
    }

    if constexpr ( _Size_tail != 0 ) {
        struct _Last_buffer_type {
            unsigned char _Data [ _Size_tail ];
        };

        ;

        const _Last_buffer_type _Last_buffer = * reinterpret_cast < const _Last_buffer_type * > ( _Left_ptr );
        * reinterpret_cast < _Last_buffer_type * > ( _Left_ptr ) = * reinterpret_cast < const _Last_buffer_type * > ( _Right_ptr );
        * reinterpret_cast < _Last_buffer_type * > ( _Right_ptr ) = _Last_buffer;
    }
}
#line 2699
}
#line 2709
#pragma warning(pop)
#pragma pack ( pop )
#line 23 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
#pragma pack ( push, 8 )
#pragma warning(push, 3)
#pragma warning(disable : 4180 4324 4412 4455 4494 4514 4574 4582 4583 4587 4588 4619 4623 4625 4626 4643 4648 4702 4793 4820 4868 4988 5026 5027 5045 5220 5246 5278 5280 5281 5285 5291 6294 4984 5053 )
#line 42
namespace std { 
#line 43
template < class _Ty, _Ty ... _Vals >
struct integer_sequence {
    static_assert ( is_integral_v < _Ty >, "integer_sequence<T, I...> requires T to be an integral type." );

    using value_type = _Ty;

    [ [ nodiscard ] ] static constexpr size_t size ( ) noexcept {
        return sizeof ... ( _Vals );
    }
};
#line 54
template< class _Ty, _Ty _Size> using make_integer_sequence = __make_integer_seq< integer_sequence, _Ty, _Size> ; 
#line 57
template< size_t ..._Vals> using index_sequence = integer_sequence< size_t, _Vals...> ; 
#line 60
template< size_t _Size> using make_index_sequence = make_integer_sequence< size_t, _Size> ; 
#line 63
template< class ..._Types> using index_sequence_for = make_index_sequence< sizeof...(_Types)> ; 
#line 66
template < class _Ty, class _Pr >
[ [ nodiscard ] ] constexpr const _Ty & ( max ) ( const _Ty & _Left [ [ msvc :: lifetimebound ] ], const _Ty & _Right [ [ msvc :: lifetimebound ] ],
    _Pr _Pred ) noexcept ( noexcept ( _Pred ( _Left, _Right ) ) ) {

    return _Pred ( _Left, _Right ) ? _Right : _Left;
}
#line 73
#pragma warning(push)
#pragma warning(disable : 28285)
template < class _Ty >
[ [ nodiscard ] ] constexpr const _Ty &
    ( max ) ( const _Ty & _Left [ [ msvc :: lifetimebound ] ], const _Ty & _Right [ [ msvc :: lifetimebound ] ] )
        noexcept ( noexcept ( _Left < _Right ) ) {

    return _Left < _Right ? _Right : _Left;
}
#pragma warning(pop)
#line 84
template< class _Ty, class _Pr> 
#line 85
[[nodiscard]] constexpr _Ty 
#line 84
max(initializer_list< _Ty> , _Pr); 
#line 87
template< class _Ty> 
#line 88
[[nodiscard]] constexpr _Ty 
#line 87
max(initializer_list< _Ty> ); 
#line 90
template < class _Ty, class _Pr >
[ [ nodiscard ] ] constexpr const _Ty & ( min ) ( const _Ty & _Left [ [ msvc :: lifetimebound ] ], const _Ty & _Right [ [ msvc :: lifetimebound ] ],
    _Pr _Pred ) noexcept ( noexcept ( _Pred ( _Right, _Left ) ) ) {

    return _Pred ( _Right, _Left ) ? _Right : _Left;
}
#line 97
#pragma warning(push)
#pragma warning(disable : 28285)
template < class _Ty >
[ [ nodiscard ] ] constexpr const _Ty &
    ( min ) ( const _Ty & _Left [ [ msvc :: lifetimebound ] ], const _Ty & _Right [ [ msvc :: lifetimebound ] ] )
        noexcept ( noexcept ( _Right < _Left ) ) {

    return _Right < _Left ? _Right : _Left;
}
#pragma warning(pop)
#line 108
template< class _Ty, class _Pr> 
#line 109
[[nodiscard]] constexpr _Ty 
#line 108
min(initializer_list< _Ty> , _Pr); 
#line 111
template< class _Ty> 
#line 112
[[nodiscard]] constexpr _Ty 
#line 111
min(initializer_list< _Ty> ); 
#line 114
template < class _Ty, size_t _Size, enable_if_t < _Is_swappable < _Ty > :: value, int > >
inline void swap ( _Ty ( & _Left ) [ _Size ], _Ty ( & _Right ) [ _Size ] ) noexcept ( _Is_nothrow_swappable < _Ty > :: value ) {
    if ( & _Left == & _Right ) {
        return;
    }

    if constexpr ( _Is_trivially_swappable_v < _Ty > ) {
        if ( ! :: std :: _Is_constant_evaluated ( ) ) {
            :: std :: _Swap_trivial_arrays ( _Left, _Right );
            return;
        }
    }

    _Ty * _First1 = _Left;
    _Ty * _Last1 = _First1 + _Size;
    _Ty * _First2 = _Right;
    for (; _First1 != _Last1; ++ _First1, ++ _First2 ) {
        swap ( * _First1, * _First2 );
    }
}
#line 138 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template < class _Ty, int _Enabled >

inline void swap ( _Ty & _Left, _Ty & _Right )
    noexcept ( is_nothrow_move_constructible_v < _Ty > && is_nothrow_move_assignable_v < _Ty > ) {
    _Ty _Tmp = :: std :: move ( _Left );
    _Left = :: std :: move ( _Right );
    _Right = :: std :: move ( _Tmp );
}
#line 147 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
struct piecewise_construct_t { 
#line 148
explicit piecewise_construct_t() = default;
#line 149
}; 
#line 151
constexpr piecewise_construct_t piecewise_construct{}; 
#line 153
struct _Ignore { 
#line 154
template < class _Ty >
    constexpr const _Ignore & operator = ( const _Ty & ) const noexcept {

        return * this;
    }
#line 159
}; 
#line 161
constexpr _Ignore ignore{}; 
#line 163
template< class ..._Types> class
#line 164
 [[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [tuple.tuple.general]/1" )]] tuple; 
#line 166
template < class _Ty1, class _Ty2 >
struct pair;
#line 169
template< class _Ty, size_t _Size> class array; 
#line 172
template< class _Tuple> struct tuple_size; 
#line 175
template< class _Ty> 
#line 176
[[msvc::no_specializations("Specializing this standard library template is forbidden by N5014 [namespace.std]/3" )]] constexpr size_t tuple_size_v = (tuple_size< _Ty> ::value); 
#line 178
template< size_t _Index, class _Tuple> struct tuple_element; 
#line 181
template< size_t _Index, class _Tuple> using tuple_element_t = typename tuple_element< _Index, _Tuple> ::type; 
#line 184
template< size_t _Index, class ..._Types> 
#line 185
[[nodiscard]] constexpr auto &&
#line 184
_Tuple_get(tuple< _Types...>  && _Tuple) noexcept; 
#line 187
template< size_t _Index, class ..._Types> 
#line 188
[[nodiscard]] constexpr tuple_element_t< _Index, tuple< _Types...> >  &
#line 187
get(tuple< _Types...>  & _Tuple) noexcept; 
#line 190
template< size_t _Index, class ..._Types> 
#line 191
[[nodiscard]] constexpr const tuple_element_t< _Index, tuple< _Types...> >  &
#line 190
get(const tuple< _Types...>  & _Tuple) noexcept; 
#line 193
template< size_t _Index, class ..._Types> 
#line 194
[[nodiscard]] constexpr tuple_element_t< _Index, tuple< _Types...> >  &&
#line 193
get(tuple< _Types...>  && _Tuple) noexcept; 
#line 196
template< size_t _Index, class ..._Types> 
#line 197
[[nodiscard]] constexpr const tuple_element_t< _Index, tuple< _Types...> >  &&
#line 196
get(const tuple< _Types...>  && _Tuple) noexcept; 
#line 199
template< size_t _Idx, class _Ty, size_t _Size> 
#line 200
[[nodiscard]] constexpr _Ty &
#line 199
get(array< _Ty, _Size>  & _Arr) noexcept; 
#line 202
template< size_t _Idx, class _Ty, size_t _Size> 
#line 203
[[nodiscard]] constexpr const _Ty &
#line 202
get(const array< _Ty, _Size>  & _Arr) noexcept; 
#line 205
template< size_t _Idx, class _Ty, size_t _Size> 
#line 206
[[nodiscard]] constexpr _Ty &&
#line 205
get(array< _Ty, _Size>  && _Arr) noexcept; 
#line 208
template< size_t _Idx, class _Ty, size_t _Size> 
#line 209
[[nodiscard]] constexpr const _Ty &&
#line 208
get(const array< _Ty, _Size>  && _Arr) noexcept; 
#line 249 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template < class _Ty1, class _Ty2 >
struct pair {
    using first_type = _Ty1;
    using second_type = _Ty2;

    template < class _Uty1 = _Ty1, class _Uty2 = _Ty2,
        enable_if_t < conjunction_v < is_default_constructible < _Uty1 >, is_default_constructible < _Uty2 >>, int > = 0 >
    constexpr explicit (
        ! conjunction_v < _Is_implicitly_default_constructible < _Uty1 >, _Is_implicitly_default_constructible < _Uty2 >> ) pair ( )
        noexcept ( is_nothrow_default_constructible_v < _Uty1 > && is_nothrow_default_constructible_v < _Uty2 > )
        : first ( ), second ( ) { }

    template < class _Uty1 = _Ty1, class _Uty2 = _Ty2,
        enable_if_t < conjunction_v < is_copy_constructible < _Uty1 >, is_copy_constructible < _Uty2 >>, int > = 0 >
    constexpr explicit ( ! conjunction_v < is_convertible < const _Uty1 &, _Uty1 >, is_convertible < const _Uty2 &, _Uty2 >> )
        pair ( const _Ty1 & _Val1, const _Ty2 & _Val2 )
            noexcept ( is_nothrow_copy_constructible_v < _Uty1 > && is_nothrow_copy_constructible_v < _Uty2 > )
        : first ( _Val1 ), second ( _Val2 ) { }




    template < class _Other1, class _Other2,

        enable_if_t < conjunction_v < is_constructible < _Ty1, _Other1 >, is_constructible < _Ty2, _Other2 >>, int > = 0 >
    constexpr explicit ( ! conjunction_v < is_convertible < _Other1, _Ty1 >, is_convertible < _Other2, _Ty2 >> )
        pair ( _Other1 && _Val1, _Other2 && _Val2 ) noexcept (
            is_nothrow_constructible_v < _Ty1, _Other1 > && is_nothrow_constructible_v < _Ty2, _Other2 > )
        : first ( :: std :: forward < _Other1 > ( _Val1 ) ), second ( :: std :: forward < _Other2 > ( _Val2 ) ) {
    }











    pair ( const pair & ) = default;
    pair ( pair && ) = default;


















    template < class _Other1, class _Other2,
        enable_if_t < conjunction_v < is_constructible < _Ty1, const _Other1 & >, is_constructible < _Ty2, const _Other2 & >>,
            int > = 0 >
    constexpr explicit ( ! conjunction_v < is_convertible < const _Other1 &, _Ty1 >, is_convertible < const _Other2 &, _Ty2 >> )
        pair ( const pair < _Other1, _Other2 > & _Right )
            noexcept ( is_nothrow_constructible_v < _Ty1, const _Other1 & >
                     && is_nothrow_constructible_v < _Ty2, const _Other2 & > )
        : first ( _Right . first ), second ( _Right . second ) { }












    template < class _Other1, class _Other2,
        enable_if_t < conjunction_v < is_constructible < _Ty1, _Other1 >, is_constructible < _Ty2, _Other2 >>, int > = 0 >
    constexpr explicit ( ! conjunction_v < is_convertible < _Other1, _Ty1 >, is_convertible < _Other2, _Ty2 >> )
        pair ( pair < _Other1, _Other2 > && _Right ) noexcept (
            is_nothrow_constructible_v < _Ty1, _Other1 > && is_nothrow_constructible_v < _Ty2, _Other2 > )
        : first ( :: std :: forward < _Other1 > ( _Right . first ) ), second ( :: std :: forward < _Other2 > ( _Right . second ) ) { }


















































    template < class ... _Types1, class ... _Types2 >
    inline pair ( piecewise_construct_t, tuple < _Types1 ... > _Val1, tuple < _Types2 ... > _Val2 )
        : pair ( _Val1, _Val2, index_sequence_for < _Types1 ... > { }, index_sequence_for < _Types2 ... > { } ) { }

    pair & operator = ( const volatile pair & ) = delete;

    template < class _Myself = pair,
        enable_if_t < conjunction_v < _Is_copy_assignable_no_precondition_check < typename _Myself :: first_type >,
                        _Is_copy_assignable_no_precondition_check < typename _Myself :: second_type >>,
            int > = 0 >
    inline pair & operator = ( _Identity_t < const _Myself & > _Right )
        noexcept ( conjunction_v < is_nothrow_copy_assignable < _Ty1 >, is_nothrow_copy_assignable < _Ty2 >> ) {
        first = _Right . first;
        second = _Right . second;
        return * this;
    }














    template < class _Myself = pair,
        enable_if_t < conjunction_v < _Is_move_assignable_no_precondition_check < typename _Myself :: first_type >,
                        _Is_move_assignable_no_precondition_check < typename _Myself :: second_type >>,
            int > = 0 >
    inline pair & operator = ( _Identity_t < _Myself && > _Right )
        noexcept ( conjunction_v < is_nothrow_move_assignable < _Ty1 >, is_nothrow_move_assignable < _Ty2 >> ) {
        first = :: std :: forward < _Ty1 > ( _Right . first );
        second = :: std :: forward < _Ty2 > ( _Right . second );
        return * this;
    }














    template < class _Other1, class _Other2,
        enable_if_t < conjunction_v < negation < is_same < pair, pair < _Other1, _Other2 >> >, is_assignable < _Ty1 &, const _Other1 & >,
                        is_assignable < _Ty2 &, const _Other2 & >>,
            int > = 0 >
    inline pair & operator = ( const pair < _Other1, _Other2 > & _Right )
        noexcept ( is_nothrow_assignable_v < _Ty1 &, const _Other1 & >
                 && is_nothrow_assignable_v < _Ty2 &, const _Other2 & > ) {
        first = _Right . first;
        second = _Right . second;
        return * this;
    }














    template < class _Other1, class _Other2,
        enable_if_t < conjunction_v < negation < is_same < pair, pair < _Other1, _Other2 >> >, is_assignable < _Ty1 &, _Other1 >,
                        is_assignable < _Ty2 &, _Other2 >>,
            int > = 0 >
    inline pair & operator = ( pair < _Other1, _Other2 > && _Right ) noexcept (
        is_nothrow_assignable_v < _Ty1 &, _Other1 > && is_nothrow_assignable_v < _Ty2 &, _Other2 > ) {
        first = :: std :: forward < _Other1 > ( _Right . first );
        second = :: std :: forward < _Other2 > ( _Right . second );
        return * this;
    }





































    inline void swap ( pair & _Right )
        noexcept ( _Is_nothrow_swappable < _Ty1 > :: value && _Is_nothrow_swappable < _Ty2 > :: value ) {
        using :: std :: swap;
        swap ( first, _Right . first );
        swap ( second, _Right . second );
    }











    _Ty1 first;
    _Ty2 second;

private :
    template < class _Tuple1, class _Tuple2, size_t ... _Indices1, size_t ... _Indices2 >
    constexpr pair ( _Tuple1 & _Val1, _Tuple2 & _Val2, index_sequence < _Indices1 ... >, index_sequence < _Indices2 ... > )
        : first ( :: std :: _Tuple_get < _Indices1 > ( :: std :: move ( _Val1 ) ) ... ),
          second ( :: std :: _Tuple_get < _Indices2 > ( :: std :: move ( _Val2 ) ) ... ) { }
};
#line 544 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template < class _Ty1, class _Ty2,
    enable_if_t < _Is_swappable < _Ty1 > :: value && _Is_swappable < _Ty2 > :: value, int > = 0 >
inline void swap ( pair < _Ty1, _Ty2 > & _Left, pair < _Ty1, _Ty2 > & _Right ) noexcept ( noexcept ( _Left . swap ( _Right ) ) ) {
    _Left . swap ( _Right );
}
#line 559 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template < class _Ty1, class _Ty2, class _Uty1, class _Uty2 >
[ [ nodiscard ] ] constexpr bool operator == ( const pair < _Ty1, _Ty2 > & _Left, const pair < _Uty1, _Uty2 > & _Right ) {
    return _Left . first == _Right . first && _Left . second == _Right . second;
}
#line 575 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template < class _Ty1, class _Ty2, class _Uty1, class _Uty2 >
[ [ nodiscard ] ] constexpr bool operator != ( const pair < _Ty1, _Ty2 > & _Left, const pair < _Uty1, _Uty2 > & _Right ) {
    return ! ( _Left == _Right );
}
#line 580
template < class _Ty1, class _Ty2, class _Uty1, class _Uty2 >
[ [ nodiscard ] ] constexpr bool operator < ( const pair < _Ty1, _Ty2 > & _Left, const pair < _Uty1, _Uty2 > & _Right ) {
    return _Left . first < _Right . first || ( ! ( _Right . first < _Left . first ) && _Left . second < _Right . second );
}
#line 585
template < class _Ty1, class _Ty2, class _Uty1, class _Uty2 >
[ [ nodiscard ] ] constexpr bool operator > ( const pair < _Ty1, _Ty2 > & _Left, const pair < _Uty1, _Uty2 > & _Right ) {
    return _Right < _Left;
}
#line 590
template < class _Ty1, class _Ty2, class _Uty1, class _Uty2 >
[ [ nodiscard ] ] constexpr bool operator <= ( const pair < _Ty1, _Ty2 > & _Left, const pair < _Uty1, _Uty2 > & _Right ) {
    return ! ( _Right < _Left );
}
#line 595
template < class _Ty1, class _Ty2, class _Uty1, class _Uty2 >
[ [ nodiscard ] ] constexpr bool operator >= ( const pair < _Ty1, _Ty2 > & _Left, const pair < _Uty1, _Uty2 > & _Right ) {
    return ! ( _Left < _Right );
}
#line 618 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template< class _Ty> 
#line 619
struct _Unrefwrap_helper { 
#line 620
using type = _Ty; 
#line 621
}; 
#line 623
template< class _Ty> 
#line 624
struct _Unrefwrap_helper< reference_wrapper< _Ty> >  { 
#line 625
using type = _Ty &; 
#line 626
}; 
#line 629
template< class _Ty> using _Unrefwrap_t = typename _Unrefwrap_helper< decay_t< _Ty> > ::type; 
#line 632
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr pair < _Unrefwrap_t < _Ty1 >, _Unrefwrap_t < _Ty2 > > make_pair ( _Ty1 && _Val1, _Ty2 && _Val2 )
    noexcept ( is_nothrow_constructible_v < _Unrefwrap_t < _Ty1 >, _Ty1 >
             && is_nothrow_constructible_v < _Unrefwrap_t < _Ty2 >, _Ty2 > ) {

    using _Mypair = pair < _Unrefwrap_t < _Ty1 >, _Unrefwrap_t < _Ty2 >>;
    return _Mypair ( :: std :: forward < _Ty1 > ( _Val1 ), :: std :: forward < _Ty2 > ( _Val2 ) );
}
#line 641
namespace rel_ops { 
#line 642
template < class _Ty >
     [ [ nodiscard ] ] bool operator != ( const _Ty & _Left, const _Ty & _Right ) {
        return ! ( _Left == _Right );
    }
#line 647
template < class _Ty >
     [ [ nodiscard ] ] bool operator > ( const _Ty & _Left, const _Ty & _Right ) {
        return _Right < _Left;
    }
#line 652
template < class _Ty >
     [ [ nodiscard ] ] bool operator <= ( const _Ty & _Left, const _Ty & _Right ) {
        return ! ( _Right < _Left );
    }
#line 657
template < class _Ty >
     [ [ nodiscard ] ] bool operator >= ( const _Ty & _Left, const _Ty & _Right ) {
        return ! ( _Left < _Right );
    }
#line 661
}
#line 663
template< class _Tuple, class  = void> 
#line 664
struct _Tuple_size_sfinae { }; 
#line 666
template< class _Tuple> 
#line 667
struct _Tuple_size_sfinae< _Tuple, void_t< decltype(tuple_size< _Tuple> ::value)> >  : public integral_constant< ::size_t, tuple_size< _Tuple> ::value>  { 
#line 668
}; 
#line 670
template< class _Tuple> 
#line 671
struct tuple_size< const _Tuple>  : public _Tuple_size_sfinae< _Tuple>  { }; 
#line 673
template< class _Tuple> 
#line 674
struct tuple_size< volatile _Tuple>  : public _Tuple_size_sfinae< _Tuple>  { }; 
#line 676
template< class _Tuple> 
#line 677
struct tuple_size< const volatile _Tuple>  : public _Tuple_size_sfinae< _Tuple>  { }; 
#line 679
template< size_t _Index, class _Tuple> 
#line 680
struct [[msvc::known_semantics]] tuple_element< _Index, const _Tuple>  : public std::tuple_element< _Index, _Tuple>  { 
#line 681
using _Mybase = std::tuple_element< _Index, _Tuple> ; 
#line 682
using type = std::add_const_t< typename _Mybase::type> ; 
#line 683
}; 
#line 685
template< size_t _Index, class _Tuple> 
#line 687
struct
#line 686
 [[msvc::known_semantics]] tuple_element< _Index, volatile _Tuple>  : public std::tuple_element< _Index, _Tuple>  { 
#line 688
using _Mybase = std::tuple_element< _Index, _Tuple> ; 
#line 689
using type = std::add_volatile_t< typename _Mybase::type> ; 
#line 690
}; 
#line 692
template< size_t _Index, class _Tuple> 
#line 694
struct
#line 693
 [[msvc::known_semantics]] tuple_element< _Index, const volatile _Tuple>  : public std::tuple_element< _Index, _Tuple>  { 
#line 695
using _Mybase = std::tuple_element< _Index, _Tuple> ; 
#line 696
using type = std::add_cv_t< typename _Mybase::type> ; 
#line 697
}; 
#line 699
template< class _Ty, size_t _Size> 
#line 700
struct tuple_size< array< _Ty, _Size> >  : public integral_constant< ::size_t, _Size>  { }; 
#line 702
template< size_t _Idx, class _Ty, size_t _Size> 
#line 703
struct [[msvc::known_semantics]] tuple_element< _Idx, array< _Ty, _Size> >  { 
#line 704
static_assert((_Idx < _Size), "array index out of bounds");
#line 706
using type = _Ty; 
#line 707
}; 
#line 709
template< class ..._Types> 
#line 710
struct tuple_size< tuple< _Types...> >  : public integral_constant< ::size_t, sizeof...(_Types)>  { }; 
#line 712
template< size_t _Index> 
#line 713
struct [[msvc::known_semantics]] tuple_element< _Index, tuple< > >  { 
#line 714
static_assert(false, "tuple index out of bounds");
#line 715
}; 
#line 717
template< class _This, class ..._Rest> 
#line 718
struct [[msvc::known_semantics]] tuple_element< 0, tuple< _This, _Rest...> >  { 
#line 719
using type = _This; 
#line 721
using _Ttype = tuple< _This, _Rest...> ; 
#line 722
}; 
#line 724
template< size_t _Index, class _This, class ..._Rest> 
#line 725
struct [[msvc::known_semantics]] tuple_element< _Index, tuple< _This, _Rest...> >  : public std::tuple_element< _Index - (1), tuple< _Rest...> >  { 
#line 726
}; 
#line 728
template< class _Ty1, class _Ty2> 
#line 729
struct tuple_size< pair< _Ty1, _Ty2> >  : public integral_constant< size_t, 2Ui64>  { }; 
#line 731
template< size_t _Idx, class _Ty1, class _Ty2> 
#line 732
struct [[msvc::known_semantics]] tuple_element< _Idx, pair< _Ty1, _Ty2> >  { 
#line 733
static_assert((_Idx < (2)), "pair index out of bounds");
#line 735
using type = conditional_t< _Idx == (0), _Ty1, _Ty2> ; 
#line 736
}; 
#line 738
template < size_t _Idx, class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr tuple_element_t < _Idx, pair < _Ty1, _Ty2 > > & get ( pair < _Ty1, _Ty2 > & _Pr ) noexcept {

    if constexpr ( _Idx == 0 ) {
        return _Pr . first;
    } else {
        return _Pr . second;
    }
}
#line 748
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr _Ty1 & get ( pair < _Ty1, _Ty2 > & _Pr ) noexcept {

    return _Pr . first;
}
#line 754
template < class _Ty2, class _Ty1 >
[ [ nodiscard ] ] constexpr _Ty2 & get ( pair < _Ty1, _Ty2 > & _Pr ) noexcept {

    return _Pr . second;
}
#line 760
template < size_t _Idx, class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr const tuple_element_t < _Idx, pair < _Ty1, _Ty2 > > & get ( const pair < _Ty1, _Ty2 > & _Pr ) noexcept {

    if constexpr ( _Idx == 0 ) {
        return _Pr . first;
    } else {
        return _Pr . second;
    }
}
#line 770
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr const _Ty1 & get ( const pair < _Ty1, _Ty2 > & _Pr ) noexcept {

    return _Pr . first;
}
#line 776
template < class _Ty2, class _Ty1 >
[ [ nodiscard ] ] constexpr const _Ty2 & get ( const pair < _Ty1, _Ty2 > & _Pr ) noexcept {

    return _Pr . second;
}
#line 782
template < size_t _Idx, class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr tuple_element_t < _Idx, pair < _Ty1, _Ty2 > > && get ( pair < _Ty1, _Ty2 > && _Pr ) noexcept {

    if constexpr ( _Idx == 0 ) {
        return :: std :: forward < _Ty1 > ( _Pr . first );
    } else {
        return :: std :: forward < _Ty2 > ( _Pr . second );
    }
}
#line 792
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr _Ty1 && get ( pair < _Ty1, _Ty2 > && _Pr ) noexcept {

    return :: std :: forward < _Ty1 > ( _Pr . first );
}
#line 798
template < class _Ty2, class _Ty1 >
[ [ nodiscard ] ] constexpr _Ty2 && get ( pair < _Ty1, _Ty2 > && _Pr ) noexcept {

    return :: std :: forward < _Ty2 > ( _Pr . second );
}
#line 804
template < size_t _Idx, class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr const tuple_element_t < _Idx, pair < _Ty1, _Ty2 > > && get ( const pair < _Ty1, _Ty2 > && _Pr ) noexcept {

    if constexpr ( _Idx == 0 ) {
        return :: std :: forward < const _Ty1 > ( _Pr . first );
    } else {
        return :: std :: forward < const _Ty2 > ( _Pr . second );
    }
}
#line 814
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr const _Ty1 && get ( const pair < _Ty1, _Ty2 > && _Pr ) noexcept {

    return :: std :: forward < const _Ty1 > ( _Pr . first );
}
#line 820
template < class _Ty2, class _Ty1 >
[ [ nodiscard ] ] constexpr const _Ty2 && get ( const pair < _Ty1, _Ty2 > && _Pr ) noexcept {

    return :: std :: forward < const _Ty2 > ( _Pr . second );
}
#line 826
template < class _Ty, class _Other = _Ty >
inline _Ty exchange ( _Ty & _Val, _Other && _New_val )
    noexcept ( conjunction_v < is_nothrow_move_constructible < _Ty >, is_nothrow_assignable < _Ty &, _Other >> ) {

    _Ty _Old_val = static_cast < _Ty && > ( _Val );
    _Val = static_cast < _Other && > ( _New_val );
    return _Old_val;
}
#line 835
template < class _Ty >
[ [ nodiscard ] ] [ [ msvc :: intrinsic ] ] constexpr add_const_t < _Ty > & as_const ( _Ty & _Val ) noexcept {
    return _Val;
}
#line 840
template < class _Ty >
void as_const ( const _Ty && ) = delete;
#line 864 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr bool _Cmp_equal ( const _Ty1 _Left, const _Ty2 _Right ) noexcept {
    ;
    if constexpr ( is_signed_v < _Ty1 > == is_signed_v < _Ty2 > ) {
        return _Left == _Right;
    } else if constexpr ( is_signed_v < _Ty2 > ) {
        return _Left == static_cast < make_unsigned_t < _Ty2 >> ( _Right ) && _Right >= 0;
    } else {
        return static_cast < make_unsigned_t < _Ty1 >> ( _Left ) == _Right && _Left >= 0;
    }
}
#line 876
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr bool _Cmp_not_equal ( const _Ty1 _Left, const _Ty2 _Right ) noexcept {
    return ! :: std :: _Cmp_equal ( _Left, _Right );
}
#line 881
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr bool _Cmp_less ( const _Ty1 _Left, const _Ty2 _Right ) noexcept {
    ;
    if constexpr ( is_signed_v < _Ty1 > == is_signed_v < _Ty2 > ) {
        return _Left < _Right;
    } else if constexpr ( is_signed_v < _Ty2 > ) {
        return _Right > 0 && _Left < static_cast < make_unsigned_t < _Ty2 >> ( _Right );
    } else {
        return _Left < 0 || static_cast < make_unsigned_t < _Ty1 >> ( _Left ) < _Right;
    }
}
#line 893
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr bool _Cmp_greater ( const _Ty1 _Left, const _Ty2 _Right ) noexcept {
    return :: std :: _Cmp_less ( _Right, _Left );
}
#line 898
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr bool _Cmp_less_equal ( const _Ty1 _Left, const _Ty2 _Right ) noexcept {
    return ! :: std :: _Cmp_less ( _Right, _Left );
}
#line 903
template < class _Ty1, class _Ty2 >
[ [ nodiscard ] ] constexpr bool _Cmp_greater_equal ( const _Ty1 _Left, const _Ty2 _Right ) noexcept {
    return ! :: std :: _Cmp_less ( _Left, _Right );
}
#line 908
template < class _Ty >
[ [ nodiscard ] ] constexpr _Ty _Min_limit ( ) noexcept {
    ;
    if constexpr ( is_signed_v < _Ty > ) {
        constexpr auto _Unsigned_max = static_cast < make_unsigned_t < _Ty >> ( - 1 );
        return static_cast < _Ty > ( ( _Unsigned_max >> 1 ) + 1 );
    } else {
        return 0;
    }
}
#line 919
template < class _Ty >
[ [ nodiscard ] ] constexpr _Ty _Max_limit ( ) noexcept {
    ;
    if constexpr ( is_signed_v < _Ty > ) {
        constexpr auto _Unsigned_max = static_cast < make_unsigned_t < _Ty >> ( - 1 );
        return static_cast < _Ty > ( _Unsigned_max >> 1 );
    } else {
        return static_cast < _Ty > ( - 1 );
    }
}
#line 930
template < class _Rx, class _Ty >
[ [ nodiscard ] ] constexpr bool _In_range ( const _Ty _Value ) noexcept {
    ;

    constexpr auto _Ty_min = _Min_limit < _Ty > ( );
    constexpr auto _Rx_min = _Min_limit < _Rx > ( );

    if constexpr ( :: std :: _Cmp_less ( _Ty_min, _Rx_min ) ) {
        if ( _Value < _Ty { _Rx_min } ) {
            return false;
        }
    }

    constexpr auto _Ty_max = _Max_limit < _Ty > ( );
    constexpr auto _Rx_max = _Max_limit < _Rx > ( );

    if constexpr ( :: std :: _Cmp_greater ( _Ty_max, _Rx_max ) ) {
        if ( _Value > _Ty { _Rx_max } ) {
            return false;
        }
    }

    return true;
}
#line 1072 "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\MSVC\\14.51.36231\\include\\utility"
}
#line 1083
#pragma warning(pop)
#pragma pack ( pop )
#line 207 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
template< class T> static __inline ::cudaError_t 
#line 208
cudaLaunchKernel(T *
#line 209
func, ::dim3 
#line 210
gridDim, ::dim3 
#line 211
blockDim, void **
#line 212
args, ::size_t 
#line 213
sharedMem = 0, ::cudaStream_t 
#line 214
stream = 0) 
#line 216
{ 
#line 217
return ::cudaLaunchKernel((const void *)func, gridDim, blockDim, args, sharedMem, stream); 
#line 218
} 
#line 279
template< class ...ExpTypes, class ...ActTypes> static __inline ::cudaError_t 
#line 280
cudaLaunchKernelEx(const ::cudaLaunchConfig_t *
#line 281
config, void (*
#line 282
kernel)(ExpTypes ...), ActTypes &&...
#line 283
args) 
#line 285
{ 
#line 286
return [&](ExpTypes ...coercedArgs) { 
#line 287
void *pArgs[] = {(&coercedArgs)...}; 
#line 288
return ::cudaLaunchKernelExC(config, (const void *)(kernel), pArgs); 
#line 289
} (std::forward< ActTypes> (args)...); 
#line 290
} 
#line 348
template< class ...ActTypes> static __inline ::cudaError_t 
#line 349
cudaLaunchKernelEx(const ::cudaLaunchConfig_t *
#line 350
config, const ::cudaKernel_t 
#line 351
kernel, ActTypes &&...
#line 352
args) 
#line 354
{ 
#line 355
void *pArgs[] = {(&args)...}; 
#line 356
return ::cudaLaunchKernelExC(config, (const void *)kernel, pArgs); 
#line 357
} 
#line 410 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
template< class T> static __inline ::cudaError_t 
#line 411
cudaLaunchCooperativeKernel(T *
#line 412
func, ::dim3 
#line 413
gridDim, ::dim3 
#line 414
blockDim, void **
#line 415
args, ::size_t 
#line 416
sharedMem = 0, ::cudaStream_t 
#line 417
stream = 0) 
#line 419
{ 
#line 420
return ::cudaLaunchCooperativeKernel((const void *)func, gridDim, blockDim, args, sharedMem, stream); 
#line 421
} 
#line 454
static __inline cudaError_t cudaEventCreate(cudaEvent_t *
#line 455
event, unsigned 
#line 456
flags) 
#line 458
{ 
#line 459
return ::cudaEventCreateWithFlags(event, flags); 
#line 460
} 
#line 498
static __inline cudaError_t cudaGraphInstantiate(cudaGraphExec_t *
#line 499
pGraphExec, cudaGraph_t 
#line 500
graph, cudaGraphNode_t *
#line 501
pErrorNode, char *
#line 502
pLogBuffer, size_t 
#line 503
bufferSize) 
#line 505
{ 
#line 506
(void)pErrorNode; 
#line 507
(void)pLogBuffer; 
#line 508
(void)bufferSize; 
#line 509
return ::cudaGraphInstantiate(pGraphExec, graph, 0); 
#line 510
} 
#line 569
static __inline cudaError_t cudaMallocHost(void **
#line 570
ptr, size_t 
#line 571
size, unsigned 
#line 572
flags) 
#line 574
{ 
#line 575
return ::cudaHostAlloc(ptr, size, flags); 
#line 576
} 
#line 578
template< class T> static __inline ::cudaError_t 
#line 579
cudaHostAlloc(T **
#line 580
ptr, ::size_t 
#line 581
size, unsigned 
#line 582
flags) 
#line 584
{ 
#line 585
return ::cudaHostAlloc((void **)((void *)ptr), size, flags); 
#line 586
} 
#line 588
template< class T> static __inline ::cudaError_t 
#line 589
cudaHostGetDevicePointer(T **
#line 590
pDevice, void *
#line 591
pHost, unsigned 
#line 592
flags) 
#line 594
{ 
#line 595
return ::cudaHostGetDevicePointer((void **)((void *)pDevice), pHost, flags); 
#line 596
} 
#line 698
template< class T> static __inline ::cudaError_t 
#line 699
cudaMallocManaged(T **
#line 700
devPtr, ::size_t 
#line 701
size, unsigned 
#line 702
flags = 1) 
#line 704
{ 
#line 705
return ::cudaMallocManaged((void **)((void *)devPtr), size, flags); 
#line 706
} 
#line 717
template< class T> static __inline ::cudaError_t 
#line 718
cudaMemPrefetchBatchAsync(T **
#line 719
dptrs, ::size_t *sizes, ::size_t count, ::cudaMemLocation *
#line 720
prefetchLocs, ::size_t *prefetchLocIdxs, ::size_t numPrefetchLocs, unsigned __int64 
#line 721
flags, ::cudaStream_t stream) 
#line 723
{ 
#line 724
return ::cudaMemPrefetchBatchAsync((void **)dptrs, sizes, count, prefetchLocs, prefetchLocIdxs, numPrefetchLocs, flags, stream); 
#line 725
} 
#line 737
template< class T> static __inline ::cudaError_t 
#line 738
cudaMemPrefetchBatchAsync(T **
#line 739
dptrs, ::size_t *sizes, ::size_t count, ::cudaMemLocation prefetchLocs, unsigned __int64 flags, ::cudaStream_t stream) 
#line 741
{ 
#line 742
::size_t prefetchLocIdxs = (0); 
#line 743
return ::cudaMemPrefetchBatchAsync((void **)dptrs, sizes, count, &prefetchLocs, &prefetchLocIdxs, 1, flags, stream); 
#line 744
} 
#line 754
template< class T> static __inline ::cudaError_t 
#line 755
cudaMemDiscardAndPrefetchBatchAsync(T **
#line 756
dptrs, ::size_t *sizes, ::size_t count, ::cudaMemLocation *
#line 757
prefetchLocs, ::size_t *prefetchLocIdxs, ::size_t numPrefetchLocs, unsigned __int64 
#line 758
flags, ::cudaStream_t stream) 
#line 760
{ 
#line 761
return ::cudaMemDiscardAndPrefetchBatchAsync((void **)dptrs, sizes, count, prefetchLocs, prefetchLocIdxs, numPrefetchLocs, flags, stream); 
#line 762
} 
#line 774
template< class T> static __inline ::cudaError_t 
#line 775
cudaMemDiscardAndPrefetchBatchAsync(T **
#line 776
dptrs, ::size_t *sizes, ::size_t count, ::cudaMemLocation prefetchLocs, unsigned __int64 flags, ::cudaStream_t stream) 
#line 778
{ 
#line 779
::size_t prefetchLocIdxs = (0); 
#line 780
return ::cudaMemDiscardAndPrefetchBatchAsync((void **)dptrs, sizes, count, &prefetchLocs, &prefetchLocIdxs, 1, flags, stream); 
#line 781
} 
#line 863
template< class T> static __inline ::cudaError_t 
#line 864
cudaStreamAttachMemAsync(::cudaStream_t 
#line 865
stream, T *
#line 866
devPtr, ::size_t 
#line 867
length = 0, unsigned 
#line 868
flags = 4) 
#line 870
{ 
#line 871
return ::cudaStreamAttachMemAsync(stream, (void *)devPtr, length, flags); 
#line 872
} 
#line 874
template< class T> static __inline ::cudaError_t 
#line 875
cudaMalloc(T **
#line 876
devPtr, ::size_t 
#line 877
size) 
#line 879
{ 
#line 880
return ::cudaMalloc((void **)((void *)devPtr), size); 
#line 881
} 
#line 883
template< class T> static __inline ::cudaError_t 
#line 884
cudaMallocHost(T **
#line 885
ptr, ::size_t 
#line 886
size, unsigned 
#line 887
flags = 0) 
#line 889
{ 
#line 890
return cudaMallocHost((void **)((void *)ptr), size, flags); 
#line 891
} 
#line 893
template< class T> static __inline ::cudaError_t 
#line 894
cudaMallocPitch(T **
#line 895
devPtr, ::size_t *
#line 896
pitch, ::size_t 
#line 897
width, ::size_t 
#line 898
height) 
#line 900
{ 
#line 901
return ::cudaMallocPitch((void **)((void *)devPtr), pitch, width, height); 
#line 902
} 
#line 913
static __inline cudaError_t cudaMallocAsync(void **
#line 914
ptr, size_t 
#line 915
size, cudaMemPool_t 
#line 916
memPool, cudaStream_t 
#line 917
stream) 
#line 919
{ 
#line 920
return ::cudaMallocFromPoolAsync(ptr, size, memPool, stream); 
#line 921
} 
#line 923
template< class T> static __inline ::cudaError_t 
#line 924
cudaMallocAsync(T **
#line 925
ptr, ::size_t 
#line 926
size, ::cudaMemPool_t 
#line 927
memPool, ::cudaStream_t 
#line 928
stream) 
#line 930
{ 
#line 931
return ::cudaMallocFromPoolAsync((void **)((void *)ptr), size, memPool, stream); 
#line 932
} 
#line 934
template< class T> static __inline ::cudaError_t 
#line 935
cudaMallocAsync(T **
#line 936
ptr, ::size_t 
#line 937
size, ::cudaStream_t 
#line 938
stream) 
#line 940
{ 
#line 941
return ::cudaMallocAsync((void **)((void *)ptr), size, stream); 
#line 942
} 
#line 944
template< class T> static __inline ::cudaError_t 
#line 945
cudaMallocFromPoolAsync(T **
#line 946
ptr, ::size_t 
#line 947
size, ::cudaMemPool_t 
#line 948
memPool, ::cudaStream_t 
#line 949
stream) 
#line 951
{ 
#line 952
return ::cudaMallocFromPoolAsync((void **)((void *)ptr), size, memPool, stream); 
#line 953
} 
#line 963
template< class T, class U> static __inline ::cudaError_t 
#line 964
cudaMemcpyBatchAsync(T *const *
#line 965
dsts, U *const *srcs, const ::size_t *sizes, ::size_t count, ::cudaMemcpyAttributes *attrs, ::size_t *
#line 966
attrsIdxs, ::size_t numAttrs, ::cudaStream_t 
#line 967
hStream) 
#line 969
{ 
#line 970
return ::cudaMemcpyBatchAsync((void *const *)dsts, (const void *const *)srcs, sizes, count, attrs, attrsIdxs, numAttrs, hStream); 
#line 971
} 
#line 983
template< class T, class U> static __inline ::cudaError_t 
#line 984
cudaMemcpyBatchAsync(T *const *
#line 985
dsts, U *const *srcs, const ::size_t *sizes, ::size_t count, ::cudaMemcpyAttributes attr, ::cudaStream_t 
#line 986
hStream) 
#line 988
{ 
#line 989
::size_t attrsIdxs = (0); 
#line 990
return ::cudaMemcpyBatchAsync((void *const *)dsts, (const void *const *)srcs, sizes, count, &attr, &attrsIdxs, 1, hStream); 
#line 991
} 
#line 1002
template< class T, class U> static __inline ::cudaError_t 
#line 1003
cudaMemcpyAsync(T 
#line 1004
dst, U src, const ::size_t size, ::cudaMemcpyAttributes *attr, ::cudaStream_t hStream) 
#line 1006
{ 
#line 1007
return ::cudaMemcpyWithAttributesAsync((void *)dst, (const void *)src, size, attr, hStream); 
#line 1008
} 
#line 1047
template< class T> static __inline ::cudaError_t 
#line 1048
cudaMemcpyToSymbol(const T &
#line 1049
symbol, const void *
#line 1050
src, ::size_t 
#line 1051
count, ::size_t 
#line 1052
offset = 0, ::cudaMemcpyKind 
#line 1053
kind = cudaMemcpyHostToDevice) 
#line 1055
{ 
#line 1056
return ::cudaMemcpyToSymbol((const void *)(&symbol), src, count, offset, kind); 
#line 1057
} 
#line 1101
template< class T> static __inline ::cudaError_t 
#line 1102
cudaMemcpyToSymbolAsync(const T &
#line 1103
symbol, const void *
#line 1104
src, ::size_t 
#line 1105
count, ::size_t 
#line 1106
offset = 0, ::cudaMemcpyKind 
#line 1107
kind = cudaMemcpyHostToDevice, ::cudaStream_t 
#line 1108
stream = 0) 
#line 1110
{ 
#line 1111
return ::cudaMemcpyToSymbolAsync((const void *)(&symbol), src, count, offset, kind, stream); 
#line 1112
} 
#line 1149
template< class T> static __inline ::cudaError_t 
#line 1150
cudaMemcpyFromSymbol(void *
#line 1151
dst, const T &
#line 1152
symbol, ::size_t 
#line 1153
count, ::size_t 
#line 1154
offset = 0, ::cudaMemcpyKind 
#line 1155
kind = cudaMemcpyDeviceToHost) 
#line 1157
{ 
#line 1158
return ::cudaMemcpyFromSymbol(dst, (const void *)(&symbol), count, offset, kind); 
#line 1159
} 
#line 1203
template< class T> static __inline ::cudaError_t 
#line 1204
cudaMemcpyFromSymbolAsync(void *
#line 1205
dst, const T &
#line 1206
symbol, ::size_t 
#line 1207
count, ::size_t 
#line 1208
offset = 0, ::cudaMemcpyKind 
#line 1209
kind = cudaMemcpyDeviceToHost, ::cudaStream_t 
#line 1210
stream = 0) 
#line 1212
{ 
#line 1213
return ::cudaMemcpyFromSymbolAsync(dst, (const void *)(&symbol), count, offset, kind, stream); 
#line 1214
} 
#line 1272
template< class T> static __inline ::cudaError_t 
#line 1273
cudaGraphAddMemcpyNodeToSymbol(::cudaGraphNode_t *
#line 1274
pGraphNode, ::cudaGraph_t 
#line 1275
graph, const ::cudaGraphNode_t *
#line 1276
pDependencies, ::size_t 
#line 1277
numDependencies, const T &
#line 1278
symbol, const void *
#line 1279
src, ::size_t 
#line 1280
count, ::size_t 
#line 1281
offset, ::cudaMemcpyKind 
#line 1282
kind) 
#line 1283
{ 
#line 1284
return ::cudaGraphAddMemcpyNodeToSymbol(pGraphNode, graph, pDependencies, numDependencies, (const void *)(&symbol), src, count, offset, kind); 
#line 1285
} 
#line 1343
template< class T> static __inline ::cudaError_t 
#line 1344
cudaGraphAddMemcpyNodeFromSymbol(::cudaGraphNode_t *
#line 1345
pGraphNode, ::cudaGraph_t 
#line 1346
graph, const ::cudaGraphNode_t *
#line 1347
pDependencies, ::size_t 
#line 1348
numDependencies, void *
#line 1349
dst, const T &
#line 1350
symbol, ::size_t 
#line 1351
count, ::size_t 
#line 1352
offset, ::cudaMemcpyKind 
#line 1353
kind) 
#line 1354
{ 
#line 1355
return ::cudaGraphAddMemcpyNodeFromSymbol(pGraphNode, graph, pDependencies, numDependencies, dst, (const void *)(&symbol), count, offset, kind); 
#line 1356
} 
#line 1394
template< class T> static __inline ::cudaError_t 
#line 1395
cudaGraphMemcpyNodeSetParamsToSymbol(::cudaGraphNode_t 
#line 1396
node, const T &
#line 1397
symbol, const void *
#line 1398
src, ::size_t 
#line 1399
count, ::size_t 
#line 1400
offset, ::cudaMemcpyKind 
#line 1401
kind) 
#line 1402
{ 
#line 1403
return ::cudaGraphMemcpyNodeSetParamsToSymbol(node, (const void *)(&symbol), src, count, offset, kind); 
#line 1404
} 
#line 1442
template< class T> static __inline ::cudaError_t 
#line 1443
cudaGraphMemcpyNodeSetParamsFromSymbol(::cudaGraphNode_t 
#line 1444
node, void *
#line 1445
dst, const T &
#line 1446
symbol, ::size_t 
#line 1447
count, ::size_t 
#line 1448
offset, ::cudaMemcpyKind 
#line 1449
kind) 
#line 1450
{ 
#line 1451
return ::cudaGraphMemcpyNodeSetParamsFromSymbol(node, dst, (const void *)(&symbol), count, offset, kind); 
#line 1452
} 
#line 1500
template< class T> static __inline ::cudaError_t 
#line 1501
cudaGraphExecMemcpyNodeSetParamsToSymbol(::cudaGraphExec_t 
#line 1502
hGraphExec, ::cudaGraphNode_t 
#line 1503
node, const T &
#line 1504
symbol, const void *
#line 1505
src, ::size_t 
#line 1506
count, ::size_t 
#line 1507
offset, ::cudaMemcpyKind 
#line 1508
kind) 
#line 1509
{ 
#line 1510
return ::cudaGraphExecMemcpyNodeSetParamsToSymbol(hGraphExec, node, (const void *)(&symbol), src, count, offset, kind); 
#line 1511
} 
#line 1559
template< class T> static __inline ::cudaError_t 
#line 1560
cudaGraphExecMemcpyNodeSetParamsFromSymbol(::cudaGraphExec_t 
#line 1561
hGraphExec, ::cudaGraphNode_t 
#line 1562
node, void *
#line 1563
dst, const T &
#line 1564
symbol, ::size_t 
#line 1565
count, ::size_t 
#line 1566
offset, ::cudaMemcpyKind 
#line 1567
kind) 
#line 1568
{ 
#line 1569
return ::cudaGraphExecMemcpyNodeSetParamsFromSymbol(hGraphExec, node, dst, (const void *)(&symbol), count, offset, kind); 
#line 1570
} 
#line 1573
static __inline cudaError_t __stdcall cudaGraphExecUpdate(cudaGraphExec_t hGraphExec, cudaGraph_t hGraph, cudaGraphNode_t *hErrorNode_out, cudaGraphExecUpdateResult *updateResult_out) 
#line 1574
{ 
#line 1575
cudaGraphExecUpdateResultInfo resultInfo; 
#line 1576
cudaError_t status = cudaGraphExecUpdate(hGraphExec, hGraph, &resultInfo); 
#line 1577
if (hErrorNode_out) { 
#line 1578
(*hErrorNode_out) = (resultInfo.errorNode); 
#line 1579
}  
#line 1580
if (updateResult_out) { 
#line 1581
(*updateResult_out) = (resultInfo.result); 
#line 1582
}  
#line 1583
return status; 
#line 1584
} 
#line 1612
template< class T> static __inline ::cudaError_t 
#line 1613
cudaUserObjectCreate(::cudaUserObject_t *
#line 1614
object_out, T *
#line 1615
objectToWrap, unsigned 
#line 1616
initialRefcount, unsigned 
#line 1617
flags) 
#line 1618
{ 
#line 1619
return ::cudaUserObjectCreate(object_out, objectToWrap, [](void *
#line 1622
vpObj) { delete (reinterpret_cast< T *>(vpObj)); } , initialRefcount, flags); 
#line 1625
} 
#line 1627
template< class T> static __inline ::cudaError_t 
#line 1628
cudaUserObjectCreate(::cudaUserObject_t *
#line 1629
object_out, T *
#line 1630
objectToWrap, unsigned 
#line 1631
initialRefcount, ::cudaUserObjectFlags 
#line 1632
flags) 
#line 1633
{ 
#line 1634
return cudaUserObjectCreate(object_out, objectToWrap, initialRefcount, (unsigned)flags); 
#line 1635
} 
#line 1662 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
template< class T> static __inline ::cudaError_t 
#line 1663
cudaGetSymbolAddress(void **
#line 1664
devPtr, const T &
#line 1665
symbol) 
#line 1667
{ 
#line 1668
return ::cudaGetSymbolAddress(devPtr, (const void *)(&symbol)); 
#line 1669
} 
#line 1694
template< class T> static __inline ::cudaError_t 
#line 1695
cudaGetSymbolSize(::size_t *
#line 1696
size, const T &
#line 1697
symbol) 
#line 1699
{ 
#line 1700
return ::cudaGetSymbolSize(size, (const void *)(&symbol)); 
#line 1701
} 
#line 1746
template< class T> static __inline ::cudaError_t 
#line 1747
cudaFuncSetCacheConfig(T *
#line 1748
func, ::cudaFuncCache 
#line 1749
cacheConfig) 
#line 1751
{ 
#line 1752
return ::cudaFuncSetCacheConfig((const void *)func, cacheConfig); 
#line 1753
} 
#line 1755
template< class T> 
#line 1757
__declspec(deprecated) static __inline ::cudaError_t 
#line 1758
cudaFuncSetSharedMemConfig(T *
#line 1759
func, ::cudaSharedMemConfig 
#line 1760
config) 
#line 1762
{ 
#line 1767 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
#pragma warning(suppress: 4996)
#line 1769 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
return ::cudaFuncSetSharedMemConfig((const void *)func, config); 
#line 1773 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
} 
#line 1806 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
template< class T> static __inline ::cudaError_t 
#line 1807
cudaOccupancyMaxActiveBlocksPerMultiprocessor(int *
#line 1808
numBlocks, T 
#line 1809
func, int 
#line 1810
blockSize, ::size_t 
#line 1811
dynamicSMemSize) 
#line 1812
{ 
#line 1813
return ::cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(numBlocks, (const void *)func, blockSize, dynamicSMemSize, 0); 
#line 1814
} 
#line 1859
template< class T> static __inline ::cudaError_t 
#line 1860
cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *
#line 1861
numBlocks, T 
#line 1862
func, int 
#line 1863
blockSize, ::size_t 
#line 1864
dynamicSMemSize, unsigned 
#line 1865
flags) 
#line 1866
{ 
#line 1867
return ::cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(numBlocks, (const void *)func, blockSize, dynamicSMemSize, flags); 
#line 1868
} 
#line 1873
class __cudaOccupancyB2DHelper { 
#line 1874
size_t n; 
#line 1876
public: __cudaOccupancyB2DHelper(size_t n_) : n(n_) { } 
#line 1877
size_t operator()(int) 
#line 1878
{ 
#line 1879
return n; 
#line 1880
} 
#line 1881
}; 
#line 1929
template< class UnaryFunction, class T> static __inline ::cudaError_t 
#line 1930
cudaOccupancyMaxPotentialBlockSizeVariableSMemWithFlags(int *
#line 1931
minGridSize, int *
#line 1932
blockSize, T 
#line 1933
func, UnaryFunction 
#line 1934
blockSizeToDynamicSMemSize, int 
#line 1935
blockSizeLimit = 0, unsigned 
#line 1936
flags = 0) 
#line 1937
{ 
#line 1938
::cudaError_t status; 
#line 1941
int device; 
#line 1942
::cudaFuncAttributes attr; 
#line 1945
int maxThreadsPerMultiProcessor; 
#line 1946
int warpSize; 
#line 1947
int devMaxThreadsPerBlock; 
#line 1948
int multiProcessorCount; 
#line 1949
int funcMaxThreadsPerBlock; 
#line 1950
int occupancyLimit; 
#line 1951
int granularity; 
#line 1954
int maxBlockSize = 0; 
#line 1955
int numBlocks = 0; 
#line 1956
int maxOccupancy = 0; 
#line 1959
int blockSizeToTryAligned; 
#line 1960
int blockSizeToTry; 
#line 1961
int blockSizeLimitAligned; 
#line 1962
int occupancyInBlocks; 
#line 1963
int occupancyInThreads; 
#line 1964
::size_t dynamicSMemSize; 
#line 1970
if (((!minGridSize) || (!blockSize)) || (!func)) { 
#line 1971
return cudaErrorInvalidValue; 
#line 1972
}  
#line 1978
status = ::cudaGetDevice(&device); 
#line 1979
if (status != (cudaSuccess)) { 
#line 1980
return status; 
#line 1981
}  
#line 1983
status = cudaDeviceGetAttribute(&maxThreadsPerMultiProcessor, cudaDevAttrMaxThreadsPerMultiProcessor, device); 
#line 1987
if (status != (cudaSuccess)) { 
#line 1988
return status; 
#line 1989
}  
#line 1991
status = cudaDeviceGetAttribute(&warpSize, cudaDevAttrWarpSize, device); 
#line 1995
if (status != (cudaSuccess)) { 
#line 1996
return status; 
#line 1997
}  
#line 1999
status = cudaDeviceGetAttribute(&devMaxThreadsPerBlock, cudaDevAttrMaxThreadsPerBlock, device); 
#line 2003
if (status != (cudaSuccess)) { 
#line 2004
return status; 
#line 2005
}  
#line 2007
status = cudaDeviceGetAttribute(&multiProcessorCount, cudaDevAttrMultiProcessorCount, device); 
#line 2011
if (status != (cudaSuccess)) { 
#line 2012
return status; 
#line 2013
}  
#line 2015
status = cudaFuncGetAttributes(&attr, func); 
#line 2016
if (status != (cudaSuccess)) { 
#line 2017
return status; 
#line 2018
}  
#line 2020
funcMaxThreadsPerBlock = (attr.maxThreadsPerBlock); 
#line 2026
occupancyLimit = maxThreadsPerMultiProcessor; 
#line 2027
granularity = warpSize; 
#line 2029
if (blockSizeLimit == 0) { 
#line 2030
blockSizeLimit = devMaxThreadsPerBlock; 
#line 2031
}  
#line 2033
if (devMaxThreadsPerBlock < blockSizeLimit) { 
#line 2034
blockSizeLimit = devMaxThreadsPerBlock; 
#line 2035
}  
#line 2037
if (funcMaxThreadsPerBlock < blockSizeLimit) { 
#line 2038
blockSizeLimit = funcMaxThreadsPerBlock; 
#line 2039
}  
#line 2041
blockSizeLimitAligned = (((blockSizeLimit + (granularity - 1)) / granularity) * granularity); 
#line 2043
for (blockSizeToTryAligned = blockSizeLimitAligned; blockSizeToTryAligned > 0; blockSizeToTryAligned -= granularity) { 
#line 2047
if (blockSizeLimit < blockSizeToTryAligned) { 
#line 2048
blockSizeToTry = blockSizeLimit; 
#line 2049
} else { 
#line 2050
blockSizeToTry = blockSizeToTryAligned; 
#line 2051
}  
#line 2053
dynamicSMemSize = blockSizeToDynamicSMemSize(blockSizeToTry); 
#line 2055
status = cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(&occupancyInBlocks, func, blockSizeToTry, dynamicSMemSize, flags); 
#line 2062
if (status != (cudaSuccess)) { 
#line 2063
return status; 
#line 2064
}  
#line 2066
occupancyInThreads = (blockSizeToTry * occupancyInBlocks); 
#line 2068
if (occupancyInThreads > maxOccupancy) { 
#line 2069
maxBlockSize = blockSizeToTry; 
#line 2070
numBlocks = occupancyInBlocks; 
#line 2071
maxOccupancy = occupancyInThreads; 
#line 2072
}  
#line 2076
if (occupancyLimit == maxOccupancy) { 
#line 2077
break; 
#line 2078
}  
#line 2079
}  
#line 2087
(*minGridSize) = (numBlocks * multiProcessorCount); 
#line 2088
(*blockSize) = maxBlockSize; 
#line 2090
return status; 
#line 2091
} 
#line 2125
template< class UnaryFunction, class T> static __inline ::cudaError_t 
#line 2126
cudaOccupancyMaxPotentialBlockSizeVariableSMem(int *
#line 2127
minGridSize, int *
#line 2128
blockSize, T 
#line 2129
func, UnaryFunction 
#line 2130
blockSizeToDynamicSMemSize, int 
#line 2131
blockSizeLimit = 0) 
#line 2132
{ 
#line 2133
return cudaOccupancyMaxPotentialBlockSizeVariableSMemWithFlags(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, blockSizeLimit, 0); 
#line 2134
} 
#line 2171
template< class T> static __inline ::cudaError_t 
#line 2172
cudaOccupancyMaxPotentialBlockSize(int *
#line 2173
minGridSize, int *
#line 2174
blockSize, T 
#line 2175
func, ::size_t 
#line 2176
dynamicSMemSize = 0, int 
#line 2177
blockSizeLimit = 0) 
#line 2178
{ 
#line 2179
return cudaOccupancyMaxPotentialBlockSizeVariableSMemWithFlags(minGridSize, blockSize, func, ((::__cudaOccupancyB2DHelper)(dynamicSMemSize)), blockSizeLimit, 0); 
#line 2180
} 
#line 2210
template< class T> static __inline ::cudaError_t 
#line 2211
cudaOccupancyAvailableDynamicSMemPerBlock(::size_t *
#line 2212
dynamicSmemSize, T *
#line 2213
func, int 
#line 2214
numBlocks, int 
#line 2215
blockSize) 
#line 2216
{ 
#line 2217
return ::cudaOccupancyAvailableDynamicSMemPerBlock(dynamicSmemSize, (const void *)func, numBlocks, blockSize); 
#line 2218
} 
#line 2269
template< class T> static __inline ::cudaError_t 
#line 2270
cudaOccupancyMaxPotentialBlockSizeWithFlags(int *
#line 2271
minGridSize, int *
#line 2272
blockSize, T 
#line 2273
func, ::size_t 
#line 2274
dynamicSMemSize = 0, int 
#line 2275
blockSizeLimit = 0, unsigned 
#line 2276
flags = 0) 
#line 2277
{ 
#line 2278
return cudaOccupancyMaxPotentialBlockSizeVariableSMemWithFlags(minGridSize, blockSize, func, ((::__cudaOccupancyB2DHelper)(dynamicSMemSize)), blockSizeLimit, flags); 
#line 2279
} 
#line 2314
template< class T> static __inline ::cudaError_t 
#line 2315
cudaOccupancyMaxPotentialClusterSize(int *
#line 2316
clusterSize, T *
#line 2317
func, const ::cudaLaunchConfig_t *
#line 2318
config) 
#line 2319
{ 
#line 2320
return ::cudaOccupancyMaxPotentialClusterSize(clusterSize, (const void *)func, config); 
#line 2321
} 
#line 2358
template< class T> static __inline ::cudaError_t 
#line 2359
cudaOccupancyMaxActiveClusters(int *
#line 2360
numClusters, T *
#line 2361
func, const ::cudaLaunchConfig_t *
#line 2362
config) 
#line 2363
{ 
#line 2364
return ::cudaOccupancyMaxActiveClusters(numClusters, (const void *)func, config); 
#line 2365
} 
#line 2399
template< class T> static __inline ::cudaError_t 
#line 2400
cudaFuncGetAttributes(::cudaFuncAttributes *
#line 2401
attr, T *
#line 2402
entry) 
#line 2404
{ 
#line 2405
return ::cudaFuncGetAttributes(attr, (const void *)entry); 
#line 2406
} 
#line 2465
template< class T> static __inline ::cudaError_t 
#line 2466
cudaFuncSetAttribute(T *
#line 2467
func, ::cudaFuncAttribute 
#line 2468
attr, int 
#line 2469
value) 
#line 2471
{ 
#line 2472
return ::cudaFuncSetAttribute((const void *)func, attr, value); 
#line 2473
} 
#line 2498
template< class T> static __inline ::cudaError_t __stdcall 
#line 2499
cudaFuncGetName(const char **
#line 2500
name, T *
#line 2501
func) 
#line 2503
{ 
#line 2504
return ::cudaFuncGetName(name, (const void *)func); 
#line 2505
} 
#line 2521
template< class T> static __inline ::cudaError_t 
#line 2522
cudaGetKernel(::cudaKernel_t *
#line 2523
kernelPtr, T *
#line 2524
func) 
#line 2526
{ 
#line 2527
return ::cudaGetKernel(kernelPtr, (const void *)func); 
#line 2528
} 
#line 2559
template< class T> static __inline ::cudaError_t 
#line 2560
cudaLibraryGetGlobal(T **dptr, ::size_t *bytes, ::cudaLibrary_t library, const char *name) 
#line 2561
{ 
#line 2562
return ::cudaLibraryGetGlobal((void **)((void *)dptr), bytes, library, name); 
#line 2563
} 
#line 2593
template< class T> static __inline ::cudaError_t 
#line 2594
cudaLibraryGetManaged(T **dptr, ::size_t *bytes, ::cudaLibrary_t library, const char *name) 
#line 2595
{ 
#line 2596
return ::cudaLibraryGetManaged((void **)((void *)dptr), bytes, library, name); 
#line 2597
} 
#line 2623
template< class T> static __inline ::cudaError_t 
#line 2624
cudaLibraryGetUnifiedFunction(T **fptr, ::cudaLibrary_t library, const char *symbol) 
#line 2625
{ 
#line 2626
return ::cudaLibraryGetUnifiedFunction((void **)((void *)fptr), library, symbol); 
#line 2627
} 
#line 2640 "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.3/bin/../include\\cuda_runtime.h"
#pragma warning(pop)
#line 495 "CMakeCUDACompilerId.cu"
const char *info_compiler = ("INFO:compiler[NVIDIA]"); 
#line 497
const char *info_simulate = ("INFO:simulate[MSVC]"); 
#line 822 "CMakeCUDACompilerId.cu"
const char info_version[] = {'I', 'N', 'F', 'O', ':', 'c', 'o', 'm', 'p', 'i', 'l', 'e', 'r', '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', '[', (('0') + ((13 / 10000000) % 10)), (('0') + ((13 / 1000000) % 10)), (('0') + ((13 / 100000) % 10)), (('0') + ((13 / 10000) % 10)), (('0') + ((13 / 1000) % 10)), (('0') + ((13 / 100) % 10)), (('0') + ((13 / 10) % 10)), (('0') + (13 % 10)), '.', (('0') + ((3 / 10000000) % 10)), (('0') + ((3 / 1000000) % 10)), (('0') + ((3 / 100000) % 10)), (('0') + ((3 / 10000) % 10)), (('0') + ((3 / 1000) % 10)), (('0') + ((3 / 100) % 10)), (('0') + ((3 / 10) % 10)), (('0') + (3 % 10)), '.', (('0') + ((73 / 10000000) % 10)), (('0') + ((73 / 1000000) % 10)), (('0') + ((73 / 100000) % 10)), (('0') + ((73 / 10000) % 10)), (('0') + ((73 / 1000) % 10)), (('0') + ((73 / 100) % 10)), (('0') + ((73 / 10) % 10)), (('0') + (73 % 10)), ']', '\000'}; 
#line 851 "CMakeCUDACompilerId.cu"
const char info_simulate_version[] = {'I', 'N', 'F', 'O', ':', 's', 'i', 'm', 'u', 'l', 'a', 't', 'e', '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', '[', (('0') + (((1951 / 100) / 10000000) % 10)), (('0') + (((1951 / 100) / 1000000) % 10)), (('0') + (((1951 / 100) / 100000) % 10)), (('0') + (((1951 / 100) / 10000) % 10)), (('0') + (((1951 / 100) / 1000) % 10)), (('0') + (((1951 / 100) / 100) % 10)), (('0') + (((1951 / 100) / 10) % 10)), (('0') + ((1951 / 100) % 10)), '.', (('0') + (((1951 % 100) / 10000000) % 10)), (('0') + (((1951 % 100) / 1000000) % 10)), (('0') + (((1951 % 100) / 100000) % 10)), (('0') + (((1951 % 100) / 10000) % 10)), (('0') + (((1951 % 100) / 1000) % 10)), (('0') + (((1951 % 100) / 100) % 10)), (('0') + (((1951 % 100) / 10) % 10)), (('0') + ((1951 % 100) % 10)), ']', '\000'}; 
#line 871 "CMakeCUDACompilerId.cu"
const char *info_platform = ("INFO:platform[Windows]"); 
#line 872
const char *info_arch = ("INFO:arch[x64]"); 
#line 877
const char *info_host_compiler = ("INFO:host_compiler[MSVC]"); 
#line 882 "CMakeCUDACompilerId.cu"
const char info_host_compiler_version[] = {'I', 'N', 'F', 'O', ':', 'h', 'o', 's', 't', '_', 'c', 'o', 'm', 'p', 'i', 'l', 'e', 'r', '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', '[', (('0') + (((1951 / 100) / 10000000) % 10)), (('0') + (((1951 / 100) / 1000000) % 10)), (('0') + (((1951 / 100) / 100000) % 10)), (('0') + (((1951 / 100) / 10000) % 10)), (('0') + (((1951 / 100) / 1000) % 10)), (('0') + (((1951 / 100) / 100) % 10)), (('0') + (((1951 / 100) / 10) % 10)), (('0') + ((1951 / 100) % 10)), '.', (('0') + (((1951 % 100) / 10000000) % 10)), (('0') + (((1951 % 100) / 1000000) % 10)), (('0') + (((1951 % 100) / 100000) % 10)), (('0') + (((1951 % 100) / 10000) % 10)), (('0') + (((1951 % 100) / 1000) % 10)), (('0') + (((1951 % 100) / 100) % 10)), (('0') + (((1951 % 100) / 10) % 10)), (('0') + ((1951 % 100) % 10)), '.', (('0') + (((195136247 % 100000) / 10000000) % 10)), (('0') + (((195136247 % 100000) / 1000000) % 10)), (('0') + (((195136247 % 100000) / 100000) % 10)), (('0') + (((195136247 % 100000) / 10000) % 10)), (('0') + (((195136247 % 100000) / 1000) % 10)), (('0') + (((195136247 % 100000) / 100) % 10)), (('0') + (((195136247 % 100000) / 10) % 10)), (('0') + ((195136247 % 100000) % 10)), '.', (('0') + ((0 / 10000000) % 10)), (('0') + ((0 / 1000000) % 10)), (('0') + ((0 / 100000) % 10)), (('0') + ((0 / 10000) % 10)), (('0') + ((0 / 1000) % 10)), (('0') + ((0 / 100) % 10)), (('0') + ((0 / 10) % 10)), (('0') + (0 % 10)), ']', '\000'}; 
#line 914 "CMakeCUDACompilerId.cu"
const char *info_language_standard_default = ("INFO:standard_default[14]"); 
#line 932 "CMakeCUDACompilerId.cu"
const char *info_language_extensions_default = ("INFO:extensions_default[OFF]"); 
#line 943 "CMakeCUDACompilerId.cu"
int main(int argc, char *argv[]) 
#line 944
{ 
#line 945
int require = 0; 
#line 946
require += (info_compiler[argc]); 
#line 947
require += (info_platform[argc]); 
#line 949
require += (info_version[argc]); 
#line 952 "CMakeCUDACompilerId.cu"
require += (info_simulate[argc]); 
#line 955 "CMakeCUDACompilerId.cu"
require += (info_simulate_version[argc]); 
#line 958 "CMakeCUDACompilerId.cu"
require += (info_host_compiler[argc]); 
#line 961 "CMakeCUDACompilerId.cu"
require += (info_host_compiler_version[argc]); 
#line 963 "CMakeCUDACompilerId.cu"
require += (info_language_standard_default[argc]); 
#line 964
require += (info_language_extensions_default[argc]); 
#line 965
(void)argv; 
#line 966
return require; 
#line 967
} 
#line 1 "CMakeCUDACompilerId.cudafe1.stub.c"
#define _NV_ANON_NAMESPACE _GLOBAL__N__6e3dc18f_22_CMakeCUDACompilerId_cu_bd57c623
#ifdef _NV_ANON_NAMESPACE
#endif
#pragma pack()
#line 1 "CMakeCUDACompilerId.cudafe1.stub.c"
#include "CMakeCUDACompilerId.cudafe1.stub.c"
#line 1 "CMakeCUDACompilerId.cudafe1.stub.c"
#undef _NV_ANON_NAMESPACE
