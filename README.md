# Reflective macros in C

## Define struct
To define a struct use the RT_DEFINE_STRUCT macro:

```
RT_DEFINE_STRUCT(name,
    int, m1,
    char, m2
)
```

## Amount of members
```RT_GET_MEMBERS_AMOUNT(name)```

## Size of member
```RT_GET_MEMBER_SIZE(name, 0)```

## Referemce to member
```RT_GET_MEMBER_REFERENCE(name, &myName, 0)```
