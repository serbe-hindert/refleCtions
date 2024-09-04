#ifndef REFLECTIVE_TYPES_H
#define REFLECTIVE_TYPES_H

#pragma region rtUtils
#define RT_CAT_FIRST_STEP(a, b) a ## b
#define RT_CAT_SECOND_STEP(a, b) RT_CAT_FIRST_STEP(a, b)
#define RT_CAT(a, b) RT_CAT_SECOND_STEP(a, b)
#pragma endregion rtUtils

#pragma region rtEval
#define RT_EVAL0(...) __VA_ARGS__
#define RT_EVAL1(...) RT_EVAL0(RT_EVAL0(RT_EVAL0(__VA_ARGS__)))
#define RT_EVAL2(...) RT_EVAL1(RT_EVAL1(RT_EVAL1(__VA_ARGS__)))
#define RT_EVAL3(...) RT_EVAL2(RT_EVAL2(RT_EVAL2(__VA_ARGS__)))
#define RT_EVAL4(...) RT_EVAL3(RT_EVAL3(RT_EVAL3(__VA_ARGS__)))
#define RT_EVAL(...)  RT_EVAL4(RT_EVAL4(RT_EVAL4(__VA_ARGS__)))
#pragma endregion rtEval

#pragma region rtStructMap
#define RT_STRUCT_MAP_END(...)
#define RT_STRUCT_MAP_OUT

#define RT_STRUCT_MAP_GET_END2() 0, RT_STRUCT_MAP_END
#define RT_STRUCT_MAP_GET_END1(...) RT_STRUCT_MAP_GET_END2
#define RT_STRUCT_MAP_GET_END(...)  RT_STRUCT_MAP_GET_END1

#define RT_STRUCT_MAP_NEXT0(test, next, ...) next RT_STRUCT_MAP_OUT
#define RT_STRUCT_MAP_NEXT1(test, next) RT_STRUCT_MAP_NEXT0(test, next, 0)
#define RT_STRUCT_MAP_NEXT(test, next) RT_STRUCT_MAP_NEXT1(RT_STRUCT_MAP_GET_END test, next)

#define RT_STRUCT_MAP0(f, x, y, peek, ...) f(x, y) RT_STRUCT_MAP_NEXT(peek, RT_STRUCT_MAP1)(f, peek, __VA_ARGS__)
#define RT_STRUCT_MAP1(f, x, y, peek, ...) f(x, y) RT_STRUCT_MAP_NEXT(peek, RT_STRUCT_MAP0)(f, peek, __VA_ARGS__)
#define RT_STRUCT_MAP(f, ...) RT_EVAL(RT_STRUCT_MAP1(f, __VA_ARGS__, ()()(), ()()(), 0))

#define RT_DECLARE_STRUCT_MEMBERS(type, member) type member;
#pragma endregion rtStructMap

#pragma region rtCountMap
#define RT_COUNT_MAP_END(...)
#define RT_COUNT_MAP_OUT

#define RT_COUNT_MAP_GET_END2() 0, RT_COUNT_MAP_END
#define RT_COUNT_MAP_GET_END1(...) RT_COUNT_MAP_GET_END2
#define RT_COUNT_MAP_GET_END(...)  RT_COUNT_MAP_GET_END1

#define RT_COUNT_MAP_NEXT0(test, next, ...) next RT_COUNT_MAP_OUT
#define RT_COUNT_MAP_NEXT1(test, next) RT_COUNT_MAP_NEXT0(test, next, 0)
#define RT_COUNT_MAP_NEXT(test, next) RT_COUNT_MAP_NEXT1(RT_COUNT_MAP_GET_END test, next)

#define RT_COUNT_MAP0(f, x, y, peek, ...) f() RT_COUNT_MAP_NEXT(peek, RT_COUNT_MAP1)(f, peek, __VA_ARGS__)
#define RT_COUNT_MAP1(f, x, y, peek, ...) f() RT_COUNT_MAP_NEXT(peek, RT_COUNT_MAP0)(f, peek, __VA_ARGS__)
#define RT_COUNT_MAP(f, ...) RT_EVAL(RT_COUNT_MAP1(f, __VA_ARGS__, ()()(), ()()(), 0))

#define RT_DECLARE_COUNT_MEMBERS() +1
#pragma endregion rtCountMap

#pragma region rtTypeSizeMap
#define RT_TYPESIZE_MAP_END(...)
#define RT_TYPESIZE_MAP_OUT

#define RT_TYPESIZE_MAP_GET_END2() 0, RT_TYPESIZE_MAP_END
#define RT_TYPESIZE_MAP_GET_END1(...) RT_TYPESIZE_MAP_GET_END2
#define RT_TYPESIZE_MAP_GET_END(...)  RT_TYPESIZE_MAP_GET_END1

#define RT_TYPESIZE_MAP_NEXT0(test, next, ...) next RT_TYPESIZE_MAP_OUT
#define RT_TYPESIZE_MAP_NEXT1(test, next) RT_TYPESIZE_MAP_NEXT0(test, next, 0)
#define RT_TYPESIZE_MAP_NEXT(test, next) RT_TYPESIZE_MAP_NEXT1(RT_TYPESIZE_MAP_GET_END test, next)

#define RT_TYPESIZE_MAP0(f, x, y, peek, ...) f(x) RT_TYPESIZE_MAP_NEXT(peek, RT_TYPESIZE_MAP1)(f, peek, __VA_ARGS__)
#define RT_TYPESIZE_MAP1(f, x, y, peek, ...) f(x) RT_TYPESIZE_MAP_NEXT(peek, RT_TYPESIZE_MAP0)(f, peek, __VA_ARGS__)
#define RT_TYPESIZE_MAP(f, ...) RT_EVAL(RT_TYPESIZE_MAP1(f, __VA_ARGS__, ()()(), ()()(), 0))

#define RT_DECLARE_TYPESIZE_MEMBERS(type) sizeof(type),
#pragma endregion rtTypeSizeMap

#pragma region rtOffsetMap
#define RT_OFFSET_MAP_END(...)
#define RT_OFFSET_MAP_OUT

#define RT_OFFSET_MAP_GET_END2() 0, RT_OFFSET_MAP_END
#define RT_OFFSET_MAP_GET_END1(...) RT_OFFSET_MAP_GET_END2
#define RT_OFFSET_MAP_GET_END(...)  RT_OFFSET_MAP_GET_END1

#define RT_OFFSET_MAP_NEXT0(test, next, ...) next RT_OFFSET_MAP_OUT
#define RT_OFFSET_MAP_NEXT1(test, next) RT_OFFSET_MAP_NEXT0(test, next, 0)
#define RT_OFFSET_MAP_NEXT(test, next) RT_OFFSET_MAP_NEXT1(RT_OFFSET_MAP_GET_END test, next)

#define RT_OFFSET_MAP0(f, structName, x, y, peek, ...) f(structName, y) RT_OFFSET_MAP_NEXT(peek, RT_OFFSET_MAP1)(f, structName, peek, __VA_ARGS__)
#define RT_OFFSET_MAP1(f, structName, x, y, peek, ...) f(structName, y) RT_OFFSET_MAP_NEXT(peek, RT_OFFSET_MAP0)(f, structName, peek, __VA_ARGS__)
#define RT_OFFSET_MAP(f, structName, ...) RT_EVAL(RT_OFFSET_MAP1(f, structName, __VA_ARGS__, ()()(), ()()(), 0))

#define RT_DECLARE_OFFSET_MEMBERS(structName, member) ((typeof(sizeof(const struct structName))) &(((const struct structName *)nullptr)->member)),
#pragma endregion rtOffsetMap



#define RT_DEFINE_STRUCT(structName, ...) \
    struct structName { \
        RT_STRUCT_MAP(RT_DECLARE_STRUCT_MEMBERS, __VA_ARGS__) \
    }; \
    \
    constexpr typeof(sizeof(struct structName)) RT_CAT(RT_STRUCT_NUMBER_OF_MEMBERS_, structName) = RT_COUNT_MAP(RT_DECLARE_COUNT_MEMBERS, __VA_ARGS__); \
    constexpr typeof(sizeof(struct structName)) RT_CAT(RT_STRUCT_TYPESIZES_OF_, structName)[RT_COUNT_MAP(RT_DECLARE_COUNT_MEMBERS, __VA_ARGS__)] = {RT_TYPESIZE_MAP(RT_DECLARE_TYPESIZE_MEMBERS, __VA_ARGS__)}; \
    const typeof(sizeof(struct structName)) RT_CAT(RT_STRUCT_OFFSETS_OF_, structName)[RT_COUNT_MAP(RT_DECLARE_COUNT_MEMBERS, __VA_ARGS__)] = {RT_OFFSET_MAP(RT_DECLARE_OFFSET_MEMBERS, structName, __VA_ARGS__)};

#define RT_GET_MEMBERS_AMOUNT(structName) (RT_CAT(RT_STRUCT_NUMBER_OF_MEMBERS_, structName))
#define RT_GET_MEMBER_SIZE(structName, memberIndex) (RT_CAT(RT_STRUCT_TYPESIZES_OF_, structName)[memberIndex])
#define RT_GET_MEMBER_REFERENCE(structName, structReference, memberIndex) ((((void*)structReference) + RT_CAT(RT_STRUCT_OFFSETS_OF_, structName)[memberIndex]))

#endif //REFLECTIVE_TYPES_H
