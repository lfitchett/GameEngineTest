#include "pch.h"

#define NUMARGS(...)  std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value

#define SequentialEnum(Name,...) \
enum Name { __VA_ARGS__ }; \
namespace \
{ \
	const std::initializer_list<Name> Name##List{ __VA_ARGS__ }; \
	const size_t Name##Size = NUMARGS(__VA_ARGS__); \
}; \

SequentialEnum(EventPriority,
	CollisionDetection,
	Calculation,
	Rendering
);