#ifndef BABA_IS_YOU_UTILS_H
#define BABA_IS_YOU_UTILS_H

#define ENUM(name, ...) \
enum name{__VA_ARGS__}; \
static const char *name##HintString = #__VA_ARGS__;

#endif //BABA_IS_YOU_UTILS_H
