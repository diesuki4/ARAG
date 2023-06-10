// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(ARAG, Log, All);

// 함수명과 라인 문자열
#define ARLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
// ARLOG_CALLINFO 출력
#define ARLOG_S(Verbosity) UE_LOG(ARAG, Verbosity, TEXT("%s"), *ARLOG_CALLINFO)
// ARLOG_CALLINFO의 UE_LOG 래퍼
#define ARLOG(Verbosity, Format, ...) UE_LOG(ARAG, Verbosity, TEXT("%s %s"), *ARLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
// 조건부 Assert
#define ARCHECK(Expr, ...) { if (!(Expr)) { ARLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }
